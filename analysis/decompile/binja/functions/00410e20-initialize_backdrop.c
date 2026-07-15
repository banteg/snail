/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_backdrop @ 0x410e20 */

00410e28        *(arg1 + 0x65c) = 1
00410e32        *(arg1 + 0x660) = 0
00410e38        *(arg1 + 0x3c) = 0xffffffff
00410e3f        *(arg1 + 0x4c) = 0
00410e42        *(arg1 + 0x6c8) = 0
00410e48        *(arg1 + 0x6c4) = 5
00410e52        *(arg1 + 0x6bc) = 0
00410e58        *(arg1 + 0x6c0) = 0x3b5a740e
00410e62        set_backdrop_texture_target(arg1, 5)
00410e73        if ((g_runtime_config.render_flags.b & 1) == 0)
00410e87        *(arg1 + 0x658) = 0
00410e8d        *(arg1 + 0x664) = 0
00410e75        *(arg1 + 0x658) = 1
00410e7f        *(arg1 + 0x664) = 0x3f800000
00410e97        *(arg1 + 0x668) = 0x3caaaaab
00410ea3        if (arg2 == 0)
00410eca        *(arg1 + 0x66c) = 0
00410ed0        *(arg1 + 0x670) = 0x3aab92a6
00410eda        *(arg1 + 0x674) = 0
00410ee0        *(arg1 + 0x678) = 0x3ae4c389
00410eea        label_410eea:
00410eea        *(arg1 + 0x694) = 0
00410ef0        *(arg1 + 0x698) = 0
00410ef6        *(arg1 + 0x68c) = 0x3f800000
00410efc        *(arg1 + 0x690) = 0x3bb60b61
00410f06        *(arg1 + 0x6b4) = 0
00410f0c        *(arg1 + 0x6b8) = 0
00410f12        *(arg1 + 0x6ac) = 0x3f800000
00410f18        *(arg1 + 0x6b0) = 0x3b888889
00410ea6        if (arg2 == 1)
00410ea8        *(arg1 + 0x66c) = 0
00410eae        *(arg1 + 0x670) = 0xbb2b92a6
00410eb8        *(arg1 + 0x674) = 0
00410ebe        *(arg1 + 0x678) = 0xbb64c389
00410ec8        goto label_410eea
00410f25        set_backdrop_texture_target(arg1, 0)
00410f34        return set_backdrop_distort(arg1, 0f)
