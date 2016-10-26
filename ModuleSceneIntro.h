#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	PhysBody* contorn;
	PhysBody* conLV;
	PhysBody* conLT;
	PhysBody* conRT;
	PhysBody* conRTop;
	PhysBody* conMid;
	
		
	PhysBody* launcher;
	PhysBody* ball;
	PhysBody* conMiniButtonL;
	PhysBody* conMiniButtonR;
	PhysBody* conMiniButtonT;
	PhysBody* conButtonB;
	PhysBody* conButtonV;
	PhysBody* conButtonR;
	PhysBody* rbumper;
	PhysBody* lbumper;
	
	b2RevoluteJoint* l_flipper_joint=nullptr;
	b2RevoluteJoint* r_flipper_joint=nullptr;

	// Pivot 0, 0
	int Pinbla[138] = {
		398, 405,
		413, 366,
		419, 338,
		422, 315,
		425, 295,
		425, 277,
		424, 255,
		422, 234,
		419, 218,
		410, 190,
		403, 173,
		395, 161,
		381, 141,
		365, 124,
		345, 108,
		317, 92,
		296, 83,
		277, 76,
		250, 71,
		224, 70,
		201, 71,
		182, 73,
		165, 77,
		143, 86,
		128, 94,
		112, 102,
		93, 116,
		79, 128,
		65, 146,
		53, 161,
		42, 180,
		35, 197,
		30, 218,
		26, 232,
		26, 243,
		25, 261,
		10, 522,
		35, 558,
		8, 576,
		20, 647,
		138, 718,
		138, 799,
		0, 800,
		1, 0,
		454, 0,
		455, 801,
		314, 800,
		314, 720,
		435, 642,
		433, 573,
		427, 546,
		419, 526,
		412, 510,
		402, 498,
		418, 516,
		424, 534,
		432, 561,
		435, 647,
		436, 797,
		454, 797,
		455, 572,
		454, 547,
		450, 530,
		444, 516,
		435, 500,
		426, 486,
		419, 479,
		429, 457,
		398, 415
	};

	int leftV[112] = {
		197, 191,
		159, 216,
		145, 226,
		136, 226,
		128, 228,
		122, 233,
		113, 240,
		106, 250,
		99, 260,
		94, 269,
		88, 282,
		86, 291,
		83, 303,
		81, 317,
		80, 329,
		79, 341,
		79, 355,
		80, 368,
		82, 379,
		83, 389,
		86, 400,
		89, 411,
		95, 424,
		97, 429,
		75, 468,
		69, 459,
		64, 445,
		62, 424,
		63, 407,
		64, 390,
		71, 370,
		77, 356,
		76, 306,
		77, 275,
		76, 257,
		76, 229,
		78, 209,
		80, 193,
		84, 175,
		89, 162,
		95, 147,
		104, 135,
		115, 125,
		126, 115,
		136, 108,
		145, 103,
		150, 101,
		149, 111,
		150, 121,
		152, 130,
		158, 140,
		162, 147,
		169, 155,
		175, 164,
		185, 172,
		196, 178
	};

	int leftT[22] = {
		76, 554,
		67, 552,
		59, 556,
		53, 561,
		41, 630,
		43, 638,
		91, 663,
		99, 662,
		106, 655,
		109, 645,
		84, 558
	};
	int rightT[26] =
	{ 405, 633,
		391, 561,
		387, 556,
		379, 551,
		372, 551,
		366, 553,
		362, 560,
		336, 647,
		340, 658,
		351, 662,
		373, 653,
		388, 646,
		401, 638
	};
	int rightTop[78] =
	{ 226, 126,
		254, 104,
		259, 104,
		263, 106,
		267, 109,
		272, 112,
		278, 114,
		284, 116,
		291, 117,
		297, 117,
		304, 118,
		312, 118,
		321, 119,
		326, 120,
		336, 122,
		342, 126,
		346, 130,
		351, 137,
		354, 146,
		355, 157,
		354, 166,
		351, 183,
		345, 176,
		340, 170,
		334, 164,
		327, 160,
		319, 157,
		310, 155,
		302, 154,
		294, 154,
		284, 154,
		276, 156,
		268, 157,
		262, 156,
		255, 154,
		249, 152,
		240, 146,
		234, 140,
		227, 132 };
	int Mid[54] = { 222, 324,
		233, 323,
		242, 324,
		252, 326,
		257, 328,
		284, 336,
		309, 351,
		316, 353,
		324, 351,
		331, 344,
		356, 319,
		362, 310,
		362, 305,
		356, 304,
		349, 307,
		338, 311,
		328, 310,
		315, 309,
		302, 305,
		292, 302,
		280, 298,
		265, 293,
		257, 295,
		247, 300,
		235, 306,
		223, 313,
		218, 319 };

	int triangleTop[6] = {
		65, 269,
		31, 243,
		66, 232
	};
	int triangleMid[6] = {
		60, 285,
		59, 322,
		30, 297
	};
	int triangleBot[6] = {
		55, 377,
		24, 351,
		59, 339
	};
	int Black[26] = {
		379, 168,
		384, 253,
		380, 263,
		355, 249,
		326, 237,
		333, 225,
		342, 220,
		352, 215,
		360, 211,
		367, 205,
		371, 199,
		371, 188,
		377, 171
	};

	int RampLeft[22] = {
		78, 205,
		67, 226,
		55, 235,
		45, 239,
		78, 244,
		73, 322,
		65, 336,
		51, 350,
		37, 357,
		75, 367,
		85, 200
	};
	int RampRight[14] = {
		18, 261,
		25, 277,
		31, 287,
		39, 294,
		45, 298,
		52, 300,
		15, 317
	};
	int bumperleft[8] = {
		88, 570,
		107, 632,
		92, 636,
		69, 568
		
	};

	
	
	int bumperright[8] = {
		357, 568,
		339, 630,
		355, 637,
		369, 577
	};
	PhysBody* sensor;
	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* boll;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* fons;
	SDL_Texture* lflip;
	SDL_Texture* rflip;
	SDL_Texture* Triangle;
	

	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;
};