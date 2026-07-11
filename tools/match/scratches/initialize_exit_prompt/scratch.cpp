// initialize_exit_prompt @ 0x4060d0 (thiscall)

#include "border_manager.h"
#include "exit.h"

extern char* g_game_base; // data_4df904

int Exit::initialize_exit_prompt()
{
    Color4f color_2;
    Color4f color_3;
    Color4f color_4;
    Color4f color_5;
    Color4f color_6;
    Color4f color_7;
    Color4f color_8;
    Color4f color_9;
    Color4f color_10;
    Color4f color_11;
    Color4f color_12;
    Color4f color_13;
    Color4f color_14;
    Color4f color_15;
    Color4f color_16;
    Color4f color_17;
    Color4f color_18;
    Color4f color_19;
    Color4f color_20;

    ((BorderManager*)(g_game_base + 0xb4c))->hide_all_borders();

    switch (state - 2) {
    case 7:
        yes_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        yes_button->initialize_frontend_widget(
            0x14,
            "Yes",
            0x14,
            0.0f,
            prompt_y - 54.0f,
            color_3.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            140.0f);

        no_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        return (int)no_button->initialize_frontend_widget(
            0x14,
            "No",
            0x14,
            0.0f,
            prompt_y,
            color_19.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            268.0f);

    case 8:
        prompt_title = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        prompt_title->initialize_frontend_widget(
            0x400002,
            "Do you really want to quit?",
            0x14,
            0.0f,
            200.0f,
            color_5.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);

        yes_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        yes_button->initialize_frontend_widget(
            0x40000014,
            "Yes",
            0x14,
            0.0f,
            prompt_y,
            color_13.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            -80.0f);
        yes_button->stack_widget_below(prompt_title);

        no_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        no_button->initialize_frontend_widget(
            0x14,
            "No",
            0x14,
            0.0f,
            prompt_y,
            color_7.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            80.0f);
        return (int)no_button->stack_widget_below(prompt_title);

    case 9:
        prompt_title = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        prompt_title->initialize_frontend_widget(
            0x400002,
            "Do you really want to quit?",
            0x14,
            0.0f,
            200.0f,
            color_17.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);

        yes_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        yes_button->initialize_frontend_widget(
            0x40000014,
            "Yes",
            0x14,
            0.0f,
            prompt_y,
            color_9.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            -80.0f);
        yes_button->stack_widget_below(prompt_title);

        no_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        no_button->initialize_frontend_widget(
            0x14,
            "No",
            0x14,
            0.0f,
            prompt_y,
            color_15.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            80.0f);
        return (int)no_button->stack_widget_below(prompt_title);

    case 0:
    case 5:
        prompt_title = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        prompt_title->initialize_frontend_widget(
            0x400002,
            "Do you really want to quit?",
            0x14,
            0.0f,
            200.0f,
            color_11.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);

        yes_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        yes_button->initialize_frontend_widget(
            0x40000014,
            "Yes",
            0x14,
            0.0f,
            330.0f,
            color_2.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            -80.0f);
        yes_button->stack_widget_below(prompt_title);

        no_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        no_button->initialize_frontend_widget(
            0x14,
            "No",
            0x14,
            0.0f,
            330.0f,
            color_4.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            80.0f);
        return (int)no_button->stack_widget_below(prompt_title);

    case 1:
        prompt_title = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        prompt_title->initialize_frontend_widget(
            0x400002,
            "Do you really want to quit?",
            0x14,
            0.0f,
            200.0f,
            color_6.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);

        yes_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        yes_button->initialize_frontend_widget(
            0x40000014,
            "Yes",
            0x14,
            0.0f,
            330.0f,
            color_8.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            -80.0f);
        yes_button->stack_widget_below(prompt_title);

        no_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        no_button->initialize_frontend_widget(
            0x14,
            "No",
            0x14,
            0.0f,
            330.0f,
            color_10.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            80.0f);
        return (int)no_button->stack_widget_below(prompt_title);

    case 2:
        prompt_title = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        prompt_title->initialize_frontend_widget(
            0x400002,
            "Do you really want to quit?",
            0x14,
            0.0f,
            200.0f,
            color_12.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);

        yes_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        yes_button->initialize_frontend_widget(
            0x40000014,
            "Yes",
            0x14,
            468.0f,
            373.0f,
            color_14.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            -80.0f);
        yes_button->stack_widget_below(prompt_title);

        no_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        no_button->initialize_frontend_widget(
            0x14,
            "No",
            0x14,
            568.0f,
            296.0f,
            color_16.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            80.0f);
        return (int)no_button->stack_widget_below(prompt_title);

    case 3:
        yes_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        yes_button->initialize_frontend_widget(
            0x14,
            "Yes",
            0x14,
            473.0f,
            33.0f,
            color_18.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);

        no_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        return (int)no_button->initialize_frontend_widget(
            0x14,
            "No",
            0x14,
            566.0f,
            108.0f,
            color_20.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);
    }

    return state - 2;
}
