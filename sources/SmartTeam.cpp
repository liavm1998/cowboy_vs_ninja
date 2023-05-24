#include "SmartTeam.hpp"

namespace ariel{
    SmartTeam::SmartTeam(Character* c):Team(c){}
    Character* NinTarget( const vector<Character*> &team , Ninja* nin) {
        double minDistance = std::numeric_limits<double>::max();
        Character* closestEnemy = nullptr;
        for (Character* ene : team) {
            if(ene->isAlive()){
                double distance = ene->distance(nin);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestEnemy = ene;
                }
            }
        }
        return closestEnemy;
    }

    Character* CowboyTarget(Team* enemy){
        for(auto* target: enemy->getMembers()){
            if(auto* cowboy = dynamic_cast<Cowboy*>(target)){
                if(cowboy->isAlive())
                    return target;
            }
        }
        for(auto* target: enemy->getMembers()){
            if(target->isAlive()){
                return target;
            }
        }
        return nullptr;
    }

    void SmartTeam::attack(Team* enemy){
            if(enemy == nullptr){
            throw  std::invalid_argument("");
        }

        for(auto* character : this->getMembers()){
            if(!character->isAlive())
                continue;
            
            
            if(auto* cowboy = dynamic_cast<Cowboy*>(character)){
                Character* target = CowboyTarget(enemy);
                if(target == nullptr){return;}
                if(cowboy->hasboolets()){
                    cowboy->shoot(target);
                }
                else{
                    cowboy->reload();
                }
            }
            else{
                auto* nin = dynamic_cast<Ninja*>(character);
                Character* target = NinTarget(enemy->getMembers(), nin);
                if(nin->distance(target) <= 1)
                    nin->slash(target);
                else
                    nin->move(target);
            }
        }
    }

}