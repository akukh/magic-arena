#pragma once

#include "character.hpp"

class Mage : public Character {
public:
    Mage(std::wstring_view name, Team* team, bool real = false) noexcept;
    Mage(Team* team) noexcept;
    ~Mage();

    /// @returns the amount of mana.
    double mana() const noexcept;

    /// @returns the amount of mana spent on a skill.
    double skill_cost() noexcept;

    /// @brief The character tries to do some kind of action on anoter.
    void action(Character* other) noexcept override;

    /// @brief The character receives a weapon with random characteristics.
    void pickup_weapon() noexcept override;

    /// @brief Calculates the correct amount of damage per hit.
    /// @returns the amount of damage.
    double hit_damage() noexcept override;

    /// @brief Writes down useful information about the character status.
    void info() noexcept override;

private:
    double       mana_;
    class Skill* skill_;
};