// initialize_track_row_runtime @ 0x408590 (thiscall, ret)
// Authored aggregate owner: cRSubRow::cRSubRow().

#include "track_attachment_types.h"

extern void* g_row_model_vtable; // off_497330 / data_497330

inline cRRowModel::cRRowModel()
{
    vtable = &g_row_model_vtable;
}

cRSubRow::cRSubRow()
{
}
