// Shared Direct3DDevice8 wrapper, partial.
//
// The vtable shape is scratch-local: different renderer functions recover
// different method windows. The stable shared part is only the vtbl pointer.
#ifndef DIRECT3D_DEVICE8_VIEW_H
#define DIRECT3D_DEVICE8_VIEW_H

struct Direct3DDevice8Vtbl;

struct Direct3DDevice8 {
    Direct3DDevice8Vtbl* vtbl;
};

#endif
