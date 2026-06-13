// initialize_cameraman @ 0x446160 (thiscall, ret)
#include "vector_types.h"

extern int g_game_base; // data_4df904

struct TransformMatrix {
    Vector4 basis_right;
    Vector4 basis_up;
    Vector4 basis_forward;
    Vector4 position;
};

void __fastcall set_matrix_identity(TransformMatrix* transform);

class CameramanState {
public:
    void initialize_cameraman();

    TransformMatrix live_matrix;             // +0x00
    TransformMatrix desired_matrix;          // +0x40
    TransformMatrix previous_desired_matrix; // +0x80
    char* player;                            // +0xc0
    char* game;                              // +0xc4
    float fov_degrees;                       // +0xc8
    unsigned char unresolved_cc;             // +0xcc
    char unknown_cd[0xd0 - 0xcd];
    float attachment_lift_envelope;          // +0xd0
    float smoothed_attachment_lift_envelope; // +0xd4
};

void CameramanState::initialize_cameraman()
{
    *(int*)&player = g_game_base + 0x42fd7c;
    *(int*)&game = g_game_base + 0x74618;
    unresolved_cc = 0;
    set_matrix_identity(&previous_desired_matrix);
    set_matrix_identity(&desired_matrix);
    set_matrix_identity(&live_matrix);
    attachment_lift_envelope = 0.0f;
    smoothed_attachment_lift_envelope = 0.0f;
    fov_degrees = 110.0f;
}
