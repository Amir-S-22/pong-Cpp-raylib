#include "raylib.h"
#include <iostream>
#include "functions.h"
#include <cstdlib>

enum State_x {POSITIVEx, NEGATIVEx, WALLl, WALLr};
enum State_y {POSITIVEy, NEGATIVEy};

int main(){
	// ------------------------------------------ Initialize ----------------------------------------------


	//Window
	const int windowWidth  { 800 };
	const int windowHeight { 500 };
	const char* windowName = TextFormat("Pong_v1");
	const char* fps_string = nullptr;
	float dt = 0;
	Vector2 top_middle 		= {windowWidth/2 , 0};
	Vector2 bottom_middle = {windowWidth/2 , windowHeight};
	InitWindow(windowWidth, windowHeight, windowName);
	SetTargetFPS( 60 );

	//rectangles
	const float box_height = 150;
	const float box_width = 10;
	const float box_start_x = 20;
	const float box_start_y = 20;
	const float box_speed = 700;
	Rectangle box_l = {box_start_x, box_start_y, box_width, box_height};
	Rectangle box_r = {windowWidth - box_start_x, box_start_y, box_width, box_height};
	
	//ball
	float ball_speed_x = 400;
	float ball_speed_y = 400;
	const float ball_start_speed_x = 400;
	const float ball_start_speed_y = 400;
	State_x state_x = POSITIVEx;
	State_y state_y = POSITIVEy;
	Vector2 ball_pos = {static_cast<float>(windowWidth/2), static_cast<float>(windowHeight/2)};

	//ScoreBoard
	int score_l = 0;
	int score_r = 0;
	const char* scoreBoard_l = nullptr;
	const char* scoreBoard_r = nullptr;

	// ------------------------------------------ Main game loop ----------------------------------------------
	while(!WindowShouldClose()){
	fps_string = TextFormat("FPS: %i", GetFPS());
	dt = GetFrameTime();

	//box Movement
	move_box(box_l, box_r, box_speed, windowHeight, box_height, dt);

	//Change scoreBoard text
	scoreBoard_l = TextFormat("%i", score_l);
	scoreBoard_r = TextFormat("%i", score_r);

	
	//ball collision with box
	if(CheckCollisionCircleRec(ball_pos, 10.0, box_l))
	{
		state_x = POSITIVEx;
		ball_speed_x += 50;
		ball_speed_y += 50;
	}
	else if(CheckCollisionCircleRec(ball_pos, 10.0, box_r))
	{
		state_x = NEGATIVEx;
		ball_speed_x += 50;
		ball_speed_y += 50;
	}


	//ball collision with walls (state)
	if(ball_pos.x >= windowWidth) 			 state_x = WALLr;	
	else if (ball_pos.x <= 0) 					 state_x = WALLl;	
	else if (ball_pos.y >= windowHeight) state_y = NEGATIVEy;  
	else if (ball_pos.y <= 0) 					 state_y = POSITIVEy;	

	//ball collision with walls (logic)
	if(state_x == WALLl)
	{
		score_r++;
		ball_pos.x = static_cast<float>( windowWidth/2 );
		ball_pos.y = static_cast<float>( std::rand()%(static_cast<int>(windowHeight)+1) );
		state_x = POSITIVEx;
		state_y = POSITIVEy;
		ball_speed_x = ball_start_speed_x;
		ball_speed_y = ball_start_speed_y;
		continue;
	}
	else if(state_x == WALLr)
	{
		score_l++;
		ball_pos.x = static_cast<float>( windowWidth/2 );
		ball_pos.y = static_cast<float>( std::rand()%(static_cast<int>(windowHeight)+1) );
		state_x = NEGATIVEx;
		state_y = POSITIVEy;
		ball_speed_x = ball_start_speed_x;
		ball_speed_y = ball_start_speed_y;
		continue;
	}

	//change of ball speed
	if(state_x == NEGATIVEx)				ball_pos.x -= (ball_speed_x * dt);
	else if(state_x == POSITIVEx)		ball_pos.x += (ball_speed_x * dt);
	if(state_y == NEGATIVEy)				ball_pos.y -= (ball_speed_y * dt);
	else if(state_y == POSITIVEy)		ball_pos.y += (ball_speed_y * dt);


	// ----------------------------------------- Draw Frame ----------------------------------------------
	BeginDrawing();
		ClearBackground(BLACK);

		DrawRectangleRec(box_l, WHITE);
		DrawRectangleRec(box_r, WHITE);
		DrawCircleV(ball_pos, 10.0, WHITE);
		DrawText(scoreBoard_l, static_cast<int>((windowWidth/4)), static_cast<int>(windowHeight/10), 50, WHITE);
		DrawText(scoreBoard_r, static_cast<int>((windowWidth/4)*3), static_cast<int>(windowHeight/10), 50, WHITE);
		DrawText(fps_string, 10, 10, 10, WHITE);
		draw_dotted_line(top_middle, bottom_middle, 15);
	EndDrawing();
	}
	return 0;
}

