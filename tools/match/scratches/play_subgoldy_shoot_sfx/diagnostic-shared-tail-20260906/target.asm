0000  sub esp, 0x1c
0003  push esi
0004  mov esi, ecx
0006  push edi
0007  mov eax, dword [esi+0x338]
000d  test al, 0x7
000f  je L34
0011  call ADDR
0016  mov dword [esp+0x8], eax
001a  fild dword [esp+0x8]
001e  fmul dword [ADDR]
0024  call ADDR
0029  mov dword [esi+0x1cc], eax
002f  lea edi, dword [eax+0x11]
0032  jmp L84
0034  test al, 0x18
0036  je L5b
0038  call ADDR
003d  mov dword [esp+0x8], eax
0041  fild dword [esp+0x8]
0045  fmul dword [ADDR]
004b  call ADDR
0050  mov dword [esi+0x1cc], eax
0056  lea edi, dword [eax+0x13]
0059  jmp L84
005b  test al, 0x60
005d  je L149
0063  call ADDR
0068  mov dword [esp+0x8], eax
006c  fild dword [esp+0x8]
0070  fmul dword [ADDR]
0076  call ADDR
007b  mov dword [esi+0x1cc], eax
0081  lea edi, dword [eax+0x16]
0084  cmp edi, -0x1
0087  je L149
008d  mov al, byte [esi+0x41d]
0093  test al, al
0095  je L13e
009b  mov eax, dword [ADDR]
00a0  fld dword [eax+0x18c]
00a6  fsub dword [esi+0x68]
00a9  fstp dword [esp+0xc]
00ad  fld dword [eax+0x190]
00b3  fsub dword [esi+0x6c]
00b6  fstp dword [esp+0x10]
00ba  fld dword [eax+0x194]
00c0  fsub dword [esi+0x70]
00c3  mov ecx, dword [esp+0x10]
00c7  mov eax, dword [esp+0xc]
00cb  mov dword [esp+0x1c], ecx
00cf  lea ecx, dword [esp+0x18]
00d3  mov dword [esp+0x18], eax
00d7  fstp dword [esp+0x14]
00db  mov edx, dword [esp+0x14]
00df  mov dword [esp+0x20], edx
00e3  call ADDR
00e8  fmul dword [ADDR]
00ee  fsubr dword [ADDR]
00f4  fst dword [esp+0x8]
00f8  fcomp dword [ADDR]
00fe  fnstsw ax
0100  test ah, 0x1
0103  je L10f
0105  mov dword [esp+0x8], 0x0
010d  jmp L128
010f  fld dword [esp+0x8]
0113  fcomp dword [ADDR]
0119  fnstsw ax
011b  test ah, 0x41
011e  jne L128
0120  mov dword [esp+0x8], 0x3f800000
0128  mov eax, dword [esp+0x8]
012c  mov ecx, ADDR
0131  push eax
0132  push edi
0133  call ADDR
0138  pop edi
0139  pop esi
013a  add esp, 0x1c
013d  ret
013e  push edi
013f  mov ecx, ADDR
0144  call ADDR
0149  pop edi
014a  pop esi
014b  add esp, 0x1c
014e  ret
