// Behavioral diagnostics for the actual S-bend source, using recovered
// allocators, texture registration, math, and mesh dependencies.
#include <stdio.h>
#include "track_attachment_types.h"
#include "tracked_allocation_stack.h"
#include "rmath_random.h"

static cRPath paths[4];
static cRObject meshes[4];
static int checks;
static int failures;
static FILE* trace;

static unsigned int hash_bytes(unsigned int hash, const void* data, int size)
{
    if (trace && fwrite(data, 1, size, trace) != (unsigned int)size)
        ++failures;
    const unsigned char* bytes = (const unsigned char*)data;
    for (int i = 0; i < size; ++i)
        hash = (hash ^ bytes[i]) * 16777619U;
    return hash;
}

static void check(bool condition, const char* label)
{
    ++checks;
    if (!condition) {
        ++failures;
        printf("FAIL: %s\n", label);
    }
}

static bool close(float a, float b)
{
    float d = a - b;
    return d > -0.00002f && d < 0.00002f;
}

static void run_case(int index, int width, float height, bool centered,
                     int expected_nodes, int expected_vertices, int expected_faces,
                     int expected_bytes, bool corrupt)
{
    cRPath& path = paths[index];
    cRObject& mesh = meshes[index];
    path.initialize_path_template_record_pair();
    path.strip_mesh = &mesh;
    g_texture_refs.Init(TEXTURE_REF_LIST_CAPACITY);
    initialize_tracked_allocation_depth();
    set_tracked_allocation_mark();
    path.initialize_sbend_path_template_pair(width, height, 3.0f, centered,
        "track/front", "track/back", "track/unused");
    if (corrupt)
        mesh.facequads[0].vertex_0 = 65535;
    check(path.segment_count == expected_nodes, "sample count");
    check(mesh.vertex_count == expected_vertices && mesh.facequad_count == expected_faces,
          "mesh counts");
    check(path.primary_samples != path.secondary_samples && path.primary_samples != 0 && path.secondary_samples != 0,
          "distinct sample banks");
    check(close(path.primary_samples[0].center_x, centered ? 0.0f : -2.0f), "centered and offset origins");
    check(close(path.primary_samples[0].transform.position.y, 0.0f) &&
          close(path.primary_samples[0].transform.position.z, 0.0f), "start position");
    bool orientation = true;
    for (int n = 0; n < expected_nodes; ++n) {
        Vector3 delta = path.secondary_samples[n].transform.position - path.primary_samples[n].transform.position;
        orientation = orientation && close(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z, 0.49000001f * 0.49000001f);
    }
    check(orientation, "secondary samples stay at fixed normal offset");
    int last = expected_nodes - 1;
    check(path.primary_samples[last].delta_length == 1.0f && path.secondary_samples[last].delta_length == 1.0f &&
          path.primary_samples[last].lateral_source == 0.0f, "terminal sample state");
    bool indices = true;
    for (int f = 0; f < expected_faces; ++f) {
        cRFaceQuad& q = mesh.facequads[f];
        indices = indices && q.vertex_0 < expected_vertices && q.vertex_1 < expected_vertices &&
            q.vertex_2 < expected_vertices && q.vertex_3 < expected_vertices;
    }
    check(indices, "face indices remain within vertex bank");
    cRFaceQuad& front = mesh.facequads[0];
    cRFaceQuad& back = mesh.facequads[1];
    check(front.vertex_1 == 1 && front.vertex_2 == width + 2 && front.vertex_3 == width + 1 &&
          back.vertex_0 == 1 && back.vertex_1 == 0 && back.vertex_2 == width + 1 && back.vertex_3 == width + 2,
          "opposite front and back winding");
    check(front.uv[0].u == 0.0f && front.uv[0].v == 0.0f && front.uv[2].u == 0.125f && front.uv[2].v == 0.125f &&
          back.uv[0].u == 0.125f && back.uv[1].u == 0.0f, "first cell UVs");
    bool textures = g_texture_refs.count == 2;
    for (int q = 0; q < expected_faces; ++q)
        textures = textures && mesh.facequads[q].texture_ref == &g_texture_refs.entries[q & 1];
    check(textures, "real texture registry reuses front and back entries");
    int terminal_row = expected_nodes * (width + 1);
    check(close(mesh.vertices[terminal_row].z, path.primary_samples[last].transform.position.z + 1.0f),
          "terminal mesh row extrapolates one unit forward");
    check((mesh.flags & OBJECT_FLAG_TEXTURE_TRANSFORM) != 0 &&
          (mesh.flags & OBJECT_FLAG_DISABLE_CULLING) == 0, "final mesh flags");
    check(g_tracked_allocation_stack.depth == 5 && g_tracked_allocation_total_bytes == expected_bytes,
          "five banks with expected guarded sizes");
    unsigned int hash = 2166136261U;
    hash = hash_bytes(hash, path.primary_samples, expected_nodes * sizeof(AttachmentSample));
    hash = hash_bytes(hash, path.secondary_samples, expected_nodes * sizeof(AttachmentSample));
    hash = hash_bytes(hash, mesh.vertices, expected_vertices * sizeof(Vector3));
    hash = hash_bytes(hash, mesh.vertex_colours, expected_vertices * sizeof(tColour));
    for (int h = 0; h < expected_faces; ++h) {
        hash = hash_bytes(hash, &mesh.facequads[h], 12);
        hash = hash_bytes(hash, mesh.facequads[h].uv, sizeof(mesh.facequads[h].uv));
        hash = hash_bytes(hash, &mesh.facequads[h].texture_ref->slot_index, sizeof(int));
    }
    // These CPU-only fixtures register null payloads, so the descriptor bank
    // contains no executable-specific pointer values. Include its names and
    // flags as well as face slot IDs to catch swapped texture bindings.
    hash = hash_bytes(hash, &g_texture_refs, 8 + g_texture_refs.count * sizeof(cRTexture));
    printf("sbend case=%d hash=%08x\n", index, hash);
    free_tracked_allocations_to_mark();
    check(g_tracked_allocation_stack.depth == 0 && g_tracked_allocation_total_bytes == 0,
          "builder allocations fully unwound");
}

int main(int argc, char** argv)
{
    if (argc == 3) {
        trace = fopen(argv[2], "wb");
        if (!trace)
            return 2;
    }
    RMathInit();
    run_case(0, 2, 1.0f, true, 4, 15, 16, 2572, argc == 2 && argv[1][0] == '!');
    run_case(1, 4, 2.0f, false, 7, 40, 56, 6200, false);
    run_case(2, 2, 0.0f, true, 1, 6, 4, 736, false);
    run_case(3, 3, 3.0f, true, 10, 44, 60, 7512, false);
    if (trace && fclose(trace) != 0)
        ++failures;
    printf("sbend checks=%d failures=%d\n", checks, failures);
    fflush(0);
    return failures ? 1 : 0;
}
