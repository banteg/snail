// Calls whose matched VC6 shape relies on x86 calling-convention leniency, so a
// generated forwarder cannot bridge them (see `snail port link`, "manual").

#include <string.h>

#include "subgame_runtime.h"
#include "tracked_allocation_stack.h"
#include "sub_hover.h"
#include "track_attachment_types.h"
#include "vector3.h"

// The definition takes the authored coordinates as raw float bits (its matched
// shape); callers pass floats. Same stack bytes on x86, distinct types in wasm.
void set_input_controller_pointer_authored_xy(int slot, int authored_x_bits, int authored_y_bits);

void set_input_controller_pointer_authored_xy(int slot, float authored_x, float authored_y)
{
    int x_bits;
    int y_bits;
    memcpy(&x_bits, &authored_x, sizeof(x_bits));
    memcpy(&y_bits, &authored_y, sizeof(y_bits));
    set_input_controller_pointer_authored_xy(slot, x_bits, y_bits);
}

// Identical-code-folded with the empty cRSubGame::AddSpeedUp @ 0x43d880.
void cRSubHover::Hover(Vector3&, float) {}

// update_subgoldy's call views (decomp/game/SubGame/update_subgoldy.cpp): the
// path receiver passes two vectors by value to the six-float definition, and the
// floor sampler reads the definition's double through x87 as a float.
struct SubgoldyPathView {
    void try_enter_track_attachment_from_swept_motion(Vector3 position, Vector3 sweep, cRSubLoc* cell);
};

void SubgoldyPathView::try_enter_track_attachment_from_swept_motion(
    Vector3 position, Vector3 sweep, cRSubLoc* cell)
{
    ((cRPath*)this)->try_enter_track_attachment_from_swept_motion(
        position.x, position.y, position.z, sweep.x, sweep.y, sweep.z, cell);
}

struct SubgoldyFloorSamplerCallView {
    float sample_track_floor_height_at_position(Vector3* position);
};

float SubgoldyFloorSamplerCallView::sample_track_floor_height_at_position(Vector3* position)
{
    return (float)((cRSubGame*)this)->GetY(position);
}

// Identical-code-folded with cREnemyManager::Init @ 0x415e20, which clears the
// first dword; no recovered body carries this owner's name.
void TrackedAllocationStack::initialize_tracked_allocation_stack()
{
    depth = 0;
}

// apply_bod_position calls tVector::operator* through a view that returns the
// hidden result pointer, as VC6 left it in EAX (this, then the result slot).
// Wasm passes the result slot before `this` and returns nothing, so a forwarder
// would hand `this` over as the result and the caller a garbage pointer.
tVector* tVector::multiply_vector_by_matrix_copy(tVector* out, const tMatrix* matrix) const
{
    *out = *this * *matrix;
    return out;
}
