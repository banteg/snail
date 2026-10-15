// Shared cRBod flag-word ownership.
#ifndef BOD_FLAGS_H
#define BOD_FLAGS_H

#include "render_scene.h"

enum BodFlag {
    // Set by cRBod::SetObject and required by the render traversal.
    BOD_FLAG_HAS_OBJECT = 0x00000002,
    // Enables the diagnostic probes in both cRGame::AI and cRGame::Render.
    BOD_FLAG_DEBUG = 0x00000010,
    // Visibility gate consumed by the render traversal and object lifecycles.
    BOD_FLAG_RENDER_ENABLED = 0x00000020,
    // Protects the saved next node from removal during the active-list walk.
    BOD_FLAG_NEXT_UPDATE_GUARD = 0x00000040,
    // Stages a second render after the sprite depth pass.
    BOD_FLAG_AFTER_SPRITES = 0x00000080,
    // Marks membership in one intrusive cLinkedList<cRBod>.
    BOD_FLAG_LINKED = 0x00000200,
    // Selects RenderableBod::transform instead of BodBase::position.
    BOD_FLAG_USE_TRANSFORM = 0x00000400,
    // Copies a borrowed AnimManager progress value into Object::animation.
    BOD_FLAG_SYNC_ANIMATION = 0x00000800,
    // Prevents the BOD from entering the per-frame contact-target registry.
    BOD_FLAG_SUPPRESS_CONTACT = 0x00001000,
};

#endif
