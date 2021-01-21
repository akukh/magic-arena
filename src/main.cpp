#include <clocale>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <windows.h>

#include "game.hpp"

int main() {
    // clang-format off
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin) , _O_U16TEXT);
    // clang-format on
menu:
    system("cls");
    std::wcout << L"\t\t\t\t~Гра Магічна Арена~\n";
    std::wcout << L"1 -- Розпочати бій, як гравець.\n";
    std::wcout << L"2 -- Розпочати бій, як спостерігач.\n";

    Game& game  = Game::instance();
    int   input = 0;
    std::wcin >> input;
    switch (input) {
        case 1: {
            system("cls");
            game.play(input);
            bool replay = false;
            std::wcout << L"Хочете спробувати ще раз? (0 / 1) ";
            std::wcin >> replay;
            if (replay)
                goto menu;
            else
                return 0;
        }
        case 2: {
            system("cls");
            game.play(input);
            bool replay = false;
            std::wcout << L"Хочете спробувати ще раз? (0 / 1) ";
            std::wcin >> replay;
            if (replay)
                goto menu;
            else
                return 0;
        }
        default: {
            bool replay = false;
            std::wcout << L"Невірний ввід! Хочете спробувати ще раз? (0 / 1) ";
            std::wcin >> replay;
            if (replay)
                goto menu;
            else
                return 0;
        }
    }
}