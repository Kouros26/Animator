#pragma once
#include "btBulletDynamicsCommon.h"

class PhysicsWorld 
{
	btDefaultCollisionConfiguration* collisionConfiguration = nullptr;
	btCollisionDispatcher* dispatcher = nullptr;
	btBroadphaseInterface* overlappingPairCache = nullptr;
	btSequentialImpulseConstraintSolver* solver = nullptr;
	btDiscreteDynamicsWorld* dynamicsWorld = nullptr;

	btAlignedObjectArray<btCollisionShape*> collisionShapes;

public:

	PhysicsWorld();
	~PhysicsWorld();
};