#include "skill.hpp"
#include "character.hpp"

Skill::Skill() noexcept : name_{}, value_{0.0}, cost_{0.0} {}

Skill::Skill(std::wstring_view name,
             double const      value,
             double const      cost) noexcept
    : name_{name}, value_{value}, cost_{cost} {}

std::wstring_view Skill::name() const noexcept { return name_; }

double Skill::value() const noexcept { return value_; }

double Skill::cost() const noexcept { return cost_; }