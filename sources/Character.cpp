#include "iostream"
#include "Character.hpp"

namespace ariel{
    Character::Character(Point _loc , int _health, string _name):location(_loc)
                                                                ,health(_health)
                                                                ,name(_name)
                                                                ,inTeam(false){}
    
    bool Character::isAlive(){
        return this->health > 0;
    }
    double Character::distance(const Character* another){
        return this->location.distance(another->location);
    }
    void Character::hit(int damage){
        if(damage<0){
            throw std::invalid_argument("");
        }
        this->health -= damage;
    }
    string Character::getName(){
        return this->name;
    }
    Point Character::getLocation(){
        return this->location;
    }
    string Character::print(){
        return "";
    }
    int Character::getHealth(){return this->health;}

    void Character::setInTeam(){
        this->inTeam = true;
    }
    bool Character::isInTeam(){
        return inTeam;
    }

    void Character::SetLocation(Point new_loc){
        this->location = new_loc;
    }
}