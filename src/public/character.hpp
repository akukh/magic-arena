#pragma once

#include <string_view>

#include "effect.hpp"

class Team;
class Weapon;

class Character {
public:
    Character(std::wstring_view name, Team* team, bool real = false) noexcept;
    virtual ~Character();

    /// @returns the status whether the character is still alive or not.
    bool is_alive() const noexcept;

    /// @returns the status whether the character has weapon or not.
    bool has_weapon() const noexcept;

    /// @returns the amount of health.
    double health() const noexcept;

    /// @brief Changes the amount of health of the character.
    void health(double const value) noexcept;

    /// @returns the unique identifier of the character.
    std::size_t id() const noexcept;

    /// @returns the name of the character.
    std::wstring_view name() const noexcept;

    /// @returns the enemy from the enemy team.
    Character* choose_enemy(Team* team) noexcept;

    /// @returns the team to which the character will attach.
    Team* team() noexcept;

    /// @brief The character drops away the weapon, if he has one.
    void drop_weapon() noexcept;

    /// @brief Attempts to damage another character.
    /// @returns the effect of the hit.
    Effect hit(Character* other) noexcept;

    /// @brief The character tries to do some kind of action on anoter.
    virtual void action(Character* other) noexcept;

    /// @brief Deals the correct amount of damage.
    /// @returns the amount of damage.
    virtual double cause_damage(double const value) noexcept;

    /// @brief The character receives a weapon with random characteristics.
    virtual void pickup_weapon() noexcept = 0;

    /// @brief Calculates the correct amount of damage per hit.
    /// @returns the amount of damage.
    virtual double hit_damage() noexcept = 0;

    /// @brief Writes down useful information about the character status.
    virtual void info() noexcept = 0;

protected:
    std::wstring_view name_;
    std::size_t       id_;
    double            health_;
    Team*             team_;
    Weapon*           weapon_;
    bool              real_;
};