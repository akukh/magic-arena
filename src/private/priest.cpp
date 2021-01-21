#include "priest.hpp"
#include "skill.hpp"
#include "team.hpp"
#include "weapon.hpp"

#include <iomanip>
#include <iostream>

Priest::Priest(std::wstring_view name, Team* team, bool real) noexcept
    : Character{name, team, real}, faith_{100.0},
      skill_{new Skill{L"Цілюща долоня", 30.0, 100.0}} {}

Priest::Priest(Team* team) noexcept : Priest{L"Жрець", team} {}

Priest::~Priest() {}

double Priest::faith() const noexcept { return faith_ < 0.0 ? 0.0 : faith_; }

double Priest::skill_cost() noexcept {
    faith_ -= skill_->cost();
    return skill_->cost();
}

Effect Priest::heal(Character* other) noexcept {
    // clang-format off
    health_ += skill_->value();
    faith_  -= skill_->cost();
    // clang-format on

    // clang-format off
    if (0 == team_->name().compare(L"Червона")) std::wcout << "\x1B[31m";
    else                                        std::wcout << "\x1B[36m";
    // clang-format on
    std::wcout << std::setw(5) << name_ << "#" << id_ << "\033[0m"
               << L" вилікував себе (+" << std::setprecision(1) << std::setw(4)
               << "\033[32m" << 30.0 << L"\033[0mОЖ, \033[33m" << skill_cost()
               << L"\033[0mОВ)\n";
    return Effect::HEALED;
}

void Priest::action(Character* other) noexcept {
    if (real_ && faith() >= skill_->cost()) {
        bool input = false;
        std::wcout << L"У вас є активні навики:\n";
        std::wcout << L"  1 -- " << skill_->name() << L" (Вилікує: "
                   << std::setprecision(1) << std::setw(4) << "\033[32m" << 30.0
                   << L"\033[0mОЖ, Вартість: " << std::fixed
                   << std::setprecision(1) << std::setw(4) << "\033[33m"
                   << skill_->cost() << L"\033[0mОВ)\n";
        std::wcout << L"Хочете ними скористатись? (0 / 1) ";
        std::wcin >> input;

        if (input)
            goto cast;
        Character::action(other);
        return;
    }
    if (health() <= 30.0 && faith() >= skill_->cost()) {
    cast:
        heal(this);
    } else {
        Character::action(other);
    }
}

void Priest::pickup_weapon() noexcept {
    if (!has_weapon()) {
        weapon_ = new Weapon{"Staff", 35.0, 50.0, this};
    }
}

double Priest::hit_damage() noexcept {
    return weapon_->damage(); //+ skill_->damage();
}

void Priest::info() noexcept {
    std::wcout << "\033[32m" << std::fixed << std::setprecision(1) << health()
               << L"\033[0mОЖ, \033[33m" << std::setw(5) << faith()
               << L"\033[0mОВ, ";
    weapon_->info();
}