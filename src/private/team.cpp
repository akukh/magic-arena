#include "team.hpp"
#include "character.hpp"
#include "factory.hpp"
#include "game.hpp"

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>

Team::Team(std::wstring_view name, std::size_t const team_size)
    : name_{name}, team_size_{team_size}, factory_{nullptr} {
    factory_[0] = new Mage_factory;
    factory_[1] = new Priest_factory;
    factory_[2] = new Warrior_factory;

    for (std::size_t i = 0; i < team_size; i++) {
        auto character = new_character()->create(this);
        character->pickup_weapon();
        characters_.push_back(character);
    }
}

Team::~Team() {}

std::wstring_view Team::name() const noexcept { return name_; }

std::size_t Team::team_size() const noexcept { return team_size_; }

bool Team::empty() const noexcept { return characters_.empty(); }

bool Team::any_alive() noexcept {
    // clang-format off
    return std::any_of(characters_.begin(), characters_.end(),
                       [](Character* c) { return c->is_alive(); });
    // clang-format on
}

void Team::show_characters() noexcept {
    // clang-format off
    if (name_.compare(L"Синя")) std::wcout << "\x1B[31m";
    else                        std::wcout << "\x1B[36m";
    // clang-format on
    int i = 1;
    std::wcout << name_ << L" команда:" << "\033[0m" << std::endl;
    for (auto character : characters_) {
        std::wcout << i << ". ";
        std::wcout.width(5);
        std::wcout << character->name() << "#" << character->id() << " (";
        character->info();
        std::wcout << ")" << std::endl;
        i++;
    }
    std::wcout << std::endl;
}

void Team::add(Character* const character) noexcept {
    character->pickup_weapon();
    characters_.push_back(character);
    team_size_++;
}

Character* Team::operator[](std::size_t const i) noexcept {
    auto const& self      = *this;
    auto const& character = self[i];
    return const_cast<Character*>(character);
}

Character const* Team::operator[](std::size_t const i) const noexcept {
    assert(i >= 0 && i < characters_.size());
    return characters_[i];
}

Factory* Team::new_character() {
    auto const result = Game::instance().randomize(0, 2);
    return factory_[result];
}