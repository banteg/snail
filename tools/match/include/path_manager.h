// Stateless authored path-name owner. Windows gives the empty cRPathManager
// one byte of storage immediately before the embedded path-template bank.
#ifndef PATH_MANAGER_H
#define PATH_MANAGER_H

class PathManager {
public:
    int find_segment_path_index_by_name(char* name); // @ 0x429ae0, cRPathManager::NameCode
};

typedef char PathManager_must_be_1[(sizeof(PathManager) == 1) ? 1 : -1];

#endif
