/*
 * mangled: _Z14ObjectTextLoadPcP8cRObject
 * demangled: ObjectTextLoad(char*, cRObject*)
 * address: 0003c7ec
 * size: 1200
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
  int local_244;
  int local_238;
  char *local_234;
  char *local_230;
  char acStack_22c [256];
  char acStack_12c [128];
  char local_ac [128];
  int local_2c;

  local_2c = __stack_chk_guard;
  pcVar6 = (char *)RShellMemoryScratch();
  sprintf(acStack_22c,"%s/_Object.txt",param_1);
  RShellLoadFile(acStack_22c,pcVar6,&local_238);
  local_244 = 0;
  pcVar6[local_238 + -2] = '\0';
  local_ac[0] = '\0';
  cVar1 = *pcVar6;
  iVar17 = 0;
  local_230 = pcVar6;
  do {
    if (cVar1 == '\0') {
      if (local_2c == __stack_chk_guard) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    if (cVar1 == '*') {
      do {
        pcVar6 = local_230;
        local_230 = pcVar6 + 1;
      } while (*local_230 != '\n');
      local_230 = pcVar6 + 2;
    }
    else {
      if (cVar1 == '[') {
        iVar7 = RTextCompStart(local_230,"[VERTEX START]");
        if (iVar7 == 0) {
          iVar7 = RTextCompStart(local_230,"[FACEQUAD START]");
          if (iVar7 != 0) {
            RTextNewLine(&local_230);
            local_234 = local_230;
            while (iVar7 = RTextCompStart(local_234,"[FACEQUAD END]"), iVar7 == 0) {
              local_244 = local_244 + 1;
              RTextNewLine(&local_234);
            }
            cRObject::RequestFaceQuads(param_2,local_244);
            while (iVar7 = RTextCompStart(local_230,"[FACEQUAD END]"), iVar7 == 0) {
              local_234 = local_230;
              iVar7 = RTextExtractInt(&local_234);
              uVar2 = RTextExtractInt(&local_234);
              iVar7 = iVar7 * 0x30;
              uVar3 = RTextExtractInt(&local_234);
              uVar4 = RTextExtractInt(&local_234);
              uVar5 = RTextExtractInt(&local_234);
              uVar8 = RTextExtractFloat(&local_234);
              uVar9 = RTextExtractFloat(&local_234);
              uVar10 = RTextExtractFloat(&local_234);
              uVar11 = RTextExtractFloat(&local_234);
              uVar12 = RTextExtractFloat(&local_234);
              uVar13 = RTextExtractFloat(&local_234);
              uVar14 = RTextExtractFloat(&local_234);
              uVar15 = RTextExtractFloat(&local_234);
              RTextExtractString(&local_234,local_ac);
              RTextAppend(local_ac,".tga");
              RTextCopy(acStack_12c,param_1);
              RTextAppend(acStack_12c,"/");
              RTextAppend(acStack_12c,local_ac);
              iVar18 = *(int *)(param_2 + 200);
              uVar16 = cRTextures::Add((cRTextures *)gTextureList,acStack_12c,(cTgaHeader *)0x0,0);
              *(undefined4 *)(iVar18 + iVar7 + 0xc) = uVar16;
              RTextNewLine(&local_230);
              iVar18 = *(int *)(param_2 + 200);
              *(undefined2 *)(iVar18 + iVar7) = 0;
              ((undefined2 *)(iVar18 + iVar7))[1] = uVar2;
              *(undefined2 *)(*(int *)(param_2 + 200) + iVar7 + 4) = uVar3;
              *(undefined2 *)(*(int *)(param_2 + 200) + iVar7 + 6) = uVar4;
              *(undefined2 *)(*(int *)(param_2 + 200) + iVar7 + 8) = uVar5;
              *(undefined4 *)(*(int *)(param_2 + 200) + iVar7 + 0x10) = uVar8;
              *(undefined4 *)(*(int *)(param_2 + 200) + iVar7 + 0x14) = uVar9;
              *(undefined4 *)(*(int *)(param_2 + 200) + iVar7 + 0x18) = uVar10;
              *(undefined4 *)(*(int *)(param_2 + 200) + iVar7 + 0x1c) = uVar11;
              *(undefined4 *)(*(int *)(param_2 + 200) + iVar7 + 0x20) = uVar12;
              *(undefined4 *)(*(int *)(param_2 + 200) + iVar7 + 0x24) = uVar13;
              *(undefined4 *)(*(int *)(param_2 + 200) + iVar7 + 0x28) = uVar14;
              *(undefined4 *)(*(int *)(param_2 + 200) + iVar7 + 0x2c) = uVar15;
            }
            RTextNewLine(&local_230);
          }
          goto LAB_0003c8bc;
        }
        RTextNewLine(&local_230);
        local_234 = local_230;
        while (iVar7 = RTextCompStart(local_234,"[VERTEX END]"), iVar7 == 0) {
          iVar17 = iVar17 + 1;
          RTextNewLine(&local_234);
        }
        cRObject::RequestVertices(param_2,iVar17);
        while (iVar7 = RTextCompStart(local_230,"[VERTEX END]"), iVar7 == 0) {
          local_234 = local_230;
          iVar7 = RTextExtractInt(&local_234);
          uVar8 = RTextExtractFloat(&local_234);
          uVar9 = RTextExtractFloat(&local_234);
          uVar10 = RTextExtractFloat(&local_234);
          RTextNewLine(&local_230);
          *(undefined4 *)(*(int *)(param_2 + 0xa4) + iVar7 * 0xc) = uVar8;
          *(undefined4 *)(*(int *)(param_2 + 0xa4) + iVar7 * 0xc + 4) = uVar9;
          *(undefined4 *)(*(int *)(param_2 + 0xa4) + iVar7 * 0xc + 8) = uVar10;
        }
      }
      RTextNewLine(&local_230);
    }
LAB_0003c8bc:
    cVar1 = *local_230;
  } while( true );
}
