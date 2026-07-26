/*
 * mangled: _Z14ObjectTextLoadPcP8cRObject
 * demangled: ObjectTextLoad(char*, cRObject*)
 * address: 00016b78
 * size: 1016
 */

/* ObjectTextLoad(char*, cRObject*) */

void ObjectTextLoad(char *param_1,cRObject *param_2)

{
  char cVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  char *pcVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  int iVar17;
  int iVar18;
  int local_25c;
  char acStack_22c [256];
  char acStack_12c [128];
  char local_ac [128];
  int local_2c;
  char *local_28;
  char *local_24;

  pcVar6 = (char *)RShellMemoryScratch();
  _sprintf(acStack_22c,"%s/_Object.txt",param_1);
  RShellLoadFile(acStack_22c,pcVar6,&local_2c);
  iVar18 = 0;
  pcVar6[local_2c + -2] = '\0';
  local_ac[0] = '\0';
  local_25c = 0;
  local_24 = pcVar6;
LAB_00016bd8:
  do {
    cVar1 = *local_24;
    while( true ) {
      if (cVar1 == '\0') {
        return;
      }
      if (cVar1 == '*') break;
      if (cVar1 == '[') {
        iVar7 = RTextCompStart(local_24,"[VERTEX START]");
        if (iVar7 == 0) {
          iVar7 = RTextCompStart(local_24,"[FACEQUAD START]");
          if (iVar7 == 0) goto LAB_00016bd8;
          RTextNewLine(&local_24);
          local_28 = local_24;
          while (iVar7 = RTextCompStart(local_28,"[FACEQUAD END]"), iVar7 == 0) {
            local_25c = local_25c + 1;
            RTextNewLine(&local_28);
          }
          cRObject::RequestFaceQuads(param_2,local_25c);
          while (iVar7 = RTextCompStart(local_24,"[FACEQUAD END]"), iVar7 == 0) {
            local_28 = local_24;
            iVar7 = RTextExtractInt(&local_28);
            uVar2 = RTextExtractInt(&local_28);
            uVar3 = RTextExtractInt(&local_28);
            uVar4 = RTextExtractInt(&local_28);
            uVar5 = RTextExtractInt(&local_28);
            uVar8 = RTextExtractFloat(&local_28);
            uVar9 = RTextExtractFloat(&local_28);
            uVar10 = RTextExtractFloat(&local_28);
            uVar11 = RTextExtractFloat(&local_28);
            uVar12 = RTextExtractFloat(&local_28);
            uVar13 = RTextExtractFloat(&local_28);
            uVar14 = RTextExtractFloat(&local_28);
            uVar15 = RTextExtractFloat(&local_28);
            RTextExtractString(&local_28,local_ac);
            RTextAppend(local_ac,".tga");
            RTextCopy(acStack_12c,param_1);
            RTextAppend(acStack_12c,"/");
            RTextAppend(acStack_12c,local_ac);
            iVar7 = iVar7 * 0x30;
            iVar17 = *(int *)(param_2 + 200);
            uVar16 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,acStack_12c,
                                     (cTgaHeader *)0x0,0);
            *(undefined4 *)(iVar7 + iVar17 + 0xc) = uVar16;
            RTextNewLine(&local_24);
            *(undefined2 *)(iVar7 + *(int *)(param_2 + 200)) = 0;
            *(undefined2 *)(iVar7 + *(int *)(param_2 + 200) + 2) = uVar2;
            *(undefined2 *)(iVar7 + *(int *)(param_2 + 200) + 4) = uVar3;
            *(undefined2 *)(iVar7 + *(int *)(param_2 + 200) + 6) = uVar4;
            *(undefined2 *)(iVar7 + *(int *)(param_2 + 200) + 8) = uVar5;
            *(undefined4 *)(iVar7 + *(int *)(param_2 + 200) + 0x10) = uVar8;
            *(undefined4 *)(iVar7 + *(int *)(param_2 + 200) + 0x14) = uVar9;
            *(undefined4 *)(iVar7 + *(int *)(param_2 + 200) + 0x18) = uVar10;
            *(undefined4 *)(iVar7 + *(int *)(param_2 + 200) + 0x1c) = uVar11;
            *(undefined4 *)(iVar7 + *(int *)(param_2 + 200) + 0x20) = uVar12;
            *(undefined4 *)(iVar7 + *(int *)(param_2 + 200) + 0x24) = uVar13;
            *(undefined4 *)(iVar7 + *(int *)(param_2 + 200) + 0x28) = uVar14;
            *(undefined4 *)(iVar7 + *(int *)(param_2 + 200) + 0x2c) = uVar15;
          }
        }
        else {
          RTextNewLine(&local_24);
          local_28 = local_24;
          while (iVar7 = RTextCompStart(local_28,"[VERTEX END]"), iVar7 == 0) {
            RTextNewLine(&local_28);
            iVar18 = iVar18 + 1;
          }
          cRObject::RequestVertices(param_2,iVar18);
          while (iVar7 = RTextCompStart(local_24,"[VERTEX END]"), iVar7 == 0) {
            local_28 = local_24;
            iVar7 = RTextExtractInt(&local_28);
            uVar8 = RTextExtractFloat(&local_28);
            uVar9 = RTextExtractFloat(&local_28);
            uVar10 = RTextExtractFloat(&local_28);
            RTextNewLine(&local_24);
            iVar7 = iVar7 * 0xc;
            *(undefined4 *)(*(int *)(param_2 + 0xa4) + iVar7) = uVar8;
            *(undefined4 *)(iVar7 + *(int *)(param_2 + 0xa4) + 4) = uVar9;
            *(undefined4 *)(iVar7 + *(int *)(param_2 + 0xa4) + 8) = uVar10;
          }
        }
      }
      RTextNewLine(&local_24);
      cVar1 = *local_24;
    }
    do {
      pcVar6 = local_24;
      local_24 = pcVar6 + 1;
    } while (*local_24 != '\n');
    local_24 = pcVar6 + 2;
  } while( true );
}
