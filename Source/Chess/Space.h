#pragma once

namespace Chess {
    struct Space {
        enum Color {
            Black,
            White
        };
        enum Type {
            None,
            Pawn
        };
        Type type;
        Color color;
    };
};