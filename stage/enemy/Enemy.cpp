#include "Enemy.h"

void Enemy::Move()
{
}

void Enemy::Initialize()
{
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//modelDoragon[0] = Model::Create();
	modelDoragon[0] = Model::CreateFromOBJ("Doragon", true);
	modelDoragon[1] = Model::CreateFromOBJ("Doragon_Head", true);	//“ª
	modelDoragon[2] = Model::CreateFromOBJ("Doragon_Jaw", true);	//Š{
	//Žñ
	for (int i = 3; i < modelNum; i++)
	{
		modelDoragon[i] = Model::CreateFromOBJ("Doragon_neck", true);
	}
	//worldTransform_[0].Initialize();
	ParentInitialize();
	worldTransform_[0].scale_ = {20.0f,20.0f,20.0f};
}

void Enemy::Update()
{
	worldTransform_[0].Update();
	ParentUpdate();
}

void Enemy::Draw(ViewProjection viewProjection)
{
	//modelDoragon[0]->Draw(worldTransform_[0], viewProjection);//‘åŒ³
	//modelDoragon[1]->Draw(worldTransform_[1], viewProjection);//“ª
	//modelDoragon[2]->Draw(worldTransform_[2], viewProjection);//Š{
	////Žñ
	//modelDoragon[3]->Draw(worldTransform_[3], viewProjection);
	//modelDoragon[4]->Draw(worldTransform_[4], viewProjection);
	//modelDoragon[5]->Draw(worldTransform_[5], viewProjection);
	//modelDoragon[6]->Draw(worldTransform_[6], viewProjection);
	//modelDoragon[7]->Draw(worldTransform_[7], viewProjection);

	for (int i = 1; i < modelNum; i++)
	{
		modelDoragon[i]->Draw(worldTransform_[i], viewProjection);
	}
}

void Enemy::ParentInitialize()
{
	worldTransform_[0].Initialize();

	//“ª
	worldTransform_[1].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[1].translation_ = { 0.0f,14.0f,-4.0f }; 
	worldTransform_[1].parent_ = &worldTransform_[0];
	worldTransform_[1].Initialize();

	//Š{
	worldTransform_[2].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[2].translation_ = { 0.0f,14.0f,-4.0f };
	worldTransform_[2].parent_ = &worldTransform_[0];
	worldTransform_[2].Initialize();

	//Žñ
	worldTransform_[3].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[3].translation_ = { 0.0f,15.0f,2.0f };
	worldTransform_[3].rotation_.x = -90 * PI / 180;
	worldTransform_[3].parent_ = &worldTransform_[0];
	worldTransform_[3].Initialize();

	worldTransform_[4].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[4].translation_ = { 0.0f,14.0f,4.5f }; 
	worldTransform_[4].rotation_.x = -50 * PI / 180;
	worldTransform_[4].parent_ = &worldTransform_[0];
	worldTransform_[4].Initialize();

	worldTransform_[5].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[5].translation_ = { 0.0f,11.5f,6.0f }; 
	worldTransform_[5].rotation_.x = 6 * PI / 180;
	worldTransform_[5].parent_ = &worldTransform_[0];
	worldTransform_[5].Initialize();

	worldTransform_[6].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[6].translation_ = { 0.0f,8.0f,5.0f }; 
	worldTransform_[6].rotation_.x = 43 * PI / 180;
	worldTransform_[6].parent_ = &worldTransform_[0];
	worldTransform_[6].Initialize();

	worldTransform_[7].scale_ = Vector3(23.0f, 23.0f, 23.0f);
	worldTransform_[7].translation_ = { 0.0f,5.5f,4.0f };
	worldTransform_[7].rotation_.x = 16 * PI / 180;
	worldTransform_[7].parent_ = &worldTransform_[0];
	worldTransform_[7].Initialize();

	worldTransform_[8].scale_ = Vector3(26.0f, 26.0f, 26.0f);
	worldTransform_[8].translation_ = { 0.0f,2.2f,3.5f };
	worldTransform_[8].rotation_.x = 4 * PI / 180;
	worldTransform_[8].parent_ = &worldTransform_[0];
	worldTransform_[8].Initialize();

	worldTransform_[9].scale_ = Vector3(31.0f, 31.0f, 31.0f);
	worldTransform_[9].translation_ = { 0.0f,-2.0f,3.5f };
	worldTransform_[9].rotation_.x = -4 * PI / 180;
	worldTransform_[9].parent_ = &worldTransform_[0];
	worldTransform_[9].Initialize();

	worldTransform_[10].scale_ = Vector3(37.0f, 37.0f, 37.0f);
	worldTransform_[10].translation_ = { 0.0f,-7.0f,4.0f };
	worldTransform_[10].rotation_.x = -4 * PI / 180;
	worldTransform_[10].parent_ = &worldTransform_[0];
	worldTransform_[10].Initialize();

	worldTransform_[11].scale_ = Vector3(42.0f, 42.0f, 42.0f);
	worldTransform_[11].translation_ = { 0.0f,-12.5f,4.5f }; 
	worldTransform_[11].rotation_.x = -5 * PI / 180;
	worldTransform_[11].parent_ = &worldTransform_[0];
	worldTransform_[11].Initialize();
}

