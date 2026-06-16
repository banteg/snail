// render_game_frame @ 0x40a490 (thiscall)

#include "bod_types.h"
#include "font_system.h"
#include "render_camera_slot.h"
#include "sprite.h"
#include "transform_matrix.h"

class GameRoot {
public:
    int render_game_frame();
};

struct RenderCameraSourceView {
    char unknown_00[0x38];
    TransformMatrix camera_matrix; // +0x38
    char unknown_78[0x80 - 0x78];
    TransformMatrix view_matrix;   // +0x80
    int camera_mode;               // +0xc0
};

class RenderBodView {
public:
    int is_bod_after_sprites(); // @ 0x42f5c0

    void* vtable;            // +0x00
    unsigned int flags;      // +0x04
    RenderBodView* prev;     // +0x08
    RenderBodView* next;     // +0x0c
    Vector3 position;        // +0x10
    int render_arg_1c;       // +0x1c
    float render_arg_20;     // +0x20
    void* object;            // +0x24
    Color4f color;           // +0x28
    TransformMatrix matrix;  // +0x38
    char unknown_78[0xbc - 0x78];
};

struct RenderBodTextureSinkView {
    char unknown_00[0x0c];
    int texture_slot; // +0x0c
};

struct RenderBodParentTextureView {
    char unknown_00[0xbc];
    RenderBodTextureSinkView* texture_sink; // +0xbc
};

struct RenderBodTextureOwnerView {
    char unknown_00[0x04];
    int texture_slot; // +0x04
};

struct SpriteDepthNode {
    SpriteDepthNode* next; // +0x00
    Vector3 position;      // +0x04
    float depth_key;       // +0x10
    Sprite* sprite;        // +0x14
};

void reset_render_counters();                // @ 0x414650
void begin_sprite_depth_render_state();      // @ 0x413540
void end_sprite_depth_render_state();        // @ 0x413650
void begin_overlay_render_state();           // @ 0x411e10
void end_overlay_render_state();             // @ 0x411de0
void noop_runtime_ai();                 // @ 0x407b50
int report_errorf(const char* format, ...);
int debug_report_stub(const char* format, ...); // @ 0x449c00, stripped in release
int render_camera(
    float viewport_x,
    float viewport_y,
    float viewport_width,
    float viewport_height,
    int camera_mode,
    TransformMatrix* camera_matrix,
    TransformMatrix* view_matrix,
    char draw_world,
    char post_sprite_pass); // @ 0x411fa0
int render_object(
    void* object,
    TransformMatrix* matrix,
    int render_arg_1c,
    float render_arg_20,
    Color4f* color,
    char after_sprites); // @ 0x4126c0
int draw_sprite_quad(Vector3* position, Sprite* sprite); // @ 0x4137f0
void draw_font_text_queue(unsigned int render_mask);     // @ 0x44a730

extern SpriteDepthNode* g_sprite_depth_buckets[]; // data_4f7050
extern SpriteDepthNode g_sprite_depth_nodes[];    // data_4e5510
extern RenderBodView* g_post_sprite_bods[];       // data_4dfb10

