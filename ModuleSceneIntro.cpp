#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = fons = boll= NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	fons = App->textures->Load("pinball/PinballBack1.png");
	boll = App->textures->Load("pinball/wheel.png");
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);
	

	contorn=App->physics->CreateChain(-1, 0, Pinbla, 138, b2BodyType::b2_staticBody);

	conLV=App->physics->CreateChain(0, 0, leftV, 112, b2BodyType::b2_staticBody);
	conLT=App->physics->CreateChain(0, 0, leftT, 22, b2BodyType::b2_staticBody);
	conRT=App->physics->CreateChain(0, 0, rightT, 26, b2BodyType::b2_staticBody);
	conRTop=App->physics->CreateChain(0, 0, rightTop, 78, b2BodyType::b2_staticBody);
	conMid =App->physics->CreateChain(0, 0, Mid, 54, b2BodyType::b2_staticBody);

	conButtonV=App->physics->CreateCircle(225, 267, 17, b2BodyType::b2_staticBody);
	conButtonB=App->physics->CreateCircle(278, 218, 17, b2BodyType::b2_staticBody);
	conButtonR=App->physics->CreateCircle(316, 283, 17, b2BodyType::b2_staticBody);

	conMiniButtonL= App->physics->CreateCircle(188, 320, 8, b2BodyType::b2_staticBody);
	conMiniButtonR=App->physics->CreateCircle(150, 349, 8, b2BodyType::b2_staticBody);
	conMiniButtonT=App->physics->CreateCircle(152, 306, 8, b2BodyType::b2_staticBody);

	
	
	rbumper = App->physics->CreateChain(0, 0, bumperright, 8, b2BodyType::b2_staticBody);
	lbumper= App->physics->CreateChain(0, 0, bumperleft, 8, b2BodyType::b2_staticBody);

	iPoint triangle_pos_a = { 56,250 };
	tri1=App->physics->CreateChain(0, 0, triangleTop, 6, b2BodyType::b2_dynamicBody);
	PhysBody* centertria = App->physics->CreateCircle(triangle_pos_a.x, triangle_pos_a.y, 3, b2BodyType::b2_staticBody);

	top_tri_join = App->physics->CreateRevoluteJoint(centertria, tri1, 0.0f, 0.0f, 0, 360, 300, 40);

	contorn=App->physics->CreateChain(1, 0, triangleMid, 6, b2BodyType::b2_staticBody);
	contorn=App->physics->CreateChain(1, 0, triangleBot, 6, b2BodyType::b2_staticBody);
	conLV=App->physics->CreateChain(0, 0, Black, 26, b2BodyType::b2_staticBody);

	
	
	
	launcher = App->physics->CreateRectangle(442, 700, 18, 20, b2BodyType::b2_staticBody);
	
	
	iPoint left_flipper_pos = { 154,734 };
	PhysBody* Ball_l_A = App->physics->CreateCircle(left_flipper_pos.x, left_flipper_pos.y, 8, b2BodyType::b2_staticBody);
	PhysBody* Chain_l_B = App->physics->CreateRectangle(left_flipper_pos.x, left_flipper_pos.y, 74, 15, b2BodyType::b2_dynamicBody);

	l_flipper_joint = App->physics->CreateRevoluteJoint(Ball_l_A, Chain_l_B, -24.0f, 0.0f, 30, -15, 300, 0);

	

	iPoint right_flipper_pos = { 297,734 };
	PhysBody* Ball_r_A = App->physics->CreateCircle(right_flipper_pos.x, right_flipper_pos.y, 8, b2BodyType::b2_staticBody);
	PhysBody* Chain_r_B = App->physics->CreateRectangle(right_flipper_pos.x, right_flipper_pos.y, 74, 15, b2BodyType::b2_dynamicBody);
	

	r_flipper_joint = App->physics->CreateRevoluteJoint(Ball_r_A, Chain_r_B, 24.0f, 0.0f, 15, -30, 300, 0);



	/*iPoint triangle_pos_a = { 60,70 };
	PhysBody* Centertra = App->physics->CreateCircle(triangle_pos_a.x, triangle_pos_a.y, 3, b2BodyType::b2_staticBody);
	PhysBody* Chain_l_B = App->physics->CreateChain(left_flipper_pos.x, left_flipper_pos.y, 74, 15, b2BodyType::b2_dynamicBody);

	l_flipper_joint = App->physics->CreateRevoluteJoint(Ball_l_A, Chain_l_B, -24.0f, 0.0f, 30, -15, 300, 0);*/

	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}
	
	App->renderer->Blit(fons, 0, 0, NULL, 0.0f, NULL);
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 7, b2BodyType::b2_dynamicBody));
		circles.getLast()->data->listener = this;
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50, b2BodyType::b2_dynamicBody));
	}
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		if(ball!= NULL)
			ball->body->SetType(b2BodyType::b2_dynamicBody);

	
	}
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN) {

		if(ball==NULL)
		
		ball=	App->physics->CreateCircle(440, 680, 7, b2BodyType::b2_staticBody);
		ball->listener = this;
	}
	
	if ((App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) || (App->input->GetKey(SDL_SCANCODE_Z) == KEY_REPEAT))
		l_flipper_joint->SetMotorSpeed(-20);
	else
		l_flipper_joint->SetMotorSpeed(20);

	//// Right flippers
	if ((App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) || (App->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT))
		r_flipper_joint->SetMotorSpeed(20);
	else
		r_flipper_joint->SetMotorSpeed(-20);

	// Prepare for raycast ------------------------------------------------------

	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	
	/*SDL_Rect section2;
	section2.x = 95;
	section2.y = 855;
	section2.h = 21;
	section2.w = 62;

	App->renderer->Blit(sprites, 168, 760, &section2, 1.0f, (-rev_joint_left->GetJointAngle() * RADTODEG), 10, 15);*/
	/*p2List_item<PhysBody*>* c = circles.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}
	

	c = boxes.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if (ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if (hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}
	c = ball;
	*/
	/*while (ball != NULL) {
		int x, y;
		ball->GetPosition(x, y);

		App->renderer->Blit(boll, x, y, NULL, 1.0f, ball->GetRotation());
	}*/
	// ray -----------------
	if (ray_on == true)
	{
		fVector destination(mouse.x - ray.x, mouse.y - ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if (normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	//App->audio->PlayFx(bonus_fx);
	if (bodyB == launcher) {
		bodyA->body->SetLinearVelocity(b2Vec2(0, -30));
	}

	if (bodyB == sensor) {

		ball = NULL;
	}

	if (bodyB == conMiniButtonL || bodyB == conMiniButtonR || bodyB == conMiniButtonT) {

		bodyA->body->SetLinearVelocity(b2Vec2(0, -10));
		//App->audio->PlayFx(bonus_fx);
	}
	if (bodyB == conButtonB || bodyB == conButtonR || bodyB == conButtonV) {

		bodyA->body->SetLinearVelocity(b2Vec2(0, -20));
		//App->audio->PlayFx(bonus_fx);
	}
	if (bodyB == rbumper) {

		bodyA->body->SetLinearVelocity(b2Vec2(-10, -10));
	}
	if (bodyB == lbumper) {

		bodyA->body->SetLinearVelocity(b2Vec2(10, -10));
	}
	
	/*
	if(bodyA)
	{
	bodyA->GetPosition(x, y);
	App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
	bodyB->GetPosition(x, y);
	App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}