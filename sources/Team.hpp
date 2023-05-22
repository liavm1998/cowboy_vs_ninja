#pragma once
#include <vector>
#include "Ninja.hpp"
#include "Cowboy.hpp"
namespace ariel{
    class Team{
        private:
            Character* captain;
            std::vector<Character*> members;
        public:
            Team(Character*);
            virtual void add(Character* character) ;
            virtual int stillAlive();
            virtual void attack(Team* other);
            virtual void print();
            Character* closestToCap(std::vector<Character*> enemy);
            void changeCaptain();
            Character* GetCaptain();
            vector<Character*> getMembers();
            
            virtual ~Team();
            Team(const Team& other) = default;
            Team& operator=(const Team& other) = default;
            Team(Team&& other) = default;
            Team& operator=(Team&& other) = default;
    };
}