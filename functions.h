#ifndef FUNCTIONS
#define FUNCTIONS

#include "raylib.h"

void move_box(Rectangle &box_l, Rectangle &box_r, float box_speed, int windowHeight, float box_height, float dt);
void draw_dotted_line(Vector2 top_middle, Vector2 bottom_middle, int gap);

#endif
