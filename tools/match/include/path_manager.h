// Stateless authored cRPathManager path-name owner. Android and iOS preserve
// the class and NameCode(char*) symbol; Windows independently gives this empty
// owner one byte immediately before the embedded path-template bank.
#ifndef PATH_MANAGER_H
#define PATH_MANAGER_H

class cRPathManager {
public:
    int find_segment_path_index_by_name(char* name); // @ 0x429ae0, cRPathManager::NameCode
};

typedef cRPathManager PathManager;

typedef char cRPathManager_must_be_1[(sizeof(cRPathManager) == 1) ? 1 : -1];

#endif
