// Native tables at 0x4974fc and 0x497334 each contain 0x407b50, the
// recovered no-op callback. Keep these compatibility-table spellings until
// the shared C++ projection owns generated virtual tables.
void noop_runtime_ai();
void* g_bod_base_vtable = (void*)&noop_runtime_ai;
void* g_path_template_record_vtable = (void*)&noop_runtime_ai;
int g_bod_base_init_count;

// Integration-only sizeof witnesses; these are not reconstructed native data.
extern "C" const unsigned int path_nodes_storage_sizes[] = {
    sizeof(g_bod_base_vtable), sizeof(g_path_template_record_vtable)
};
