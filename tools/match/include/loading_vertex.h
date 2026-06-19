#ifndef LOADING_VERTEX_H
#define LOADING_VERTEX_H

struct LoadingVertex {
    float x;
    float y;
    float z;
    float u;
    float v;
};

typedef char LoadingVertex_must_be_0x14[
    (sizeof(LoadingVertex) == 0x14) ? 1 : -1];

#endif
