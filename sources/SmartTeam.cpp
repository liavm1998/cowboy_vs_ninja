#include "SmartTeam.hpp"

namespace ariel{
    template<typename Base, typename T>
    inline bool instanceof(const T*) {
        return std::is_base_of<Base, T>::value;
    }
    SmartTeam::SmartTeam(Character* c):Iteam(c){
        this->add(c);
    }
    void SmartTeam::add(Character* c){
        this->Characters.push_back(c);
    }
    int SmartTeam::stillAlive(){
        return 0;
        // int count = 0;
        // for (size_t i = 0; i < this->memebers.size(); i++)
        // {
        //     Character* a = this->memebers.at(i);
        //     if(a->isAlive()){
        //         count++;
        //     }
        // }
        // return count;
    }
    void SmartTeam::attack(Iteam* b){
        
    }
    void SmartTeam::print(){

    }
}