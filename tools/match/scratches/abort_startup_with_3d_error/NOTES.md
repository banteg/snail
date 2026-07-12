# abort_startup_with_3d_error

Startup failure helper at 0x4088a0. It shows the 3D accelerator/DirectX error
dialog and exits the process. The apparent Binary Ninja tailcall into
`initialize_sub_loc` is just fallthrough into the next function after the noreturn
CRT `exit` call.

Exact match: 100.00%, 7/7 instructions, with four masked operands resolved.
The source needs `MessageBoxA` as a dllimport to emit `call dword [ADDR]`, and
the CRT `exit` declaration needs `__declspec(noreturn)` to avoid a synthetic
cleanup/return tail.
