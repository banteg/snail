sub esp, 0x74
push ebx
push ebp
push esi
mov esi, ecx
push edi
mov al, byte [esi+0x41d]
test al, al
jne L672
mov al, byte [esi+0x41c]
test al, al
jne L672
mov al, byte [esi+0x2d8]
test al, al
jne L672
mov al, byte [esi+0x338]
mov bl, 0x80
test bl, al
jne L129
xor edi, edi
mov eax, dword [esi+0x408]
mov ebp, 0x1
add eax, edi
cmp dword [eax+0x357940], ebp
jne L115
cmp byte [eax+0x357954], 0x1
jne L115
fld dword [eax+0x357928]
fsub dword [esi+0x2964]
fstp dword [esp+0x30]
fld dword [eax+0x35792c]
fsub dword [esi+0x2968]
mov ecx, dword [esp+0x30]
fstp dword [esp+0x34]
fld dword [eax+0x357930]
fsub dword [esi+0x296c]
mov edx, dword [esp+0x34]
mov dword [esp+0x48], ecx
mov dword [esp+0x4c], edx
fst dword [esp+0x38]
fcomp dword [ADDR]
mov eax, dword [esp+0x38]
mov dword [esp+0x50], eax
fnstsw ax
test ah, 0x1
je L115
lea ecx, dword [esp+0x48]
call ADDR
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L115
fld dword [esi+0x1d4]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x40
je Lf5
mov ecx, dword [esi+0x1d8]
mov dword [esi+0x1d4], ecx
mov edx, dword [esi+0x408]
push 0x0
push 0x3e19999a
lea ecx, dword [esi+0x3c4]
mov byte [edi+edx*1+0x357954], 0x0
call ADDR
add edi, 0x98
cmp edi, 0x17c0
jl L45
jmp L12e
mov ebp, 0x1
xor edi, edi
mov eax, dword [esi+0x408]
add eax, edi
cmp dword [eax+0x356b80], ebp
jne L1d2
fld dword [eax+0x356b68]
fsub dword [esi+0x2964]
fstp dword [esp+0x30]
fld dword [eax+0x356b6c]
fsub dword [esi+0x2968]
mov ecx, dword [esp+0x30]
fstp dword [esp+0x34]
fld dword [eax+0x356b70]
fsub dword [esi+0x296c]
mov edx, dword [esp+0x34]
mov dword [esp+0x18], ecx
mov dword [esp+0x1c], edx
fst dword [esp+0x38]
fcomp dword [ADDR]
mov eax, dword [esp+0x38]
mov dword [esp+0x20], eax
fnstsw ax
test ah, 0x1
je L1d2
lea ecx, dword [esp+0x18]
call ADDR
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L1d2
mov ecx, dword [esi+0x408]
push 0x0
push 0x3ca3d70a
mov dword [edi+ecx*1+0x356b80], 0x2
lea ecx, dword [esi+0x3c4]
call ADDR
add edi, 0xb0
cmp edi, 0xdc0
jl L130
mov edx, dword [esi+0x408]
mov edi, dword [edx+0x359140]
test edi, edi
je L32d
cmp dword [edi+0x84], ebp
jne L31f
fld dword [edi+0x68]
fsub dword [esi+0x2964]
fstp dword [esp+0x30]
fld dword [edi+0x6c]
fsub dword [esi+0x2968]
mov eax, dword [esp+0x30]
fstp dword [esp+0x34]
fld dword [edi+0x70]
fsub dword [esi+0x296c]
mov ecx, dword [esp+0x34]
mov dword [esp+0x18], eax
mov dword [esp+0x1c], ecx
fst dword [esp+0x38]
fcomp dword [ADDR]
mov edx, dword [esp+0x38]
mov dword [esp+0x20], edx
fnstsw ax
test ah, 0x1
je L31f
lea ecx, dword [esp+0x18]
call ADDR
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L31f
test byte [esi+0x338], bl
jne L2ae
fld dword [esp+0x18]
fmul dword [esi+0x418]
fmul dword [ADDR]
fsubr dword [esi+0x410]
fstp dword [esi+0x410]
fld dword [esp+0x20]
fmul dword [esi+0x418]
fmul dword [ADDR]
fsubr dword [esi+0x418]
fstp dword [esi+0x418]
mov ecx, 0x2
mov dword [edi+0x84], ecx
fld dword [esp+0x18]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L2d2
mov dword [edi+0x88], ecx
jmp L2d8
mov dword [edi+0x88], ebp
push 0x0
push 0x0
mov ecx, esi
call ADDR
push 0x0
push 0x3d23d70a
lea ecx, dword [esi+0x3c4]
call ADDR
call ADDR
mov dword [esp+0x10], eax
fild dword [esp+0x10]
fmul dword [ADDR]
call ADDR
mov ecx, 0x27
sub ecx, eax
push ecx
mov ecx, ADDR
call ADDR
mov edi, dword [edi+0x80]
test edi, edi
jne L1f8
xor edi, edi
mov edx, dword [esi+0x408]
mov ecx, dword [edi+edx*1+0x356420]
lea eax, dword [edi+edx*1]
cmp ecx, ebp
je L34c
cmp ecx, 0x4
jne L54f
fld dword [eax+0x356408]
fsub dword [esi+0x2964]
fstp dword [esp+0x30]
fld dword [eax+0x35640c]
fsub dword [esi+0x2968]
fstp dword [esp+0x34]
fld dword [eax+0x356410]
fsub dword [esi+0x296c]
mov eax, dword [esp+0x30]
mov ecx, dword [esp+0x34]
mov dword [esp+0x18], eax
mov dword [esp+0x1c], ecx
fst dword [esp+0x38]
fcomp dword [ADDR]
mov edx, dword [esp+0x38]
mov dword [esp+0x20], edx
fnstsw ax
test ah, 0x1
je L54f
lea ecx, dword [esp+0x18]
call ADDR
fst dword [esp+0x10]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L54f
test byte [esi+0x338], bl
jne L53d
mov al, byte [esi+0x2d8]
test al, al
jne L508
mov eax, dword [esi+0x408]
mov byte [esi+0x2d8], 0x1
mov byte [esi+0x384], 0x0
mov dword [esp+0x3c], 0x0
fld dword [eax+0x38]
fld st(0)
fmul dword [ADDR]
mov edx, dword [esp+0x3c]
lea ecx, dword [esi+0x410]
mov dword [esi+0x410], edx
fstp dword [esp+0x40]
mov eax, dword [esp+0x40]
fmul dword [ADDR]
mov dword [ecx+0x4], eax
fstp dword [esp+0x44]
mov edx, dword [esp+0x44]
mov dword [ecx+0x8], edx
mov ecx, esi
call ADDR
mov eax, dword [esi+0x408]
mov dword [esi+0x42e8], 0xa
mov byte [edi+eax*1+0x356479], 0x1
call ADDR
mov dword [esp+0x14], eax
fild dword [esp+0x14]
fmul dword [ADDR]
call ADDR
mov edx, dword [esi+0x408]
mov ecx, 0x22
sub ecx, eax
push ecx
lea ecx, dword [edi+edx*1+0x3563a0]
call ADDR
fld dword [esp+0x10]
fmul dword [ADDR]
mov dword [esi+0x3f4c], 0x0
push 0x50
push 0x5c
fld st(0)
fmul dword [esp+0x20]
fstp dword [esp+0x5c]
fld dword [esp+0x24]
fmul st(1)
fstp dword [esp+0x60]
fmul dword [esp+0x28]
fld dword [esp+0x5c]
fadd dword [esi+0x2964]
fstp dword [esp+0x50]
fld dword [esp+0x60]
fadd dword [esi+0x2968]
mov eax, dword [esp+0x50]
mov dword [esp+0x68], eax
mov eax, dword [esi+0x380]
push eax
fstp dword [esp+0x58]
mov ecx, dword [esp+0x58]
fadd dword [esi+0x296c]
mov dword [esp+0x70], ecx
lea ecx, dword [esp+0x6c]
push ecx
lea ecx, dword [esi+0x1d0]
fstp dword [esp+0x60]
mov edx, dword [esp+0x60]
mov dword [esp+0x78], edx
call ADDR
jmp L54f
mov edx, dword [esi+0x408]
push 0x0
push 0x3f800000
lea ecx, dword [esi+0x3c4]
fld dword [edx+0x38]
fld st(0)
fmul st(1)
fmul dword [ADDR]
fmul dword [ADDR]
fstp dword [esi+0x418]
fstp st(0)
call ADDR
jmp L54f
mov eax, dword [esi+0x408]
lea ecx, dword [edi+eax*1+0x3563a0]
call ADDR
add edi, 0xec
cmp edi, 0x760
jl L32f
xor edi, edi
mov ecx, dword [esi+0x408]
lea eax, dword [edi+ecx*1]
mov ecx, dword [edi+ecx*1+0x125e4b8]
cmp ecx, ebp
jne L65e
fld dword [eax+0x125e490]
fsub dword [esi+0x2964]
fstp dword [esp+0x48]
fld dword [eax+0x125e494]
fsub dword [esi+0x2968]
mov edx, dword [esp+0x48]
fstp dword [esp+0x4c]
fld dword [eax+0x125e498]
fsub dword [esi+0x296c]
mov eax, dword [esp+0x4c]
mov dword [esp+0x6c], edx
mov dword [esp+0x70], eax
fst dword [esp+0x50]
fcomp dword [ADDR]
mov ecx, dword [esp+0x50]
mov dword [esp+0x74], ecx
fnstsw ax
test ah, 0x1
je L65e
lea ecx, dword [esp+0x6c]
call ADDR
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L65e
push 0x0
push 0x3
mov ecx, esi
call ADDR
push -0x1
push ebp
push 0xa
mov ecx, ADDR
call ADDR
push 0x1b
mov ecx, ADDR
call ADDR
mov edx, dword [esi+0x408]
mov dword [edi+edx*1+0x125e4b8], 0x4
mov ebx, dword [esi+0x4338]
mov eax, dword [esi+0x408]
inc ebx
mov dword [esi+0x4338], ebx
mov ecx, ebx
mov edx, dword [eax+0x40]
test edx, edx
jne L65e
mov edx, dword [eax+0x1b01e0]
mov eax, dword [eax+0x35bb94]
push edx
push ecx
add eax, 0x2cc
push ADDR
push eax
call ADDR
add esp, 0x10
add edi, 0x8c
cmp edi, 0x1b58
jl L563
jmp L677
mov ebp, 0x1
xor edi, edi
mov ecx, dword [esi+0x408]
lea eax, dword [edi+ecx*1]
mov ecx, dword [edi+ecx*1+0x356038]
cmp ecx, ebp
jne L77c
fld dword [eax+0x356010]
fsub dword [esi+0x2964]
fstp dword [esp+0x18]
fld dword [eax+0x356014]
fsub dword [esi+0x2968]
mov edx, dword [esp+0x18]
fstp dword [esp+0x1c]
fld dword [eax+0x356018]
fsub dword [esi+0x296c]
mov eax, dword [esp+0x1c]
mov dword [esp+0x24], edx
mov dword [esp+0x28], eax
fstp dword [esp+0x20]
fld dword [esi+0x6c]
fcomp dword [ADDR]
mov ecx, dword [esp+0x20]
mov dword [esp+0x2c], ecx
fnstsw ax
test ah, 0x1
jne L77c
fld dword [esp+0x20]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L77c
fld dword [esp+0x1c]
fcomp dword [ADDR]
fld dword [esp+0x1c]
fnstsw ax
test ah, 0x1
je L715
fchs
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L77c
lea ecx, dword [esp+0x24]
call ADDR
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L77c
push 0xe
mov ecx, ADDR
call ADDR
mov edx, dword [esi+0x408]
mov dword [edi+edx*1+0x356038], 0x2
mov eax, dword [esi+0x408]
lea ecx, dword [edi+eax*1+0x356000]
push ecx
mov ecx, esi
call ADDR
push 0x0
push 0xbf000000
lea ecx, dword [esi+0x3c4]
call ADDR
add edi, 0x74
cmp edi, 0x3a0
jl L679
mov eax, dword [esi+0x408]
cmp dword [eax+0x355e30], ebp
jne L86c
fld dword [eax+0x355e18]
fsub dword [esi+0x2964]
fstp dword [esp+0x18]
fld dword [eax+0x355e1c]
fsub dword [esi+0x2968]
mov edx, dword [esp+0x18]
fstp dword [esp+0x1c]
fld dword [eax+0x355e20]
fsub dword [esi+0x296c]
mov eax, dword [esp+0x1c]
mov dword [esp+0x24], edx
mov dword [esp+0x28], eax
fstp dword [esp+0x20]
fld dword [esi+0x6c]
fcomp dword [ADDR]
mov ecx, dword [esp+0x20]
mov dword [esp+0x2c], ecx
fnstsw ax
test ah, 0x1
jne L86c
fld dword [esp+0x20]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L86c
fld dword [esp+0x1c]
fcomp dword [ADDR]
fld dword [esp+0x1c]
fnstsw ax
test ah, 0x1
je L81d
fchs
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L86c
lea ecx, dword [esp+0x24]
call ADDR
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L86c
mov edx, dword [esi+0x408]
mov ecx, esi
mov dword [edx+0x355e30], 0x2
call ADDR
mov eax, dword [esi+0x408]
fld dword [eax+0x38]
fmul dword [ADDR]
fstp dword [esi+0x418]
mov eax, dword [esi+0x408]
cmp dword [eax+0x355e9c], ebp
jne L918
fld dword [eax+0x355e74]
fsub dword [esi+0x2964]
fstp dword [esp+0x18]
fld dword [eax+0x355e78]
fsub dword [esi+0x2968]
mov ecx, dword [esp+0x18]
fstp dword [esp+0x1c]
fld dword [eax+0x355e7c]
fsub dword [esi+0x296c]
mov edx, dword [esp+0x1c]
mov dword [esp+0x24], ecx
mov dword [esp+0x28], edx
fstp dword [esp+0x20]
fld dword [esi+0x6c]
fcomp dword [ADDR]
mov eax, dword [esp+0x20]
mov dword [esp+0x2c], eax
fnstsw ax
test ah, 0x1
jne L918
fld dword [esp+0x20]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L918
lea ecx, dword [esp+0x24]
call ADDR
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L918
mov ecx, dword [esi+0x408]
mov dword [ecx+0x355e9c], 0x2
lea ecx, dword [esi+0x2750]
call ADDR
xor edi, edi
mov ebx, 0x7
mov ebp, 0xbdcccccd
mov edx, dword [esi+0x408]
mov ecx, dword [edi+edx*1+0x35b80c]
lea eax, dword [edi+edx*1]
cmp ecx, 0x1
jne Lb2d
fld dword [eax+0x35b7f4]
fsub dword [esi+0x2964]
fstp dword [esp+0x48]
fld dword [eax+0x35b7f8]
fsub dword [esi+0x2968]
fstp dword [esp+0x4c]
fld dword [eax+0x35b7fc]
fsub dword [esi+0x296c]
mov eax, dword [esp+0x48]
mov ecx, dword [esp+0x4c]
mov dword [esp+0x78], eax
mov dword [esp+0x7c], ecx
fst dword [esp+0x50]
fcomp dword [ADDR]
mov edx, dword [esp+0x50]
mov dword [esp+0x80], edx
fnstsw ax
test ah, 0x1
je Lb2d
lea ecx, dword [esp+0x78]
call ADDR
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je Lb2d
mov eax, dword [esi+0x408]
mov dword [edi+eax*1+0x35b80c], 0x2
mov al, byte [esi+0x440]
test al, al
jne La07
mov ecx, dword [esi+0x408]
mov eax, dword [edi+ecx*1+0x35b814]
cmp eax, 0x3
je L9f5
cmp eax, ebx
je L9f5
fld dword [ecx+0x38]
fmul dword [ADDR]
fstp dword [esi+0x418]
jmp La07
push 0x2b
mov ecx, ADDR
mov dword [esi+0x418], ebp
call ADDR
mov ecx, dword [esi+0x408]
mov eax, dword [edi+ecx*1+0x35b814]
cmp eax, 0x4
je Labb
cmp eax, 0x5
je Labb
cmp eax, 0x8
jne La5c
mov eax, dword [esi+0x308]
cmp eax, 0x8
jge La3f
inc eax
mov dword [esi+0x308], eax
jmp La47
jne La47
mov dword [esi+0x308], ebx
mov eax, dword [esi+0x308]
dec eax
cmp eax, 0x6
jle Lb16
jmp Lb11
cmp eax, 0x1
jne La7d
push 0x0
push 0x2
mov ecx, esi
call ADDR
push 0x1
mov ecx, ADDR
call ADDR
jmp Lb2d
cmp eax, 0x2
je La8b
cmp eax, 0x6
jne Lb2d
push 0x0
push 0x2
mov ecx, esi
call ADDR
push 0x2a
mov ecx, ADDR
call ADDR
mov ecx, dword [esi+0x378]
mov dword [esi+0x374], ecx
lea ecx, dword [esi+0x150]
call ADDR
jmp Lb2d
mov eax, dword [esi+0x404]
cmp eax, 0xa
jge Lae9
test byte [ecx+0x4c], 0x10
je Lad9
cmp dword [ecx+0x40], 0x3
je Lad9
inc eax
mov dword [esi+0x404], eax
push -0x1
push 0x1
push 0x5
mov ecx, ADDR
call ADDR
mov eax, dword [esi+0x308]
cmp eax, 0x8
jge Lafd
inc eax
mov dword [esi+0x308], eax
jmp Lb05
jne Lb05
mov dword [esi+0x308], ebx
mov eax, dword [esi+0x308]
dec eax
cmp eax, 0x6
jle Lb16
mov eax, 0x6
inc eax
mov ecx, ADDR
push eax
call ADDR
push 0x0
push 0x2
mov ecx, esi
call ADDR
add edi, 0x1f8
cmp edi, 0x3f0
jl L924
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x74
ret
