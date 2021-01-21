#include "game.hpp"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

Game::Game() noexcept : gen_(time(nullptr)) {}

Game::~Game() {}

Game& Game::instance() noexcept {
    static Game instance;
    return instance;
}

std::size_t Game::id() noexcept {
    static std::size_t id = 100;
    return ++id;
}

void Game::play(int const type) noexcept {
    if (1 == type)
        arena_.arena_5x5_with_player();
    else
        arena_.arena_5x5();
}

int Game::randomize(int const from, int const to) noexcept {
    std::uniform_int_distribution<> uid(from, to);
    return uid(gen_);
}

double Game::randomize(double const from, double const to) noexcept {
    std::uniform_real_distribution<> urd(from, to);
    return urd(gen_);
}