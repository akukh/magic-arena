#include "weapon.hpp"
#include "character.hpp"
#include "game.hpp"

#include <iomanip>
#include <iostream>

Weapon::Weapon() noexcept
    : name_{}, min_damage_{0.0}, max_damage_{0.0}, owner_{nullptr} {}

// clang-format off
Weapon::Weapon(std::string_view name,
               double const     min_damage,
               double const     max_damage,
               Character*       owner) noexcept
    : name_{name},
      min_damage_{min_damage},
      max_damage_{max_damage},
      owner_{owner} 
{}
// clang-format on

double Weapon::damage() const noexcept {
    return Game::instance().randomize(min_damage_, max_damage_);
}

void Weapon::info() noexcept {
    std::wcout << L"Сила: " << std::setw(4) << min_damage_ << L" / "
               << std::setw(4) << max_damage_;
}