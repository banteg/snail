// calc_path_length_z @ 0x42c600 (cRPath::CalcLengthZ)

#include <stddef.h>

#include "track_attachment_types.h"
#include "transform_matrix.h"

void __fastcall Path::calc_path_length_z()
{
    int segment_count = this->segment_count;
    this->row_span_count = 0;

    if (segment_count > 0) {
        float* sample_z = &this->secondary_samples->transform.position.z;
        int remaining = segment_count;
        do {
            int row_span = (int)(*sample_z + 1.0f);
            if (row_span > this->row_span_count)
                this->row_span_count = row_span;
            sample_z = (float*)((char*)sample_z + sizeof(AttachmentSample));
            --remaining;
        } while (remaining != 0);
    }

    int i = 0;
    if (segment_count > 0) {
        int sample_offset = 0;
        do {
            AttachmentSample* primary = (AttachmentSample*)((char*)this->primary_samples + sample_offset);
            primary->inverse_matrix.invert_matrix_from_source(primary->transform);

            AttachmentSample* secondary = (AttachmentSample*)((char*)this->secondary_samples + sample_offset);
            secondary->inverse_matrix.invert_matrix_from_source(secondary->transform);

            ++i;
            sample_offset += sizeof(AttachmentSample);
        } while (i < this->segment_count);
    }

    int segment_index = 0;
    if (this->segment_count - 1 > 0) {
        int sample_offset = 0;
        do {
            Vector3 cross;
            AttachmentSample* primary = (AttachmentSample*)((char*)this->primary_samples + sample_offset);
            AttachmentSample* next = primary + 1;
            cross.cross_vectors(
                &primary->transform.basis_forward,
                &next->transform.basis_forward);

            *(float*)((char*)this->primary_samples + sample_offset
                + offsetof(AttachmentSample, lateral_source)) =
                (float)cross.dot_vector(
                    *(Vector3*)((char*)this->primary_samples + sample_offset));

            if (this->is_mirrored_x)
                *(float*)((char*)this->primary_samples + sample_offset
                    + offsetof(AttachmentSample, lateral_source)) *= -1.0f;

            if (*(float*)((char*)this->primary_samples + sample_offset
                    + offsetof(AttachmentSample, lateral_source)) > 0.0f)
                *(float*)((char*)this->primary_samples + sample_offset
                    + offsetof(AttachmentSample, lateral_source)) = 0.0f;

            if (*(float*)((char*)this->primary_samples + sample_offset
                    + offsetof(AttachmentSample, lateral_source)) < -0.1f)
                *(float*)((char*)this->primary_samples + sample_offset
                    + offsetof(AttachmentSample, lateral_source)) = -0.1f;

            ++segment_index;
            sample_offset += sizeof(AttachmentSample);
        } while (segment_index < this->segment_count - 1);
    }

    (this->primary_samples + this->segment_count - 1)->lateral_source = 0.0f;
    this->strip_mesh->flags |= OBJECT_FLAG_TEXTURE_TRANSFORM;
    this->strip_mesh->flags &= ~OBJECT_FLAG_DISABLE_CULLING;
}
