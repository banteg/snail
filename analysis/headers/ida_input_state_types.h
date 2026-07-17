#ifndef IDA_INPUT_STATE_TYPES_H
#define IDA_INPUT_STATE_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct DirectInputGuid {
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t data4[8];
} DirectInputGuid;

typedef struct DIDEVICEINSTANCEA {
    uint32_t dwSize;
    DirectInputGuid guidInstance;
    DirectInputGuid guidProduct;
    uint32_t dwDevType;
    char tszInstanceName[260];
    char tszProductName[260];
    DirectInputGuid guidFFDriver;
    uint16_t wUsagePage;
    uint16_t wUsage;
} DIDEVICEINSTANCEA;

typedef struct DIDEVICEOBJECTINSTANCEA {
    uint32_t dwSize;
    DirectInputGuid guidType;
    uint32_t dwOfs;
    uint32_t dwType;
    uint32_t dwFlags;
    char tszName[260];
    uint32_t dwFFMaxForce;
    uint32_t dwFFForceResolution;
    uint16_t wCollectionNumber;
    uint16_t wDesignatorIndex;
    uint16_t wUsagePage;
    uint16_t wUsage;
    uint32_t dwDimension;
    uint16_t wExponent;
    uint16_t wReportId;
} DIDEVICEOBJECTINSTANCEA;

typedef struct DIPROPHEADER {
    uint32_t dwSize;
    uint32_t dwHeaderSize;
    uint32_t dwObj;
    uint32_t dwHow;
} DIPROPHEADER;

typedef struct DIPROPRANGE {
    DIPROPHEADER diph;
    int32_t lMin;
    int32_t lMax;
} DIPROPRANGE;

typedef struct DIJOYSTATE2 {
    int32_t lX;
    int32_t lY;
    int32_t lZ;
    int32_t lRx;
    int32_t lRy;
    int32_t lRz;
    int32_t rglSlider[2];
    uint32_t rgdwPOV[4];
    uint8_t rgbButtons[128];
    int32_t lVX;
    int32_t lVY;
    int32_t lVZ;
    int32_t lVRx;
    int32_t lVRy;
    int32_t lVRz;
    int32_t rglVSlider[2];
    int32_t lAX;
    int32_t lAY;
    int32_t lAZ;
    int32_t lARx;
    int32_t lARy;
    int32_t lARz;
    int32_t rglASlider[2];
    int32_t lFX;
    int32_t lFY;
    int32_t lFZ;
    int32_t lFRx;
    int32_t lFRy;
    int32_t lFRz;
    int32_t rglFSlider[2];
} DIJOYSTATE2;

typedef struct IDirectInputDevice8A IDirectInputDevice8A;
typedef struct IDirectInputDevice8AVtbl {
    void* QueryInterface;
    void* AddRef;
    int32_t (__stdcall* Release)(IDirectInputDevice8A* self);
    void* GetCapabilities;
    int32_t (__stdcall* EnumObjects)(IDirectInputDevice8A* self, void* callback, void* user, uint32_t flags);
    void* GetProperty;
    int32_t (__stdcall* SetProperty)(IDirectInputDevice8A* self, void* property_id, const DIPROPHEADER* property);
    int32_t (__stdcall* Acquire)(IDirectInputDevice8A* self);
    int32_t (__stdcall* Unacquire)(IDirectInputDevice8A* self);
    int32_t (__stdcall* GetDeviceState)(IDirectInputDevice8A* self, uint32_t bytes, void* state_out);
    void* GetDeviceData;
    int32_t (__stdcall* SetDataFormat)(IDirectInputDevice8A* self, void* data_format);
    void* SetEventNotification;
    int32_t (__stdcall* SetCooperativeLevel)(IDirectInputDevice8A* self, int32_t window, uint32_t flags);
    void* GetObjectInfo;
    void* GetDeviceInfo;
    void* RunControlPanel;
    void* Initialize;
    void* CreateEffect;
    void* EnumEffects;
    void* GetEffectInfo;
    void* GetForceFeedbackState;
    void* SendForceFeedbackCommand;
    void* EnumCreatedEffectObjects;
    void* Escape;
    int32_t (__stdcall* Poll)(IDirectInputDevice8A* self);
} IDirectInputDevice8AVtbl;

struct IDirectInputDevice8A {
    IDirectInputDevice8AVtbl* lpVtbl;
};

typedef struct IDirectInput8A IDirectInput8A;
typedef struct IDirectInput8AVtbl {
    void* QueryInterface;
    void* AddRef;
    int32_t (__stdcall* Release)(IDirectInput8A* self);
    int32_t (__stdcall* CreateDevice)(IDirectInput8A* self, const DirectInputGuid* guid, IDirectInputDevice8A** device_out, void* outer_unknown);
    int32_t (__stdcall* EnumDevices)(IDirectInput8A* self, uint32_t device_class, void* callback, void* user, uint32_t flags);
    void* GetDeviceStatus;
    void* RunControlPanel;
    void* Initialize;
    void* FindDevice;
} IDirectInput8AVtbl;

struct IDirectInput8A {
    IDirectInput8AVtbl* lpVtbl;
};

typedef enum InputButtonFlag {
    INPUT_BUTTON_PRIMARY = 0x4000,
    INPUT_BUTTON_SECONDARY = 0x8000,
} InputButtonFlag;

typedef struct InputControllerSlot {
    float axis_x;
    float axis_y;
    InputButtonFlag buttons;
    float pointer_x;
    float pointer_y;
    float authored_x;
    float authored_y;
    float pointer_value;
} InputControllerSlot;

typedef struct InputState {
    int32_t controller_slot;
    InputButtonFlag pressed_buttons;
    InputButtonFlag released_buttons;
    InputButtonFlag previous_buttons;
    InputButtonFlag inverse_current_buttons;
    float axis_x;
    float axis_y;
    int32_t unknown_1c;
    float pointer_x;
    float pointer_y;
    float authored_x;
    float authored_y;
    float pointer_value;
    InputButtonFlag current_buttons;
} InputState;

typedef struct GameInputBodBase {
    void* vtable;
    uint32_t list_flags;
    struct GameInputBodBase* list_prev;
    struct GameInputBodBase* list_next;
    float position[3];
    float render_arg_1c;
    float render_arg_20;
    void* object;
    float color[4];
} GameInputBodBase;

typedef struct GameInput {
    GameInputBodBase bod;
    InputState input;
} GameInput;

typedef struct MouseScreenRect {
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
} MouseScreenRect;

typedef struct Point {
    int32_t x;
    int32_t y;
} Point;

char __cdecl read_pressed_text_input_key_code(void);
char __cdecl read_repeating_text_input_key_code(void);

extern float g_text_input_repeat_step;
extern float g_text_input_repeat_accumulator;
extern uint8_t g_text_input_last_repeat_code;

extern int32_t g_input_region_top[2];
extern int32_t g_input_region_bottom[2];
extern int32_t g_input_region_left[2];
extern int32_t g_input_region_right[2];

void __cdecl update_input_controller_pointer_region(
    int32_t slot,
    int32_t left,
    int32_t top,
    int32_t right,
    int32_t bottom,
    int32_t x,
    int32_t y,
    int32_t pointer_value,
    char button_a,
    char button_b,
    char button_c,
    char capture_when_outside,
    char force_clamp);
void* __cdecl set_input_controller_pointer_authored_xy(
    int32_t slot,
    float authored_x,
    float authored_y);

#endif
