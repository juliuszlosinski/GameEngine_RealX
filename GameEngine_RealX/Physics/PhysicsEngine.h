#ifndef PHYSX_H
#define PHYSX_H

#include <iostream>
#include "../Graphics/Model.h"
#include "PxPhysicsAPI.h"

#define PVD_HOST "127.0.0.1"
#define PVD_PORT 5425
#define PVD_TIMEOUT 1000


class PhysicsEngine
{
	physx::PxDefaultErrorCallback     mDefaultErrorCallback;
	physx::PxDefaultAllocator     mDefaultAllocatorCallback;
	
	physx::PxFoundation*			  mFoundation;	// Foundation for Physics SDK.
	physx::PxPvd*			 mPhysXVisualDebugger;	// Application PhysX Visual Debugger.
	physx::PxPhysics*					 mPhysics;	// Physics SDK.
	physx::PxDefaultCpuDispatcher* mCPUDispatcher;	// Organizing threads.
	physx::PxScene*				           mScene;	// Will contain all actors, scene is a singleton!. We need PxSceneDesc to create it.
	physx::PxMaterial*					mMaterial;	// Material for every actor.
	physx::PxCooking*					 mCooking;	// Serialization big data.

	physx::PxReal						stackZ;

	const physx::PxReal SLOW_MOTION   = 1.0f / 240.0f;
	const physx::PxReal NORMAL_MOTION = 1.0f / 60.0f;
public:
	// Default constructor.
	PhysicsEngine()
	{
		mFoundation = nullptr;
		mPhysXVisualDebugger = nullptr;
		mPhysics = nullptr;
		mCPUDispatcher = nullptr;
		mScene = nullptr;
		mMaterial = nullptr;
		mCooking = nullptr;
		stackZ = 0.0f;
	}

	// Initializing physx foundation that is base for creating objects from PhysX SDK.
	void InitFoundation()
	{
		// Creating the singleton foundation.
		mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION,
			mDefaultAllocatorCallback,
			mDefaultErrorCallback);

