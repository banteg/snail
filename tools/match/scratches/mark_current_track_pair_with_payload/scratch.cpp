// mark_current_track_pair_with_payload @ 0x43d3d0 (thiscall, ret 0x4)

struct TrackPairSprite {
    int unknown_00;
    unsigned int flags;
    char unknown_08[0x50 - 0x08];
    int payload;
};

class Player {
public:
    TrackPairSprite* mark_current_track_pair_with_payload(int payload);

    char unknown_00[0x98];
    TrackPairSprite* first_track_pair_sprite;
    TrackPairSprite* second_track_pair_sprite;
};

TrackPairSprite* Player::mark_current_track_pair_with_payload(int payload)
{
    first_track_pair_sprite->flags |= 0x40;
    second_track_pair_sprite->flags |= 0x40;
    first_track_pair_sprite->payload = payload;
    TrackPairSprite* second = second_track_pair_sprite;
    second->payload = payload;
    return second;
}
