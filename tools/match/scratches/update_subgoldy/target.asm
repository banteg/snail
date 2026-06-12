sub esp, 0x40
push ebx
push ebp
mov ebp, ecx
push esi
push edi
mov eax, dword [ebp+0x408]
mov cl, byte [eax+0x9]
test cl, cl
je L63
mov ecx, dword [ADDR]
cmp dword [ecx+0x1b8], 0x9
je L20f0
lea ecx, dword [ebp+0x3c4]
call ADDR
lea ecx, dword [ebp+0x3f0]
call ADDR
lea ecx, dword [ebp+0x3f4]
call ADDR
mov ecx, dword [ebp+0x408]
add ecx, 0x12727d8
call ADDR
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x40
ret
cmp byte [ebp+0x384], 0x1
jne Lc1
mov esi, dword [ebp+0x388]
mov eax, dword [ebp+0x390]
add eax, 0x3
mov ecx, dword [esi+0x44]
cmp eax, ecx
jl L85
lea eax, dword [ecx+-0x1]
lea ecx, dword [eax*8]
mov edx, dword [ebp+0x29a8]
sub ecx, eax
lea eax, dword [ecx+ecx*2]
mov ecx, dword [esi+0x58]
fld dword [ecx+eax*8+0xa4]
fmul dword [ADDR]
fsub dword [edx+0x80]
fmul dword [ADDR]
fadd dword [edx+0x80]
fstp dword [edx+0x80]
jmp Le1
mov eax, dword [ebp+0x29a8]
fld dword [eax+0x80]
fchs
fmul dword [ADDR]
fadd dword [eax+0x80]
fstp dword [eax+0x80]
lea esi, dword [ebp+0x4344]
mov ecx, esi
call ADDR
mov edx, dword [ebp+0x29a8]
mov eax, dword [esi]
mov dword [edx+0x84], eax
mov ecx, dword [ebp+0x29a8]
mov edx, dword [ebp+0x4350]
mov dword [ecx+0x88], edx
mov eax, dword [ebp+0x408]
mov ecx, dword [eax+0x40]
test ecx, ecx
jne L122
mov ecx, ebp
call ADDR
mov eax, dword [ebp+0x40c]
sub eax, 0x0
je L20f0
mov esi, 0x2
sub eax, esi
je L20f0
mov eax, dword [ebp+0x408]
cmp dword [eax+0xff25dc], 0x14
jle L15e
mov cl, byte [eax+0xa854]
test cl, cl
jne L15e
mov byte [eax+0xa854], 0x1
mov eax, dword [ebp+0x408]
mov edi, 0x4000
mov cl, byte [eax+0xff25d0]
test cl, cl
je L240
mov ecx, dword [eax+0xff25d4]
mov eax, dword [eax+0xff25dc]
cmp eax, dword [ecx+0x6c]
jge L240
cmp dword [ebp+0x120], esi
je L240
lea edx, dword [eax+eax*2]
push 0x41800000
lea ebx, dword [ebp+0x68]
mov ax, word [ecx+edx*2+0x70]
push eax
call ADDR
fstp dword [ebx]
mov eax, dword [ebp+0x408]
add esp, 0x8
mov ecx, dword [eax+0xff25dc]
mov edx, dword [eax+0xff25d4]
lea ecx, dword [ecx+ecx*2]
test byte [edx+ecx*2+0x74], 0x4
je L1d8
mov byte [eax+0xa854], 0x1
jmp L1df
mov byte [eax+0xa854], 0x0
mov eax, dword [ebp+0x408]
mov ecx, dword [eax+0xff25dc]
mov edx, dword [eax+0xff25d4]
lea ecx, dword [ecx+ecx*2]
test byte [edx+ecx*2+0x74], 0x8
je L574
mov eax, dword [ADDR]
mov dword [eax+0x1b8], 0x1a
mov ecx, dword [ADDR]
mov dword [ecx+0x1bc], 0xa
mov edx, dword [ADDR]
mov byte [edx+0x30c], 0x1
mov eax, dword [ADDR]
lea ecx, dword [eax+0x24]
call ADDR
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x40
ret
mov al, byte [ebp+0x3c0]
test al, al
je L26a
mov al, byte [ebp+0x440]
test al, al
je L26a
mov eax, 0x43a00000
mov dword [ebp+0x273c], eax
mov dword [ebp+0x2740], eax
jmp L363
mov al, byte [ebp+0x2d8]
test al, al
je L2d5
fld dword [ebp+0x29cc]
fadd st(0), st(0)
fsubr dword [ebp+0x273c]
fst dword [ebp+0x273c]
fstp dword [ebp+0x2740]
fld dword [ebp+0x273c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L2ac
fld dword [ADDR]
jmp L35d
fld dword [ebp+0x273c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L2ca
fld dword [ADDR]
jmp L35d
fld dword [ebp+0x273c]
jmp L35d
mov ecx, dword [ebp+0x2970]
mov edx, dword [ecx*4+ADDR]
push edx
call ADDR
mov eax, dword [ebp+0x43c]
add esp, 0x4
fstp st(0)
fld dword [eax+0x28]
fsub dword [ebp+0x2740]
fadd dword [ebp+0x273c]
fcom dword [ADDR]
fst dword [ebp+0x273c]
fnstsw ax
test ah, 0x1
je L31f
fstp st(0)
fld dword [ADDR]
jmp L334
fcom dword [ADDR]
fnstsw ax
test ah, 0x41
jne L334
fstp st(0)
fld dword [ADDR]
fstp dword [ebp+0x273c]
mov ecx, dword [ebp+0x43c]
mov edx, dword [ecx+0x28]
mov dword [ebp+0x2740], edx
mov eax, dword [ebp+0x2970]
cmp eax, 0x1
jne L363
mov eax, dword [ebp+0x43c]
fld dword [eax+0x28]
fstp dword [ebp+0x273c]
mov al, byte [ebp+0x440]
test al, al
jne L3d3
fld dword [ebp+0x273c]
fsubr dword [ADDR]
fmul dword [ADDR]
fcom dword [ADDR]
fnstsw ax
test ah, 0x1
je L396
fstp st(0)
fld dword [ADDR]
jmp L3ab
fcom dword [ADDR]
fnstsw ax
test ah, 0x41
jne L3ab
fstp st(0)
fld dword [ADDR]
cmp dword [ebp+0x120], esi
je L3d1
mov ecx, dword [ebp+0x408]
fld dword [ecx+0x38]
fmul dword [ADDR]
fxch st(0), st(1)
fsub dword [ebp+0x68]
fmulp st(1)
fadd dword [ebp+0x68]
fstp dword [ebp+0x68]
jmp L3d3
fstp st(0)
mov edx, dword [ebp+0x68]
lea ebx, dword [ebp+0x68]
push 0x41800000
push 0x41800000
push edx
call ADDR
add esp, 0x8
push eax
call ADDR
fst dword [esp+0x18]
mov eax, dword [esp+0x18]
push 0x41800000
fstp dword [ebx]
mov esi, dword [ebp+0x408]
push eax
call ADDR
mov ecx, dword [esi+0xff25dc]
add esp, 0x10
lea ecx, dword [ecx+ecx*2]
push 0x42000000
mov word [esi+ecx*2+0xfd2b80], ax
mov edx, dword [ebp+0x408]
mov esi, edx
mov eax, dword [edx+0xff25dc]
test eax, eax
jne L47c
mov eax, dword [ebp+0x70]
push eax
call ADDR
mov ecx, dword [esi+0xff25dc]
push 0x42000000
add ecx, 0x2a31eb
lea ecx, dword [ecx+ecx*2]
mov word [esi+ecx*2], ax
mov ecx, dword [ebp+0x408]
mov eax, dword [ecx+0xff25dc]
add eax, 0x2a31eb
lea edx, dword [eax+eax*2]
mov ax, word [ecx+edx*2]
push eax
call ADDR
add esp, 0x10
jmp L4cd
fld dword [ebp+0x70]
fsub dword [ADDR]
push ecx
fstp dword [esp]
call ADDR
mov ecx, dword [esi+0xff25dc]
push 0x42000000
add ecx, 0x2a31eb
lea ecx, dword [ecx+ecx*2]
mov word [esi+ecx*2], ax
mov ecx, dword [ebp+0x408]
mov eax, dword [ecx+0xff25dc]
add eax, 0x2a31eb
lea edx, dword [eax+eax*2]
mov ax, word [ecx+edx*2]
push eax
call ADDR
fadd dword [ADDR]
add esp, 0x10
fstp dword [ADDR]
mov eax, dword [ebp+0x408]
mov cl, byte [eax+0xa854]
test cl, cl
je L52f
mov ecx, dword [ebp+0x43c]
test dword [ecx+0x4], edi
je L506
mov ecx, dword [eax+0xff25dc]
lea edx, dword [ecx+ecx*2]
or byte [eax+edx*2+0xfd2b84], 0x1
lea eax, dword [eax+edx*2+0xfd2b84]
mov eax, dword [ebp+0x43c]
test dword [eax+0xc], edi
je L52f
mov eax, dword [ebp+0x408]
mov ecx, dword [eax+0xff25dc]
lea ecx, dword [ecx+ecx*2]
or byte [eax+ecx*2+0xfd2b84], 0x2
lea eax, dword [eax+ecx*2+0xfd2b84]
mov eax, dword [ebp+0x43c]
test dword [eax+0xc], edi
jne L54c
test dword [eax+0x4], edi
jne L54c
mov edx, dword [ebp+0x408]
mov byte [edx+0xa854], 0x1
mov eax, dword [ebp+0x408]
mov cl, byte [eax+0xa854]
test cl, cl
je L574
mov ecx, dword [eax+0xff25dc]
lea ecx, dword [ecx+ecx*2]
or byte [eax+ecx*2+0xfd2b84], 0x4
lea eax, dword [eax+ecx*2+0xfd2b84]
fld dword [ebx]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L593
mov dword [ebx], 0xc0800000
mov dword [ebp+0x410], 0x0
fld dword [ebx]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L5b2
mov dword [ebx], 0x40800000
mov dword [ebp+0x410], 0x0
mov al, byte [ebp+0x84]
test al, al
je L5c3
mov ecx, ebp
call ADDR
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
mov edi, dword [ebp+0x408]
mov ecx, eax
mov dword [esp+0x10], eax
call ADDR
lea ecx, dword [eax+eax*2]
lea edx, dword [ecx+ecx*4]
lea eax, dword [eax+edx*4]
lea esi, dword [edi+eax*4+ADDR]
mov eax, dword [edi+eax*4+ADDR]
test eax, eax
jle L74b
cmp eax, dword [ebp+0x1e8]
je L74b
mov ecx, dword [edi+0xa874]
inc ecx
cmp eax, ecx
jge L74b
mov dword [ebp+0x1e8], eax
mov eax, dword [esi+0xf0]
mov edx, eax
shl edx, 0x5
add edx, eax
shl edx, 0x4
add edx, eax
mov eax, dword [ebp+0x408]
shl edx, 0x5
mov cl, byte [edx+eax*1+0xa670]
test cl, cl
je L74b
mov dword [ebp+0x1ec], 0x2
mov eax, dword [esi+0xf0]
mov ecx, eax
mov edx, dword [ebp+0x408]
shl ecx, 0x5
add ecx, eax
shl ecx, 0x4
add ecx, eax
shl ecx, 0x5
lea eax, dword [ecx+edx*1+0xa670]
mov dword [ebp+0x1fc], eax
mov dword [ebp+0x1f0], 0x0
mov dword [ebp+0x1f4], 0x41f00000
mov eax, dword [esi+0xf0]
mov ecx, eax
mov edx, dword [ebp+0x408]
shl ecx, 0x5
add ecx, eax
shl ecx, 0x4
add ecx, eax
shl ecx, 0x5
mov eax, dword [ecx+edx*1+0xa870]
mov dword [ebp+0x1f8], eax
mov al, byte [ebp+0x14c]
test al, al
jne L6fc
mov byte [ebp+0x14c], 0x1
push -0x1
fld dword [ebx]
fcomp dword [ADDR]
lea edi, dword [ebp+0x2984]
push 0x1
fnstsw ax
test ah, 0x41
jne L6e6
push 0x4
jmp L6e8
push 0x3
mov ecx, edi
call ADDR
push -0x1
push 0x0
push 0x1
mov ecx, edi
call ADDR
mov esi, dword [esi+0xf0]
mov edx, dword [ebp+0x408]
mov ecx, esi
shl ecx, 0x5
add ecx, esi
shl ecx, 0x4
add ecx, esi
shl ecx, 0x5
mov eax, dword [ecx+edx*1+0xa874]
cmp eax, -0x1
je L732
push eax
push 0x2
push 0xd
mov ecx, ADDR
call ADDR
lea eax, dword [ebp+0x1ec]
push 0x1
push eax
mov eax, dword [ADDR]
lea ecx, dword [eax+0x12e6f58]
call ADDR
mov al, byte [ebp+0x41d]
test al, al
jne L79c
mov ecx, dword [esp+0x10]
mov al, byte [ecx+0x3c]
cmp al, 0x1d
je L764
cmp al, 0x1e
jne L79c
mov al, byte [ebp+0x384]
test al, al
jne L79c
mov edx, dword [esp+0x10]
push ebp
push ebx
push edx
lea ecx, dword [ebp+0x384]
call ADDR
mov eax, dword [ebp+0x388]
cmp dword [eax+0x38], 0x18
jne L79c
push -0x1
push 0x0
push 0xc
mov ecx, ADDR
call ADDR
mov al, byte [ebp+0x2d8]
test al, al
je L7f5
fld dword [ebp+0x418]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L7e0
mov ecx, dword [ebp+0x408]
fld dword [ecx+0x38]
fld st(0)
fmul st(1)
fmul dword [ADDR]
fmul dword [ADDR]
fadd dword [ebp+0x418]
fstp dword [ebp+0x418]
fstp st(0)
fld dword [ebp+0x418]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L853
jmp L849
mov ecx, dword [ebp+0x408]
fild dword [ecx+0x50]
fcomp dword [ebp+0x70]
fnstsw ax
test ah, 0x41
jne L823
fld dword [ecx+0x38]
fld st(0)
fmul st(1)
fmul dword [ADDR]
fadd dword [ebp+0x418]
fstp dword [ebp+0x418]
fstp st(0)
fld dword [ebp+0x418]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L840
mov dword [ebp+0x418], 0x3f800000
cmp dword [ebp+0x120], 0x2
jne L853
mov dword [ebp+0x418], 0x0
mov al, byte [ebp+0x384]
lea edi, dword [ebp+0x384]
cmp al, 0x1
jne L9a4
mov edx, dword [ebp+0x418]
lea esi, dword [ebp+0x410]
push esi
push ebx
push edx
mov ecx, edi
call ADDR
cmp eax, 0x3
ja L12dd
jmp dword [eax*4+ADDR]
cmp byte [edi], 0x1
jne L12dd
mov ecx, ebp
call ADDR
jmp L12dd
mov eax, dword [ebp+0x388]
cmp dword [eax+0x38], 0xf
je L8d1
mov ecx, dword [ebp+0x408]
fld dword [ecx+0x38]
fld st(0)
fmul st(1)
fmul dword [ADDR]
fadd st(0), st(0)
fadd dword [ebp+0x418]
fstp dword [ebp+0x418]
fstp st(0)
fld dword [ebx]
fadd dword [esi]
fstp dword [ebx]
fld dword [esi+0x4]
fadd dword [ebx+0x4]
fstp dword [ebx+0x4]
fld dword [esi+0x8]
fadd dword [ebx+0x8]
fstp dword [ebx+0x8]
mov edx, dword [ebp+0x408]
fld dword [edx+0x38]
fmul dword [ADDR]
fsubr dword [ADDR]
fmul dword [ebp+0x418]
fstp dword [ebp+0x418]
mov eax, dword [ebp+0x408]
fld dword [eax+0x38]
fmul dword [ADDR]
fsubr dword [ADDR]
fmul dword [ebp+0x414]
fstp dword [ebp+0x414]
mov ecx, dword [ebp+0x408]
fld dword [ecx+0x38]
fmul dword [ADDR]
fsubr dword [ADDR]
fmul dword [esi]
fstp dword [esi]
mov edx, dword [ebp+0x408]
fld dword [edx+0x38]
fld st(0)
fmul st(1)
fmul dword [ADDR]
fadd dword [ebp+0x414]
fstp dword [ebp+0x414]
fstp st(0)
fld dword [ebx]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L980
mov dword [ebx], 0xc0800000
mov dword [esi], 0x0
fld dword [ebx]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L12dd
mov dword [ebx], 0x40800000
mov dword [esi], 0x0
jmp L12dd
fld dword [ebp+0x410]
fadd dword [ebx]
fstp dword [ebx]
fld dword [ebp+0x414]
fadd dword [ebx+0x4]
fstp dword [ebx+0x4]
fld dword [ebp+0x418]
fadd dword [ebx+0x8]
fstp dword [ebx+0x8]
fld dword [ebx]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L9e5
mov dword [ebx], 0xc0800000
mov dword [ebp+0x410], 0x0
fld dword [ebx]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne La04
mov dword [ebx], 0x40800000
mov dword [ebp+0x410], 0x0
mov al, byte [ebp+0x440]
test al, al
jne Lacf
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0xf
je La7a
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x10
je La7a
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x12
je La7a
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x13
je La7a
cmp dword [ebp+0x3c4], 0x2
jne Lacf
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
mov ecx, eax
call ADDR
test al, al
je Lacf
mov eax, dword [ebp+0x408]
fld dword [eax+0x38]
fld st(0)
fmul st(1)
fmul dword [ADDR]
fadd st(0), st(0)
fadd dword [ebp+0x418]
fstp dword [ebp+0x418]
mov ecx, dword [ebp+0x408]
fstp st(0)
fild dword [ecx+0x50]
fcomp dword [ebp+0x70]
fnstsw ax
test ah, 0x41
je Lacf
fld dword [ebp+0x70]
fcomp dword [ebp+0x2738]
fnstsw ax
test ah, 0x41
jne Lacf
fld dword [ebp+0x70]
fadd dword [ADDR]
fstp dword [ebp+0x2738]
cmp dword [ebp+0x275c], 0x1
jne Lafb
mov edx, dword [ebp+0x408]
fld dword [edx+0x38]
fld st(0)
fmul st(1)
fmul dword [ADDR]
fadd st(0), st(0)
fadd dword [ebp+0x418]
fstp dword [ebp+0x418]
fstp st(0)
mov al, byte [ebp+0x1e4]
test al, al
jne Lb26
mov eax, dword [ebp+0x408]
fld dword [eax+0x38]
fmul dword [ADDR]
fsubr dword [ADDR]
fmul dword [ebp+0x418]
fstp dword [ebp+0x418]
mov ecx, dword [ebp+0x408]
fld dword [ecx+0x38]
fmul dword [ADDR]
fsubr dword [ADDR]
fmul dword [ebp+0x414]
fstp dword [ebp+0x414]
mov edx, dword [ebp+0x408]
fld dword [edx+0x38]
fmul dword [ADDR]
fsubr dword [ADDR]
fmul dword [ebp+0x410]
fstp dword [ebp+0x410]
mov al, byte [ebp+0x41c]
test al, al
je Lba1
mov eax, dword [ebp+0x408]
fld dword [eax+0x38]
fld st(0)
fmul st(1)
fmul dword [ADDR]
fadd st(0), st(0)
fadd dword [ebp+0x418]
fstp dword [ebp+0x418]
mov byte [ebp+0x41d], 0x0
fstp st(0)
jmp Lf78
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
mov esi, eax
mov al, byte [ebp+0x41d]
test al, al
je Ldaa
mov edi, dword [ebp+0x408]
mov ecx, esi
call ADDR
lea ecx, dword [eax+eax*2]
lea ecx, dword [ecx+ecx*4]
lea edx, dword [eax+ecx*4]
mov eax, dword [edi+edx*4+ADDR]
test ah, 0x1
jne Lc0e
mov eax, dword [ebp+0x275c]
test eax, eax
jne Lc0e
mov al, byte [ebp+0x2d8]
test al, al
jne Lc0e
fld dword [edi+0x38]
fmul dword [ADDR]
fsubr dword [ADDR]
fmul dword [ebp+0x418]
fstp dword [ebp+0x418]
mov ecx, esi
call ADDR
lea ecx, dword [eax+eax*2]
lea ecx, dword [ecx+ecx*4]
lea edx, dword [eax+ecx*4]
mov eax, dword [ebp+0x408]
test byte [eax+edx*4+ADDR], 0x40
je Lcd5
fld dword [ebp+0x410]
fmul dword [ADDR]
mov ecx, esi
fstp dword [esp+0x14]
fld dword [ebp+0x414]
fmul dword [ADDR]
fstp dword [esp+0x18]
fld dword [ebp+0x418]
fmul dword [ADDR]
fstp dword [esp+0x1c]
call ADDR
lea ecx, dword [eax+eax*2]
lea ecx, dword [ecx+ecx*4]
lea edx, dword [eax+ecx*4]
mov eax, dword [ebp+0x408]
mov ecx, dword [eax+edx*4+ADDR]
mov eax, dword [esp+0x14]
push ecx
mov ecx, dword [esp+0x1c]
sub esp, 0xc
mov edx, esp
sub esp, 0xc
mov dword [edx], eax
mov eax, dword [esp+0x38]
mov dword [edx+0x4], ecx
mov ecx, ebx
mov dword [edx+0x8], eax
mov eax, dword [ecx]
mov edx, esp
mov dword [edx], eax
mov eax, dword [ecx+0x4]
mov ecx, dword [ecx+0x8]
mov dword [edx+0x4], eax
mov dword [edx+0x8], ecx
mov ecx, esi
call ADDR
lea ecx, dword [eax+eax*2]
lea edx, dword [ecx+ecx*4]
mov ecx, dword [ebp+0x408]
lea eax, dword [eax+edx*4]
mov edx, dword [ecx+eax*4+ADDR]
mov ecx, dword [edx+0x38]
call ADDR
mov al, byte [ebp+0x41d]
test al, al
je Ldaa
mov ecx, esi
call ADDR
lea ecx, dword [eax+eax*2]
lea ecx, dword [ecx+ecx*4]
lea edx, dword [eax+ecx*4]
mov eax, dword [ebp+0x408]
test byte [eax+edx*4+ADDR], 0x80
je Ldaa
fld dword [ebp+0x410]
fmul dword [ADDR]
mov ecx, esi
fstp dword [esp+0x14]
fld dword [ebp+0x414]
fmul dword [ADDR]
fstp dword [esp+0x18]
fld dword [ebp+0x418]
fmul dword [ADDR]
fstp dword [esp+0x1c]
call ADDR
lea ecx, dword [eax+eax*2]
lea ecx, dword [ecx+ecx*4]
lea edx, dword [eax+ecx*4]
mov eax, dword [ebp+0x408]
mov ecx, dword [eax+edx*4+ADDR]
mov eax, dword [esp+0x14]
push ecx
mov ecx, dword [esp+0x1c]
sub esp, 0xc
mov edx, esp
sub esp, 0xc
mov dword [edx], eax
mov eax, dword [esp+0x38]
mov dword [edx+0x4], ecx
mov ecx, ebx
mov dword [edx+0x8], eax
mov eax, dword [ecx]
mov edx, esp
mov dword [edx], eax
mov eax, dword [ecx+0x4]
mov ecx, dword [ecx+0x8]
mov dword [edx+0x4], eax
mov dword [edx+0x8], ecx
mov ecx, esi
call ADDR
lea ecx, dword [eax+eax*2]
lea edx, dword [ecx+ecx*4]
mov ecx, dword [ebp+0x408]
lea eax, dword [eax+edx*4]
mov edx, dword [ecx+eax*4+ADDR]
mov ecx, dword [edx+0x38]
call ADDR
mov al, byte [ebp+0x384]
test al, al
jne Lf78
fld dword [ebp+0x6c]
fcomp dword [ADDR]
mov edi, 0x3efae148
fnstsw ax
test ah, 0x1
je Le56
fld dword [ebp+0x6c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne Le56
mov ecx, esi
call ADDR
test al, al
jne Le56
cmp byte [esi+0x3c], 0x16
je Le56
lea ecx, dword [ebp+0x38]
call ADDR
mov byte [ebp+0x1e4], 0x0
fld dword [ebp+0x414]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je Le2f
fld dword [ebp+0x414]
fsub dword [ADDR]
push ecx
lea ecx, dword [ebp+0x4344]
fstp dword [esp]
call ADDR
fld dword [ebp+0x414]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
je Le4f
mov dword [ebp+0x6c], edi
mov dword [ebp+0x414], 0x0
mov byte [ebp+0x41d], 0x0
mov al, byte [esi+0x3c]
test al, al
je Le65
cmp al, 0x23
jne Lef1
fld dword [ebp+0x6c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je Lef1
fld dword [ebp+0x414]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
je Lef1
fld dword [ebp+0x70]
call ADDR
mov dword [esp+0x10], eax
mov al, byte [esi+0x3d]
fild dword [esp+0x10]
test al, 0x2
fsubr dword [ebp+0x70]
jne Leaa
fld dword [ADDR]
jmp Leb0
fld dword [ADDR]
test al, 0x1
mov dword [esp+0x10], 0x0
je Lec4
mov dword [esp+0x10], 0x3e4ccccd
fld st(1)
fcomp st(1)
fnstsw ax
test ah, 0x1
fstp st(0)
je Leef
fcomp dword [esp+0x10]
fnstsw ax
test ah, 0x41
jne Lef1
mov al, byte [ebp+0x41d]
test al, al
jne Lef1
mov ecx, ebp
call ADDR
jmp Lef1
fstp st(0)
mov ecx, dword [ebp+0x408]
cmp dword [ecx+0x40], 0x3
jne Lf03
push ebx
call ADDR
mov eax, dword [ebp+0x408]
mov ecx, dword [eax+0x4c]
test ch, 0x4
je Lf1a
test byte [ADDR], 0x2
je Lf57
fld dword [ebp+0x6c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je Lf57
mov ecx, dword [ebp+0x414]
push ecx
lea ecx, dword [ebp+0x4344]
call ADDR
mov byte [ebp+0x1e4], 0x0
mov dword [ebp+0x414], 0x0
mov byte [ebp+0x41d], 0x0
mov dword [ebp+0x6c], edi
fld dword [ebp+0x6c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je Lf78
mov al, byte [ebp+0x84]
test al, al
jne Lf78
mov ecx, ebp
call ADDR
fld dword [ebp+0x1dc]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x40
jne Lfb4
fld dword [ebp+0x1e0]
fadd dword [ebp+0x1dc]
fst dword [ebp+0x1dc]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne Lfb4
mov dword [ebp+0x1dc], 0x0
mov al, byte [ebp+0x41d]
test al, al
jne L1235
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
fadd dword [ADDR]
fcom dword [ebp+0x6c]
fnstsw ax
test ah, 0x41
jne L11db
fld dword [ebp+0x414]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
je Lffa
fstp dword [ebp+0x6c]
jmp Lffc
fstp st(0)
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x8
je L11c4
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x9
je L11c4
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0xa
je L11c4
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0xb
je L11c4
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0xc
je L11c4
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0xd
je L11c4
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x2
je L1151
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x3
je L1151
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x4
je L1151
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x5
je L1151
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x6
je L1151
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x7
je L1151
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
mov cl, byte [eax+0x3c]
test cl, cl
je L11fe
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x23
je L11fe
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x16
je L11fe
mov byte [ebp+0x1e4], 0x0
mov dword [ebp+0x414], 0x0
jmp L11fe
fld dword [ebp+0x1dc]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x40
je L1170
mov edx, dword [ebp+0x1e0]
mov dword [ebp+0x1dc], edx
mov eax, dword [ebp+0x408]
fld dword [eax+0x38]
fmul dword [ADDR]
fstp dword [ebp+0x414]
mov al, byte [ebp+0x2d8]
test al, al
jne L11fe
fld dword [ebx]
fcomp dword [ADDR]
push -0x1
lea esi, dword [ebp+0x2984]
push 0x1
fnstsw ax
test ah, 0x41
jne L11ac
push 0x4
jmp L11ae
push 0x3
mov ecx, esi
call ADDR
push -0x1
push 0x0
push 0x1
mov ecx, esi
call ADDR
jmp L11fe
mov ecx, dword [ebp+0x408]
fld dword [ecx+0x38]
fmul dword [ADDR]
fstp dword [ebp+0x414]
jmp L11fe
mov edx, dword [ebp+0x408]
fstp st(0)
fld dword [edx+0x38]
fld st(0)
fmul st(1)
fmul dword [ADDR]
fadd dword [ebp+0x414]
fstp dword [ebp+0x414]
fstp st(0)
fld dword [ebp+0x6c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L12dd
fld dword [ebp+0x414]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
je L12dd
mov ecx, ebp
call ADDR
jmp L12dd
mov eax, dword [ebp+0x408]
push ebx
fld dword [eax+0x38]
fld st(0)
fmul st(1)
fmul dword [ADDR]
fadd dword [ebp+0x414]
fstp dword [ebp+0x414]
mov ecx, dword [ebp+0x408]
fstp st(0)
call ADDR
mov esi, eax
cmp byte [esi+0x3c], 0x16
jne L12dd
fld dword [esi+0x14]
fadd dword [ADDR]
fcomp dword [ebp+0x6c]
fnstsw ax
test ah, 0x41
jne L12dd
fld dword [esi+0x14]
fsub dword [ADDR]
fcomp dword [ebp+0x6c]
fnstsw ax
test ah, 0x1
je L12dd
mov ecx, dword [ebp+0x414]
push ecx
lea ecx, dword [ebp+0x4344]
call ADDR
mov edx, dword [ebp+0x408]
push 0x29
mov ecx, ADDR
fld dword [edx+0x38]
fmul dword [ADDR]
fstp dword [ebp+0x414]
fld dword [esi+0x14]
fadd dword [ADDR]
fstp dword [ebp+0x6c]
mov byte [ebp+0x41d], 0x0
mov byte [ebp+0x1e4], 0x1
call ADDR
lea ecx, dword [ebp+0x3f4]
call ADDR
mov al, byte [ebp+0x41c]
test al, al
jne L13ee
mov al, byte [ebp+0x384]
test al, al
jne L13ee
fld dword [ebx+0x8]
fadd dword [ADDR]
mov eax, dword [ebx]
mov ecx, dword [ebx+0x4]
mov dword [esp+0x14], eax
mov edx, eax
mov dword [esp+0x18], ecx
mov eax, ecx
fstp dword [esp+0x1c]
mov ecx, dword [esp+0x1c]
mov dword [esp+0x20], edx
lea edx, dword [esp+0x20]
mov dword [esp+0x28], ecx
mov ecx, dword [ebp+0x408]
push edx
mov dword [esp+0x28], eax
call ADDR
cmp byte [eax+0x3c], 0xe
jne L13ee
fld dword [ebp+0x6c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L13ee
xor esi, esi
mov dword [ebp+0x418], esi
fld dword [ebp+0x70]
fadd dword [ADDR]
call ADDR
mov dword [esp+0x10], eax
fild dword [esp+0x10]
fsub dword [ADDR]
fstp dword [ebp+0x70]
fld dword [ebp+0x4350]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x40
je L13a6
push 0x2f
mov ecx, ADDR
call ADDR
push 0xbea8f5c3
lea ecx, dword [ebp+0x4344]
call ADDR
fld dword [ebp+0x32c]
fadd dword [ebp+0x328]
fst dword [ebp+0x328]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L13f6
mov dword [ebp+0x328], esi
mov al, byte [ebp+0x41d]
test al, al
jne L13f6
mov ecx, ebp
call ADDR
jmp L13f6
xor esi, esi
mov dword [ebp+0x328], esi
cmp dword [ebp+0x350], esi
jne L1559
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x2
je L14b0
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x4
je L14b0
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x5
je L14b0
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x7
je L14b0
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0xa
je L14b0
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x8
je L14b0
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0xa
je L14b0
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0xb
je L14b0
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0xd
jne L1559
mov al, byte [ebp+0x41d]
test al, al
jne L1559
fld dword [ebp+0x6c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
je L1559
mov eax, dword [ebp+0x408]
push ebx
fld dword [eax+0x38]
fmul dword [ADDR]
fstp dword [ebp+0x35c]
mov ecx, dword [ebp+0x408]
call ADDR
cmp byte [eax+0x3c], 0x2
je L1545
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x5
je L1545
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0x8
je L1545
mov ecx, dword [ebp+0x408]
push ebx
call ADDR
cmp byte [eax+0x3c], 0xb
je L1545
mov dword [ebp+0x350], 0x2
mov dword [ebp+0x354], 0xbf800000
jmp L1559
mov dword [ebp+0x350], 0x1
mov dword [ebp+0x354], 0x3f800000
fld dword [ebp+0x1d4]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x40
jne L1591
fld dword [ebp+0x1d8]
fadd dword [ebp+0x1d4]
fst dword [ebp+0x1d4]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1591
mov dword [ebp+0x1d4], esi
mov ecx, dword [ebp+0x408]
fild dword [ecx+0x58]
fstp dword [esp+0x10]
fld dword [ebp+0x70]
fcomp dword [esp+0x10]
fnstsw ax
test ah, 0x1
jne L1926
mov al, byte [ebp+0x41d]
test al, al
jne L1926
mov al, byte [ebp+0x440]
test al, al
jne L168b
cmp dword [ecx+0x40], 0x4
jne L15fa
fld dword [ebp+0x70]
fsub dword [esp+0x10]
push ecx
lea ecx, dword [ebp+0x2e8]
fdiv dword [ebp+0x418]
fsubr dword [ADDR]
fmul dword [ADDR]
fstp dword [esp]
call ADDR
mov ecx, dword [ebp+0x408]
mov dword [ebp+0x444], esi
mov dword [ebp+0x448], 0x3c888889
mov byte [ebp+0x44e], 0x0
fld dword [ecx+0x38]
fmul dword [ADDR]
fld dword [ebp+0x418]
fcomp st(1)
fnstsw ax
test ah, 0x1
jne L1651
fstp st(0)
fld dword [ecx+0x38]
fmul dword [ADDR]
fld dword [ebp+0x418]
fcomp st(1)
fnstsw ax
test ah, 0x41
je L1651
fstp st(0)
fld dword [ebp+0x418]
fstp dword [ebp+0x418]
mov ecx, ADDR
call ADDR
lea ecx, dword [ebp+0x2750]
call ADDR
mov edi, 0x5
push esi
mov ecx, ADDR
mov dword [ebp+0x42e8], edi
call ADDR
mov byte [ebp+0x41c], 0x0
jmp L1690
mov edi, 0x5
mov byte [ebp+0x440], 0x1
mov ecx, dword [ebp+0x408]
fild dword [ecx+0x58]
fadd dword [ADDR]
fcomp dword [ebp+0x70]
fnstsw ax
test ah, 0x1
je L16de
fld dword [ecx+0x38]
fld st(0)
fmulp st(1)
fmul dword [ADDR]
fadd st(0), st(0)
fsubr dword [ebp+0x418]
fst dword [ebp+0x418]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L16de
mov dword [ebp+0x418], esi
fld dword [ebp+0x2748]
fadd dword [ebp+0x2744]
fst dword [ebp+0x2744]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1703
mov dword [ebp+0x2744], esi
fld dword [ebp+0x444]
fadd dword [ebp+0x448]
mov ecx, dword [ebp+0x408]
fstp dword [ebp+0x444]
mov dword [ecx+0x1270fc8], 0x2
fld dword [ebp+0x444]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1759
mov al, byte [ebp+0x44e]
test al, al
jne L1759
push -0x1
push 0x2
push 0x8
mov ecx, ADDR
mov byte [ebp+0x44e], 0x1
call ADDR
fld dword [ebp+0x444]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L17ae
mov eax, dword [ebp+0x408]
mov ecx, dword [eax+0x40]
cmp ecx, esi
je L177e
cmp ecx, 0x1
jne L17ae
mov dl, byte [eax+0x12727f0]
mov ecx, 0x40a33333
cmp dl, 0x1
jne L17a0
mov edx, dword [ebp+0x43c]
test byte [edx+0x5], 0x40
je L17a0
mov dword [ebp+0x444], ecx
cmp dword [eax+0x12727ec], edi
jne L17ae
mov dword [ebp+0x444], ecx
fld dword [ebp+0x444]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L17ed
mov ecx, dword [ebp+0x408]
mov eax, dword [ecx+0x40]
cmp eax, esi
je L17d3
cmp eax, 0x1
jne L17ed
cmp dword [ecx+0x12727ec], edi
je L17ed
fld dword [ebp+0x444]
fsub dword [ebp+0x448]
fstp dword [ebp+0x444]
fld dword [ebp+0x444]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L197a
mov eax, dword [ADDR]
lea ecx, dword [eax+0x24]
mov eax, dword [eax+0x24]
cmp eax, esi
jne L181e
push esi
call ADDR
jmp L197a
cmp eax, 0x4
jne L197a
mov eax, dword [ebp+0x408]
cmp dword [eax+0x12727ec], esi
je L1840
lea ecx, dword [eax+0x12727d8]
call ADDR
mov ecx, dword [ebp+0x408]
cmp dword [ecx+0x40], esi
jne L18a6
mov edx, dword [ADDR]
mov eax, dword [edx+0x12d4644]
mov edx, dword [ecx+0x44]
dec eax
cmp edx, eax
jne L188e
push 0x1
call ADDR
mov ecx, dword [ADDR]
mov dword [ecx+0x1bc], 0x1d
mov edx, dword [ADDR]
mov dword [edx+0x1b8], 0x1a
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x40
ret
push esi
call ADDR
mov eax, dword [ebp+0x408]
mov dword [eax+0x1270fc8], 0x1
jmp L18ad
push 0x1
call ADDR
mov ebp, dword [ebp+0x408]
cmp dword [ebp+0x40], 0x7
jne L18e1
mov ecx, dword [ADDR]
mov dword [ecx+0x1b8], 0x1a
mov edx, dword [ADDR]
mov dword [edx+0x1bc], 0x2
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x40
ret
mov al, byte [ebp+0xff25d1]
test al, al
mov eax, dword [ADDR]
mov ecx, dword [eax+0x1b8]
mov dword [eax+0x1bc], ecx
mov edx, dword [ADDR]
je L1914
mov dword [edx+0x1b8], 0x1a
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x40
ret
mov dword [edx+0x1b8], 0x1b
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x40
ret
mov al, byte [ebp+0x41c]
test al, al
jne L197a
mov al, byte [ebp+0x2d8]
test al, al
jne L197a
fld dword [ecx+0x38]
fmul dword [ADDR]
fld dword [ebp+0x418]
fcomp st(1)
fnstsw ax
test ah, 0x1
jne L1974
fstp st(0)
fld dword [ecx+0x38]
fmul dword [ADDR]
fld dword [ebp+0x418]
fcomp st(1)
fnstsw ax
test ah, 0x41
je L1974
fstp st(0)
fld dword [ebp+0x418]
fstp dword [ebp+0x418]
mov eax, ebx
mov ecx, dword [eax]
mov dword [esp+0x44], ecx
mov edx, dword [eax+0x4]
mov dword [esp+0x48], edx
mov eax, dword [eax+0x8]
mov dword [esp+0x4c], eax
mov al, byte [ebp+0x384]
cmp al, 0x1
jne L19b2
lea ecx, dword [ebp+0x3b0]
mov edx, ebx
mov eax, dword [ecx]
mov dword [edx], eax
mov eax, dword [ecx+0x4]
mov dword [edx+0x4], eax
mov ecx, dword [ecx+0x8]
mov dword [edx+0x8], ecx
lea ecx, dword [ebp+0x2750]
call ADDR
mov al, byte [ebp+0x440]
test al, al
je L19f8
mov eax, dword [ADDR]
mov ecx, 0x10
lea esi, dword [eax+0x15c]
lea edi, dword [eax+0x2cc]
rep movsd dword [edi], dword [esi]
mov eax, dword [ADDR]
xor esi, esi
fld dword [eax+0x300]
fsub dword [ADDR]
fstp dword [eax+0x300]
lea ecx, dword [ebp+0x3c4]
call ADDR
lea ecx, dword [ebp+0x3f0]
call ADDR
lea eax, dword [ebp+0x2964]
mov edx, ebx
fld dword [ebp+0x276c]
mov edi, dword [edx]
mov ecx, eax
fld st(0)
mov dword [ecx], edi
mov edi, dword [edx+0x4]
mov edx, dword [edx+0x8]
mov dword [ecx+0x4], edi
mov dword [ecx+0x8], edx
fmul dword [ebp+0x58]
fstp dword [esp+0x38]
fld st(0)
fmul dword [ebp+0x5c]
fstp dword [esp+0x3c]
fmul dword [ebp+0x60]
fld dword [ebp+0x2768]
fld st(0)
fmul dword [ebp+0x48]
fstp dword [esp+0x14]
fld st(0)
fmul dword [ebp+0x4c]
fstp dword [esp+0x18]
fmul dword [ebp+0x50]
fld dword [ebp+0x2764]
fld st(0)
fmul dword [ebp+0x38]
fstp dword [esp+0x20]
fld st(0)
fmul dword [ebp+0x3c]
fstp dword [esp+0x24]
fmul dword [ebp+0x40]
fld dword [esp+0x20]
fadd dword [esp+0x14]
fstp dword [esp+0x2c]
fld dword [esp+0x24]
fadd dword [esp+0x18]
fstp dword [esp+0x30]
faddp st(1)
fld dword [esp+0x2c]
fadd dword [esp+0x38]
fstp dword [esp+0x20]
fld dword [esp+0x30]
fadd dword [esp+0x3c]
fstp dword [esp+0x24]
faddp st(1)
fld dword [esp+0x20]
fadd dword [eax]
fstp dword [eax]
fld dword [esp+0x24]
fadd dword [eax+0x4]
fstp dword [eax+0x4]
fadd dword [eax+0x8]
fstp dword [eax+0x8]
mov eax, dword [ebp+0x3dc]
cmp eax, esi
jle L1ad6
dec eax
mov dword [ebp+0x3dc], eax
cmp byte [ebp+0x384], 0x1
jne L1ae5
mov eax, dword [esp+0x44]
mov dword [ebx], eax
mov ecx, dword [ebp+0x408]
fld dword [ecx+0x38]
fmul dword [ADDR]
fst dword [ebp+0x35c]
cmp dword [ebp+0x350], esi
je L1b29
fadd dword [ebp+0x358]
fst dword [ebp+0x358]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1b2b
mov dword [ebp+0x358], esi
mov dword [ebp+0x350], esi
jmp L1b2b
fstp st(0)
cmp dword [ebp+0x360], esi
je L1b5e
fld dword [ebp+0x36c]
fadd dword [ebp+0x368]
fst dword [ebp+0x368]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1b5e
mov dword [ebp+0x368], esi
mov dword [ebp+0x360], esi
mov edx, dword [ebp+0x408]
fld dword [edx+0x38]
fmul dword [ADDR]
fst dword [ebp+0x378]
fld dword [ebp+0x374]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1bbf
fadd dword [ebp+0x374]
fst dword [ebp+0x374]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1bb2
lea ecx, dword [ebp+0x150]
mov dword [ebp+0x374], esi
call ADDR
jmp L1bc1
lea ecx, dword [ebp+0x150]
call ADDR
jmp L1bc1
fstp st(0)
mov ecx, dword [ebp+0x408]
cmp dword [ecx+0x40], 0x4
jne L1cb6
mov eax, dword [ecx+0x44]
mov edx, eax
shl edx, 0x6
sub edx, eax
lea edx, dword [eax+edx*4]
lea edx, dword [eax+edx*4]
lea eax, dword [eax+edx*2]
shl eax, 0x6
add eax, ecx
cmp dword [eax+0x944150], 0x1
jne L1cb6
mov dl, byte [ecx+0xff25d0]
test dl, dl
jne L1cb6
mov ecx, dword [ecx+0xff25dc]
mov edx, dword [eax+0x9441bc]
cmp ecx, edx
jl L1c16
mov ecx, edx
mov edx, dword [ebp+0x304]
cmp edx, esi
je L1c2c
mov edi, dword [eax+0x944174]
sub edi, edx
add ecx, edi
jne L1c43
mov cx, word [eax+0x9441c2]
push 0x42000000
push ecx
call ADDR
add esp, 0x8
jmp L1c62
lea edx, dword [ecx+ecx*2]
push 0x42000000
mov ax, word [eax+edx*2+0x9441c2]
push eax
call ADDR
fadd dword [ADDR]
add esp, 0x8
fstp dword [ADDR]
mov ecx, dword [ebp+0x408]
mov al, byte [ecx+0xff25d0]
test al, al
je L1c81
mov edx, dword [ebp+0x70]
mov dword [ADDR], edx
fld dword [ebp+0x70]
fadd dword [ADDR]
fld dword [ADDR]
fcomp st(1)
fnstsw ax
test ah, 0x1
je L1ca6
mov eax, dword [ADDR]
fstp st(0)
mov dword [esp+0x10], eax
jmp L1caa
fstp dword [esp+0x10]
mov ecx, dword [esp+0x10]
push ecx
mov ecx, ebp
call ADDR
mov edx, dword [ebp+0x408]
mov eax, dword [ADDR]
push ecx
fild dword [edx+0x54]
lea ecx, dword [eax+0x4ec10]
fdivr dword [ebp+0x70]
fstp dword [esp]
call ADDR
mov ecx, dword [ebp+0x408]
fild dword [ecx+0x58]
fsub dword [ADDR]
fld dword [ebp+0x70]
fsub dword [ADDR]
fstp dword [esp+0x10]
fcom dword [esp+0x10]
fnstsw ax
test ah, 0x1
jne L1d03
fstp st(0)
fld dword [esp+0x10]
mov eax, dword [ebp+0x275c]
fstp dword [ebp+0x2980]
cmp eax, 0x1
jne L1d5c
fld dword [ebp+0x6c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L1d55
fld dword [ebp+0x414]
fmul dword [ADDR]
fst dword [ebp+0x414]
mov edx, dword [ebp+0x408]
fld dword [edx+0x38]
fld st(0)
fmul st(1)
fmul dword [ADDR]
fsubr st(2)
fstp dword [ebp+0x414]
fstp st(0)
fstp st(0)
mov byte [ebp+0x41d], 0x0
mov al, byte [ebp+0x41d]
test al, al
je L1e0c
fld dword [ebp+0x438]
fadd dword [ebp+0x434]
fst dword [ebp+0x434]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1dd4
mov al, byte [ebp+0x44c]
test al, al
jne L1dd4
push -0x1
push esi
push 0x3
mov ecx, ADDR
call ADDR
mov al, byte [ebp+0x2d8]
mov byte [ebp+0x44c], 0x1
test al, al
jne L1dd4
fld dword [ebp+0x6c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L1dd4
push -0x1
push 0x1
push 0x5
lea ecx, dword [ebp+0x2984]
call ADDR
fld dword [ebp+0x6c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je L1e0c
mov al, byte [ebp+0x44d]
test al, al
jne L1e0c
push -0x1
push 0x2
push 0x1
mov ecx, ADDR
call ADDR
mov byte [ebp+0x44d], 0x1
mov byte [ebp+0x44c], 0x1
fld dword [ebp+0x330]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1e54
fld dword [ebp+0x334]
fadd dword [ebp+0x330]
fst dword [ebp+0x330]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1e54
push -0x1
push 0x2
push 0x7
mov ecx, ADDR
call ADDR
mov dword [ebp+0x330], esi
mov eax, dword [ebp+0x408]
fld dword [eax+0x38]
fmul dword [ADDR]
fld dword [eax+0x38]
fmul dword [ADDR]
fsub st(1)
fmul dword [ADDR]
fadd st(1)
fcomp dword [ebp+0x418]
fnstsw ax
test ah, 0x41
jne L1eda
fcomp dword [ebp+0x418]
fnstsw ax
test ah, 0x1
je L1edc
mov al, byte [ebp+0x41d]
test al, al
jne L1edc
cmp dword [ebp+0x120], 0x2
je L1edc
fld dword [ebp+0x4360]
fadd dword [ebp+0x435c]
fst dword [ebp+0x435c]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1ee2
push -0x1
push 0x1
push 0x6
mov ecx, ADDR
mov dword [ebp+0x435c], esi
call ADDR
jmp L1ee2
fstp st(0)
mov dword [ebp+0x435c], esi
mov ecx, ebp
call ADDR
lea ecx, dword [ebp+0x2a88]
call ADDR
lea ecx, dword [ebp+0x3c6c]
call ADDR
lea ecx, dword [ebp+0x30d8]
call ADDR
lea ecx, dword [ebp+0x34b4]
call ADDR
lea ecx, dword [ebp+0x3890]
call ADDR
mov ecx, dword [ebp+0x408]
add ecx, 0x125e480
call ADDR
lea ecx, dword [ebp+0x2984]
call ADDR
mov ecx, ebp
call ADDR
mov eax, dword [ADDR]
cmp dword [eax+0x1066bf4], 0xa
jge L1f5d
mov ecx, dword [ebp+0x2734]
mov dword [ebp+0x2730], ecx
mov ecx, dword [ebp+0x408]
test dword [ecx+0x4c], ADDR
je L208b
mov al, byte [ebp+0x440]
test al, al
jne L208b
mov al, byte [ebp+0x2d8]
test al, al
jne L208b
mov eax, dword [ebp+0x120]
cmp eax, esi
je L1f9f
cmp eax, 0x4
jne L208b
fld dword [ebp+0x2730]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L1fe0
fld dword [ebp+0x2734]
fadd dword [ebp+0x2730]
fst dword [ebp+0x2730]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L208b
mov dword [ebp+0x2730], esi
jmp L208b
mov al, byte [ecx+0xa854]
test al, al
je L208b
mov dl, byte [ecx+0xff25d0]
test dl, dl
je L2012
mov eax, dword [ecx+0xff25dc]
mov esi, dword [ecx+0xff25d4]
lea eax, dword [eax+eax*2]
test byte [esi+eax*2+0x74], 0x1
jne L2021
test dl, dl
jne L2048
mov eax, dword [ebp+0x43c]
test dword [eax+0x4], 0x4000
je L2044
mov ecx, ebp
call ADDR
push ebp
mov ecx, ebp
call ADDR
fld dword [ebp+0x2734]
fadd dword [ADDR]
fstp dword [ebp+0x2730]
jmp L208b
test dl, dl
je L2062
mov eax, dword [ecx+0xff25dc]
mov ecx, dword [ecx+0xff25d4]
lea eax, dword [eax+eax*2]
test byte [ecx+eax*2+0x74], 0x2
jne L2070
test dl, dl
jne L208b
mov edx, dword [ebp+0x43c]
mov eax, dword [edx+0xc]
test ah, 0x40
je L208b
mov eax, dword [ebp+0x2734]
mov ecx, ebp
mov dword [ebp+0x2730], eax
call ADDR
push ebp
mov ecx, ebp
call ADDR
mov ecx, dword [ebp+0x408]
add ecx, 0x12727d8
call ADDR
mov eax, dword [ebp+0x408]
mov esi, dword [eax+0xfd2b7c]
inc esi
mov dword [eax+0xfd2b7c], esi
mov eax, dword [ebp+0x408]
mov edx, dword [eax+0xff25dc]
inc edx
mov dword [eax+0xff25dc], edx
mov eax, dword [ebp+0x408]
cmp dword [eax+0xff25dc], 0x5208
jne L20df
lea ecx, dword [eax+0x1272828]
call ADDR
mov ecx, dword [ebp+0x408]
add ecx, 0x1272828
call ADDR
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x40
ret
ret 0x43b9
add byte [ebp+-0xeffbc47], ch
mov ecx, 0xb9ad0043
inc ebx
