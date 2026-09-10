? fn_80009C28(s32 *, ? *, f32, f32, f32, f32, f32, f32, f32, f32); /* extern */
? fn_8000A254(void *);                              /* extern */
? fn_8000B82C(void *);                              /* extern */
? fn_8000B8FC(void *, f32);                         /* extern */
u8 *fn_8000CC7C(s32, ?, ?);                         /* extern */
? fn_8000DD60(u8 *);                                /* extern */
? fn_8000DF98(void *);                              /* extern */
? fn_8000F250(? *, ?, ?, void *);                   /* extern */
u8 *fn_8000F764(void *, u8 *);                      /* extern */
f32 fn_8000F98C(u8 **);                             /* extern */
? fn_80019E0C(void *, void *, ?, void *);           /* extern */
? fn_80021470(void *, f32);                         /* extern */
? fn_80021A80(void *, s32);                         /* extern */
s32 fn_8003D04C(void *, void *);                    /* extern */
s32 fn_80040B4C(s8);                                /* extern */
? fn_80047238(void *);                              /* extern */
? fn_80047ADC(void *, void *, f32, f32, f32, f32);  /* extern */
extern ? lbl_80162288;
extern ? lbl_8058F3A0;
extern ? lbl_8081E178;
extern void *lbl_808F3E78;
extern f32 lbl_808F3E80;
extern f32 lbl_808F5830;
extern f32 lbl_808F5834;
extern f32 lbl_808F5838;
extern f32 lbl_808F583C;
extern f32 lbl_808F5840;
extern f32 lbl_808F5844;
extern f32 lbl_808F5848;
extern f32 lbl_808F584C;
extern f32 lbl_808F5850;
extern f32 lbl_808F5854;
extern f32 lbl_808F5858;
extern f32 lbl_808F585C;

