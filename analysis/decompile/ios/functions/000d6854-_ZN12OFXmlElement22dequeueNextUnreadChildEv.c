/*
 * mangled: _ZN12OFXmlElement22dequeueNextUnreadChildEv
 * demangled: OFXmlElement::dequeueNextUnreadChild()
 * address: 000d6854
 * size: 120
 */

/* OFXmlElement::dequeueNextUnreadChild() */

void OFXmlElement::dequeueNextUnreadChild(void)

{
  int iVar1;
  int *in_r0;
  int in_r1;
  int iVar2;
  int iVar3;
  int *piVar4;

  piVar4 = *(int **)(in_r1 + 0x10);
  iVar1 = *(int *)(in_r1 + 0x14) - (int)piVar4 >> 2;
  if (iVar1 != 0) {
    iVar3 = *piVar4;
    if (*(char *)(iVar3 + 0x20) != '\0') {
      iVar2 = 0;
      do {
        iVar2 = iVar2 + 1;
        if (iVar2 == iVar1) goto LAB_000d68a4;
        iVar3 = piVar4[iVar2];
      } while (*(char *)(iVar3 + 0x20) != '\0');
    }
    *(undefined1 *)(iVar3 + 0x20) = 1;
    *in_r0 = iVar3;
    *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1;
    return;
  }
LAB_000d68a4:
  *in_r0 = 0;
  return;
}
