/*
 * mangled: _Z12PngLoadImagePcPS_PiS1_S1_
 * demangled: PngLoadImage(char*, char**, int*, int*, int*)
 * address: 00009c00
 * size: 336
 */

/* PngLoadImage(char*, char**, int*, int*, int*) */

void PngLoadImage(char *param_1,char **param_2,int *param_3,int *param_4,int *param_5)

{
  ID IVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  uint in_fpscr;
  char acStack_130 [256];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;

  MacGetFileName(param_1,acStack_130);
  IVar1 = NSString::stringWithUTF8String_
                    ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",acStack_130);
  IVar1 = UIImage::imageWithContentsOfFile_
                    ((ID)&_OBJC_CLASS___UIImage,"imageWithContentsOfFile:",IVar1);
  IVar1 = UIImage::CGImage(IVar1,"CGImage");
  iVar2 = _CGImageGetWidth();
  iVar3 = _CGImageGetHeight(IVar1);
  pcVar4 = _malloc(iVar3 * iVar2 * 4);
  uVar5 = _CGImageGetColorSpace(IVar1);
  uVar5 = _CGBitmapContextCreate(pcVar4,iVar2,iVar3,8,iVar2 << 2,uVar5,1);
  local_30 = 0;
  local_2c = 0;
  local_28 = VectorUnsignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
  local_24 = VectorUnsignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
  _CGContextDrawImage(uVar5,0,0,local_28,local_24,IVar1);
  _CGContextRelease(uVar5);
  _printf("Png %s=%ix%i\n",param_1,iVar2,iVar3);
  *param_3 = iVar2;
  *param_4 = iVar3;
  *param_5 = 4;
  *param_2 = pcVar4;
  return;
}
