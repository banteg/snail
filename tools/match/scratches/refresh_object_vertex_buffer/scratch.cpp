// refresh_object_vertex_buffer @ 0x412250 (cdecl)

struct ObjectRenderGeometry;

struct Vector3 {
    float x;
    float y;
    float z;
};

struct ObjectVertex {
    float x;
    float y;
    float z;
};

struct ObjectRenderVertex {
    float x;
    float y;
    float z;
    unsigned int diffuse;
    float u;
    float v;
};

struct ObjectUv {
    float u;
    float v;
};

struct ObjectFaceQuad {
    char unknown_00[0x10];
    ObjectUv uv[4]; // +0x10
};

struct ObjectAnimationFrame {
    ObjectVertex* vertices; // +0x00
    Vector3* normals;       // +0x04
};

struct ObjectAnimation {
    char unknown_00[0x04];
    int frame_index;                  // +0x04
    ObjectAnimationFrame** frames;    // +0x08
    float frame_scale;                // +0x0c
};

struct ObjectVertexBuffer;

struct ObjectVertexBufferVtbl {
    char unknown_00[0x2c];
    int (__stdcall* Lock)(ObjectVertexBuffer* self, int offset, int size,
        ObjectRenderVertex** vertices, int flags);
    int (__stdcall* Unlock)(ObjectVertexBuffer* self);
};

struct ObjectVertexBuffer {
    ObjectVertexBufferVtbl* vtbl;
};

struct ObjectRenderBuffers {
    char unknown_00[0x08];
    ObjectVertexBuffer* vertex_buffer; // +0x08
};

struct ObjectDistort {
    int apply_distort_to_object(ObjectRenderGeometry* object); // @ 0x41aa50
};

struct ObjectRenderGeometry {
    char unknown_00[0x10];
    unsigned int flags; // +0x10
    char unknown_14[0x2c - 0x14];
    int vertex_count; // +0x2c
    char unknown_30[0x38 - 0x30];
    ObjectVertex* vertices; // +0x38
    ObjectVertex* copied_vertices; // +0x3c
    char unknown_40[0x5c - 0x40];
    ObjectFaceQuad* facequads; // +0x5c
    Vector3* vertex_normals; // +0x60
    char unknown_64[0xbc - 0x64];
    ObjectAnimation* animation; // +0xbc
    ObjectRenderBuffers* render_buffers; // +0xc0
    int grouped_vertex_count; // +0xc4
};

void refresh_object_vertex_buffer(ObjectRenderGeometry* object)
{
    unsigned int flags = object->flags;
    if ((flags & 0x200000) != 0) {
        ObjectAnimation* animation = object->animation;
        int frame_index = (int)((float)animation->frame_index * animation->frame_scale);
        object->vertices = animation->frames[frame_index]->vertices;

        frame_index = (int)((float)animation->frame_index * animation->frame_scale);
        object->vertex_normals = animation->frames[frame_index]->normals;

        if ((flags & 0x800000) != 0) {
            ((ObjectDistort*)((char*)object + 0x80))->apply_distort_to_object(object);
        }

        ObjectRenderVertex* vertices;
        object->render_buffers->vertex_buffer->vtbl->Lock(
            object->render_buffers->vertex_buffer, 0, object->grouped_vertex_count * 0x18,
            &vertices, 0);

        int count = object->grouped_vertex_count;
        int i = 0;
        if (count > 0) {
            int destination_offset = 0;
            int source_offset = 0;
            do {
                int* source = (int*)((char*)object->vertices + source_offset);
                int* destination = (int*)((char*)vertices + destination_offset);
                ++i;

                int x = source[0];
                source_offset += 0xc;
                destination[0] = x;

                destination_offset += 0x18;
                int y = source[1];
                destination[1] = y;

                int z = source[2];
                destination[2] = z;
            } while (i < object->grouped_vertex_count);
        }

        object->render_buffers->vertex_buffer->vtbl->Unlock(object->render_buffers->vertex_buffer);
    } else if ((flags & 4) != 0) {
        ObjectRenderVertex* vertices;
        object->render_buffers->vertex_buffer->vtbl->Lock(
            object->render_buffers->vertex_buffer, 0, object->grouped_vertex_count * 0x18,
            &vertices, 0);

        int count = object->grouped_vertex_count;
        int i = 0;
        if (count > 0) {
            int destination_offset = 0;
            int source_offset = 0;
            do {
                int* source = (int*)((char*)object->vertices + source_offset);
                int* destination = (int*)((char*)vertices + destination_offset);
                source_offset += 0xc;

                int x = source[0];
                destination_offset += 0x18;
                destination[0] = x;

                int y = source[1];
                destination[1] = y;

                int z = source[2];
                destination[2] = z;

                int quad_index = i / 4;
                int corner_index = i & 3;
                ++i;

                destination[4] = *(int*)&object->facequads[quad_index].uv[corner_index].u;
                destination[5] = *(int*)&object->facequads[quad_index].uv[corner_index].v;
            } while (i < object->grouped_vertex_count);
        }

        object->render_buffers->vertex_buffer->vtbl->Unlock(object->render_buffers->vertex_buffer);
    }
}
