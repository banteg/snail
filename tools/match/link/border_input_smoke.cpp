// Diagnostic editor comparison. Input, OK-widget update, layout and teardown
// are explicit harness seams. Original machine code receives no source credit.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frontend_widget.h"
#include "input_ok_state.h"
#include "game_root.h"

struct Fixture {
    unsigned int id, key, mode, cursor, capacity;
    unsigned int blink, step, visible, flags, controls;
    char text[64];
};
struct GuardedBorder {
    unsigned int before[4];
    unsigned int storage[sizeof(cRBorder) / 4];
    unsigned int after[4];
};
static GuardedBorder subject_storage, ok_storage;
static cRBorder* subject = (cRBorder*)subject_storage.storage;
static cRBorder* ok = (cRBorder*)ok_storage.storage;
static unsigned int events[4][5], event_count, current_key, ai_action;
static unsigned int total_events;
cRGame* g_game;

static void require(int condition, const char* message)
{
    if (!condition) { printf("HARNESS FAILURE: %s\n", message); fflush(0); exit(2); }
}
static void event(unsigned int kind, unsigned int detail)
{
    require(event_count < 4, "event capacity");
    events[event_count][0] = kind;
    events[event_count][1] = subject->input_cursor;
    events[event_count][2] = subject->input_length;
    events[event_count][3] = subject->widget_flags;
    events[event_count][4] = detail;
    ++event_count;
    ++total_events;
}
char read_repeating_text_input_key_code()
{
    event(1, current_key);
    return (char)current_key;
}
void cRInputOK::AI()
{
    require(this == subject->input_ok_state(), "OK state receiver");
    require(source_widget == subject && ok_widget == ok, "OK state pointers");
    event(2, ai_action);
    if (ai_action == 1)
        ok->widget_flags |= FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
    if (ai_action == 2)
        subject->input_flags ^= 1;
    if (ai_action == 3)
        subject->widget_flags |= FRONTEND_WIDGET_FLAG_TEXT_INPUT_SUBMIT_REQUESTED;
}
void cRBorder::RePosition()
{
    require(this == subject, "layout receiver");
    event(3, input_flags);
}
int cRBorderManager::kill_border(cRBorder* border)
{
    require(this == &g_game->border_manager && border == ok, "teardown receiver/argument");
    event(4, 2);
    return 0;
}
static void write_exact(FILE* f, const void* data, unsigned int size)
{
    require(fwrite(data, 1, size, f) == size, "output write");
}
static void check_guards(const GuardedBorder& border)
{
    for (int i = 0; i < 4; ++i) {
        require(border.before[i] == 0x5a5a5a5a, "leading guard");
        require(border.after[i] == 0x5a5a5a5a, "trailing guard");
    }
}
int main(int argc, char** argv)
{
    require(argc == 3, "usage: border_input_smoke fixtures output");
    FILE* input = fopen(argv[1], "rb");
    FILE* output = fopen(argv[2], "wb");
    require(input != 0 && output != 0, "open fixture/output");
    unsigned int input_header[3];
    require(fread(input_header, 1, sizeof(input_header), input) == sizeof(input_header), "fixture header");
    require(input_header[0] == 0x31464942 && input_header[2] == sizeof(Fixture), "fixture format");
    require(input_header[1] != 0 && input_header[1] <= 100000, "fixture count");
    unsigned int output_header[4] = {0x314f4942, input_header[1],
        8 + sizeof(events) + 2 * sizeof(cRBorder), sizeof(cRBorder)};
    write_exact(output, output_header, sizeof(output_header));
    g_game = (cRGame*)malloc(sizeof(cRGame));
    require(g_game != 0, "game allocation");
    memset(g_game, 0x39, sizeof(cRGame));
    for (unsigned int case_index = 0; case_index < input_header[1]; ++case_index) {
        Fixture fixture;
        require(fread(&fixture, 1, sizeof(fixture), input) == sizeof(fixture), "fixture read");
        require(fixture.id == case_index && fixture.text[63] == 0, "fixture identity/text boundary");
        unsigned int length = strlen(fixture.text);
        require(length <= 48 && fixture.cursor <= length && fixture.capacity <= 64, "fixture bounds");
        require(fixture.key <= 255 && fixture.controls < 16, "fixture controls");
        memset(&subject_storage, 0x5a, sizeof(subject_storage));
        memset(&ok_storage, 0x5a, sizeof(ok_storage));
        memset(subject, fixture.id & 1 ? 0xa5 : 0, sizeof(cRBorder));
        memset(ok, fixture.id & 1 ? 0x3c : 0, sizeof(cRBorder));
        subject->input_ok_state()->source_widget = subject;
        subject->input_ok_state()->ok_widget = ok;
        memset(subject->text_buffer, 0, sizeof(subject->text_buffer));
        memcpy(subject->text_buffer, fixture.text, fixture.cursor);
        subject->text_buffer[fixture.cursor] = '|';
        memcpy(subject->text_buffer + fixture.cursor + 1, fixture.text + fixture.cursor,
               length - fixture.cursor + 1);
        subject->input_cursor = fixture.cursor;
        subject->input_length = length;
        subject->input_capacity = fixture.capacity;
        subject->input_flags = fixture.mode;
        subject->widget_flags = fixture.flags;
        subject->input_cursor_visible = fixture.visible;
        memcpy(&subject->input_cursor_blink_progress, &fixture.blink, 4);
        memcpy(&subject->input_cursor_blink_step, &fixture.step, 4);
        ok->widget_flags = fixture.controls & 4 ? FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED : 0;
        current_key = fixture.key;
        ai_action = fixture.controls & 3;
        event_count = 0;
        memset(events, 0, sizeof(events));
        subject->InputText();
        check_guards(subject_storage);
        check_guards(ok_storage);
        require(subject->input_ok_state()->source_widget == subject &&
                subject->input_ok_state()->ok_widget == ok, "preserved pointer identities");
        unsigned int record_header[2] = {fixture.id, event_count};
        write_exact(output, record_header, sizeof(record_header));
        write_exact(output, events, sizeof(events));
        unsigned char normalized[sizeof(cRBorder)];
        memcpy(normalized, subject, sizeof(normalized));
        // Compare identities above, then canonicalize only the two initialized pointers.
        unsigned int tokens[2] = {0xf00d0001, 0xf00d0002};
        memcpy(normalized + 0x2c4, tokens, sizeof(tokens));
        write_exact(output, normalized, sizeof(normalized));
        write_exact(output, ok, sizeof(cRBorder));
    }
    require(fgetc(input) == EOF, "fixture trailing bytes");
    unsigned char* game_bytes = (unsigned char*)g_game;
    for (unsigned int i = 0; i < sizeof(cRGame); ++i)
        require(game_bytes[i] == 0x39, "game storage changed");
    require(fclose(input) == 0 && fclose(output) == 0, "close files");
    free(g_game);
    printf("border-input cases=%u events=%u\n", input_header[1], total_events);
    fflush(0);
    return 0;
}
