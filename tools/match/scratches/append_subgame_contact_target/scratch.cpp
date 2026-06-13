// append_subgame_contact_target @ 0x415ef0 (thiscall, ret 0x10)
// Appends one `{kind, position, radius, object}` entry to the per-frame
// subgame contact registry unless the target object is hidden by flag 0x1000.

struct Vector3 {
    float x;
    float y;
    float z;
};

struct ContactObject {
    int unknown_00;
    unsigned int flags; // +0x04, 0x1000 suppresses contact target append
};

struct ContactTargetEntry {
    int kind;              // +0x00
    Vector3 position;      // +0x04
    float radius;          // +0x10
    ContactObject* object; // +0x14
};

class ContactTargetRegistry {
public:
    void append_subgame_contact_target(
        const Vector3* position,
        float radius,
        int kind,
        ContactObject* object
    );

    int count; // +0x00
    ContactTargetEntry entries[1]; // +0x04, variable capacity in native owner
};

void ContactTargetRegistry::append_subgame_contact_target(
    const Vector3* position,
    float radius,
    int kind,
    ContactObject* object
)
{
    if ((object->flags & 0x1000) != 0)
        return;

    entries[count].kind = kind;
    entries[count].position = *position;
    entries[count].radius = radius;
    entries[count].object = object;
    ++count;
}
