#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include"PhysVehicle3D.h"
#include "SDL2_ttf-2.0.14\include\SDL_ttf.h"
#include <string>

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


	TTF_Init();

	int window_w = 200;
	int window_h = 600;

	SDL_CreateWindowAndRenderer(200, 600, 0, &window, &renderer);
	//renderer = SDL_CreateRenderer(App->window->window, -1, 0);
	SDL_SetWindowPosition(window, SCREEN_WIDTH / 2 - window_w - 25, SCREEN_HEIGHT / 2);
	font = TTF_OpenFont("images/times.ttf", 24);
	if (font == NULL)
		LOG("FONT FAILED TO LOAD");

	get_text_and_rect(renderer, 0, 0, text1, font, &texture1, &rect1);
	//get_text_and_rect(renderer, 0, rect1.y + rect1.h, "world", font, &texture2, &rect2);



	//*****Sensor

	sensor1.size = { 10,2,1 };
	sensor1.SetPos(30, 0, 30);
	sensor_1 = App->physics->AddBody(sensor1, 0);
	sensor_1->SetAsSensor(true);
	sensor_1->collision_listeners.add(this);
	

	//******Constraint

	constraintcube.size = vec3(120, 12, 1);
	constraintcube.SetPos(30, 0, 30);
	constraintcube.color = White;
	constraintcube.SetRotation(90, vec3(0, 0, 1));
	constraintpb = App->physics->AddBody(constraintcube, 10000);
	constraintpb->GetBody()->setLinearFactor(btVector3(0, 0, 0));

	motor1.height = 1;
	motor1.radius = 0.1f;
	motor1.SetPos(30, 0, 30);
	motor1.SetRotation(90, vec3(0, 0, 1));
	motor_1 = App->physics->AddBody(motor1, 10000);
	motor_1->GetBody()->setLinearFactor(btVector3(0, 0, 0));

	App->physics->AddConstraintHinge(*motor_1, *constraintpb, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 0, 0), true, true);

	//**********

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	cube1 = App->physics->AddCube(vec3(5, 0.05, 20), vec3(0, 0, 10), 0, vec3(1,0,0), Green);
	cube_1 = App->physics->AddCubePB(cube1, false, this);

	cube2 = App->physics->AddCube(vec3(5, 0.05, 4), vec3(-4.5, 0, 18), 0, vec3(1,0,0), Green);
	cube_2 = App->physics->AddCubePB(cube2, false, this);

	cube3 = App->physics->AddCube(vec3(5, 2, 4), vec3(-9, 0, 18), -25, vec3(0,0,1), Green);
	cube_3 = App->physics->AddCubePB(cube3, false, this);

	cube4 = App->physics->AddCube(vec3(5, 2, 4), vec3(-15, 0, 18), 25, vec3(0, 0, 1), Green);
	cube_4 = App->physics->AddCubePB(cube4, false, this);

	cube5 = App->physics->AddCube(vec3(5, 0.05, 4), vec3(-19.5, 0, 18), 0, vec3(1, 0, 0), Green);
	cube_5 = App->physics->AddCubePB(cube5, false, this);

	cube6 = App->physics->AddCube(vec3(8, 0.05, 5), vec3(-24.7, 0, 19.7), 23, vec3(0, 1, 0), Green);
	cube_6 = App->physics->AddCubePB(cube6, false, this);

	cube7 = App->physics->AddCube(vec3(5, 0.05, 10), vec3(-27.5, 0, 25), 0, vec3(1, 0, 0), Green);
	cube_7 = App->physics->AddCubePB(cube7, false, this);

	cube8 = App->physics->AddCube(vec3(5, 2, 5), vec3(-27.5, 0, 32), -30, vec3(1, 0, 0), Green);
	cube_8 = App->physics->AddCubePB(cube8, false, this);
	
	cube9 = App->physics->AddCube(vec3(5, 2, 5), vec3(-27.5, 1.2, 36.5), 0, vec3(1, 0, 0), Green);
	cube_9 = App->physics->AddCubePB(cube9, false, this);

	cube10 = App->physics->AddCube(vec3(5, 2, 5), vec3(-27.5, 0, 41), 30, vec3(1, 0, 0), Green);
	cube_10 = App->physics->AddCubePB(cube10, false, this);

	cube11 = App->physics->AddCube(vec3(5, 0.05, 10), vec3(-27.5, 0, 46), 0, vec3(1, 0, 0), Green);
	cube_11 = App->physics->AddCubePB(cube11, false, this);

	cube12 = App->physics->AddCube(vec3(7, 0.05, 4), vec3(-21.5, 0, 49), 0, vec3(1, 0, 0), Green);
	cube_12 = App->physics->AddCubePB(cube12, false, this);

	cube13 = App->physics->AddCube(vec3(10, 0.05, 4), vec3(-15, 1, 49), 15, vec3(0, 0, 1), Green);
	cube_13 = App->physics->AddCubePB(cube13, false, this);

	cube14 = App->physics->AddCube(vec3(5, 0.05, 17), vec3(-7.8, 2.3, 42.5), 0, vec3(1, 0, 0), Green);
	cube_14 = App->physics->AddCubePB(cube14, false, this);

	cube15 = App->physics->AddCube(vec3(3, 0.05, 8), vec3(-2.5, 0.75, 29), -60, vec3(0, 1, 0), Green);
	cube_15 = App->physics->AddCubePB(cube15, false, this);

	cube16 = App->physics->AddCube(vec3(12, 0.05, 4), vec3(8.5, 0, 23), 0, vec3(1, 0, 0), Green);
	cube_16 = App->physics->AddCubePB(cube16, false, this);

	cube17 = App->physics->AddCube(vec3(5, 0.05, 8), vec3(12.5, 0, 18), -20, vec3(0, 1, 0), Green);
	cube_17 = App->physics->AddCubePB(cube17, false, this);

	cube18 = App->physics->AddCube(vec3(5, 2, 5), vec3(14, 0, 12), 22.5, vec3(1.6, -1, 0), Green);
	cube_18 = App->physics->AddCubePB(cube18, false, this);

	cube19 = App->physics->AddCube(vec3(5, 2, 7.8), vec3(14.6, 0.8, 6), 0, vec3(1, 0, 0), Green);
	cube_19 = App->physics->AddCubePB(cube19, false, this);

	cube20 = App->physics->AddCube(vec3(5, 2, 5), vec3(14.6, -0.1, 0.4), -22.5, vec3(1, 0, 0), Green);
	cube_20 = App->physics->AddCubePB(cube20, false, this);

	cube21 = App->physics->AddCube(vec3(5, 0.05, 12), vec3(16.5, 0, -7), -20, vec3(0, 1, 0), Green);
	cube_21 = App->physics->AddCubePB(cube21, false, this);

	cube22 = App->physics->AddCube(vec3(5, 0.05, 15), vec3(16, 0, -18), 20, vec3(0, 1, 0), Green);
	cube_22 = App->physics->AddCubePB(cube22, false, this);

	cube23 = App->physics->AddCube(vec3(15, 0.05, 4), vec3(7.8, 0, -24), 0, vec3(1, 0, 0), Green);
	cube_23 = App->physics->AddCubePB(cube23, false, this);

	////tunel1l.size = vec3(8, 3, 0.05);
	////tunel1l.color = White;
	////tunel1l.SetPos(-19.5, 1.5, 21.5);
	////tunel1l.SetRotation(30, { 0,1,0 });
	////tunel_1l = App->physics->AddBody(tunel1l, 0);
	////tunel_1l->collision_listeners.add(this);

	////tunel1r.size = vec3(10, 3, 0.05);
	////tunel1r.color = White;
	////tunel1r.SetPos(-24.5, 1.5, 18);
	////tunel1r.SetRotation(30, { 0,1,0 });
	////tunel_1r = App->physics->AddBody(tunel1r, 0);
	////tunel_1r->collision_listeners.add(this);

	////tunel1u.size = vec3(10, 0.05, 5);
	////tunel1u.color = White;
	////tunel1u.SetPos(-23.5, 3, 20.2);
	////tunel1u.SetRotation(30, { 0,1,0 });
	////tunel_1u = App->physics->AddBody(tunel1u, 0);
	////tunel_1u->collision_listeners.add(this);


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	TTF_Quit();
	SDL_DestroyTexture(texture1);
	SDL_DestroyTexture(texture2);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;

	//*****TIMER
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		timer = !timer;
		aux1 = (float)SDL_GetTicks() / 1000;
		aux3 = cont;
		LOG("Timer: %f", cont);
	}

	if (timer)
	{

		aux2 = (float)SDL_GetTicks() / 1000 - aux1;

		cont = aux2 + aux3;
	}

	//**INT TO CHAR
	//cont=(((int)cont * 100) % 100) / 100;
	std::string s = std::to_string(cont);
	cont_char = s.c_str();
	cont_charr = (char*)cont_char;

	//TIMER****

	constraintpb->GetTransform(&constraintcube.transform);
	constraintcube.Render();

	sensor_1->GetTransform(&sensor1.transform);
	sensor1.Render();

	//**Print text

	get_text_and_rect(renderer, 0, 0, cont_charr, font, &texture1, &rect1);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, texture1, NULL, &rect1);
	SDL_RenderCopy(renderer, texture2, NULL, &rect2);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture1);

	//*******

	cube_1->GetTransform(&cube1->transform);
	cube1->Render();

	cube_2->GetTransform(&cube2->transform);
	cube2->Render();

	cube_3->GetTransform(&cube3->transform);
	cube3->Render();

	cube_4->GetTransform(&cube4->transform);
	cube4->Render();

	cube_5->GetTransform(&cube5->transform);
	cube5->Render();

	cube_6->GetTransform(&cube6->transform);
	cube6->Render();

	cube_7->GetTransform(&cube7->transform);
	cube7->Render();

	cube_8->GetTransform(&cube8->transform);
	cube8->Render();

	cube_9->GetTransform(&cube9->transform);
	cube9->Render();

	cube_10->GetTransform(&cube10->transform);
	cube10->Render();

	cube_11->GetTransform(&cube11->transform);
	cube11->Render();

	cube_12->GetTransform(&cube12->transform);
	cube12->Render();

	cube_13->GetTransform(&cube13->transform);
	cube13->Render();

	cube_14->GetTransform(&cube14->transform);
	cube14->Render();

	cube_15->GetTransform(&cube15->transform);
	cube15->Render();

	cube_16->GetTransform(&cube16->transform);
	cube16->Render();

	cube_17->GetTransform(&cube17->transform);
	cube17->Render();

	cube_18->GetTransform(&cube18->transform);
	cube18->Render();

	cube_19->GetTransform(&cube19->transform);
	cube19->Render();

	cube_20->GetTransform(&cube20->transform);
	cube20->Render();

	cube_21->GetTransform(&cube21->transform);
	cube21->Render();

	cube_22->GetTransform(&cube22->transform);
	cube22->Render();

	cube_23->GetTransform(&cube23->transform);
	cube23->Render();


	/*tunel_1l->GetTransform(&tunel1l.transform);
	tunel1l.Render();
	tunel_1r->GetTransform(&tunel1r.transform);
	tunel1r.Render();
	tunel_1u->GetTransform(&tunel1u.transform);
	tunel1u.Render();*/
	p.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1==pb_chassis || body1==sensor_1){//body1 == sensor_1) {
		LOG("COLLISIOOOOON");
	}
	LOG("REEEEEEEEEEEEEE");
}

