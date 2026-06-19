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

typedef char ArchiveEntry_must_be_0x0c[(sizeof(ArchiveEntry) == 0x0c) ? 1 : -1];

#endif
