#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1800.0f
#define TURN_DEGREES 25.0f * DEGTORAD
#define BRAKE_POWER 75.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	mat4x4 matrix;
private:
	uint currentTime = 0;
	uint TimeFlag = 0;
	float brakedelay = 0;
};