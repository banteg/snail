// spawn_sub_lazer_projectile @ 0x441670 (thiscall, ret 0x8)

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Vector4 {
    float x;
    float y;
    float z;
    float w;
};

struct TransformMatrix {
    void set_matrix_z_direction(const Vector3* direction);

    Vector4 basis_right;
    Vector4 basis_up;
    Vector4 basis_forward;
    Vector4 position;
};

struct Game {
    char unknown_00[0x38];
    float track_center_x;
    char unknown_3c[0x355bd4 - 0x3c];
    char sub_lazer_list_head[0x10];
};

void __fastcall set_matrix_identity(TransformMatrix* transform);
int report_errorf(char* format, ...);

class SubLazerSlot {
public:
    void spawn_sub_lazer_projectile(const Vector3* origin, const Vector3* direction);

    int unknown_00;
    unsigned int list_flags;
    SubLazerSlot* list_prev;
    SubLazerSlot* list_next;
    char unknown_10[0x38 - 0x10];
    TransformMatrix live_matrix;
    char unknown_78[0x80 - 0x78];
    int state;
    char unknown_84[0x88 - 0x84];
    Game* owner_game;
    Vector3 velocity;
    float sprite_bob_phase;
    float sprite_bob_phase_step;
};

void SubLazerSlot::spawn_sub_lazer_projectile(const Vector3* origin, const Vector3* direction)
{
    state = 1;
    set_matrix_identity(&live_matrix);
    Vector3* position = (Vector3*)&live_matrix.position;
    Vector3* velocity_copy = &velocity;
    *position = *origin;
    *velocity_copy = *direction;
    sprite_bob_phase = 0.0f;
    sprite_bob_phase_step = owner_game->track_center_x * 0.0055555557f;

    SubLazerSlot* head = (SubLazerSlot*)owner_game->sub_lazer_list_head;
    if ((list_flags & 0x200) != 0) {
        report_errorf("List ADDafter");
    } else {
        list_prev = head;
        list_next = head->list_next;
        head->list_next = this;
        if (list_next != 0) {
            list_next->list_prev = this;
        }
        list_flags |= 0x200;
    }

    live_matrix.set_matrix_z_direction(&velocity);
}
