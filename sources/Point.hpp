
#pragma once
//for student test1
#include <stdexcept>
#include <iostream>

namespace ariel{
    class Point{
    private:
        double pos_x;
        double pos_y;
    public:
        Point():pos_x(0),pos_y(0){};
        Point(double _pos_x, double _pos_y);
    
        double distance(Point other);
        void moveTowards(Point other,double dist);

        static Point moveTowards(Point cur, Point other, double dist);

        double getX() const;
        double getY() const;
        std::string print() const;
    };
}