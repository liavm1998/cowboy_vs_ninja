#include "iostream"
#include "Team.hpp"

namespace ariel{
    Team::Team(Character* character): captain(character){
        this->members.reserve(10);
        /// instead of add(member) because using virtual func in constructor is bad habit
        if(character->isInTeam()){
            throw std::runtime_error("already in team");
        }
        character->setInTeam();
        members.push_back(character);
    }

    void Team::add(Character* character){
        if(this->members.size() == 10)
            throw std::runtime_error("can't have more than 10 members");
        if(character->isInTeam())
            throw std::runtime_error("this Character already in team");
        character->setInTeam();
        members.push_back(character);
    }

    int Team::stillAlive(){
        int count = 0;
        for (auto a : this->members){
            if(a->isAlive())
                count++;
        }
        return count;
    }


    Character* Team::closestToCap( const vector<Character*> &team) {
        double minDistance = std::numeric_limits<double>::max();
        Character* closestEnemy = nullptr;
        for (Character* ene : team) {
            if(ene->isAlive()){
                double distance = ene->distance(this->captain);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestEnemy = ene;
                }
            }
        }
        return closestEnemy;
    }

    void Team::CowboysAttack(const Team& enemy){
        for(auto character : this->members){
            if(!character->isAlive()){
                continue;
            }
            Character* target = closestToCap(enemy.members);
            if(target == nullptr){return;}
            if(auto* cowboy = dynamic_cast<Cowboy*>(character)) {
                if(!target->isAlive()){
                    target = closestToCap(enemy.members);
                }
                if(target == nullptr){return;}
                if(cowboy->hasboolets())
                    cowboy->shoot(target);
                else
                    cowboy->reload();
            }
        }
    }

    void Team::NinjaAttack(const Team& enemy){
        for(auto* character : this->members){
            if(!character->isAlive())
                continue;
            if(auto* nin = dynamic_cast<Ninja*>(character)) {
                Character* target = closestToCap(enemy.members);
                if(target == nullptr){return;}
                if(nin->distance(target) <= 1)
                    nin->slash(target);
                else
                    nin->move(target);
            }
        }
    }
    void Team::attack(Team* enemy){
        if(enemy == nullptr)
            throw std::invalid_argument("need to pass enemy argument");
        if(!enemy->stillAlive())
            throw std::runtime_error("");
        this->changeCaptain();
        // first cowboys
        CowboysAttack(*enemy);
        // then ninjas
        NinjaAttack(*enemy);
    }
    void Team::print(){
        cout << "hello" << endl;
    }

    void Team::changeCaptain(){
        this->captain = this->closestToCap(members);
    }

    Character* Team::GetCaptain(){
        return this->captain;
    }

    vector<Character*> Team::getMembers() const{
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