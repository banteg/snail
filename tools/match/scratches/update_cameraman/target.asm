sub esp, 0x44
push ebx
push ebp
mov ebp, ecx
push esi
push edi
push 0x3f800000
mov eax, dword [ebp+0xc0]
mov byte [ebp+0xcc], 0x0
push 0xbf000000
push 0x3fe66666
fld dword [eax+0x2964]
fmul dword [ADDR]
push ecx
lea ecx, dword [esp+0x24]
lea ebx, dword [ebp+0x40]
fstp dword [esp]
push 0x0
push 0x3f722d1f
push 0xbea5f890
push 0x0
push 0x0
push 0x3ea5f890
push 0x3f722d1f
push 0x0
push 0x0
push 0x0
push 0x0
push 0x3f800000
call ADDR
mov ecx, 0x10
mov esi, eax
mov edi, ebx
rep movsd dword [edi], dword [esi]
mov ecx, ebx
call ADDR
mov edx, dword [ebp+0xc4]
mov ecx, dword [ebp+0xc0]
fild dword [edx+0x50]
fcom dword [ecx+0x296c]
fnstsw ax
test ah, 0x41
jne L122
fdivr dword [ecx+0x296c]
fmul dword [ADDR]
fsub dword [ADDR]
fcom dword [ADDR]
fnstsw ax
test ah, 0x1
je Lc3
fstp st(0)
fld dword [ADDR]
jmp Ld8
fcom dword [ADDR]
fnstsw ax
test ah, 0x41
jne Ld8
fstp st(0)
fld dword [ADDR]
fld dword [ADDR]
fsub st(1)
push ecx
fst dword [esp+0x14]
fmul dword [ecx+0x2968]
fmul dword [ADDR]
fadd dword [ebp+0x74]
fst dword [ebp+0x74]
fxch st(0), st(1)
fmul dword [ADDR]
fmul dword [ecx+0x2968]
mov ecx, ebx
fadd st(1)
fstp dword [ebp+0x74]
fstp st(0)
fld dword [esp+0x14]
fmul dword [ADDR]
fstp dword [esp]
call ADDR
jmp L136
fstp st(0)
fld dword [ecx+0x2968]
fmul dword [ADDR]
fadd dword [ebp+0x74]
fstp dword [ebp+0x74]
mov ecx, dword [ebp+0xc0]
cmp byte [ecx+0x384], 0x1
jne L1e1
mov edx, dword [ecx+0x388]
mov eax, dword [edx+0x38]
cmp eax, 0x10
je L17a
cmp eax, 0x8
je L17a
cmp eax, 0x9
je L17a
cmp eax, 0xa
je L17a
cmp eax, 0x2b
je L17a
cmp eax, 0x2d
je L17a
cmp eax, 0x24
je L17a
cmp eax, 0xe
jne L1e1
mov eax, dword [ecx+0x38c]
fld dword [ecx+0x70]
fsub dword [eax+0x18]
fdiv dword [edx+0x4c]
fcom dword [ADDR]
fnstsw ax
test ah, 0x1
je L1a0
fstp st(0)
fld dword [ADDR]
jmp L1b5
fcom dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1b5
fstp st(0)
fld dword [ADDR]
fmul dword [ADDR]
push ecx
fstp dword [esp]
call ADDR
fmul dword [ADDR]
add esp, 0x4
fsubr dword [ADDR]
fmul dword [ADDR]
fstp dword [ebp+0xd0]
jmp L1eb
mov dword [ebp+0xd0], 0x0
mov ecx, dword [ebp+0xc0]
fld dword [ecx+0x2dc]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L240
fld dword [ecx+0x2dc]
fmul dword [ADDR]
push ecx
fadd dword [ADDR]
fstp dword [esp]
call ADDR
fmul dword [ADDR]
add esp, 0x4
fsubr dword [ADDR]
fmul dword [ADDR]
fadd dword [ebp+0xd0]
fstp dword [ebp+0xd0]
fld dword [ebp+0xd0]
fsub dword [ebp+0xd4]
mov ecx, dword [ebp+0xc0]
fmul dword [ADDR]
fadd dword [ebp+0xd4]
fst dword [ebp+0xd4]
fmul dword [ecx+0x2968]
fadd dword [ebp+0x74]
fstp dword [ebp+0x74]
fld dword [ecx+0x2964]
fmul dword [ADDR]
fadd dword [ebp+0x70]
fstp dword [ebp+0x70]
fld dword [ecx+0x296c]
fadd dword [ebp+0x78]
fadd dword [ADDR]
fst dword [ebp+0x78]
fld st(0)
fsub dword [ebp+0xb8]
fcom dword [ADDR]
fnstsw ax
test ah, 0x41
jne L2b9
fstp st(0)
fsub dword [ADDR]
fstp dword [ebp+0xb8]
jmp L2d6
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L2d4
fsub dword [ADDR]
fstp dword [ebp+0xb8]
jmp L2d6
fstp st(0)
fld dword [ecx+0x2968]
fsub dword [ADDR]
fmul dword [ADDR]
fsubr dword [ADDR]
fmul dword [ADDR]
fst dword [esp+0x10]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L30f
mov dword [esp+0x10], 0xbf9c5a1c
jmp L328
fld dword [esp+0x10]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L328
mov dword [esp+0x10], 0x3f9c5a1c
mov ecx, dword [esp+0x10]
push ecx
mov ecx, ebx
call ADDR
mov esi, dword [ebp+0xc0]
push ecx
mov edx, esi
fld dword [edx+0x358]
fmul dword [ADDR]
fstp dword [esp]
call ADDR
fmul dword [ADDR]
mov ecx, ebx
fsubr dword [ADDR]
fmul dword [esi+0x354]
fmul dword [ADDR]
fld dword [esi+0x2964]
fmul dword [ADDR]
fmul dword [ADDR]
fmul dword [ADDR]
faddp st(1)
fstp dword [esp]
call ADDR
mov eax, dword [ebp+0xc0]
cmp byte [eax+0x384], 0x1
jne L3db
lea ecx, dword [esp+0x14]
call ADDR
mov ecx, dword [ebp+0xc0]
mov edx, dword [ecx+0x39c]
lea ecx, dword [esp+0x14]
push edx
call ADDR
lea eax, dword [esp+0x14]
mov ecx, ebx
push eax
call ADDR
mov ecx, dword [ebp+0xc0]
mov edx, dword [ecx+0x3a0]
mov ecx, ebx
push edx
call ADDR
mov eax, dword [ebp+0xc0]
mov cl, byte [eax+0x41d]
test cl, cl
je L3f9
mov eax, dword [eax+0x42c]
mov ecx, ebx
push eax
call ADDR
mov ecx, dword [ebp+0xc0]
mov edx, dword [ecx+0x370]
mov ecx, ebx
push edx
call ADDR
mov eax, dword [ebp+0xc0]
cmp byte [eax+0x384], 0x1
jne L4a9
mov ecx, dword [eax+0x388]
cmp dword [ecx+0x38], 0x18
jne L4a9
mov edx, dword [eax+0x38c]
fld dword [eax+0x70]
fsub dword [edx+0x18]
fdiv dword [ecx+0x4c]
fcom dword [ADDR]
fnstsw ax
test ah, 0x1
je L452
fstp st(0)
fld dword [ADDR]
jmp L467
fcom dword [ADDR]
fnstsw ax
test ah, 0x41
jne L467
fstp st(0)
fld dword [ADDR]
fmul dword [ADDR]
push ecx
fstp dword [esp]
call ADDR
fmul dword [ADDR]
push ecx
fsubr dword [ADDR]
fst dword [esp+0x18]
fstp qword [esp]
push ADDR
call ADDR
fld dword [esp+0x1c]
fmul dword [ADDR]
add esp, 0xc
fadd dword [ADDR]
jmp L4af
fld dword [ADDR]
fsub dword [ebp+0xc8]
mov eax, dword [ebp+0xc4]
push ecx
lea edi, dword [ebp+0x80]
mov ecx, ebp
fmul dword [ADDR]
fadd dword [ebp+0xc8]
fstp dword [ebp+0xc8]
fld dword [eax+0x38]
fmul dword [ADDR]
fstp dword [esp]
push ebx
push edi
call ADDR
mov ecx, 0x10
mov esi, ebx
rep movsd dword [edi], dword [esi]
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x44
ret
