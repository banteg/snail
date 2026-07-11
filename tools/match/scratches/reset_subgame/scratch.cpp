// reset_subgame @ 0x437b10 (thiscall, ret)

#include "subgame_runtime.h"
#include "timer_counters.h"

typedef unsigned int DWORD;

extern "C" void* memcpy(void* dest, const void* src, unsigned int count);
#pragma intrinsic(memcpy)

void SubgameRuntime::reset_subgame()
{
    DWORD* self = (DWORD*)this;

    int health_count = 8;
    DWORD* health = self + 874513;
    do {
        *(health - 3) = 0;
        *health = (DWORD)this;
        health += 29;
        --health_count;
    } while (health_count);

    self[874380] = 0;
    self[874383] = (DWORD)this;
    self[874407] = 0;
    self[874410] = (DWORD)this;

    DWORD* garbage = self + 877684;
    int garbage_count = 50;
    do {
        *(garbage - 2) = 0;
        *garbage = (DWORD)this;
        *(garbage - 3) = 0;
        garbage += 49;
        --garbage_count;
    } while (garbage_count);

    DWORD* slug = self + 874762;
    int slug_count = 8;
    do {
        *(slug - 2) = 0;
        *slug = (DWORD)this;
        slug += 59;
        --slug_count;
    } while (slug_count);

    DWORD* ring = self + 880215;
    int ring_count = 2;
    do {
        *(ring - 84) = 0;
        *ring = (DWORD)this;
        ring += 126;
        --ring_count;
    } while (ring_count);

    if (*((unsigned char*)this + 16721360) == 1
        && self[16] == self[4147919]) {
        DWORD saved_score = self[4147909];
        DWORD saved_tail_a = self[4147916];
        self[978578] = saved_score;
        DWORD saved_tail_b = self[4147917];
        self[978585] = saved_tail_a;
        memcpy(self + 978579, self + 4147910, 0x18);
        self[978586] = saved_tail_b;
    } else {
        if (self[4834290] == 2) {
            self[978578] = 0;
            ((Player*)(self + 978393))->clear_subgoldy_score_buckets();
        }
        ((TimerCounters*)(self + 978579))->zero_timer_counters();
        self[978585] = 0;
        self[978586] = 0;
    }

    self[978616] = 0;
    *((unsigned char*)this) = 1;
    *((unsigned char*)this + 1) = 1;
    *((unsigned char*)this + 16721360) = 0;
    self[877648] = 0;
}
