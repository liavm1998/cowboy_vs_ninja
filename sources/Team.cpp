#include "iostream"
#include "Team.hpp"

namespace ariel{
    Team::Team(Character* Character){
        this->captain = Character;
        this->add(Character);
    }
    void Team::add(Character* character){
            if(this->members.size() == 10){
                throw std::runtime_error("");
            }
            if(character->isInTeam()){
                throw std::runtime_error("");
            }
            character->setInTeam();
            members.push_back(character);
            
    }
    
    int Team::stillAlive(){
        int count = 0;
        for (size_t i = 0; i < this->members.size(); i++){
            Character* a = this->members.at(i);
            if(a->isAlive()){
                count++;
            }
        }
        return count;
    }


    Character* Team::closestToCap(std::vector<Character*> team) {
        Character* cap = this->captain;
        double minDistance = std::numeric_limits<double>::max();
        Character* closestEnemy = nullptr;

        for (Character* ene : team) {
            if(ene->isAlive())
            {
                double distance = ene->distance(cap); 
                if (distance < minDistance) {
                    minDistance = distance;
                    closestEnemy = ene;
                }
            }
        }
        return closestEnemy;
    }


    void Team::attack(Team* enemy){
        // TODO enemy vec deep copy will solve a lot and you can pop dead members
        if(enemy == nullptr){
            throw std::invalid_argument("");
        }
        if(!enemy->stillAlive())
        {
            throw std::runtime_error("");
        }
        this->changeCaptain();
        // first cowboys
        Character* target = closestToCap(enemy->members);
        if(target == nullptr){return;}
        for(size_t i = 0; i < this->members.size(); i++){
            Character* character = this->members[i];
            if(!target->isAlive()){
                    target = closestToCap(enemy->members);
                    if(target == nullptr){return;}
                }
            if(!character->isAlive()){
                continue;
            }
            if(Cowboy* cowboy = dynamic_cast<Cowboy*>(character)) {
                if(!target->isAlive()){
                    target = closestToCap(enemy->members);
                    if(target == nullptr){return;}
                }
                if(cowboy->hasboolets())
                {
                    cowboy->shoot(target);
                    if(target == enemy->captain && !enemy->captain->isAlive()){
                        enemy->changeCaptain();

                    }
                }
                else{
                    cowboy->reload();
                }
            }
        }       
        // then ninjas
        for(Character * character : this->members){
            if(!character->isAlive()){
                continue;
            }
            if(Ninja* nin = dynamic_cast<Ninja*>(character)) {
                if(!target->isAlive()){
                    target = closestToCap(enemy->members);
                    if(target == nullptr){return;}
                }
                if(nin->distance(target) <= 1)
                {
                    nin->slash(target);
                }
                else{
                    nin->move(target);
                }
            }
        }
    }
    void Team::print(){

    }

    void Team::changeCaptain(){
        this->captain = this->closestToCap(members);
    }

    Character* Team::GetCaptain(){
        return this->captain;
    }

    vector<Character*> Team::getMembers(){
        return this->members;
    }
    Team::~Team() {
        captain = nullptr;
        for (Character* member : members) {
            delete member; // Deallocate each member
        }
        members.clear();
    }
}