#pragma once
#include "glm/fwd.hpp"

namespace DG {

    using ButtonCode = uint8_t;

    namespace Button {
        inline constexpr ButtonCode Button_1 = 0;
        inline constexpr ButtonCode Button_2 = 1;
        inline constexpr ButtonCode Button_3 = 2;
        inline constexpr ButtonCode Button_4 = 3;
        inline constexpr ButtonCode Button_5 = 4;
        inline constexpr ButtonCode Button_6 = 5;
        inline constexpr ButtonCode Button_7 = 6;
        inline constexpr ButtonCode Button_8 = 7;
        inline constexpr ButtonCode Button_Last = Button_8;
        inline constexpr ButtonCode Button_Left = Button_1;
        inline constexpr ButtonCode Button_Right = Button_2;
        inline constexpr ButtonCode Button_Middle = Button_3;
    }

}