int GameRoot::render_game_frame()
{
    char* base = (char*)this;
    int skip_count = *(int*)(base + 0x56c);
    if (skip_count > 0) {
        --skip_count;
        *(int*)(base + 0x56c) = skip_count;
        return skip_count;
    }

    reset_render_counters();

    int rendered_sprite_count = 0;
    TransformMatrix transform;
    set_matrix_identity(&transform);

    int camera_order[5];
    camera_order[0] = -1;
    camera_order[1] = -1;
    camera_order[2] = -1;
    camera_order[3] = -1;
    camera_order[4] = -1;

    int active_camera_count = 0;
    RenderCameraSlot* slots = (RenderCameraSlot*)(base + 0x5b4);
    int i;
    for (i = 0; i < 5; ++i) {
        if ((slots[i].flags & 1) != 0) {
            ++active_camera_count;
        }
    }

    *(unsigned int*)(base + 0x5e4) =
        (*(unsigned int*)(base + 0x5e4) & 0x00ffffff) | 0x02000000;

    int ordered_count = 0;
    for (i = 0; i < 5; ++i) {
        if ((slots[i].flags & 1) == 0) {
            continue;
        }

        int insert = 0;
        while (insert < ordered_count &&
            slots[i].sort_key > slots[camera_order[insert]].sort_key) {
            ++insert;
        }

        int j;
        for (j = ordered_count; j > insert; --j) {
            camera_order[j] = camera_order[j - 1];
        }
        camera_order[insert] = i;
        ++ordered_count;
    }

    if (active_camera_count <= 0) {
        noop_runtime_ai();
        return 0;
    }

    int* camera_cursor = camera_order;
    int remaining_cameras = active_camera_count;
    do {
        int camera_index = *camera_cursor;
        RenderCameraSlot* slot = &slots[camera_index];

        if ((slot->flags & 1) != 0) {
            RenderCameraSourceView* source = (RenderCameraSourceView*)slot->source;
            render_camera(
                slot->viewport_x,
                slot->viewport_y,
                slot->viewport_width,
                slot->viewport_height,
                source->camera_mode,
                &source->camera_matrix,
                &source->view_matrix,
                slot->draw_world,
                0);

            int post_sprite_count = 0;
            if ((slot->flags & 2) == 0) {
                RenderBodView* bod = *(RenderBodView**)(base + 0x5ac);
                RenderBodView** post_cursor = g_post_sprite_bods;
                while (bod != 0) {
                    unsigned int bod_flags = bod->flags;
                    if ((bod_flags & 0x10) != 0) {
                        debug_report_stub("DEBUG RENDER\n");
                    }

                    if ((bod_flags & 2) != 0 &&
                        (bod_flags & 0x20) != 0 &&
                        (slot->flags & bod_flags & 0xff000000) != 0) {
                        if ((bod_flags & 0x80) != 0) {
                            *post_cursor = bod;
                            ++post_cursor;
                            ++post_sprite_count;
                        } else {
                            if ((bod_flags & 0x800) != 0) {
                                RenderBodParentTextureView* texture_parent =
                                    *(RenderBodParentTextureView**)((char*)bod + 0x24);
                                RenderBodTextureOwnerView* texture_owner =
                                    *(RenderBodTextureOwnerView**)((char*)bod + 0x78);
                                texture_parent->texture_sink->texture_slot =
                                    texture_owner->texture_slot;
                            }
                            if ((bod_flags & 0x400) == 0) {
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
                            } else {
                                render_object(
                                    bod->object,
                                    &bod->matrix,
                                    bod->render_arg_1c,
                                    bod->render_arg_20,
                                    &bod->color,
                                    (char)bod->is_bod_after_sprites());
                            }
                        }
                    }

                    bod = bod->next;
                }
            }

            Sprite* sprite = g_sprite_active_heads[camera_index];
            SpriteDepthNode* next_depth_node = g_sprite_depth_nodes;
            begin_sprite_depth_render_state();

            while (sprite != 0) {
                ++rendered_sprite_count;
                unsigned int sprite_flags = sprite->flags;
                if ((slot->flags & sprite_flags & 0xff000000) == 0) {
                    report_errorf("Loose Sprite scene viewport");
                } else if ((sprite_flags & 1) != 0 &&
                    (sprite_flags & 0x40) != 0 &&
                    (sprite_flags & 0x200) == 0) {
                    Vector3 projected = sprite->position;
                    TransformMatrix camera_matrix = source->view_matrix;
                    projected.multiply_vector_by_matrix(camera_matrix);
                    projected.x = -projected.x;
                    projected.z = -projected.z;

                    float depth_key = projected.z * 4.19672108f + sprite->depth_bias;
                    int bucket_index = (int)depth_key;
                    if (bucket_index >= 0x100) {
                        bucket_index = 0xff;
                    }
                    if (bucket_index >= 0) {
                        SpriteDepthNode* head = g_sprite_depth_buckets[bucket_index];
                        SpriteDepthNode* previous = 0;
                        SpriteDepthNode* cursor = head;
                        if (cursor == 0) {
                            g_sprite_depth_buckets[bucket_index] = next_depth_node;
                        } else {
                            while (cursor != 0 && depth_key < cursor->depth_key) {
                                previous = cursor;
                                cursor = cursor->next;
                            }
                            if (cursor == 0) {
                                previous->next = next_depth_node;
                            } else if (previous == 0) {
                                next_depth_node->next = cursor;
                                g_sprite_depth_buckets[bucket_index] = next_depth_node;
                            } else {
                                previous->next = next_depth_node;
                                next_depth_node->next = cursor;
                            }
                        }

                        next_depth_node->next = 0;
                        next_depth_node->position = projected;
                        next_depth_node->depth_key = depth_key;
                        next_depth_node->sprite = sprite;
                        sprite->render_bucket_index = bucket_index;
                        sprite->render_depth_key = depth_key;
                        ++next_depth_node;
                    }
                }

                sprite = sprite->next;
            }

            for (int bucket = 0xff; bucket >= 0; --bucket) {
                SpriteDepthNode* node = g_sprite_depth_buckets[bucket];
                while (node != 0) {
                    Sprite* node_sprite = node->sprite;
                    if ((node_sprite->flags & 2) != 0) {
                        node_sprite->update_sprite_facing_angle(&source->view_matrix);
                    }
                    draw_sprite_quad(&node->position, node_sprite);
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
                    source->camera_mode,
                    &source->camera_matrix,
                    &source->view_matrix,
                    slot->draw_world,
                    1);

                RenderBodView** post_cursor = g_post_sprite_bods + post_sprite_count;
                do {
                    --post_cursor;
                    RenderBodView* bod = *post_cursor;
                    unsigned int bod_flags = bod->flags;
                    if ((bod_flags & 0x400) == 0) {
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
                    } else {
                        render_object(
                            bod->object,
                            &bod->matrix,
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

    return 0;
}
