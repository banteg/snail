// Shared ObjectProc.o functions, partial: procedural track-tile objects.
#ifndef OBJECT_PROC_H
#define OBJECT_PROC_H

#include "object_fwd.h"

void ObjectProcTileFast(Object* object, char* texture_path, float x_offset); // @ 0x41a0b0
void ObjectProcTileFastRamp(int selector, Object* object); // @ 0x41a170
void ObjectProcTileFloorFast(Object* object, char* texture_path, float x_offset); // @ 0x41a1c0
void ObjectProcTileFloorCornerFast(int selector, Object* object, char* texture_path); // @ 0x41a290
void ObjectProcFringe(
    Object* object, int edge_selector, int orientation,
    int row_selector, int column_selector, char* texture_path); // @ 0x41a4d0

#endif
