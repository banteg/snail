// build_track_fringe_objects @ 0x434be0 (thiscall, ret)
// Structure-first scratch for directional runtime fringe object emission.

#include "track_attachment_types.h"

extern char* g_game_base; // data_4df904
extern unsigned char g_track_render_flags; // byte_4df934

#define FRINGE_BOD(base, family, edge_a, edge_b) \
    (*(void**)(g_game_base + (base) + (((((family) * 12) + (edge_a)) * 3 + (edge_b)) * 0x38)))

struct Vec3Bits {
    int x;
    int y;
    int z;
};

struct ColorBits {
    int r;
    int g;
    int b;
    int a;
};

class FringeObject {
public:
    int set_bod_object(void* object);

    void* vtable; // +0x00
    unsigned int flags; // +0x04
    char unknown_08[0x10 - 0x08];
    Vector3 position; // +0x10
    char unknown_1c[0x28 - 0x1c];
    ColorBits color; // +0x28
};

class FringeManager {
public:
    void initialize_fringe_manager();
    FringeObject* allocate_fringe_object();
};

class Game {
public:
    int build_track_fringe_objects();
    bool is_neighbor_cell_solid(TrackRowCell* cell, int dx, int dz);
    int* get_track_skirt_color(int* scratch);

    char unknown_00[0x54];
    int runtime_row_count; // +0x54
};

int debug_report_stub(char* format, ...); // sub_449c00
extern char g_used_fringe_bods_format[]; // "Used %i fringe bods\n"

