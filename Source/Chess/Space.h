#pragma once

namespace Chess {
    struct Space {
        enum Color {
            Black,
            White
        };
        enum Type {
            None,
            Pawn,
            Rook,
            Knight,
            Bishop,
            King,
            Queen
        };
        Type type = None;
        Color color;

        Space();
        void operator=(const Space& space);
        Space(const Space& space);
        Space(Type type, Color color);
    };
};