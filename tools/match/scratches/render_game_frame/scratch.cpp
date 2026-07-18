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

    int active_camera_count = 0;
    int camera_order[CAMERA_SLOT_COUNT];
    camera_order[0] = -1;
    camera_order[1] = -1;
    camera_order[2] = -1;
    camera_order[3] = -1;
    camera_order[CAMERA_LAST_INDEX] = -1;

    RenderCameraSlot* slots = render_camera_slots;
    {
        for (int active_index = 0;
             active_index < CAMERA_SLOT_COUNT;
             ++active_index) {
            if ((slots[active_index].flags & 1) != 0) {
                ++active_camera_count;
            }
        }
    }

    slots[1].flags =
        (slots[1].flags & ~RENDER_SCENE_MASK) | RENDER_SCENE_PLAYER_0;

    int ordered_count = 0;
    {
        for (int order_index = 0;
             order_index < CAMERA_SLOT_COUNT;
             ++order_index) {
            if ((slots[order_index].flags & 1) != 0) {
                if (ordered_count == 0) {
                    camera_order[0] = order_index;
                    ordered_count = 1;
                } else {
                    for (int insert = 0; insert < ordered_count; ++insert) {
                        if (slots[order_index].sort_key >
                            slots[camera_order[insert]].sort_key) {
                            if (insert < CAMERA_LAST_INDEX) {
                                int* shift = &camera_order[CAMERA_LAST_INDEX];
                                int shift_count = CAMERA_LAST_INDEX - insert;
                                do {
                                    *shift = shift[-1];
                                    --shift;
                                    --shift_count;
                                } while (shift_count != 0);
                            }
                            camera_order[insert] = order_index;
                            ++ordered_count;
                            break;
                        }
                    }
                }
            }
        }
    }

    int post_sprite_count = 0;
    int rendered_bod_count = 0;
    if (active_camera_count > 0) {
        int* camera_cursor = camera_order;
        int remaining_cameras = active_camera_count;
        do {
            int camera_index = *camera_cursor;

        if ((render_camera_slots[camera_index].flags & 1) != 0) {
            render_camera(
                render_camera_slots[camera_index].viewport_x,
                render_camera_slots[camera_index].viewport_y,
                render_camera_slots[camera_index].viewport_width,
                render_camera_slots[camera_index].viewport_height,
                render_camera_slots[camera_index].source->fov_degrees,
                &render_camera_slots[camera_index].source->transform,
                &render_camera_slots[camera_index].source->view_matrix,
                render_camera_slots[camera_index].draw_world,
                0);

            post_sprite_count = 0;
            if ((render_camera_slots[camera_index].flags & 2) == 0) {
                RenderableBod* bod =
                    (RenderableBod*)active_bod_list.first;
                RenderableBod** post_cursor = g_post_sprite_bods;
                while (bod != 0) {
                    if ((bod->list_flags & BOD_FLAG_DEBUG) != 0) {
                        debug_report_stub("DEBUG RENDER\n");
                    }

                    if ((bod->list_flags & BOD_FLAG_HAS_OBJECT) != 0 &&
                        (bod->list_flags & BOD_FLAG_RENDER_ENABLED) != 0 &&
                        (render_camera_slots[camera_index].flags &
                         bod->list_flags & RENDER_SCENE_MASK) != 0) {
                        if ((bod->list_flags & BOD_FLAG_AFTER_SPRITES) != 0) {
                            *post_cursor = bod;
                            ++post_cursor;
                            ++post_sprite_count;
                        }
                        ++rendered_bod_count;
                        if ((bod->list_flags & BOD_FLAG_SYNC_ANIMATION) != 0) {
                            Object* animated_object = bod->object;
                            AnimManager* animation_manager =
                                bod->render_animation_manager;
                            animated_object->animation->progress =
                                animation_manager->progress;
                        }
                        if ((bod->list_flags & BOD_FLAG_USE_TRANSFORM) != 0) {
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
                if ((render_camera_slots[camera_index].flags &
                     sprite_flags & RENDER_SCENE_MASK) != 0) {
                    if ((sprite_flags & SPRITE_FLAG_ACTIVE) != 0 &&
                        (sprite_flags & SPRITE_FLAG_RENDER_ENABLED) != 0 &&
                        (sprite_flags & SPRITE_FLAG_DELAYED_RENDER) == 0) {
                        Vector3 projected = sprite->position;
                        TransformMatrix camera_matrix =
                            render_camera_slots[camera_index].source->view_matrix;
                        projected *= camera_matrix;
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
                    if ((node->sprite->flags & SPRITE_FLAG_ORIENT_TO_MOTION) != 0) {
                        node->sprite->update_sprite_facing_angle(
                            &render_camera_slots[camera_index].source->view_matrix);
                    }
                    draw_sprite_quad(&node->position, node->sprite);
                    node = node->next;
                }
                g_sprite_depth_buckets[bucket] = node;
            }

            end_sprite_depth_render_state();
            begin_overlay_render_state();
            draw_font_text_queue(render_camera_slots[camera_index].flags);
            end_overlay_render_state();

            if ((render_camera_slots[camera_index].flags & 2) == 0 &&
                post_sprite_count != 0) {
                render_camera(
                    render_camera_slots[camera_index].viewport_x,
                    render_camera_slots[camera_index].viewport_y,
                    render_camera_slots[camera_index].viewport_width,
                    render_camera_slots[camera_index].viewport_height,
                    render_camera_slots[camera_index].source->fov_degrees,
                    &render_camera_slots[camera_index].source->transform,
                    &render_camera_slots[camera_index].source->view_matrix,
                    render_camera_slots[camera_index].draw_world,
                    1);

                int replay_count = post_sprite_count;
                post_sprite_count = 0;
                rendered_bod_count += replay_count;
                RenderableBod** post_cursor =
                    g_post_sprite_bods + replay_count;
                do {
                    --post_cursor;
                    RenderableBod* bod = *post_cursor;
                    unsigned int bod_flags = bod->list_flags;
                    if ((bod_flags & BOD_FLAG_USE_TRANSFORM) != 0) {
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
                    --replay_count;
                } while (replay_count != 0);
            }
        }

            ++camera_cursor;
            --remaining_cameras;
        } while (remaining_cameras != 0);
    }

    noop_runtime_ai();
}
