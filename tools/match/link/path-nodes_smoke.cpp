#include <stdio.h>
#include "track_attachment_types.h"
#include "tracked_allocation_stack.h"

extern void* g_path_template_record_vtable;

static int checks;
static int failures;
static void check(bool condition, const char* label)
{
    ++checks;
    if (!condition) {
        ++failures;
        printf("FAIL: %s\n", label);
    }
}

int main(int argc, char** argv)
{
    cRPath path; // The current projection implicitly calls both real cRBod constructors.
    cRObject mesh;
    check(g_bod_base_init_count == 2 && path.color.a == 1.0f && path.fringe_mesh_bod.color.r == 1.0f,
          "base and fringe constructed by recovered cRBod constructor");
    // The recovered path constructor is still represented as a method. Its
    // explicit invocation repeats base initialization; this fixture does not
    // claim that the projection reproduces the game's constructor lifecycle.
    cRPath* result = path.initialize_path_template_record_pair();
    check(result == &path && g_bod_base_init_count == 4 && path.vtable == &g_path_template_record_vtable &&
          path.fringe_mesh_bod.vtable == &g_bod_base_vtable, "recovered path initializer and callback tables");
    initialize_tracked_allocation_depth();
    set_tracked_allocation_mark();
    path.segment_count = 2;
    path.strip_mesh = &mesh;
    path.is_mirrored_x = 0;
    path.GetNodes();
    check(path.primary_samples != 0 && path.secondary_samples != 0 && path.primary_samples != path.secondary_samples,
          "GetNodes allocates two distinct banks");
    check(g_tracked_allocation_stack.depth == 2 && g_tracked_allocation_total_bytes == 688,
          "two 168-byte samples per bank plus guards");
    check(path.primary_samples[1].lateral_source == 0.0f && path.secondary_samples[1].transform.position.z == 0.0f,
          "node banks zero initialized");
    for (int i = 0; i < 2; ++i) {
        path.primary_samples[i].transform.Identity();
        path.secondary_samples[i].transform.Identity();
    }
    path.primary_samples[0].transform.position = Vector3(2.0f, 3.0f, 4.0f);
    path.primary_samples[1].transform.basis_up = Vector3(0.0f, 0.0f, -1.0f);
    path.primary_samples[1].transform.basis_forward = Vector3(0.0f, 1.0f, 0.0f);
    path.secondary_samples[1].transform.position.z = 3.25f;
    mesh.flags = OBJECT_FLAG_DISABLE_CULLING | OBJECT_FLAG_TOON_ENABLED;
    path.CalcLengthZ();
    if (argc == 2 && argv[1][0] == '!')
        path.row_span_count = 0;
    check(path.row_span_count == 4, "row span from secondary sample positions");
    check(path.primary_samples[0].inverse_matrix.position.x == -2.0f &&
          path.primary_samples[0].inverse_matrix.position.y == -3.0f &&
          path.primary_samples[0].inverse_matrix.position.z == -4.0f,
          "primary inverse transforms populated");
    check(path.secondary_samples[1].inverse_matrix.position.z == -3.25f,
          "secondary inverse transforms populated");
    check(path.primary_samples[0].lateral_source == -0.1f, "negative lateral bend clamps at minus one tenth");
    check(path.primary_samples[1].lateral_source == 0.0f, "last sample has no outgoing bend");
    check(mesh.flags == (OBJECT_FLAG_TOON_ENABLED | OBJECT_FLAG_TEXTURE_TRANSFORM), "mesh render flags updated");
    path.is_mirrored_x = 1;
    path.CalcLengthZ();
    check(path.primary_samples[0].lateral_source == 0.0f, "mirroring reverses bend before positive clamp");
    path.segment_count = 1;
    path.primary_samples[0].lateral_source = 9.0f;
    path.CalcLengthZ();
    check(path.row_span_count == 1 && path.primary_samples[0].lateral_source == 0.0f,
          "single sample has span and cleared terminal bend");
    check(g_tracked_allocation_stack.depth == 2 && g_tracked_allocation_total_bytes == 688,
          "geometry calculation adds no allocation");
    free_tracked_allocations_to_mark();
    check(g_tracked_allocation_stack.depth == 0 && g_tracked_allocation_total_bytes == 0,
          "node banks released by recovered allocator");
    printf("path-nodes checks=%d failures=%d\n", checks, failures);
    fflush(0);
    return failures ? 1 : 0;
}
