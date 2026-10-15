// Raw-copy view for a 3-float position when x/z are moved as integer bits.
#ifndef POSITION_BITS_H
#define POSITION_BITS_H

struct PositionBits {
    int x;
    float y;
    int z;
};

#endif
