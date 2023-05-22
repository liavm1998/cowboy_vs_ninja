#pragma once
#include "Cowboy.hpp"
#include "Ninja.hpp"

namespace ariel{
    class Iteam{
        private:
            Character* teamLeader;
        protected:
            Character* getTeamLeader() const {
                return teamLeader;
            }
        public:
            Iteam(Character* character):teamLeader(character){};
            virtual void add(Character*) = 0;
            virtual int stillAlive() = 0;
            virtual void attack(Iteam* another)= 0;
            virtual void print()= 0;
            virtual ~Iteam() = default;
            Iteam(const Iteam&) = default;
            Iteam& operator=(const Iteam&) = default;
            Iteam(Iteam&&) = default;
            Iteam& operator=(Iteam&&) = default;
    };

}
