// update_cameraman @ 0x4461d0 (thiscall, ret) — cRCameraman::AI()
// Builds the desired follow-camera matrix from the player pose, attachment
// envelopes, lane lean, and exit rolls, then blends live toward it at
// subgame_rate * 0.3. No game-base reads: everything hangs off `this`.

struct Vector3 {
    float x;
    float y;
    float z;
};

struct TransformMatrix {
    float right[3];
    float pad0;
    float up[3];
    float pad1;
    float forward[3];
    float pad2;
    Vector3 position; // +0x30
    float pad3;

    TransformMatrix* initialize_matrix_from_values(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);
    void orthogonalize_matrix();
    void rotate_matrix_world_x(float angle);
    void rotate_matrix_world_z(float angle);
    void set_matrix_identity();
    void multiply_matrix_in_place(TransformMatrix* other);
    void linear_interpolate_matrix(TransformMatrix* from, TransformMatrix* to, float alpha);
};

struct TrackRowCell {
    char unknown_00[0x18];
    float anchor_position_z; // +0x18
};

struct PathTemplate {
    char unknown_00[0x38];
    int kind;             // +0x38
    char unknown_3c[0x4c - 0x3c];
    float segment_count_f; // +0x4c
};

struct Game {
    char unknown_00[0x38];
    float subgame_rate;        // +0x38
    char unknown_3c[0x50 - 0x3c];
    int first_block_row_count; // +0x50
};

struct Player {
    char unknown_00[0x68];
    Vector3 live_position; // +0x68, live-matrix position row
    char unknown_74[0x2dc - 0x74];
    float cutscene_pitch_cycle; // +0x2dc
    char unknown_2e0[0x354 - 0x2e0];
    float lane_lean_amplitude; // +0x354
    float lane_lean_progress;  // +0x358
    char unknown_35c[0x370 - 0x35c];
    float heading_roll; // +0x370
    char unknown_374[0x384 - 0x374];
    unsigned char follow_active; // +0x384 (embedded FollowState)
    char unknown_385[3];
    PathTemplate* follow_template; // +0x388
    TrackRowCell* follow_source_cell; // +0x38c
    char unknown_390[0x39c - 0x390];
    float follow_orientation_a; // +0x39c
    float follow_orientation_b; // +0x3a0
    char unknown_3a4[0x41d - 0x3a4];
    unsigned char attachment_exit_pending; // +0x41d
    char unknown_41e[0x42c - 0x41e];
    float post_follow_exit_roll; // +0x42c (player.h post_follow_value_b lane)
    char unknown_430[0x2964 - 0x430];
    Vector3 cached_camera_target_world; // +0x2964
};

struct CameramanState {
    void update_cameraman();

    TransformMatrix live_matrix;             // +0x00
    TransformMatrix desired_matrix;          // +0x40
    TransformMatrix previous_desired_matrix; // +0x80
    Player* player;                          // +0xc0
    Game* game;                              // +0xc4
    float fov_degrees;                       // +0xc8
    unsigned char unresolved_cc;             // +0xcc
    char unknown_cd[3];
    float attachment_lift_envelope;          // +0xd0
    float smoothed_attachment_lift_envelope; // +0xd4
};

float cosine(float angle);
int debug_report_stub(char* format, ...); // @ 0x449c00, stripped in release
extern char g_worm_fov_report_format[];

