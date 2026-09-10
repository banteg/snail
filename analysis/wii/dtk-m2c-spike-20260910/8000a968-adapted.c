? fn_8000F63C(void *);                              /* extern */
f64 fn_800CB5A8(f32);                               /* extern */
extern ? lbl_8015DC20;
extern f32 lbl_808F4878;
extern f32 lbl_808F4884;
extern f32 lbl_808F4890;
extern f32 lbl_808F4894;
extern f32 lbl_808F4898;
extern f32 lbl_808F489C;

void *fn_8000A968(void *arg0, void *arg1) {
    f32 temp_f3;
    f32 temp_f4;
    f32 temp_f5;
    f32 temp_f5_2;
    f32 temp_f5_3;
    f32 temp_f5_4;
    f32 temp_f7;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;
    s32 var_r0;

    temp_f5 = arg1->unk0;
    temp_f4 = arg1->unk14;
    temp_f3 = arg1->unk28;
    if ((lbl_808F4890 + (temp_f3 + (temp_f5 + temp_f4))) > lbl_808F4898) {
        temp_f7 = lbl_808F4894 / (f32) fn_800CB5A8();
        arg0->unkC = (f32) (lbl_808F489C / temp_f7);
        arg0->unk8 = (f32) (temp_f7 * (arg1->unk4 - arg1->unk10));
        arg0->unk0 = (f32) (temp_f7 * (arg1->unk18 - arg1->unk24));
        arg0->unk4 = (f32) (temp_f7 * (arg1->unk20 - arg1->unk8));
    } else {
        if (temp_f5 >= temp_f4) {
            if (temp_f5 > temp_f3) {
                var_r0 = 0;
            } else if (temp_f4 > temp_f3) {
                var_r0 = 1;
            } else {
                var_r0 = 2;
            }
        } else if (temp_f4 >= temp_f3) {
            var_r0 = 1;
        } else if (temp_f5 > temp_f3) {
            var_r0 = 0;
        } else {
            var_r0 = 2;
        }
        if (var_r0 == 0) {
            var_f1 = ((lbl_808F4890 + arg1->unk0) - arg1->unk14) - arg1->unk28;
            if (var_f1 < lbl_808F4884) {
                fn_8000F63C(&lbl_8015DC20 + 0x21);
                var_f1 = lbl_808F4884;
            }
            temp_f5_2 = lbl_808F4878 * (f32) fn_800CB5A8(var_f1);
            arg0->unk4 = (f32) ((arg1->unk10 + arg1->unk4) / temp_f5_2);
            arg0->unkC = (f32) ((arg1->unk24 + arg1->unk18) / temp_f5_2);
            arg0->unk8 = (f32) ((arg1->unk20 + arg1->unk8) / temp_f5_2);
            arg0->unk0 = (f32) (lbl_808F489C * temp_f5_2);
        } else if ((u32) var_r0 == 1U) {
            var_f1_2 = ((lbl_808F4890 + arg1->unk14) - arg1->unk0) - arg1->unk28;
            if (var_f1_2 < lbl_808F4884) {
                fn_8000F63C(&lbl_8015DC20 + 0x30);
                var_f1_2 = lbl_808F4884;
            }
            temp_f5_3 = lbl_808F4878 * (f32) fn_800CB5A8(var_f1_2);
            arg0->unk0 = (f32) ((arg1->unk10 + arg1->unk4) / temp_f5_3);
            arg0->unkC = (f32) ((arg1->unk20 + arg1->unk8) / temp_f5_3);
            arg0->unk8 = (f32) ((arg1->unk24 + arg1->unk18) / temp_f5_3);
            arg0->unk4 = (f32) (lbl_808F489C * temp_f5_3);
        } else if ((u32) var_r0 == 2U) {
            var_f1_3 = ((lbl_808F4890 + arg1->unk28) - arg1->unk0) - arg1->unk14;
            if (var_f1_3 < lbl_808F4884) {
                fn_8000F63C(&lbl_8015DC20 + 0x30);
                var_f1_3 = lbl_808F4884;
            }
            temp_f5_4 = lbl_808F4878 * (f32) fn_800CB5A8(var_f1_3);
            arg0->unk0 = (f32) ((arg1->unk20 + arg1->unk8) / temp_f5_4);
            arg0->unkC = (f32) ((arg1->unk10 + arg1->unk4) / temp_f5_4);
            arg0->unk4 = (f32) ((arg1->unk24 + arg1->unk18) / temp_f5_4);
            arg0->unk8 = (f32) (lbl_808F489C * temp_f5_4);
        }
    }
    return arg0;
}
