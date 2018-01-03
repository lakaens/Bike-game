#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

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

	Cube *cube1, *cube2, *cube3, *cube4, *cube5, *cube6, *cube7, *cube8, *tunel1r, *tunel1l, *tunel1u, *cube9, *cube10, *cube11, *cube12, *cube13, *cube14, *cube15, *cube16, *cube17, *cube18, *cube19, *cube20, *cube21, *cube22, *cube23, *cube24, *cube25;
	PhysBody3D *cube_1, *cube_2, *cube_3, *cube_4, *cube_5, *cube_6, *cube_7, *cube_8, *tunel_1r, *tunel_1l, *tunel_1u, *cube_9, *cube_10, *cube_11, *cube_12, *cube_13, *cube_14, *cube_15, *cube_16, *cube_17, *cube_18, *cube_19, *cube_20, *cube_21, *cube_22, *cube_23, *cube_24, *cube_25;

};
