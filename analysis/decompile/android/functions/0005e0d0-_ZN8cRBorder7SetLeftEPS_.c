/*
 * mangled: _ZN8cRBorder7SetLeftEPS_
 * demangled: cRBorder::SetLeft(cRBorder*)
 * address: 0005e0d0
 * size: 536
 */

/* cRBorder::SetLeft(cRBorder*) */

void __thiscall cRBorder::SetLeft(cRBorder *this,cRBorder *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;

  if ((*(uint *)(this + 0x194) & 0x800) == 0) {
    if (*(int *)(param_1 + 0x254) == 0) {
      fVar1 = (*(float *)(param_1 + 0x6ec) - *(float *)(param_1 + 0x20c)) -
              *(float *)(param_1 + 0x264);
      *(float *)(this + 0x6ec) = fVar1;
      if (*(int *)(this + 0x254) == 0) {
        *(float *)(this + 0x6ec) =
             fVar1 + ((-*(float *)(this + 0x20c) - *(float *)(this + 0x23c)) -
                     *(float *)(this + 0x264));
      }
      else {
        *(undefined4 *)(this + 0x6ec) = 0;
        *(float *)(this + 600) =
             (fVar1 + ((*(float *)(this + 0x23c) * -0.5 - *(float *)(this + 0x20c)) -
                      *(float *)(this + 0x264))) - 320.0;
      }
    }
    else {
      fVar1 = ((*(float *)(param_1 + 600) + 320.0 + *(float *)(param_1 + 0x23c) * -0.5) -
              *(float *)(param_1 + 0x20c)) - *(float *)(param_1 + 0x264);
      *(float *)(this + 0x6ec) = fVar1;
      if (*(int *)(this + 0x254) == 0) {
        *(float *)(this + 0x6ec) = fVar1 + (-*(float *)(this + 0x20c) - *(float *)(this + 0x264));
      }
      else {
        *(undefined4 *)(this + 0x6ec) = 0;
        *(float *)(this + 600) =
             (fVar1 + ((*(float *)(this + 0x23c) * -0.5 - *(float *)(this + 0x20c)) -
                      *(float *)(this + 0x264))) - 320.0;
      }
    }
    *(undefined4 *)(this + 0x6f0) = *(undefined4 *)(param_1 + 0x6f0);
  }
  else {
    if (*(int *)(param_1 + 0x254) == 0) {
      fVar2 = *(float *)(param_1 + 0x23c);
      fVar1 = *(float *)(param_1 + 0x6ec);
      *(undefined4 *)(this + 0x230) = *(undefined4 *)(param_1 + 0x6f0);
      fVar2 = fVar1 + fVar2 + *(float *)(this + 0x264);
      *(float *)(this + 0x22c) = fVar2;
    }
    else if (*(int *)(param_1 + 0x254) == 3) {
      fVar4 = *(float *)(param_1 + 600);
      fVar1 = *(float *)(param_1 + 0x23c);
      fVar3 = *(float *)(param_1 + 0x20c);
      fVar2 = *(float *)(param_1 + 0x264);
      *(undefined4 *)(this + 0x230) = *(undefined4 *)(param_1 + 0x6f0);
      fVar2 = ((((fVar4 + 320.0) - fVar1) - *(float *)(this + 0x23c)) - fVar3) - fVar2;
      *(float *)(this + 0x22c) = fVar2;
    }
    else {
      fVar3 = *(float *)(param_1 + 600);
      fVar1 = *(float *)(param_1 + 0x23c);
      fVar4 = *(float *)(param_1 + 0x20c);
      fVar2 = *(float *)(param_1 + 0x264);
      *(undefined4 *)(this + 0x230) = *(undefined4 *)(param_1 + 0x6f0);
      fVar2 = fVar3 + 320.0 + fVar1 * 0.5 + fVar4 + fVar2;
      *(float *)(this + 0x22c) = fVar2;
    }
    *(float *)(this + 0x6ec) = fVar2;
    *(undefined4 *)(this + 0x6f0) = *(undefined4 *)(this + 0x230);
  }
  RePosition(this);
  return;
}
