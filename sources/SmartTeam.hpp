#include <vector>
#include "Team.hpp"
namespace ariel{
    class SmartTeam:public virtual Team{
        private:
            vector<Character*> Characters;
        public:
            SmartTeam(Character*);
            void attack(Team* another) override;
    };
}