#include <vector>
#include "Iteam.hpp"
namespace ariel{
    class SmartTeam:public virtual Iteam{
        private:
            vector<Character*> Characters;
        public:
            SmartTeam(Character*);
            void add(Character* character) override;
            int stillAlive() override;
            void attack(Iteam* another) override;
            void print() override;
            ~SmartTeam() override= default;
            SmartTeam(const SmartTeam&) = delete;
            SmartTeam& operator=(const SmartTeam&) = delete;
            SmartTeam(SmartTeam&&) = delete;
            SmartTeam& operator=(SmartTeam&&) = delete;

    };
}