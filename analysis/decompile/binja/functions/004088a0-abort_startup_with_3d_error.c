/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: abort_startup_with_3d_error @ 0x4088a0 */

004088ae        MessageBoxA(nullptr, "Snail Mail failed to start.\nPlease make sure you have at least\na 32 Meg 3D Hardware Accelerated Card \nand the latest DirectX drivers.", "ERROR", MB_ICONEXCLAMATION)
004088b6        sub_48be4f(0)
004088bf        return initialize_bod(0x4a10a4) __tailcall
