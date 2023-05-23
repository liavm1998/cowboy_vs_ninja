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
        void CowboysAttack(const Team& enemy);
        void NinjaAttack(const Team& enemy);

        virtual void print();
        Character* closestToCap(const vector<Character*> &team);
        void changeCaptain();
        Character* GetCaptain();
        vector<Character*> getMembers() const;

        virtual ~Team();
        Team(const Team& other) = default;
        Team& operator=(const Team& other) = default;
        Team(Team&& other) = default;
        Team& operator=(Team&& other) = default;

    };
}