int Game::build_track_fringe_objects()
{
    Game* game = this;
    Game* original_game = game;
    ((FringeManager*)(g_game_base + 0x3d01d4))->initialize_fringe_manager();

    int edge_a = 0;
    int row = 0;
    if (game->runtime_row_count > 0) {
        unsigned char* row_flags = (unsigned char*)((char*)game + 0x5ccac8);
        TrackRowCell* cell = (TrackRowCell*)((char*)game + 0x3bfac8);
        unsigned char* row_flags_head = row_flags;

        do {
            int lane_count = 8;
            do {
                unsigned char edge_id = cell->tile_flags_3d;
                int family = 0;
                if (edge_id == 9) {
                    family = 1;
                } else if (edge_id == 5) {
                    family = 3;
                } else if (edge_id == 10) {
                    family = 2;
                } else if (edge_id == 6) {
                    family = 4;
                }

                unsigned char tile_id = cell->tile_id;
                if (tile_id == 2 || tile_id == 8 || tile_id == 5)
                    family = 5;
                if (tile_id == 3 || tile_id == 9 || tile_id == 11
                    || tile_id == 12 || tile_id == 13 || tile_id == 6)
                    family = 6;
                if (tile_id == 4 || tile_id == 10 || tile_id == 7)
                    family = 7;

                if ((*row_flags & 4) != 0 || edge_id == 0 || tile_id == 0x20
                    || (g_track_render_flags & 0x20) == 0) {
                    cell->fringe_front = 0;
                    cell->fringe_right = 0;
                    cell->fringe_left = 0;
                    cell->fringe_back = 0;
                } else if (game->is_neighbor_cell_solid(cell, 0, 0)) {
                    if (game->is_neighbor_cell_solid(cell, 0, 1)) {
                        cell->fringe_front = 0;
                    } else {
                        if (!game->is_neighbor_cell_solid(cell, 1, 1))
                            edge_a = !game->is_neighbor_cell_solid(cell, 1, 0) + 1;
                        int edge_b;
                        if (game->is_neighbor_cell_solid(cell, -1, 1))
                            edge_b = 0;
                        else
                            edge_b = !game->is_neighbor_cell_solid(cell, -1, 0) + 1;

                        FringeObject* object =
                            ((FringeManager*)(g_game_base + 0x3d01d4))->allocate_fringe_object();
                        cell->fringe_front = object;
                        object->set_bod_object(FRINGE_BOD(0x44dd4, family, edge_a, edge_b));
                        cell->fringe_front->flags |= 0x20;
                        cell->fringe_front->position = cell->anchor_position;
                        int color0[4];
                        int* color = game->get_track_skirt_color(color0);
                        game = original_game;
                        edge_a = 0;
                        cell->fringe_front->color.r = color[0];
                        cell->fringe_front->color.g = color[1];
                        cell->fringe_front->color.b = color[2];
                        cell->fringe_front->color.a = color[3];
                    }

                    if (game->is_neighbor_cell_solid(cell, 1, 0)) {
                        cell->fringe_right = 0;
                    } else {
                        if (!game->is_neighbor_cell_solid(cell, 1, -1))
                            edge_a = !game->is_neighbor_cell_solid(cell, 0, -1) + 1;
                        int edge_b;
                        if (game->is_neighbor_cell_solid(cell, 1, 1))
                            edge_b = 0;
                        else
                            edge_b = !game->is_neighbor_cell_solid(cell, 0, 1) + 1;

                        FringeObject* object =
                            ((FringeManager*)(g_game_base + 0x3d01d4))->allocate_fringe_object();
                        cell->fringe_right = object;
                        object->set_bod_object(FRINGE_BOD(0x44fcc, family, edge_a, edge_b));
                        cell->fringe_right->flags |= 0x20;
                        cell->fringe_right->position = cell->anchor_position;
                        int color1[4];
                        int* color = game->get_track_skirt_color(color1);
                        game = original_game;
                        edge_a = 0;
                        cell->fringe_right->color.r = color[0];
                        cell->fringe_right->color.g = color[1];
                        cell->fringe_right->color.b = color[2];
                        cell->fringe_right->color.a = color[3];
                    }

                    if (game->is_neighbor_cell_solid(cell, -1, 0)) {
                        cell->fringe_left = 0;
                    } else {
                        if (!game->is_neighbor_cell_solid(cell, -1, 1))
                            edge_a = !game->is_neighbor_cell_solid(cell, 0, 1) + 1;
                        int edge_b;
                        if (game->is_neighbor_cell_solid(cell, -1, -1))
                            edge_b = 0;
                        else
                            edge_b = !game->is_neighbor_cell_solid(cell, 0, -1) + 1;

                        FringeObject* object =
                            ((FringeManager*)(g_game_base + 0x3d01d4))->allocate_fringe_object();
                        cell->fringe_left = object;
                        object->set_bod_object(FRINGE_BOD(0x451c4, family, edge_a, edge_b));
                        cell->fringe_left->flags |= 0x20;
                        cell->fringe_left->position = cell->anchor_position;
                        int color2[4];
                        int* color = game->get_track_skirt_color(color2);
                        game = original_game;
                        edge_a = 0;
                        cell->fringe_left->color.r = color[0];
                        cell->fringe_left->color.g = color[1];
                        cell->fringe_left->color.b = color[2];
                        cell->fringe_left->color.a = color[3];
                    }

                    if (game->is_neighbor_cell_solid(cell, 0, -1)) {
                        cell->fringe_back = 0;
                    } else {
                        if (!game->is_neighbor_cell_solid(cell, -1, -1))
                            edge_a = !game->is_neighbor_cell_solid(cell, -1, 0) + 1;
                        int edge_b;
                        if (game->is_neighbor_cell_solid(cell, 1, -1))
                            edge_b = 0;
                        else
                            edge_b = !game->is_neighbor_cell_solid(cell, 1, 0) + 1;

                        FringeObject* object =
                            ((FringeManager*)(g_game_base + 0x3d01d4))->allocate_fringe_object();
                        cell->fringe_back = object;
                        object->set_bod_object(FRINGE_BOD(0x453bc, family, edge_a, edge_b));
                        cell->fringe_back->flags |= 0x20;
                        cell->fringe_back->position = cell->anchor_position;
                        int color3[4];
                        int* color = game->get_track_skirt_color(color3);
                        game = original_game;
                        edge_a = 0;
                        cell->fringe_back->color.r = color[0];
                        cell->fringe_back->color.g = color[1];
                        cell->fringe_back->color.b = color[2];
                        cell->fringe_back->color.a = color[3];
                    }
                }

                row_flags = row_flags_head;
                if ((*row_flags_head & 4) != 0) {
                    FringeObject* object = cell->fringe_front;
                    if (object != 0)
                        object->flags &= ~0x20;
                    object = cell->fringe_back;
                    if (object != 0)
                        object->flags &= ~0x20;
                    object = cell->fringe_right;
                    if (object != 0)
                        object->flags &= ~0x20;
                    object = cell->fringe_left;
                    if (object != 0)
                        object->flags &= ~0x20;
                }

                ++cell;
                --lane_count;
            } while (lane_count);

            row_flags = row_flags_head + 0xf4;
            ++row;
            row_flags_head = row_flags;
        } while (row < game->runtime_row_count);
    }

    return debug_report_stub(g_used_fringe_bods_format, *(int*)(g_game_base + 0x42fd14));
}
