// Declaration prelude of the Windows RShell.o translation unit.
//
// VC6 numbers frontend symbols with one counter for the whole translation
// unit. A call's operand hash folds in its callee's number, so the order in
// which C2 emits two call operands depends on how many declarations precede
// the callee (see tools/match/c2/address-order.md, "Hash kinds").
// read_repeating_text_input_key_code (RShellInkeyInput) is byte-exact only
// when RstrASC's number puts its hash in the wrapping window.
//
// RShell compiles as one translation unit, and its first member includes this
// header, so it stands where RShell.cpp's header block stood: before every
// function. RstrASC is first declared when enumerate_matching_archive_or_fs_entries
// includes rstring.h; the twelve members before it are counted for real.
//
// The SDK includes are the real Microsoft DirectX 8.1 SDK headers, fetched
// by tools/match/fetch_dx81_sdk.sh. Each is justified by the binary:
// - Direct3DCreate8(0xdc): 220 is D3D_SDK_VERSION for DirectX 8.1;
// - statically linked D3DX8 code (DisableD3DXPSGP, d3d8d.dll);
// - DirectInput8Create;
// - timeGetTime (mmsystem).
// Sound is BASS, loaded at run time, so dsound.h is not included.
#ifndef RSHELL_PRELUDE_H
#define RSHELL_PRELUDE_H

// The SDK block and the stand-in only steer VC6's symbol numbering; the port
// needs neither.
#ifndef SNAIL_PORT

#include <windows.h>
#include <mmsystem.h>
#include "../../tools/match/sdk/dx81/d3d8.h"
#include "../../tools/match/sdk/dx81/d3dx8.h"
#define DIRECTINPUT_VERSION 0x0800
#include "../../tools/match/sdk/dx81/dinput.h"

// STAND-IN, not recovered source. Between the SDK headers and the recovered
// headers below, RstrASC needs 10,541..12,588 more frontend ids to land in its
// window (measured with the matcher); the enum holds 11,564, the middle: 1 for
// its type and 1 per enumerator. It holds the place of the unrecovered part of
// RShell.cpp's header block. Strings name RShell.h, GDX.h, font.h and
// RSprite.h, and the headers in decomp/include are partial views of them:
// together (those that compile beside the SDK) they consume only about 8,300
// ids, so the gap cannot be closed from recovered headers yet. Count
// replacements with crimson's per-kind id table (scripts/c2/fe_id_probe.py,
// note frontend-ids.md) and shrink the enum by what they consume.
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
    // 11 * 1000
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
    // + 5 * 100
    RSHELL_STANDIN_100(rshell_standin_m0),
    RSHELL_STANDIN_100(rshell_standin_m1),
    RSHELL_STANDIN_100(rshell_standin_m2),
    RSHELL_STANDIN_100(rshell_standin_m3),
    RSHELL_STANDIN_100(rshell_standin_m4),
    // + 6 * 10 + 3 = 11,563
    RSHELL_STANDIN_10(rshell_standin_n0),
    RSHELL_STANDIN_10(rshell_standin_n1),
    RSHELL_STANDIN_10(rshell_standin_n2),
    RSHELL_STANDIN_10(rshell_standin_n3),
    RSHELL_STANDIN_10(rshell_standin_n4),
    RSHELL_STANDIN_10(rshell_standin_n5),
    rshell_standin_o0,
    rshell_standin_o1,
    rshell_standin_o2
};

#endif  // SNAIL_PORT

// The recovered part of RShell.cpp's header block: every header RShell's
// members include, hoisted here as one block. Before RstrASC they supply
// 1,381 ids that the stand-in used to hold. rstring.h stays with
// enumerate_matching_archive_or_fs_entries, since RstrASC must follow the
// stand-in.
#include <direct.h>
#include <io.h>
#include <stdarg.h>
#include <stdio.h>
#include "archive_index.h"
#include "audio_system.h"
#include "authored_view_state.h"
#include "font_system.h"
#include "input_controller_state.h"
#include "loading_bar.h"
#include "main_loop_state.h"
#include "rdebug.h"
#include "rshell.h"
#include "rtext.h"
#include "text_input_repeat_state.h"
#include "tracked_allocation_stack.h"

#endif
