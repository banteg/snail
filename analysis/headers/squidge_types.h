#ifndef SQUIDGE_TYPES_H
#define SQUIDGE_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the shipped Windows
 * cRSquidge child at Player +0x4344. Android preserves the exact six-float
 * layout and all four method bodies; iOS independently preserves the same
 * authored class-qualified method surface.
 */

typedef struct cRSquidge {
    float y_output;
    float y_velocity;
    float y_phase;
    float z_output;
    float z_velocity;
    float z_phase;
} cRSquidge;

typedef char cRSquidge_must_be_0x18[
    (sizeof(cRSquidge) == 0x18) ? 1 : -1];

#endif
