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
005d  je L16c
0063  call ADDR
0068  mov dword [esp+0x8], eax
006c  fild dword [esp+0x8]
0070  fmul dword [ADDR]
0076  call ADDR
007b  mov dword [esi+0x1cc], eax
0081  lea edi, dword [eax+0x16]
0084  cmp edi, -0x1
0087  je L16c
008d  mov dl, byte [esi+0x41d]
0093  xor eax, eax
0095  test dl, dl
0097  setne al
009a  sub eax, 0x0
009d  je L161
00a3  dec eax
00a4  jne L16c
00aa  mov eax, dword [ADDR]
00af  fld dword [eax+0x18c]
00b5  fsub dword [esi+0x68]
00b8  fstp dword [esp+0xc]
00bc  fld dword [eax+0x190]
00c2  fsub dword [esi+0x6c]
00c5  fstp dword [esp+0x10]
00c9  fld dword [eax+0x194]
00cf  fsub dword [esi+0x70]
00d2  mov ecx, dword [esp+0x10]
00d6  mov eax, dword [esp+0xc]
00da  mov dword [esp+0x1c], ecx
00de  lea ecx, dword [esp+0x18]
00e2  mov dword [esp+0x18], eax
00e6  fstp dword [esp+0x14]
00ea  mov edx, dword [esp+0x14]
00ee  mov dword [esp+0x20], edx
00f2  call ADDR
00f7  fmul dword [ADDR]
00fd  fsubr dword [ADDR]
0103  fst dword [esp+0x8]
0107  fcomp dword [ADDR]
010d  fnstsw ax
010f  test ah, 0x1
0112  je L132
0114  mov dword [esp+0x8], 0x0
011c  mov ecx, ADDR
0121  mov eax, dword [esp+0x8]
0125  push eax
0126  push edi
0127  call ADDR
012c  pop edi
012d  pop esi
012e  add esp, 0x1c
0131  ret
0132  fld dword [esp+0x8]
0136  fcomp dword [ADDR]
013c  fnstsw ax
013e  test ah, 0x41
0141  jne L14b
0143  mov dword [esp+0x8], 0x3f800000
014b  mov eax, dword [esp+0x8]
014f  mov ecx, ADDR
0154  push eax
0155  push edi
0156  call ADDR
015b  pop edi
015c  pop esi
015d  add esp, 0x1c
0160  ret
0161  push edi
0162  mov ecx, ADDR
0167  call ADDR
016c  pop edi
016d  pop esi
016e  add esp, 0x1c
0171  ret
