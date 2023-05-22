

#pragma once
#include "Character.hpp"

namespace ariel{
    class Cowboy:public Character{
        private:
            int bullets;
        public:
            Cowboy(string name, Point location);
            bool hasboolets();
            void shoot(Character * enemy);
            void reload();
            string print() override;           
    };
    
}