
#include "Ninja.hpp"

namespace ariel {
    
    OldNinja::OldNinja(string name, Point _loc): Ninja(_loc,150,name,8){}
    TrainedNinja::TrainedNinja(string name, Point _loc): Ninja(_loc,120,name,12){}
    YoungNinja::YoungNinja(string name, Point _loc): Ninja(_loc,100,name,14){}

    void Ninja::move(Character* character){
        Point new_location  = this->getLocation();
        new_location.moveTowards(character->getLocation(),speed);
        this->SetLocation(new_location);
    }
    void Ninja::slash(Character* enemy){
        if(enemy == this){
            throw std::runtime_error("cant shoot myself");
        }
        if(!isAlive()){
            throw std::runtime_error("i am dead i cant shoot target");
        } 
        if( !enemy->isAlive() ){
            throw std::runtime_error("no alive target");
        }
        if(distance(enemy)<=1){
            enemy->hit(40);
        }
    }
    string Ninja::print() {
        std::string str = "N, " +
        this->getName()+" HP: " +
        std::to_string(this->getHealth()) + "location: " +
        this->getLocation().print();
        return str;
    };
    int Ninja::getSpeed(){
        return this->speed;
    }
}