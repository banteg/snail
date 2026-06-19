// Matrix-backed attachment path-template view, partial.
// iOS Path.o keeps this template owner as cRPath.
//
// This is a sibling view of AttachmentPathTemplate for path-follow scratches
// that need samples as AttachmentSampleMatrixView. It intentionally depends on
// the including scratch's local Vec3 and TransformMatrix views through
// track_attachment_sample_matrix_view.h.
#ifndef TRACK_ATTACHMENT_MATRIX_PATH_VIEW_H
#define TRACK_ATTACHMENT_MATRIX_PATH_VIEW_H

#include "track_attachment_sample_matrix_view.h"

struct AttachmentPathTemplateMatrixView {
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
    unsigned char special_runtime_flag_9c; // +0x9c
    char unknown_9d[0xa8 - 0x9d];
};

#endif
