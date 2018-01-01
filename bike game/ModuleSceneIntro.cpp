#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include"PhysVehicle3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	cube1.size = vec3(4,0.05,20);
	cube1.color = White;
	cube1.SetPos(0, 0, 10);
	cube_1=App->physics->AddBody(cube1, 2000);
	cube2.size = vec3(5,0.05, 4);
	cube2.color = White;
	cube2.SetPos(-4.5, 0, 18);
	cube_2=App->physics->AddBody(cube2, 2000);
	cube3.size=vec3(5,2,4);
	cube3.color = White;
	cube3.SetPos(-9,0,18);
	cube3.SetRotation(23.f, vec3(0,0,-1));
	
	cube_3=App->physics->AddBody(cube3, 2000);
	

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	cube1.Render();
	cube_1->GetTransform(&cube1.transform);
	cube2.Render();
	cube_2->GetTransform(&cube2.transform);
	cube3.Render();
	cube_3->GetTransform(&cube3.transform);
	p.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

