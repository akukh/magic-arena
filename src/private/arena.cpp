#include "arena.hpp"
#include "mage.hpp"
#include "priest.hpp"
#include "team.hpp"
#include "warrior.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <thread>

Arena::Arena() noexcept
    : red_{nullptr}, blue_{nullptr}, player_character_{nullptr} {}

Arena::~Arena() {
    delete blue_;
    delete red_;
}

void Arena::arena_5x5() {
    blue_ = new Team{L"Синя", 5};
    red_  = new Team{L"Червона", 5};
    blue_->show_characters();
    red_->show_characters();

    std::queue<Character*>  battle_queue;
    std::vector<Character*> dead_characters;

    for (std::size_t i = 0; i < 5; i++) {
        if (!blue_->empty() && !red_->empty()) {
            battle_queue.push((*blue_)[i]);
            battle_queue.push((*red_)[i]);
        }
    }

    for (std::size_t i = 0; blue_->any_alive() && red_->any_alive(); i++) {
        // clang-format off
        if (
                    battle_queue.front()->is_alive()
                && (blue_->any_alive() || red_->any_alive())
           )
        // clang-format on
        {
            std::wcout
                << "+-------------------------------------------------------"
                   "---------------------------+\n";
            std::wcout << L"| Раунд: " << i << std::endl;
            std::wcout
                << "+-------------------------------------------------------"
                   "---------------------------+\n";
            auto fighter    = battle_queue.front();
            auto enemy_team = fighter->team() == red_ ? blue_ : red_;
            auto best_enemy = fighter->choose_enemy(enemy_team);

            battle_queue.push(fighter);
            battle_queue.pop();

            // clang-format off
            if (
                        best_enemy
                    &&  best_enemy->is_alive() && fighter->is_alive()
                    &&  best_enemy->team() != fighter->team()
               )
            // clang-format on
            {
                // clang-format off
                if (red_ == fighter->team()) std::wcout << "\x1B[31m";
                else                         std::wcout << "\x1B[36m";
                // clang-format on
                std::wcout << std::setw(5) << fighter->name() << L"#"
                           << fighter->id() << "\033[0m"
                           << L" вибрав ціллю персонажа: ";
                // clang-format off
                if (red_ == enemy_team) std::wcout << "\x1B[31m";
                else                    std::wcout << "\x1B[36m";
                // clang-format on
                std::wcout << best_enemy->name() << L"#" << best_enemy->id()
                           << "\033[0m"
                           << " (";
                best_enemy->info();
                std::wcout << ")\n";
                fighter->action(best_enemy);
            }

            if (!best_enemy->is_alive()) {
                dead_characters.push_back(best_enemy);
            }
        }

        if (!battle_queue.front()->is_alive()) {
            battle_queue.pop();
        }
    }

    winner();
}

void Arena::arena_5x5_with_player() {
    std::wstring player_name;
    std::wstring player_class;
    int          player_age;

    std::wcout << L"Вітаємо тебе на арені, мандрівнику.\n";
    std::wcout << L"Вкажи своє ім'я: ";
    std::wcin >> player_name;
    std::wcout << L"Вкажи свій вік: ";
    std::wcin >> player_age;
    std::wcout << L"Вкажи свій клас (Маг, Воїн, Жрець): ";
    std::wcin >> player_class;

    blue_                = new Team{L"Синя", 5};
    red_                 = new Team{L"Червона", 4};
    auto const player_id = player_name + player_class;

    if (0 == player_class.compare(L"Маг"))
        player_character_ = new Mage{player_id, red_, true};
    else if (0 == player_class.compare(L"Воїн"))
        player_character_ = new Warrior{player_id, red_, true};
    else if (0 == player_class.compare(L"Жрець"))
        player_character_ = new Priest{player_id, red_, true};
    else
        std::wcout << L"Ви ввели невірний клас свого персонажу.\n";

    red_->add(player_character_);

    blue_->show_characters();
    red_->show_characters();

    std::queue<Character*>  battle_queue;
    std::vector<Character*> dead_characters;
    for (std::size_t i = 0; i < 4; i++) {
        if (!blue_->empty() && !red_->empty()) {
            battle_queue.push((*blue_)[i]);
            battle_queue.push((*red_)[i]);
        }
    }
    battle_queue.push((*blue_)[4]);
    battle_queue.push(player_character_);

    for (std::size_t i = 0; blue_->any_alive() && red_->any_alive(); i++) {
        // clang-format off
        if (
                    battle_queue.front()->is_alive()
                && (blue_->any_alive() || red_->any_alive())
           )
        // clang-format on
        {
            std::wcout
                << "+-------------------------------------------------------"
                   "---------------------------+\n";
            std::wcout << L"| Раунд: " << i << std::endl;
            std::wcout
                << "+-------------------------------------------------------"
                   "---------------------------+\n";
            auto       fighter    = battle_queue.front();
            auto       enemy_team = fighter->team() == red_ ? blue_ : red_;
            Character* best_enemy = nullptr;
            if (player_character_ == fighter) {
                int input = 0;
                std::wcout << L"Виберіть кого ви хочете атакувати.\n";
                enemy_team->show_characters();
                std::wcin >> input;
                best_enemy = (*enemy_team)[input - 1];
            } else {
                best_enemy = fighter->choose_enemy(enemy_team);
            }

            battle_queue.push(fighter);
            battle_queue.pop();

            // clang-format off
            if (
                        best_enemy
                    &&  best_enemy->is_alive() && fighter->is_alive()
                    &&  best_enemy->team() != fighter->team()
               )
            // clang-format on
            {
                // clang-format off
                if (red_ == fighter->team()) std::wcout << "\x1B[31m";
                else                         std::wcout << "\x1B[36m";
                // clang-format on
                std::wcout << std::setw(5) << fighter->name() << L"#"
                           << fighter->id() << "\033[0m"
                           << L" вибрав ціллю персонажа: ";
                // clang-format off
                if (red_ == enemy_team) std::wcout << "\x1B[31m";
                else                    std::wcout << "\x1B[36m";
                // clang-format on
                std::wcout << best_enemy->name() << L"#" << best_enemy->id()
                           << "\033[0m"
                           << " (";
                best_enemy->info();
                std::wcout << ")\n";
                fighter->action(best_enemy);
            }

            if (best_enemy && !best_enemy->is_alive()) {
                dead_characters.push_back(best_enemy);
            }
        }

        if (!battle_queue.front()->is_alive()) {
            battle_queue.pop();
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    winner();
}

void Arena::winner() noexcept {
    Team* winner = nullptr;
    std::wcout << std::endl << L"////////////////////// Вітання! Перемогла ";
    if (blue_->any_alive()) {
        // clang-format off
        if (0 == blue_->name().compare(L"Червона")) std::wcout << "\x1B[31m";
        else                                        std::wcout << "\x1B[36m";
        // clang-format on
        std::wcout << blue_->name();
        winner = blue_;
    } else {
        // clang-format off
        if (0 == red_->name().compare(L"Червона")) std::wcout << "\x1B[31m";
        else                                       std::wcout << "\x1B[36m";
        // clang-format on
        std::wcout << red_->name();
        winner = red_;
    }
    std::wcout << L" команда\033[0m! ////////////////////////\n";

    for (std::size_t i = 0; i < winner->team_size(); i++) {
        if ((*winner)[i]->is_alive()) {
            std::wcout.width(5);
            std::wcout << (*winner)[i]->name() << "#" << (*winner)[i]->id()
                       << " (";
            std::wcout.width(5);
            (*winner)[i]->info();
            std::wcout << ")" << std::endl;
        }
    }
}