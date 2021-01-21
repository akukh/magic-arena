#pragma once

#include <cstddef>
#include <string_view>
#include <vector>

class Factory;

class Team {
public:
    friend class Character;

    Team(std::wstring_view name, std::size_t const team_size);
    ~Team();

    /// @returns the name of the team.
    std::wstring_view name() const noexcept;

    /// @returns the team size.
    std::size_t team_size() const noexcept;

    /// @returns if the team is empty.
    bool empty() const noexcept;

    /// @returns is there anyone alive in the team.
    bool any_alive() noexcept;

    /// @brief Prints down all characters in the team.
    void show_characters() noexcept;

    /// @brief Add new character to the team.
    void add(Character* const character) noexcept;

    // clang-format off
    Character*       operator[](std::size_t const i) noexcept;
    Character const* operator[](std::size_t const i) const noexcept;
    // clang-format on

private:
    Factory* new_character();

    std::wstring_view       name_;
    std::size_t             team_size_;
    Factory*                factory_[3];
    std::vector<Character*> characters_;
};