/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_jet_particles @ 0x43a580 */
/* selector: uninit_jet_particles */

void __thiscall sub_43A580(int *this)
{
  int *v1; // esi
  int v2; // ebx
  int v3; // edi

  v1 = this + 8;
  v2 = 15;
  do
  {
    v3 = 2;
    do
    {
      kill_sprite(*v1);
      v1 += 4;
      --v3;
    }
    while ( v3 );
    --v2;
  }
  while ( v2 );
}

