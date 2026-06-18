// request_object_animation @ 0x430a70 (thiscall, ret 0x10)

#include "object_animation_types.h"
#include "object_render_types.h"

void* allocate_tracked_memory(int size, char* name); // @ 0x431b60
int report_errorf(char* format, ...); // @ 0x431cc0
extern "C" double __cdecl floor(double value);

struct XAnimationKeyframe {
    char unknown_00[0x24];
    Object* object; // +0x24
    char unknown_28[0x7c - 0x28];
    int frame_number; // +0x7c
};

ObjectAnimation* Object::request_object_animation(
    int keyframe_count, void* keyframes_raw, float progress_step, unsigned short flags)
{
    XAnimationKeyframe* keyframes = (XAnimationKeyframe*)keyframes_raw;

    for (int i = 0; i < keyframe_count; ++i) {
        if (keyframes[i].object->vertex_count != vertex_count) {
            report_errorf("Anim tween Vertices don't match Frame %i",
                keyframes[i].frame_number);
            return 0;
        }
    }

    this->flags |= 0x200000;

    int generated_frame_count = (int)(1.0f / progress_step);
    animation = (ObjectAnimation*)allocate_tracked_memory(0x14, "Object Animation");
    animation->generated_frame_count = generated_frame_count;
    animation->flags = flags;
    animation->progress = 0.0f;
    animation->progress_step = progress_step;
    animation->frames = (ObjectAnimationFrame**)allocate_tracked_memory(
        generated_frame_count << 2, "Object Animation Frame array");

    int current_keyframe = 0;
    int current_time = keyframes[0].frame_number;
    int next_time;
    if (keyframe_count == 1)
        next_time = keyframes[0].frame_number;
    else
        next_time = keyframes[1].frame_number;

    int last_frame = keyframes[keyframe_count - 1].frame_number;
    for (int frame = 0; frame < generated_frame_count; ++frame) {
        animation->frames[frame] =
            (ObjectAnimationFrame*)allocate_tracked_memory(8, "Object Animation Frame");
        animation->frames[frame]->vertices =
            (Vector3*)allocate_tracked_memory(vertex_count * 0xc,
                "Object Animation Frame Vertices");
        animation->frames[frame]->facequad_normals =
            (Vector3*)allocate_tracked_memory(facequad_count * 0x18,
                "Object Animation Frame FaceQuad Normals");

        float frame_time_float =
            (float)(last_frame * frame) / (float)generated_frame_count;
        int frame_time = (int)floor(frame_time_float);
        if (frame_time >= next_time && current_keyframe < keyframe_count - 1) {
            current_time = keyframes[current_keyframe + 1].frame_number;
            next_time = keyframes[current_keyframe + 2].frame_number;
            ++current_keyframe;
        }

        float tween =
            (frame_time_float - (float)current_time) / (float)(next_time - current_time);

        for (int vertex_index = 0; vertex_index < vertex_count; ++vertex_index) {
            if (keyframe_count == 1) {
                animation->frames[frame]->vertices[vertex_index] =
                    keyframes[current_keyframe].object->vertices[vertex_index];
            } else {
                Vector3* a = &keyframes[current_keyframe].object->vertices[vertex_index];
                Vector3* b = &keyframes[current_keyframe + 1].object->vertices[vertex_index];
                Vector3* out = &animation->frames[frame]->vertices[vertex_index];
                out->x = (b->x - a->x) * tween + a->x;
                out->y = (b->y - a->y) * tween + a->y;
                out->z = (b->z - a->z) * tween + a->z;
            }
        }

        vertices = animation->frames[frame]->vertices;
        facequad_normals = animation->frames[frame]->facequad_normals;
        calc_object_facequad_normals();
    }

    animation->progress = 0.0f;
    return animation;
}
