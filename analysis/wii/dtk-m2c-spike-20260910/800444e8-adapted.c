u8 *fn_8000C4D8(? *, s32, ?, ?);                    /* extern */
s32 fn_8000D8D4(void *, s32);                       /* extern */
? fn_8000DF98(void *);                              /* extern */
? fn_8000F6E0(void *, ? *);                         /* extern */
u8 *fn_8000F764(? *, u8 *);                         /* extern */
s32 fn_8000F8F0(u8 **);                             /* extern */
? sprintf(? *, void *, s32, void *);                /* extern */
extern ? lbl_80161498;
extern ? lbl_80167060;
extern ? lbl_801670B0;
extern s32 lbl_808F3E78;
extern f32 lbl_808F519C;
extern f32 lbl_808F51A0;
extern f32 lbl_808F51A4;
extern f32 lbl_808F51A8;
extern f32 lbl_808F51AC;
extern f32 lbl_808F51B0;
extern f32 lbl_808F51B4;
extern f32 lbl_808F51B8;

void fn_800444E8(void *arg0) {
    ? sp50;
    ? sp10;
    u8 *sp8;
    ? *var_r25;
    ? *var_r5;
    ? *var_r6;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    s32 temp_r0;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_r18;
    s32 var_r20;
    s32 var_r22;
    s32 var_r24;
    s32 var_r7;
    u8 *temp_r21;
    u8 *temp_r3;
    u8 *temp_r3_2;
    u8 *temp_r3_3;
    u8 *temp_r3_4;
    u8 *var_r27;
    u8 *var_r3;
    u8 *var_r4;
    u8 temp_r0_2;
    void *temp_r23;
    void *temp_r4;
    void *temp_r6;
    void *var_r26;

    arg0->unk0 = 0;
    var_r6 = &lbl_801670B0;
    arg0->unk8 = 0;
    var_r7 = 0;
    arg0->unk14 = 1;
    var_ctr = 0xC;
    do {
        var_r7 += 8;
        var_r6->unk0 = (f32) (var_r6->unk0 * lbl_808F519C);
        var_r6->unk4 = (f32) ((lbl_808F51A8 * ((var_r6->unk4 * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r6->unk8 = (f32) (var_r6->unk8 * lbl_808F519C);
        var_r6->unkC = (f32) ((lbl_808F51A8 * ((var_r6->unkC * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r6->unk10 = (f32) (var_r6->unk10 * lbl_808F519C);
        var_r6->unk14 = (f32) ((lbl_808F51A8 * ((var_r6->unk14 * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r6->unk18 = (f32) (var_r6->unk18 * lbl_808F519C);
        var_r6->unk1C = (f32) ((lbl_808F51A8 * ((var_r6->unk1C * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r6->unk20 = (f32) (var_r6->unk20 * lbl_808F519C);
        var_r6->unk24 = (f32) ((lbl_808F51A8 * ((var_r6->unk24 * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r6->unk28 = (f32) (var_r6->unk28 * lbl_808F519C);
        var_r6->unk2C = (f32) ((lbl_808F51A8 * ((var_r6->unk2C * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r6->unk30 = (f32) (var_r6->unk30 * lbl_808F519C);
        var_r6->unk34 = (f32) ((lbl_808F51A8 * ((f32) (var_r6->unk34 * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r6->unk38 = (f32) (var_r6->unk38 * lbl_808F519C);
        var_r6->unk3C = (f32) ((lbl_808F51A8 * ((var_r6->unk3C * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r6 += 0x40;
        var_ctr -= 1;
    } while (var_ctr != 0);
    temp_r0 = var_r7 * 8;
    temp_r4 = &lbl_801670B0 + temp_r0;
    var_r5 = &lbl_80167060;
    temp_r4->unk0 = (f32) (*(&lbl_801670B0 + temp_r0) * lbl_808F519C);
    temp_r4->unk4 = (f32) ((lbl_808F51A8 * ((temp_r4->unk4 * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
    temp_r4->unk8 = (f32) (temp_r4->unk8 * lbl_808F519C);
    temp_r4->unkC = (f32) ((lbl_808F51A8 * ((temp_r4->unkC * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
    temp_r4->unk10 = (f32) (temp_r4->unk10 * lbl_808F519C);
    temp_r4->unk14 = (f32) ((lbl_808F51A8 * ((temp_r4->unk14 * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
    temp_r4->unk18 = (f32) (temp_r4->unk18 * lbl_808F519C);
    temp_r4->unk1C = (f32) ((lbl_808F51A8 * ((temp_r4->unk1C * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
    temp_r4->unk20 = (f32) (temp_r4->unk20 * lbl_808F519C);
    temp_r4->unk24 = (f32) ((lbl_808F51A8 * ((temp_r4->unk24 * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
    var_ctr_2 = 2;
    do {
        var_r5->unk0 = (f32) (var_r5->unk0 * lbl_808F519C);
        var_r5->unk4 = (f32) ((lbl_808F51A8 * ((var_r5->unk4 * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r5->unk8 = (f32) (var_r5->unk8 * lbl_808F519C);
        var_r5->unkC = (f32) ((lbl_808F51A8 * ((var_r5->unkC * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r5->unk10 = (f32) (var_r5->unk10 * lbl_808F519C);
        var_r5->unk14 = (f32) ((lbl_808F51A8 * ((var_r5->unk14 * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r5->unk18 = (f32) (var_r5->unk18 * lbl_808F519C);
        var_r5->unk1C = (f32) ((lbl_808F51A8 * ((var_r5->unk1C * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r5->unk20 = (f32) (var_r5->unk20 * lbl_808F519C);
        var_r5->unk24 = (f32) ((lbl_808F51A8 * ((var_r5->unk24 * lbl_808F51A0) - lbl_808F51AC)) + lbl_808F51A4);
        var_r5 += 0x28;
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    arg0->unk10F78 = (s32) (lbl_808F3E78 + 0x60CCC);
    temp_f31 = lbl_808F51B8;
    temp_r21 = fn_8000C4D8(&lbl_80161498, fn_8000D8D4(arg0 + 0x10000, lbl_808F3E78 + 0x60000), 0, 0);
    temp_f29 = lbl_808F51B0;
    var_r26 = arg0;
    temp_f30 = lbl_808F51B4;
    var_r25 = &lbl_80167060;
    var_r22 = 0;
    var_r18 = 0;
    var_r27 = arg0 + 0x10938;
loop_5:
    sprintf(&sp10, &lbl_80161498 + 0x13, var_r22);
    temp_r3 = fn_8000F764(&sp10, temp_r21);
    sp8 = temp_r3;
    if (temp_r3 == NULL) {
        fn_8000DF98(&lbl_80161498 + 0x1D);
        return;
    }
    temp_r3_2 = fn_8000F764(&lbl_80161498 + 0x42, temp_r3);
    temp_r3_3 = temp_r3_2 + 1;
    sp8 = temp_r3_3;
    if ((s32) temp_r3_2->unk1 != 0x22) {
        fn_8000DF98(&lbl_80161498 + 0x44);
        return;
    }
    var_r3 = temp_r3_3 + 1;
    sp8 = var_r3;
    var_r4 = var_r27;
loop_11:
    if ((s32) *var_r3 != 0x22) {
        temp_r0_2 = *var_r3;
        var_r3 += 1;
        *var_r4 = temp_r0_2;
        var_r4 += 1;
        sp8 = var_r3;
        goto loop_11;
    }
    *var_r4 = 0;
    temp_r3_4 = fn_8000F764(&lbl_80161498 + 0x5D, sp8);
    sp8 = temp_r3_4;
    sp8 = fn_8000F764(&lbl_80161498 + 0x69, temp_r3_4) + 1;
    temp_r23 = &lbl_801670B0 + var_r18;
    var_r26->unk109B8 = fn_8000F8F0(&sp8);
    var_r20 = 0;
    var_r24 = 0;
    var_r26->unk109BC = temp_f29;
    var_r26->unk109C0 = temp_f29;
    var_r26->unk109C4 = temp_f29;
    var_r26->unk109C8 = temp_f30;
    var_r26->unk109CC = (f32) var_r25->unk0;
    var_r26->unk109D0 = (f32) var_r25->unk4;
    var_r26->unk109D4 = temp_f31;
loop_14:
    if (var_r20 < (s32) var_r26->unk109B8) {
        (arg0 + (arg0->unk14 * 0x2A0))->unk1C = var_r22;
        (arg0 + (arg0->unk14 * 0x2A0))->unk24 = (f32) (temp_r23 + ((var_r24 / (s32) var_r26->unk109B8) * 8))->unk8;
        temp_r6 = temp_r23 + ((var_r24 / (s32) var_r26->unk109B8) * 8);
        (arg0 + (arg0->unk14 * 0x2A0))->unk28 = (f32) temp_r6->unkC;
        (arg0 + (arg0->unk14 * 0x2A0))->unk2C = temp_f31;
        sprintf(&sp50, &lbl_80161498 + 0x6B, arg0->unk14, temp_r6);
        fn_8000F6E0(arg0 + (arg0->unk14 * 0x2A0) + 0x38, &sp50);
        fn_8000F6E0(arg0 + (arg0->unk14 * 0x2A0) + 0xB8, &sp50);
        var_r24 += 0xA;
        var_r20 += 1;
        arg0->unk14 = (s32) (arg0->unk14 + 1);
        goto loop_14;
    }
    var_r22 += 1;
    var_r26 += 0xA0;
    var_r25 += 8;
    var_r18 += 0x50;
    var_r27 += 0xA0;
    if (var_r22 >= 0xA) {
        arg0->unk1C = 0;
        arg0->unk24 = (f32) lbl_801670B0.unk0;
        arg0->unk28 = (f32) lbl_801670B0.unk4;
        arg0->unk2C = (f32) lbl_808F51B8;
        arg0->unk38 = 0;
        arg0->unkB8 = 0;
        return;
    }
    goto loop_5;
}
