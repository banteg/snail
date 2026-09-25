// Declaration prelude of the Windows RShell.o translation unit.
//
// VC6 numbers frontend symbols with one counter for the whole translation
// unit. A call's operand hash folds in its callee's number, so the order in
// which C2 emits two call operands depends on how many declarations precede
// the callee (see tools/match/c2/address-order.md, "Hash kinds").
// read_repeating_text_input_key_code (RShellInkeyInput) is byte-exact only
// when RstrASC's number puts its hash in the wrapping window.
//
// The includes below are the real Microsoft DirectX 8.1 SDK headers, fetched
// by tools/match/fetch_dx81_sdk.sh. Each is justified by the binary:
// - Direct3DCreate8(0xdc): 220 is D3D_SDK_VERSION for DirectX 8.1;
// - statically linked D3DX8 code (DisableD3DXPSGP, d3d8d.dll);
// - DirectInput8Create;
// - timeGetTime (mmsystem).
// Sound is BASS, loaded at run time, so dsound.h is not included.
#ifndef RSHELL_PRELUDE_H
#define RSHELL_PRELUDE_H

#include <windows.h>
#include <mmsystem.h>
#include "../sdk/dx81/d3d8.h"
#include "../sdk/dx81/d3dx8.h"
#define DIRECTINPUT_VERSION 0x0800
#include "../sdk/dx81/dinput.h"

// STAND-IN, not recovered source. After the SDK headers, RShell's own
// includes still had 12,737..14,784 more frontend ids before RstrASC's
// first declaration. Presumably these are RShell.h plus the engine and game
// headers it pulls in; strings name RShell.h, GDX.h, font.h and RSprite.h.
// The enum below holds their place with 13,763 ids: 1 for the enum type and
// 1 per enumerator. Replace it with recovered headers as they are
// identified, counting them with crimson's per-kind id table
// (scripts/c2/fe_id_probe.py, note frontend-ids.md). Pad any shortfall.
#define RSHELL_STANDIN_10(p) \
    p##0, p##1, p##2, p##3, p##4, p##5, p##6, p##7, p##8, p##9
#define RSHELL_STANDIN_100(p)                                          \
    RSHELL_STANDIN_10(p##0), RSHELL_STANDIN_10(p##1),                  \
    RSHELL_STANDIN_10(p##2), RSHELL_STANDIN_10(p##3),                  \
    RSHELL_STANDIN_10(p##4), RSHELL_STANDIN_10(p##5),                  \
    RSHELL_STANDIN_10(p##6), RSHELL_STANDIN_10(p##7),                  \
    RSHELL_STANDIN_10(p##8), RSHELL_STANDIN_10(p##9)
#define RSHELL_STANDIN_1000(p)                                         \
    RSHELL_STANDIN_100(p##0), RSHELL_STANDIN_100(p##1),                \
    RSHELL_STANDIN_100(p##2), RSHELL_STANDIN_100(p##3),                \
    RSHELL_STANDIN_100(p##4), RSHELL_STANDIN_100(p##5),                \
    RSHELL_STANDIN_100(p##6), RSHELL_STANDIN_100(p##7),                \
    RSHELL_STANDIN_100(p##8), RSHELL_STANDIN_100(p##9)

enum RShellProjectHeaderStandIn {
    // 13 * 1000
    RSHELL_STANDIN_1000(rshell_standin_a),
    RSHELL_STANDIN_1000(rshell_standin_b),
    RSHELL_STANDIN_1000(rshell_standin_c),
    RSHELL_STANDIN_1000(rshell_standin_d),
    RSHELL_STANDIN_1000(rshell_standin_e),
    RSHELL_STANDIN_1000(rshell_standin_f),
    RSHELL_STANDIN_1000(rshell_standin_g),
    RSHELL_STANDIN_1000(rshell_standin_h),
    RSHELL_STANDIN_1000(rshell_standin_i),
    RSHELL_STANDIN_1000(rshell_standin_j),
    RSHELL_STANDIN_1000(rshell_standin_k),
    RSHELL_STANDIN_1000(rshell_standin_l),
    RSHELL_STANDIN_1000(rshell_standin_m),
    // + 7 * 100
    RSHELL_STANDIN_100(rshell_standin_n0),
    RSHELL_STANDIN_100(rshell_standin_n1),
    RSHELL_STANDIN_100(rshell_standin_n2),
    RSHELL_STANDIN_100(rshell_standin_n3),
    RSHELL_STANDIN_100(rshell_standin_n4),
    RSHELL_STANDIN_100(rshell_standin_n5),
    RSHELL_STANDIN_100(rshell_standin_n6),
    // + 6 * 10 + 2 = 13,762
    RSHELL_STANDIN_10(rshell_standin_o0),
    RSHELL_STANDIN_10(rshell_standin_o1),
    RSHELL_STANDIN_10(rshell_standin_o2),
    RSHELL_STANDIN_10(rshell_standin_o3),
    RSHELL_STANDIN_10(rshell_standin_o4),
    RSHELL_STANDIN_10(rshell_standin_o5),
    rshell_standin_p0,
    rshell_standin_p1
};

#endif
