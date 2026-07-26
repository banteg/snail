/*
 * mangled: _Z15ObjectProcMovieP7cRMoviePci
 * demangled: ObjectProcMovie(cRMovie*, char*, int)
 * address: 0003ba24
 * size: 796
 */

/* ObjectProcMovie(cRMovie*, char*, int) */

void ObjectProcMovie(cRMovie *param_1,char *param_2,int param_3)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined2 *puVar8;
  int iVar9;
  char *local_264;
  char *local_260;
  char *local_25c;
  char cStack_237;
  char local_236;
  char local_235;
  char local_234;
  char local_233 [511];
  int local_34;

  local_34 = __stack_chk_guard;
  strcpy(&local_234,param_2);
  pcVar3 = &local_234;
  if (local_234 == '.') {
    local_264 = &cStack_237;
    local_25c = &local_235;
    local_260 = &local_236;
  }
  else {
    do {
      local_25c = pcVar3;
      pcVar3 = local_25c + 1;
    } while (local_25c[1] != '.');
    local_264 = local_25c + -2;
    local_260 = local_25c + -1;
  }
  iVar7 = 0;
  do {
    iVar9 = iVar7;
    *local_264 = (char)(iVar9 / 100) + '0';
    cVar1 = (char)(iVar9 / 10);
    *local_260 = cVar1 + (char)((iVar9 / 10) / 10) * -10 + '0';
    *local_25c = (char)iVar9 + cVar1 * -10 + '0';
    iVar4 = RShellFindFile(&local_234,false);
    iVar7 = iVar9 + 1;
  } while (iVar4 != 0);
  if (iVar9 == 0) {
    RShellError("Cannot find movie frames\n");
  }
  else {
    cRObject::RequestVertices((cRObject *)param_1,4);
    puVar6 = *(undefined4 **)(param_1 + 0xa4);
    puVar6[2] = 0;
    puVar6[1] = 0x42c80000;
    *puVar6 = 0x42480000;
    iVar7 = *(int *)(param_1 + 0xa4);
    *(undefined4 *)(iVar7 + 0xc) = 0xc2480000;
    *(undefined4 *)(iVar7 + 0x10) = 0x42c80000;
    *(undefined4 *)(iVar7 + 0x14) = 0;
    iVar7 = *(int *)(param_1 + 0xa4);
    *(undefined4 *)(iVar7 + 0x18) = 0xc2480000;
    *(undefined4 *)(iVar7 + 0x1c) = 0;
    *(undefined4 *)(iVar7 + 0x20) = 0;
    iVar7 = *(int *)(param_1 + 0xa4);
    *(undefined4 *)(iVar7 + 0x24) = 0x42480000;
    *(undefined4 *)(iVar7 + 0x28) = 0;
    *(undefined4 *)(iVar7 + 0x2c) = 0;
    cRObject::RequestFaceQuads((cRObject *)param_1,iVar9);
    iVar7 = 0;
    puVar8 = *(undefined2 **)(param_1 + 200);
    do {
      *(undefined4 *)(puVar8 + 8) = 0x3f800000;
      *(undefined4 *)(puVar8 + 10) = 0x3f800000;
      *(undefined4 *)(puVar8 + 0xc) = 0;
      *(undefined4 *)(puVar8 + 0xe) = 0x3f800000;
      *(undefined4 *)(puVar8 + 0x10) = 0;
      *(undefined4 *)(puVar8 + 0x12) = 0;
      *(undefined4 *)(puVar8 + 0x14) = 0x3f800000;
      *(undefined4 *)(puVar8 + 0x16) = 0;
      puVar8[1] = 0;
      puVar8[3] = 2;
      puVar8[4] = 3;
      puVar8[2] = 1;
      *puVar8 = 0;
      *local_264 = (char)(iVar7 / 100) + '0';
      cVar2 = (char)(iVar7 / 10);
      cVar1 = (char)iVar7;
      *local_260 = cVar2 + (char)((iVar7 / 10) / 10) * -10 + '0';
      iVar7 = iVar7 + 1;
      *local_25c = cVar1 + cVar2 * -10 + '0';
      piVar5 = (int *)cRTextures::Add((cRTextures *)gTextureList,&local_234,(cTgaHeader *)0x0,0);
      *(int **)(puVar8 + 6) = piVar5;
      *piVar5 = param_3;
      puVar8 = puVar8 + 0x18;
    } while (iVar7 < iVar9);
    *(undefined4 *)(param_1 + 0x11c) = 0;
    *(undefined4 *)(param_1 + 0x118) = 0;
    *(undefined4 *)(param_1 + 0x110) = 1;
    *(undefined4 *)(param_1 + 0x114) = 0;
    wprintf("Movie %s Frames %i\n",param_2,iVar9);
  }
  if (local_34 != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
