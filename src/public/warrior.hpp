#pragma once

#include "character.hpp"

class Warrior : public Character {
public:
    Warrior(std::wstring_view name, Team* team, bool real = false) noexcept;
    Warrior(Team* team) noexcept;
    ~Warrior();

    /// @returns the amount of fury.
    double fury() const noexcept;

    /// @returns the amount of fury spent on a skill.
    double skill_cost() noexcept;

    /// @brief The character tries to do some kind of action on anoter.
    void action(Character* other) noexcept override;

    /// @brief The character receives a weapon with random characteristics.
    void pickup_weapon() noexcept override;

    /// @brief Deals the correct amount of damage.
    double cause_damage(double const value) noexcept override;

    /// @brief Calculates the correct amount of damage per hit.
    /// @returns the amount of damage.
    double hit_damage() noexcept override;

    /// @brief Writes down useful information about the character status.
    void info() noexcept override;

private:
    double fury_;
    double resistance_;
};