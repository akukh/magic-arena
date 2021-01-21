#include "warrior.hpp"
#include "weapon.hpp"

#include <iomanip>
#include <iostream>

Warrior::Warrior(std::wstring_view name, Team* team, bool real) noexcept
    : Character{name, team, real}, fury_{100.0}, resistance_{0.24} {}

Warrior::Warrior(Team* team) noexcept : Warrior{L"Воїн", team} {}

Warrior::~Warrior() {}

double Warrior::fury() const noexcept { return fury_ < 0.0 ? 0.0 : fury_; }

double Warrior::skill_cost() noexcept {
    fury_ -= 10; // skill_->mana_cost();
    return fury_;
}

void Warrior::action(Character* other) noexcept { Character::action(other); }

void Warrior::pickup_weapon() noexcept {
    if (!has_weapon()) {
        weapon_ = new Weapon{"Axe", 45.0, 80.0, this};
    }
}

double Warrior::cause_damage(double const value) noexcept {
    auto const damage = value - (value * resistance_);
    health_ -= damage;
    return damage;
}

double Warrior::hit_damage() noexcept {
    return weapon_->damage(); // + skill_->damage();
}

void Warrior::info() noexcept {
    std::wcout << "\033[32m" << std::fixed << std::setprecision(1) << health()
               << L"\033[0mОЖ, \033[33m" << std::setw(5) << fury()
               << L"\033[0mОЛ, ";
    weapon_->info();
}