// flush_row_event_display @ 0x404830 (thiscall, ret)

extern char* g_game_base; // data_4df904

struct FrontendWidget;

struct BorderManager {
    void kill_border(FrontendWidget* border);
};

class Player {
public:
    void add_subgoldy_score(int score_kind, int bonus_score);
};

class RowEventDisplayController {
public:
    void flush_row_event_display();

    FrontendWidget* widget_a;   // +0x00
    FrontendWidget* widget_b;   // +0x04
    FrontendWidget* widget_c;   // +0x08
    FrontendWidget* widget_d;   // +0x0c
    FrontendWidget* widget_e;   // +0x10
    int state;                  // +0x14
    char unknown_18[0x4];
    int parcel_target_count;    // +0x1c
    int bonus_enabled;          // +0x20
    char unknown_24[0x4];
    int delivered_parcel_count; // +0x28
    char unknown_2c[0x1c];
    int bonus_score;            // +0x48
    int display_token;          // +0x4c
};

void RowEventDisplayController::flush_row_event_display()
{
    if (state != 0) {
        if (delivered_parcel_count != parcel_target_count) {
            while (delivered_parcel_count < parcel_target_count) {
                ((Player*)(g_game_base + 0x42fd7c))->add_subgoldy_score(4, 0);
                delivered_parcel_count += 1;
            }

            if (bonus_enabled != 0) {
                ((Player*)(g_game_base + 0x42fd7c))->add_subgoldy_score(bonus_score, 0);
                delivered_parcel_count += 1;
            }
        }

        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(widget_a);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(widget_b);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(widget_d);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(widget_c);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(widget_e);

        if (*(int*)(g_game_base + 0x430060) != display_token)
            *(int*)(g_game_base + 0x430060) = display_token;

        state = 0;
    }
}