void Enemy::ParentUpdate()
{
	ParentSetPosition();

	for (int i = 0; i < modelNum; i++)
	{
		worldTransform_[i].Update();
	}
}

void Enemy::ParentSetPosition()
{
	Vector3 original = worldTransform_[0].translation_;

	//“ª
	worldTransform_[1].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[1].translation_ = Vector3(original.x, original.y + 14.0f, original.z - 4.0f);

	//Š{
	worldTransform_[2].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[2].translation_ = Vector3(original.x, original.y + 14.0f, original.z - 4.0f);

	//Žñ
	worldTransform_[3].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[3].translation_ = Vector3(original.x, original.y + 15.0f, original.z + 2.0f);
	worldTransform_[3].rotation_.x = -90 * PI / 180;

	worldTransform_[4].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[4].translation_ = Vector3(original.x, original.y + 14.0f, original.z + 4.5f);
	worldTransform_[4].rotation_.x = -50 * PI / 180;

	worldTransform_[5].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[5].translation_ = Vector3(original.x, original.y + 11.5f, original.z + 6.0f);
	worldTransform_[5].rotation_.x = 6 * PI / 180;

	worldTransform_[6].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[6].translation_ = Vector3(original.x, original.y + 8.0f, original.z + 5.0f);
	worldTransform_[6].rotation_.x = 43 * PI / 180;

	worldTransform_[7].scale_ = Vector3(23.0f, 23.0f, 23.0f);
	worldTransform_[7].translation_ = Vector3(original.x, original.y + 5.5f, original.z + 4.0f);
	worldTransform_[7].rotation_.x = 16 * PI / 180;

	worldTransform_[8].scale_ = Vector3(26.0f, 26.0f, 26.0f);
	worldTransform_[8].translation_ = Vector3(original.x, original.y + 2.2f, original.z + 3.5f);
	worldTransform_[8].rotation_.x = 4 * PI / 180;

	worldTransform_[9].scale_ = Vector3(31.0f, 31.0f, 31.0f);
	worldTransform_[9].translation_ = Vector3(original.x, original.y - 2.0f , original.z + 3.5f);
	worldTransform_[9].rotation_.x = -4 * PI / 180;

	worldTransform_[10].scale_ = Vector3(37.0f, 37.0f, 37.0f);
	worldTransform_[10].translation_ = Vector3(original.x, original.y - 7.0f, original.z + 4.0f);
	worldTransform_[10].rotation_.x = -4 * PI / 180;

	worldTransform_[11].scale_ = Vector3(42.0f, 42.0f, 42.0f);
	worldTransform_[11].translation_ = Vector3(original.x, original.y - 12.5f, original.z + 4.5f);
	worldTransform_[11].rotation_.x = -5 * PI / 180;
}



