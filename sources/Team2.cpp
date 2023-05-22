
#include "Team2.hpp"

namespace ariel{
    template<typename Base, typename T>
    inline bool instanceof(const T*) {
        return std::is_base_of<Base, T>::value;
    }
    Team2::Team2(Character* Character):Team(Character){}
    
    void Team2::attack(Team* enemy){
        if(enemy == nullptr){
            throw  std::invalid_argument("");
        }
        if(!enemy->stillAlive())
        {
            throw std::runtime_error("");
        }
        this->changeCaptain();
        

        for(size_t i = 0; i < this->getMembers().size(); i++){
            // attacker
            Character* character = this->getMembers()[i];
            if(!character->isAlive()){
                continue;
            }
            // defender
            Character* target = closestToCap(enemy->getMembers());
            if(target == nullptr){return;}
            if(Cowboy* cowboy = dynamic_cast<Cowboy*>(character)){
                if(cowboy->hasboolets())
                {
                    cowboy->shoot(target);
                    if(target == enemy->GetCaptain() && !enemy->GetCaptain()->isAlive()){
                        enemy->changeCaptain();
                    }
                }
                else{
                    cowboy->reload();
                }
            }
            else{
                Ninja* nin = dynamic_cast<Ninja*>(character);
            }
        }
    }
    void Team2::print(){

    }
}