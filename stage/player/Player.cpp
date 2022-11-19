#include "Player.h"
using namespace MathUtility;

Player* Player::GetInstance()
{
	static Player* player = new Player;
	return player;
}

void Player::Initialize(ViewProjection* viewProjection)
{
	debugText_ = DebugText::GetInstance();
	model_ = Model::Create();
	modelKnight[0] = Model::Create();
	modelKnight[1] = Model::CreateFromOBJ("Knight_head");
	modelKnight[2] = Model::CreateFromOBJ("Knight_chest");
	modelKnight[3] = Model::CreateFromOBJ("Knight_handLeft");
	modelKnight[4] = Model::CreateFromOBJ("Knight_handRight");
	modelKnight[5] = Model::CreateFromOBJ("Knight_footLeft");
	modelKnight[6] = Model::CreateFromOBJ("Knight_footRight");
	input_ = Input::GetInstance();
	worldTransform_[0].Initialize();
	ParentInitialize();
	worldTransform_[0].translation_ = { -POLE_RAD,2.0f,-POLE_RAD };
	direction_ = Front;
	viewProjection_ = viewProjection;
}

Vector3 GetCameraPos(Direction direction, float cameraDistance)
{
	float angle = 0;

	switch (direction)
	{
	case Right:	angle = 3.0f * PI / 2.0f;	break;
	case Back:	angle = -PI;				break;
	case Left:	angle = PI / 2.0f;			break;
	}

	return Vector3(0, 0, -cameraDistance) * Matrix4RotationY(angle);
}

void Player::Move()
{
	float horizontalSpd = (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT)) * 0.5f;

	// 移動
	switch (direction_)
	{
	case Front:
		worldTransform_[0].translation_.x += horizontalSpd;
		break;
	case Right:
		worldTransform_[0].translation_.z += horizontalSpd;
		break;
	case Back:
		worldTransform_[0].translation_.x -= horizontalSpd;
		break;
	case Left:
		worldTransform_[0].translation_.z -= horizontalSpd;
		break;
	}

	// ジャンプ
	if (input_->PushKey(DIK_SPACE))
	{
		jamp_.StartJamp(1.5f, 0.1f, 2.0f);
	}
	jamp_.Update(worldTransform_[0].translation_.y);

	viewProjection_->eye = viewProjection_->target = worldTransform_[0].translation_;
	viewProjection_->target.y += 2.0f;
	if (!isTurn_)
	{
		viewProjection_->eye += GetCameraPos(direction_, CAMERA_DISTANCE);
		larpVec[0] = viewProjection_->eye;

		// 方向転換
		switch (direction_)
		{
		case Front:
			if (Turn(worldTransform_[0].translation_.x, Left, -POLE_RAD)) { break; }
			Turn(worldTransform_[0].translation_.x, Right, POLE_RAD);
			break;
		case Right:
			if(Turn(worldTransform_[0].translation_.z, Front, -POLE_RAD)) { break; };
			Turn(worldTransform_[0].translation_.z, Back, POLE_RAD);
			break;
		case Back:
			if(Turn(worldTransform_[0].translation_.x, Left, -POLE_RAD)) { break; };
			Turn(worldTransform_[0].translation_.x, Right, POLE_RAD);
			break;
		case Left:
			if(Turn(worldTransform_[0].translation_.z, Front, -POLE_RAD)) { break; };
			Turn(worldTransform_[0].translation_.z, Back, POLE_RAD);
			break;
		}
	}

	if (isTurn_)
	{
		larpVec[1] = viewProjection_->eye + GetCameraPos(direction_, CAMERA_DISTANCE);
		float t = (float)++nowFlame / (float)LERP_FLAME;
		viewProjection_->eye = lerp(larpVec[0], larpVec[1], t);

		if (nowFlame >= LERP_FLAME)
		{
			nowFlame = 0;
			isTurn_ = 0;
		}

		if (!x) { x = true; }

		// 方向転換
		switch (direction_)
		{
		case Front:
			if (Turn(worldTransform_[0].translation_.x, Left, -POLE_RAD)) { break; }
			Turn(worldTransform_[0].translation_.x, Right, POLE_RAD);
			break;
		case Right:
			if (Turn(worldTransform_[0].translation_.z, Front, -POLE_RAD)) { break; };
			Turn(worldTransform_[0].translation_.z, Back, POLE_RAD);
			break;
		case Back:
			if (Turn(worldTransform_[0].translation_.x, Left, -POLE_RAD)) { break; };
			Turn(worldTransform_[0].translation_.x, Right, POLE_RAD);
			break;
		case Left:
			if (Turn(worldTransform_[0].translation_.z, Front, -POLE_RAD)) { break; };
			Turn(worldTransform_[0].translation_.z, Back, POLE_RAD);
			break;
		}
	}

	debugText_->SetPos(0, 0);
	debugText_->Printf("%f,%f,%f", larpVec[0].x, larpVec[0].y, larpVec[0].z);
}

