// build_track_fringe_objects @ 0x434be0 (thiscall, void)
// Structure-first scratch for directional runtime fringe object emission.

#include "track_attachment_types.h"
#include "fringe_object.h"
#include "game_root.h"
#include "runtime_config.h"
#include "subgame_runtime.h"
#include "track_fringe_bod_catalog.h"


#define FRINGE_BOD(direction, family, edge_a, edge_b) \
    (g_game->root_bod_catalog.fringe_catalog \
            .entries[family][direction][edge_a][edge_b].object)

int debug_report_stub(char* format, ...);
extern char g_used_fringe_bods_format[]; // "Used %i fringe bods\n"

void cRSubGame::FringeEdgeTrack()
{
    g_game->subgame.fringe_manager.Init();

    int edge_a = 0;
    int row = 0;
    if (runtime_row_count > 0) {

        do {
            int lane = 0;
            do {
                unsigned char open_edge_mask = runtime_cells[row][lane].open_edge_mask;
                int family = 0;
                if (open_edge_mask
                    == (SUBLOC_OPEN_PREVIOUS_LANE | SUBLOC_OPEN_PREVIOUS_ROW)) {
                    family = 1;
                } else if (open_edge_mask
                    == (SUBLOC_OPEN_NEXT_LANE | SUBLOC_OPEN_PREVIOUS_ROW)) {
                    family = 3;
                } else if (open_edge_mask
                    == (SUBLOC_OPEN_PREVIOUS_LANE | SUBLOC_OPEN_NEXT_ROW)) {
                    family = 2;
                } else if (open_edge_mask
                    == (SUBLOC_OPEN_NEXT_LANE | SUBLOC_OPEN_NEXT_ROW)) {
                    family = 4;
                }

                unsigned char tile_id = runtime_cells[row][lane].tile_id;
                if (tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE
                    || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED
                    || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACKET)
                    family = 5;
                if (tile_id == SUBLOC_TILE_RAMP_GREATER
                    || tile_id == SUBLOC_TILE_RAMP_GREATER_RAISED
                    || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH
                    || tile_id == SUBLOC_TILE_RAMP_GREATER_BACKPATCH
                    || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH
                    || tile_id == SUBLOC_TILE_RAMP_LESS)
                    family = 6;
                if (tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE
                    || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED
                    || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACKET)
                    family = 7;

                if ((runtime_rows[row].flags & SUBROW_FLAG_SUPPRESS_TRACK_RENDER) != 0
                    || open_edge_mask == 0
                    || tile_id == SUBLOC_TILE_FLOOR_HASH_MARKER
                    || (g_runtime_config.render_flags & RUNTIME_RENDER_TRACK_FRINGE) == 0) {
                    runtime_cells[row][lane].fringe_front = 0;
                    runtime_cells[row][lane].fringe_right = 0;
                    runtime_cells[row][lane].fringe_left = 0;
                    runtime_cells[row][lane].fringe_back = 0;
                } else if (TestLoc(&runtime_cells[row][lane], 0, 0) == 1) {
                    if (!TestLoc(&runtime_cells[row][lane], 0, 1)) {
                        if (TestLoc(&runtime_cells[row][lane], 1, 1) != 1)
                            edge_a = (TestLoc(&runtime_cells[row][lane], 1, 0) != 1) + 1;
                        int edge_b;
                        if (TestLoc(&runtime_cells[row][lane], -1, 1) == 1)
                            edge_b = 0;
                        else
                            edge_b = (TestLoc(&runtime_cells[row][lane], -1, 0) != 1) + 1;

                        // The cell slot is a transient borrowed handle. The
                        // render-cache pass consumes and clears it after this
                        // builder completes.
                        Fringe* front_fringe =
                            g_game->subgame.fringe_manager.GetFringe();
                        runtime_cells[row][lane].fringe_front = front_fringe;
                        front_fringe->SetObject(
                            FRINGE_BOD(TRACK_FRINGE_FRONT, family, edge_a, edge_b));
                        runtime_cells[row][lane].fringe_front->list_flags |= BOD_FLAG_RENDER_ENABLED;
                        runtime_cells[row][lane].fringe_front->position = runtime_cells[row][lane].position;
                        tColour color0;
                        tColour* skirt_color = g_game->subgame.GetSkirtColour(&color0);
                        runtime_cells[row][lane].fringe_front->color = *skirt_color;
                        edge_a = 0;
                    } else {
                        runtime_cells[row][lane].fringe_front = 0;
                    }

                    if (!TestLoc(&runtime_cells[row][lane], 1, 0)) {
                        if (TestLoc(&runtime_cells[row][lane], 1, -1) != 1)
                            edge_a = (TestLoc(&runtime_cells[row][lane], 0, -1) != 1) + 1;
                        int edge_b;
                        if (TestLoc(&runtime_cells[row][lane], 1, 1) == 1)
                            edge_b = 0;
                        else
                            edge_b = (TestLoc(&runtime_cells[row][lane], 0, 1) != 1) + 1;

                        Fringe* right_fringe =
                            g_game->subgame.fringe_manager.GetFringe();
                        runtime_cells[row][lane].fringe_right = right_fringe;
                        right_fringe->SetObject(
                            FRINGE_BOD(TRACK_FRINGE_RIGHT, family, edge_a, edge_b));
                        runtime_cells[row][lane].fringe_right->list_flags |= BOD_FLAG_RENDER_ENABLED;
                        runtime_cells[row][lane].fringe_right->position = runtime_cells[row][lane].position;
                        tColour color1;
                        tColour* skirt_color = g_game->subgame.GetSkirtColour(&color1);
                        runtime_cells[row][lane].fringe_right->color = *skirt_color;
                        edge_a = 0;
                    } else {
                        runtime_cells[row][lane].fringe_right = 0;
                    }

                    if (!TestLoc(&runtime_cells[row][lane], -1, 0)) {
                        if (TestLoc(&runtime_cells[row][lane], -1, 1) != 1)
                            edge_a = (TestLoc(&runtime_cells[row][lane], 0, 1) != 1) + 1;
                        int edge_b;
                        if (TestLoc(&runtime_cells[row][lane], -1, -1) == 1)
                            edge_b = 0;
                        else
                            edge_b = (TestLoc(&runtime_cells[row][lane], 0, -1) != 1) + 1;

                        Fringe* left_fringe =
                            g_game->subgame.fringe_manager.GetFringe();
                        runtime_cells[row][lane].fringe_left = left_fringe;
                        left_fringe->SetObject(
                            FRINGE_BOD(TRACK_FRINGE_LEFT, family, edge_a, edge_b));
                        runtime_cells[row][lane].fringe_left->list_flags |= BOD_FLAG_RENDER_ENABLED;
                        runtime_cells[row][lane].fringe_left->position = runtime_cells[row][lane].position;
                        tColour color2;
                        tColour* skirt_color = g_game->subgame.GetSkirtColour(&color2);
                        runtime_cells[row][lane].fringe_left->color = *skirt_color;
                        edge_a = 0;
                    } else {
                        runtime_cells[row][lane].fringe_left = 0;
                    }

                    if (!TestLoc(&runtime_cells[row][lane], 0, -1)) {
                        if (TestLoc(&runtime_cells[row][lane], -1, -1) != 1)
                            edge_a = (TestLoc(&runtime_cells[row][lane], -1, 0) != 1) + 1;
                        int edge_b;
                        if (TestLoc(&runtime_cells[row][lane], 1, -1) == 1)
                            edge_b = 0;
                        else
                            edge_b = (TestLoc(&runtime_cells[row][lane], 1, 0) != 1) + 1;

                        Fringe* back_fringe =
                            g_game->subgame.fringe_manager.GetFringe();
                        runtime_cells[row][lane].fringe_back = back_fringe;
                        back_fringe->SetObject(
                            FRINGE_BOD(TRACK_FRINGE_BACK, family, edge_a, edge_b));
                        runtime_cells[row][lane].fringe_back->list_flags |= BOD_FLAG_RENDER_ENABLED;
                        runtime_cells[row][lane].fringe_back->position = runtime_cells[row][lane].position;
                        tColour color3;
                        tColour* skirt_color = g_game->subgame.GetSkirtColour(&color3);
                        runtime_cells[row][lane].fringe_back->color = *skirt_color;
                        edge_a = 0;
                    } else {
                        runtime_cells[row][lane].fringe_back = 0;
                    }
                }

                if ((runtime_rows[row].flags
                        & SUBROW_FLAG_SUPPRESS_TRACK_RENDER)
                    != 0) {
                    Fringe* object = runtime_cells[row][lane].fringe_front;
                    if (object != 0)
                        object->list_flags &= ~BOD_FLAG_RENDER_ENABLED;
                    object = runtime_cells[row][lane].fringe_back;
                    if (object != 0)
                        object->list_flags &= ~BOD_FLAG_RENDER_ENABLED;
                    object = runtime_cells[row][lane].fringe_right;
                    if (object != 0)
                        object->list_flags &= ~BOD_FLAG_RENDER_ENABLED;
                    object = runtime_cells[row][lane].fringe_left;
                    if (object != 0)
                        object->list_flags &= ~BOD_FLAG_RENDER_ENABLED;
                }

                ++lane;
            } while (lane < SUBGAME_TRACK_LANE_COUNT);

            ++row;
        } while (row < runtime_row_count);
    }

    debug_report_stub(
        g_used_fringe_bods_format,
        g_game->subgame.fringe_manager.count);
}
