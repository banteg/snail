// This fixture uses zero-initialized storage, as the native tracked allocator
// provides for object banks, and the recovered constructor/Init functions.
#include <stdio.h>
#include "object_render_types.h"
#include "sprite.h"
#include "tracked_allocation_stack.h"

static cRObject object;
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
    initialize_tracked_allocation_depth();
    set_tracked_allocation_mark();
    check(object.vertex_count == 0 && object.facequad_count == 0 && object.flags == 0,
          "constructed zero-backed object");
    object.flags = 123;
    object.blend_mode = 456;
    object.Init();
    check(object.flags == 0 && object.blend_mode == 0, "recovered Init clears its fields");

    object.RequestVertices(4);
    check(object.vertex_count == 4 && object.vertices != 0 && object.vertex_colours != 0,
          "vertex allocation also requests colours");
    check(g_tracked_allocation_stack.depth == 2 && g_tracked_allocation_total_bytes == 128,
          "vertex and colour allocation sizes");
    bool initial = true;
    for (int i = 0; i < 4; ++i) {
        initial = initial && object.vertices[i].x == 0.0f && object.vertices[i].y == 0.0f &&
            object.vertices[i].z == 0.0f && object.vertex_colours[i].r == 1.0f &&
            object.vertex_colours[i].g == 1.0f && object.vertex_colours[i].b == 1.0f &&
            object.vertex_colours[i].a == 0.0f;
        object.vertices[i].x = (float)(i + 1);
        object.vertices[i].y = (float)(i + 11);
        object.vertices[i].z = (float)(i + 21);
    }
    check(initial, "vertices zeroed and colours RGB white with alpha left zero");
    Vector3* original = object.vertices;
    object.RequestVertices(2);
    check(object.vertices == original && object.vertex_count == 4 && g_tracked_allocation_stack.depth == 2,
          "smaller vertex request retains original count and allocation");
    object.RequestVerticesCopy();
    if (argc == 2 && argv[1][0] == '!')
        object.copied_vertices[3].z = 0.0f;
    check(object.copied_vertices != original && object.copied_vertices[0].x == 1.0f &&
          object.copied_vertices[3].z == 24.0f, "copied vertex storage and contents");
    object.vertices[1].y = 99.0f;
    object.CopyVertices();
    check(object.copied_vertices[1].y == 99.0f, "copy refreshes existing storage");

    object.RequestFaceQuads(2);
    check(object.facequad_count == 2 && object.facequad_capacity == 2 && object.facequads != 0,
          "facequad initial count and capacity");
    check(g_tracked_allocation_stack.get_tracked_allocation_size((char*)object.facequads - 4) == 104,
          "facequad stride is 48 bytes");
    object.RequestFaceQuads(3); // Facequad allocation is currently top of stack.
    check(object.facequad_count == 3 && object.facequad_capacity == 3 &&
          g_tracked_allocation_stack.depth == 4, "facequad growth replaces top allocation");
    cRFaceQuad* quads = object.facequads;
    object.RequestFaceQuads(1);
    check(object.facequads == quads && object.facequad_count == 1 && object.facequad_capacity == 3,
          "facequad shrink reuses capacity");
    object.RequestFaceQuads(0);
    check(object.facequads == quads && object.facequad_count == 0 && object.facequad_capacity == 3,
          "zero facequad request only clears active count");
    // Restore the valid active range directly; a new RequestFaceQuads after
    // count zero would allocate again in the recovered implementation.
    object.facequad_count = 3;
    Vector3* normals = object.RequestFaceQuadNormals();
    check(normals == object.facequad_normals && object.vertex_normals != 0 &&
          g_tracked_allocation_stack.depth == 6, "normal banks allocated");
    check(g_tracked_allocation_stack.get_tracked_allocation_size((char*)normals - 4) == 80,
          "two vector normals per facequad");
    check(object.RequestFaceQuadNormals() == normals && g_tracked_allocation_stack.depth == 6,
          "normal requests reuse existing storage");
    object.RequestFaceQuadTextureGroups(2);
    int* groups = object.texture_group_ends;
    object.RequestFaceQuadTextureGroups(1);
    check(object.texture_group_count == 1 && object.texture_group_capacity == 2 &&
          object.texture_group_ends == groups, "texture groups retain fixed capacity");
    object.RequestEdges(5);
    check(object.edge_count == 5 && object.edges != 0 &&
          g_tracked_allocation_stack.get_tracked_allocation_size((char*)object.edges - 4) == 188,
          "edge records have 36 byte stride");
    object.RequestEdges(9);
    check(object.edge_count == 5 && g_tracked_allocation_stack.depth == 8,
          "later edge requests preserve original bank");
    check(g_tracked_allocation_total_bytes == 676, "all mesh banks accounted including guards");
    free_tracked_allocations_to_mark();
    check(g_tracked_allocation_stack.depth == 0 && g_tracked_allocation_total_bytes == 0,
          "mesh banks unwind without leaked tracked bytes");

    printf("mesh-storage checks=%d failures=%d\n", checks, failures);
    fflush(0);
    return failures ? 1 : 0;
}
