#include "right_polygone.h"

Right_Polygone::Right_Polygone() {}
qreal Right_Polygone::area(){
    return 0.25 * apexes_num * side * side / std::tan(M_PI / apexes_num);
}
qreal Right_Polygone::perimeter(){
    return apexes_num * side;
}
void Right_Polygone::change_side(double spinside){
    side = spinside;
    calculate_points();
}
void Right_Polygone::calculate_points(){
    points.resize(apexes_num);
    pointsx.resize(apexes_num);
    pointsy.resize(apexes_num);

    double angleIncrement = 2 * M_PI / apexes_num;

    for (int i = 0; i < apexes_num; ++i) {
        double angle = i * angleIncrement;
        pointsx[i]  = side * std::cos(angle);
        pointsy[i] = side * std::sin(angle);

        points[i] = QPointF(pointsx[i], pointsy[i]);
    }

    centerset();

}
void Right_Polygone::number_apexes(int number){
    apexes_num = number;
    calculate_points();
}
