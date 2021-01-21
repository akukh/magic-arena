#pragma once

#include <vector>

class Team;
class Character;

class Arena {
public:
    Arena() noexcept;
    ~Arena();

    /// @brief Starts 5x5 arena.
    void arena_5x5();

    /// @brief Starts 5x5 arena with player.
    void arena_5x5_with_player();

private:
    void winner() noexcept;

    Team*              red_;
    Team*              blue_;
    Character*         player_character_;
    std::vector<Team*> teams_;
};