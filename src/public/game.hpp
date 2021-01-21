#pragma once

#include <cstddef>
#include <random>

#include "arena.hpp"

/// @brief ...
class Game {
public:
    /// @returns an instance of the single game object.
    static Game& instance() noexcept;

    /// @brief Starts the game.
    static std::size_t id() noexcept;

    /// @{
    /// @returns a random number in a range `from` `to`.
    // clang-format off
       int randomize(   int const from,    int const to) noexcept;
    double randomize(double const from, double const to) noexcept;
    // clang-format on
    /// @}

    /// @brief Starts the game.
    void play(int const type) noexcept;

private:
    Game() noexcept;
    ~Game();
    Game(Game const&) noexcept = delete;
    Game& operator=(Game const&) noexcept = delete;

    std::mt19937 gen_;
    Arena        arena_;
};