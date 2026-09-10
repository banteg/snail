? fn_8000DF98(void *, s32 *, s32);                  /* extern */
u32 fn_8003EFF4(? *, s32, ?, ?);                    /* extern */
? unrecognized_restgpr_26(f32, f32, f32, f32, f32, f32); /* extern */
void *unrecognized_savegpr_26();                    /* extern */
extern ? lbl_80161894;
extern ? lbl_80167478;
extern ? lbl_8058FB38;
extern f32 lbl_808F5378;
extern f32 lbl_808F537C;
extern f32 lbl_808F53CC;
extern f32 lbl_808F53DC;
extern f32 lbl_808F54CC;
extern f32 lbl_808F54FC;

void fn_80052A00(void) {
    s32 spC;
    s32 sp8;
    ? *var_r29;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f5;
    f32 temp_f6;
    f32 var_f28;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r6;
    s32 var_ctr;
    s32 var_r5;
    s32 var_r7;
    u16 temp_r3_3;
    u16 temp_r3_4;
    u16 temp_r3_5;
    u32 temp_r3_2;
    void *temp_r28;
    void *temp_r3;
    void *var_r30;

    temp_r3 = unrecognized_savegpr_26();
    temp_f30 = lbl_808F5378;
    var_r30 = temp_r3;
    var_r29 = &lbl_80167478;
    temp_r28 = temp_r3->unk7A4;
    temp_f29 = lbl_808F537C;
    do {
        var_r30->unk810 = temp_f30;
        var_f28 = temp_f30;
        var_r30->unk80C = temp_f30;
        var_r30->unk808 = temp_f30;
        var_r30->unk81C = temp_f30;
        var_r30->unk818 = temp_f30;
        var_r30->unk814 = temp_f30;
        var_r30->unk804 = (s32) var_r29->unk0;
        temp_r3_2 = fn_8003EFF4(&lbl_8058FB38, var_r29->unk4, 0, 0);
        temp_r0_2 = temp_r28->unkCC;
        var_r7 = 0;
        var_r5 = 0;
        var_ctr = temp_r0_2;
        if (temp_r0_2 > 0) {
loop_2:
            temp_r6 = temp_r28->unkD4;
            if ((u32) (temp_r6 + var_r5)->unkC == temp_r3_2) {
                if (temp_r28->unk0 & 0x20) {
                    temp_r5 = var_r7 * 0x30;
                    var_r30->unk808 = (f32) ((temp_r28->unk18 * (f32) *(temp_r28->unkAC + ((temp_r6 + temp_r5)->unk2 * 6))) + var_r30->unk808);
                    var_r30->unk80C = (f32) ((temp_r28->unk18 * (f32) (temp_r28->unkAC + ((temp_r28->unkD4 + temp_r5)->unk2 * 6))->unk2) + var_r30->unk80C);
                    var_r30->unk810 = (f32) ((temp_r28->unk18 * (f32) (temp_r28->unkAC + ((temp_r28->unkD4 + temp_r5)->unk2 * 6))->unk4) + var_r30->unk810);
                } else {
                    temp_r5_2 = var_r7 * 0x30;
                    temp_r3_3 = (temp_r6 + temp_r5_2)->unk2;
                    var_r30->unk808 = (f32) ((temp_r28->unk18 * (f32) (s8) *(temp_r28->unkAC + ((temp_r3_3 * 4) - temp_r3_3))) + var_r30->unk808);
                    temp_r3_4 = (temp_r28->unkD4 + temp_r5_2)->unk2;
                    var_r30->unk80C = (f32) ((temp_r28->unk18 * (f32) (s8) (temp_r28->unkAC + ((temp_r3_4 * 4) - temp_r3_4))->unk1) + var_r30->unk80C);
                    temp_r3_5 = (temp_r28->unkD4 + temp_r5_2)->unk2;
                    var_r30->unk810 = (f32) ((temp_r28->unk18 * (f32) (s8) (temp_r28->unkAC + ((temp_r3_5 * 4) - temp_r3_5))->unk2) + var_r30->unk810);
                }
                var_f28 = temp_f30 + temp_f29;
            } else {
                var_r5 += 0x30;
                var_r7 += 1;
                var_ctr -= 1;
                if (var_ctr != 0) {
                    goto loop_2;
                }
            }
        }
        if (temp_f30 == var_f28) {
            temp_r5_3 = var_r29->unk0;
            sp8 = temp_r5_3;
            spC = var_r29->unk4;
            fn_8000DF98(&lbl_80161894 + 0xE3, &sp8, temp_r5_3);
        } else {
            temp_f1 = temp_f29 / var_f28;
            var_r30->unk808 = (f32) (var_r30->unk808 * temp_f1);
            var_r30->unk80C = (f32) (var_r30->unk80C * temp_f1);
            var_r30->unk810 = (f32) (var_r30->unk810 * temp_f1);
        }
        temp_r0 = var_r29->unk0;
        var_r30 += 0x1C;
        var_r29 += 8;
    } while (temp_r0 != 0);
    temp_f6 = temp_r3->unkA04 + lbl_808F53DC;
    temp_f5 = temp_r3->unk95C + lbl_808F53CC;
    temp_f1_2 = temp_r3->unkA00;
    temp_r3->unkA04 = temp_f6;
    temp_r3->unk95C = temp_f5;
    temp_r3->unkA18 = 1;
    temp_r3->unkA1C = (f32) lbl_808F5378;
    temp_r3->unkA20 = (f32) lbl_808F54CC;
    temp_r3->unkA24 = (f32) lbl_808F54FC;
    temp_r3->unkA38 = temp_f1_2;
    temp_r3->unkA3C = temp_f6;
    temp_r3->unkA40 = (f32) temp_r3->unkA08;
    unrecognized_restgpr_26(temp_f1_2, lbl_808F54FC, lbl_808F54CC, lbl_808F5378, temp_f5, temp_f6);
}
