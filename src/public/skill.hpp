#pragma once

#include <string_view>

class Skill {
public:
    Skill() noexcept;
    Skill(std::wstring_view name,
          double const      value,
          double const      cost) noexcept;

    /// @returns the name of the skill.
    std::wstring_view name() const noexcept;

    /// @returns the value of the skill.
    double value() const noexcept;

    /// @returns the cost of the skill.
    double cost() const noexcept;

private:
    std::wstring_view name_;
    double            value_;
    double            cost_;
};