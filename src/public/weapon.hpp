#pragma once

#include <string_view>

class Character;

class Weapon {
public:
    Weapon() noexcept;
    Weapon(std::string_view name,
           double const     min_damage,
           double const     max_damage,
           Character*       owner) noexcept;

    /// @returns the amount of damage done by the weapon.
    double damage() const noexcept;

    /// @brief Writes down useful information about the weapon stats.
    void info() noexcept;

private:
    std::string_view name_;
    double           min_damage_;
    double           max_damage_;
    Character*       owner_;
};