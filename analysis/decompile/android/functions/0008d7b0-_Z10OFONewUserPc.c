/*
 * mangled: _Z10OFONewUserPc
 * demangled: OFONewUser(char*)
 * address: 0008d7b0
 * size: 88
 */

/* OFONewUser(char*) */

void OFONewUser(char *param_1)

{
  strcpy(gOFUser,param_1);
  wprintf(":OF New User %s",gOFUser);
  strcpy(gConfig + 0xf0,gOFUser);
  gOFOLoadFlag = 1;
  return;
}
