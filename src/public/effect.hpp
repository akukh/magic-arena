#pragma once

#include <cstddef>

enum class Effect : std::size_t {
    INCORRECT = 0,
    MISSED,
    WOUNDED,
    KILLED,
    DEAD,
    SELF_MURDERED,
    HEALED
};