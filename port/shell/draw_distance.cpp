// The optional longer view (draw_distance.h). What limits the original's view
// ahead of the snail, from the player's z:
//
// - the projection's far plane, 52 units from the camera (render_camera), and
//   the fog band 30-50 (initialize_game_assets_and_world);
// - the static track: build_track_render_caches bakes every row into 24-row
//   cache bodies at level start, and update_track_render_cache_rows links a
//   cache row once the player is within 46 units of it;
// - everything the row scan in cRSubGame::AI links or spawns, up to
//   active_window_min_z + 46 (player z + 38): row models, uncached cells
//   (wall2, trampolines, path entries) and every pickup, hazard, parcel and
//   ring. The spawns draw RAND and allocate from pools, so they stay as they
//   are; the bodies that already exist are previewed here;
// - the ten landscape repeats, hidden past fog_end and wrapped three repeats
//   ahead by update_active_landscape_entry.
//
// Each write below goes through an undo log that draw_distance_end_frame
// replays backwards, so the game's state after a frame is the state before it.

#include <string.h>

#include "draw_distance.h"
#include "game_root.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"

float g_port_draw_distance = 1.0f;

namespace {

const float kOriginalFarZ = 52.0f;  // render_camera
const int kGameplayFrontendState = 11;
const int kCacheRowSpan = 24;       // rows per SegmentCache row

struct Saved {
    void* at;
    unsigned int size;
    unsigned char bytes[16];
};

Saved g_undo[16384];
int g_undo_count = 0;
float g_extra = 0;

template <typename T>
void save(T& value)
{
    static_assert(sizeof(T) <= sizeof(Saved::bytes), "undo slot too small");
    if (g_undo_count == (int)(sizeof(g_undo) / sizeof(g_undo[0])))
        __builtin_trap();
    Saved& slot = g_undo[g_undo_count++];
    slot.at = &value;
    slot.size = sizeof(T);
    memcpy(slot.bytes, &value, sizeof(T));
}

template <typename T>
void set(T& value, const T& to)
{
    save(value);
    value = to;
}

// cLinkedList<cRBod>::AddAfter, as update_subgame links group members.
void link_after(BodNode* node, BodNode* head)
{
    if (node->list_flags & BOD_FLAG_LINKED)
        return;
    BodNode* next = head->list_next;
    set(node->list_prev, head);
    set(node->list_next, next);
    set(head->list_next, node);
    if (next)
        set(next->list_prev, node);
    set(node->list_flags, node->list_flags | BOD_FLAG_LINKED);
}

// cLinkedList<cRBod>::Add, as update_subgame links row models.
void link_front(BodList* list, BodNode* node)
{
    if (node->list_flags & BOD_FLAG_LINKED)
        return;
    BodNode* first = list->first;
    set(node->list_prev, (BodNode*)0);
    set(node->list_next, first);
    if (first)
        set(first->list_prev, node);
    set(list->first, node);
    set(node->list_flags, node->list_flags | BOD_FLAG_LINKED);
}

// Cache rows update_track_render_cache_rows would link once the player is
// `extra` units further on, linked the same way.
void preview_cache_rows(cRSubGame* game, float horizon)
{
    SegmentCache& cache = game->segment_cache;
    int built = (game->runtime_row_count + kCacheRowSpan - 1) / kCacheRowSpan;
    if (built > TRACK_RENDER_CACHE_ROW_COUNT)
        built = TRACK_RENDER_CACHE_ROW_COUNT;
    float row_z = cache.next_cache_row_z;
    for (int row = cache.next_cache_row_index; row < built && horizon > row_z; ++row, row_z += kCacheRowSpan) {
        TrackRenderCacheSlot* slots = cache.slots[row];
        tColour skirt;
        game->GetSkirtColour(&skirt);
        for (int family = 0; family < TRACK_RENDER_CACHE_FAMILY_COUNT; ++family) {
            BodNode* head = family == TRACK_RENDER_CACHE_FRINGE ? (BodNode*)&game->fringe_attachment_list_head
                                                                : (BodNode*)&game->track_body_list_head;
            link_after(&slots[family], head);
            set(slots[family].position, Vector3(0.0f, 0.0f, 0.0f));
            if (family == TRACK_RENDER_CACHE_FRINGE)
                set(slots[family].color, skirt);
            else {
                tColour white;
                white.White();
                set(slots[family].color, white);
            }
        }
    }
}

// The bodies the row scan links without spawning anything: row models and
// uncached cells. Pickups, hazards, parcels and rings are spawned there (with
// RAND draws and pool slots), so they still appear at the original distance.
void preview_scan_rows(cRSubGame* game, int end)
{
    if (end > game->completion_row_start + 20)
        end = game->completion_row_start + 20;
    if (end > game->runtime_row_count)
        end = game->runtime_row_count;
    for (int row = game->runtime_row_scan_end; row < end; ++row) {
        if (row < 0)
            continue;
        cRSubRow& sub_row = game->runtime_rows[row];
        if (sub_row.flags & SUBROW_FLAG_ROW_MODEL_PRESENT)
            link_front(&g_game->active_bod_list, &sub_row.row_model);
        for (int lane = 0; lane < SUBGAME_TRACK_LANE_COUNT; ++lane) {
            cRSubLoc& cell = game->runtime_cells[row][lane];
            if ((cell.list_flags & BOD_FLAG_LINKED) || !(cell.lane_and_flags & SUBLOC_FLAG_UNCACHED_BODY))
                continue;
            if (cell.tile_id == SUBLOC_TILE_PATH_ENTRY_LOWERCASE || cell.tile_id == SUBLOC_TILE_PATH_ENTRY_UPPERCASE) {
                if (!cell.object)
                    continue;
                link_after(&cell, &game->special_track_cell_list_head);
                set(cell.render_arg_20, (float)(row % SUBGAME_TRACK_LANE_COUNT) * 0.125f);
                link_after(&sub_row.attachment_body, &game->fringe_attachment_list_head);
                set(sub_row.attachment_body.position, cell.position);
            } else {
                link_after(&cell, &game->track_body_list_head);
            }
        }
    }
}

// Landscape repeats: show the ones hidden past fog_end that are now in view,
// and spread the repeats that update_active_landscape_entry has wrapped onto
// the same place out ahead of the furthest one.
void preview_landscape(cRSubGame* game, float horizon)
{
    ActiveLandscapeEntry* entries = game->landscape_manager.active_entries;
    float furthest = -1e30f;
    float span = 0;
    for (int i = 0; i < LANDSCAPE_ACTIVE_ENTRY_COUNT; ++i) {
        ActiveLandscapeEntry& entry = entries[i];
        if (entry.state != 1 || !entry.object || !(entry.list_flags & BOD_FLAG_LINKED))
            continue;
        span = entry.repeat_z_span;
        if (entry.transform.position.z > furthest)
            furthest = entry.transform.position.z;
    }
    if (span <= 0)
        return;
    for (int i = 0; i < LANDSCAPE_ACTIVE_ENTRY_COUNT; ++i) {
        ActiveLandscapeEntry& entry = entries[i];
        if (entry.state != 1 || !entry.object || !(entry.list_flags & BOD_FLAG_LINKED))
            continue;
        bool duplicate = false;
        for (int j = 0; j < i; ++j) {
            float dz = entries[j].transform.position.z - entry.transform.position.z;
            if (entries[j].state == 1 && entries[j].object && dz < span * 0.01f && dz > -span * 0.01f)
                duplicate = true;
        }
        if (duplicate && furthest + span + entry.object->bounds_min.z < horizon) {
            furthest += span;
            set(entry.transform.position.z, furthest);
        }
        float near_edge = entry.object->bounds_min.z + entry.transform.position.z;
        if (!(entry.list_flags & BOD_FLAG_RENDER_ENABLED) && near_edge <= horizon)
            set(entry.list_flags, entry.list_flags | BOD_FLAG_RENDER_ENABLED);
    }
}

}  // namespace

