#include "../pieces.h"
#include "../movement.h"

void KingGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& moves) {
    Space* space = state->GetSpace(loc);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(1, 0), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(-1, 0), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(0, 1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(0, -1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(1, 1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(-1, -1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(1, -1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(-1, 1), moves);

    if (!space->modified) {
        uint backRowY = space->color == Space::Color::Black ? 0 : 7;
        if (!(state->GetSpace(Vector2u(0, backRowY)))->modified && state->GetSpace(Vector2u(1, backRowY))->type == Space::Type::None && state->GetSpace(Vector2u(2, backRowY))->type == Space::Type::None && state->GetSpace(Vector2u(3, backRowY))->type == Space::Type::None) {
            moves << Vector2u(2, backRowY);
        }
        if (!(state->GetSpace(Vector2u(7, backRowY)))->modified && state->GetSpace(Vector2u(5, backRowY))->type == Space::Type::None && state->GetSpace(Vector2u(6, backRowY))->type == Space::Type::None) {
            moves << Vector2u(6, backRowY);
        }
    }
}