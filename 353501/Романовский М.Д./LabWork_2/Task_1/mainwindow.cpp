#include <QDateEdit>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <exception>
#include <qdatetimeedit.h>
#include <qerrormessage.h>
#include <qlogging.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <stdexcept>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow() : ui(new Ui::MainWindow), birthday(2006, 2, 7) {
  file = nullptr;

  ui->setupUi(this);

  connect(ui->openFile, &QPushButton::clicked, this, &MainWindow::onOpenClick);
  connect(ui->newFile, &QPushButton::clicked, this, &MainWindow::onNewClick);
  connect(ui->mainTable, &QTableWidget::itemSelectionChanged, this,
          &MainWindow::onSelectedRow);

  connect(ui->birthdayInp, &QDateEdit::dateChanged, this,
          &MainWindow::onBirthdayChanged);

  connect(ui->editEntry, &QPushButton::clicked, this, &MainWindow::onEditEntry);
  connect(ui->addEntry, &QPushButton::clicked, this, &MainWindow::onAddEntry);
  connect(ui->deleteEntry, &QPushButton::clicked, this,
          &MainWindow::onDeleteEntry);

  selectedRow = -1;
  updateSidebar();
}

void MainWindow::loadFile(QByteArray contents) {
  dates.clear();
  if (contents.length() == 0)
    return updateTable();

  int pos = 0;
  while (pos < contents.length()) {
    if (contents[pos] == ' ' || contents[pos] == '\n' ||
        contents[pos] == '\t') {
      pos++;
    } else {
      if (pos + 10 > contents.length())
        throw std::invalid_argument("Not enough file");

      QByteArray dateBytes = contents.sliced(pos, 10);
      dates.append(Date::FromString(dateBytes.toStdString()));
      filePos.append(pos);

      pos += 10;
    }
  }

  updateTable();
}

void MainWindow::updateTable() {
  ui->mainTable->setRowCount(dates.count());
  for (int i = 0; i < dates.count(); i++) {
    updateRow(i);
  }
}

void MainWindow::updateRowNext(int row) {
  if (row < 0)
    return;

  Date date = dates[row];
  QString val;
  if (row + 1 < dates.count()) {
    val = QString::number(date.Duration(dates[row + 1]));
  }

  ui->mainTable->setItem(row, 2, new QTableWidgetItem(val));
}

void MainWindow::updateRow(int row) {
  if (row < 0)
    return;

  Date date = dates[row];

  ui->mainTable->setItem(
      row, 0, new QTableWidgetItem(QString::fromStdString(date.ToString())));
  ui->mainTable->setItem(
      row, 1,
      new QTableWidgetItem(QString::fromStdString(date.NextDay().ToString())));

  updateRowNext(row);
  updateRowNext(row - 1);
}

void MainWindow::onOpenClick() {
  QString fileName = QFileDialog::getOpenFileName(this, "Open File", "",
                                                  tr("Text files (*.txt)"));
  if (fileName.length() == 0)
    return;

  if (file) {
    file->close();
    delete file;
    file = nullptr;
  }

  file = new QFile(fileName, this);

  try {
    file->open(QFile::ReadWrite);

    QByteArray contents = file->readAll();
    loadFile(contents);
  } catch (std::exception &e) {
    QMessageBox::critical(this, "Failed to load file",
                          QString("Failed to load file:\n%0").arg(e.what()));
  }
}

void MainWindow::onNewClick() {
  QString fileName = QFileDialog::getSaveFileName(this, "New File", "",
                                                  tr("Text files (*.txt)"));
  if (fileName.length() == 0)
    return;

  if (file) {
    file->close();
    delete file;
    file = nullptr;
  }

  try {
    {
      QFile f(fileName);
      f.open(QFile::WriteOnly | QFile::Truncate);
      f.write("\n");
      f.close();
    }

    file = new QFile(fileName, this);
    file->open(QFile::ReadWrite);
    updateTable();
  } catch (std::exception &e) {
    QMessageBox::critical(this, "Failed to load file",
                          QString("Failed to load file:\n%0").arg(e.what()));
  }
}

void MainWindow::onSelectedRow() {
  auto selected = ui->mainTable->selectedItems();
  if (selected.count() > 0) {
    selectedRow = selected[0]->row();
  } else {
    selectedRow = -1;
  }

  updateSidebar();
}

void MainWindow::updateSidebar() {
  if (selectedRow >= dates.count())
    selectedRow = -1;

  ui->editEntry->setDisabled(selectedRow == -1);
  ui->deleteEntry->setDisabled(selectedRow == -1);

  Date today = Date::FromQDate(QDate::currentDate());
  Date selected = selectedRow != -1 ? dates[selectedRow] : today;

  ui->todayDate->setText(QString::fromStdString(today.ToString()));
  ui->tilToday->setText(QString::number(today.Duration(selected)));

  ui->tilBirth->setText(
      QString::number(selected.DaysTillYourBithday(birthday)));

  ui->nextDay->setText(QString::fromStdString(selected.NextDay().ToString()));
  ui->prevDay->setText(
      QString::fromStdString(selected.PreviousDay().ToString()));

  ui->isLeap->setText(selected.IsLeap() ? "YES" : "NO");
  ui->weekNumber->setText(QString::number(selected.WeekNumber()));
}

void MainWindow::onBirthdayChanged(QDate date) {
  birthday = Date::FromQDate(date);
  updateSidebar();
}

void MainWindow::onEditEntry() {
  bool ok;
  QString newDateS = QInputDialog::getText(
      this, "Edit entry", "New date:", QLineEdit::Normal,
      QString::fromStdString(dates[selectedRow].ToString()), &ok);
  if (!ok)
    return;

  try {
    Date newDate = Date::FromString(newDateS.toStdString());
    dates[selectedRow] = newDate;
    updateRow(selectedRow);

    if (file) {
      file->seek(filePos[selectedRow]);
      file->write(QByteArray::fromStdString(newDate.ToString()));
      file->flush();
    }
  } catch (std::exception &e) {
    QMessageBox::critical(this, "Failed to load file",
                          QString("Failed to load file:\n%0").arg(e.what()));
  }
}

void MainWindow::onAddEntry() {
  bool ok;

  Date today = Date::FromQDate(QDate::currentDate());
  QString newDateS =
      QInputDialog::getText(this, "Add entry", "New date:", QLineEdit::Normal,
                            QString::fromStdString(today.ToString()), &ok);
  if (!ok)
    return;

  try {
    Date newDate = Date::FromString(newDateS.toStdString());
    dates.push_back(newDate);
    ui->mainTable->setRowCount(dates.count());
    updateRow(dates.count() - 1);

    if (file) {
      file->seek(file->size());
      filePos.push_back(file->size() + 1);
      file->write(QByteArray::fromStdString("\n" + newDate.ToString()));
      file->flush();
    }
  } catch (std::exception &e) {
    QMessageBox::critical(this, "Failed to load file",
                          QString("Failed to load file:\n%0").arg(e.what()));
  }
}

void MainWindow::onDeleteEntry() {
  if (selectedRow >= dates.count())
    return;

  if (selectedRow == -1)
    return;
  dates.remove(selectedRow);
  if (file) {
    file->seek(filePos[selectedRow]);
    file->write("          ");
    file->flush();
    filePos.remove(selectedRow);
  }

  ui->mainTable->removeRow(selectedRow);
  updateRow(selectedRow - 1);

  updateTable();
  ui->mainTable->clearSelection();
}