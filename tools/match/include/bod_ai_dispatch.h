// Cast-only ABI view for the slot-zero AI callback shared by cRBod-derived
// runtime objects. Concrete owners keep their explicit vtable word, so this
// surface must not be inherited by their recovered layouts.
#ifndef BOD_AI_DISPATCH_H
#define BOD_AI_DISPATCH_H

class BodAiDispatch {
public:
    virtual void update_bod_ai() = 0;
};

typedef char BodAiDispatch_must_be_0x04[
    (sizeof(BodAiDispatch) == 0x04) ? 1 : -1];

#endif
