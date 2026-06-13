// spawn_salt_hazard @ 0x441560 (thiscall, ret 0x4)

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
    void set_matrix_rotation_identity();     // @ 0x44d250, thiscall, matched
    void rotate_matrix_world_y(float angle); // thiscall

    Vector4 basis_right;
    Vector4 basis_up;
    Vector4 basis_forward;
    Vector4 position;
};

struct SaltHazardSlot {
    int unknown_00;
    unsigned int list_flags;    // +0x04, 0x200 = linked
    SaltHazardSlot* list_prev;  // +0x08
    SaltHazardSlot* list_next;  // +0x0c
    char unknown_10[0x38 - 0x10];
    TransformMatrix live_matrix; // +0x38, position row at +0x68
    char unknown_78[0x80 - 0x78];
    int state;                  // +0x80, 0 free / 1 live
    char unknown_84[0x8c - 0x84];
    float velocity_x;           // +0x8c, zeroed at spawn
    float velocity_y;           // +0x90, game rate / 30
    float velocity_z;           // +0x94 low byte poked to 1 at spawn
};

struct Game {
    char unknown_00[0x74650];
    float salt_speed_base;      // +0x74650
    char unknown_74654[0x3ca224 - 0x74654];
    SaltHazardSlot salt_list_head; // +0x3ca224, node-shaped anchor
};

extern Game* volatile g_game; // data_4df904
int next_math_random_value();
int report_errorf(char* format, ...);

class SaltHazardPool {
public:
    int spawn_salt_hazard(const Vector3* position);

    SaltHazardSlot slots[40];
};

int SaltHazardPool::spawn_salt_hazard(const Vector3* position)
{
    int index = 0;
    int* state = &slots[0].state;
    do {
        if (!*state)
            goto found;
        ++index;
        state += 38;
    } while (index < 40);
    return index;

found:
    SaltHazardSlot* slot = &slots[index];
    slot->state = 1;
    slot->velocity_x = 0.0f;
    slot->velocity_y = g_game->salt_speed_base * 0.033333335f;
    Vector3* spawn_position = (Vector3*)&slot->live_matrix.position;
    *spawn_position = *position;
    slot->live_matrix.set_matrix_rotation_identity();
    float angle = ((float)next_math_random_value() - 16384.0f) * 0.0001917476f;
    slot->live_matrix.rotate_matrix_world_y(angle);
    *(unsigned char*)&slot->velocity_z = 1;
    SaltHazardSlot* head = &g_game->salt_list_head;
    if ((slot->list_flags & 0x200) != 0)
        return report_errorf("List ADDafter");
    slot->list_prev = head;
    slot->list_next = head->list_next;
    head->list_next = slot;
    if (slot->list_next)
        slot->list_next->list_prev = slot;
    return slot->list_flags |= 0x200;
}