void CameramanState::update_cameraman()
{
    TransformMatrix transform;
    Player* p = player;
    unresolved_cc = 0;
    desired_matrix = *transform.initialize_matrix_from_values(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.94600099f, 0.32416201f, 0.0f,
        0.0f, -0.32416201f, 0.94600099f, 0.0f,
        p->cached_camera_target_world.x * 0.40000001f, 1.8f, -0.5f, 1.0f);
    desired_matrix.orthogonalize_matrix();

    Player* ramp_player = player;
    float first_rows = (float)game->first_block_row_count;
    if (first_rows > ramp_player->cached_camera_target_world.z) {
        float ramp = ramp_player->cached_camera_target_world.z / first_rows * 1.4f - 0.40000001f;
        if (ramp < 0.0f)
            ramp = 0.0f;
        else if (ramp > 1.0f)
            ramp = 1.0f;
        float inverse_ramp = 1.0f - ramp;
        float lifted = (1.0f - ramp) * ramp_player->cached_camera_target_world.y * 1.15f
            + desired_matrix.position.y;
        desired_matrix.position.y = lifted;
        desired_matrix.position.y = ramp * 0.34999999f * ramp_player->cached_camera_target_world.y + lifted;
        desired_matrix.rotate_matrix_world_x(inverse_ramp * 0.87249994f);
    } else {
        desired_matrix.position.y =
            ramp_player->cached_camera_target_world.y * 0.34999999f + desired_matrix.position.y;
    }

    Player* lift_player = player;
    PathTemplate* template_record;
    int kind;
    if (lift_player->follow_active == 1
        && ((template_record = lift_player->follow_template,
             kind = template_record->kind,
             kind == 0x10)
            || kind == 8
            || kind == 9
            || kind == 10
            || kind == 0x2b
            || kind == 0x2d
            || kind == 0x24
            || kind == 0xe)) {
        float phase = (lift_player->live_position.z - lift_player->follow_source_cell->anchor_position_z)
            / template_record->segment_count_f;
        if (phase < 0.0f)
            phase = 0.0f;
        else if (phase > 1.0f)
            phase = 1.0f;
        attachment_lift_envelope = (0.5f - cosine(phase * 6.2831855f) * 0.5f) * 0.34999999f;
    } else {
        attachment_lift_envelope = 0.0f;
    }

    Player* pitch_player = player;
    if (pitch_player->cutscene_pitch_cycle > 0.0f) {
        attachment_lift_envelope =
            (0.5f - cosine(pitch_player->cutscene_pitch_cycle * 4.712389f + 1.5707964f) * 0.5f) * 0.23999999f
            + attachment_lift_envelope;
    }

    Player* target_player = player;
    float smoothed = (attachment_lift_envelope - smoothed_attachment_lift_envelope) * 0.1f
        + smoothed_attachment_lift_envelope;
    smoothed_attachment_lift_envelope = smoothed;
    desired_matrix.position.y = smoothed * target_player->cached_camera_target_world.y + desired_matrix.position.y;
    desired_matrix.position.x = target_player->cached_camera_target_world.x * 0.33333334f + desired_matrix.position.x;
    float desired_z = target_player->cached_camera_target_world.z + desired_matrix.position.z + 0.40000001f;
    desired_matrix.position.z = desired_z;
    float trailing_z = desired_z - previous_desired_matrix.position.z;
    if (trailing_z > 3.0f)
        previous_desired_matrix.position.z = desired_z - 3.0f;
    else if (trailing_z < 1.7f)
        previous_desired_matrix.position.z = desired_z - 1.7f;

    float pitch = (-2.0f - (target_player->cached_camera_target_world.y - 0.49000001f) * 5.0f) * 0.017449999f;
    if (pitch < -1.2214999f)
        pitch = -1.2214999f;
    else if (pitch > 1.2214999f)
        pitch = 1.2214999f;
    desired_matrix.rotate_matrix_world_x(pitch);

    Player* lean_player = player;
    float lean_roll = (0.5f - cosine(lean_player->lane_lean_progress * 3.1415927f) * 0.5f)
        * lean_player->lane_lean_amplitude * 6.2831855f;
    float steer_roll = lean_player->cached_camera_target_world.x * -8.0f;
    steer_roll = steer_roll * 0.017449999f;
    desired_matrix.rotate_matrix_world_z(lean_roll + steer_roll * 0.17f);

    if (player->follow_active == 1) {
        transform.set_matrix_identity();
        transform.rotate_matrix_world_z(player->follow_orientation_a);
        desired_matrix.multiply_matrix_in_place(&transform);
        desired_matrix.rotate_matrix_world_z(player->follow_orientation_b);
    }
    Player* exit_player = player;
    if (exit_player->attachment_exit_pending)
        desired_matrix.rotate_matrix_world_z(exit_player->post_follow_exit_roll);
    desired_matrix.rotate_matrix_world_z(player->heading_roll);

    Player* worm_player = player;
    PathTemplate* worm_template;
    float desired_fov;
    if (worm_player->follow_active == 1 && (worm_template = worm_player->follow_template, worm_template->kind == 0x18)) {
        float phase = (worm_player->live_position.z - worm_player->follow_source_cell->anchor_position_z)
            / worm_template->segment_count_f;
        if (phase < 0.0f)
            phase = 0.0f;
        else if (phase > 1.0f)
            phase = 1.0f;
        float envelope = 0.5f - cosine(phase * 6.2831855f) * 0.5f;
        debug_report_stub(g_worm_fov_report_format, (double)envelope);
        desired_fov = envelope * 50.0f + 110.0f;
    } else {
        desired_fov = 110.0f;
    }
    Game* rate_game = game;
    fov_degrees = (desired_fov - fov_degrees) * 0.30000001f + fov_degrees;
    live_matrix.linear_interpolate_matrix(
        &previous_desired_matrix,
        &desired_matrix,
        rate_game->subgame_rate * 0.30000001f);
    previous_desired_matrix = desired_matrix;
}