float draw_distance_extra()
{
    return g_extra;
}

void draw_distance_begin_frame()
{
    g_undo_count = 0;
    g_extra = 0;
    if (g_port_draw_distance <= 1.0f)
        return;
    cRSubGame* game = &g_game->subgame;
    if (g_game->players[0].frontend_state != kGameplayFrontendState || game->subgame_state < 2
        || game->subgame_state > 4)
        return;
    g_extra = kOriginalFarZ * (g_port_draw_distance - 1.0f);
    cRSubGoldy* player = game->embedded_player();
    preview_cache_rows(game, player->transform.position.z + 46.0f + g_extra);
    preview_scan_rows(game, (int)player->active_window_min_z + 46 + (int)g_extra);
    preview_landscape(game, player->transform.position.z + g_game->fog_end + g_extra);
}

void draw_distance_end_frame()
{
    while (g_undo_count > 0) {
        Saved& slot = g_undo[--g_undo_count];
        memcpy(slot.at, slot.bytes, slot.size);
    }
}

void draw_distance_projection(const float* projection, float* out)
{
    memcpy(out, projection, 16 * sizeof(float));
    if (g_extra <= 0 || projection[11] != -1.0f || projection[15] != 0.0f || projection[10] == -1.0f)
        return;
    // build_perspective_projection_matrix: m10 = f / (n - f), m14 = m10 * n.
    float near_z = projection[14] / projection[10];
    float far_z = projection[10] * near_z / (1.0f + projection[10]) + g_extra;
    out[10] = far_z / (near_z - far_z);
    out[14] = out[10] * near_z;
}
