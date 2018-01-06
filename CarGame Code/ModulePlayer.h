#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1800.0f
#define TURN_DEGREES 30.0f * DEGTORAD
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
	bool count;
	bool timer = false;
	float aux1 = 0, aux2 = 0, aux3 = 0;
	float cont = 0;
};