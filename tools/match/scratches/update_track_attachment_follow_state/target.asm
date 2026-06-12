sub esp, 0x180
push ebx
push ebp
mov ebp, ecx
push esi
fld dword [esp+0x190]
mov ecx, dword [ebp+0xc]
mov esi, dword [ebp+0x4]
push edi
mov edx, dword [esi+0x5c]
lea eax, dword [ecx*8]
sub eax, ecx
lea eax, dword [eax+eax*2]
fmul dword [edx+eax*8+0x8c]
lea edx, dword [edx+eax*8+0x8c]
fst dword [esp+0x10]
fadd dword [ebp+0x10]
fcomp dword [edx]
fnstsw ax
test ah, 0x41
jne L1f7
mov ebx, 0x80
mov edi, 0x3f19999a
fld dword [edx]
fsub dword [ebp+0x10]
inc ecx
mov dword [ebp+0x10], 0x0
mov dword [ebp+0xc], ecx
mov eax, dword [esi+0x44]
fsubr dword [esp+0x10]
shl eax, 0x1
cmp ecx, eax
fstp dword [esp+0x10]
jne L85
push -0x1
push 0x1
push 0x4
mov ecx, ADDR
call ADDR
mov eax, dword [ebp+0x4]
mov cl, byte [eax+0x9c]
test cl, cl
je L1bd
mov eax, dword [eax+0x44]
mov esi, dword [ebp+0xc]
lea ecx, dword [eax+-0x1]
cmp esi, ecx
jne L113
mov ecx, dword [ebp+0x8]
call ADDR
lea ecx, dword [eax+eax*2]
lea edx, dword [ecx+ecx*4]
mov ecx, dword [ADDR]
lea eax, dword [eax+edx*4]
mov edx, dword [ecx+eax*4+ADDR]
mov ecx, dword [ebp+0x8]
mov esi, dword [edx+0x38]
call ADDR
lea ecx, dword [eax+eax*2]
lea ecx, dword [ecx+ecx*4]
lea edx, dword [eax+ecx*4]
mov eax, dword [ADDR]
mov ecx, dword [eax+edx*4+ADDR]
mov edx, dword [esi+0xa4]
mov dword [ecx+0x24], edx
mov ecx, dword [ebp+0x8]
call ADDR
lea ecx, dword [eax+eax*2]
lea ecx, dword [ecx+ecx*4]
lea edx, dword [eax+ecx*4]
mov eax, dword [ADDR]
mov ecx, dword [eax+edx*4+ADDR]
mov dword [ecx+0x34], 0x3f800000
jmp L1bd
lea ecx, dword [eax+eax*2]
mov eax, 0x92492493
imul ecx
add edx, ecx
sar edx, 0x2
mov eax, edx
shr eax, 0x1f
add edx, eax
cmp esi, edx
jne L1bd
mov ecx, dword [ebp+0x8]
call ADDR
lea ecx, dword [eax+eax*2]
lea ecx, dword [ecx+ecx*4]
lea edx, dword [eax+ecx*4]
mov eax, dword [ADDR]
mov eax, dword [eax+edx*4+ADDR]
mov ecx, dword [eax+0x4]
or ecx, ebx
mov dword [eax+0x4], ecx
mov ecx, dword [ebp+0x8]
call ADDR
lea ecx, dword [eax+eax*2]
lea ecx, dword [ecx+ecx*4]
lea edx, dword [eax+ecx*4]
mov eax, dword [ADDR]
mov ecx, dword [eax+edx*4+ADDR]
mov esi, dword [ecx+0x38]
mov ecx, dword [ebp+0x8]
call ADDR
lea ecx, dword [eax+eax*2]
lea edx, dword [ecx+ecx*4]
mov ecx, dword [ADDR]
lea eax, dword [eax+edx*4]
mov edx, dword [ecx+eax*4+ADDR]
mov eax, dword [esi+0xa0]
mov dword [edx+0x24], eax
mov ecx, dword [ebp+0x8]
call ADDR
lea ecx, dword [eax+eax*2]
lea ecx, dword [ecx+ecx*4]
lea edx, dword [eax+ecx*4]
mov eax, dword [ADDR]
mov ecx, dword [eax+edx*4+ADDR]
mov dword [ecx+0x34], edi
mov esi, dword [ebp+0x4]
mov ecx, dword [ebp+0xc]
cmp ecx, dword [esi+0x44]
je L240
fld dword [esp+0x10]
lea eax, dword [ecx*8]
fadd dword [ebp+0x10]
sub eax, ecx
lea edx, dword [eax+eax*2]
mov eax, dword [esi+0x5c]
fcomp dword [eax+edx*8+0x8c]
lea edx, dword [eax+edx*8+0x8c]
fnstsw ax
test ah, 0x41
je L54
fld dword [esp+0x10]
fadd dword [ebp+0x10]
mov ebx, dword [ebp+0xc]
fstp dword [esp+0x14]
mov edx, dword [esp+0x14]
mov dword [ebp+0x10], edx
mov edx, dword [ebp+0x4]
mov eax, dword [edx+0x44]
lea edi, dword [eax+-0x1]
lea eax, dword [ebx*8]
cmp ebx, edi
jne L3f4
mov ecx, dword [edx+0x58]
sub eax, ebx
lea eax, dword [eax+eax*2]
shl eax, 0x3
add ecx, eax
mov esi, dword [ecx+0x90]
mov dword [esp+0x28], esi
jmp L427
fld dword [esp+0x10]
fcomp dword [ADDR]
mov byte [ebp], 0x0
fnstsw ax
test ah, 0x1
jne L25d
mov dword [esp+0x10], 0x3f7fbe77
mov ecx, dword [ebp+0x4]
fld dword [esp+0x194]
mov edx, dword [ecx+0x44]
lea eax, dword [edx*8]
sub eax, edx
lea edx, dword [eax+eax*2]
mov eax, dword [ecx+0x5c]
mov ecx, dword [esp+0x19c]
fmul dword [eax+edx*8+-0x1c]
fst dword [ecx+0x8]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne L29b
mov dword [ecx+0x8], 0x3f800000
mov edx, dword [ebp+0x4]
cmp dword [edx+0x38], 0x1f
jne L39d
fld dword [ecx+0x8]
fmul dword [ADDR]
mov edx, dword [esp+0x198]
push -0x1
push 0x0
push 0xf
fstp dword [ecx+0x4]
mov ecx, dword [ebp+0x4]
fld dword [edx]
mov esi, dword [ecx+0x44]
fld dword [esp+0x1c]
fadd dword [ecx+0x50]
mov ecx, dword [ecx+0x5c]
lea eax, dword [esi*8]
sub eax, esi
lea eax, dword [eax+eax*2]
fld st(0)
fmul dword [ecx+eax*8+-0x88]
lea eax, dword [ecx+eax*8]
mov ecx, dword [ebp+0x8]
add ecx, 0x10
fstp dword [esp+0x84]
fld st(0)
fmul dword [eax+-0x84]
fstp dword [esp+0x88]
fmul dword [eax+-0x80]
fld dword [ecx]
fadd dword [eax+-0x78]
fld dword [eax+-0x74]
fadd dword [ecx+0x4]
fstp dword [esp+0x7c]
fld dword [eax+-0x70]
fadd dword [ecx+0x8]
mov eax, edx
fstp dword [esp+0x80]
fadd dword [esp+0x84]
fstp dword [esp+0x28]
fld dword [esp+0x7c]
fadd dword [esp+0x88]
mov ecx, dword [esp+0x28]
mov dword [eax], ecx
fstp dword [esp+0x2c]
fld dword [esp+0x80]
mov ecx, dword [esp+0x2c]
fadd st(1)
mov dword [eax+0x4], ecx
fstp dword [esp+0x30]
mov ecx, dword [esp+0x30]
fstp st(0)
mov dword [eax+0x8], ecx
fstp dword [edx]
mov edx, dword [ADDR]
mov eax, dword [ebp+0x38]
fld dword [edx+0x74650]
fmul dword [ADDR]
fstp dword [eax+0x2e0]
mov eax, dword [ebp+0x38]
mov ecx, dword [eax+0x2e0]
mov dword [eax+0x2dc], ecx
mov ecx, ADDR
call ADDR
jmp L3ca
mov ecx, dword [edx+0x44]
mov esi, dword [ebp+0x8]
lea eax, dword [ecx*8]
sub eax, ecx
mov ecx, dword [edx+0x5c]
lea eax, dword [eax+eax*2]
fld dword [ecx+eax*8+-0x70]
fadd dword [esi+0x18]
fadd dword [edx+0x50]
mov edx, dword [esp+0x198]
fadd dword [esp+0x10]
fstp dword [edx+0x8]
mov ecx, dword [ebp+0x4]
mov eax, dword [ebp+0x38]
pop edi
pop esi
fld dword [ecx+0x98]
fadd dword [eax+0x370]
pop ebp
pop ebx
fstp dword [eax+0x370]
mov eax, 0x3
add esp, 0x180
ret 0xc
mov esi, dword [edx+0x5c]
sub eax, ebx
fld dword [esp+0x14]
lea eax, dword [eax+eax*2]
mov ecx, dword [edx+0x58]
shl eax, 0x3
add ecx, eax
fdiv dword [esi+eax*1+0x8c]
fld dword [ecx+0x138]
fsub dword [ecx+0x90]
fmulp st(1)
fadd dword [ecx+0x90]
fstp dword [esp+0x28]
cmp ebx, edi
jne L437
mov esi, dword [ecx+0x9c]
mov dword [esp+0x10], esi
jmp L45d
mov esi, dword [edx+0x5c]
fld dword [esp+0x14]
fdiv dword [esi+eax*1+0x8c]
fld dword [ecx+0x144]
fsub dword [ecx+0x9c]
fmulp st(1)
fadd dword [ecx+0x9c]
fstp dword [esp+0x10]
cmp ebx, edi
jne L46d
mov ecx, dword [ecx+0xa0]
mov dword [esp+0x18], ecx
jmp L493
mov esi, dword [edx+0x5c]
fld dword [esp+0x14]
fdiv dword [esi+eax*1+0x8c]
fld dword [ecx+0x148]
fsub dword [ecx+0xa0]
fmulp st(1)
fadd dword [ecx+0xa0]
fstp dword [esp+0x18]
cmp dword [edx+0x38], 0x2a
jne L62c
mov ebx, dword [esp+0x198]
lea eax, dword [esp+0x14]
lea ecx, dword [esp+0x2c]
push eax
fld dword [ebx]
fsub dword [esp+0x2c]
mov eax, dword [esp+0x1c]
push ecx
push 0x3efae148
push ecx
fstp dword [esp]
push eax
mov ecx, edx
call ADDR
mov eax, dword [ebp+0xc]
test eax, eax
je L4db
mov ecx, dword [ebp+0x4]
mov edx, dword [ecx+0x44]
dec edx
cmp eax, edx
jne L555
lea ecx, dword [esp+0x90]
call ADDR
mov eax, dword [esp+0x5c]
mov ecx, dword [esp+0x60]
mov edx, dword [esp+0x64]
mov dword [esp+0xc0], eax
mov eax, dword [ebp+0xc]
mov dword [esp+0xc4], ecx
mov ecx, 0x10
lea esi, dword [esp+0x2c]
lea edi, dword [esp+0x150]
mov dword [esp+0xc8], edx
test eax, eax
rep movsd dword [edi], dword [esi]
jne L52a
mov eax, dword [ebp+0x10]
mov dword [esp+0x18], eax
jmp L537
fld dword [ADDR]
fsub dword [ebp+0x10]
fstp dword [esp+0x18]
mov ecx, dword [esp+0x18]
lea edx, dword [esp+0x150]
push ecx
lea eax, dword [esp+0x94]
push edx
push eax
lea ecx, dword [esp+0x38]
call ADDR
mov ecx, dword [ebp+0xc]
mov edx, dword [ebp+0x4]
lea esi, dword [ebp+0x2c]
lea eax, dword [ecx*8]
sub eax, ecx
lea ecx, dword [eax+eax*2]
mov eax, dword [edx+0x5c]
mov edx, dword [esp+0x19c]
fld dword [eax+ecx*8+0x88]
fmul dword [ebp+0x10]
lea eax, dword [eax+ecx*8]
mov ecx, dword [ebp+0x8]
lea edi, dword [edx+0x4]
fadd dword [ecx+0x18]
mov ecx, dword [esp+0x60]
fadd dword [eax+0x38]
fld dword [esp+0x2c]
fmul dword [esp+0x10]
mov eax, dword [esp+0x5c]
fstp dword [esp+0x2c]
fld dword [esp+0x30]
fmul dword [esp+0x10]
fstp dword [esp+0x30]
fld dword [esp+0x34]
fmul dword [esp+0x10]
fstp dword [esp+0x34]
fld dword [edi]
fadd dword [ebp+0x14]
mov dword [esi], eax
mov eax, dword [esp+0x2c]
mov dword [ebp+0x30], ecx
fstp dword [ebp+0x14]
fstp dword [ebp+0x34]
mov edx, dword [ADDR]
add edx, ADDR
mov dword [edx], eax
mov ecx, dword [esp+0x30]
mov dword [edx+0x4], ecx
mov eax, dword [esp+0x34]
mov dword [edx+0x8], eax
mov ecx, dword [ADDR]
mov edx, dword [esp+0x3c]
add ecx, ADDR
mov dword [ecx], edx
mov eax, dword [esp+0x40]
mov dword [ecx+0x4], eax
mov edx, dword [esp+0x44]
mov dword [ecx+0x8], edx
mov eax, dword [ADDR]
mov ecx, dword [esp+0x4c]
add eax, ADDR
mov dword [eax], ecx
mov edx, dword [esp+0x50]
mov dword [eax+0x4], edx
mov ecx, dword [esp+0x54]
mov dword [eax+0x8], ecx
jmp L861
mov ecx, dword [edx+0x5c]
cmp ebx, edi
fld dword [esp+0x14]
fmul dword [ecx+eax*1+0x80]
lea esi, dword [ecx+eax*1]
mov ecx, dword [ebp+0x8]
fmul dword [esp+0x10]
fadd dword [ecx+0x10]
fadd dword [esi+0x30]
fstp dword [esp+0x1c]
fld dword [esp+0x14]
fmul dword [esi+0x84]
fmul dword [esp+0x10]
fadd dword [ecx+0x14]
fadd dword [esi+0x34]
fstp dword [esp+0x20]
fld dword [esp+0x14]
fmul dword [esi+0x88]
fadd dword [ecx+0x18]
fadd dword [esi+0x38]
fstp dword [esp+0x24]
jne L68c
lea ecx, dword [esp+0x2c]
call ADDR
jmp L728
mov ecx, 0x10
lea edi, dword [esp+0xd0]
inc ebx
rep movsd dword [edi], dword [esi]
fld dword [esp+0x14]
mov esi, dword [edx+0x5c]
lea ecx, dword [ebx*8]
sub ecx, ebx
lea edi, dword [esp+0x110]
lea ecx, dword [ecx+ecx*2]
lea esi, dword [esi+ecx*8]
mov ecx, 0x10
rep movsd dword [edi], dword [esi]
mov dword [esp+0x108], 0x0
mov dword [esp+0x104], 0x0
mov dword [esp+0x100], 0x0
mov dword [esp+0x148], 0x0
mov dword [esp+0x144], 0x0
mov dword [esp+0x140], 0x0
mov edx, dword [edx+0x5c]
push ecx
lea ecx, dword [esp+0xd4]
fdiv dword [edx+eax*1+0x8c]
lea eax, dword [esp+0x114]
fstp dword [esp]
push eax
push ecx
lea ecx, dword [esp+0x38]
call ADDR
fld dword [esp+0x2c]
fmul dword [esp+0x10]
mov edx, dword [esp+0x19c]
mov eax, dword [esp+0x198]
lea esi, dword [ebp+0x2c]
mov ebx, dword [esp+0x198]
lea edi, dword [edx+0x4]
mov ecx, esi
fstp dword [esp+0x2c]
fld dword [esp+0x30]
fmul dword [esp+0x10]
fstp dword [esp+0x30]
fld dword [esp+0x34]
fmul dword [esp+0x10]
fstp dword [esp+0x34]
fld dword [edi]
fadd dword [ebp+0x14]
fst dword [ebp+0x14]
fld dword [esp+0x3c]
fmul st(1)
fstp dword [esp+0x84]
fld dword [esp+0x40]
fmul st(1)
fstp dword [esp+0x88]
fmul dword [esp+0x44]
fld dword [eax]
fsub dword [esp+0x28]
fld st(0)
fmul dword [esp+0x2c]
fstp dword [esp+0x6c]
fld dword [esp+0x30]
fmul st(1)
fstp dword [esp+0x70]
fmul dword [esp+0x34]
fld dword [esp+0x6c]
fadd dword [esp+0x1c]
fstp dword [esp+0x78]
fld dword [esp+0x70]
fadd dword [esp+0x20]
fstp dword [esp+0x7c]
fadd dword [esp+0x24]
fld dword [esp+0x78]
fadd dword [esp+0x84]
fstp dword [esp+0x1c]
fld dword [esp+0x7c]
fadd dword [esp+0x88]
mov edx, dword [esp+0x1c]
mov dword [ecx], edx
fstp dword [esp+0x20]
mov eax, dword [esp+0x20]
fadd st(1)
mov dword [ecx+0x4], eax
fstp dword [esp+0x24]
mov edx, dword [esp+0x24]
mov dword [ecx+0x8], edx
mov eax, dword [ADDR]
mov ecx, dword [esp+0x2c]
add eax, ADDR
fstp st(0)
mov dword [eax], ecx
mov edx, dword [esp+0x30]
mov dword [eax+0x4], edx
mov ecx, dword [esp+0x34]
mov dword [eax+0x8], ecx
mov edx, dword [ADDR]
mov eax, dword [esp+0x3c]
add edx, ADDR
mov dword [edx], eax
mov ecx, dword [esp+0x40]
mov dword [edx+0x4], ecx
mov eax, dword [esp+0x44]
mov dword [edx+0x8], eax
mov ecx, dword [ADDR]
mov edx, dword [esp+0x4c]
add ecx, ADDR
mov dword [ecx], edx
mov eax, dword [esp+0x50]
mov dword [ecx+0x4], eax
mov edx, dword [esp+0x54]
mov dword [ecx+0x8], edx
mov ecx, dword [esp+0x3c]
mov edx, dword [esp+0x40]
lea eax, dword [ebp+0x20]
mov dword [ebp+0x20], ecx
mov ecx, dword [esp+0x44]
mov dword [eax+0x4], edx
mov edx, dword [ebp+0x4]
mov dword [eax+0x8], ecx
mov ecx, dword [edx+0x44]
mov eax, dword [ebp+0xc]
dec ecx
cmp eax, ecx
mov dword [esp+0x18], eax
lea ecx, dword [eax*8]
jne L8b9
sub ecx, eax
mov eax, dword [edx+0x58]
lea ecx, dword [ecx+ecx*2]
shl ecx, 0x3
mov eax, dword [eax+ecx*1+0x98]
mov dword [ebp+0x1c], eax
mov eax, dword [edx+0x58]
mov eax, dword [eax+ecx*1+0x94]
mov dword [ebp+0x18], eax
jmp L974
sub ecx, eax
mov eax, dword [edx+0x58]
lea ecx, dword [ecx+ecx*2]
shl ecx, 0x3
fld dword [eax+ecx*1+0x140]
fsub dword [eax+ecx*1+0x98]
lea ebx, dword [eax+ecx*1]
fcom dword [ADDR]
fnstsw ax
test ah, 0x41
jne L8ea
fsub dword [ADDR]
jmp L8fd
fcom dword [ADDR]
fnstsw ax
test ah, 0x1
je L8fd
fadd dword [ADDR]
mov eax, dword [edx+0x5c]
fld dword [ebp+0x10]
fdiv dword [eax+ecx*1+0x8c]
fmul st(1)
fadd dword [ebx+0x98]
fstp dword [ebp+0x1c]
mov eax, dword [edx+0x58]
fstp st(0)
fld dword [eax+ecx*1+0x13c]
fsub dword [eax+ecx*1+0x94]
lea ebx, dword [eax+ecx*1]
fcom dword [ADDR]
fnstsw ax
test ah, 0x41
jne L940
fsub dword [ADDR]
jmp L953
fcom dword [ADDR]
fnstsw ax
test ah, 0x1
je L953
fadd dword [ADDR]
mov eax, dword [edx+0x5c]
fld dword [ebp+0x10]
fdiv dword [eax+ecx*1+0x8c]
fmul st(1)
fadd dword [ebx+0x94]
mov ebx, dword [esp+0x198]
fstp dword [ebp+0x18]
fstp st(0)
mov eax, dword [edx+0x5c]
fld dword [ebp+0x10]
fdiv dword [eax+ecx*1+0x8c]
mov ecx, dword [ebp+0x38]
fiadd dword [esp+0x18]
fmul dword [edx+0x98]
fidiv dword [edx+0x44]
fstp dword [ebp+0x1c]
cmp dword [ecx+0x275c], 0x1
je La92
fld dword [ebx]
fsub dword [esp+0x28]
fcom dword [ADDR]
fnstsw ax
test ah, 0x1
je L9b6
fchs
fild dword [edx+0x54]
fmul dword [ADDR]
fadd dword [ADDR]
fxch st(0), st(1)
fcompp
fnstsw ax
test ah, 0x41
jne La92
fld dword [ebp+0x14]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
je La92
mov eax, dword [esi]
mov edx, ebx
mov dword [edx], eax
mov ecx, dword [esi+0x4]
mov dword [edx+0x4], ecx
mov eax, dword [esi+0x8]
mov dword [edx+0x8], eax
mov ecx, dword [ebp+0x4]
mov eax, dword [ebp+0x38]
fld dword [ecx+0x98]
fadd dword [eax+0x370]
fstp dword [eax+0x370]
fld dword [ebx]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je La43
fld dword [ADDR]
xor eax, eax
pop edi
fstp dword [ebx]
mov edx, dword [ebp+0x4]
pop esi
pop ebp
pop ebx
mov ecx, dword [edx+0x40]
test ecx, ecx
sete al
add esp, 0x180
ret 0xc
fld dword [ebx]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x41
jne La74
fld dword [ADDR]
xor eax, eax
pop edi
fstp dword [ebx]
mov edx, dword [ebp+0x4]
pop esi
pop ebp
pop ebx
mov ecx, dword [edx+0x40]
test ecx, ecx
sete al
add esp, 0x180
ret 0xc
fld dword [ebx]
xor eax, eax
pop edi
fstp dword [ebx]
mov edx, dword [ebp+0x4]
pop esi
pop ebp
pop ebx
mov ecx, dword [edx+0x40]
test ecx, ecx
sete al
add esp, 0x180
ret 0xc
fld dword [ebp+0x14]
fcomp dword [ADDR]
fnstsw ax
test ah, 0x1
je Laaf
mov dword [ebp+0x14], 0x0
mov dword [edi], 0x0
pop edi
pop esi
pop ebp
xor eax, eax
pop ebx
add esp, 0x180
ret 0xc
