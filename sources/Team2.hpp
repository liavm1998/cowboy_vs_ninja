#pragma once
#include <vector>
#include "Team.hpp"

namespace ariel {
    class Team2 : public Team {
        public:
            Team2(Character*);
            void attack(Team* another) override;
            void print() override;
            ~Team2() override = default;
            Team2(const Team2&) = delete;
            Team2& operator=(const Team2&) = delete;
            Team2(Team2&&) = delete;
            Team2& operator=(Team2&&) = delete;
    };
}