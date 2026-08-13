#ifndef DAMAGE_GUAGE_TYPES_H
#define DAMAGE_GUAGE_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the shipped Windows
 * cRDamageGuage controller at Player +0x3c4. The Guage spelling is authored.
 * Android preserves the no-argument Init/AI/Take family and the same field
 * range; iOS retains AI/Take and a version-specific Init(cRSubGoldy*) ABI.
 */

typedef unsigned char uint8_t;
typedef int int32_t;

typedef enum DamageGuageState {
    DAMAGE_GUAGE_STATE_MONITORING = 0,
    DAMAGE_GUAGE_STATE_WARNING_TRANSITION = 1,
    DAMAGE_GUAGE_STATE_DRAINING = 2,
} DamageGuageState;

typedef struct cRDamageGuage {
    DamageGuageState state;
    float pulse_progress;
    float pulse_step;
    /* Cleared by Init on Windows and Android; no live consumer is proved. */
    uint8_t unresolved_byte_0c;
    uint8_t _pad_0d[0x3];
    float warning_transition_progress;
    float warning_transition_step;
    int32_t skin_hold_ticks;
    float fill;
    float display_fill;
    float hit_flash_progress;
    float hit_flash_step;
} cRDamageGuage;

typedef char cRDamageGuage_must_be_0x2c[
    (sizeof(cRDamageGuage) == 0x2c) ? 1 : -1];

#endif
