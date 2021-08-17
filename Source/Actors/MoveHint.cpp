#include "MoveHint.h"

bool MoveHint::IsOfType(short id) {
    return id == ID || Sprite::IsOfType(id);
}