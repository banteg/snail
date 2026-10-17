// Lifted Android path builders (BuildInvert1, BuildHalfPole, HalfPolePos,
// BuildShimmy, BuildDetour), the 16 mobile path template pairs + 2 entry
// transition pairs, and the trampoline bounce ring (cRSubTrampRingManager).

#include <stdio.h>
#include <string.h>

#include "attachment_sample.h"
#include "bod_list.h"
#include "bod_types.h"
#include "extras.h"
#include "game_root.h"
#include "object_render_types.h"
#include "path_manager.h"
#include "rstring.h"
#include "segment_catalog_types.h"
#include "squidge.h"
#include "sub_loc_tile_ids.h"
#include "sub_tracks.h"
#include "subgame_runtime.h"
#include "texture_registry.h"
#include "transform_matrix.h"
#include "track_attachment_types.h"

float Sqrt(float value);
float ATan(float y, float x);
float Sin(float angle);
float Cos(float angle);
void load_object_definition(char* path, Object* object);

int path_name_code_recovered(cRPathManager* self, char* name)
    __asm__("_ZN13cRPathManager18NameCode_recoveredEPc");
void kind42_transform_recovered(
    cRPath* self, float radius, float x, float y, TransformMatrix* transform, float* out_angle)
    __asm__("_ZN6cRPath45compute_kind42_attachment_transform_recoveredEfffP7tMatrixPf");
void squidge_start_y_recovered(cRSquidge* self, float value)
    __asm__("_ZN9cRSquidge16StartY_recoveredEf");
void set_object_color(Object* object, tColour color);

// The shell keeps its extra paths as primary/secondary pairs, laid out like
// one row of cRSubGame::paths.
struct PathPair {
    cRPath primary;
    cRPath secondary;
};

