
#include "Team2.hpp"

namespace ariel{

    Team2::Team2(Character* Character):Team(Character){}

    void Team2::attack(Team* enemy){
        if(enemy == nullptr){
            throw  std::invalid_argument("");
        }
        this->changeCaptain();

        for(auto* character : this->getMembers()){
            if(!character->isAlive())
                continue;
            Character* target = closestToCap(enemy->getMembers());
            if(target == nullptr){return;}
            if(auto* cowboy = dynamic_cast<Cowboy*>(character)){
                if(cowboy->hasboolets()){
                    cowboy->shoot(target);
                }
                else{
                    cowboy->reload();
                }
            }
            else{
                auto* nin = dynamic_cast<Ninja*>(character);
                if(nin->distance(target) <= 1)
                    nin->slash(target);
                else
                    nin->move(target);
            }
        }
    }
    void Team2::print(){
        for(auto* character:this->getMembers()){
            cout << character->print() <<endl;
        }
    }
}