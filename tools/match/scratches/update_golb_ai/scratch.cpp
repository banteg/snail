// update_golb_ai @ 0x414820 (thiscall, ret) — one live Golb shot per tick.
// Straight or path-follow flight, homing blend (kind 2), per-kind trail
// effects, garbage/slug contact sweeps, wall-14 impact, lifetime cleanup.

struct Vec3 {
    float x;
    float y;
    float z;
};

float __fastcall normalize_vector(Vec3* vector);
void add_subgoldy_score(int* player, int event_id, int value);
void hit_slug_hazard(int slug, int mode);
void* qmemcpy(void* dest, const void* src, unsigned int size);
char* get_track_grid_cell_at_world_position(char* game, Vec3* position);
void set_matrix_z_direction(float* matrix, float direction_z, Vec3* direction);
void rotate_matrix_world_z(float* matrix, float angle);
void add_vapour_point(void* vapour, const void* matrix);

struct Game {
    char unknown_00[0x9];
    unsigned char paused; // +0x09
    char unknown_0a[0x38 - 0x0a];
    float subgame_rate; // +0x38
    char unknown_3c[0x359140 - 0x3c];
    int garbage_list_head; // +0x359140
};

struct Player {
    char unknown_00[0x70];
    float live_position_z; // +0x70
    char unknown_74[0x2980 - 0x74];
    float golb_band_min_z; // +0x2980
};

struct PathFollow {
    unsigned char active; // +0x00
    char unknown_01[0x18 - 0x01];
    Vec3 output_position; // +0x18 (this+724)
    char unknown_24[0x28 - 0x24];

    int calc_path_length_z(float path_factor, Vec3* position, Vec3* velocity);
    void initialize_path_follow_golb(int cell, void* position, void* shot);
};

struct TrackRowCell {
    char unknown_00[0x3c];
    unsigned char tile_id; // +0x3c
};

struct GolbShot {
    void update_golb_ai();
    void kill_golb();
    void spawn_golb_impact_sprite(Vec3* position);
    void spawn_golb_smoke(Vec3* position);
    void spawn_golb_trail_sprite(Vec3* position);

    char unknown_000[0x80];
    char vapour[0x150 - 0x80];       // +0x80 vapour trail object
    float live_matrix[16];           // +0x150 (this+336)
    char unknown_190[0x198 - 0x190];
    int homing_target_active;        // +0x198 (this+408)
    Vec3 homing_target;              // +0x19c (this+412)
    char unknown_1a8[4];
    float homing_blend;              // +0x1ac (this+428)
    float homing_blend_step;         // +0x1b0 (this+432)
    float spin;                      // +0x1b4 (this+436)
    float spin_step;                 // +0x1b8 (this+440)
    unsigned char skip_one_tick;     // +0x1bc (this+444)
    unsigned char slug_bounce_armed; // +0x1bd (this+445)
    char unknown_1be[2];
    int kind;                        // +0x1c0 (this+448): 0 golb, 1 lazer, 2 rocket
    char unknown_1c4[0x1f4 - 0x1c4];
    Vec3 position;                   // +0x1f4 (this+500)
    char unknown_200[0x234 - 0x200];
    Vec3 previous_output;            // +0x234 (this+564)
    char unknown_240[0x244 - 0x240];
    int state;                       // +0x244 (this+580)
    void* owner_body;                // +0x248 (this+584)
    Vec3 velocity;                   // +0x24c (this+588)
    Vec3 direction;                  // +0x258 (this+600)
    float path_factor;               // +0x264 (this+612)
    float lifetime;                  // +0x268 (this+616)
    float lifetime_step;             // +0x26c (this+620)
    Game* game;                      // +0x270 (this+624)
    char unknown_274[4];
    Player* player;                  // +0x278 (this+632)
    // the source transform at +636 spans 0x40 bytes whose POSITION ROW is
    // the live output position at +684 — one TransformMatrix, two views
    float source_basis[12];          // +0x27c (this+636), rotation rows
    Vec3 output_position;            // +0x2ac (this+684), the matrix position row
    float source_matrix_pad;         // +0x2b8
    PathFollow path_follow;          // +0x2bc (this+700)
    float path_entry_z_latch;        // +0x2e4 (this+740)
};

