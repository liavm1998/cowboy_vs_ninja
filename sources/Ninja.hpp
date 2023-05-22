
#pragma once
#include "Character.hpp"

namespace ariel{
    class Ninja:public Character{
        private:
            int speed;
        protected:
            Ninja(Point _loc,int health , string name,int _speed):Character(_loc,health,std::move(name)),speed(_speed){}
        public:
            void move(Character* character);
            void slash(Character* character);
            string print() override;
            int getSpeed();
    };

    class OldNinja:public Ninja{
        public:
            OldNinja(string name, Point location);
    };
    class TrainedNinja:public Ninja{
        public:
            TrainedNinja(string name, Point location);
    };
    class YoungNinja:public Ninja{
        public:
            YoungNinja(string name, Point location);
    };
}
