#include "mage.hpp"
#include "skill.hpp"
#include "team.hpp"
#include "weapon.hpp"

#include <iomanip>
#include <iostream>

Mage::Mage(std::wstring_view name, Team* team, bool real) noexcept
    : Character{name, team, real}, mana_{100.0},
      skill_{new Skill{L"Вогненна куля", 30.0, 100.0}} {}

Mage::Mage(Team* team) noexcept : Mage{L"Маг", team} {}

Mage::~Mage() {}

double Mage::mana() const noexcept { return mana_ < 0.0 ? 0.0 : mana_; }

double Mage::skill_cost() noexcept {
    mana_ -= skill_->cost();
    return skill_->cost();
}

void Mage::action(Character* other) noexcept {
    if (real_ && mana() >= skill_->cost()) {
        bool input = false;
        std::wcout << L"У вас є активні навики:\n";
        std::wcout << L"  1 -- " << skill_->name() << L" (Шкода: "
                   << skill_->value() << L", Вартість: " << std::fixed
                   << std::setprecision(1) << std::setw(4) << "\033[33m"
                   << skill_->cost() << L"\033[0mОМ)\n";
        std::wcout << L"Хочете ними скористатись? (0 / 1) ";
        std::wcin >> input;

        if (input)
            goto cast;
        Character::action(other);
        return;
    }
    if (other->health() <= skill_->value() && mana() >= skill_->cost()) {

    cast:
        mana_ -= skill_->cost();

        auto const damage          = weapon_->damage() + skill_->value();
        auto const damage_received = other->cause_damage(damage);

        // clang-format off
        if (0 == team_->name().compare(L"Червона")) std::wcout << "\x1B[31m";
        else                                        std::wcout << "\x1B[36m";
        // clang-format on
        std::wcout << std::setw(5) << name_ << "#" << id_ << "\033[0m"
                   << L" використав навик '" << skill_->name()
                   << L"' та підпалив ";
        // clang-format off
        if (0 == other->team()->name().compare(L"Червона")) std::wcout << "\x1B[31m";
        else                                                std::wcout << "\x1B[36m";
        // clang-format on
        std::wcout << other->name() << "#" << other->id() << "\033[0m"
                   << L" на " << damage_received << L" шкоди\n";
        std::wcout << "  (-" << std::fixed << std::setprecision(1)
                   << std::setw(4) << "\033[33m" << skill_->cost()
                   << L"\033[0mОМ)\n";
        if (!other->is_alive()) {
            // clang-format off
            if (0 == team_->name().compare(L"Червона")) std::wcout << "\x1B[31m";
            else                                        std::wcout << "\x1B[36m";
            // clang-format on
            std::wcout << std::setw(5) << name_ << "#" << id_ << "\033[0m"
                       << L" вбив персонажа: ";
            // clang-format off
            if (0 == other->team()->name().compare(L"Червона")) std::wcout << "\x1B[31m";
            else                                                std::wcout << "\x1B[36m";
            // clang-format on
            std::wcout << other->name() << "#" << other->id() << "\033[0m"
                       << L"\n";
        }
    } else {
        Character::action(other);
    }
}

void Mage::pickup_weapon() noexcept {
    if (!has_weapon()) {
        weapon_ = new Weapon{"Staff", 35.0, 50.0, this};
    }
}

double Mage::hit_damage() noexcept {
    return weapon_->damage(); // + skill_->damage();
}

void Mage::info() noexcept {
    std::wcout << "\033[32m" << std::fixed << std::setprecision(1) << health()
               << L"\033[0mОЖ, \033[33m" << std::setw(5) << mana()
               << L"\033[0mОМ, ";
    weapon_->info();
}