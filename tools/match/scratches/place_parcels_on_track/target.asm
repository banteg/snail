sub esp, 0x214
mov eax, dword [ecx+0x40]
push ebx
push ebp
push esi
cmp eax, 0x1
push edi
mov dword [esp+0x28], ecx
jne L26
call ADDR
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x214
ret
xor esi, esi
cmp eax, esi
je L35
cmp eax, 0x7
jne L951
xor eax, eax
mov dword [eax+ADDR], esi
mov dword [eax+ADDR], esi
add eax, 0x20c
cmp eax, 0x106000
jl L37
mov eax, dword [ecx+0xa874]
xor ebp, ebp
cmp eax, esi
mov dword [esp+0x14], esi
mov dword [esp+0x20], ebp
mov dword [esp+0x2c], esi
jle L398
lea eax, dword [esp+0x94]
lea ebx, dword [ecx+0xa87c]
mov dword [esp+0x30], eax
mov dword [esp+0x10], ebx
mov ecx, dword [esp+0x30]
xor eax, eax
mov dword [esp+0x1c], eax
mov dword [esp+0x24], eax
mov dword [ecx], 0x2710
mov ecx, dword [esp+0x2c]
mov edx, ecx
shl edx, 0x6
add edx, ecx
lea ecx, dword [ecx+edx*2]
shl ecx, 0x2
jmp Lab
mov eax, dword [esp+0x24]
mov edi, dword [ebx]
xor edx, edx
test edi, edi
jle L321
lea edi, dword [ebx+0x10]
mov dword [esp+0x34], edi
lea edi, dword [ebx+0x818]
mov dword [esp+0x18], edi
jmp Lce
mov eax, dword [esp+0x24]
test byte [edi+-0x8], 0x1
je L1a1
cmp dword [edi+-0x4], eax
jne L1a1
test eax, eax
jne L154
mov eax, ebp
shl eax, 0x6
add eax, ebp
lea eax, dword [ebp+eax*2]
shl eax, 0x2
mov dword [eax+ADDR], esi
mov ebx, dword [eax+ADDR]
shl ebx, 0x4
mov dword [ebx+eax*1+ADDR], edx
mov ebx, dword [eax+ADDR]
mov ebp, dword [edi]
shl ebx, 0x4
lea ebx, dword [ebx+eax*1+ADDR]
mov dword [ebx], ebp
mov ebp, dword [edi+0x4]
mov dword [ebx+0x4], ebp
mov edi, dword [edi+0x8]
mov ebp, dword [esp+0x20]
mov dword [ebx+0x8], edi
mov dword [eax+ADDR], 0x0
mov ebx, dword [eax+ADDR]
inc ebx
inc ebp
mov dword [eax+ADDR], ebx
mov eax, dword [esp+0x14]
inc eax
mov dword [esp+0x20], ebp
mov dword [esp+0x14], eax
jmp L1a1
mov dword [ecx+ADDR], esi
mov eax, dword [ecx+ADDR]
shl eax, 0x4
mov dword [eax+ecx*1+ADDR], edx
mov eax, dword [ecx+ADDR]
mov ebx, dword [edi]
shl eax, 0x4
lea eax, dword [eax+ecx*1+ADDR]
mov dword [eax], ebx
mov ebx, dword [edi+0x4]
mov dword [eax+0x4], ebx
mov edi, dword [edi+0x8]
mov dword [eax+0x8], edi
mov eax, dword [esp+0x24]
mov dword [ecx+ADDR], eax
mov eax, dword [ecx+ADDR]
inc eax
mov dword [ecx+ADDR], eax
mov edi, dword [esp+0x34]
mov eax, ebp
shl eax, 0x6
add eax, ebp
mov dword [esp+0x20], 0x0
mov dword [esp+0x38], edi
lea eax, dword [ebp+eax*2]
shl eax, 0x2
mov edi, dword [esp+0x38]
movsx ebx, byte [edi]
mov edi, dword [esp+0x24]
add edi, 0x30
cmp ebx, edi
jne L2dc
mov edi, dword [esp+0x24]
test edi, edi
jne L267
fild dword [esp+0x20]
mov dword [eax+ADDR], esi
mov edi, dword [eax+ADDR]
shl edi, 0x4
fsub dword [ADDR]
mov dword [edi+eax*1+ADDR], edx
mov edi, dword [eax+ADDR]
shl edi, 0x4
fadd dword [ADDR]
lea edi, dword [edi+eax*1+ADDR]
mov dword [esp+0x40], 0x0
mov dword [esp+0x44], 0x0
add eax, 0x20c
fstp dword [esp+0x3c]
mov ebx, dword [esp+0x3c]
mov dword [edi], ebx
mov ebx, dword [esp+0x40]
mov dword [edi+0x4], ebx
mov ebx, dword [esp+0x44]
mov dword [edi+0x8], ebx
mov edi, dword [esp+0x14]
mov dword [eax+ADDR], 0x0
mov ebx, dword [eax+ADDR]
inc ebx
inc ebp
mov dword [eax+ADDR], ebx
inc edi
mov dword [esp+0x14], edi
jmp L2dc
fild dword [esp+0x20]
mov dword [ecx+ADDR], esi
mov edi, dword [ecx+ADDR]
shl edi, 0x4
fsub dword [ADDR]
mov dword [edi+ecx*1+ADDR], edx
mov edi, dword [ecx+ADDR]
shl edi, 0x4
fadd dword [ADDR]
lea edi, dword [edi+ecx*1+ADDR]
mov dword [esp+0x4c], 0x0
mov dword [esp+0x50], 0x0
fstp dword [esp+0x48]
mov ebx, dword [esp+0x48]
mov dword [edi], ebx
mov ebx, dword [esp+0x4c]
mov dword [edi+0x4], ebx
mov ebx, dword [esp+0x50]
mov dword [edi+0x8], ebx
mov edi, dword [esp+0x24]
mov dword [ecx+ADDR], edi
mov edi, dword [ecx+ADDR]
inc edi
mov dword [ecx+ADDR], edi
mov edi, dword [esp+0x20]
mov ebx, dword [esp+0x38]
inc edi
add ebx, 0x100
cmp edi, 0x8
mov dword [esp+0x20], edi
mov dword [esp+0x38], ebx
jl L1bf
mov edi, dword [esp+0x18]
mov ebx, dword [esp+0x34]
inc edx
add edi, 0x38
inc ebx
mov dword [esp+0x20], ebp
mov dword [esp+0x34], ebx
mov ebx, dword [esp+0x10]
mov dword [esp+0x18], edi
cmp edx, dword [ebx]
jl Lca
mov eax, dword [ecx+ADDR]
test eax, eax
jle L35e
mov edx, dword [ecx+ADDR]
mov edi, dword [esp+edx*4+0x94]
lea edx, dword [esp+edx*4+0x94]
cmp eax, edi
jge L345
mov dword [edx], eax
cmp eax, dword [esp+0x1c]
jle L34f
mov dword [esp+0x1c], eax
mov edx, dword [esp+0x2c]
inc edx
add ecx, 0x20c
mov dword [esp+0x2c], edx
mov eax, dword [esp+0x24]
inc eax
cmp eax, 0xa
mov dword [esp+0x24], eax
jl La7
mov eax, dword [esp+0x28]
mov edi, dword [esp+0x30]
inc esi
add edi, 0x4
mov ecx, dword [eax+0xa874]
add ebx, 0x4220
cmp esi, ecx
mov dword [esp+0x30], edi
mov dword [esp+0x10], ebx
jl L80
mov ebx, dword [esp+0x28]
mov eax, 0x51eb851f
mov edi, dword [ebx+0x1b01e0]
lea ecx, dword [edi+edi*4]
shl ecx, 0x4
imul ecx
sar edx, 0x5
mov ecx, edx
mov eax, dword [ebx+0xa874]
shr ecx, 0x1f
add edx, ecx
mov esi, edx
mov edx, dword [esp+0x1c]
sub esi, edx
mov edx, dword [esp+0x14]
test eax, eax
mov dword [esp+0x24], esi
mov dword [esp+0x18], edx
jle L402
mov dword [esp+0x10], eax
mov eax, dword [esp+0x18]
lea edx, dword [esp+0x94]
mov ecx, dword [edx]
cmp ecx, 0x2710
je L3f2
add eax, ecx
mov ecx, dword [esp+0x10]
add edx, 0x4
dec ecx
mov dword [esp+0x10], ecx
jne L3e6
jmp L406
mov eax, dword [esp+0x18]
cmp eax, edi
jge L41e
lea eax, dword [ebx+0x1b0150]
push eax
push ADDR
call ADDR
add esp, 0x8
mov ecx, dword [ebx+0x1b01e0]
mov eax, dword [esp+0x14]
sub ecx, esi
cmp ecx, eax
jle L442
add ebx, 0x1b0150
push ebx
push ADDR
call ADDR
add esp, 0x8
xor ebx, ebx
test esi, esi
mov dword [esp+0x14], ebx
jle L68c
mov eax, dword [esp+0x2c]
test eax, eax
jle L68c
fild dword [esp+0x2c]
push ADDR
push ecx
fstp dword [esp]
call ADDR
add esp, 0x8
call ADDR
mov edx, eax
mov dword [esp+0x10], 0x0
shl edx, 0x6
add edx, eax
lea edi, dword [eax+edx*2]
shl edi, 0x2
mov eax, dword [edi+ADDR]
add ebx, eax
test eax, eax
mov dword [esp+0x14], ebx
jle L57f
lea ebx, dword [edi+ADDR]
mov eax, dword [edi+ADDR]
mov esi, dword [esp+0x28]
mov ecx, eax
shl ecx, 0x5
add ecx, eax
shl ecx, 0x4
add ecx, eax
shl ecx, 0x5
mov eax, dword [ecx+esi*1+0xa878]
mov ecx, dword [ebx+-0x4]
add eax, ecx
mov dword [esp+0x18], eax
lea ecx, dword [eax+eax*2]
lea edx, dword [ecx+ecx*4]
lea eax, dword [eax+edx*4]
lea esi, dword [esi+eax*4]
test byte [esi+ADDR], 0x10
je L4fb
mov ecx, dword [esp+0x28]
add ecx, 0x1b0150
push ecx
push ADDR
call ADDR
add esp, 0x8
mov ecx, dword [esi+ADDR]
mov edx, ebx
or ecx, 0x11
lea eax, dword [esi+ADDR]
fild dword [esp+0x18]
mov dword [esi+ADDR], ecx
mov ecx, dword [edx]
mov dword [esp+0x1c], eax
mov dword [eax], ecx
mov ecx, dword [edx+0x4]
mov dword [eax+0x4], ecx
mov edx, dword [edx+0x8]
mov dword [eax+0x8], edx
fadd dword [esi+ADDR]
fadd dword [ADDR]
fstp dword [esi+ADDR]
fld dword [esi+ADDR]
fadd dword [ADDR]
fstp dword [esi+ADDR]
test byte [esi+ADDR], 0x20
je L565
mov eax, dword [esp+0x1c]
fld dword [eax]
fmul dword [ADDR]
fstp dword [eax]
mov eax, dword [esp+0x10]
mov ecx, dword [edi+ADDR]
inc eax
add ebx, 0x10
cmp eax, ecx
mov dword [esp+0x10], eax
jl L4a5
mov eax, dword [edi+ADDR]
xor ecx, ecx
mov dword [esp+0x38], eax
mov eax, dword [esp+0x2c]
test eax, eax
mov dword [esp+0x1c], ecx
jle L67c
lea edi, dword [eax+-0x1]
mov edx, ADDR
mov esi, ADDR
mov dword [esp+0x18], edi
mov dword [esp+0x34], edx
mov dword [esp+0x30], esi
mov ebx, dword [esp+0x38]
cmp dword [esi], ebx
jne L65b
cmp ecx, edi
jge L63e
mov eax, edx
mov edx, edi
sub edx, ecx
mov dword [esp+0x10], edx
mov esi, dword [eax]
xor edx, edx
test esi, esi
jle L608
lea ecx, dword [eax+-0x40c]
lea esi, dword [ecx+0x20c]
mov edi, ecx
inc edx
add ecx, 0x10
mov ebx, dword [esi]
mov dword [edi], ebx
mov ebx, dword [esi+0x4]
mov dword [edi+0x4], ebx
mov ebx, dword [esi+0x8]
mov dword [edi+0x8], ebx
mov esi, dword [esi+0xc]
mov dword [edi+0xc], esi
mov esi, dword [eax]
cmp edx, esi
jl L5dc
mov ecx, dword [esp+0x1c]
mov edx, dword [eax]
mov dword [eax+-0x20c], edx
mov edx, dword [eax+0x8]
mov dword [eax+-0x204], edx
mov edx, dword [eax+0x4]
mov dword [eax+-0x208], edx
mov edx, dword [esp+0x10]
add eax, 0x20c
dec edx
mov dword [esp+0x10], edx
jne L5ce
mov edi, dword [esp+0x18]
mov edx, dword [esp+0x34]
mov esi, dword [esp+0x30]
mov ebx, dword [esp+0x2c]
dec ecx
sub esi, 0x20c
sub edx, 0x20c
dec ebx
dec edi
mov dword [esp+0x2c], ebx
mov dword [esp+0x18], edi
mov eax, ebx
inc ecx
add esi, 0x20c
add edx, 0x20c
cmp ecx, eax
mov dword [esp+0x1c], ecx
mov dword [esp+0x30], esi
mov dword [esp+0x34], edx
jl L5b4
mov ebx, dword [esp+0x14]
mov ecx, dword [esp+0x24]
cmp ebx, ecx
jl L454
mov eax, dword [esp+0x28]
cmp ebx, dword [eax+0x1b01e0]
jge L825
lea ecx, dword [ebp+-0x1]
mov dword [esp+0x1c], ecx
test ebp, ebp
jle L825
fild dword [esp+0x20]
push ADDR
push ecx
fstp dword [esp]
call ADDR
add esp, 0x8
call ADDR
mov ebx, eax
mov ecx, dword [esp+0x14]
mov edx, ebx
mov edi, dword [esp+0x28]
shl edx, 0x6
add edx, ebx
lea esi, dword [ebx+edx*2]
shl esi, 0x2
mov eax, dword [esi+ADDR]
add ecx, eax
mov eax, dword [esi+ADDR]
mov edx, eax
mov dword [esp+0x14], ecx
shl edx, 0x5
add edx, eax
lea ecx, dword [esi+ADDR]
shl edx, 0x4
add edx, eax
mov dword [esp+0x18], ecx
shl edx, 0x5
mov eax, dword [edx+edi*1+0xa878]
mov edx, dword [ecx]
add eax, edx
mov dword [esp+0x10], eax
lea ecx, dword [eax+eax*2]
lea ecx, dword [ecx+ecx*4]
lea edx, dword [eax+ecx*4]
mov al, byte [edi+edx*4+ADDR]
test al, 0x10
lea edi, dword [edi+edx*4]
je L744
mov eax, dword [esp+0x28]
add eax, 0x1b0150
push eax
push ADDR
call ADDR
add esp, 0x8
mov edx, dword [edi+ADDR]
lea eax, dword [edi+ADDR]
or edx, 0x11
lea ecx, dword [esi+ADDR]
fild dword [esp+0x10]
mov dword [edi+ADDR], edx
mov esi, dword [ecx]
mov edx, eax
mov dword [edx], esi
mov esi, dword [ecx+0x4]
mov dword [edx+0x4], esi
mov ecx, dword [ecx+0x8]
mov dword [edx+0x8], ecx
fadd dword [edi+ADDR]
fadd dword [ADDR]
fstp dword [edi+ADDR]
fld dword [edi+ADDR]
fadd dword [ADDR]
fstp dword [edi+ADDR]
test byte [edi+ADDR], 0x20
je L7ac
fld dword [eax]
fmul dword [ADDR]
fstp dword [eax]
mov edx, dword [esp+0x1c]
cmp ebx, edx
jge L801
mov eax, dword [esp+0x18]
sub edx, ebx
lea ecx, dword [eax+0x20c]
mov edi, eax
mov esi, ecx
dec edx
mov ebx, dword [esi]
mov dword [edi], ebx
mov ebx, dword [esi+0x4]
mov dword [edi+0x4], ebx
mov ebx, dword [esi+0x8]
mov dword [edi+0x8], ebx
mov esi, dword [esi+0xc]
mov dword [edi+0xc], esi
mov esi, dword [eax+0x40c]
mov dword [eax+0x200], esi
mov esi, dword [eax+0x414]
mov dword [eax+0x208], esi
mov dword [eax+0x204], 0x0
mov eax, ecx
jne L7ba
mov edx, dword [esp+0x1c]
mov eax, dword [esp+0x28]
dec ebp
dec edx
mov ecx, dword [eax+0x1b01e0]
mov dword [esp+0x1c], edx
mov edx, dword [esp+0x14]
mov dword [esp+0x20], ebp
cmp edx, ecx
jl L6a3
mov ebp, dword [esp+0x28]
mov esi, dword [esp+0x14]
mov eax, dword [ebp+0x1b01e0]
cmp esi, eax
je L868
lea ecx, dword [ebp+0x1b0150]
push ecx
push eax
push ADDR
call ADDR
mov ecx, dword [ebp+0x1b01e8]
add esp, 0xc
test ecx, ecx
je L868
mov eax, dword [ebp+0x1b01e0]
imul eax, esi
cdq
idiv ecx
mov dword [ebp+0x1b01e8], eax
mov dword [ebp+0x1b01e0], esi
mov eax, dword [ebp+0x54]
test eax, eax
mov dword [esp+0x10], 0x0
jle L951
lea esi, dword [ebp+ADDR]
mov eax, dword [esi]
test al, 0x1
je L937
test al, 0x40
je L937
mov ecx, dword [esi+0xa4]
call ADDR
fld dword [esi+0x98]
mov ebx, eax
call ADDR
mov edi, eax
sub edi, ebx
jns L8b9
xor edi, edi
mov ecx, dword [esi+0xa4]
mov edx, dword [ecx+0x38]
cmp dword [edx+0x38], 0x2a
jne L91a
lea eax, dword [esp+0x18]
mov ecx, edx
push eax
mov eax, dword [esi+0x94]
lea edx, dword [esp+0x58]
push edx
mov edx, dword [esi+0x90]
push eax
lea eax, dword [edi*8]
sub eax, edi
push edx
mov edx, dword [ecx+0x58]
lea eax, dword [eax+eax*2]
mov eax, dword [edx+eax*8+0xa0]
push eax
call ADDR
mov ecx, dword [esp+0x84]
mov edx, dword [esp+0x88]
mov dword [esi+0x90], ecx
mov dword [esi+0x94], edx
jmp L937
lea ebx, dword [esi+0x90]
push ebx
call ADDR
push eax
mov eax, dword [esi+0xa4]
push edi
push ebx
mov ecx, dword [eax+0x38]
call ADDR
mov eax, dword [esp+0x10]
mov ecx, dword [ebp+0x54]
inc eax
add esi, 0xf4
cmp eax, ecx
mov dword [esp+0x10], eax
jl L887
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x214
ret
