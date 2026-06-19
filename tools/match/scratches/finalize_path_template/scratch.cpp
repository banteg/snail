// finalize_path_template @ 0x42c600 (thiscall)

#include "track_attachment_types.h"
#include "transform_matrix.h"

const int PATH_TEMPLATE_STRIP_MESH_FLAG_RUNTIME_READY = 0x80;
const int PATH_TEMPLATE_STRIP_MESH_FLAG_IMPORTED_X_MESH = 0x100000;

void __fastcall finalize_path_template(AttachmentPathTemplate* path)
{
    int segment_count = path->segment_count;
    path->row_span_count = 0;

    if (segment_count > 0) {
        float* sample_z = &path->secondary_samples->transform.position.z;
        int remaining = segment_count;
        do {
            int row_span = (int)(*sample_z + 1.0f);
            if (row_span > path->row_span_count)
                path->row_span_count = row_span;
            sample_z = (float*)((char*)sample_z + sizeof(AttachmentSample));
            --remaining;
        } while (remaining != 0);
    }

    int i = 0;
    if (segment_count > 0) {
        int sample_offset = 0;
        do {
            AttachmentSample* primary = (AttachmentSample*)((char*)path->primary_samples + sample_offset);
            ((TransformMatrix*)primary->inverse_matrix)->invert_matrix_from_source(
                (TransformMatrix*)&primary->transform);

            AttachmentSample* secondary = (AttachmentSample*)((char*)path->secondary_samples + sample_offset);
            ((TransformMatrix*)secondary->inverse_matrix)->invert_matrix_from_source(
                (TransformMatrix*)&secondary->transform);

            ++i;
            sample_offset += sizeof(AttachmentSample);
        } while (i < path->segment_count);
    }

    int segment_index = 0;
    if (path->segment_count - 1 > 0) {
        int sample_offset = 0;
        do {
            Vector3 cross;
            cross.cross_vectors(
                (Vector3*)((char*)path->primary_samples + sample_offset + 0x20),
                (Vector3*)((char*)path->primary_samples + sample_offset + 0xc8));

            float* lateral_source =
                (float*)((char*)path->primary_samples + sample_offset + 0xa4);
            *lateral_source =
                (float)cross.dot_vector(
                    (Vector3*)((char*)path->primary_samples + sample_offset));

            if (path->is_mirrored_x)
                *lateral_source *= -1.0f;

            if (*lateral_source > 0.0f)
                *lateral_source = 0.0f;

            if (*lateral_source < -0.1f)
                *lateral_source = -0.1f;

            ++segment_index;
            sample_offset += sizeof(AttachmentSample);
        } while (segment_index < path->segment_count - 1);
    }

    (path->primary_samples + path->segment_count - 1)->lateral_source = 0.0f;
    path->strip_mesh->flags |= PATH_TEMPLATE_STRIP_MESH_FLAG_RUNTIME_READY;
    path->strip_mesh->flags &= ~PATH_TEMPLATE_STRIP_MESH_FLAG_IMPORTED_X_MESH;
}
