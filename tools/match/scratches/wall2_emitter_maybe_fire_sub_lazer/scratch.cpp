// wall2_emitter_maybe_fire_sub_lazer @ 0x439d50 (thiscall, ret)
// Fringe-object update: wall2 (tile 14) fires at the player through the
// 4% gate once the active row start passes the player z; tiles 22/29/30
// and the default lane cull or sync the attachment skirt color.

struct Vector3 {
    float x;
    float y;
    float z;
};

float random_float_below(float maximum, const char* tag);
float random_signed_float_below(float maximum, const char* tag);
float normalize_vector(float* vector);
void set_color_alpha(int* color, int alpha_bits);
int* get_track_skirt_color(int* skirt_owner, float* scratch);

struct FringeOwnerRecord {
    char unknown_00[0x38];
    int kind;        // +0x38, 24 = WORM
    char unknown_3c[0x48 - 0x3c];
    int row_count;   // +0x48
};

struct SubLazerPoolApi {
    void shoot_subgoldy(const float* origin, const Vector3* direction); // pinned
};

struct PlayerBlock {
    char unknown_00[0x68];
    Vector3 position; // +0x68
};

struct Game {
    char unknown_00[0x74621];
    unsigned char suspended;     // +0x74621
    char unknown_74622[0x74650 - 0x74622];
    float subgame_rate;          // +0x74650
    char unknown_74654[0x74668 - 0x74654];
    int active_row_start;        // +0x74668
    char unknown_7466c[0x74670 - 0x7466c];
    int active_row_end;          // +0x74670
    char unknown_74674[0x74698 - 0x74674];
    int skirt_color_owner;       // +0x74698
    char unknown_7469c[0x3cb118 - 0x7469c];
    SubLazerPoolApi sub_lazer_pool; // +0x3cb118
    char unknown_3cb1c8[0x42fd7c - 0x3cb118 - 4];
    PlayerBlock player;          // +0x42fd7c
    char unknown_42fe58[0x4326fc - 0x42fd7c - sizeof(PlayerBlock)];
    float cull_plane_z;          // +0x4326fc
    char unknown_432700[0x6411b8 - 0x432700];
    int row_color_records[1];    // +0x6411b8, 244-byte stride per row
};

extern Game* g_game; // data_4df904 (this TU caches the base, reloading after calls)

struct FringeObject {
    void wall2_emitter_maybe_fire_sub_lazer();
    int get_row_index(); // get_track_cell_row_index, thiscall
    void destroy_sub_lazer_projectile();

    char unknown_00[0x10];
    Vector3 position;   // +0x10
    char unknown_1c[0x20 - 0x1c];
    float fade;         // +0x20
    char unknown_24[0x28 - 0x24];
    int color[4];       // +0x28
    FringeOwnerRecord* owner; // +0x38
    unsigned char tile; // +0x3c
    char unknown_3d[3];
    unsigned int flags; // +0x40, 0x2000 = live emitter, lane nibble at >>8
};

void FringeObject::wall2_emitter_maybe_fire_sub_lazer()
{
    if ((flags & 0x2000) == 0)
        return;
    if (g_game->suspended)
        return;
    switch (tile) {
    case 14: {
        if ((float)g_game->active_row_start >= g_game->player.position.z)
            goto cull_check;
        if (random_float_below(100.0f, "W") < 4.0f) {
            float spawn[3];
            float spawn_y = position.y + 8.0f;
            float spawn_z = position.z;
            spawn[0] = position.x;
            int lane = (int)((flags >> 8) & 0xF);
            spawn[1] = spawn_y;
            spawn[2] = spawn_z;
            spawn[0] = (float)lane * 0.5f + spawn[0];
            float jitter = random_signed_float_below(3.0f, "Wall2");
            float target_y = g_game->player.position.y;
            float target_z = jitter + 8.0f + g_game->player.position.z;
            float direction[3];
            direction[0] = g_game->player.position.x - spawn[0];
            direction[1] = target_y - spawn_y;
            float dz = target_z - spawn_z;
            direction[2] = dz;
            if (dz >= -4.0f)
                goto cull_check;
            normalize_vector(direction);
            direction[0] *= 0.40000001f;
            direction[1] *= 0.40000001f;
            direction[2] *= 0.40000001f;
            g_game->sub_lazer_pool.shoot_subgoldy(spawn, (const Vector3*)direction);
        }
cull_check:
        if (position.z < g_game->cull_plane_z)
            destroy_sub_lazer_projectile();
        return;
    }
    case 22:
        if (position.z >= g_game->cull_plane_z)
            return;
        goto destroy;
    case 29:
    case 30: {
        if (owner->kind == 24) {
            fade = fade - g_game->subgame_rate * 0.033333335f;
            set_color_alpha(color, 1061997773);
        }
        float scratch[4];
        int* skirt = get_track_skirt_color(&g_game->skirt_color_owner, scratch);
        int* record = (int*)((char*)g_game->row_color_records + 244 * get_row_index());
        record[0] = skirt[0];
        record[1] = skirt[1];
        record[2] = skirt[2];
        record[3] = skirt[3];
        if (g_game->cull_plane_z - ((float)owner->row_count + 5.0f) > position.z)
            destroy_sub_lazer_projectile();
        break;
    }
    default:
        if (position.z < g_game->cull_plane_z
            && (float)(g_game->active_row_end - 5) > position.z) {
destroy:
            destroy_sub_lazer_projectile();
        }
        break;
    }
}
