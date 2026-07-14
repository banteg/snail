// render_game_frame @ 0x40a490 (thiscall)

#include "bod_types.h"
#include "font_system.h"
#include "game_root.h"
#include "object_animation_types.h"
#include "object_render_types.h"
#include "render_camera_slot.h"
#include "sprite.h"
#include "transform_matrix.h"

void reset_render_counters();                // @ 0x414650
void begin_sprite_depth_render_state();      // @ 0x413540
void end_sprite_depth_render_state();        // @ 0x413650
void begin_overlay_render_state();           // @ 0x411e10
void end_overlay_render_state();             // @ 0x411de0
void noop_runtime_ai();                      // @ 0x407b50
int report_errorf(const char* format, ...);
int debug_report_stub(const char* format, ...); // @ 0x449c00, stripped in release
int draw_sprite_quad(Vector3* position, Sprite* sprite); // @ 0x4137f0
void draw_font_text_queue(unsigned int render_mask);     // @ 0x44a730

extern RenderableBod* g_post_sprite_bods[]; // data_4dfb10

void GameRoot::render_game_frame()
{
    enum {
        CAMERA_SLOT_COUNT =
            sizeof(render_camera_slots) / sizeof(render_camera_slots[0]),
        CAMERA_LAST_INDEX = CAMERA_SLOT_COUNT - 1,
    };

    int skip_count = render_skip_count;
    if (skip_count > 0) {
        --skip_count;
        render_skip_count = skip_count;
        return;
    }

    reset_render_counters();

    int rendered_sprite_count = 0;
    TransformMatrix transform;
    set_matrix_identity(&transform);

    int camera_order[CAMERA_SLOT_COUNT];
    camera_order[0] = -1;
    camera_order[1] = -1;
    camera_order[2] = -1;
    camera_order[3] = -1;
    camera_order[CAMERA_LAST_INDEX] = -1;

    int active_camera_count = 0;
    RenderCameraSlot* slots = render_camera_slots;
    int i;
    for (i = 0; i < CAMERA_SLOT_COUNT; ++i) {
        if ((slots[i].flags & 1) != 0) {
            ++active_camera_count;
        }
    }

    slots[1].flags = (slots[1].flags & 0x00ffffff) | 0x02000000;

    int ordered_count = 0;
    for (i = 0; i < CAMERA_SLOT_COUNT; ++i) {
        if ((slots[i].flags & 1) != 0) {
            if (ordered_count == 0) {
                camera_order[0] = i;
                ordered_count = 1;
            } else {
                for (int insert = 0; insert < ordered_count; ++insert) {
                    if (slots[i].sort_key > slots[camera_order[insert]].sort_key) {
                        if (insert < CAMERA_LAST_INDEX) {
                            int* shift = &camera_order[CAMERA_LAST_INDEX];
                            int shift_count = CAMERA_LAST_INDEX - insert;
                            do {
                                *shift = shift[-1];
                                --shift;
                                --shift_count;
                            } while (shift_count != 0);
                        }
                        camera_order[insert] = i;
                        ++ordered_count;
                        break;
                    }
                }
            }
        }
    }

    int post_sprite_count = 0;
    if (active_camera_count > 0) {
        int* camera_cursor = camera_order;
        int remaining_cameras = active_camera_count;
        do {
            int camera_index = *camera_cursor;
            RenderCameraSlot* slot = &slots[camera_index];

        if ((slot->flags & 1) != 0) {
            RenderCamera* source = slot->source;
            render_camera(
                slot->viewport_x,
                slot->viewport_y,
                slot->viewport_width,
                slot->viewport_height,
                source->fov_degrees,
                &source->transform,
                &source->view_matrix,
                slot->draw_world,
                0);

            post_sprite_count = 0;
            if ((slot->flags & 2) == 0) {
                RenderableBod* bod =
                    (RenderableBod*)active_bod_list.first;
                RenderableBod** post_cursor = g_post_sprite_bods;
                while (bod != 0) {
                    if ((bod->list_flags & 0x10) != 0) {
                        debug_report_stub("DEBUG RENDER\n");
                    }

                    if ((bod->list_flags & 2) != 0 &&
                        (bod->list_flags & 0x20) != 0 &&
                        (slot->flags & bod->list_flags & 0xff000000) != 0) {
                        if ((bod->list_flags & 0x80) != 0) {
                            *post_cursor = bod;
                            ++post_cursor;
                            ++post_sprite_count;
                        }
                        if ((bod->list_flags & 0x800) != 0) {
                            Object* animated_object = bod->object;
                            AnimManager* animation_manager =
                                bod->render_animation_manager;
                            animated_object->animation->progress =
                                animation_manager->progress;
                        }
                        if ((bod->list_flags & 0x400) != 0) {
                            render_object(
                                bod->object,
                                &bod->transform,
                                bod->render_arg_1c,
                                bod->render_arg_20,
                                &bod->color,
                                (char)bod->is_bod_after_sprites());
                        } else {
                            transform.position = bod->position;
                            render_object(
                                bod->object,
                                &transform,
                                bod->render_arg_1c,
                                bod->render_arg_20,
                                &bod->color,
                                (char)bod->is_bod_after_sprites());
                        }
                    }

                    bod = (RenderableBod*)bod->list_next;
                }
            }

            Sprite* sprite = g_sprite_active_heads[camera_index];
            SpriteDepthNode* next_depth_node = g_sprite_depth_nodes;
            begin_sprite_depth_render_state();

            while (sprite != 0) {
                ++rendered_sprite_count;
                unsigned int sprite_flags = sprite->flags;
                if ((slot->flags & sprite_flags & 0xff000000) != 0) {
                    if ((sprite_flags & 1) != 0 &&
                        (sprite_flags & 0x40) != 0 &&
                        (sprite_flags & 0x200) == 0) {
                        Vector3 projected = sprite->position;
                        TransformMatrix camera_matrix = source->view_matrix;
                        projected.multiply_vector_by_matrix(camera_matrix);
                        projected.x = -projected.x;
                        projected.z = -projected.z;

                        float depth_key = -projected.z;
                        depth_key *= 4.19672108f;
                        depth_key += sprite->depth_bias;
                        int bucket_index = (int)depth_key;
                        if (bucket_index >= 0x100) {
                            bucket_index = 0xff;
                        }
                        if (bucket_index >= 0) {
                            SpriteDepthNode* head = g_sprite_depth_buckets[bucket_index];
                            SpriteDepthNode* previous = 0;
                            SpriteDepthNode* cursor = head;
                            if (cursor != 0) {
                                while (cursor != 0 && depth_key < cursor->depth_key) {
                                    previous = cursor;
                                    cursor = cursor->next;
                                }
                                if (cursor == 0) {
                                    previous->next = next_depth_node;
                                    next_depth_node->next = 0;
                                } else if (previous == 0) {
                                    next_depth_node->next = cursor;
                                    g_sprite_depth_buckets[bucket_index] = next_depth_node;
                                } else {
                                    previous->next = next_depth_node;
                                    next_depth_node->next = cursor;
                                }
                            } else {
                                g_sprite_depth_buckets[bucket_index] = next_depth_node;
                                next_depth_node->next = 0;
                            }

                            next_depth_node->position = projected;
                            next_depth_node->depth_key = depth_key;
                            next_depth_node->sprite = sprite;
                            sprite->render_bucket_index = bucket_index;
                            sprite->render_depth_key = depth_key;
                            ++next_depth_node;
                        }
                    }
                } else {
                    report_errorf("Loose Sprite scene viewport");
                }

                sprite = sprite->next;
            }

            for (int bucket = 0xff; bucket >= 0; --bucket) {
                SpriteDepthNode* node = g_sprite_depth_buckets[bucket];
                while (node != 0) {
                    if ((node->sprite->flags & 2) != 0) {
                        node->sprite->update_sprite_facing_angle(&source->view_matrix);
                    }
                    draw_sprite_quad(&node->position, node->sprite);
                    node = node->next;
                }
                g_sprite_depth_buckets[bucket] = node;
            }

            end_sprite_depth_render_state();
            begin_overlay_render_state();
            draw_font_text_queue(slot->flags);
            end_overlay_render_state();

            if ((slot->flags & 2) == 0 && post_sprite_count != 0) {
                render_camera(
                    slot->viewport_x,
                    slot->viewport_y,
                    slot->viewport_width,
                    slot->viewport_height,
                    source->fov_degrees,
                    &source->transform,
                    &source->view_matrix,
                    slot->draw_world,
                    1);

                RenderableBod** post_cursor =
                    g_post_sprite_bods + post_sprite_count;
                do {
                    --post_cursor;
                    RenderableBod* bod = *post_cursor;
                    unsigned int bod_flags = bod->list_flags;
                    if ((bod_flags & 0x400) != 0) {
                        render_object(
                            bod->object,
                            &bod->transform,
                            bod->render_arg_1c,
                            bod->render_arg_20,
                            &bod->color,
                            (char)bod->is_bod_after_sprites());
                    } else {
                        transform.position.x = bod->position.x;
                        transform.position.y = bod->position.y;
                        transform.position.z = bod->position.z;
                        render_object(
                            bod->object,
                            &transform,
                            bod->render_arg_1c,
                            bod->render_arg_20,
                            &bod->color,
                            (char)bod->is_bod_after_sprites());
                    }
                    --post_sprite_count;
                } while (post_sprite_count != 0);
            }
        }

            ++camera_cursor;
            --remaining_cameras;
        } while (remaining_cameras != 0);
    }

    noop_runtime_ai();
}
