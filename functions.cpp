#include "raylib.h"
#include <iostream>

void move_box(Rectangle &box_l, Rectangle &box_r, float box_speed, int windowHeight, float box_height, float dt){
	if(IsKeyDown(KEY_W) && box_l.y >= static_cast<float>(5)) box_l.y -= box_speed * dt;
	else if(IsKeyDown(KEY_S )&& box_l.y <= static_cast<float>(windowHeight - box_height - 5)) box_l.y += box_speed * dt;

	if(IsKeyDown(KEY_UP) && box_r.y >= static_cast<float>(5)) box_r.y -= box_speed * dt;
	else if(IsKeyDown(KEY_DOWN )&& box_r.y <= static_cast<float>(windowHeight - box_height - 5)) box_r.y += box_speed * dt;
}

void draw_dotted_line(Vector2 top_middle, Vector2 bottom_middle, int gap){
	int height = static_cast<int>(bottom_middle.y-top_middle.y);
	int number_of_lines = static_cast<int>(height/gap);
	Vector2 tail = {top_middle.x, 0};
	Vector2 head = {top_middle.x, static_cast<float>(gap)};

	for(int i = 0; i < number_of_lines; i++){
		if(i%2 == 0)
		{
			tail.y = head.y;
			head.y += gap;
		}
		DrawLineBezier(tail, head, 10,WHITE); 
		tail.y = head.y;
		head.y += gap;
	}
}
