// sort_object_faces_by_texture_group @ 0x419fd0 (cdecl)

#include "object_render_types.h"

void sort_object_faces_by_texture_group(Object* object)
{
    int base_index = 0;
    int grouped_swaps = 0;
    int face_count = object->facequad_count;
    ObjectFaceQuad* facequads = object->facequads;

    if (face_count > 0) {
        do {
            TextureRef* texture_ref = facequads[base_index].texture_ref;
            int scan_index = base_index + 1;

            if (scan_index < face_count) {
                ObjectFaceQuad* scan_face = &facequads[scan_index];
                int insert_index = scan_index;
                ObjectFaceQuad* insert_face = &facequads[base_index + 1];

                do {
                    if (scan_face->texture_ref == texture_ref) {
                        if (scan_index == insert_index) {
                            ++base_index;
                            ++insert_face;
                            ++insert_index;
                        } else {
                            ObjectFaceQuad swap = *insert_face;
                            *insert_face = *scan_face;
                            *scan_face = swap;
                            ++base_index;
                            ++insert_face;
                            ++insert_index;
                            ++grouped_swaps;
                        }
                    }

                    ++scan_index;
                    ++scan_face;
                } while (scan_index < object->facequad_count);
            }

            face_count = object->facequad_count;
            ++base_index;
        } while (base_index < face_count);
    }
    (void)grouped_swaps;
}
