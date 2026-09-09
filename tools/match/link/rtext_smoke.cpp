// Exercise the recovered RShell declarations, including the void token API.
#include <stdio.h>
#include <string.h>
#include "rtext.h"

static int checks;
static int failures;

static void check(bool condition, const char* label)
{
    ++checks;
    if (!condition) {
        ++failures;
        printf("FAIL: %s\n", label);
    }
}

int main(int argc, char** argv)
{
    char source[] = "  alpha beta\r\n-42 17\r\nvalue=-12.5 end";
    char* cursor = source;
    char output[32];
    memset(output, '#', sizeof(output));
    RTextExtractString(&cursor, output);
    check(strcmp(output, "alpha") == 0, "token skips leading spaces");
    check(cursor == source + 7, "token leaves space delimiter unconsumed");
    check(output[6] == '#', "token writes only text and terminator");
    RTextExtractString(&cursor, output);
    check(strcmp(output, "beta") == 0, "next token starts at preceding delimiter");
    check(cursor == source + 12, "token stops before carriage return");
    RTextExtractString(&cursor, output);
    check(output[0] == 0 && cursor == source + 12, "carriage return gives empty token");
    RTextNewLine(&cursor);
    check(cursor == source + 14, "newline advances past CRLF");
    check(RTextExtractInt(&cursor) == -42 && *cursor == ' ', "negative integer and cursor");
    check(RTextExtractInt(&cursor) == 17 && *cursor == '\r', "positive integer and cursor");
    RTextNewLine(&cursor);
    float fraction = RTextExtractFloat(&cursor);
    check(fraction > -12.50001f && fraction < -12.49999f && *cursor == ' ',
          "float scans prefix and parses fraction with native x87 precision");

    char tab_token[] = "a\tb \r";
    cursor = tab_token;
    RTextExtractString(&cursor, output);
    check(strcmp(output, "a\tb") == 0 && cursor == tab_token + 3,
          "tab is token content, not a delimiter");
    char empty_token[] = "   \r";
    cursor = empty_token;
    RTextExtractString(&cursor, output);
    check(output[0] == 0 && cursor == empty_token + 3, "spaces before empty CR token");

    char copied[32];
    RTextCopy(copied, "Mail");
    check(strcmp(copied, "Mail") == 0, "copy includes terminator");
    RTextAppend(copied, " Box");
    check(strcmp(copied, "Mail Box") == 0, "append preserves existing text");
    check(RTextCompStart(copied, "mAiL"), "case insensitive prefix");
    check(!RTextCompStart("Ma", "Mail"), "short source cannot satisfy prefix");
    check(!RTextCompStart(copied, "Fail"), "different prefix is rejected");
    check(RTextCompStart(copied, ""), "empty prefix succeeds");

    char no_digits[] = "-x";
    cursor = no_digits;
    check(RTextExtractInt(&cursor) == 0 && cursor == no_digits + 1,
          "integer consumes minus even without digits");
    char plus_float[] = "+2.5 ";
    cursor = plus_float;
    check(RTextExtractFloat(&cursor) == 0.0f && cursor == plus_float,
          "shipped float parser stops at unconsumed plus");
    char end_line[] = "end";
    cursor = end_line;
    RTextNewLine(&cursor);
    check(cursor == end_line + sizeof(end_line), "newline advances once past terminating NUL");

    cursor = source;
    RTextExtractString(&cursor, output);
    if (argc == 2 && argv[1][0] == '!')
        output[0] = '!';
    check(strcmp(output, "alpha") == 0, "final token corruption control");

    printf("rtext checks=%d failures=%d\n", checks, failures);
    fflush(0);
    return failures ? 1 : 0;
}