void fn_80075CC8(void *arg0, s32 arg1) {
    s32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    u8 *sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f26;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f27;
    f32 var_f27_2;
    f32 var_f28;
    s32 var_r24;
    s32 var_r25;
    s32 var_r4;
    u8 *temp_r27;
    u8 *temp_r30;
    u8 *temp_r3;
    u8 *temp_r3_11;
    u8 *var_r26;
    u8 *var_r3;
    u8 temp_r3_2;
    u8 temp_r4;
    void *temp_r3_10;
    void *temp_r3_3;
    void *temp_r3_4;
    void *temp_r3_5;
    void *temp_r3_6;
    void *temp_r3_7;
    void *temp_r3_8;
    void *temp_r3_9;
    void *temp_r5;
    void *temp_r5_2;
    void *temp_r6;
    void *var_r3_2;

    fn_8000F250(&lbl_80162288, 1, 0, &lbl_80162288 + 0x14);
    fn_80019E0C(lbl_808F3E78 + 0x3BF58, lbl_808F3E78 + 0x350000 + (fn_8003D04C(lbl_808F3E78 + 0x350DA4, &lbl_80162288 + 0x15) * 0x1A8) + 0xDA8, 0, lbl_808F3E78);
    fn_80021470(lbl_808F3E78 + 0x2000, lbl_808F5830);
    fn_80047238(lbl_808F3E78 + 0x3CBEC);
    temp_r27 = fn_8000CC7C(arg1, 0, 0);
    arg0->unkC = (s32) lbl_8058F3A0.unk30;
    sp8 = lbl_808F5830;
    spC = lbl_808F5840;
    sp10 = lbl_808F5838;
    sp14 = lbl_808F5830;
    sp18 = lbl_808F5830;
    sp1C = lbl_808F5830;
    sp20 = lbl_808F5830;
    sp24 = lbl_808F5834;
    fn_80009C28(&sp50, &lbl_8058F3A0, lbl_808F5834, lbl_808F5830, lbl_808F5830, lbl_808F5830, lbl_808F5830, lbl_808F5838, lbl_808F583C, lbl_808F5830);
    lbl_808F3E78->unk22C = sp50;
    lbl_808F3E78->unk230 = sp54;
    lbl_808F3E78->unk234 = sp58;
    lbl_808F3E78->unk238 = sp5C;
    lbl_808F3E78->unk23C = sp60;
    lbl_808F3E78->unk240 = sp64;
    lbl_808F3E78->unk244 = sp68;
    lbl_808F3E78->unk248 = sp6C;
    lbl_808F3E78->unk24C = sp70;
    lbl_808F3E78->unk250 = sp74;
    lbl_808F3E78->unk254 = sp78;
    lbl_808F3E78->unk258 = sp7C;
    lbl_808F3E78->unk25C = sp80;
    lbl_808F3E78->unk260 = sp84;
    lbl_808F3E78->unk264 = sp88;
    lbl_808F3E78->unk268 = sp8C;
    lbl_808F3E78->unk348 = (f32) lbl_808F5844;
    arg0->unk0 = (f32) lbl_808F5830;
    temp_f1 = lbl_808F5848 * lbl_808F3E80;
    arg0->unk4 = (f32) (lbl_808F5834 / temp_f1);
    fn_80047ADC(lbl_808F3E78 + 0x354, lbl_808F3E78, temp_f1, lbl_808F5848, lbl_808F5844, sp8C);
    arg0->unk8 = 0;
    temp_f26 = lbl_808F5834;
    arg0->unk14 = 0;
    var_f28 = lbl_808F584C;
    temp_r3 = fn_8000F764(&lbl_80162288 + 0x22, temp_r27);
    sp28 = temp_r3;
    sp28 = fn_8000F764(&lbl_80162288 + 0x2E, temp_r3) + 1;
    temp_f30 = lbl_808F5830;
    temp_f31 = lbl_808F5854;
    temp_r30 = fn_8000F764(&lbl_80162288 + 0x30, temp_r27);
    temp_f29 = lbl_808F5850;
loop_21:
    if (sp28 < temp_r30) {
        var_r26 = sp28;
        var_r25 = 0;
        var_f27 = lbl_808F5830;
        if ((s32) *var_r26 == 0x2A) {
            sp28 = var_r26 + 1;
        } else {
            var_r3 = var_r26;
loop_5:
            temp_r3_2 = *var_r3;
            if (((s8) temp_r3_2 != 0) && ((s8) temp_r3_2 != 0xD)) {
                var_r25 += 1;
                temp_f0 = (&lbl_8081E178 + (fn_80040B4C((s8) temp_r3_2) * 4))->unk3208;
                var_r3 = sp28 + 1;
                sp28 = var_r3;
                var_f27 += temp_f0;
                goto loop_5;
            }
            if (var_r25 > 0) {
                var_r24 = 0;
                var_f27_2 = var_f27 * temp_f29 * temp_f26;
loop_18:
                if (var_r24 < var_r25) {
                    if ((s32) *var_r26 != 0x20) {
                        temp_r5 = arg0 + (arg0->unk14 * 0x90);
                        temp_r5_2 = temp_r5 + 0x18;
                        if (temp_r5->unk18 & 0x200) {
                            fn_8000DF98(&lbl_80162288 + 0x3A);
                        } else {
                            temp_r3_3 = lbl_808F3E78->unkA50;
                            if (temp_r3_3 == NULL) {
                                lbl_808F3E78->unkA50 = temp_r5_2;
                                temp_r5_2->unk4 = 0;
                                lbl_808F3E78->unkA50->unk8 = 0;
                            } else {
                                temp_r3_3->unk4 = temp_r5_2;
                                temp_r6 = lbl_808F3E78->unkA50;
                                temp_r6->unk4->unk8 = temp_r6;
                                temp_r3_4 = lbl_808F3E78->unkA50->unk4;
                                lbl_808F3E78->unkA50 = temp_r3_4;
                                temp_r3_4->unk4 = 0;
                            }
                            temp_r5->unk18 = (s32) (temp_r5->unk18 | 0x200);
                        }
                        fn_80021A80(arg0 + (arg0->unk14 * 0x90) + 0x18, (&lbl_8081E178 + (fn_80040B4C((s8) *var_r26) * 0x30))->unk1A28);
                        fn_8000A254(arg0 + (arg0->unk14 * 0x90) + 0x48);
                        sp38 = temp_f30;
                        sp3C = temp_f31;
                        temp_r3_5 = arg0 + (arg0->unk14 * 0x90);
                        sp40 = temp_f30;
                        temp_r3_5->unk78 = temp_f30;
                        temp_r3_5->unk7C = temp_f31;
                        temp_r3_5->unk80 = temp_f30;
                        temp_r3_6 = arg0 + (arg0->unk14 * 0x90);
                        temp_r3_6->unk78 = (f32) (temp_r3_6->unk78 + var_f27_2);
                        temp_r3_7 = arg0 + (arg0->unk14 * 0x90);
                        temp_r3_7->unk80 = (f32) (temp_r3_7->unk80 + var_f28);
                        fn_8000B82C(arg0 + (arg0->unk14 * 0x90) + 0x3C);
                        fn_8000B8FC(arg0 + (arg0->unk14 * 0x90) + 0x3C, lbl_808F5858);
                        temp_r3_8 = arg0 + (arg0->unk14 * 0x90);
                        temp_r3_8->unkA0 = temp_f30;
                        temp_r3_8->unk9C = temp_f30;
                        temp_r3_8->unk98 = temp_f30;
                        temp_r4 = *var_r26;
                        (arg0 + (arg0->unk14 * 0x90))->unkA4 = temp_r4;
                        temp_r3_9 = arg0 + (arg0->unk14 * 0x90) + 0x18;
                        temp_r3_9->unk2C->unk8(temp_r3_9, temp_r4);
                        arg0->unk14 = (s32) (arg0->unk14 + 1);
                    }
                    temp_r3_10 = &lbl_8081E178 + (fn_80040B4C((s8) *var_r26) * 4);
                    var_r26 += 1;
                    var_r24 += 1;
                    var_f27_2 = -((temp_f26 * (lbl_8081E178.unk3408 + temp_r3_10->unk3208)) - var_f27_2);
                    goto loop_18;
                }
            }
        }
        if ((s32) *sp28 == 0xD) {
            var_f28 -= temp_f26;
            sp28 += 2;
        }
        goto loop_21;
    }
    temp_r3_11 = fn_8000F764(&lbl_80162288 + 0x43, temp_r27);
    sp28 = temp_r3_11;
    sp28 = fn_8000F764(&lbl_80162288 + 0x2E, temp_r3_11);
    temp_f1_2 = fn_8000F98C(&sp28);
    arg0->unk10 = temp_f1_2;
    var_r3_2 = arg0;
    sp2C = lbl_808F5830;
    temp_f1_3 = (f32) lbl_808F5830;
    var_r4 = 0;
    sp30 = lbl_808F5830;
    sp44 = lbl_808F5830;
    sp48 = lbl_808F5830;
    temp_f2 = (lbl_808F585C + -var_f28) * (lbl_808F5834 / ((f32) temp_f1_2 * lbl_808F3E80));
    sp34 = temp_f2;
    sp4C = temp_f2;
loop_24:
    if (var_r4 < (s32) arg0->unk14) {
        var_r3_2->unk98 = temp_f1_3;
        var_r4 += 1;
        var_r3_2->unk9C = temp_f1_3;
        var_r3_2->unkA0 = (f32) temp_f2;
        var_r3_2 += 0x90;
        goto loop_24;
    }
    fn_8000DD60(temp_r27);
}
