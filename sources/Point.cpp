#include <math.h>
#include "Point.hpp"

namespace ariel{
    Point::Point(double _pos_x, double _pos_y): pos_x(_pos_x), pos_y(_pos_y){}
    double Point::distance(Point other){
        return sqrt(pow(this->pos_x - other.pos_x,2) + pow(this->pos_y - other.pos_y,2));
    }
    void Point::moveTowards(Point other,double dist){
        if(dist<0){
            throw std::invalid_argument("");
        }
        double deltaX = other.pos_x - pos_x;
        double deltaY = other.pos_y - pos_y;

        double ratio = dist / distance(other);
        if(ratio >= 1)
            ratio = 1;

        pos_x += ratio * deltaX;
        pos_y += ratio * deltaY;
    }
    Point Point::moveTowards(Point cur, Point other, double dist){
        Point ret_p(cur.getX(),cur.getY());
        ret_p.moveTowards(other,dist);
        return ret_p;
    }
    double Point::getX()const{ return this->pos_x;}
    double Point::getY()const{ return this->pos_y;}
    std::string Point::print()const{
        return "("+ std::to_string(getX()) + "," +std::to_string(getY()) + ")";
    }
}