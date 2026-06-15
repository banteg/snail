// initialize_sound_bank @ 0x44dcb0 (stdcall, ret 0x4)

int register_sound_sample(char* path, int normalization_class);

struct SoundBankEntry {
    char* path;               // +0x00
    int handle;               // +0x04
    int normalization_class;  // +0x08
};

char* __stdcall initialize_sound_bank(SoundBankEntry* entries)
{
    SoundBankEntry* cursor = entries;
    char* result = cursor->path;

    if (*result != 0) {
        SoundBankEntry* store = entries;
        do {
            store->handle = register_sound_sample(result, store->normalization_class);
            cursor += 1;
            store = cursor;
            result = cursor->path;
        } while (*result != 0);
    }

    return result;
}
