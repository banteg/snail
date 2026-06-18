// noop_runtime_slot_constructor @ 0x408600 (thiscall, returns this)

class RuntimeSlot {
public:
    RuntimeSlot* noop_runtime_slot_constructor();
};

RuntimeSlot* RuntimeSlot::noop_runtime_slot_constructor()
{
    return this;
}
