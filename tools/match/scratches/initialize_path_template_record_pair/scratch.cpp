// initialize_path_template_record_pair @ 0x4085c0 (thiscall, ret)

extern void* g_path_template_record_pair_vtable; // off_497334 / data_497334

class BodBase {
public:
    void initialize_bod_base();

    void* vtable; // +0x00
};

class PathTemplateRecordPair : public BodBase {
public:
    PathTemplateRecordPair* initialize_path_template_record_pair();

    char unknown_04[0x60 - 0x04];
    BodBase second_record; // +0x60
};

PathTemplateRecordPair* PathTemplateRecordPair::initialize_path_template_record_pair()
{
    initialize_bod_base();
    second_record.initialize_bod_base();
    vtable = &g_path_template_record_pair_vtable;
    return this;
}
