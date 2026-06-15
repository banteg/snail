// Matrix-backed attachment sample view, partial.
//
// This intentionally depends on the including scratch's local Vec3 and
// TransformMatrix views. TransformMatrix is still divergent across scratches,
// but these two attachment-follow users agree on the sample fields.
#ifndef TRACK_ATTACHMENT_SAMPLE_MATRIX_VIEW_H
#define TRACK_ATTACHMENT_SAMPLE_MATRIX_VIEW_H

struct AttachmentSampleMatrixView {
    TransformMatrix transform;       // +0x00
    char unknown_40[0x40];
    Vec3 delta_dir_to_next;          // +0x80
    float delta_length;              // +0x8c
    float center_x;                  // +0x90
    float rotation_scalar_94;        // +0x94
    float rotation_scalar_98;        // +0x98
    float lateral_scale;             // +0x9c
    float special_scalar;            // +0xa0
    char unknown_a4[0x04];
};

#endif
