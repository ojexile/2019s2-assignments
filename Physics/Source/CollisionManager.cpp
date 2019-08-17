#include "CollisionManager.h"
#include "Rigidbody.h"
#include "AudioManager.h"
#include "ScriptComponent.h"
#include "WorldValues.h"
#include "ChunkCollider.h"
#include "PlayerScript.h"
CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

Vector3 Truncate(Vector3 input)
{
	return Vector3((int)input.x, (int)input.y, (int)input.z) + Vector3(0.5, 0.5, 0.5);
}
#define NEW_COLLISION
Rigidbody::ePhysicsTypes CollisionManager::CheckCollision(GameObject* go1, GameObject* go2)
{
	// go1 is always ball
	switch (go2->GetComponent<Rigidbody>()->GetType())
	{
	case Rigidbody::BALL:
	{
		Vector3 dis = (go2->GetComponent<TransformComponent>()->GetPosition() - go1->GetComponent<TransformComponent>()->GetPosition());
		float combRadius = go2->GetComponent<TransformComponent>()->GetScale().x + go2->GetComponent<TransformComponent>()->GetScale().x;
		Vector3 u = go1->GetComponent<Rigidbody>()->GetVel() - go2->GetComponent<Rigidbody>()->GetVel();
		if (dis.Length() < combRadius && u.Dot(dis) > 0.0f)
		{
			//CHENG_LOG("ball-ball");
			return Rigidbody::BALL;
		}
	}
	break;
	case Rigidbody::PILLAR:
	{
		Vector3 pos1 = go1->GetComponent<TransformComponent>()->GetPosition();
		Vector3 pos2 = go2->GetComponent<TransformComponent>()->GetPosition();
		Vector3 scale2 = go2->GetComponent<TransformComponent>()->GetScale();
		Vector3 tempPos2 = pos2;
		tempPos2.y = pos1.y;
		Vector3 dis = (tempPos2 - pos1);
		float combRadius = go2->GetComponent<TransformComponent>()->GetScale().x + go1->GetComponent<TransformComponent>()->GetScale().x;
		Vector3 u = go1->GetComponent<Rigidbody>()->GetVel() - go2->GetComponent<Rigidbody>()->GetVel();
		if (dis.Length() < combRadius && u.Dot(dis) > 0.0f)
		{
			if (pos1.y < pos2.y + scale2.y)
			{
				if (pos1.y >= pos2.y)
				{
					//CHENG_LOG("ball-pillar");
					return Rigidbody::PILLAR;
				}
			}
		}
	}
	break;
	case Rigidbody::BOX:
	{
		//--------------------------------------------------------------------------------
		Rigidbody* rigid1 = go1->GetComponent<Rigidbody>();
		Rigidbody* rigid2 = go2->GetComponent<Rigidbody>();

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
				return Rigidbody::SQUARE;
			}

			//================================================================================
		}
	}
	// DO NOT BREAK, FALL THROUGH TO ALLOW PERPEN WALL COLL
	case Rigidbody::SQUARE:
	{
		//--------------------------------------------------------------------------------
		Rigidbody* rigid1 = go1->GetComponent<Rigidbody>();
		Rigidbody* rigid2 = go2->GetComponent<Rigidbody>();

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
				float projDepth = walltoball.Dot(-N) / walltoball.Length() * walltoball.Length();
				float depth = (wallScale.x / 2 + radius) - projDepth;
				trans1->Translate(depth * -N);
				//trans1->Translate({ 0,0,-0.2f });
				return Rigidbody::SQUARE;
			}
		}

		//================================================================================
	}
	// DO NOT BREAK, FALL THROUGH TO ALLOW PERPEN WALL COLL
	case Rigidbody::WALL: // check coll
	{
		//--------------------------------------------------------------------------------
		Rigidbody* rigid1 = go1->GetComponent<Rigidbody>();
		Rigidbody* rigid2 = go2->GetComponent<Rigidbody>();

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
				float projDepth = walltoball.Dot(-N) / walltoball.Length() * walltoball.Length();
				float depth = (wallScale.x / 2 + radius) - projDepth;
				trans1->Translate(depth * -N);
				return Rigidbody::WALL;
			}
		}
	}
	break;
	case Rigidbody::PADDLE:
	{
		//--------------------------------------------------------------------------------
		Rigidbody* rigid1 = go1->GetComponent<Rigidbody>();
		Rigidbody* rigid2 = go2->GetComponent<Rigidbody>();

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
				float projDepth = walltoball.Dot(-N) / walltoball.Length() * walltoball.Length();
				float depth = (wallScale.x / 2 + radius) - projDepth;
				trans1->Translate(depth * -N);
				return Rigidbody::PADDLE;
			}
		}
	}
	break;
	default:
		break;
	}
	return Rigidbody::NONE;
}
void CollisionManager::CollisionResponse(GameObject* go1, GameObject* go2, Rigidbody::ePhysicsTypes e)
{
	// go1 is always ball
	switch (e)
	{
	case Rigidbody::BALL:
	{
		//float p1 = go1->GetComponent<ChengRigidbody>()->GetMass() * go1->GetComponent<ChengRigidbody>()->GetVel().x;
		//float p2 = go2->GetComponent<ChengRigidbody>()->GetMass() * go2->GetComponent<ChengRigidbody>()->GetVel().x;
		// Response--------------------------------------------------------------------------------
		float m1 = go1->GetComponent<Rigidbody>()->GetMass();
		float m2 = go2->GetComponent<Rigidbody>()->GetMass();
		Vector3 u1 = go1->GetComponent<Rigidbody>()->GetVel();
		Vector3 u2 = go2->GetComponent<Rigidbody>()->GetVel();
		Vector3 pos1 = go1->GetComponent<TransformComponent>()->GetPosition();
		Vector3 pos2 = go2->GetComponent<TransformComponent>()->GetPosition();

		Vector3 newVel1 = u1 - 2 * m2 / (m1 + m2) * (((u1 - u2).Dot(pos1 - pos2)) / (pos1 - pos2).LengthSquared()) * (pos1 - pos2);
		Vector3 newVel2 = u2 - 2 * m1 / (m1 + m2) * (((u2 - u1).Dot(pos2 - pos1)) / (pos2 - pos1).LengthSquared()) * (pos2 - pos1);

		go1->GetComponent<Rigidbody>()->SetVel(newVel1);
		go2->GetComponent<Rigidbody>()->SetVel(newVel2);
	}
	break;
	case Rigidbody::PILLAR:
	{
		//float p1 = go1->GetComponent<ChengRigidbody>()->GetMass() * go1->GetComponent<ChengRigidbody>()->GetVel().x;
		//float p2 = go2->GetComponent<ChengRigidbody>()->GetMass() * go2->GetComponent<ChengRigidbody>()->GetVel().x;
		// Response--------------------------------------------------------------------------------
		// change to wall coll base on pos diff as normal
		float m1 = go1->GetComponent<Rigidbody>()->GetMass();
		float m2 = go1->GetComponent<Rigidbody>()->GetMass();
		Vector3 u1 = go1->GetComponent<Rigidbody>()->GetVel();
		Vector3 u2 = -go1->GetComponent<Rigidbody>()->GetVel();
		Vector3 pos1 = go1->GetComponent<TransformComponent>()->GetPosition();
		Vector3 pos2 = go2->GetComponent<TransformComponent>()->GetPosition();
		pos2.y = pos1.y;

		Vector3 newVel1 = u1 - 2 * m2 / (m1 + m2) * (((u1 - u2).Dot(pos1 - pos2)) / (pos1 - pos2).LengthSquared()) * (pos1 - pos2);
		//Vector3 newVel2 = u2 - 2 * m1 / (m1 + m2) * (((u2 - u1).Dot(pos2 - pos1)) / (pos2 - pos1).LengthSquared()) * (pos2 - pos1);
		go1->GetComponent<Rigidbody>()->SetVel(newVel1);
		//go2->GetComponent<ChengRigidbody>()->SetVel(newVel2);
	}
	break;
	case Rigidbody::BOX:
	{
		// DEPRECIATED 3D COLLDIER
		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		Rigidbody* rigid1 = go1->GetComponent<Rigidbody>();
		Mtx44 rot;
		rot.SetToRotation(trans2->GetDegrees() + 90, 0, 1, 0);

		Vector3 N = { 0,1,0 };
		Vector3 v = rigid1->GetVel() - (2 * rigid1->GetVel().Dot(N)) * N;
		v *= rigid1->GetMat().GetBounce();
		go1->GetComponent<Rigidbody>()->SetVel(v);
	}
	break;
	case Rigidbody::SQUARE:
	{
		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		Rigidbody* rigid1 = go1->GetComponent<Rigidbody>();
		Rigidbody* rigid2 = go2->GetComponent<Rigidbody>();
		Mtx44 rot;
		rot.SetToRotation(trans2->GetDegrees() + 90, 0, 1, 0);

		Vector3 N = rot * Vector3(1, 0, 0);
		Vector3 v = rigid1->GetVel() - (2 * rigid1->GetVel().Dot(N)) * N;
		if (v.Length() > 20)
		{
			if (WorldValues::TimeScale > 0)
				v *= rigid1->GetMat().GetBounce() * rigid2->GetMat().GetBounce();
			else
				v *= 1 / (rigid1->GetMat().GetBounce() * rigid2->GetMat().GetBounce());
			//v *= rigid1->GetMat().GetBounce() * rigid2->GetMat().GetBounce();
		}
		go1->GetComponent<Rigidbody>()->SetVel(v);

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
	case Rigidbody::WALL:
	{
		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		Rigidbody* rigid1 = go1->GetComponent<Rigidbody>();
		Rigidbody* rigid2 = go2->GetComponent<Rigidbody>();
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
				v *= rigid1->GetMat().GetBounce() * rigid2->GetMat().GetBounce();
			else
				v *= 1 / (rigid1->GetMat().GetBounce() * rigid2->GetMat().GetBounce());
			// v *= rigid1->GetMat().GetBounce() * rigid2->GetMat().GetBounce();
		}

		go1->GetComponent<Rigidbody>()->SetVel(v);

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
	case Rigidbody::PADDLE:
	{
		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		//trans1->SetPosition()
		float fDist = (trans1->GetPosition() - trans2->GetPosition()).Length();
		Rigidbody* rigid1 = go1->GetComponent<Rigidbody>();
		Rigidbody* rigid2 = go2->GetComponent<Rigidbody>();
		Vector3 N = { 1,0,0 };
		if (trans2->GetDegrees() != 0)
		{
			Mtx44 rot;
			rot.SetToRotation(trans2->GetDegrees(), trans2->GetRotation().x, trans2->GetRotation().y, trans2->GetRotation().z);
			N = rot * Vector3(1, 0, 0);
		}
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
		go1->GetComponent<Rigidbody>()->SetVel(v);

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
void CollisionManager::Update(GameObjectManager* GOM)
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
			if (go1->GetComponent<Rigidbody>(true) && go1->GetComponent<Rigidbody>(true)->IsActive())
			{
				CheckCollision(go1, GOList, i);
				if (go1->GetComponent<ChunkCollider>() == nullptr)
					CheckChunkCollision(go1, GOList);
			}
			for (unsigned j = 0; j < go1->GetChildList()->size(); ++j)
			{
				GameObject* goChild = go1->GetChildList()->at(j);
				if (!goChild->IsActive())
					continue;
				if (goChild->GetComponent<Rigidbody>(true))
					CheckCollision(goChild, GOList, i);
			}
		}
	}
}

Rigidbody::ePhysicsTypes CollisionManager::CheckChunkCollision(GameObject* go1, std::vector<GameObject*>* GOList)
{
	std::vector<GameObject*> chunks;
	float halfPlayerSize = go1->GetComponent<TransformComponent>()->GetScale().x;
	float halfPlayerHeight = go1->GetComponent<TransformComponent>()->GetScale().y;
	float ky = go1->TRANS->GetPosition().y;
	Vector3 vertices[] = { go1->TRANS->GetPosition()  + Vector3(halfPlayerSize, halfPlayerHeight, halfPlayerSize),
					 go1->TRANS->GetPosition() + Vector3(halfPlayerSize, halfPlayerHeight, -halfPlayerSize),
					 go1->TRANS->GetPosition() + Vector3(-halfPlayerSize, halfPlayerHeight, halfPlayerSize),
					 go1->TRANS->GetPosition() + Vector3(-halfPlayerSize, halfPlayerHeight, -halfPlayerSize),
					 go1->TRANS->GetPosition() + Vector3(halfPlayerSize, -halfPlayerHeight, halfPlayerSize),
					 go1->TRANS->GetPosition() + Vector3(halfPlayerSize, -halfPlayerHeight, -halfPlayerSize),
					 go1->TRANS->GetPosition() + Vector3(-halfPlayerSize, -halfPlayerHeight, halfPlayerSize),
					 go1->TRANS->GetPosition() + Vector3(-halfPlayerSize, -halfPlayerHeight, -halfPlayerSize) };
	for (auto it1 = GOList->begin(); it1 != GOList->end(); ++it1)
	{
		GameObject* go2 = *it1;
		Vector3 dist = go2->TRANS->GetPosition() - go1->TRANS->GetPosition();
		if (go2->GetComponent<ChunkCollider>() != nullptr)
		{
			ChunkData* chunkData = go2->GetComponent<ChunkCollider>()->GetChunk();
			if (dist.Length() < chunkData->GetSize().Length())
			{
				for (int i = 0; i < 8; ++i)
				{
					if (go2->GetComponent<ChunkCollider>()->GetChunk()->IsSolid(vertices[i] - go2->GetComponent<TransformComponent>()->GetPosition()))
					{
						chunks.push_back(go2);
						break;
					}
				}
			}
		}
	}
	float shortestMagnitude = 10;
	Vector3 shortestDirection = Vector3(0, 0, 0);
	if(chunks.size() != 0)
	for (int i = 0; i < 27; ++i)
	{
		if (i == 13) continue;
		float forceMagnitudePos = 0;
		Vector3 forceDirection;
		forceDirection.x = (i % 3 == 0 ? -1 : (i % 3 == 1 ? 0 : 1));
		forceDirection.z = ((i % 9) / 3 == 0 ? -1 : ((i % 9) / 3 == 1 ? 0 : 1));
		forceDirection.y = (i / 9 == 0 ? -1 : (i / 9 == 1 ? 0 : 1));
		forceDirection.Normalize();
		for (float increment = 1; increment > 0.000004; increment /= 2)
		{
			while (true)
			{
				bool k = true;
				for (auto it = chunks.begin(); it != chunks.end(); it++)
				{
					ChunkData* cd = (*it)->GetComponent<ChunkCollider>()->GetChunk();
					for (int i = 0; i < 8; ++i)
					{
						Vector3 pos = - (*it)->TRANS->GetPosition() + vertices[i];
						if (cd->IsSolid(pos + forceDirection * (forceMagnitudePos + increment)))
						{
							k = false;
							break;
						}
						if (!k) break;
					}
					if (!k) break;
				}
				if (k) break;
				forceMagnitudePos += increment;
			}
		}
		if (shortestMagnitude > forceMagnitudePos)
		{
			shortestMagnitude = forceMagnitudePos;
			shortestDirection = forceDirection;
		}
	}
	if (shortestDirection.IsZero() || shortestMagnitude <= 0.008) return Rigidbody::ePhysicsTypes::NONE;
	go1->GetComponent<Rigidbody>()->QueueMapForce(shortestDirection * shortestMagnitude * go1->RIGID->GetMass() * 400);
	Vector3 vel = go1->RIGID->GetVel();

	go1->GetComponent<Rigidbody>()->QueueVel(-2 * shortestDirection * (vel.Dot(shortestDirection)));
	if(go1->GetComponent<ScriptComponent>() != nullptr)
		go1->GetComponent<ScriptComponent>()->Collide(GOList->front());
	return Rigidbody::ePhysicsTypes::CHUNK;
}

void CollisionManager::CheckCollision(GameObject* go1, std::vector<GameObject*>* GOList, int i)
{
	for (unsigned j = i + 1; j < GOList->size(); ++j)
	{
		GameObject* go2 = GOList->at(j);
		if (!go2->IsActive())
			continue;
		if (!go2->GetComponent<Rigidbody>(true))
			continue;
		if (!go2->GetComponent<Rigidbody>(true)->IsActive())
			continue;
		GameObject* goA = go1;
		GameObject* goB = go2;
		// force go1 to be a ball
		if (!go1->GetComponent<Rigidbody>(true))
			continue;
		if (!go2->GetComponent<Rigidbody>(true))
			continue;
		if (go1->GetComponent<Rigidbody>()->GetType() != Rigidbody::BALL)
		{
			// swap ball to front
			if (go2->GetComponent<Rigidbody>()->GetType() == Rigidbody::BALL)
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
		Rigidbody::ePhysicsTypes eCollideType = Rigidbody::NONE;
		eCollideType = CheckCollision(goA, goB);
		if (eCollideType != Rigidbody::NONE)
		{
			if(goA->RIGID->GetResponseActive() && goB->RIGID->GetResponseActive())
				CollisionResponse(goA, goB, eCollideType);
			ScriptComponent* Script1 = goA->GetComponent<ScriptComponent>(true);
			if (Script1)
				Script1->Collide(goB);
			ScriptComponent* Script2 = goB->GetComponent<ScriptComponent>(true);
			if (Script2)
				Script2->Collide(goA);
		}
	}
}
