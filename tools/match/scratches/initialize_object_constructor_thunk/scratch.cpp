// Object::initialize_object_constructor_thunk @ 0x42f6e0

#include "object_render_types.h"

Object* Object::initialize_object_constructor_thunk()
{
    initialize_object();
    return this;
}
