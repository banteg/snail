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
005d  je L145
0063  call ADDR
0068  mov dword [esp+0x8], eax
006c  fild dword [esp+0x8]
0070  fmul dword [ADDR]
0076  call ADDR
007b  mov dword [esi+0x1cc], eax
0081  lea edi, dword [eax+0x16]
0084  cmp edi, -0x1
0087  je L145
008d  mov al, byte [esi+0x41d]
0093  test al, al
0095  jne La8
0097  push edi
0098  mov ecx, ADDR
009d  call ADDR
00a2  pop edi
00a3  pop esi
00a4  add esp, 0x1c
00a7  ret
00a8  mov eax, dword [ADDR]
00ad  fld dword [eax+0x18c]
00b3  fsub dword [esi+0x68]
00b6  fstp dword [esp+0xc]
00ba  fld dword [eax+0x190]
00c0  fsub dword [esi+0x6c]
00c3  fstp dword [esp+0x10]
00c7  fld dword [eax+0x194]
00cd  fsub dword [esi+0x70]
00d0  mov ecx, dword [esp+0x10]
00d4  mov eax, dword [esp+0xc]
00d8  mov dword [esp+0x1c], ecx
00dc  lea ecx, dword [esp+0x18]
00e0  mov dword [esp+0x18], eax
00e4  fstp dword [esp+0x14]
00e8  mov edx, dword [esp+0x14]
00ec  mov dword [esp+0x20], edx
00f0  call ADDR
00f5  fmul dword [ADDR]
00fb  fsubr dword [ADDR]
0101  fst dword [esp+0x8]
0105  fcomp dword [ADDR]
010b  fnstsw ax
010d  test ah, 0x1
0110  je L11c
0112  mov dword [esp+0x8], 0x0
011a  jmp L135
011c  fld dword [esp+0x8]
0120  fcomp dword [ADDR]
0126  fnstsw ax
0128  test ah, 0x41
012b  jne L135
012d  mov dword [esp+0x8], 0x3f800000
0135  mov eax, dword [esp+0x8]
0139  mov ecx, ADDR
013e  push eax
013f  push edi
0140  call ADDR
0145  pop edi
0146  pop esi
0147  add esp, 0x1c
014a  ret
