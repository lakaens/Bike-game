#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "SDL2_ttf-2.0.14\include\SDL_ttf.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,
		TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {

		int text_width;
		int text_height;
		SDL_Surface *surface;
		SDL_Color textColor = { 255, 255, 255, 0 };

		surface = TTF_RenderText_Solid(font, text, textColor);
		*texture = SDL_CreateTextureFromSurface(renderer, surface);
		text_width = surface->w;
		text_height = surface->h;
		//LOG("w:%i,h:%i", text_width, text_height);
		SDL_FreeSurface(surface);
		rect->x = x;
		rect->y = y;
		rect->w = text_width;
		rect->h = text_height;
	}

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	Cube *cube1, *cube2, *cube3, *cube4, *cube5, *cube6, *cube7, *cube8, *tunel1r, *tunel1l, *tunel1u, *cube9, *cube10, *cube11, *cube12, *cube13, *cube14, *cube15, *cube16, *cube17, *cube18, *cube19, *cube20, *cube21, *cube22, *cube23, *cube24, *cube25, *cube26, *cube27, *cube28, *cube29, *cube30, *cube31, *cube32, *cube33, *cube34, *cube35;
	PhysBody3D *cube_1, *cube_2, *cube_3, *cube_4, *cube_5, *cube_6, *cube_7, *cube_8, *tunel_1r, *tunel_1l, *tunel_1u, *cube_9, *cube_10, *cube_11, *cube_12, *cube_13, *cube_14, *cube_15, *cube_16, *cube_17, *cube_18, *cube_19, *cube_20, *cube_21, *cube_22, *cube_23, *cube_24, *cube_25, *cube_26, *cube_27, *cube_28, *cube_29, *cube_30, *cube_31, *cube_32, *cube_33, *cube_34, *cube_35;


	//******

	SDL_Rect rect1;
	SDL_Rect rect2;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture1 = NULL;
	SDL_Texture* texture2 = NULL;
	SDL_Window* window = NULL;
	TTF_Font* font = NULL;
	char* text1 = "Hello World";
	float cont = 0;
	char const *cont_char = "Helloo";
	char* cont_charr = "default";
	bool timer = false;
	float aux1 = 0, aux2 = 0, aux3 = 0;
	//******Sensor
	Cube meta, fmeta;
	PhysBody3D* meta_, *fmeta_;
	//******Constraint
	Cube constraintcube;
	PhysBody3D* constraintpb;
	Cylinder motor1;
	PhysBody3D* motor_1;
};