		// Checking if foundation is correctly created.
		if (!mFoundation)
		{
			std::cout << "PhysX::PxCreateFoundation failed!\n";
		}
	}

	physx::PxReal getValueOfNormalMotion()
	{
		return NORMAL_MOTION;
	}

	physx::PxReal getValueOfSlowMotion()
	{
		return SLOW_MOTION;
	}

	// Initializing PhysX Visual Debugger (PVD).
	void InitPVD()
	{
		// Creating PhysX visual debugger.
		mPhysXVisualDebugger = physx::PxCreatePvd(*mFoundation);

		// Checking PhysX visual debugger is correctly createad.
		if (!mPhysXVisualDebugger)
		{
			std::cout << "PhysX::PxCreatePVD failed!\n";
		}

		// Creatng transport for commucation TCP/IP.
		physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(
			PVD_HOST, PVD_PORT, PVD_TIMEOUT
		);

		// Checking if transport is correctly created.
		if (!transport)
		{
			std::cout << "PhysX::PxCreateDefaultPvdSocketTransportCreate failed!\n";
		}

		// Connecting to the PVD application.
		mPhysXVisualDebugger->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
	}

	// Initializing Physics SDK.
	void InitPhysics()
	{
		// Creating a flag about recording memory allocations.
		bool recordMemoryAllocations = true;

		// Creating physics SDK.
		mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION,
			*mFoundation,
			physx::PxTolerancesScale(),
			recordMemoryAllocations,
			mPhysXVisualDebugger);

		// Checking if physics SDK is propertly created.
		if (!mPhysics)
		{
			std::cout << "PhysX::PxCreatePhysics failed!\n";
		}
	}

	// Initializing dispatcher for organizing CPU work like threads.
	void InitDispatcher()
	{
		// Creating variable that holds number of threads.
		int numberOfThreads = 2;

		// Creating dispatcher.
		mCPUDispatcher = physx::PxDefaultCpuDispatcherCreate(numberOfThreads);

		// Checking if dispatcher is correctly created.
		if (!mCPUDispatcher)
		{
			std::cout << "PhysX::PxDefaultCpuDispatcherCreate failed!\n";
		}
	}

	// Initialzing material for actors (like static friction, dynamic friction and restitution).
	void InitMaterial()
	{
		// Setting up the attributes for material.
		physx::PxReal staticFriction = 0.5f;
		physx::PxReal dynamicFriction = 0.5f;
		physx::PxReal restitution = 0.6f;

		// Creating material.
		mMaterial = mPhysics->createMaterial(
			staticFriction, dynamicFriction, restitution
		);

		// Checking if material is correctly created.
		if (!mMaterial)
		{
			std::cout << "PhysX::CreateMaterial failed!\n";
		}
	}

	// Initializing cooking for big data's serialization.
	void InitCooking()
	{
		// Creating cooking.
		physx::PxCookingParams params(physx::PxTolerancesScale());
		physx::PxTolerancesScale scale;
		scale.length = 1.05;

		mCooking  = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation,
			physx::PxCookingParams(physx::PxTolerancesScale()));

		// Checking if cooking is correctly created.
		if (!mCooking)
		{
			std::cout << "PhysX::PxCreateCooking failed!\n";
		}
	}
	
	// Initializing all components (all necessary members, essential variables, scene and setting up PVD client.
	void Init()
	{
		InitEssentialVariables();
		InitScene();
		SetScenePVDClient();
	}

	// Initializing all necessary members.
	void InitEssentialVariables()
	{
		// 1. Initializing foundation for physics.
		InitFoundation();

		// 2. Initializing PhysX Visual Debugger.
		InitPVD();

		// 3. Initializing physics member that will use foundation and PVD as constructor parameters.
		InitPhysics();

		// 4. Initializing CPU Dispatcher for threads handling.
		InitDispatcher();

		// 5. Initializing material (static/ dynamic friction and restitution) for actors.
		InitMaterial();

		// 6. Initializing cooking for big data's serialization.
		InitCooking();
	}

	// Initializing scene that will use gravition vector, adding CPU dispatcher and shading filter.
	void InitScene()
	{
		// Creating scene desciptor.
		physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());

		// Setting up gravity.
		sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);

		// Setting up cpu dispatcher.
		sceneDesc.cpuDispatcher = mCPUDispatcher;

		// Setting up filter shader.
		sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

		// Creating a scene by using "physics member" and passing to it created scene descriptor.
		mScene = mPhysics->createScene(sceneDesc);

		// Checking if scene is correctly created.
		if (!mScene)
		{
			std::cout << "PhysX::Create scene failed!\n";
		}
	}

	// Setting up scene PhysX Visuall Debugger client.
	void SetScenePVDClient()
	{
		// Creating a pvd client.
		physx::PxPvdSceneClient* phyicsVisualDebuggerClient = mScene->getScenePvdClient();

		// Checking if pvd client is correctly created.
		if (phyicsVisualDebuggerClient)
		{
			phyicsVisualDebuggerClient->setScenePvdFlag(
				physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true
			);
			phyicsVisualDebuggerClient->setScenePvdFlag(
				physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true
			);
			phyicsVisualDebuggerClient->setScenePvdFlag(
				physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true
			);
		}
	}

	// Creating static plane and adding to physics scene.
	void CreateStaticPlane()
	{
		// Creating a static ground plane.
		physx::PxRigidStatic* pGroundPlane = physx::PxCreatePlane(*mPhysics, physx::PxPlane(0, 1, 0, 0), *mMaterial);

		// Checking if plane correctly created.
		if (!pGroundPlane)
		{
			std::cout << "Physx::PxCreatePlane failed!\n";
		}

		// Adding plane to the scene.
		mScene->addActor(*pGroundPlane);
	}

	physx::PxRigidDynamic* CreateDynamicSphere(float radius = 1.0f, physx::PxVec3 position = physx::PxVec3(0.0f, 0.0f, 0.0f))
	{
		physx::PxShape* actorShape = mPhysics->createShape(
			physx::PxSphereGeometry(radius),
			*mMaterial
		);


		physx::PxRigidDynamic* actorBody = mPhysics->createRigidDynamic(
			physx::PxTransform(position)
		);

		actorBody->attachShape(*actorShape);

		std::cout << "\n";
		std::cout << "Global pose of an actor x: " << actorBody->getGlobalPose().p.x << "\n";
		std::cout << "Global pose of an actor y: " << actorBody->getGlobalPose().p.y << "\n";
		std::cout << "Global pose of an actor z: " << actorBody->getGlobalPose().p.z << "\n";
		std::cout << "Global rotation of an actor x: " << actorBody->getGlobalPose().q.x << "\n";
		std::cout << "Global rotation of an actor y: " << actorBody->getGlobalPose().q.y << "\n";
		std::cout << "Global rotation of an actor z: " << actorBody->getGlobalPose().q.z << "\n";
		std::cout << "\n";

		physx::PxRigidBodyExt::updateMassAndInertia(*actorBody, 10.0f);
		mScene->addActor(*actorBody);

		return actorBody;
	}

	physx::PxRigidStatic* CreateStaticSphere(float radius = 1.0f, physx::PxVec3 position = physx::PxVec3(0.0f, 0.0f, 0.0f))
	{
		physx::PxShape* actorShape = mPhysics->createShape(
			physx::PxSphereGeometry(radius),
			*mMaterial
		);


		physx::PxRigidStatic* actorBody = mPhysics->createRigidStatic(
			physx::PxTransform(position)
		);

		actorBody->attachShape(*actorShape);

		std::cout << "\n";
		std::cout << "Global pose of an actor x: " << actorBody->getGlobalPose().p.x << "\n";
		std::cout << "Global pose of an actor y: " << actorBody->getGlobalPose().p.y << "\n";
		std::cout << "Global pose of an actor z: " << actorBody->getGlobalPose().p.z << "\n";
		std::cout << "Global rotation of an actor x: " << actorBody->getGlobalPose().q.x << "\n";
		std::cout << "Global rotation of an actor y: " << actorBody->getGlobalPose().q.y << "\n";
		std::cout << "Global rotation of an actor z: " << actorBody->getGlobalPose().q.z << "\n";
		std::cout << "\n";

		mScene->addActor(*actorBody);

		return actorBody;
	}

	physx::PxRigidDynamic* CreateDynamicBox(physx::PxVec3 size = physx::PxVec3(1.0f, 1.0f, 1.0f), physx::PxVec3 position = physx::PxVec3(0.0f, 0.0f, 0.0f))
	{
		physx::PxShape* actorShape = mPhysics->createShape(
			physx::PxBoxGeometry(size.x, size.y, size.z),
			*mMaterial
		);


		physx::PxRigidDynamic* actorBody = mPhysics->createRigidDynamic(
			physx::PxTransform(position)
		);

		actorBody->attachShape(*actorShape);

		std::cout << "\n";
		std::cout << "Global pose of an actor x: " << actorBody->getGlobalPose().p.x << "\n";
		std::cout << "Global pose of an actor y: " << actorBody->getGlobalPose().p.y << "\n";
		std::cout << "Global pose of an actor z: " << actorBody->getGlobalPose().p.z << "\n";
		std::cout << "Global rotation of an actor x: " << actorBody->getGlobalPose().q.x << "\n";
		std::cout << "Global rotation of an actor y: " << actorBody->getGlobalPose().q.y << "\n";
		std::cout << "Global rotation of an actor z: " << actorBody->getGlobalPose().q.z << "\n";
		std::cout << "\n";

		physx::PxRigidBodyExt::updateMassAndInertia(*actorBody, 10.0f);
		mScene->addActor(*actorBody);

		return actorBody;
	}

	physx::PxRigidStatic* CreateStaticBox(physx::PxVec3 size = physx::PxVec3(1.0f, 1.0f, 1.0f), physx::PxVec3 position = physx::PxVec3(0.0f, 0.0f, 0.0f))
	{
		physx::PxShape* actorShape = mPhysics->createShape(
			physx::PxBoxGeometry(size.x, size.y, size.z),
			*mMaterial
		);


		physx::PxRigidStatic* actorBody = mPhysics->createRigidStatic(
			physx::PxTransform(position)
		);

		actorBody->attachShape(*actorShape);

		std::cout << "\n";
		std::cout << "Global pose of an actor x: " << actorBody->getGlobalPose().p.x << "\n";
		std::cout << "Global pose of an actor y: " << actorBody->getGlobalPose().p.y << "\n";
		std::cout << "Global pose of an actor z: " << actorBody->getGlobalPose().p.z << "\n";
		std::cout << "Global rotation of an actor x: " << actorBody->getGlobalPose().q.x << "\n";
		std::cout << "Global rotation of an actor y: " << actorBody->getGlobalPose().q.y << "\n";
		std::cout << "Global rotation of an actor z: " << actorBody->getGlobalPose().q.z << "\n";
		std::cout << "\n";

		mScene->addActor(*actorBody);

		return actorBody;
	}

	physx::PxRigidStatic* CreateStaticCapsule(float radius = 0.15f, float halfHeight = 0.35f, physx::PxVec3 position = physx::PxVec3(0.0f, 0.0f, 0.0f))
	{
		physx::PxShape* actorShape = mPhysics->createShape(
			physx::PxCapsuleGeometry(radius, halfHeight),
			*mMaterial
		);

		physx::PxRigidStatic* actorBody = mPhysics->createRigidStatic(
			physx::PxTransform(position)
		);

		actorBody->attachShape(*actorShape);

		std::cout << "\n";
		std::cout << "Global pose of an actor x: " << actorBody->getGlobalPose().p.x << "\n";
		std::cout << "Global pose of an actor y: " << actorBody->getGlobalPose().p.y << "\n";
		std::cout << "Global pose of an actor z: " << actorBody->getGlobalPose().p.z << "\n";
		std::cout << "Global rotation of an actor x: " << actorBody->getGlobalPose().q.x << "\n";
		std::cout << "Global rotation of an actor y: " << actorBody->getGlobalPose().q.y << "\n";
		std::cout << "Global rotation of an actor z: " << actorBody->getGlobalPose().q.z << "\n";
		std::cout << "\n";

		mScene->addActor(*actorBody);

		return actorBody;
	}

	physx::PxRigidDynamic* CreateDynamicCapsule(float radius = 0.15f, float halfHeight = 0.35f, physx::PxVec3 position = physx::PxVec3(0.0f, 0.0f, 0.0f))
	{
		physx::PxShape* actorShape = mPhysics->createShape(
			physx::PxCapsuleGeometry(radius, halfHeight),
			*mMaterial
		);

		physx::PxRigidDynamic* actorBody = mPhysics->createRigidDynamic(
			physx::PxTransform(position)
		);

		actorBody->attachShape(*actorShape);

		std::cout << "\n";
		std::cout << "Global pose of an actor x: " << actorBody->getGlobalPose().p.x << "\n";
		std::cout << "Global pose of an actor y: " << actorBody->getGlobalPose().p.y << "\n";
		std::cout << "Global pose of an actor z: " << actorBody->getGlobalPose().p.z << "\n";
		std::cout << "Global rotation of an actor x: " << actorBody->getGlobalPose().q.x << "\n";
		std::cout << "Global rotation of an actor y: " << actorBody->getGlobalPose().q.y << "\n";
		std::cout << "Global rotation of an actor z: " << actorBody->getGlobalPose().q.z << "\n";
		std::cout << "\n";

		physx::PxRigidBodyExt::updateMassAndInertia(*actorBody, 10.0f);
		mScene->addActor(*actorBody);

		return actorBody;
	}

	// Creating stack of spheres and setting up these on the stack.
	void CreateStack(const physx::PxTransform& transformationVector, physx::PxU32 heightOfStack, physx::PxReal radiusOfSphere)
	{
		// Creating a shape for the actor.
		physx::PxShape* actorShape = mPhysics->createShape(
			physx::PxSphereGeometry(radiusOfSphere), *mMaterial
		);

		// Creating actors and adding the to the scene.
		for (physx::PxU32 i = 0; i < heightOfStack; i++)
		{
			for (physx::PxU32 j = 0; j < heightOfStack - i; j++)
			{
				physx::PxTransform localTm(physx::PxVec3(
					physx::PxReal(j * 2) - physx::PxReal(radiusOfSphere - i),
					physx::PxReal(i * 2 + 1), 0) * radiusOfSphere);
			
				physx::PxRigidDynamic* actorBody = mPhysics->createRigidDynamic(
					transformationVector.transform(localTm)
				);

				actorBody->attachShape(*actorShape);
				std::cout << "\n";
				std::cout << "Global pose of an actor x: " << actorBody->getGlobalPose().p.x << "\n";
				std::cout << "Global pose of an actor y: " << actorBody->getGlobalPose().p.y << "\n";
				std::cout << "Global pose of an actor z: " << actorBody->getGlobalPose().p.z << "\n";
				std::cout << "Global rotation of an actor x: " << actorBody->getGlobalPose().q.x << "\n";
				std::cout << "Global rotation of an actor y: " << actorBody->getGlobalPose().q.y << "\n";
				std::cout << "Global rotation of an actor z: " << actorBody->getGlobalPose().q.z << "\n";
				std::cout << "\n";
				physx::PxRigidBodyExt::updateMassAndInertia(*actorBody, 10.0f);
				mScene->addActor(*actorBody);
			}
		}

		// Releasing actor's shape.
		actorShape->release();
	}

	// Creating multiple stacks.
	void createMultipleStacks(physx::PxU32 numberOfStacks, physx::PxU32 stackHeight, physx::PxReal sphereRadius)
	{
		// Creating stacks.
		for (physx::PxU32 i = 0; i < numberOfStacks; i++)
		{
			CreateStack(physx::PxTransform(physx::PxVec3(0, 0, stackZ -= 10.0f)), stackHeight, sphereRadius);
		}
	}

	// Render loop.
	void RenderLoop(physx::PxReal renderSpeed)
	{
		while (mScene)
		{
			mScene->simulate(renderSpeed);
			std::cout << "PhysX::Simulating...\n";
			mScene->fetchResults(true);
			std::cout << "PhysX::Fetching results...\n";
		}
	}

	// Updating PhysX.
	void Update(physx::PxReal renderSpeed)
	{
		mScene->simulate(renderSpeed);
		std::cout << "PhysX::Simulating...\n";
		mScene->fetchResults(true);
		std::cout << "PhysX::Fetching results...\n";
	}

	// Creating triangle mesh by using mesh descriptor.
	physx::PxTriangleMesh* CreateTriangleMesh(physx::PxTriangleMeshDesc meshDescriptor)
	{
		// Creating default memory output stream.
		physx::PxDefaultMemoryOutputStream buffer;

		// Checking if cooking is done correctly.
		if (!mCooking->cookTriangleMesh(meshDescriptor, buffer))
		{
			std::cout << "PhysX::Triangle mesh is nullptr!\n";
			return nullptr;
		}

		// Creating default memory input stream.
		physx::PxDefaultMemoryInputData input(buffer.getData(), buffer.getSize());

		// Getting the result.
		return mPhysics->createTriangleMesh(input);
	}

	// Creating a dynamic actor from model.
	physx::PxRigidDynamic* CreateDynamicActorFromModel(Model& model, physx::PxVec3 position)
	{
		// 1. Creating mesh descriptor for the model.
		physx::PxTriangleMeshDesc meshDescriptor = CreateMeshDesc(model);

		// 2. Creating triangle mesh based on previously created mesh descriptor.
		physx::PxTriangleMesh* triangleMesh = CreateTriangleMesh(meshDescriptor);

		// 3. Creating shape based on previously created triangle mesh.
		physx::PxShape* dynamicShape = mPhysics->createShape(
			physx::PxTriangleMeshGeometry(triangleMesh),
			*mMaterial,
			true
		);

		// 4. Creating dynamic rigid body for model.
		physx::PxRigidDynamic* dynamicBody = mPhysics->createRigidDynamic(
			physx::PxTransform(position)
		);

		// 5. Attaching shape to rigid body.
		dynamicBody->attachShape(*dynamicShape);

		physx::PxRigidBodyExt::updateMassAndInertia(*dynamicBody, 10.0f);

		// 6. Adding actor to the scene.
		mScene->addActor(*dynamicBody);

		// 7. Releasing the static shape.
		dynamicShape->release();

		// 8. Returning the dynamic body.
		return dynamicBody;
	}

	// Creating a static actor from model.
	physx::PxRigidStatic* CreateStaticActorFromModel(Model& model, physx::PxVec3 position)
	{
		// 1. Creating mesh descriptor for the model.
		physx::PxTriangleMeshDesc meshDescriptor = CreateMeshDesc(model);

		// 2. Creating triangle mesh based on previously created mesh descriptor.
		physx::PxTriangleMesh* triangleMesh = CreateTriangleMesh(meshDescriptor);

		// 3. Creating shape based on previously created triangle mesh.
		physx::PxShape* staticShape = mPhysics->createShape(
			physx::PxTriangleMeshGeometry(triangleMesh),
			*mMaterial,
			true
		);

		// 4. Creating static rigid body for model.
		physx::PxRigidStatic* staticBody = mPhysics->createRigidStatic(
			physx::PxTransform(position)
		);

		// 5. Attaching shape to rigid body.
		staticBody->attachShape(*staticShape);

		// 6. Adding actor to the scene.
		mScene->addActor(*staticBody);

		// 7. Releasing the static shape.
		staticShape->release();

		// 8. Returning the rigid body.
		return staticBody;
	}

	// Creating mesh descriptor from model.
	physx::PxTriangleMeshDesc CreateMeshDesc(Model& model)
	{
		physx::PxTriangleMeshDesc meshDescriptor;

		std::vector<glm::vec3> glVertices = model.getTotalVertexPositions();
		meshDescriptor.points.count = static_cast<physx::PxU32>(glVertices.size());
		meshDescriptor.points.stride = sizeof(physx::PxVec3);
		meshDescriptor.points.data = ConvertVerticesToPx(glVertices);

		std::vector<unsigned int> pxIndices = model.getTotalIndices();
		meshDescriptor.triangles.count = static_cast<physx::PxU32>(pxIndices.size()) / 3;
		meshDescriptor.triangles.stride = 3 * sizeof(physx::PxU32);
		meshDescriptor.triangles.data = ConvertIndicesToPx(pxIndices);

		if (!meshDescriptor.isValid())
		{
			std::cout << "PhysX::Triangle mesh descriptor is not valid!\n";
		}

		return meshDescriptor;
	}

	// Converting vertices to physX vertices.
	physx::PxVec3* ConvertVerticesToPx(std::vector<glm::vec3> glVertices)
	{
		physx::PxVec3* pxVertices = new physx::PxVec3[glVertices.size()];
		for (int i = 0; i < glVertices.size(); i++)
		{
			pxVertices[i].x = glVertices[i].x;
			pxVertices[i].y = glVertices[i].y;
			pxVertices[i].z = glVertices[i].z;
		}
		return pxVertices;
	}

	// Converting indices to physX indices.
	physx::PxU32* ConvertIndicesToPx(std::vector<unsigned int> glIndices)
	{
		physx::PxU32* pxIndices = new physx::PxU32[glIndices.size()];
		for (int i = 0; i < glIndices.size(); i++)
		{
			pxIndices[i] = glIndices[i]-1;
		}
		return pxIndices;
	}

	// Destructor.
	~PhysicsEngine()
	{
		mFoundation->release();
		mPhysXVisualDebugger->release();
		mPhysics->release();
		mCPUDispatcher->release();
		mScene->release();
		mMaterial->release();
		std::cout << "PhysX::All variables are released!\n";
	}
};

#endif