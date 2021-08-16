#include "Space.h"
using namespace Chess;

Space::Space() {}

void Space::operator=(const Space& space) {
    type = space.type;
    color = space.color;
}

Space::Space(const Space& space) {
    *this = space;
}

Space::Space(Type _type, Color _color) : type{_type}, color{_color} {}