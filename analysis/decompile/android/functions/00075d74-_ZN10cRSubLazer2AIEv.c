/*
 * mangled: _ZN10cRSubLazer2AIEv
 * demangled: cRSubLazer::AI()
 * address: 00075d74
 * size: 632
 */

/* cRSubLazer::AI() */

void __thiscall cRSubLazer::AI(cRSubLazer *this)

{
  uint *puVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  float fVar5;
  float fVar6;

  fVar5 = DAT_00075fec;
  iVar4 = DAT_00075ff8 + 0x75d90;
  if (*(char *)(*(int *)(this + 0x7c) + 0x19) == '\0') {
    if (*(int *)(this + 0x74) == 1) {
      fVar6 = *(float *)(this + 0x8c);
      *(float *)(this + 0x8c) = fVar6 + *(float *)(this + 0x90);
      if (fVar6 + *(float *)(this + 0x90) <= fVar5) {
        fVar6 = *(float *)(this + 0x60);
        fVar5 = *(float *)(this + 100);
        *(float *)(this + 0x60) = fVar6 + *(float *)(this + 0x84);
        *(float *)(this + 0x5c) = *(float *)(this + 0x5c) + *(float *)(this + 0x80);
        *(float *)(this + 100) = fVar5 + *(float *)(this + 0x88);
        if ((0.0 <= fVar6 + *(float *)(this + 0x84)) &&
           (*(float *)((int)DWORD_ARRAY_000110f8 + *(int *)(this + 0x7c) + 0x11c8) <=
            fVar5 + *(float *)(this + 0x88))) {
          piVar3 = *(int **)(iVar4 + DAT_00075ffc);
          iVar4 = cRSubGame::LocFromPos
                            (*piVar3 + 0x718a0,*(undefined4 *)(this + 0x5c),
                             *(undefined4 *)(this + 0x60),*(undefined4 *)(this + 100));
          puVar1 = (uint *)cRSubGame::RowFromPos
                                     (*piVar3 + 0x718a0,*(undefined4 *)(this + 0x5c),
                                      *(undefined4 *)(this + 0x60),*(undefined4 *)(this + 100));
          if ((*(char *)(iVar4 + 0x30) == '\x0e') && (*(float *)(this + 0x60) < DAT_00075ff4)) {
LAB_00075f0c:
            Kill(this);
            return;
          }
          uVar2 = *puVar1;
          if ((uVar2 & 0x40) != 0) {
            iVar4 = cRPath::SearchPos(*(cRPath **)(puVar1[0x26] + 0x2c),
                                      *(float *)(this + 0x5c) + *(float *)(this + 0x80),
                                      *(float *)(this + 0x60) + *(float *)(this + 0x84),
                                      *(float *)(this + 100) + *(float *)(this + 0x88),
                                      *(float *)(this + 0x80) * DAT_00075ff0,
                                      *(float *)(this + 0x84) * DAT_00075ff0,
                                      *(float *)(this + 0x88) * DAT_00075ff0,puVar1[0x26]);
            if (iVar4 != 0) goto LAB_00075f0c;
            uVar2 = *puVar1;
          }
          if ((uVar2 & 0x80) == 0) {
            return;
          }
          iVar4 = cRPath::SearchPos(*(cRPath **)(puVar1[0x27] + 0x2c),
                                    *(float *)(this + 0x5c) + *(float *)(this + 0x80),
                                    *(float *)(this + 0x60) + *(float *)(this + 0x84),
                                    *(float *)(this + 100) + *(float *)(this + 0x88),
                                    *(float *)(this + 0x80) * DAT_00075ff0,
                                    *(float *)(this + 0x84) * DAT_00075ff0,
                                    *(float *)(this + 0x88) * DAT_00075ff0,puVar1[0x27]);
          if (iVar4 == 0) {
            return;
          }
        }
        Kill(this);
        return;
      }
      *(undefined4 *)(this + 0x74) = 2;
    }
    else if (*(int *)(this + 0x74) == 2) {
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(**(int **)(iVar4 + DAT_00075ffc) + 0x358),(cRBod *)this);
      *(undefined4 *)(this + 0x74) = 0;
    }
  }
  return;
}
