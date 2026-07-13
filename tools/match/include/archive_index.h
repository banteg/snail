#ifndef ARCHIVE_INDEX_H
#define ARCHIVE_INDEX_H

typedef struct ArchiveEntry {
    char* path;      // +0x00
    int data_offset; // +0x04
    int byte_count;  // +0x08
} ArchiveEntry;

typedef struct ArchiveIndex {
    int count;               // +0x00
    ArchiveEntry entries[1]; // +0x04
} ArchiveIndex;

// Public RShellReadDirectory output record retained by iOS symbols.
typedef char DirectoryEntryName[128];

typedef enum ArchiveEntryExtensionClass {
    ARCHIVE_ENTRY_EXTENSION_UNKNOWN = 0,
    ARCHIVE_ENTRY_EXTENSION_TGA = 1,
    ARCHIVE_ENTRY_EXTENSION_WAV = 2,
    ARCHIVE_ENTRY_EXTENSION_MP3 = 3,
} ArchiveEntryExtensionClass;

typedef char ArchiveEntry_must_be_0x0c[(sizeof(ArchiveEntry) == 0x0c) ? 1 : -1];
typedef char DirectoryEntryName_must_be_0x80[
    (sizeof(DirectoryEntryName) == 0x80) ? 1 : -1];

typedef struct File File;

extern File* g_archive_file; // data_53c7f0 / iOS gDatFP
extern ArchiveIndex* g_archive_index_records; // data_53c7f8 / iOS gDat

#endif