bool Player::Turn(float& pos1D, Direction nextDirection, float limitPos)
{
	if (limitPos <= 0) { isTurn_ = pos1D < limitPos; }
	else { isTurn_ = pos1D > limitPos; }
	if (!isTurn_) { return false; }
	pos1D = limitPos;
	nowFlame = 0;
	direction_ = nextDirection;
	return true;
}

void Player::Update()
{
	Move();
	ParentUpdate();
	worldTransform_[0].Update();
}

void Player::Draw()
{
	//modelKnight[0]->Draw(worldTransform_[0], *viewProjection_);
	modelKnight[1]->Draw(worldTransform_[1], *viewProjection_);	//頭
	modelKnight[2]->Draw(worldTransform_[2], *viewProjection_);	//胴
	modelKnight[3]->Draw(worldTransform_[3], *viewProjection_);	//左腕
	modelKnight[4]->Draw(worldTransform_[4], *viewProjection_);	//右腕
	modelKnight[5]->Draw(worldTransform_[5], *viewProjection_);	//左足
	modelKnight[6]->Draw(worldTransform_[6], *viewProjection_);	//右足
}

void Player::OnCollision(Collider* collider)
{

}

void Player::ParentInitialize()
{
	worldTransform_[1].Initialize();
	worldTransform_[2].Initialize();
	worldTransform_[3].Initialize();
	worldTransform_[4].Initialize();
	worldTransform_[5].Initialize();
	worldTransform_[6].Initialize();
}

void Player::ParentUpdate()
{
	ParentSetPosition();
	AttackMotion();
	WalkMotion();
	//各worldTransform
	worldTransform_[1].Update();
	worldTransform_[2].Update();
	worldTransform_[3].Update();
	worldTransform_[4].Update();
	worldTransform_[5].Update();
	worldTransform_[6].Update();
}

