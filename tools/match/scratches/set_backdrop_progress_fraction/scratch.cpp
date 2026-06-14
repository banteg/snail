// set_backdrop_progress_fraction @ 0x410c30 (thiscall, ret 0x4)

class Backdrop {
public:
    void set_backdrop_progress_fraction(float fraction);

    char unknown_000[0x6c8];
    float progress_fraction; // +0x6c8
};

void Backdrop::set_backdrop_progress_fraction(float fraction)
{
    progress_fraction = fraction;
}
