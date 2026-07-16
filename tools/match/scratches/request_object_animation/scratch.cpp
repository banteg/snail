// request_object_animation @ 0x430a70 (thiscall, ret 0x10)

#include <stddef.h>

#include "object_animation_types.h"
#include "object_render_types.h"

void* allocate_tracked_memory(int size, char* name); // @ 0x431b60
int report_errorf(char* format, ...); // @ 0x431cc0
extern "C" double __cdecl floor(double value);

void Object::request_object_animation(
    int keyframe_count, XAnimationKeyframe* keyframes,
    float progress_step, int flags)
{
    for (int i = 0; i < keyframe_count; ++i) {
        if (keyframes[i].object->vertex_count != vertex_count) {
            report_errorf(
                "Anim tween Vertices don't match Frame %i", keyframes[i].frame_number);
            return;
        }
    }

    this->flags |= OBJECT_FLAG_HAS_ANIMATION;

    int generated_frame_count = (int)(1.0f / progress_step);
    animation = (ObjectAnimation*)allocate_tracked_memory(
        sizeof(ObjectAnimation), "Object Animation");
    animation->generated_frame_count = generated_frame_count;
    animation->flags = flags;
    animation->progress = 0.0f;
    animation->progress_step = progress_step;
    animation->frames = (ObjectAnimationFrame**)allocate_tracked_memory(
        generated_frame_count * sizeof(*animation->frames),
        "Object Animation Frame array");

    int current_keyframe = 0;
    int current_time = keyframes[0].frame_number;
    int next_time;
    if (keyframe_count == 1)
        next_time = keyframes[0].frame_number;
    else
        next_time = keyframes[1].frame_number;

    int frame = 0;
    if (generated_frame_count > 0) {
        float generated_frame_count_float = (float)generated_frame_count;
        int* last_frame_number = &keyframes[keyframe_count - 1].frame_number;
        Object** keyframe_object_cursor = &keyframes->object;
        do {
            animation->frames[frame] =
                (ObjectAnimationFrame*)allocate_tracked_memory(
                    sizeof(ObjectAnimationFrame), "Object Animation Frame");
            animation->frames[frame]->vertices =
                (Vector3*)allocate_tracked_memory(vertex_count * sizeof(Vector3),
                    "Object Animation Frame Vertices");
            animation->frames[frame]->facequad_normals =
                (Vector3*)allocate_tracked_memory(
                    facequad_count * sizeof(Vector3) * 2,
                    "Object Animation Frame FaceQuad Normals");

            float frame_time_float =
                (float)(*last_frame_number * frame) / generated_frame_count_float;
            int frame_time = (int)floor(frame_time_float);
            if (frame_time >= next_time && current_keyframe < keyframe_count - 1) {
                ++current_keyframe;
                keyframe_object_cursor =
                    (Object**)((char*)keyframe_object_cursor + sizeof(XAnimationKeyframe));
                XAnimationKeyframe* current_keyframe_record =
                    (XAnimationKeyframe*)((char*)keyframe_object_cursor
                        - offsetof(XAnimationKeyframe, object));
                current_time = current_keyframe_record->frame_number;
                next_time = current_keyframe_record[1].frame_number;
            }

            float keyframe_span = (float)(next_time - current_time);
            float tween = (frame_time_float - (float)current_time) / keyframe_span;

            for (int vertex_index = 0; vertex_index < vertex_count; ++vertex_index) {
                if (keyframe_count == 1) {
                    animation->frames[frame]->vertices[vertex_index] =
                        (*keyframe_object_cursor)->vertices[vertex_index];
                } else {
                    Object* next_object =
                        *(Object**)((char*)keyframe_object_cursor + sizeof(XAnimationKeyframe));
                    Vector3* b = &next_object->vertices[vertex_index];
                    Vector3* a = &(*keyframe_object_cursor)->vertices[vertex_index];
                    Vector3* out = &animation->frames[frame]->vertices[vertex_index];
                    Vector3 tweened = (*b - *a) * tween + *a;
                    *out = tweened;
                }
            }

            vertices = animation->frames[frame]->vertices;
            facequad_normals = animation->frames[frame]->facequad_normals;
            calc_object_facequad_normals();
            ++frame;
        } while (frame < generated_frame_count);
    }

    animation->progress = 0.0f;
}