void GolbShot::update_golb_ai()
{
    float speed;
    float deflect_speed;
    float lived;
    float direction_x;
    float direction_y;
    float direction_z;
    Vec3* new_output;
    Vec3* new_direction;
    Vec3 probe;
    Vec3 delta;
    Vec3 smoke_position;
    Vec3 trail_a;
    Vec3 trail_b;
    Vec3 wall_impact;

    if (game->paused)
        return;
    if (skip_one_tick == 1) {
        skip_one_tick = 0;
        return;
    }
    switch (state) {
    case 1:
        break;
    default:
        return;
    }

    if (path_follow.active == 1) {
        switch (path_follow.calc_path_length_z(path_factor, &position, &velocity)) {
        case 1:
        case 3:
            output_position = position;
            break;
        case 0:
        case 2:
            output_position = path_follow.output_position;
            break;
        default:
            break;
        }
    } else {
        Vec3* movement = &velocity;
        Vec3* current_position = &position;
        current_position->x = movement->x + current_position->x;
        current_position->y = movement->y + current_position->y;
        current_position->z = movement->z + current_position->z;
        if (kind == 0) {
            if (position.y > 0.49000001f || position.y < 0.0f) {
                velocity.y = velocity.y - game->subgame_rate * 0.017000001f;
            } else {
                velocity.y = 0.0f;
            }
        } else if (kind == 2 && homing_target_active) {
            float blend = homing_blend_step + homing_blend;
            homing_blend = blend;
            if (blend > 1.0f)
                homing_blend = 1.0f;
            speed = normalize_vector(&velocity);
            delta.x = homing_target.x - position.x;
            delta.y = homing_target.y - position.y;
            delta.z = homing_target.z - position.z;
            if (normalize_vector(&delta) < 0.40000001f) {
                spawn_golb_impact_sprite(&position);
                goto retire;
            }
            float pull = homing_blend;
            float pull_x = delta.x * pull;
            float pull_y = delta.y * pull;
            float pull_z = delta.z * pull;
            float keep = 1.0f - homing_blend * 1.5f;
            float keep_x = keep * velocity.x;
            float keep_y = keep * velocity.y;
            float keep_z = keep * velocity.z;
            velocity.x = keep_x + pull_x;
            velocity.y = keep_y + pull_y;
            velocity.z = keep_z + pull_z;
            normalize_vector(&velocity);
            velocity.x = speed * velocity.x;
            velocity.y = speed * velocity.y;
            velocity.z = speed * velocity.z;
            if (speed < 0.1f)
                goto retire;
        }
        output_position.x = position.x;
        output_position.y = position.y;
        output_position.z = position.z;
        if (path_entry_z_latch < output_position.z && position.y < 1.0f && position.y > 0.0f) {
            TrackRowCell* cell = (TrackRowCell*)get_track_grid_cell_at_world_position((char*)game, &output_position);
            if (cell->tile_id == 30) {
                path_entry_z_latch = output_position.z;
                path_follow.initialize_path_follow_golb((int)cell, &position, this);
            }
            if (velocity.z > 1.0f && ((TrackRowCell*)((char*)cell - 672))->tile_id == 30) {
                path_entry_z_latch = output_position.z + 1.0f;
                path_follow.initialize_path_follow_golb((int)((char*)cell - 672), &position, this);
            }
        }
    }

    if (kind) {
        if (kind == 1) {
            add_vapour_point(vapour + (0x80 - 0x80), source_basis);
        } else if (kind == 2) {
            float spun = spin_step + spin;
            spin = spun;
            qmemcpy(live_matrix, source_basis, 0x40);
            if (spun > 6.2831855f)
                spin = spun - 6.2831855f;
            spawn_golb_smoke(&output_position);
            float half_x = direction.x * 0.5f;
            float half_y = direction.y * 0.5f;
            float half_z = direction.z * 0.5f;
            smoke_position.x = output_position.x - half_x;
            smoke_position.y = output_position.y - half_y;
            smoke_position.z = output_position.z - half_z;
            spawn_golb_smoke(&smoke_position);
        }
    } else {
        float* body_position = (float*)((char*)owner_body + 72);
        body_position[0] = output_position.x;
        body_position[1] = output_position.y;
        body_position[2] = output_position.z;
        spawn_golb_trail_sprite(&output_position);
        float third_x = direction.x * 0.30000001f;
        float third_y = direction.y * 0.30000001f;
        float third_z = direction.z * 0.30000001f;
        trail_a.x = output_position.x - third_x;
        trail_a.y = output_position.y - third_y;
        trail_a.z = output_position.z - third_z;
        spawn_golb_trail_sprite(&trail_a);
        float deep_x = direction.x * 0.60000002f;
        float deep_y = direction.y * 0.60000002f;
        float deep_z = direction.z * 0.60000002f;
        trail_b.x = output_position.x - deep_x;
        trail_b.y = output_position.y - deep_y;
        trail_b.z = output_position.z - deep_z;
        spawn_golb_trail_sprite(&trail_b);
    }

    new_output = &output_position;
    new_direction = &direction;
    direction_x = new_output->x - previous_output.x;
    direction_y = new_output->y - previous_output.y;
    direction_z = new_output->z - previous_output.z;
    new_direction->x = direction_x;
    new_direction->y = direction_y;
    new_direction->z = direction_z;
    if (kind == 2) {
        set_matrix_z_direction(live_matrix, direction.z, &direction);
        rotate_matrix_world_z(live_matrix, spin);
    }
    lived = lifetime_step + lifetime;
    lifetime = lived;
    previous_output.x = output_position.x;
    previous_output.y = output_position.y;
    previous_output.z = output_position.z;
    if (lived <= 1.0f) {
        Player* bounds_player = player;
        if (position.z >= bounds_player->golb_band_min_z
            && bounds_player->live_position_z + 46.0f >= position.z) {
            int garbage = game->garbage_list_head;
            if (garbage) {
                while (1) {
                    if (*(int*)(garbage + 132) == 1) {
                        probe.x = *(float*)(garbage + 104) - output_position.x;
                        probe.y = *(float*)(garbage + 108) - output_position.y;
                        probe.z = *(float*)(garbage + 112) - output_position.z;
                        float dz = probe.z;
                        if (dz < 0.0f)
                            dz = -dz;
                        if (dz < 3.0f && normalize_vector(&probe) < *(float*)(garbage + 156) + 0.49000001f) {
                            *(int*)(garbage + 132) = 2;
                            *(int*)(garbage + 136) = probe.x >= 0.0f ? 1 : 2;
                            add_subgoldy_score((int*)player, 0, 0);
                            if (kind != 1)
                                break;
                        }
                    }
                    garbage = *(int*)(garbage + 128);
                    if (!garbage)
                        goto slugs;
                }
                kill_golb();
                spawn_golb_impact_sprite(&output_position);
                if (kind == 2) {
                    for (int splash = game->garbage_list_head; splash; splash = *(int*)(splash + 128)) {
                        if (*(int*)(splash + 132) == 1) {
                            probe.x = *(float*)(splash + 104) - output_position.x;
                            probe.y = *(float*)(splash + 108) - output_position.y;
                            probe.z = *(float*)(splash + 112) - output_position.z;
                            if (normalize_vector(&probe) < 3.0f) {
                                *(int*)(splash + 132) = 2;
                                if (probe.x >= 0.0f)
                                    *(int*)(splash + 136) = 1;
                                else
                                    *(int*)(splash + 136) = 2;
                                add_subgoldy_score((int*)player, 0, 0);
                            }
                        }
                    }
                }
                return;
            }
slugs:
            int slug_index = 0;
            for (int m = 0; m < 1888; m += 236) {
                char* slot = (char*)game + m;
                int slug_state = *(int*)(slot + 0x356420);
                if (slug_state == 1 || slug_state == 4) {
                    probe.x = *(float*)(slot + 0x356408) - output_position.x;
                    probe.y = *(float*)(slot + 0x35640c) - output_position.y;
                    probe.z = *(float*)(slot + 0x356410) - output_position.z;
                    float dz = probe.z;
                    if (dz < 0.0f)
                        dz = -dz;
                    if (dz < 2.5f && normalize_vector(&probe) < 2.5f) {
                        path_follow.active = 0;
                        deflect_speed = normalize_vector(&velocity);
                        probe.y = 0.0f;
                        normalize_vector(&probe);
                        velocity.x = -(deflect_speed * probe.x);
                        float reflect_z = deflect_speed * probe.z;
                        velocity.y = 0.0f;
                        velocity.z = -reflect_z;
                        if (kind == 1) {
                            kill_golb();
                            spawn_golb_impact_sprite(&output_position);
                            hit_slug_hazard((int)((char*)game + 236 * slug_index + 0x3563a0), 2);
                            return;
                        }
                        if (kind == 2) {
                            kill_golb();
                            spawn_golb_impact_sprite(&output_position);
                            hit_slug_hazard((int)((char*)game + 236 * slug_index + 0x3563a0), 4);
                            return;
                        }
                        if (kind == 0) {
                            if (slug_bounce_armed) {
                                kill_golb();
                                spawn_golb_impact_sprite(&output_position);
                            } else {
                                slug_bounce_armed = 1;
                            }
                            return;
                        }
                    }
                }
                ++slug_index;
            }
            if (((TrackRowCell*)get_track_grid_cell_at_world_position((char*)game, &output_position))->tile_id != 14)
                return;
            wall_impact.x = output_position.x;
            wall_impact.y = output_position.y;
            wall_impact.z = output_position.z - 1.0f;
            spawn_golb_impact_sprite(&wall_impact);
        }
    }
retire:
    kill_golb();
}
