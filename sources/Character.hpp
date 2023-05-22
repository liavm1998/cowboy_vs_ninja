
#pragma once
#include "Point.hpp"
#include <string>

constexpr int default_hp = 100;
using namespace std;
namespace ariel {
    class Character{
        private:
            Point location;
            int health;
            string name;
            bool inTeam;
        public:
            Character()=delete;
            Character(const Character&) = delete;
            Character& operator=(const Character&) = delete;
            Character(Character&&) = delete;
            Character& operator=(Character&&) = delete;

            Character(Point _loc , int _health, string _name);
            bool isAlive();
            double distance(const Character* another);
            void hit(int damage);
            string getName();
            Point getLocation();
            virtual string print() = 0;
            virtual ~Character() = default;

            //for test implemention
            int getHealth();
            void setInTeam();
            bool isInTeam();
            void SetLocation(Point new_loc);
    };
}