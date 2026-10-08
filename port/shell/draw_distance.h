#ifndef SNAIL_PORT_DRAW_DISTANCE_H
#define SNAIL_PORT_DRAW_DISTANCE_H

// An optional longer view down the track, off by default. It changes only
// what a rendered frame shows: before render_frame draws, it links the track
// the game has already built but not yet activated (render-cache rows,
// row models, uncached cells, landscape repeats) into the render list, and
// it undoes every write once the frame is drawn, so the simulation never
// sees it. The emulated device moves the far plane and fog out to match.

// The view distance as a multiple of the original's (52 units to the far
// plane); 1 or less keeps the original view.
extern float g_port_draw_distance;

void draw_distance_begin_frame();
void draw_distance_end_frame();

// World units the current frame sees past the original's view (0 when off
// or outside a level), and the view as a multiple of the original's (1 when
// off or outside a level). The emulated device moves the far plane out by the
// first and scales the fog band by the second, so the track fades out over a
// proportionally longer stretch, as the original's did over its own.
float draw_distance_extra();
float draw_distance_scale();

// The projection the device uses for `projection`: a perspective matrix with
// its far plane moved out by draw_distance_extra(); others unchanged.
void draw_distance_projection(const float* projection, float* out);

#endif
