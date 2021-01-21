#pragma once

#include "character.hpp"

class Priest : public Character {
public:
    Priest(std::wstring_view name, Team* team, bool real = false) noexcept;
    Priest(Team* team) noexcept;
    ~Priest();

    /// @returns the amount of faith.
    double faith() const noexcept;

    /// @returns the amount of faith spent on a skill.
    double skill_cost() noexcept;

    /// @brief Attempts to heal another character.
    /// @returns the effect of the heal.
    Effect heal(Character* other) noexcept;

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
    double       faith_;
    class Skill* skill_;
};