void Player::ParentSetPosition()
{
	if (input_->PushKey(DIK_LEFT))//左右の判定
	{
		LorR = 0;
	}
	if (input_->PushKey(DIK_RIGHT))
	{
		LorR = 1;
	}

#pragma region 手前
	if (worldTransform_[0].translation_.z <= -24.5)//手前
	{
		if (LorR == 0)
		{
			Rot = 90;
		}
		else
		{
			Rot = 270;
		}

		worldTransform_[1].rotation_.y = Rot * PI / 180;
		worldTransform_[1].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[1].translation_.y = worldTransform_[0].translation_.y + 3.5f;
		worldTransform_[1].translation_.z = worldTransform_[0].translation_.z;

		//胴
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		if (LorR == 0)//左右で腕に位置が反転するため
		{
			//左腕
			worldTransform_[3].rotation_.y = Rot * PI / 180;
			worldTransform_[3].translation_.x = worldTransform_[0].translation_.x;
			worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[3].translation_.z = worldTransform_[0].translation_.z - 1.4f;

			//右腕
			worldTransform_[4].rotation_.y = Rot * PI / 180;
			worldTransform_[4].translation_.x = worldTransform_[0].translation_.x;
			worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[4].translation_.z = worldTransform_[0].translation_.z + 1.4f;
		}
		else
		{
			//左腕
			worldTransform_[3].rotation_.y = Rot * PI / 180;
			worldTransform_[3].translation_.x = worldTransform_[0].translation_.x;
			worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[3].translation_.z = worldTransform_[0].translation_.z + 1.4f;

			//右腕
			worldTransform_[4].rotation_.y = Rot * PI / 180;
			worldTransform_[4].translation_.x = worldTransform_[0].translation_.x;
			worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[4].translation_.z = worldTransform_[0].translation_.z - 1.4f;
		}

		//左足
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z - 0.6f;

		//右足
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z + 0.6f;
	}
#pragma endregion

#pragma region 奥
	else if (worldTransform_[0].translation_.z >= 24.5)//手前
	{
		if (LorR == 1)
		{
			Rot = 90;
		}
		else
		{
			Rot = 270;
		}
		worldTransform_[1].rotation_.y = Rot * PI / 180;
		worldTransform_[1].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[1].translation_.y = worldTransform_[0].translation_.y + 3.5f;
		worldTransform_[1].translation_.z = worldTransform_[0].translation_.z;

		//胴
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		if (LorR == 1)//左右で腕に位置が反転するため
		{
			//左腕
			worldTransform_[3].rotation_.y = Rot * PI / 180;
			worldTransform_[3].translation_.x = worldTransform_[0].translation_.x;
			worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[3].translation_.z = worldTransform_[0].translation_.z - 1.4f;

			//右腕
			worldTransform_[4].rotation_.y = Rot * PI / 180;
			worldTransform_[4].translation_.x = worldTransform_[0].translation_.x;
			worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[4].translation_.z = worldTransform_[0].translation_.z + 1.4f;
		}
		else
		{
			//左腕
			worldTransform_[3].rotation_.y = Rot * PI / 180;
			worldTransform_[3].translation_.x = worldTransform_[0].translation_.x;
			worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[3].translation_.z = worldTransform_[0].translation_.z + 1.4f;

			//右腕
			worldTransform_[4].rotation_.y = Rot * PI / 180;
			worldTransform_[4].translation_.x = worldTransform_[0].translation_.x;
			worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[4].translation_.z = worldTransform_[0].translation_.z - 1.4f;
		}

		//左足
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z - 0.6f;

		//右足
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z + 0.6f;
	}
#pragma endregion

#pragma region 左
	else if (worldTransform_[0].translation_.x <= -24.5f)
	{
		if (LorR == 1)
		{
			Rot = 0;
		}
		else
		{
			Rot = 180;
		}

		//頭
		worldTransform_[1].rotation_.y = Rot * PI / 180;
		worldTransform_[1].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[1].translation_.y = worldTransform_[0].translation_.y + 3.5f;
		worldTransform_[1].translation_.z = worldTransform_[0].translation_.z;

		//胴
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		if (LorR == 0)//左右で腕に位置が反転するため
		{
			//左腕
			worldTransform_[3].rotation_.y = Rot * PI / 180;
			worldTransform_[3].translation_.x = worldTransform_[0].translation_.x - 1.4f;
			worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[3].translation_.z = worldTransform_[0].translation_.z;

			//右腕
			worldTransform_[4].rotation_.y = Rot * PI / 180;
			worldTransform_[4].translation_.x = worldTransform_[0].translation_.x + 1.4f;
			worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[4].translation_.z = worldTransform_[0].translation_.z;
		}
		else
		{
			//左腕
			worldTransform_[3].rotation_.y = Rot * PI / 180;
			worldTransform_[3].translation_.x = worldTransform_[0].translation_.x + 1.4f;
			worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[3].translation_.z = worldTransform_[0].translation_.z;

			//右腕
			worldTransform_[4].rotation_.y = Rot * PI / 180;
			worldTransform_[4].translation_.x = worldTransform_[0].translation_.x - 1.4f;
			worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[4].translation_.z = worldTransform_[0].translation_.z;
		}

		

		//左足
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x + 0.6f;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z;

		//右足
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x - 0.6f;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z;
	}
#pragma endregion

#pragma region 右
	else if (worldTransform_[0].translation_.x >= 24.5f)
	{
		if (LorR == 0)
		{
			Rot = 0;
		}
		else
		{
			Rot = 180;
		}
		//頭
		worldTransform_[1].rotation_.y = Rot * PI / 180;
		worldTransform_[1].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[1].translation_.y = worldTransform_[0].translation_.y + 3.5f;
		worldTransform_[1].translation_.z = worldTransform_[0].translation_.z;

		//胴
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		if (LorR == 1)//左右で腕に位置が反転するため
		{
			//左腕
			worldTransform_[3].rotation_.y = Rot * PI / 180;
			worldTransform_[3].translation_.x = worldTransform_[0].translation_.x - 1.4f;
			worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[3].translation_.z = worldTransform_[0].translation_.z;

			//右腕
			worldTransform_[4].rotation_.y = Rot * PI / 180;
			worldTransform_[4].translation_.x = worldTransform_[0].translation_.x + 1.4f;
			worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[4].translation_.z = worldTransform_[0].translation_.z;
		}
		else
		{
			//左腕
			worldTransform_[3].rotation_.y = Rot * PI / 180;
			worldTransform_[3].translation_.x = worldTransform_[0].translation_.x + 1.4f;
			worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[3].translation_.z = worldTransform_[0].translation_.z;

			//右腕
			worldTransform_[4].rotation_.y = Rot * PI / 180;
			worldTransform_[4].translation_.x = worldTransform_[0].translation_.x - 1.4f;
			worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 1.7f;
			worldTransform_[4].translation_.z = worldTransform_[0].translation_.z;
		}

		//左足
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x + 0.6f;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z;

		//右足
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x - 0.6f;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z;
	}
#pragma endregion
	
}

