// Invincibility shell controller view, partial.
#ifndef INVINCIBLE_SHELL_H
#define INVINCIBLE_SHELL_H

class InvincibleShellController {
public:
    void initialize_invincible_shell(); // @ 0x444ac0
    void start_invincible_shell(); // @ 0x444ae0

    char unknown_00[0x80];
    int state; // +0x80
    float spin_phase; // +0x84
    float spin_phase_step; // +0x88
    float fade_progress; // +0x8c
    float fade_step; // +0x90
};

#endif
