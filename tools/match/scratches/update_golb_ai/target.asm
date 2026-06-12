sub esp, 0x70
push ebx
push ebp
mov ebp, ecx
push esi
push edi
mov eax, dword [ebp+0x270]
mov cl, byte [eax+0x9]
test cl, cl
jne La48
cmp byte [ebp+0x1bc], 0x1
jne L32
pop edi
mov byte [ebp+0x1bc], 0x0
pop esi
pop ebp
pop ebx
add esp, 0x70
ret
mov eax, dword [ebp+0x244]
dec eax
jne La48
mov al, byte [ebp+0x2bc]
lea ecx, dword [ebp+0x2bc]
cmp al, 0x1
jne Lb9
mov edx, dword [ebp+0x264]
lea eax, dword [ebp+0x24c]
lea esi, dword [ebp+0x1f4]
push eax
push esi
push edx
call ADDR
cmp eax, 0x3
ja L366
jmp dword [eax*4+ADDR]
mov ecx, dword [esi]
mov edx, dword [esi+0x4]
lea eax, dword [ebp+0x2ac]
mov dword [ebp+0x2ac], ecx
mov ecx, dword [esi+0x8]
mov dword [eax+0x4], edx
mov dword [eax+0x8], ecx
jmp L366
lea edx, dword [ebp+0x2d4]
lea eax, dword [ebp+0x2ac]
mov ecx, dword [edx]
mov dword [eax], ecx
mov ecx, dword [edx+0x4]
mov dword [eax+0x4], ecx
mov edx, dword [edx+0x8]
mov dword [eax+0x8], edx
jmp L366
fld dword [ebp+0x24c]
fadd dword [ebp+0x1f4]
lea edi, dword [ebp+0x24c]
lea esi, dword [ebp+0x1f4]
fstp dword [esi]
fld dword [edi+0x4]
fadd dword [esi+0x4]
fstp dword [esi+0x4]
fld dword [edi+0x8]
fadd dword [esi+0x8]
fstp dword [esi+0x8]
mov eax, dword [ebp+0x1c0]
test eax, eax
jne L144
fld dword [ebp+0x1f8]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
je L124
fld dword [ebp+0x1f8]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
jne L124
mov dword [ebp+0x250], 0x0
jmp L29b
mov eax, dword [ebp+0x270]
fld dword [eax+0x38]
fmul dword [ADDR]
fsubr dword [ebp+0x250]
fstp dword [ebp+0x250]
jmp L29b
cmp eax, 0x2
jne L29b
mov eax, dword [ebp+0x198]
test eax, eax
je L29b
fld dword [ebp+0x1b0]
fadd dword [ebp+0x1ac]
fst dword [ebp+0x1ac]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L184
mov dword [ebp+0x1ac], 0x3f800000
mov ecx, edi
call ADDR
fstp dword [esp+0x10]
fld dword [ebp+0x19c]
fsub dword [esi]
fstp dword [esp+0x2c]
fld dword [ebp+0x1a0]
fsub dword [esi+0x4]
mov ecx, dword [esp+0x2c]
mov dword [esp+0x20], ecx
lea ecx, dword [esp+0x20]
fstp dword [esp+0x30]
fld dword [ebp+0x1a4]
fsub dword [esi+0x8]
mov edx, dword [esp+0x30]
mov dword [esp+0x24], edx
fstp dword [esp+0x34]
mov eax, dword [esp+0x34]
mov dword [esp+0x28], eax
call ADDR
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L1e9
push esi
jmp La3a
fld dword [ebp+0x1ac]
fld dword [esp+0x20]
fmul st(1)
mov ecx, edi
fstp dword [esp+0x44]
fld dword [esp+0x24]
fmul st(1)
fstp dword [esp+0x48]
fmul dword [esp+0x28]
fld dword [ebp+0x1ac]
fmul dword [ADDR]
fsubr dword [ADDR]
fld st(0)
fmul dword [edi]
fstp dword [esp+0x38]
fld st(0)
fmul dword [edi+0x4]
fstp dword [esp+0x3c]
fmul dword [edi+0x8]
fld dword [esp+0x38]
fadd dword [esp+0x44]
fstp dword [esp+0x2c]
fld dword [esp+0x3c]
fadd dword [esp+0x48]
mov edx, dword [esp+0x2c]
mov dword [ecx], edx
fstp dword [esp+0x30]
mov eax, dword [esp+0x30]
fadd st(1)
mov dword [ecx+0x4], eax
fstp dword [esp+0x34]
mov edx, dword [esp+0x34]
fstp st(0)
mov dword [ecx+0x8], edx
call ADDR
fstp st(0)
fld dword [esp+0x10]
fmul dword [edi]
fstp dword [edi]
fld dword [esp+0x10]
fmul dword [edi+0x4]
fstp dword [edi+0x4]
fld dword [esp+0x10]
fmul dword [edi+0x8]
fstp dword [edi+0x8]
fld dword [esp+0x10]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
jne La41
lea ecx, dword [ebp+0x2ac]
mov eax, esi
mov edx, ecx
mov edi, dword [eax]
fld dword [ebp+0x2e4]
mov dword [edx], edi
mov edi, dword [eax+0x4]
mov eax, dword [eax+0x8]
mov dword [edx+0x4], edi
mov dword [edx+0x8], eax
fcomp dword [ebp+0x2b4]
fnstsw ax
test ah, 0x1
je L366
fld dword [ebp+0x1f8]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L366
fld dword [ebp+0x1f8]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L366
push ecx
mov ecx, dword [ebp+0x270]
call ADDR
mov edi, eax
mov bl, 0x1e
cmp byte [edi+0x3c], bl
jne L325
mov ecx, dword [ebp+0x2b4]
push ebp
mov dword [ebp+0x2e4], ecx
push esi
push edi
lea ecx, dword [ebp+0x2bc]
call ADDR
fld dword [ebp+0x254]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L366
cmp byte [edi+-0x264], bl
jne L366
fld dword [ebp+0x2b4]
fadd dword [ADDR]
push ebp
add edi, 0xfffffd60
push esi
push edi
lea ecx, dword [ebp+0x2bc]
fstp dword [ebp+0x2e4]
call ADDR
mov eax, dword [ebp+0x1c0]
sub eax, 0x0
je L45f
dec eax
je L448
dec eax
jne L568
fld dword [ebp+0x1b8]
fadd dword [ebp+0x1b4]
lea esi, dword [ebp+0x27c]
lea edi, dword [ebp+0x150]
mov ecx, 0x10
fcom dword [ADDR]
fst dword [ebp+0x1b4]
rep movsd dword [edi], dword [esi]
fnstsw ax
test ah, 0x41
jne L3c3
fsub dword [ADDR]
fstp dword [ebp+0x1b4]
jmp L3c5
fstp st(0)
lea esi, dword [ebp+0x2ac]
mov ecx, ebp
push esi
call ADDR
fld dword [ebp+0x258]
fmul dword [ADDR]
fld dword [ebp+0x25c]
fmul dword [ADDR]
fstp dword [esp+0x48]
fld dword [ebp+0x260]
fmul dword [ADDR]
fstp dword [esp+0x4c]
fld dword [esi]
fsub st(1)
fstp dword [esp+0x2c]
mov edx, dword [esp+0x2c]
fstp st(0)
fld dword [esi+0x4]
fsub dword [esp+0x48]
mov dword [esp+0x50], edx
lea edx, dword [esp+0x50]
push edx
fstp dword [esp+0x34]
fld dword [esi+0x8]
fsub dword [esp+0x50]
mov eax, dword [esp+0x34]
mov dword [esp+0x58], eax
fstp dword [esp+0x38]
mov ecx, dword [esp+0x38]
mov dword [esp+0x5c], ecx
mov ecx, ebp
call ADDR
jmp L568
lea eax, dword [ebp+0x27c]
lea ecx, dword [ebp+0x80]
push eax
call ADDR
jmp L568
mov ecx, dword [ebp+0x248]
lea esi, dword [ebp+0x2ac]
mov edx, esi
add ecx, 0x48
push esi
mov eax, dword [edx]
mov dword [ecx], eax
mov eax, dword [edx+0x4]
mov dword [ecx+0x4], eax
mov edx, dword [edx+0x8]
mov dword [ecx+0x8], edx
mov ecx, ebp
call ADDR
fld dword [ebp+0x258]
fmul dword [ADDR]
fld dword [ebp+0x25c]
fmul dword [ADDR]
fstp dword [esp+0x48]
fld dword [ebp+0x260]
fmul dword [ADDR]
fstp dword [esp+0x4c]
fld dword [esi]
fsub st(1)
fstp dword [esp+0x2c]
mov eax, dword [esp+0x2c]
fstp st(0)
fld dword [esi+0x4]
fsub dword [esp+0x48]
mov dword [esp+0x5c], eax
lea eax, dword [esp+0x5c]
push eax
fstp dword [esp+0x34]
fld dword [esi+0x8]
fsub dword [esp+0x50]
mov ecx, dword [esp+0x34]
mov dword [esp+0x64], ecx
mov ecx, ebp
fstp dword [esp+0x38]
mov edx, dword [esp+0x38]
mov dword [esp+0x68], edx
call ADDR
fld dword [ebp+0x258]
fmul dword [ADDR]
fld dword [ebp+0x25c]
fmul dword [ADDR]
fstp dword [esp+0x48]
fld dword [ebp+0x260]
fmul dword [ADDR]
fstp dword [esp+0x4c]
fld dword [esi]
fsub st(1)
fstp dword [esp+0x2c]
mov ecx, dword [esp+0x2c]
fstp st(0)
fld dword [esi+0x4]
fsub dword [esp+0x48]
mov dword [esp+0x68], ecx
lea ecx, dword [esp+0x68]
push ecx
mov ecx, ebp
fstp dword [esp+0x34]
fld dword [esi+0x8]
fsub dword [esp+0x50]
mov edx, dword [esp+0x34]
mov dword [esp+0x70], edx
fstp dword [esp+0x38]
mov eax, dword [esp+0x38]
mov dword [esp+0x74], eax
call ADDR
fld dword [ebp+0x2ac]
fsub dword [ebp+0x234]
lea edi, dword [ebp+0x2ac]
lea eax, dword [ebp+0x258]
mov edx, eax
mov ebx, 0x2
fstp dword [esp+0x2c]
fld dword [edi+0x4]
fsub dword [ebp+0x238]
mov ecx, dword [esp+0x2c]
fstp dword [esp+0x30]
fld dword [edi+0x8]
fsub dword [ebp+0x23c]
mov dword [edx], ecx
mov ecx, dword [esp+0x30]
mov dword [edx+0x4], ecx
fstp dword [esp+0x34]
mov ecx, dword [esp+0x34]
mov dword [edx+0x8], ecx
mov ecx, dword [ebp+0x1c0]
cmp ecx, ebx
jne L5df
lea esi, dword [ebp+0x150]
push eax
mov ecx, esi
call ADDR
mov edx, dword [ebp+0x1b4]
mov ecx, esi
push edx
call ADDR
fld dword [ebp+0x26c]
fadd dword [ebp+0x268]
mov eax, edi
mov ecx, dword [eax]
fst dword [ebp+0x268]
mov edx, dword [eax+0x4]
mov dword [ebp+0x234], ecx
fcomp dword [ADDR]
mov eax, dword [eax+0x8]
mov dword [ebp+0x238], edx
mov dword [ebp+0x23c], eax
fnstsw ax
test ah, 0x41
je La41
mov ecx, dword [ebp+0x278]
fld dword [ebp+0x1fc]
fcomp dword [ecx+0x2980]
fnstsw ax
test ah, 0x1
jne La41
fld dword [ecx+0x70]
fadd dword [ADDR]
fcomp dword [ebp+0x1fc]
fnstsw ax
test ah, 0x1
jne La41
mov ecx, dword [ebp+0x270]
mov esi, dword [ecx+0x359140]
test esi, esi
je L744
cmp dword [esi+0x84], 0x1
jne L736
fld dword [esi+0x68]
fsub dword [edi]
fstp dword [esp+0x2c]
fld dword [esi+0x6c]
fsub dword [edi+0x4]
mov edx, dword [esp+0x2c]
fstp dword [esp+0x30]
fld dword [esi+0x70]
fsub dword [edi+0x8]
mov eax, dword [esp+0x30]
mov dword [esp+0x14], edx
mov dword [esp+0x18], eax
fcom dword [ADDR]
fst dword [esp+0x34]
mov ecx, dword [esp+0x34]
mov dword [esp+0x1c], ecx
fnstsw ax
test ah, 0x1
je L6ba
fchs
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L736
lea ecx, dword [esp+0x14]
call ADDR
fld dword [esi+0x9c]
fadd dword [ADDR]
fxch st(0), st(1)
fcompp
fnstsw ax
test ah, 0x1
je L731
mov dword [esi+0x84], ebx
fld dword [esp+0x14]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L70b
mov dword [esi+0x88], ebx
mov ebx, 0x1
jmp L716
mov ebx, 0x1
mov dword [esi+0x88], ebx
mov ecx, dword [ebp+0x278]
push 0x0
push 0x0
call ADDR
cmp dword [ebp+0x1c0], ebx
jne L87b
mov ebx, 0x2
mov esi, dword [esi+0x80]
test esi, esi
jne L669
xor esi, esi
xor ebx, ebx
mov eax, dword [ebp+0x270]
add eax, ebx
mov ecx, dword [eax+0x356420]
cmp ecx, 0x1
je L764
cmp ecx, 0x4
jne L863
fld dword [eax+0x356408]
fsub dword [edi]
fstp dword [esp+0x2c]
fld dword [eax+0x35640c]
fsub dword [edi+0x4]
mov ecx, dword [esp+0x2c]
fstp dword [esp+0x30]
fld dword [eax+0x356410]
fsub dword [edi+0x8]
mov edx, dword [esp+0x30]
mov dword [esp+0x14], ecx
mov dword [esp+0x18], edx
fcom dword [ADDR]
fst dword [esp+0x34]
mov eax, dword [esp+0x34]
mov dword [esp+0x1c], eax
fnstsw ax
test ah, 0x1
je L7b1
fchs
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L863
lea ecx, dword [esp+0x14]
call ADDR
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L863
lea ecx, dword [ebp+0x24c]
mov byte [ebp+0x2bc], 0x0
call ADDR
fstp dword [esp+0x10]
lea ecx, dword [esp+0x14]
mov dword [esp+0x18], 0x0
call ADDR
fstp st(0)
fld dword [esp+0x10]
fmul dword [esp+0x14]
lea eax, dword [ebp+0x24c]
mov dword [esp+0x24], 0x0
mov edx, dword [esp+0x24]
fchs
fstp dword [esp+0x20]
fld dword [esp+0x10]
fmul dword [esp+0x1c]
mov ecx, dword [esp+0x20]
mov dword [eax], ecx
fchs
fstp dword [esp+0x28]
mov ecx, dword [esp+0x28]
mov dword [eax+0x4], edx
mov dword [eax+0x8], ecx
mov eax, dword [ebp+0x1c0]
cmp eax, 0x1
je L951
cmp eax, 0x2
je L98b
test eax, eax
je L9c5
add ebx, 0xec
inc esi
cmp ebx, 0x760
jl L748
jmp L9f5
mov ecx, ebp
call ADDR
push edi
mov ecx, ebp
call ADDR
cmp dword [ebp+0x1c0], 0x2
jne La48
mov edx, dword [ebp+0x270]
mov esi, dword [edx+0x359140]
test esi, esi
je La48
cmp dword [esi+0x84], ebx
jne L93b
fld dword [esi+0x68]
fsub dword [edi]
fstp dword [esp+0x2c]
fld dword [esi+0x6c]
fsub dword [edi+0x4]
mov eax, dword [esp+0x2c]
fstp dword [esp+0x30]
fld dword [esi+0x70]
fsub dword [edi+0x8]
mov ecx, dword [esp+0x30]
mov dword [esp+0x14], eax
mov dword [esp+0x18], ecx
lea ecx, dword [esp+0x14]
fstp dword [esp+0x34]
mov edx, dword [esp+0x34]
mov dword [esp+0x1c], edx
call ADDR
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L93b
mov ecx, 0x2
mov dword [esi+0x84], ecx
fld dword [esp+0x14]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L926
mov dword [esi+0x88], ecx
jmp L92c
mov dword [esi+0x88], ebx
mov ecx, dword [ebp+0x278]
push 0x0
push 0x0
call ADDR
mov esi, dword [esi+0x80]
test esi, esi
jne L8ab
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x70
ret
mov ecx, ebp
call ADDR
push edi
mov ecx, ebp
call ADDR
lea edx, dword [esi*8]
push 0x2
sub edx, esi
lea eax, dword [esi+edx*4]
mov edx, dword [ebp+0x270]
lea ecx, dword [esi+eax*2]
lea ecx, dword [edx+ecx*4+0x3563a0]
call ADDR
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x70
ret
mov ecx, ebp
call ADDR
push edi
mov ecx, ebp
call ADDR
lea eax, dword [esi*8]
push 0x4
sub eax, esi
lea ecx, dword [esi+eax*4]
mov eax, dword [ebp+0x270]
lea edx, dword [esi+ecx*2]
lea ecx, dword [eax+edx*4+0x3563a0]
call ADDR
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x70
ret
mov al, byte [ebp+0x1bd]
test al, al
jne L9de
pop edi
mov byte [ebp+0x1bd], 0x1
pop esi
pop ebp
pop ebx
add esp, 0x70
ret
mov ecx, ebp
call ADDR
push edi
mov ecx, ebp
call ADDR
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x70
ret
mov ecx, dword [ebp+0x270]
push edi
call ADDR
cmp byte [eax+0x3c], 0xe
jne La48
fld dword [edi+0x8]
fsub dword [ADDR]
mov ecx, dword [edi]
mov edx, dword [edi+0x4]
mov eax, ecx
mov dword [esp+0x2c], ecx
mov dword [esp+0x30], edx
mov dword [esp+0x74], eax
fstp dword [esp+0x34]
mov ecx, edx
mov edx, dword [esp+0x34]
lea eax, dword [esp+0x74]
mov dword [esp+0x78], ecx
mov dword [esp+0x7c], edx
push eax
mov ecx, ebp
call ADDR
mov ecx, ebp
call ADDR
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x70
ret
mov eax, 0x99004148
dec eax
inc ecx
add byte [eax+-0x66ffbeb8], bh
dec eax
inc ecx
