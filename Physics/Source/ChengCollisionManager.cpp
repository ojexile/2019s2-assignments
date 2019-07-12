#include "ChengCollisionManager.h"
#include "ChengRigidbody.h"
ChengCollisionManager::ChengCollisionManager()
{
}

ChengCollisionManager::~ChengCollisionManager()
{
}
ChengRigidbody::ePhysicsTypes ChengCollisionManager::CheckCollision(GameObject* go1, GameObject* go2)
{
	// go1 is always ball
	switch (go2->GetComponent<ChengRigidbody>()->m_eType)
	{
	case ChengRigidbody::BALL:
	{
		Vector3 dis = (go2->GetComponent<TransformComponent>()->GetPosition() - go1->GetComponent<TransformComponent>()->GetPosition());
		float combRadius = go2->GetComponent<TransformComponent>()->GetScale().x + go2->GetComponent<TransformComponent>()->GetScale().x;
		Vector3 u = go1->GetComponent<ChengRigidbody>()->m_vVel - go2->GetComponent<ChengRigidbody>()->m_vVel;
		if (dis.Length() < combRadius && u.Dot(dis) > 0.0f)
		{
			CHENG_LOG("ball-ball");
			return ChengRigidbody::BALL;
		}
	}
	break;
	case ChengRigidbody::PILLAR:
	{
		Vector3 pos1 = go1->GetComponent<TransformComponent>()->GetPosition();
		Vector3 pos2 = go2->GetComponent<TransformComponent>()->GetPosition();
		pos2.y = pos1.y;
		Vector3 dis = (pos2 - pos1);
		float combRadius = go2->GetComponent<TransformComponent>()->GetScale().x / 2 + go1->GetComponent<TransformComponent>()->GetScale().x;
		Vector3 u = go1->GetComponent<ChengRigidbody>()->m_vVel;
		if (dis.Length() < combRadius && u.Dot(dis) > 0.0f)
		{
			CHENG_LOG("ball-pillar");
			return ChengRigidbody::PILLAR;
		}
	}
	break;
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

		if (rigid1->m_vVel.Dot(N) > 0)
		{
			Vector3 NP = N.Cross({ 0,-1,0 });

			Vector3 wallScale = trans2->GetScale();
			// Shrink wall size to give priority to lower colls
			const float fOffset = 1.f;
			wallScale.x -= fOffset;
			wallScale.z -= fOffset;
			// x and z flipped for perpen coll
			float fTemp = wallScale.x;
			wallScale.x = wallScale.z;
			wallScale.z = fTemp;
			if (w0minusb1.Dot(N) < trans1->GetScale().x + wallScale.x * 0.5f
				&& Math::FAbs(w0minusb1.Dot(NP)) < trans1->GetScale().x + wallScale.z * 0.5f)
			{
				CHENG_LOG("ball - square");
				return ChengRigidbody::SQUARE;
			}
		}

		//================================================================================
	}
	// DO NOT BREAK, FALL THROUGH TO ALLOW PERPEN WALL COLL
	case ChengRigidbody::WALL:
	{
		//--------------------------------------------------------------------------------
		ChengRigidbody* rigid1 = go1->GetComponent<ChengRigidbody>();
		ChengRigidbody* rigid2 = go2->GetComponent<ChengRigidbody>();

		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		//--------------------------------------------------------------------------------
		//Vector3 N = Vector3(,0,)
		Mtx44 rot;

		rot.SetToRotation(trans2->GetDegrees(), 0, 1, 0);
		Vector3 N = rot * Vector3(1, 0, 0);
		//--------------------------------------------------------------------------------
		Vector3 w0minusb1 = trans2->GetPosition() - trans1->GetPosition();
		Vector3 pDir = N;
		//--------------------------------------------------------------------------------
		if (w0minusb1.Dot(N) < 0)
			N = -N;

		if (rigid1->m_vVel.Dot(N) > 0)
		{
			Vector3 NP = N.Cross({ 0,-1,0 });

			Vector3 wallScale = trans2->GetScale();
			if (w0minusb1.Dot(N) < trans1->GetScale().x + wallScale.x * 0.5f
				&& Math::FAbs(w0minusb1.Dot(NP)) < trans1->GetScale().x + wallScale.z * 0.5f)
			{
				CHENG_LOG("ball - wall");
				return ChengRigidbody::WALL;
			}
		}

		//================================================================================
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
		//float p1 = go1->GetComponent<ChengRigidbody>()->m_fMass * go1->GetComponent<ChengRigidbody>()->m_vVel.x;
		//float p2 = go2->GetComponent<ChengRigidbody>()->m_fMass * go2->GetComponent<ChengRigidbody>()->m_vVel.x;
		// Response--------------------------------------------------------------------------------
		float m1 = go1->GetComponent<ChengRigidbody>()->m_fMass;
		float m2 = go2->GetComponent<ChengRigidbody>()->m_fMass;
		Vector3 u1 = go1->GetComponent<ChengRigidbody>()->m_vVel;
		Vector3 u2 = go2->GetComponent<ChengRigidbody>()->m_vVel;
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
		//float p1 = go1->GetComponent<ChengRigidbody>()->m_fMass * go1->GetComponent<ChengRigidbody>()->m_vVel.x;
		//float p2 = go2->GetComponent<ChengRigidbody>()->m_fMass * go2->GetComponent<ChengRigidbody>()->m_vVel.x;
		// Response--------------------------------------------------------------------------------
		float m1 = go1->GetComponent<ChengRigidbody>()->m_fMass;
		float m2 = go1->GetComponent<ChengRigidbody>()->m_fMass;
		Vector3 u1 = go1->GetComponent<ChengRigidbody>()->m_vVel;
		Vector3 u2 = -go1->GetComponent<ChengRigidbody>()->m_vVel;
		Vector3 pos1 = go1->GetComponent<TransformComponent>()->GetPosition();
		Vector3 pos2 = go2->GetComponent<TransformComponent>()->GetPosition();
		pos2.y = pos1.y;

		Vector3 newVel1 = u1 - 2 * m2 / (m1 + m2) * (((u1 - u2).Dot(pos1 - pos2)) / (pos1 - pos2).LengthSquared()) * (pos1 - pos2);
		//Vector3 newVel2 = u2 - 2 * m1 / (m1 + m2) * (((u2 - u1).Dot(pos2 - pos1)) / (pos2 - pos1).LengthSquared()) * (pos2 - pos1);
		go1->GetComponent<ChengRigidbody>()->SetVel(newVel1);
		//go2->GetComponent<ChengRigidbody>()->SetVel(newVel2);
	}
	break;
	case ChengRigidbody::SQUARE:
	{
		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		ChengRigidbody* rigid1 = go1->GetComponent<ChengRigidbody>();
		Mtx44 rot;
		rot.SetToRotation(trans2->GetDegrees() + 90, 0, 1, 0);

		Vector3 N = rot * Vector3(1, 0, 0);
		Vector3 v = rigid1->m_vVel - (2 * rigid1->m_vVel.Dot(N)) *N;
		go1->GetComponent<ChengRigidbody>()->SetVel(v);
	}
	break;
	case ChengRigidbody::WALL:
	{
		TransformComponent* trans1 = go1->GetComponent<TransformComponent>();
		TransformComponent* trans2 = go2->GetComponent<TransformComponent>();
		ChengRigidbody* rigid1 = go1->GetComponent<ChengRigidbody>();
		Mtx44 rot;
		rot.SetToRotation(trans2->GetDegrees(), 0, 1, 0);

		Vector3 N = rot * Vector3(1, 0, 0);
		Vector3 v = rigid1->m_vVel - (2 * rigid1->m_vVel.Dot(N)) *N;
		go1->GetComponent<ChengRigidbody>()->SetVel(v);
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
		std::vector<GameObject*> GOList = *it->second->GetGOList();
		for (unsigned i = 0; i < GOList.size(); ++i)
		{
			GameObject* go1 = GOList[i];
			if (!go1->IsActive())
				continue;
			if (!go1->GetComponent<ChengRigidbody>(true))
				continue;
			/*for (unsigned i = 0; i < GOList[i]->GetChildList()->size(); ++i)
			{
				GameObject* goChild = GOList[i];
				if (!go->IsActive())
					continue;
			}*/
			for (unsigned j = i + 1; j < GOList.size(); ++j)
			{
				GameObject* go2 = GOList[j];
				if (!go2->IsActive())
					continue;
				if (!go2->GetComponent<ChengRigidbody>(true))
					continue;
				GameObject* goA = go1;
				GameObject* goB = go2;
				// force go1 to be a ball
				if (go1->GetComponent<ChengRigidbody>()->m_eType != ChengRigidbody::BALL)
				{
					// swap ball to front
					if (go2->GetComponent<ChengRigidbody>()->m_eType == ChengRigidbody::BALL)
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
				CollisionResponse(goA, goB, CheckCollision(goA, goB));
			}
		}
	}
}