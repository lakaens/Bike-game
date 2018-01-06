#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include"PhysVehicle3D.h"
#include "SDL2_ttf-2.0.14\include\SDL_ttf.h"
#include <string>
#include <algorithm>
#include <iostream>
#include "ModuleAudio.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets (-37,1,8 /12?)
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->audio->PlayMusic("music/carmusic.ogg");

	TTF_Init();

	int window_w = 200;
	int window_h = 600;

	SDL_CreateWindowAndRenderer(250, 90, 0, &window, &renderer);
	//renderer = SDL_CreateRenderer(App->window->window, -1, 0);
	SDL_SetWindowPosition(window, SCREEN_WIDTH, 50);
	font = TTF_OpenFont("images/times.ttf", 24);
	if (font == NULL)
		LOG("FONT FAILED TO LOAD");

	//get_text_and_rect(renderer, 0, 0, text1, font, &texture1, &rect1);
	//get_text_and_rect(renderer, 0, rect1.y + rect1.h, "world", font, &texture2, &rect2);

	std::string s = std::to_string(lastscoref);
	lastscore = (char*)s.c_str();
	s = std::to_string(topscoref);
	topscore = (char*)s.c_str();
	char* charaux = "Last score: 0";
	get_text_and_rect(renderer, 0, 25, charaux, font, &texture2, &rect2);
	charaux = "Top score: 0";
	get_text_and_rect(renderer, 0, 50, charaux, font, &texture3, &rect3);
	
	//*****Sensor

	meta.size = { 5,5,1 };
	meta.SetPos(0, 1, 2);
	meta_ = App->physics->AddBody(meta, 0);
	meta_->SetAsSensor(true);
	meta_->collision_listeners.add(this);

	fmeta.size = { 5,5,1 };
	fmeta.SetPos(0, 1, -2);
	fmeta_ = App->physics->AddBody(fmeta, 0);
	fmeta_->SetAsSensor(true);
	fmeta_->collision_listeners.add(this);

	checkpoint1.size = { 1,5,5 };
	checkpoint1.SetPos(-39, 1, 19.65);
	checkpoint_1 = App->physics->AddBody(checkpoint1, 0);
	checkpoint_1->SetAsSensor(true);
	checkpoint_1->collision_listeners.add(this);

	checkpoint2.size = { 5,5,1 };
	checkpoint2.SetPos(-8.6, 4.9, 63);
	checkpoint_2 = App->physics->AddBody(checkpoint2, 0);
	checkpoint_2->SetAsSensor(true);
	checkpoint_2->collision_listeners.add(this);

	checkpoint3.size = { 5,5,1 };
	checkpoint3.SetPos(10, 3, 6.5);
	checkpoint_3 = App->physics->AddBody(checkpoint3, 0);
	checkpoint_3->SetAsSensor(true);
	checkpoint_3->collision_listeners.add(this);

	checkpoint4.size = { 1,5,5 };
	checkpoint4.SetPos(-22, 1, -29.3);
	checkpoint_4 = App->physics->AddBody(checkpoint4, 0);
	checkpoint_4->SetAsSensor(true);
	checkpoint_4->collision_listeners.add(this);

	//checkpoint5.size = { 1,5,5 };
	//checkpoint5.SetPos(-36.95, 1, 10.15);
	//checkpoint_5 = App->physics->AddBody(checkpoint5, 0);
	//checkpoint_5->SetAsSensor(true);
	//checkpoint_5->collision_listeners.add(this);

	floor.size = { 1000,0.05f,1000 };
	floor.SetPos(0, 0, 0);
	floor_ = App->physics->AddBody(floor, 0);
	floor_->SetAsSensor(true);
	floor_->collision_listeners.add(this);

	//******Constraint

	constraintcube.size = vec3(12, 12, 1);
	constraintcube.SetPos(-37, 1, 8);
	constraintcube.color = White;
	
	constraintpb = App->physics->AddBody(constraintcube, 10000000);
	constraintpb->GetBody()->setLinearFactor(btVector3(0, 0, 0));

	motor1.height = 1;
	motor1.radius = 0.1f;
	motor1.SetPos(-37, 1, 8);
	//motor1.SetRotation(90, vec3(0, 0, 1));
	motor_1 = App->physics->AddBody(motor1, 1000000);
	motor_1->GetBody()->setLinearFactor(btVector3(0, 0, 0));

	App->physics->AddConstraintHinge(*motor_1, *constraintpb, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 1, 0), vec3(0, 0, 0), true, true);

	//**********

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	cube1 = App->physics->AddCube(vec3(5, 0.05, 20), vec3(0, 1, 10), 0, vec3(1, 0, 0), Red);
	cube_1 = App->physics->AddCubePB(cube1, false, this);

	cube2 = App->physics->AddCube(vec3(7, 0.05, 5), vec3(-6, 1, 17.48), 0, vec3(1, 0, 0), Red);
	cube_2 = App->physics->AddCubePB(cube2, false, this);

	cube3 = App->physics->AddCube(vec3(5, 2, 5), vec3(-12, 0.7, 17.48), -15, vec3(0, 0, 1), Red);
	cube_3 = App->physics->AddCubePB(cube3, false, this);

	cube4 = App->physics->AddCube(vec3(5, 2, 5), vec3(-20, 0.7, 17.5), 15, vec3(0, 0, 1), Red);
	cube_4 = App->physics->AddCubePB(cube4, false, this);

	cube5 = App->physics->AddCube(vec3(12, 0.05, 5), vec3(-28.5, 1, 17.5), 0, vec3(1, 0, 0), Red);
	cube_5 = App->physics->AddCubePB(cube5, false, this);

	cube6 = App->physics->AddCube(vec3(12, 0.05, 5), vec3(-39, 1, 19.65), 23, vec3(0, 1, 0), Red);
	cube_6 = App->physics->AddCubePB(cube6, false, this);

	cube7 = App->physics->AddCube(vec3(5, 0.05, 13), vec3(-43, 1, 26.2), 0, vec3(1, 0, 0), Red);
	cube_7 = App->physics->AddCubePB(cube7, false, this);

	cube8 = App->physics->AddCube(vec3(5, 2, 5), vec3(-43, 1, 32), -30, vec3(1, 0, 0), Red);
	cube_8 = App->physics->AddCubePB(cube8, false, this);

	cube9 = App->physics->AddCube(vec3(5, 2, 9), vec3(-43, 2.1, 38.2), 0, vec3(1, 0, 0), Red);
	cube_9 = App->physics->AddCubePB(cube9, false, this);

	cube10 = App->physics->AddCube(vec3(5, 2, 10), vec3(-43, 0.45, 47.1), 20, vec3(1, 0, 0), Red);
	cube_10 = App->physics->AddCubePB(cube10, false, this);

	cube11 = App->physics->AddCube(vec3(5, 0.05, 18), vec3(-43, 1, 57.5), 0, vec3(1, 0, 0), Red);
	cube_11 = App->physics->AddCubePB(cube11, false, this);

	cube12 = App->physics->AddCube(vec3(20, 0.05, 5), vec3(-35.5, 1, 69), 0, vec3(1, 0, 0), Red);
	cube_12 = App->physics->AddCubePB(cube12, false, this);

	cube13 = App->physics->AddCube(vec3(15, 0.05, 5), vec3(-18.3, 2.95, 69), 15, vec3(0, 0, 1), Red);
	cube_13 = App->physics->AddCubePB(cube13, false, this);

	cube14 = App->physics->AddCube(vec3(5, 0.05, 17), vec3(-8.6, 4.9, 63), 0, vec3(1, 0, 0), Red);
	cube_14 = App->physics->AddCubePB(cube14, false, this);

	cube15 = App->physics->AddCube(vec3(5, 0.05, 12), vec3(-8.6, 2.85, 48.85), -20, vec3(1, 0, 0), Red);
	cube_15 = App->physics->AddCubePB(cube15, false, this);

	cube16 = App->physics->AddCube(vec3(5, 0.05, 15), vec3(-5, 1, 38), -30, vec3(0, 1, 0), Red);
	cube_16 = App->physics->AddCubePB(cube16, false, this);

	cube17 = App->physics->AddCube(vec3(5, 0.05, 10), vec3(2, 1, 29), -50, vec3(0, 1, 0), Red);
	cube_17 = App->physics->AddCubePB(cube17, false, this);

	cube18 = App->physics->AddCube(vec3(5, 2, 15), vec3(6, 0, 25), 35, vec3(4, -10, 0), Red);
	cube_18 = App->physics->AddCubePB(cube18, false, this);

	cube19 = App->physics->AddCube(vec3(5, 2, 25), vec3(10, 1.5, 6.5), 0, vec3(1, 0, 0), Red);
	cube_19 = App->physics->AddCubePB(cube19, false, this);

	cube20 = App->physics->AddCube(vec3(5, 0.05, 8), vec3(10, 2, -13), 0, vec3(1, 0, 0), Red);
	cube_20 = App->physics->AddCubePB(cube20, false, this);

	cube21 = App->physics->AddCube(vec3(5, 0.05, 8), vec3(10, 0.95, -20.88), 15, vec3(-1, 0, 0), Red);
	cube_21 = App->physics->AddCubePB(cube21, false, this);

	cube22 = App->physics->AddCube(vec3(5, 0.05, 12), vec3(10, 1, -26.8), 0, vec3(1, 0, 0), Red);
	cube_22 = App->physics->AddCubePB(cube22, false, this);

	cube23 = App->physics->AddCube(vec3(25, 0.05, 5), vec3(0, 1, -35.2), 0, vec3(1, 0, 0), Red);
	cube_23 = App->physics->AddCubePB(cube23, false, this);

	cube24 = App->physics->AddCube(vec3(25, 0.05, 5), vec3(-22, 1, -29.3), 30, vec3(0, 1, 0), Red);
	cube_24 = App->physics->AddCubePB(cube24, false, this);

	cube25 = App->physics->AddCube(vec3(7, 0.05, 5), vec3(-35.1, 1, -23.4), 0, vec3(1, 0, 0), Red);
	cube_25 = App->physics->AddCubePB(cube25, false, this);

	cube26 = App->physics->AddCube(vec3(5, 2, 5), vec3(-41.3, 0.7, -23.4), -15, vec3(0, 0, 1), Red);
	cube_26 = App->physics->AddCubePB(cube26, false, this);

	cube27 = App->physics->AddCube(vec3(5, 2, 5), vec3(-51.3, 0.7, -23.4), 15, vec3(0, 0, 1), Red);
	cube_27 = App->physics->AddCubePB(cube27, false, this);

	cube28 = App->physics->AddCube(vec3(5, 0.05, 15), vec3(-56.5, 1, -18), 0, vec3(1, 0, 0), Red);
	cube_28 = App->physics->AddCubePB(cube28, false, this);

	cube29 = App->physics->AddCube(vec3(25, 0.05, 5), vec3(-46.5, 1, -7.6), -25, vec3(0, 1, 0), Red);
	cube_29 = App->physics->AddCubePB(cube29, false, this);

	cube30 = App->physics->AddCube(vec3(5, 0.05, 15), vec3(-38, 1, 1.9), -25, vec3(0, 1, 0), Red);
	cube_30 = App->physics->AddCubePB(cube30, false, this);

	cube31 = App->physics->AddCube(vec3(13, 0.05, 5), vec3(-36.95, 1, 10.15), 0, vec3(1, 0, 0), Red);
	cube_31 = App->physics->AddCubePB(cube31, false, this);

	cube32 = App->physics->AddCube(vec3(5, 0.05, 30), vec3(-26.5, 1, -2), -25, vec3(0, 1, 0), Red);
	cube_32 = App->physics->AddCubePB(cube32, false, this);

	cube33 = App->physics->AddCube(vec3(25, 0.05, 5), vec3(-10, 1, -14.2), 0, vec3(1, 0, 0), Red);
	cube_33 = App->physics->AddCubePB(cube33, false, this);

	cube34 = App->physics->AddCube(vec3(5, 0.05, 12), vec3(0, 1, -6), 0, vec3(1, 0, 0), Red);
	cube_34 = App->physics->AddCubePB(cube34, false, this);



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

	

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
		App->player->vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		App->player->vehicle->body->setAngularVelocity(btVector3(0, 0, 0));
		App->player->vehicle->SetTransform(IdentityMatrix.M);
		App->player->vehicle->SetPos(0, 2, 2);
		cont = 0;
		metabool = true;

	}


	//*****TIMER
	if (metabool)//App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		timer_on = !timer_on;
		aux1 = (float)SDL_GetTicks() / 1000;
		aux3 = cont;
		LOG("Timer: %f", cont);
		metabool = false;
	}

	if (timer_on)
	{

		aux2 = (float)SDL_GetTicks() / 1000 - aux1;

		cont = aux2 + aux3;
	}

	//**INT TO CHAR
	//cont=(((int)cont * 100) % 100) / 100;
	std::string s = std::to_string(cont);
	//cont_char = s.c_str();
	//cont_charr = (char*)cont_char;
	cont_charr = (char*)s.c_str();
	

	std::string s1 = std::to_string(lastscoref);
	lastscore = (char*)s1.c_str();
	std::string s2 = std::to_string(topscoref);
	topscore = (char*)s2.c_str();
	flagg = false;
	
	//TIMER****



	constraintpb->GetTransform(&constraintcube.transform);
	constraintcube.Render();

	//meta_->GetTransform(&meta.transform);
	//meta.Render();

	//fmeta_->GetTransform(&fmeta.transform);
	//fmeta.Render();
	//**Print text

	/*char* charaux = "Last score: 0";
	get_text_and_rect(renderer, 0, 25, charaux, font, &texture2, &rect2);
	charaux = "Top score: 0";
	get_text_and_rect(renderer, 0, 50, charaux, font, &texture3, &rect3);*/





	get_text_and_rect(renderer, 0, 0, titletime, font, &texturetime, &recttime);
	get_text_and_rect(renderer, 0, 25, titlelast, font, &lastlap, &rectlast);
	get_text_and_rect(renderer, 0, 50, titletop, font, &toplap, &recttop);
	get_text_and_rect(renderer, recttime.w, 0, cont_charr, font, &texture1, &rect1);
	get_text_and_rect(renderer, rectlast.w, 25, lastscore, font, &texture2, &rect2);
	get_text_and_rect(renderer, recttop.w, 50, topscore, font, &texture3, &rect3);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, texture1, NULL, &rect1);
	SDL_RenderCopy(renderer, texture2, NULL, &rect2);
	SDL_RenderCopy(renderer, texture3, NULL, &rect3);
	SDL_RenderCopy(renderer, lastlap, NULL, &rectlast);
	SDL_RenderCopy(renderer, toplap, NULL, &recttop);
	SDL_RenderCopy(renderer, texturetime, NULL, &recttime);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture1);
	SDL_DestroyTexture(texture2);
	SDL_DestroyTexture(texture3);
	SDL_DestroyTexture(lastlap);
	SDL_DestroyTexture(toplap);
	SDL_DestroyTexture(texturetime);
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

	cube_24->GetTransform(&cube24->transform);
	cube24->Render();

	cube_25->GetTransform(&cube25->transform);
	cube25->Render();

	cube_26->GetTransform(&cube26->transform);
	cube26->Render();

	cube_27->GetTransform(&cube27->transform);
	cube27->Render();

	cube_28->GetTransform(&cube28->transform);
	cube28->Render();

	cube_29->GetTransform(&cube29->transform);
	cube29->Render();

	cube_30->GetTransform(&cube30->transform);
	cube30->Render();

	cube_31->GetTransform(&cube31->transform);
	cube31->Render();

	cube_32->GetTransform(&cube32->transform);
	cube32->Render();

	cube_33->GetTransform(&cube33->transform);
	cube33->Render();

	cube_34->GetTransform(&cube34->transform);
	cube34->Render();

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
	uint currentTime = SDL_GetTicks();
	

	if (body1 == meta_ && body2 == (PhysBody3D*)App->player->vehicle && metabooldisabled + delay < currentTime) {//body1 == sensor_1) {
		//App->player->count = true;
		delay = 3000;
		metabooldisabled = SDL_GetTicks();
		metabool= !metabool;
		LOG("current:%i, bool:%i", currentTime, metabooldisabled);
		checklist = 0;
	}

	if (body1 == fmeta_ && body2 == (PhysBody3D*)App->player->vehicle && fmetabooldisabled + delay2 < currentTime) {//body1 == sensor_1) {
		LOG("final time:%f", cont);
		//Pintar aqui el tiempo de la vuelta. Printar 3 primeros + Ultima vuelta

		//scores[index] = cont;
		//index++;
		//std::sort(scores, scores + 100);

		lastscoref = cont;
		LOG("LASTSCORE: %f", lastscoref);
		if (lastscoref < topscoref)
			topscoref = lastscoref;


		std::string s = std::to_string(lastscoref);
		lastscore = (char*)s.c_str();
		s = std::to_string(topscoref);
		topscore = (char*)s.c_str();

		
		//***
		


		delay2 = 3000;
		fmetabooldisabled = SDL_GetTicks();

		cont = 0;
		delay = 0;
		metabool = true;
	}
	//*****
	if (body1 == meta_ && body2 == (PhysBody3D*)App->player->vehicle) {//body1 == sensor_1) {
		App->player->count = true;
	}
	if (body1 == fmeta_ && body2 == (PhysBody3D*)App->player->vehicle) {//body1 == sensor_1) {

	}
	if (body1 == checkpoint_1 && body2 == (PhysBody3D*)App->player->vehicle) {
		checklist = 1;
	}
	if (body1 == checkpoint_2 && body2 == (PhysBody3D*)App->player->vehicle) {
		checklist = 2;
	}
	if (body1 == checkpoint_3 && body2 == (PhysBody3D*)App->player->vehicle) {
		checklist = 3;
	}
	if (body1 == checkpoint_4 && body2 == (PhysBody3D*)App->player->vehicle) {
		checklist = 4;
	}
	/*if (body1 == checkpoint_5&& body2 == (PhysBody3D*)App->player->vehicle) {
		checklist = 5;
	}*/
	if (body1 == floor_ && body2 == (PhysBody3D*)App->player->vehicle) {
		switch (checklist) {
		case 0:
			App->player->vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
			App->player->vehicle->body->setAngularVelocity(btVector3(0, 0, 0));
			App->player->vehicle->SetTransform(IdentityMatrix.M);
			App->player->vehicle->SetPos(0, 2, 4);

			break;
		case 1:
			App->player->vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
			App->player->vehicle->body->setAngularVelocity(btVector3(0, 0, 0));
			App->player->vehicle->SetTransform(IdentityMatrix.rotate(300, { 0,1,0 }).M);
			App->player->vehicle->SetPos(-39, 1, 19.65);
			break;
		case 2:
			App->player->vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
			App->player->vehicle->body->setAngularVelocity(btVector3(0, 0, 0));
			App->player->vehicle->SetTransform(IdentityMatrix.rotate(180, { 0, 1, 0 }).M);
			App->player->vehicle->SetPos(-8.6, 4.9, 63);


			break;
		case 3:
			App->player->vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
			App->player->vehicle->body->setAngularVelocity(btVector3(0, 0, 0));
			App->player->vehicle->SetTransform(IdentityMatrix.rotate(180, { 0,1,0 }).M);
			App->player->vehicle->SetPos(10, 3, 6.5);
			break;
		case 4:
			App->player->vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
			App->player->vehicle->body->setAngularVelocity(btVector3(0, 0, 0));
			App->player->vehicle->SetTransform(IdentityMatrix.rotate(300, { 0,1,0 }).M);
			App->player->vehicle->SetPos(-22, 1, -29.3);
			break;
		/*case 5:
			App->player->vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
			App->player->vehicle->SetTransform(IdentityMatrix.M);
			App->player->vehicle->SetPos(-36.95, 1, 10.15);
			break;*/
		default:
			break;
		}
	}

}

