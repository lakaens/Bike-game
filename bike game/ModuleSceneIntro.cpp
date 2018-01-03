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
	//cube1.size = vec3(4,0.05,20);
	//cube1.color = White;
	//cube1.SetPos(0, 0, 10);
	//cube_1=App->physics->AddBody(cube1, 2000);
	//cube2.size = vec3(5,0.05, 4);
	//cube2.color = White;
	//cube2.SetPos(-4.5, 0, 18);
	//cube_2=App->physics->AddBody(cube2, 2000);
	//cube3.size=vec3(5,2,4);
	//cube3.color = White;
	//cube3.SetPos(-9,0,18);
	//cube3.SetRotation(23.f, vec3(0,0,-1));
	//
	//cube_3=App->physics->AddBody(cube3, 2000);
	//

	cubetest = App->physics->AddCube(vec3(4, 0.05, 20), vec3(0, 0, 10), 0, vec3(1, 0, 0), Green);
	cube_test = App->physics->AddCubePB(cubetest, false, this);



	cube1.size = vec3(5, 0.05, 20);
	cube1.color = White;
	cube1.SetPos(0, 0, 10);
	cube_1 = App->physics->AddBody(cube1, 0);
	cube_1->collision_listeners.add(this);

	cube2.size = vec3(5,0.05, 4);
	cube2.color = White;
	cube2.SetPos(-4.5, 0, 18);
	cube_2=App->physics->AddBody(cube2, 0);
	cube_2->collision_listeners.add(this);

	cube3.size=vec3(5,2,4);
	cube3.color = White;
	cube3.SetPos(-9,0,18);
	cube3.SetRotation(-25, { 0,0,1 });
	cube_3 = App->physics->AddBody(cube3, 0);
	cube_3->collision_listeners.add(this);

	cube4.size = vec3(5, 2, 4);
	cube4.color = White;
	cube4.SetPos(-15, 0, 18);
	cube4.SetRotation(25, { 0,0,1 });
	cube_4 = App->physics->AddBody(cube4, 0);
	cube_4->collision_listeners.add(this);

	cube5.size = vec3(5, 0.05, 4);
	cube5.color = White;
	cube5.SetPos(-19.5, 0, 18);
	cube_5 = App->physics->AddBody(cube5, 0);
	cube_5->collision_listeners.add(this);

	cube6.size = vec3(10, 0.05, 5);
	cube6.color = White;
	cube6.SetPos(-23.5, 0, 20.2);
	cube6.SetRotation(30, {0,1,0});
	cube_6 = App->physics->AddBody(cube6, 0);
	cube_6->collision_listeners.add(this);

	cube7.size = vec3(5, 0.05, 6);
	cube7.color = White;
	cube7.SetPos(-27.5, 0, 24);
	cube_7 = App->physics->AddBody(cube7, 0);
	cube_7->collision_listeners.add(this);

	cube8.size = vec3(5, 2, 5);
	cube8.color = White;
	cube8.SetPos(-27.5, 0, 28);
	cube8.SetRotation(30, { -1,0,0 });
	cube_8 = App->physics->AddBody(cube8, 0);
	cube_8->collision_listeners.add(this);

	//tunel1l.size = vec3(8, 3, 0.05);
	//tunel1l.color = White;
	//tunel1l.SetPos(-19.5, 1.5, 21.5);
	//tunel1l.SetRotation(30, { 0,1,0 });
	//tunel_1l = App->physics->AddBody(tunel1l, 0);
	//tunel_1l->collision_listeners.add(this);

	//tunel1r.size = vec3(10, 3, 0.05);
	//tunel1r.color = White;
	//tunel1r.SetPos(-24.5, 1.5, 18);
	//tunel1r.SetRotation(30, { 0,1,0 });
	//tunel_1r = App->physics->AddBody(tunel1r, 0);
	//tunel_1r->collision_listeners.add(this);

	//tunel1u.size = vec3(10, 0.05, 5);
	//tunel1u.color = White;
	//tunel1u.SetPos(-23.5, 3, 20.2);
	//tunel1u.SetRotation(30, { 0,1,0 });
	//tunel_1u = App->physics->AddBody(tunel1u, 0);
	//tunel_1u->collision_listeners.add(this);

	cube9.size = vec3(5, 2, 5);
	cube9.color = White;
	cube9.SetPos(-27.5, 1.2, 32.5);
	cube_9 = App->physics->AddBody(cube9, 0);
	cube_9->collision_listeners.add(this);

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

	cube_test->GetTransform(&cubetest->transform);
	cubetest->Render();


	cube_1->GetTransform(&cube1.transform);
	cube1.Render();
	cube_2->GetTransform(&cube2.transform);
	cube2.Render();
	cube_3->GetTransform(&cube3.transform);
	cube3.Render();
	cube_4->GetTransform(&cube4.transform);
	cube4.Render();
	cube_5->GetTransform(&cube5.transform);
	cube5.Render();
	cube_6->GetTransform(&cube6.transform);
	cube6.Render();
	cube_7->GetTransform(&cube7.transform);
	cube7.Render();
	cube_8->GetTransform(&cube8.transform);
	cube8.Render();
	/*tunel_1l->GetTransform(&tunel1l.transform);
	tunel1l.Render();
	tunel_1r->GetTransform(&tunel1r.transform);
	tunel1r.Render();
	tunel_1u->GetTransform(&tunel1u.transform);
	tunel1u.Render();*/
	cube_9->GetTransform(&cube9.transform);
	cube9.Render();
	p.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

