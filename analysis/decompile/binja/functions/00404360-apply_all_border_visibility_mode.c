/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: apply_all_border_visibility_mode @ 0x404360 */

0040436f        switch (mode)
00404376        case 0
00404376        int32_t i = 0
004043cc        while (i s< 0x42f18)
00404378        struct BorderManager* owner = stack->owner
00404385        int32_t eax = *(&owner->borders[0].flags + i)
00404395        if (eax != 0 && (eax & 0x10001400) == 0)
00404397        eax:1.b |= 0x10
0040439a        *(&owner->borders[0].flags + i) = eax
004043ac        stack->entries[stack->entry_count].widget = &stack->owner->borders + i
004043b5        stack->entries[stack->entry_count].generation = stack->generation
004043bd        stack->entry_count += 1
004043c0        i += 0x724
004043d3        stack->generation += 1
004043d8        case 1
004043d8        int32_t generation = stack->generation
004043dc        if (generation s> 0)
004043e3        stack->generation = generation - 1
004043e5        int32_t entry_count = stack->entry_count
004043ea        if (entry_count s> 0)
004043f0        int32_t eax_9 = entry_count - 1
004043f3        stack->entry_count = eax_9
004043f6        if (eax_9 s>= 0)
00404409        while (stack->entries[eax_9].generation == stack->generation)
0040440f        void* widget = stack->entries[eax_9].widget
0040441b        *(widget + 0x1a0) &= 0xffffefff
00404424        void* widget_1 = stack->entries[stack->entry_count].widget
0040442e        *(widget_1 + 0x21c) = *(widget_1 + 0x214)
00404437        void* widget_2 = stack->entries[stack->entry_count].widget
00404441        *(widget_2 + 0x220) = *(widget_2 + 0x214)
0040444e        stack->entries[stack->entry_count].widget->hover_blend_target = 0
0040445f        stack->entries[stack->entry_count].widget->hover_blend_current = 0
00404469        int32_t entry_count_1 = stack->entry_count
0040446c        eax_9 = entry_count_1 - 1
0040446d        stack->entry_count = eax_9
00404470        if (entry_count_1 - 1 s< 0)
00404474        stack->entry_count = eax_9 + 1
00404478        return
0040451f        stack->entry_count += 1
004044dd        case 2
004044dd        int32_t generation_1 = stack->generation
004044e1        if (generation_1 s> 0)
004044e4        stack->generation = generation_1 - 1
004044e6        int32_t entry_count_2 = stack->entry_count
004044eb        if (entry_count_2 s> 0)
004044ed        int32_t eax_26 = entry_count_2 - 1
004044f0        stack->entry_count = eax_26
004044f3        if (eax_26 s>= 0)
00404502        while (stack->entries[eax_26].generation == stack->generation)
00404504        void* widget_3 = stack->entries[eax_26].widget
00404510        *(widget_3 + 0x1a0) &= 0xffff7fff
00404516        int32_t entry_count_3 = stack->entry_count
00404519        eax_26 = entry_count_3 - 1
0040451a        stack->entry_count = eax_26
0040451d        if (entry_count_3 - 1 s< 0)
0040451d        break
0040451f        stack->entry_count += 1
0040447b        case 3
0040447b        int32_t i_1 = 0
004044d1        while (i_1 s< 0x42f18)
0040447d        struct BorderManager* owner_1 = stack->owner
0040448a        int32_t eax_17 = *(&owner_1->borders[0].flags + i_1)
0040449a        if (eax_17 != 0 && (eax_17 & 0x10009400) == 0)
0040449c        eax_17:1.b |= 0x80
0040449f        *(&owner_1->borders[0].flags + i_1) = eax_17
004044b1        stack->entries[stack->entry_count].widget = &stack->owner->borders + i_1
004044ba        stack->entries[stack->entry_count].generation = stack->generation
004044c2        stack->entry_count += 1
004044c5        i_1 += 0x724
004044d8        stack->generation += 1
00404524        return
