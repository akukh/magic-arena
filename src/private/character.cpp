#include "character.hpp"
#include "game.hpp"
#include "team.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

// clang-format off
Character::Character(std::wstring_view name, Team* team, bool real) noexcept
    : name_{name},
      id_{Game::id() + Game::instance().randomize(1, 100)},
      health_{100.0},
      team_{team},
      weapon_{nullptr},
      real_{real}
{}
// clang-format on

Character::~Character() {
    // clang-format off
    if (team_)   delete team_;
    if (weapon_) delete weapon_;
    // clang-format on
}

bool Character::is_alive() const noexcept { return health_ > 0.0; }

bool Character::has_weapon() const noexcept { return nullptr != weapon_; }

double Character::health() const noexcept {
    return health_ < 0.0 ? 0.0 : health_;
}

void Character::health(double const value) noexcept { health_ = value; }

std::size_t Character::id() const noexcept { return id_; }

std::wstring_view Character::name() const noexcept { return name_; }

Team* Character::team() noexcept { return team_; }

Character* Character::choose_enemy(Team* team) noexcept {
    // clang-format off
    auto characters = team->characters_;
    auto best_enemy =
        std::min_element(characters.begin(), characters.end(), [](Character* c1, Character* c2) {
                         if (c1->is_alive() || c2->is_alive()) return c2->health() < c1->health();
                         return c1->health() < c2->health();
                    });
    // clang-format on
    return *best_enemy;
}

Effect Character::hit(Character* other) noexcept {
    if (!is_alive() || !other->is_alive()) {
        return Effect::DEAD;
    } else if (!has_weapon()) {
        return Effect::INCORRECT;
    }

    auto const damage          = hit_damage();
    auto const damage_received = other->cause_damage(damage);

    if (damage_received <= 0.0) {
        // clang-format off
        if (0 == team_->name().compare(L"Червона")) std::wcout << "\x1B[31m";
        else                                        std::wcout << "\x1B[36m";
        // clang-format on
        std::wcout << std::setw(5) << name_ << "#" << id_ << "\033[0m"
                   << L" не влучив!\n";
        return Effect::MISSED;
    }

    // clang-format off
    if (0 == team_->name().compare(L"Червона")) std::wcout << "\x1B[31m";
    else                                        std::wcout << "\x1B[36m";
    // clang-format on
    std::wcout << std::setw(5) << name_ << "#" << id_ << "\033[0m"
               << L" завдав " << std::fixed << std::setprecision(1)
               << std::abs(damage_received) << L" шкоди персонажу: ";
    // clang-format off
    if (0 == other->team()->name().compare(L"Червона")) std::wcout << "\x1B[31m";
    else                                                std::wcout << "\x1B[36m";
    // clang-format on
    std::wcout << other->name() << "#" << other->id() << "\033[0m"
               << L" (\033[32m" << std::setw(2) << std::fixed
               << std::setprecision(1) << other->health() << "\033[0m"
               << L"ОЖ)\n";

    if (!other->is_alive())
        return Effect::KILLED;
    return Effect::WOUNDED;
}

void Character::action(Character* other) noexcept {
    if (Effect::KILLED == hit(other)) {
        // clang-format off
        if (0 == team_->name().compare(L"Червона")) std::wcout << "\x1B[31m";
        else                                        std::wcout << "\x1B[36m";
        // clang-format on
        std::wcout << std::setw(5) << name_ << "#" << id_ << "\033[0m"
                   << L" вбив персонажа: ";
        // clang-format off
        if (0 == other->team()->name().compare(L"Червона")) std::wcout << "\x1B[31m";
        else                                                std::wcout << "\x1B[36m";
        // clang-format on
        std::wcout << other->name() << "#" << other->id() << "\033[0m" << L"\n";
    }
}

double Character::cause_damage(double const value) noexcept {
    health_ -= value;
    return value;
}