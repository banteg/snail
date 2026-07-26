/*
 * mangled: _ZN8cRBorder8SetRightEPS_
 * demangled: cRBorder::SetRight(cRBorder*)
 * address: 00038c90
 * size: 468
 */

/* cRBorder::SetRight(cRBorder*) */

void __thiscall cRBorder::SetRight(cRBorder *this,cRBorder *param_1)

{
  cRBorder *pcVar1;
  float fVar2;
  float fVar3;

  if ((*(uint *)(this + 0x194) & 0x800) == 0) {
    if (*(int *)(param_1 + 0x254) == 0) {
      pcVar1 = this + 0x6ec;
      fVar2 = *(float *)(param_1 + 0x6ec) + *(float *)(param_1 + 0x23c) +
              *(float *)(param_1 + 0x20c) + *(float *)(param_1 + 0x264);
      *(float *)pcVar1 = fVar2;
      if (*(int *)(this + 0x254) == 0) {
        *(float *)pcVar1 = fVar2 + *(float *)(this + 0x20c) + *(float *)(this + 0x264);
      }
      else {
        *(undefined4 *)pcVar1 = 0;
        *(float *)(this + 600) =
             (fVar2 + *(float *)(this + 0x20c) + *(float *)(this + 0x23c) * 0.5 +
                      *(float *)(this + 0x264)) - 320.0;
      }
    }
    else {
      pcVar1 = this + 0x6ec;
      fVar2 = *(float *)(param_1 + 600) + 320.0 + *(float *)(param_1 + 0x23c) * 0.5 +
              *(float *)(param_1 + 0x20c) + *(float *)(param_1 + 0x264);
      *(float *)pcVar1 = fVar2;
      if (*(int *)(this + 0x254) == 0) {
        *(float *)pcVar1 = fVar2 + *(float *)(this + 0x20c) + *(float *)(this + 0x264);
      }
      else {
        *(undefined4 *)pcVar1 = 0;
        *(float *)(this + 600) =
             (fVar2 + *(float *)(this + 0x20c) + *(float *)(this + 0x23c) * 0.5 +
                      *(float *)(this + 0x264)) - 320.0;
      }
    }
    *(undefined4 *)(this + 0x6f0) = *(undefined4 *)(param_1 + 0x6f0);
  }
  else {
    if (*(int *)(param_1 + 0x254) == 0) {
      fVar3 = *(float *)(param_1 + 0x6ec) + *(float *)(param_1 + 0x23c);
      fVar2 = *(float *)(this + 0x264);
    }
    else if (*(int *)(param_1 + 0x254) == 3) {
      fVar3 = *(float *)(param_1 + 600) + 320.0 + *(float *)(param_1 + 0x20c);
      fVar2 = *(float *)(param_1 + 0x264);
    }
    else {
      fVar3 = *(float *)(param_1 + 600) + 320.0 + *(float *)(param_1 + 0x23c) * 0.5 +
              *(float *)(param_1 + 0x20c);
      fVar2 = *(float *)(param_1 + 0x264);
    }
    *(undefined4 *)(this + 0x230) = *(undefined4 *)(param_1 + 0x6f0);
    *(float *)(this + 0x22c) = fVar3 + fVar2;
    *(float *)(this + 0x6ec) = fVar3 + fVar2;
    *(undefined4 *)(this + 0x6f0) = *(undefined4 *)(this + 0x230);
  }
  RePosition(this);
  return;
}
