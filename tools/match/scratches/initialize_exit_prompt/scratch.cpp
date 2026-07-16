// initialize_exit_prompt @ 0x4060d0 (thiscall)

#include "border_manager.h"
#include "exit.h"
#include "game_root.h"


void Exit::initialize_exit_prompt()
{
    tColour color_2;
    tColour color_3;
    tColour color_4;
    tColour color_5;
    tColour color_6;
    tColour color_7;
    tColour color_8;
    tColour color_9;
    tColour color_10;
    tColour color_11;
    tColour color_12;
    tColour color_13;
    tColour color_14;
    tColour color_15;
    tColour color_16;
    tColour color_17;
    tColour color_18;
    tColour color_19;
    tColour color_20;

    g_game->border_manager.hide_all_borders();

    switch (state - 2) {
    case 7:
        yes_button = g_game->border_manager.allocate_border();
        yes_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "Yes",
            0x14,
            0.0f,
            prompt_y - 54.0f,
            color_3.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            140.0f);

        no_button = g_game->border_manager.allocate_border();
        no_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "No",
            0x14,
            0.0f,
            prompt_y,
            color_19.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            268.0f);
        return;

    case 8:
        prompt_title = g_game->border_manager.allocate_border();
        prompt_title->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            "Do you really want to quit?",
            0x14,
            0.0f,
            200.0f,
            color_5.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);

        yes_button = g_game->border_manager.allocate_border();
        yes_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION |
                FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "Yes",
            0x14,
            0.0f,
            prompt_y,
            color_13.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            -80.0f);
        yes_button->stack_widget_below(prompt_title);

        no_button = g_game->border_manager.allocate_border();
        no_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "No",
            0x14,
            0.0f,
            prompt_y,
            color_7.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            80.0f);
        no_button->stack_widget_below(prompt_title);
        return;

    case 9:
        prompt_title = g_game->border_manager.allocate_border();
        prompt_title->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            "Do you really want to quit?",
            0x14,
            0.0f,
            200.0f,
            color_17.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);

        yes_button = g_game->border_manager.allocate_border();
        yes_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION |
                FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "Yes",
            0x14,
            0.0f,
            prompt_y,
            color_9.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            -80.0f);
        yes_button->stack_widget_below(prompt_title);

        no_button = g_game->border_manager.allocate_border();
        no_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "No",
            0x14,
            0.0f,
            prompt_y,
            color_15.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            80.0f);
        no_button->stack_widget_below(prompt_title);
        return;

    case 0:
    case 5:
        prompt_title = g_game->border_manager.allocate_border();
        prompt_title->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            "Do you really want to quit?",
            0x14,
            0.0f,
            200.0f,
            color_11.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);

        yes_button = g_game->border_manager.allocate_border();
        yes_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION |
                FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "Yes",
            0x14,
            0.0f,
            330.0f,
            color_2.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            -80.0f);
        yes_button->stack_widget_below(prompt_title);

        no_button = g_game->border_manager.allocate_border();
        no_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "No",
            0x14,
            0.0f,
            330.0f,
            color_4.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            80.0f);
        no_button->stack_widget_below(prompt_title);
        return;

    case 1:
        prompt_title = g_game->border_manager.allocate_border();
        prompt_title->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            "Do you really want to quit?",
            0x14,
            0.0f,
            200.0f,
            color_6.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);

        yes_button = g_game->border_manager.allocate_border();
        yes_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION |
                FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "Yes",
            0x14,
            0.0f,
            330.0f,
            color_8.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            -80.0f);
        yes_button->stack_widget_below(prompt_title);

        no_button = g_game->border_manager.allocate_border();
        no_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "No",
            0x14,
            0.0f,
            330.0f,
            color_10.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            80.0f);
        no_button->stack_widget_below(prompt_title);
        return;

    case 2:
        prompt_title = g_game->border_manager.allocate_border();
        prompt_title->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            "Do you really want to quit?",
            0x14,
            0.0f,
            200.0f,
            color_12.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);

        yes_button = g_game->border_manager.allocate_border();
        yes_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION |
                FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "Yes",
            0x14,
            468.0f,
            373.0f,
            color_14.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            -80.0f);
        yes_button->stack_widget_below(prompt_title);

        no_button = g_game->border_manager.allocate_border();
        no_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "No",
            0x14,
            568.0f,
            296.0f,
            color_16.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            80.0f);
        no_button->stack_widget_below(prompt_title);
        return;

    case 3:
        yes_button = g_game->border_manager.allocate_border();
        yes_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "Yes",
            0x14,
            473.0f,
            33.0f,
            color_18.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);

        no_button = g_game->border_manager.allocate_border();
        no_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED |
                FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            "No",
            0x14,
            566.0f,
            108.0f,
            color_20.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);
        return;
    }

    return;
}
