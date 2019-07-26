#include "ChengCollisionManager.h"
#include "ChengRigidbody.h"
#include "AudioManager.h"
#include "ScriptComponent.h"
#include "WorldValues.h"
ChengCollisionManager::ChengCollisionManager()
{
}

ChengCollisionManager::~ChengCollisionManager()
{
}
ChengRigidbody::ePhysicsTypes ChengCollisionManager::CheckCollision(GameObject* go1, GameObject* go2)
{
	// go1 is always ball
	switch (go2->GetComponent<ChengRigidbody>()->GetType())
	{
	case ChengRigidbody::BALL:
	{
		Vector3 dis = (go2->GetComponent<TransformComponent>()->GetPosition() - go1->GetComponent<TransformComponent>()->GetPosition());
		float combRadius = go2->GetComponent<TransformComponent>()->GetScale().x + go2->GetComponent<TransformComponent>()->GetScale().x;
		Vector3 u = go1->GetComponent<ChengRigidbody>()->GetVel() - go2->GetComponent<ChengRigidbody>()->GetVel();
		if (dis.Length() < combRadius && u.Dot(dis) > 0.0f)
		{
			//CHENG_LOG("ball-ball");
			return ChengRigidbody::BALL;
		}
	}
	break;
	case ChengRigidbody::PILLAR:
	{
		Vector3 pos1 = go1->GetComponent<TransformComponent>()->GetPosition();
		Vector3 pos2 = go2->GetComponent<TransformComponent>()->GetPosition();
		Vector3 scale2 = go2->GetComponent<TransformComponent>()->GetScale();
		Vector3 tempPos2 = pos2;
		tempPos2.y = pos1.y;
		Vector3 dis = (tempPos2 - pos1);
		float combRadius = go2->GetComponent<TransformComponent>()->GetScale().x + go1->GetComponent<TransformComponent>()->GetScale().x;
		Vector3 u = go1->GetComponent<ChengRigidbody>()->GetVel();
		if (dis.Length() < combRadius && u.Dot(dis) > 0.0f)
		{
			if (pos1.y < pos2.y + scale2.y)
			{
				if (pos1.y >= pos2.y)
				{
					//CHENG_LOG("ball-pillar");
					return ChengRigidbody::PILLAR;
				}
			}
		}
	}
	break;
	case ChengRigidbody::BOX:
	{
		//--------------------------------------------------------------------------------
		ChengRigidbody* rigid1 = go1->GetComponent<ChengRigidbody>();
		ChengRigidbody* rigid2 = go2->GetComponent<ChengRigidbody>();

		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		//--------------------------------------------------------------------------------
		//Vector3 N = Vector3(,0,)
		Mtx44 rot;

		rot.SetToRotation(90, 1, 0, 0);
		Vector3 N = { 0,1,0 };
		//--------------------------------------------------------------------------------
		Vector3 w0minusb1 = trans2->GetPosition() - trans1->GetPosition();
		Vector3 pDir = N;
		//--------------------------------------------------------------------------------
		if (w0minusb1.Dot(N) < 0)
			N = -N;

		if (rigid1->GetVel().Dot(N) > 0)
		{
			Vector3 NP = { -N.z,N.y, N.x };

			Vector3 wallScale = trans2->GetScale();
			// Shrink wall size to give priority to lower colls
			const float fOffset = 1.f;
			wallScale.x += fOffset;
			wallScale.y += fOffset;
			wallScale.z += fOffset;
			// x and z flipped for perpen coll
			float width = wallScale.x;
			float height = wallScale.y;
			float depth = wallScale.y;
			if (w0minusb1.Dot(N) < trans1->GetScale().x + width * 0.5f
				&& Math::FAbs(w0minusb1.Dot(NP)) < trans1->GetScale().x + depth * 0.5f
				&& Math::FAbs(w0minusb1.Dot(NP.Cross(N))) < trans1->GetScale().x + height * 0.5f)
			{
				//CHENG_LOG("ball - cube");
				return ChengRigidbody::SQUARE;
			}

			//================================================================================
		}
	}
	// DO NOT BREAK, FALL THROUGH TO ALLOW PERPEN WALL COLL
	case ChengRigidbody::SQUARE:
	{
		//--------------------------------------------------------------------------------
		ChengRigidbody* rigid1 = go1->GetComponent<ChengRigidbody>();
		ChengRigidbody* rigid2 = go2->GetComponent<ChengRigidbody>();

		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		//--------------------------------------------------------------------------------
		//Vector3 N = Vector3(,0,)
		Mtx44 rot;

		rot.SetToRotation(trans2->GetDegrees() + 90, 0, 1, 0);
		Vector3 N = rot * Vector3(1, 0, 0);
		//--------------------------------------------------------------------------------
		Vector3 w0minusb1 = trans2->GetPosition() - trans1->GetPosition();
		Vector3 pDir = N;
		//--------------------------------------------------------------------------------
		if (w0minusb1.Dot(N) < 0)
			N = -N;
		Vector3 NP = { -N.z,N.y, N.x };

		if (rigid1->GetVel().Dot(N) > 0)
		{
			Vector3 wallScale = trans2->GetScale();
			// x and z flipped for perpen coll
			float fTemp = wallScale.x;
			wallScale.x = wallScale.z * 1.1f;
			wallScale.z = fTemp * 0.9f;
			if (w0minusb1.Dot(N) < trans1->GetScale().x + wallScale.x * 0.5f
				&& Math::FAbs(w0minusb1.Dot(NP)) < trans1->GetScale().x + wallScale.z * 0.5f
				&& Math::FAbs(w0minusb1.Dot(NP.Cross(N))) < trans1->GetScale().x + wallScale.y * 0.5f)
			{
				//CHENG_LOG("ball - square");
				// Resolve
				// project wall to ball
				float radius = trans1->GetScale().x;
				Vector3 walltoball = trans1->GetPosition() - trans2->GetPosition();
				walltoball.y = 0;
				Vector3 radiusOffset = walltoball.Normalized() * radius;
				//walltoball += radiusOffset;
				float projDepth = walltoball.Dot(-N) / walltoball.Length()*walltoball.Length();
				float depth = (wallScale.x / 2 + radius) - projDepth;
				trans1->Translate(depth * -N);
				//trans1->Translate({ 0,0,-0.2f });
				return ChengRigidbody::SQUARE;
			}
		}

		//================================================================================
	}
	// DO NOT BREAK, FALL THROUGH TO ALLOW PERPEN WALL COLL
	case ChengRigidbody::WALL: // check coll
	{
		//--------------------------------------------------------------------------------
		ChengRigidbody* rigid1 = go1->GetComponent<ChengRigidbody>();
		ChengRigidbody* rigid2 = go2->GetComponent<ChengRigidbody>();

		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		//--------------------------------------------------------------------------------
		//Vector3 N = Vector3(,0,)
		Vector3 N = { 1,0,0 };
		if (trans2->GetDegrees() != 0)
		{
			Mtx44 rot;
			rot.SetToRotation(trans2->GetDegrees(), trans2->GetRotation().x, trans2->GetRotation().y, trans2->GetRotation().z);
			N = rot * Vector3(1, 0, 0);
		}
		//--------------------------------------------------------------------------------
		Vector3 w0minusb1 = trans2->GetPosition() - trans1->GetPosition();
		Vector3 pDir = N;
		//--------------------------------------------------------------------------------
		if (w0minusb1.Dot(N) < 0)
			N = -N;
		Vector3 NP = { N.z,N.y, -N.x };

		if (rigid1->GetVel().Dot(N) > 0)
		{
			Vector3 wallScale = trans2->GetScale();

			if (w0minusb1.Dot(N) <= trans1->GetScale().x + wallScale.x * 0.5f
				&& Math::FAbs(w0minusb1.Dot(NP)) <= trans1->GetScale().x + wallScale.z * 0.5f
				&& Math::FAbs(w0minusb1.Dot(NP.Cross(N))) < trans1->GetScale().x + wallScale.y * 0.5f)
			{
				//CHENG_LOG("ball - wall");
				// Resolve
				// project wall to ball
				float radius = trans1->GetScale().x;
				Vector3 walltoball = trans1->GetPosition() - trans2->GetPosition();
				walltoball.y = 0;
				Vector3 radiusOffset = walltoball.Normalized() * radius;
				//walltoball += radiusOffset;
				float projDepth = walltoball.Dot(-N) / walltoball.Length()*walltoball.Length();
				float depth = (wallScale.x / 2 + radius) - projDepth;
				trans1->Translate(depth * -N);
				return ChengRigidbody::WALL;
			}
		}
	}
	break;
	case ChengRigidbody::PADDLE:
	{
		//--------------------------------------------------------------------------------
		ChengRigidbody* rigid1 = go1->GetComponent<ChengRigidbody>();
		ChengRigidbody* rigid2 = go2->GetComponent<ChengRigidbody>();

		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		Vector3 pos1 = trans1->GetPosition();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		Vector3 pos2 = trans2->GetPosition();
		float fDist = (pos1 - pos2).Length();
		//--------------------------------------------------------------------------------
		//Vector3 N = Vector3(,0,)
		Mtx44 rot;
		Vector3 N = { 1,0,0 };
		if (trans2->GetDegrees() != 0)
		{
			rot.SetToRotation(trans2->GetDegrees(), trans2->GetRotation().x, trans2->GetRotation().y, trans2->GetRotation().z);
			N = rot * Vector3(1, 0, 0);
		}
		Vector3 NP = { -N.z,N.y, N.x };
		pos2 -= NP * (trans2->GetScale().z / 2);
		//--------------------------------------------------------------------------------
		Vector3 w0minusb1 = pos2 - trans1->GetPosition();
		Vector3 pDir = N;

		float fCircum = 2 * 3.1425f * (fDist);
		Vector3 avel = rigid2->GetAVel();
		float fSpeed = avel.y / 360 * fCircum;
		//fSpeed = fabs(fSpeed);
		Vector3 vel = rigid1->GetVel();
		Vector3 relVel = rigid1->GetVel() + N * fSpeed;

		//--------------------------------------------------------------------------------
		if (w0minusb1.Dot(N) < 0)
			N = -N;

		if (relVel.Dot(N) > 0)
		{
			Vector3 wallScale = trans2->GetScale();

			if (w0minusb1.Dot(N) <= trans1->GetScale().x + wallScale.x * 0.5f
				&& Math::FAbs(w0minusb1.Dot(NP)) <= trans1->GetScale().x + wallScale.z * 0.5f
				&& Math::FAbs(w0minusb1.Dot(NP.Cross(N))) <= trans1->GetScale().x + wallScale.y * 0.5f)
			{
				// Resolve
				// project wall to ball
				float radius = trans1->GetScale().x;
				Vector3 walltoball = trans1->GetPosition() - trans2->GetPosition();
				walltoball.y = 0;
				Vector3 radiusOffset = walltoball.Normalized() * radius;
				//walltoball += radiusOffset;
				float projDepth = walltoball.Dot(-N) / walltoball.Length()*walltoball.Length();
				float depth = (wallScale.x / 2 + radius) - projDepth;
				trans1->Translate(depth * -N);
				return ChengRigidbody::PADDLE;
			}
		}
	}
	break;
	default:
		break;
	}
	return ChengRigidbody::NONE;
}
void ChengCollisionManager::CollisionResponse(GameObject* go1, GameObject* go2, ChengRigidbody::ePhysicsTypes e)
{
	// go1 is always ball
	switch (e)
	{
	case ChengRigidbody::BALL:
	{
		//float p1 = go1->GetComponent<ChengRigidbody>()->GetMass() * go1->GetComponent<ChengRigidbody>()->GetVel().x;
		//float p2 = go2->GetComponent<ChengRigidbody>()->GetMass() * go2->GetComponent<ChengRigidbody>()->GetVel().x;
		// Response--------------------------------------------------------------------------------
		float m1 = go1->GetComponent<ChengRigidbody>()->GetMass();
		float m2 = go2->GetComponent<ChengRigidbody>()->GetMass();
		Vector3 u1 = go1->GetComponent<ChengRigidbody>()->GetVel();
		Vector3 u2 = go2->GetComponent<ChengRigidbody>()->GetVel();
		Vector3 pos1 = go1->GetComponent<TransformComponent>()->GetPosition();
		Vector3 pos2 = go2->GetComponent<TransformComponent>()->GetPosition();

		Vector3 newVel1 = u1 - 2 * m2 / (m1 + m2) * (((u1 - u2).Dot(pos1 - pos2)) / (pos1 - pos2).LengthSquared()) * (pos1 - pos2);
		Vector3 newVel2 = u2 - 2 * m1 / (m1 + m2) * (((u2 - u1).Dot(pos2 - pos1)) / (pos2 - pos1).LengthSquared()) * (pos2 - pos1);

		go1->GetComponent<ChengRigidbody>()->SetVel(newVel1);
		go2->GetComponent<ChengRigidbody>()->SetVel(newVel2);
	}
	break;
	case ChengRigidbody::PILLAR:
	{
		//float p1 = go1->GetComponent<ChengRigidbody>()->GetMass() * go1->GetComponent<ChengRigidbody>()->GetVel().x;
		//float p2 = go2->GetComponent<ChengRigidbody>()->GetMass() * go2->GetComponent<ChengRigidbody>()->GetVel().x;
		// Response--------------------------------------------------------------------------------
		// change to wall coll base on pos diff as normal
		float m1 = go1->GetComponent<ChengRigidbody>()->GetMass();
		float m2 = go1->GetComponent<ChengRigidbody>()->GetMass();
		Vector3 u1 = go1->GetComponent<ChengRigidbody>()->GetVel();
		Vector3 u2 = -go1->GetComponent<ChengRigidbody>()->GetVel();
		Vector3 pos1 = go1->GetComponent<TransformComponent>()->GetPosition();
		Vector3 pos2 = go2->GetComponent<TransformComponent>()->GetPosition();
		pos2.y = pos1.y;

		Vector3 newVel1 = u1 - 2 * m2 / (m1 + m2) * (((u1 - u2).Dot(pos1 - pos2)) / (pos1 - pos2).LengthSquared()) * (pos1 - pos2);
		//Vector3 newVel2 = u2 - 2 * m1 / (m1 + m2) * (((u2 - u1).Dot(pos2 - pos1)) / (pos2 - pos1).LengthSquared()) * (pos2 - pos1);
		go1->GetComponent<ChengRigidbody>()->SetVel(newVel1);
		//go2->GetComponent<ChengRigidbody>()->SetVel(newVel2);
	}
	break;
	case ChengRigidbody::BOX:
	{
		// DEPRECIATED 3D COLLDIER
		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		ChengRigidbody* rigid1 = go1->GetComponent<ChengRigidbody>();
		Mtx44 rot;
		rot.SetToRotation(trans2->GetDegrees() + 90, 0, 1, 0);

		Vector3 N = { 0,1,0 };
		Vector3 v = rigid1->GetVel() - (2 * rigid1->GetVel().Dot(N)) *N;
		v *= rigid1->GetMat()->GetBounce();
		go1->GetComponent<ChengRigidbody>()->SetVel(v);
	}
	break;
	case ChengRigidbody::SQUARE:
	{
		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		ChengRigidbody* rigid1 = go1->GetComponent<ChengRigidbody>();
		ChengRigidbody* rigid2 = go2->GetComponent<ChengRigidbody>();
		Mtx44 rot;
		rot.SetToRotation(trans2->GetDegrees() + 90, 0, 1, 0);

		Vector3 N = rot * Vector3(1, 0, 0);
		Vector3 v = rigid1->GetVel() - (2 * rigid1->GetVel().Dot(N)) *N;
		if (v.Length() > 20)
		{
			if (WorldValues::TimeScale > 0)
				v *= rigid1->GetMat()->GetBounce() * rigid2->GetMat()->GetBounce();
			else
				v *= 1 / (rigid1->GetMat()->GetBounce() * rigid2->GetMat()->GetBounce());
			//v *= rigid1->GetMat()->GetBounce() * rigid2->GetMat()->GetBounce();
		}
		go1->GetComponent<ChengRigidbody>()->SetVel(v);

		// Angular
		if ((trans2->GetPosition() - trans1->GetPosition()).Dot(N) < 0)
		{
			N = -N;
		}
		Vector3 NP = { -N.z,N.y, N.x };
		// proj vel on NP
		Vector3 proj = (v.Dot(NP)) / (v.LengthSquared()) * NP;
		// Angular
		Vector3 torque = (proj * 1).Cross(N * trans1->GetScale().x);
		rigid1->SetTorque(torque * 10000000);
	}
	break;
	case ChengRigidbody::WALL:
	{
		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		ChengRigidbody* rigid1 = go1->GetComponent<ChengRigidbody>();
		ChengRigidbody* rigid2 = go2->GetComponent<ChengRigidbody>();
		Vector3 N = { 1,0,0 };
		if (trans2->GetDegrees() != 0)
		{
			Mtx44 rot;
			rot.SetToRotation(trans2->GetDegrees(), trans2->GetRotation().x, trans2->GetRotation().y, trans2->GetRotation().z);
			N = rot * Vector3(1, 0, 0);
		}

		Vector3 v = rigid1->GetVel() - (2 * rigid1->GetVel().Dot(N)) * N;

		// set min vel due to spam collision while rolling
		if (v.Length() > 20)
		{
			if (WorldValues::TimeScale > 0)
				v *= rigid1->GetMat()->GetBounce() * rigid2->GetMat()->GetBounce();
			else
				v *= 1 / (rigid1->GetMat()->GetBounce() * rigid2->GetMat()->GetBounce());
			// v *= rigid1->GetMat()->GetBounce() * rigid2->GetMat()->GetBounce();
		}

		go1->GetComponent<ChengRigidbody>()->SetVel(v);

		// Angular
		if ((trans2->GetPosition() - trans1->GetPosition()).Dot(N) < 0)
		{
			N = -N;
		}
		Vector3 NP = { -N.z,N.y, N.x };
		// proj vel on NP
		Vector3 proj = (v.Dot(NP)) / (v.LengthSquared()) * NP;
		// Angular
		Vector3 torque = (proj * 1).Cross(N * trans1->GetScale().x);
		rigid1->SetTorque(torque * 10000000);
	}
	break;
	case ChengRigidbody::PADDLE:
	{
		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		//trans1->SetPosition()
		float fDist = (trans1->GetPosition() - trans2->GetPosition()).Length();
		ChengRigidbody* rigid1 = go1->GetComponent<ChengRigidbody>();
		ChengRigidbody* rigid2 = go2->GetComponent<ChengRigidbody>();
		Mtx44 rot;
		rot.SetToRotation(trans2->GetDegrees(), trans2->GetRotation().x, trans2->GetRotation().y, trans2->GetRotation().z);
		Vector3 N = rot * Vector3(1, 0, 0);
		float fCircum = 2 * 3.1425f * (fDist);
		Vector3 avel = rigid2->GetAVel();
		float fSpeed = avel.y / 360 * fCircum;
		if ((trans2->GetPosition() - trans1->GetPosition()).Dot(N) < 0)
		{
			fSpeed = -(fSpeed);
			N = -N;
		}

		Vector3 vel = rigid1->GetVel();
		Vector3 relVel = rigid1->GetVel() + N * fSpeed;
		Vector3 v = relVel - (2 * relVel.Dot(N)) * N;
		go1->GetComponent<ChengRigidbody>()->SetVel(v);

		// Angular
		if ((trans2->GetPosition() - trans1->GetPosition()).Dot(N) < 0)
		{
			N = -N;
		}
		Vector3 NP = { -N.z,N.y, N.x };
		// proj vel on NP
		Vector3 proj = (v.Dot(NP)) / (v.LengthSquared()) * NP;
		// Angular
		Vector3 torque = (proj * 1).Cross(N * trans1->GetScale().x);
		rigid1->SetTorque(torque * 100000);
	}
	break;
	default:
		break;
	}
}
void ChengCollisionManager::Update(GameObjectManager* GOM)
{
	std::map<std::string, LayerData*>::iterator it;
	// TODO multilayer collision?
	for (it = GOM->GetLayerList()->begin(); it != GOM->GetLayerList()->end(); it++)
	{
		// it->first == key
		// it->second == value
		// TODO Child coll
		std::vector<GameObject*>* GOList = it->second->GetGOList();
		for (unsigned i = 0; i < GOList->size(); ++i)
		{
			GameObject* go1 = GOList->at(i);
			if (!go1->IsActive())
				continue;
			if (go1->GetComponent<ChengRigidbody>(true))
				CheckCollision(go1, GOList, i);
			for (unsigned j = 0; j < go1->GetChildList()->size(); ++j)
			{
				GameObject* goChild = go1->GetChildList()->at(j);
				if (!goChild->IsActive())
					continue;
				if (goChild->GetComponent<ChengRigidbody>(true))
					CheckCollision(goChild, GOList, i);
			}
		}
	}
}
void ChengCollisionManager::CheckCollision(GameObject* go1, std::vector<GameObject*>* GOList, int i)
{
	for (unsigned j = i + 1; j < GOList->size(); ++j)
	{
		GameObject* go2 = GOList->at(j);
		if (!go2->IsActive())
			continue;
		if (!go2->GetComponent<ChengRigidbody>(true))
			continue;
		GameObject* goA = go1;
		GameObject* goB = go2;
		// force go1 to be a ball
		if (go1->GetComponent<ChengRigidbody>()->GetType() != ChengRigidbody::BALL)
		{
			// swap ball to front
			if (go2->GetComponent<ChengRigidbody>()->GetType() == ChengRigidbody::BALL)
			{
				goA = go2;
				goB = go1;
			}
			// ignore !ball !ball
			else
			{
				continue;
			}
		}
		ChengRigidbody::ePhysicsTypes eCollideType = CheckCollision(goA, goB);
		if (eCollideType != ChengRigidbody::NONE)
		{
			CollisionResponse(goA, goB, eCollideType);
			ScriptComponent * Script1 = goA->GetComponent<ScriptComponent>(true);
			if (Script1)
				Script1->Collide(goB);
			ScriptComponent * Script2 = goB->GetComponent<ScriptComponent>(true);
			if (Script2)
				Script2->Collide(goA);
		}
	}
}