namespace {

typedef AttachmentSample PathTemplateSample;

PathPair& subgame_path_pair(int slot)
{
    return *reinterpret_cast<PathPair*>(g_game->subgame.paths[slot]);
}

enum {
    kMobilePathBaseCode = 100,
    kMobilePathCount = 16,
    kExtraLoopTheLoop1Transition = 16,
    kExtraInvert1Transition = 17,
    kTotalExtraPathPairs = 21,
    kHalfPoleExtraIndex = 15,
    kTrampRingSlotCount = 8,
};

const char* const kMobilePathNames[kMobilePathCount] = {
    "LOOPTHELOOP1",
    "SBEND1",
    "SBEND2",
    "SBEND4",
    "DETOUR2",
    "DETOUR3",
    "DETOUR",
    "SUPERTRAMPLEFT",
    "TURNOVER2",
    "TURNOVER3",
    "SHIMMY1",
    "SHIMMY2",
    "SHIMMY4",
    "SHIMMY",
    "INVERT1",
    "HALFPOLE",
};

PathPair g_pc_path_pairs_backup[PATH_PAIR_COUNT];
PathPair g_extra_path_pairs[kTotalExtraPathPairs];
bool g_paths_initialized = false;
int g_halfpole_active_slot = -1;

struct SubTrampRing : public cRBodPos {
    int state;
    float progress;
    float step;
};

Object* g_tramp_ring_object = 0;
SubTrampRing g_tramp_rings[kTrampRingSlotCount];

void zero_vec(tVector& v)
{
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
}

void compute_path_deltas(int count, PathTemplateSample* primary, PathTemplateSample* secondary)
{
    for (int i = 0; i < count - 1; ++i) {
        primary[i].delta_dir_to_next = primary[i + 1].transform.position - primary[i].transform.position;
        primary[i].delta_length = primary[i].delta_dir_to_next.Normalize();
        secondary[i].delta_dir_to_next = secondary[i + 1].transform.position - secondary[i].transform.position;
        secondary[i].delta_length = secondary[i].delta_dir_to_next.Normalize();
    }
    primary[count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary[count - 1].delta_length = 1.0f;
    secondary[count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary[count - 1].delta_length = 1.0f;
}

void build_strip_mesh(Path* path, char* texture_a, char* texture_b, bool halfpole)
{
    path->strip_mesh->RequestVertices((path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(2 * path->width_cells * path->segment_count);

    Vector3* vertices = path->strip_mesh->vertices;
    cRFaceQuad* facequads = path->strip_mesh->facequads;
    TransformMatrix pole_transform;
    pole_transform.Identity();
    float out_angle = 0.0f;

    for (int row = 0; row <= path->segment_count; ++row) {
        for (int column = 0; column <= path->width_cells; ++column) {
            float lateral = (float)column - (float)path->width_cells * 0.5f;
            Vector3 generated;
            if (row != path->segment_count) {
                Vector3 offset = path->primary_samples[row].transform.basis_right * lateral;
                generated = path->primary_samples[row].transform.position + offset;
            } else {
                Vector3 offset = path->primary_samples[row - 1].transform.basis_right * lateral;
                generated = (path->primary_samples[row - 1].transform.position + Vector3(0.0f, 0.0f, 1.0f)) + offset;
            }
            int v_idx = column + row * (path->width_cells + 1);
            vertices[v_idx] = generated;
            if (halfpole) {
                int r_sample = row != path->segment_count ? row : row - 1;
                float radius = path->primary_samples[r_sample].special_scalar;
                float root = (float)Sqrt(radius * radius - 16.0f);
                float angle = ATan(4.0f, root) * vertices[v_idx].x * 0.25f;
                out_angle = angle;
                if (row > 1 && row != path->segment_count) {
                    vertices[v_idx].x = Sin(angle) * radius;
                    vertices[v_idx].y = -(radius - Cos(angle) * radius);
                }
            }
        }
    }

    for (int row = 0; row < path->segment_count; ++row) {
        float v0 = (float)(row % 8) * 0.125f;
        float v1 = (float)(row % 8 + 1) * 0.125f;
        for (int column = 0; column < path->width_cells; ++column) {
            float u0 = (float)column * 0.125f;
            float u1 = (float)(column + 1) * 0.125f;
            unsigned short stride = (unsigned short)path->width_cells + 1;
            for (int side = 0; side < 2; ++side) {
                int face_offset = side + 2 * (row * path->width_cells + column);
                facequads[face_offset].header_word = 0;
                if (side == 0) {
                    facequads[face_offset].vertex_0 = column + row * stride;
                    facequads[face_offset].vertex_1 = row * stride + column + 1;
                    facequads[face_offset].vertex_2 = (row + 1) * stride + column + 1;
                    facequads[face_offset].vertex_3 = column + (row + 1) * stride;
                    facequads[face_offset].texture_ref = g_texture_refs.Add(texture_a, 0, 0);
                    facequads[face_offset].uv[0].u = u0;
                    facequads[face_offset].uv[0].v = v0;
                    facequads[face_offset].uv[1].u = u1;
                    facequads[face_offset].uv[1].v = v0;
                    facequads[face_offset].uv[2].u = u1;
                    facequads[face_offset].uv[2].v = v1;
                    facequads[face_offset].uv[3].u = u0;
                    facequads[face_offset].uv[3].v = v1;
                } else {
                    facequads[face_offset].vertex_0 = row * stride + column + 1;
                    facequads[face_offset].vertex_1 = column + row * stride;
                    facequads[face_offset].vertex_2 = column + (row + 1) * stride;
                    facequads[face_offset].vertex_3 = (row + 1) * stride + column + 1;
                    facequads[face_offset].texture_ref = g_texture_refs.Add(texture_b, 0, 0);
                    facequads[face_offset].uv[0].u = u1;
                    facequads[face_offset].uv[0].v = v0;
                    facequads[face_offset].uv[1].u = u0;
                    facequads[face_offset].uv[1].v = v0;
                    facequads[face_offset].uv[2].u = u0;
                    facequads[face_offset].uv[2].v = v1;
                    facequads[face_offset].uv[3].u = u1;
                    facequads[face_offset].uv[3].v = v1;
                }
            }
        }
    }
}

// Android BuildCage2 (30 nodes) and BuildTwister2A (66 nodes). These replace
// the PC variants only in the extras bank; original constructors stay intact.
void build_mobile_shared_path(Path* path, bool cage, bool handedness, char* texture)
{
    path->kind = cage ? PATH_TEMPLATE_KIND_CAGE2 : PATH_TEMPLATE_KIND_TWISTER2;
    path->is_mirrored_x = 0;
    path->side_exit_mode = 0;
    path->width_cells = 3;
    path->width_or_scale = 1.0f;
    path->segment_count = cage ? 30 : 66;
    path->segment_count_f = (float)path->segment_count;
    path->GetNodes();
    path->has_entry_mesh_transition = 0;

    const int last = path->segment_count - 1;
    const float start_x = handedness ? -2.5f : 2.5f;
    for (int row = 0; row <= last; ++row) {
        PathTemplateSample& p = path->primary_samples[row];
        PathTemplateSample& s = path->secondary_samples[row];
        float x, y = 0.0f;
        if (row == 0 || row == last) {
            x = cage && row == last ? -start_x : start_x;
        } else if (cage) {
            x = Cos((float)(row - 1) * 9.424778f / 28.0f) * start_x;
        } else {
            float phase = (float)(row - 1) * 12.566371f / 64.0f;
            float half_phase = phase * 0.5f;
            if (!handedness)
                phase += 3.1415927f;
            x = (Cos(phase) * 0.5f + 0.5f) * -5.0f + 2.5f;
            y = Sin(half_phase) * Sin(phase) * 2.5f;
        }
        p.center_x = x;
        p.rotation_scalar_94 = p.rotation_scalar_98 = p.special_scalar = 0.0f;
        p.lateral_scale = 1.0f;
        p.transform.Identity();
        p.transform.position = Vector3(x, y, (float)row);
        s.transform.Identity();
        s.transform.position = Vector3(x, y + 0.49000001f, (float)row);
    }
    // The first and final samples retain identity orientation on Android.
    for (int row = 1; row < last - 1; ++row) {
        for (int side = 0; side < 2; ++side) {
            PathTemplateSample* bank = side ? path->secondary_samples : path->primary_samples;
            TransformMatrix& frame = bank[row].transform;
            frame.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            frame.basis_forward = bank[row + 1].transform.position - frame.position;
            frame.basis_forward.Normalize();
            frame.basis_right.Cross(frame.basis_up, frame.basis_forward);
            if (cage) {
                float phase = (float)row * 6.2831855f / 28.0f;
                frame.RotLocalZ((1.0f - Cos(phase)) * 0.5f * path->primary_samples[row].center_x * 0.39269909f);
            } else {
                frame.basis_up.Cross(frame.basis_forward, frame.basis_right);
                frame.Orthoganalize();
            }
        }
    }
    compute_path_deltas(path->segment_count, path->primary_samples, path->secondary_samples);
    build_strip_mesh(path, texture, texture, false);
    path->CalcLengthZ();
}

// Lifted from Android cRPath::BuildInvert1 (000516a4).
void build_invert1(Path* path, int width_cells_, char* texture_a, char* texture_b)
{
    path->kind = PATH_TEMPLATE_KIND_INVERT;
    path->is_mirrored_x = 0;
    path->side_exit_mode = 0;
    path->width_cells = width_cells_;
    path->width_or_scale = 1.0f;
    path->segment_count = 34;
    path->segment_count_f = 34.0f;
    path->GetNodes();
    path->has_entry_mesh_transition = 1;

    float cx = (float)path->width_cells * 0.5f - 4.0f;
    PathTemplateSample* p = path->primary_samples;
    PathTemplateSample* s = path->secondary_samples;

    p[0].center_x = cx;
    p[0].rotation_scalar_94 = 0.0f;
    p[0].rotation_scalar_98 = 0.0f;
    p[0].lateral_scale = 1.0f;
    p[0].special_scalar = 0.0f;
    p[0].transform.Identity();
    p[0].transform.position = Vector3(cx, 0.0f, 0.0f);
    p[0].delta_length = 1.0f;
    s[0].transform.Identity();
    s[0].transform.position = Vector3(cx, 0.49000001f, 0.0f);
    s[0].delta_length = 1.0f;

    p[33].center_x = cx;
    p[33].rotation_scalar_94 = 0.0f;
    p[33].rotation_scalar_98 = 3.1415927f;
    p[33].lateral_scale = 1.0f;
    p[33].special_scalar = 0.0f;
    p[33].transform.Identity();
    p[33].transform.position = Vector3(cx, 0.0f, 33.0f);
    p[33].delta_length = 1.0f;
    s[33].transform.Identity();
    s[33].transform.position = Vector3(cx, 0.49000001f, 33.0f);
    s[33].delta_length = 1.0f;

    for (int i = 0; i < 32; ++i) {
        float t = (float)i;
        float angle = (t * 6.2831855f) / 32.0f;
        int idx = i + 1;
        p[idx].center_x = p[0].center_x + t * (p[33].center_x - p[0].center_x) * 0.03125f;
        p[idx].rotation_scalar_94 = 0.0f;
        p[idx].rotation_scalar_98 = -angle;
        p[idx].lateral_scale = 1.0f;
        p[idx].special_scalar = 0.0f;
        p[idx].transform.Identity();
        p[idx].transform.position.x = p[0].center_x * Cos(angle);
        p[idx].transform.position.y = -p[0].center_x * Sin(angle);
        p[idx].transform.position.z = (float)idx;
        p[idx].transform.basis_up = Vector3(Sin(angle), Cos(angle), 0.0f);
        p[idx].transform.basis_forward = p[idx].transform.position - p[idx - 1].transform.position;
        p[idx].transform.basis_forward.Normalize();
        p[idx].transform.basis_right.Cross(p[idx].transform.basis_up, p[idx].transform.basis_forward);
        p[idx].transform.basis_up.Cross(p[idx].transform.basis_forward, p[idx].transform.basis_right);
        p[idx].transform.Orthoganalize();

        s[idx].transform = p[idx].transform;
        Vector3 offset = p[idx].transform.basis_up * 0.49000001f;
        s[idx].transform.position.x += offset.x;
        s[idx].transform.position.y += offset.y;
        s[idx].transform.position.z += offset.z;
    }

    compute_path_deltas(path->segment_count, p, s);
    build_strip_mesh(path, texture_a, texture_b, false);
    path->CalcLengthZ();
}

// Lifted from Android cRPath::BuildHalfPole (00050c78).
void build_halfpole(Path* path, int width_cells_, char* texture_a, char* texture_b)
{
    path->kind = PATH_TEMPLATE_KIND_NONLINEAR_42;
    path->is_mirrored_x = 0;
    path->side_exit_mode = 0;
    path->width_cells = width_cells_;
    path->width_or_scale = 1.0f;
    path->segment_count = 52;
    path->segment_count_f = 52.0f;
    path->GetNodes();
    path->has_entry_mesh_transition = 0;

    PathTemplateSample* p = path->primary_samples;
    PathTemplateSample* s = path->secondary_samples;

    for (int i = 0; i < 16; ++i) {
        float index = (float)i;
        float angle = (index * 0.0625f) * 3.1415927f + 1.5707964f;
        float depth = ((0.5f - Sin(angle) * 0.5f) * 0.94999999f + 0.050000001f) * 4.0f;
        p[i].center_x = (float)path->width_cells * 0.5f - 4.0f;
        p[i].rotation_scalar_98 = 0.0f;
        p[i].rotation_scalar_94 = 0.0f;
        p[i].special_scalar = (depth * depth + 16.0f) / (depth + depth);
        p[i].lateral_scale = 1.0f;
        p[i].transform.Identity();
        p[i].transform.position = Vector3(p[i].center_x, 0.0f, index);
        p[i].delta_length = 1.0f;

        s[i].transform.Identity();
        s[i].transform.position = Vector3(p[i].center_x, 0.49000001f, index);
        s[i].delta_length = 1.0f;
    }

    for (int i = 0; i < 16; ++i) {
        int idx = 36 + i;
        float angle = (1.0f - (float)i * 0.0625f) * 3.1415927f + 1.5707964f;
        float depth = ((0.5f - Sin(angle) * 0.5f) * 0.94999999f + 0.050000001f) * 4.0f;
        p[idx].center_x = 4.0f - (float)path->width_cells * 0.5f;
        p[idx].rotation_scalar_98 = 0.0f;
        p[idx].rotation_scalar_94 = 0.0f;
        p[idx].special_scalar = (depth * depth + 16.0f) / (depth + depth);
        p[idx].lateral_scale = 1.0f;
        p[idx].transform.Identity();
        float z = (float)idx;
        p[idx].transform.position = Vector3(p[idx].center_x, 0.0f, z);
        p[idx].delta_length = 1.0f;

        s[idx].transform.Identity();
        s[idx].transform.position = Vector3(p[idx].center_x, 0.49000001f, z);
        s[idx].delta_length = 1.0f;
    }

    for (int i = 0; i < 20; ++i) {
        int idx = 16 + i;
        p[idx].center_x = p[0].center_x + ((p[36].center_x - p[0].center_x) * (float)i) / 20.0f;
        p[idx].rotation_scalar_98 = 0.0f;
        p[idx].rotation_scalar_94 = 0.0f;
        p[idx].special_scalar = 4.0f;
        p[idx].lateral_scale = 1.0f;
        p[idx].transform.Identity();
        p[idx].transform.position = Vector3(0.0f, 0.0f, (float)idx);
        p[idx].transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
        p[idx].transform.basis_forward = p[idx].transform.position - p[idx - 1].transform.position;
        p[idx].transform.basis_forward.Normalize();
        p[idx].transform.basis_right.Cross(p[idx].transform.basis_up, p[idx].transform.basis_forward);

        s[idx].transform = p[idx].transform;
        Vector3 offset = p[idx].transform.basis_up * 0.49000001f;
        s[idx].transform.position.x += offset.x;
        s[idx].transform.position.y += offset.y;
        s[idx].transform.position.z += offset.z;
    }

    compute_path_deltas(path->segment_count, p, s);
    build_strip_mesh(path, texture_a, texture_b, true);
    path->CalcLengthZ();
}

// Lifted from Android cRPath::BuildShimmy (00051f8c).
void build_shimmy(Path* path, int width_cells_, char* texture_a, char* texture_b)
{
    path->kind = PATH_TEMPLATE_KIND_WIBBLE;
    path->is_mirrored_x = 0;
    path->side_exit_mode = 0;
    path->width_cells = width_cells_;
    path->width_or_scale = 1.0f;
    path->segment_count = 32;
    path->segment_count_f = 32.0f;
    path->GetNodes();
    path->has_entry_mesh_transition = 0;

    float cx0 = (path->width_cells == 1) ? -0.5f : 0.0f;
    float amplitude = 0.30000001f;
    switch (path->width_cells) {
    case 1:
        amplitude = 0.100000001f;
        break;
    case 2:
        amplitude = 0.150000006f;
        break;
    case 4:
        amplitude = 0.200000003f;
        break;
    default:
        break;
    }

    PathTemplateSample* p = path->primary_samples;
    PathTemplateSample* s = path->secondary_samples;

    p[0].center_x = cx0;
    p[0].rotation_scalar_94 = 0.0f;
    p[0].rotation_scalar_98 = 0.0f;
    p[0].transform.Identity();
    p[0].transform.position = Vector3(cx0, 0.0f, 0.0f);
    p[0].delta_length = 1.0f;
    s[0].transform.Identity();
    s[0].transform.position = Vector3(cx0, 0.49000001f, 0.0f);
    s[0].delta_length = 1.0f;

    p[31].center_x = cx0;
    p[31].rotation_scalar_94 = 0.0f;
    p[31].rotation_scalar_98 = 0.0f;
    p[31].transform.Identity();
    p[31].transform.position = Vector3(cx0, 0.0f, 31.0f);
    p[31].delta_length = 1.0f;
    s[31].transform.Identity();
    s[31].transform.position = Vector3(cx0, 0.49000001f, 31.0f);
    s[31].delta_length = 1.0f;

    for (int i = 0; i < 30; ++i) {
        int idx = i + 1;
        float angle = ((float)i * 25.132742f) / 30.0f;
        p[idx].center_x = p[0].center_x + Sin(angle) * amplitude;
        p[idx].rotation_scalar_94 = 0.0f;
        p[idx].rotation_scalar_98 = 0.0f;
        p[idx].transform.Identity();
        p[idx].transform.position = Vector3(p[idx].center_x, 0.0f, (float)idx);
        p[idx].transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
        p[idx].transform.basis_forward =
            Vector3(0.0f, 0.0f - p[idx - 1].transform.position.y, (float)idx - p[idx - 1].transform.position.z);
        p[idx].transform.basis_forward.Normalize();
        p[idx].transform.basis_right.Cross(p[idx].transform.basis_up, p[idx].transform.basis_forward);

        s[idx].transform = p[idx].transform;
        s[idx].transform.position.x = p[0].center_x;
        s[idx].transform.position.y += p[idx].transform.basis_up.y * 0.49000001f;
        s[idx].transform.position.z += p[idx].transform.basis_up.z * 0.49000001f;
    }

    compute_path_deltas(path->segment_count, p, s);
    build_strip_mesh(path, texture_a, texture_b, false);
    path->CalcLengthZ();
}

// Lifted from Android cRPath::BuildDetour (00054e7c).
void build_detour(Path* path, int width_cells_, char* texture_a, char* texture_b)
{
    path->kind = PATH_TEMPLATE_KIND_SNAKE;
    path->is_mirrored_x = 0;
    path->side_exit_mode = 0;
    path->width_cells = width_cells_;
    path->width_or_scale = 1.0f;
    path->segment_count = 46;
    path->segment_count_f = 46.0f;
    path->GetNodes();
    path->has_entry_mesh_transition = 0;

    float cx0 = (float)path->width_cells * 0.5f - 4.0f;
    PathTemplateSample* p = path->primary_samples;
    PathTemplateSample* s = path->secondary_samples;

    for (int i = 0; i < 3; ++i) {
        p[i].center_x = cx0;
        p[i].rotation_scalar_94 = 0.0f;
        p[i].rotation_scalar_98 = 0.0f;
        p[i].transform.Identity();
        p[i].transform.position = Vector3(cx0, 0.0f, (float)i);
        s[i].transform.Identity();
        s[i].transform.position = Vector3(cx0, 0.49000001f, (float)i);
    }

    for (int i = 0; i <= 40; ++i) {
        int idx = i + 3;
        float phase = ((float)i * 6.2831855f) / 39.0f;
        float roll = Sin(phase * 0.5f) * -1.396f * Cos(phase);
        p[idx].center_x = Cos(phase) * p[0].center_x;
        p[idx].rotation_scalar_94 = 0.0f;
        p[idx].rotation_scalar_98 = 0.0f;
        p[idx].transform.Identity();
        p[idx].transform.position = Vector3(p[idx].center_x, 0.0f, (float)idx);
        s[idx].transform.Identity();
        s[idx].transform.position = Vector3(p[idx].center_x, 0.0f, (float)idx);

        if (i == 0) {
            p[idx].transform.RotIdentity();
            s[idx].transform.RotIdentity();
        } else {
            int prev = idx - 1;
            p[prev].transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            p[prev].transform.basis_forward = p[idx].transform.position - p[prev].transform.position;
            p[prev].transform.basis_forward.Normalize();
            p[prev].transform.basis_right.Cross(p[prev].transform.basis_up, p[prev].transform.basis_forward);
            p[prev].transform.RotLocalZ(roll);

            s[prev].transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            s[prev].transform.basis_forward = s[idx].transform.position - s[prev].transform.position;
            s[prev].transform.basis_forward.Normalize();
            s[prev].transform.basis_right.Cross(s[prev].transform.basis_up, s[prev].transform.basis_forward);
            s[prev].transform.RotLocalZ(roll);
            s[prev].transform.position.x += s[prev].transform.basis_up.x * 0.49000001f;
            s[prev].transform.position.y += s[prev].transform.basis_up.y * 0.49000001f;
            s[prev].transform.position.z += s[prev].transform.basis_up.z * 0.49000001f;
        }
    }

    for (int idx = 43; idx < 46; ++idx) {
        p[idx].center_x = p[0].center_x;
        p[idx].rotation_scalar_94 = 0.0f;
        p[idx].rotation_scalar_98 = 0.0f;
        p[idx].transform.Identity();
        p[idx].transform.position = Vector3(p[0].center_x, 0.0f, (float)idx);
        s[idx].transform.Identity();
        s[idx].transform.position = Vector3(p[0].center_x, 0.49000001f, (float)idx);
    }

    compute_path_deltas(path->segment_count, p, s);
    build_strip_mesh(path, texture_a, texture_b, false);
    path->CalcLengthZ();
}

// Android cRPath::BuildSBend (0004ee74).
void build_sbend(Path* path, int width_cells_, float height, bool centered, char* texture_a, char* texture_b)
{
    path->kind = PATH_TEMPLATE_KIND_FAMILY_10;
    path->is_mirrored_x = 0;
    path->side_exit_mode = 0;
    path->width_cells = width_cells_;
    path->width_or_scale = 1.0f;
    int steps = (int)(height * 6.2831855f * 0.5f);
    path->segment_count = steps + 1;
    path->segment_count_f = (float)(steps + 1);
    float x_bias = (width_cells_ == 1) ? 0.5f : 0.0f;
    path->GetNodes();
    path->has_entry_mesh_transition = 0;

    PathTemplateSample* p = path->primary_samples;
    PathTemplateSample* s = path->secondary_samples;

    if (centered)
        p[0].center_x = x_bias;
    else
        p[0].center_x = (x_bias - 4.0f) + (float)width_cells_ * 0.5f;
    p[0].rotation_scalar_98 = 0.0f;
    p[0].rotation_scalar_94 = 0.0f;
    p[0].special_scalar = 0.0f;
    p[0].lateral_scale = 1.0f;
    p[0].transform.Identity();
    p[0].transform.position.x = p[0].center_x;
    p[0].transform.position.y = 0.0f;
    p[0].transform.position.z = 0.0f;

    s[0].transform.Identity();
    s[0].transform.position.x = p[0].center_x;
    s[0].transform.position.y = 0.49000001f;
    s[0].transform.position.z = 0.0f;

    for (int i = 0; i < steps; ++i) {
        int idx = i + 1;
        float phase = (float)i * 6.2831855f / (float)steps;
        p[idx].center_x = p[0].center_x;
        p[idx].rotation_scalar_98 = 0.0f;
        p[idx].rotation_scalar_94 = 0.0f;
        p[idx].special_scalar = 0.0f;
        p[idx].lateral_scale = 1.0f;
        p[idx].transform.Identity();
        p[idx].transform.position.x = p[idx].center_x;
        p[idx].transform.position.y = (1.0f - Cos(phase * 0.5f)) * 0.5f * height;
        p[idx].transform.position.z = (float)idx;

        p[idx].transform.basis_up = Vector3(1.0f, 0.0f, 0.0f);
        p[idx].transform.basis_forward = p[idx].transform.position - p[idx - 1].transform.position;
        p[idx].transform.basis_forward.Normalize();
        p[idx].transform.basis_up.Cross(p[idx].transform.basis_forward, p[idx].transform.basis_right);

        s[idx].transform = p[idx].transform;
        s[idx].transform.position.x += p[idx].transform.basis_up.x * 0.49000001f;
        s[idx].transform.position.y += p[idx].transform.basis_up.y * 0.49000001f;
        s[idx].transform.position.z += p[idx].transform.basis_up.z * 0.49000001f;
    }

    compute_path_deltas(path->segment_count, p, s);
    build_strip_mesh(path, texture_a, texture_b, false);
    path->CalcLengthZ();
}

void shift_supertramp_x(Path* path, float dx)
{
    for (int i = 0; i <= path->segment_count; ++i) {
        path->primary_samples[i].center_x += dx;
        path->primary_samples[i].transform.position.x += dx;
        path->secondary_samples[i].transform.position.x += dx;
    }
    if (path->strip_mesh && path->strip_mesh->vertices) {
        for (int v = 0; v < path->strip_mesh->vertex_count; ++v)
            path->strip_mesh->vertices[v].x += dx;
    }
}

void finish_standard_pair(PathPair& pair)
{
    zero_vec(pair.primary.position);
    pair.secondary.SetObject(g_object_list.Add());
    pair.secondary.Mirror(&pair.primary);
    zero_vec(pair.secondary.position);
    pair.primary.build_track_fringe_mesh((char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_vec(pair.primary.fringe_mesh_bod.position);
    pair.secondary.build_track_fringe_mesh((char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_vec(pair.secondary.fringe_mesh_bod.position);
}

void link_transition_pair(PathPair& base, PathPair& trans)
{
    base.primary.entry_transition_strip_mesh = trans.primary.object;
    base.primary.entry_base_strip_mesh = base.primary.object;
    base.secondary.entry_transition_strip_mesh = trans.secondary.object;
    base.secondary.entry_base_strip_mesh = base.secondary.object;
}

bool is_halfpole_path(const cRPath* path)
{
    if (path == &g_extra_path_pairs[kHalfPoleExtraIndex].primary
        || path == &g_extra_path_pairs[kHalfPoleExtraIndex].secondary)
        return true;
    if (g_halfpole_active_slot >= 0 && g_halfpole_active_slot < PATH_PAIR_COUNT && g_game) {
        const PathPair& mapped = subgame_path_pair(g_halfpole_active_slot);
        if (path == &mapped.primary || path == &mapped.secondary)
            return true;
    }
    return false;
}

}  // namespace

void extras_init_paths()
{
    if (!g_port_ultimate || g_paths_initialized)
        return;

    memcpy(g_pc_path_pairs_backup, g_game->subgame.paths, sizeof(g_pc_path_pairs_backup));
    int start_object_index = g_object_list.count;

    for (int i = 0; i < kTotalExtraPathPairs; ++i) {
        g_extra_path_pairs[i].primary.initialize_path_template_record_pair();
        g_extra_path_pairs[i].secondary.initialize_path_template_record_pair();
        g_extra_path_pairs[i].primary.SetObject(g_object_list.Add());
    }

    char* slide0 = (char*)"Objects/World00/Slide0.tga";
    char* track0 = (char*)"Objects/World00/Track0.tga";
    char* back = (char*)"Objects/World00/Back.tga";
    char* dark = (char*)"Objects/Path/VeryDark.tga";
    char* warn = (char*)"Objects/World00/TrackWarn.tga";
    char* fringe = (char*)"Objects/Universe/Fringe.tga";

    // 0: LOOPTHELOOP1 + 16: TRANS_LOOPTHELOOP1
    g_extra_path_pairs[0].primary.initialize_looptheloop_path_template_pair(6.0f, 1, 0, slide0, back, dark);
    finish_standard_pair(g_extra_path_pairs[0]);
    g_extra_path_pairs[kExtraLoopTheLoop1Transition].primary.initialize_looptheloop_path_template_pair(
        6.0f, 1, 1, slide0, back, dark);
    finish_standard_pair(g_extra_path_pairs[kExtraLoopTheLoop1Transition]);
    link_transition_pair(g_extra_path_pairs[0], g_extra_path_pairs[kExtraLoopTheLoop1Transition]);

    // 1..3: SBEND1, SBEND2, SBEND4 + update PC slot 14 (SBEND, unused on PC) to Android BuildSBend
    const int sbend_widths[3] = {1, 2, 4};
    for (int i = 0; i < 3; ++i) {
        build_sbend(&g_extra_path_pairs[1 + i].primary, sbend_widths[i], 8.0f, true, track0, track0);
        finish_standard_pair(g_extra_path_pairs[1 + i]);
    }
    g_pc_path_pairs_backup[14].primary.initialize_path_template_record_pair();
    g_pc_path_pairs_backup[14].secondary.initialize_path_template_record_pair();
    g_pc_path_pairs_backup[14].primary.SetObject(g_object_list.Add());
    build_sbend(&g_pc_path_pairs_backup[14].primary, 8, 8.0f, true, track0, track0);
    finish_standard_pair(g_pc_path_pairs_backup[14]);
    subgame_path_pair(14) = g_pc_path_pairs_backup[14];

    // 4..6: DETOUR2, DETOUR3, DETOUR
    const int detour_widths[3] = {2, 3, 4};
    for (int i = 0; i < 3; ++i) {
        build_detour(&g_extra_path_pairs[4 + i].primary, detour_widths[i], slide0, back);
        finish_standard_pair(g_extra_path_pairs[4 + i]);
    }

    // 7: SUPERTRAMPLEFT (-3.0f primary, +3.0f secondary)
    g_extra_path_pairs[7].primary.initialize_supertramp_path_template_pair(6.0f, 2, 1, slide0, back, dark, warn);
    shift_supertramp_x(&g_extra_path_pairs[7].primary, -3.0f);
    zero_vec(g_extra_path_pairs[7].primary.position);
    g_extra_path_pairs[7].primary.build_track_fringe_supertramp_mesh(fringe);
    zero_vec(g_extra_path_pairs[7].primary.fringe_mesh_bod.position);

    g_extra_path_pairs[7].secondary.SetObject(g_object_list.Add());
    g_extra_path_pairs[7].secondary.initialize_supertramp_path_template_pair(6.0f, 2, 1, slide0, back, dark, warn);
    shift_supertramp_x(&g_extra_path_pairs[7].secondary, 3.0f);
    zero_vec(g_extra_path_pairs[7].secondary.position);
    g_extra_path_pairs[7].secondary.build_track_fringe_supertramp_mesh(fringe);
    zero_vec(g_extra_path_pairs[7].secondary.fringe_mesh_bod.position);

    // 8..9: TURNOVER2, TURNOVER3
    g_extra_path_pairs[8].primary.initialize_turnover_path_template_pair(6.0f, 2, 0, slide0, back, dark);
    finish_standard_pair(g_extra_path_pairs[8]);
    g_extra_path_pairs[9].primary.initialize_turnover_path_template_pair(6.0f, 3, 0, slide0, back, dark);
    finish_standard_pair(g_extra_path_pairs[9]);

    // 10..13: SHIMMY1, SHIMMY2, SHIMMY4, SHIMMY
    const int shimmy_widths[4] = {1, 2, 4, 8};
    for (int i = 0; i < 4; ++i) {
        build_shimmy(&g_extra_path_pairs[10 + i].primary, shimmy_widths[i], slide0, slide0);
        finish_standard_pair(g_extra_path_pairs[10 + i]);
    }

    // 14: INVERT1 + 17: TRANS_INVERT1
    build_invert1(&g_extra_path_pairs[14].primary, 4, slide0, back);
    finish_standard_pair(g_extra_path_pairs[14]);
    build_invert1(&g_extra_path_pairs[kExtraInvert1Transition].primary, 4, slide0, back);
    finish_standard_pair(g_extra_path_pairs[kExtraInvert1Transition]);
    link_transition_pair(g_extra_path_pairs[14], g_extra_path_pairs[kExtraInvert1Transition]);

    // 15: HALFPOLE
    build_halfpole(&g_extra_path_pairs[kHalfPoleExtraIndex].primary, 8, slide0, back);
    finish_standard_pair(g_extra_path_pairs[kHalfPoleExtraIndex]);

    // Shared names changed shape in mobile as well: CAGE2, TWISTER2A/B.
    const int shared_slots[3] = {15, 45, 46};
    for (int i = 0; i < 3; ++i) {
        PathPair& pair = g_extra_path_pairs[18 + i];
        build_mobile_shared_path(&pair.primary, i == 0, i != 2, slide0);
        finish_standard_pair(pair);
        g_pc_path_pairs_backup[shared_slots[i]] = pair;
        subgame_path_pair(shared_slots[i]) = pair;
    }

    // TrampRing object and 8 pool instances
    g_tramp_ring_object = g_object_list.Add();
    load_object_definition((char*)"Objects/TrampRing", g_tramp_ring_object);
    g_tramp_ring_object->blend_mode = 5;
    g_tramp_ring_object->flags |= OBJECT_FLAG_DISABLE_CULLING | OBJECT_FLAG_REFRESH_TINT_EACH_DRAW;
    if (g_tramp_ring_object->facequads && g_tramp_ring_object->facequads[0].texture_ref)
        g_tramp_ring_object->facequads[0].texture_ref->flags |= 0x400;
    for (int i = 0; i < kTrampRingSlotCount; ++i) {
        g_tramp_rings[i].initialize_noop_renderable_bod();
        g_tramp_rings[i].SetObject(g_tramp_ring_object);
        g_tramp_rings[i].list_flags |= BOD_FLAG_USE_TRANSFORM | BOD_FLAG_AFTER_SPRITES;
        g_tramp_rings[i].transform.Identity();
        g_tramp_rings[i].state = 0;
        g_tramp_rings[i].progress = 0.0f;
        g_tramp_rings[i].step = 0.0f;
    }

    for (int idx = start_object_index; idx < g_object_list.count; ++idx) {
        Object* obj = &g_object_list.objects[idx];
        if (obj->vertex_count != 0) {
            obj->calc_object_bounding_box();
            ObjectProcJoinTextures(obj);
            obj->CalcTextureGroups();
            if ((obj->flags & OBJECT_FLAG_TOON_ENABLED) != 0) {
                obj->CalcFaceQuadNormals();
                obj->CalcEdges();
            }
            build_object_texture_group_buffers(obj);
        }
    }

    tColour path_transition_color;
    path_transition_color.noop_this_constructor();
    path_transition_color.store_color4f(1.0f, 1.0f, 1.0f, 0.60000002f);
    set_object_color(g_extra_path_pairs[kExtraLoopTheLoop1Transition].primary.object, path_transition_color);
    set_object_color(g_extra_path_pairs[kExtraLoopTheLoop1Transition].secondary.object, path_transition_color);
    set_object_color(g_extra_path_pairs[kExtraInvert1Transition].primary.object, path_transition_color);
    set_object_color(g_extra_path_pairs[kExtraInvert1Transition].secondary.object, path_transition_color);
    g_paths_initialized = true;
}

static void remap_segment_paths(SubSegment* seg, int* mapped_slot_for_extra, bool* slot_used)
{
    for (int r = 0; r < seg->row_count; ++r) {
        if ((seg->rows[r].flags & AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY) == 0)
            continue;
        int idx = seg->rows[r].path_template_index;
        if (idx >= 0 && idx < PATH_PAIR_COUNT)
            slot_used[idx] = true;
    }
    for (int r = 0; r < seg->row_count; ++r) {
        if ((seg->rows[r].flags & AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY) == 0)
            continue;
        int idx = seg->rows[r].path_template_index;
        if (idx < kMobilePathBaseCode || idx >= kMobilePathBaseCode + kMobilePathCount)
            continue;
        int extra_idx = idx - kMobilePathBaseCode;
        if (mapped_slot_for_extra[extra_idx] < 0) {
            int chosen = -1;
            // Prefer auxiliary slots 51..62 and unused WARP slot 30 first.
            for (int s = 51; s < PATH_PAIR_COUNT; ++s) {
                if (!slot_used[s]) {
                    chosen = s;
                    break;
                }
            }
            if (chosen < 0 && !slot_used[30])
                chosen = 30;
            if (chosen < 0) {
                for (int s = 0; s < 51; ++s) {
                    if (s != 36 && !slot_used[s]) {
                        chosen = s;
                        break;
                    }
                }
            }
            if (chosen >= 0) {
                slot_used[chosen] = true;
                mapped_slot_for_extra[extra_idx] = chosen;
                subgame_path_pair(chosen) = g_extra_path_pairs[extra_idx];
                if (extra_idx == kHalfPoleExtraIndex)
                    g_halfpole_active_slot = chosen;
            }
        }
        if (mapped_slot_for_extra[extra_idx] >= 0)
            seg->rows[r].path_template_index = mapped_slot_for_extra[extra_idx];
    }
}

void extras_map_level_paths(cRSubTracks* level_def)
{
    if (!g_port_ultimate || !g_paths_initialized || level_def != &g_game->subgame.level_definition)
        return;

    memcpy(g_game->subgame.paths, g_pc_path_pairs_backup, sizeof(g_pc_path_pairs_backup));
    g_halfpole_active_slot = -1;

    int mapped_slot_for_extra[kMobilePathCount];
    for (int i = 0; i < kMobilePathCount; ++i)
        mapped_slot_for_extra[i] = -1;
    bool slot_used[PATH_PAIR_COUNT];
    memset(slot_used, 0, sizeof(slot_used));

    for (int i = 0; i < level_def->segment_count; ++i)
        remap_segment_paths(&level_def->segment_slots[i], mapped_slot_for_extra, slot_used);
    remap_segment_paths(&level_def->first_segment, mapped_slot_for_extra, slot_used);
    remap_segment_paths(&level_def->last_segment, mapped_slot_for_extra, slot_used);
}

void extras_clear_tramp_rings()
{
    if (!g_paths_initialized || !g_game)
        return;
    for (int i = 0; i < kTrampRingSlotCount; ++i) {
        if ((g_tramp_rings[i].list_flags & BOD_FLAG_LINKED) != 0)
            g_game->active_bod_list.remove_bod(&g_tramp_rings[i]);
        g_tramp_rings[i].state = 0;
        g_tramp_rings[i].progress = 0.0f;
    }
}

// Android cRSubTrampRingManager::AddRing (0006d5b4).
void extras_add_tramp_ring(cRSubLoc* cell)
{
    if (!g_port_ultimate || !g_paths_initialized || !cell)
        return;
    while (cell->tile_id == SUBLOC_TILE_TRAMPOLINE)
        cell -= 1;
    cRSubLoc* scan = cell + 1;
    while (scan->tile_id == SUBLOC_TILE_TRAMPOLINE)
        scan -= SUBGAME_TRACK_LANE_COUNT;
    cRSubLoc* center = scan + 3 * SUBGAME_TRACK_LANE_COUNT;

    for (int i = 0; i < kTrampRingSlotCount; ++i) {
        SubTrampRing& ring = g_tramp_rings[i];
        if (ring.state == 0) {
            ring.state = 1;
            ring.progress = 0.0f;
            ring.step = g_game->subgame.subgame_rate * 0.041666668f;
            ring.transform.Identity();
            ring.transform.position = center->position;
            ring.transform.position.y -= 0.2f;
            ring.color.Set(1.0f, 1.0f, 1.0f, 250.0f / 255.0f);
            ring.list_flags |= BOD_FLAG_RENDER_ENABLED | BOD_FLAG_USE_TRANSFORM;
            if ((ring.list_flags & BOD_FLAG_LINKED) == 0)
                ring.add_bod_after(&g_game->subgame.fringe_attachment_list_head);
            return;
        }
    }
}

// Android cRSubTrampRing::AI (0006d948).
void extras_step_tramp_rings()
{
    if (!g_port_ultimate || !g_paths_initialized || !g_game)
        return;
    if (g_game->subgame.subgame_state != 2)
        return;
    for (int i = 0; i < kTrampRingSlotCount; ++i) {
        SubTrampRing& ring = g_tramp_rings[i];
        if (ring.state != 1)
            continue;
        ring.progress += ring.step;
        if (ring.progress > 1.0f) {
            ring.state = 0;
            ring.progress = 0.0f;
            if ((ring.list_flags & BOD_FLAG_LINKED) != 0)
                g_game->active_bod_list.remove_bod(&ring);
            continue;
        }
        ring.transform.RotIdentity();
        float scale = 2.5f + 12.0f * ring.progress;
        ring.transform.basis_right = ring.transform.basis_right * scale;
        ring.transform.basis_up = ring.transform.basis_up * scale;
        ring.transform.basis_forward = ring.transform.basis_forward * scale;
        int alpha_byte = (int)((1.0f - ring.progress) * 250.0f);
        ring.color.a = (float)alpha_byte * (1.0f / 255.0f);
    }
}

int cRPathManager::NameCode(char* name)
{
    int code = path_name_code_recovered(this, name);
    if (code != -1 || !g_port_ultimate)
        return code;
    for (int i = 0; i < kMobilePathCount; ++i) {
        if (Rstrcmp(name, (char*)kMobilePathNames[i]))
            return kMobilePathBaseCode + i;
    }
    return -1;
}

// Android cRPath::HalfPolePos (0004c5f0) when `this` is the HALFPOLE path pair.
void cRPath::compute_kind42_attachment_transform(
    float radius, float x, float y, TransformMatrix* transform, float* out_angle)
{
    if (!g_port_ultimate || !is_halfpole_path(this)) {
        kind42_transform_recovered(this, radius, x, y, transform, out_angle);
        return;
    }
    float root = (float)Sqrt(radius * radius - 16.0f);
    float angle = ATan(4.0f, root);
    *out_angle = angle * x * 0.25f;
    transform->RotIdentity();
    transform->RotLocalZ(-*out_angle);

    float r = radius + y;
    transform->position.x = Sin(*out_angle) * r;
    transform->position.y = -(radius - Cos(*out_angle) * r);
}

void cRSquidge::StartY(float value)
{
    squidge_start_y_recovered(this, value);
    if (!g_port_ultimate || !g_game)
        return;
    cRSubGoldy* player = &g_game->subgame.player;
    if (this == &player->squidge) {
        cRSubLoc* cell = g_game->subgame.LocFromPos(&player->transform.position);
        if (cell && cell->tile_id == SUBLOC_TILE_TRAMPOLINE
            && cell->position.y + 0.49000001f > player->transform.position.y
            && cell->position.y - 0.49000001f < player->transform.position.y) {
            extras_add_tramp_ring(cell);
        }
    }
}

__attribute__((export_name("snail_extra_path_pair")))
const PathPair* extras_get_mobile_path_pair(int extra_index)
{
    if (extra_index < 0 || extra_index >= kTotalExtraPathPairs)
        return 0;
    return &g_extra_path_pairs[extra_index];
}

__attribute__((export_name("snail_tramp_ring_active_count")))
int extras_tramp_ring_active_count()
{
    int active = 0;
    for (int i = 0; i < kTrampRingSlotCount; ++i) {
        if (g_tramp_rings[i].state != 0)
            ++active;
    }
    return active;
}
