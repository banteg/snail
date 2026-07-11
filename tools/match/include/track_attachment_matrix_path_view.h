// Matrix-backed cRPath view, partial.
// iOS Path.o preserves the authored owner name.
//
// This is a sibling view of Path for path-follow scratches
// that need samples as AttachmentSampleMatrixView. It intentionally depends on
// the including scratch's local Vec3 and TransformMatrix views through
// track_attachment_sample_matrix_view.h.
#ifndef TRACK_ATTACHMENT_MATRIX_PATH_VIEW_H
#define TRACK_ATTACHMENT_MATRIX_PATH_VIEW_H

#include "track_attachment_sample_matrix_view.h"

struct PathMatrixView {
    char unknown_00[0x38];
    int kind;                              // +0x38
    unsigned char is_mirrored_x;           // +0x3c
    char unknown_3d[0x40 - 0x3d];
    int side_exit_mode;                    // +0x40
    int segment_count;                     // +0x44
    unsigned int row_span_count;           // +0x48, runtime rows stamped by entry tiles
    float segment_count_f;                 // +0x4c
    float width_or_scale;                  // +0x50
    int width_cells;                       // +0x54
    AttachmentSampleMatrixView* primary_samples;   // +0x58
    AttachmentSampleMatrixView* secondary_samples; // +0x5c
    char unknown_60[0x98 - 0x60];
    union {
        float installed_heading_delta;
        int installed_heading_bits;
    };                                     // +0x98
    union {
        unsigned char has_entry_mesh_transition; // +0x9c
        unsigned char special_runtime_flag_9c;
    };
    char unknown_9d[0xa0 - 0x9d];
    void* entry_transition_strip_mesh; // +0xa0
    void* entry_base_strip_mesh;       // +0xa4
};

#endif
