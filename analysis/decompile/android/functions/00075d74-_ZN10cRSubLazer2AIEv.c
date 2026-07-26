/*
 * mangled: _ZN10cRSubLazer2AIEv
 * demangled: cRSubLazer::AI()
 * address: 00075d74
 * size: 632
 */

/* cRSubLazer::AI() */

void __thiscall cRSubLazer::AI(cRSubLazer *this)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  float fVar4;
  float fVar5;

  if (*(char *)(*(int *)(this + 0x7c) + 0x19) == '\0') {
    if (*(int *)(this + 0x74) == 1) {
      fVar4 = *(float *)(this + 0x8c);
      *(float *)(this + 0x8c) = fVar4 + *(float *)(this + 0x90);
      if (fVar4 + *(float *)(this + 0x90) <= 1.0) {
        fVar5 = *(float *)(this + 0x60);
        fVar4 = *(float *)(this + 100);
        *(float *)(this + 0x60) = fVar5 + *(float *)(this + 0x84);
        *(float *)(this + 0x5c) = *(float *)(this + 0x5c) + *(float *)(this + 0x80);
        *(float *)(this + 100) = fVar4 + *(float *)(this + 0x88);
        if ((0.0 <= fVar5 + *(float *)(this + 0x84)) &&
           (*(float *)((int)DWORD_ARRAY_000110f8 + *(int *)(this + 0x7c) + 0x11c8) <=
            fVar4 + *(float *)(this + 0x88))) {
          iVar1 = cRSubGame::LocFromPos
                            (Game + 0x718a0,*(undefined4 *)(this + 0x5c),
                             *(undefined4 *)(this + 0x60),*(undefined4 *)(this + 100));
          puVar2 = (uint *)cRSubGame::RowFromPos
                                     (Game + 0x718a0,*(undefined4 *)(this + 0x5c),
                                      *(undefined4 *)(this + 0x60),*(undefined4 *)(this + 100));
          if ((*(char *)(iVar1 + 0x30) == '\x0e') && (*(float *)(this + 0x60) < 7.0)) {
LAB_00075f0c:
            Kill(this);
            return;
          }
          uVar3 = *puVar2;
          if ((uVar3 & 0x40) != 0) {
            iVar1 = cRPath::SearchPos(*(cRPath **)(puVar2[0x26] + 0x2c),
                                      *(float *)(this + 0x5c) + *(float *)(this + 0x80),
                                      *(float *)(this + 0x60) + *(float *)(this + 0x84),
                                      *(float *)(this + 100) + *(float *)(this + 0x88),
                                      *(float *)(this + 0x80) * 1.05,*(float *)(this + 0x84) * 1.05,
                                      *(float *)(this + 0x88) * 1.05,puVar2[0x26]);
            if (iVar1 != 0) goto LAB_00075f0c;
            uVar3 = *puVar2;
          }
          if ((uVar3 & 0x80) == 0) {
            return;
          }
          iVar1 = cRPath::SearchPos(*(cRPath **)(puVar2[0x27] + 0x2c),
                                    *(float *)(this + 0x5c) + *(float *)(this + 0x80),
                                    *(float *)(this + 0x60) + *(float *)(this + 0x84),
                                    *(float *)(this + 100) + *(float *)(this + 0x88),
                                    *(float *)(this + 0x80) * 1.05,*(float *)(this + 0x84) * 1.05,
                                    *(float *)(this + 0x88) * 1.05,puVar2[0x27]);
          if (iVar1 == 0) {
            return;
          }
        }
        Kill(this);
        return;
      }
      *(undefined4 *)(this + 0x74) = 2;
    }
    else if (*(int *)(this + 0x74) == 2) {
      cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)this);
      *(undefined4 *)(this + 0x74) = 0;
    }
  }
  return;
}
