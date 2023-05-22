#include "Cowboy.hpp"
#include "iostream"

namespace ariel {
    Cowboy::Cowboy(string name, Point location):Character(location,110,name), bullets(6){}
    bool Cowboy::hasboolets(){
        return bullets > 0;
    }
    void Cowboy::shoot(Character * enemy){
        if(enemy == this){
            throw std::runtime_error("cant shoot myself");
        }
        if(!isAlive()){
            throw std::runtime_error("i am dead i cant shoot target");
        } 
        if( !enemy->isAlive() ){
            throw std::runtime_error("no alive target");
        }
        if(bullets <= 0){
            return;
        }
        bullets --;
        enemy->hit(10);
    }
    void Cowboy::reload(){
        if(!isAlive()){
            throw std::runtime_error("");
        }
        this->bullets = 6;
    }
    string Cowboy::print() {
        std::string str = "Cowboy ,";
        str += std::to_string(this->getHealth());
        str += this->getLocation().print();  
        return str;
    }
    
}