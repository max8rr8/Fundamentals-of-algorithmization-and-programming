#pragma once

#include "Date.h"
#include <QFile>
#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
  
public:
  MainWindow();

private:
  void loadFile(QByteArray contents);
  void updateTable();
  void updateRowNext(int row);
  void updateRow(int row);

  void updateSidebar();

private slots:
  void onOpenClick();
  void onNewClick();
  void onSelectedRow();
  void onBirthdayChanged(QDate date);

  void onEditEntry();
  void onAddEntry();
  void onDeleteEntry();

protected:
  QFile *file;
  Ui::MainWindow *ui;
  QVector<Date> dates;
  QVector<int> filePos;
  Date birthday;
  int selectedRow;
};