void Player::WalkMotion()
{
	
	float walkTIME = 10;
	if (input_->PushKey(DIK_LEFT) || input_->PushKey(DIK_RIGHT))
	{
		if(walkFlag == true)
		{
			walkTimer++;
			walkPos += 0.1;
			if(walkTimer >= walkTIME)
			{
				walkTimer = 0.0f;
				walkFlag = false;
			}
		}
		if (walkFlag == false)
		{
			walkTimer++;
			walkPos -= 0.1;
			if (walkTimer >= walkTIME)
			{
				walkTimer = 0.0f;
				walkFlag = true;
			}
		}		
	}
	else// このままだと止まった時に手足の位置がずれているので直す
	{
		walkPos = 0.0f;
	}


	//モーションを反映
	if (worldTransform_[0].translation_.z >= 24.5f || worldTransform_[0].translation_.z <= -24.5f)
	{
		if(isAttack == false)// 攻撃モーションと重なってしまうため
		{
			worldTransform_[3].rotation_.x = walkPos * 10 * PI / 180;
			worldTransform_[4].rotation_.x = walkPos * 10 * PI / 180;
		}
		
		worldTransform_[5].translation_.x += walkPos;
		worldTransform_[6].translation_.x -= walkPos;
	}
	if (worldTransform_[0].translation_.x >= 24.5f || worldTransform_[0].translation_.x <= -24.5f)
	{
		if (isAttack == false)// 攻撃モーションと重なってしまうため
		{
			worldTransform_[3].rotation_.x = walkPos * 10 * PI / 180;
			worldTransform_[4].rotation_.x = walkPos * 10 * PI / 180;
		}
		worldTransform_[5].translation_.z += walkPos;
		worldTransform_[6].translation_.z -= walkPos;
	}
}

void Player::AttackMotion()
{
	if(isAttack == false)
	{
		if (input_->TriggerKey(DIK_A))
		{
			isAttack = true;
			isUp = true;
		}
	}
	

	if(isAttack == true)
	{
		if(isUp == true)//振り上げる
		{
			ATrot += 20.0f;

			
			if (ATrot == 180)//真上まで右手を上げたら
			{
				//ATrot = 0.0f;
				isUp = false;
			}
		}

		if(isUp == false)//振り下げる
		{
			ATrot -= 30.0f;
			
			if(ATrot == 0.0f)
			{
				isAttack = false;
			}
		}
	}

	worldTransform_[4].rotation_.x = ATrot * PI / 180;
}