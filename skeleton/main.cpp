#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "CanonBall.h"

#include "SistemaDeParticulas.h"
#include "WorldManager.h"

#include "PlayerController.h"


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;


//practica 1
//CanonBall* canonBall = NULL;
// //RenderItem* ground = NULL;
//RenderItem* diane = NULL;

std::vector<Particle*> particles;

SistemaDeParticulas* particleSystem;
WorldManager* worldManager;

PlayerController* player;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	
	//ground = new RenderItem(CreateShape(PxBoxGeometry(500, 1, 500)), new PxTransform( -100, -5, -100 ), {1,1,1,1});
	//diane = new RenderItem(CreateShape(PxBoxGeometry(5, 5, 5)), new PxTransform(-140, 10, -170), {1,0,0,1});
	//canonBall = new CanonBall({ 20, 30, 0 }, 50, 5, { 0, -0.2, 0 }, 0.999, 200);

	particleSystem = new SistemaDeParticulas();
	worldManager = new WorldManager(gPhysics, gScene, particleSystem);
	//particleSystem->CreateParticleGenerator(SistemaDeParticulas::fuente, {0,0,0}, {0, 2, 0});
	player = new PlayerController(10, worldManager);

	GetCamera()->setOffset(GetCamera()->getEye() - player->getPlayerPos());
	GetCamera()->changeMove();
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->integrate(t);
	}

	particleSystem->Update(t);
	worldManager->update(t);

	GetCamera()->setEye(player->getPlayerPos() + GetCamera()->getOffset());
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();

}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (toupper(key))
	{
		//case 'B': break;
		//case ' ':	break;
	case 'E':
	{
		particleSystem->CreateFireWorkSystem('E');
		break;
	}
	case 'R':
	{
		particleSystem->CreateFireWorkSystem('R');
		break;
	}
	case 'T':
	{
		particleSystem->CreateFireWorkSystem('T');
		break;
	}
	case 'Y':
	{
		particleSystem->CreateFireWorkSystem('Y');
		break;
	}
	case 'U':
	{
		particleSystem->CreateFireWorkSystem('U');
		break;
	}
	case 'I':
	{
		particleSystem->CreateFireWorkSystem('I');
		break;
	}
	case 'H':
	{
		particleSystem->CreateParticleGenerator(SistemaDeParticulas::fuente, { 0,0,0 }, { 0, 5, 5 });
		break;
	}
	case 'F':
	{
		particleSystem->CreateParticleGenerator(SistemaDeParticulas::laser, { 0,0,0 }, { 0, 2, 0 });
		break;
	}
	case 'G':
	{
		particleSystem->CreateParticleGenerator(SistemaDeParticulas::snow, { 0,0,0 }, { 0, 0, 0 });
		break;
	}
	case 'Q':
		particles.push_back(new CanonBall(GetCamera()->getEye(), 180, 5, 10, {0, -0.5, 0}, 0.999, 350));
		break;
	case 'Z':
		particleSystem->CreatePhysicsParticle('z');
		break;
	case 'X':
		particleSystem->CreatePhysicsParticle('x');
		break;
	case 'C':
		particleSystem->CreatePhysicsParticle('c');
		break;
	case 'V':
		particleSystem->CreatePhysicsParticle('v');
		break;
	/*case '1':
		particleSystem->ControlForceGenerators('1');
		break;
	case '2':
		particleSystem->ControlForceGenerators('2');
		break;
	case '3':
		particleSystem->ControlForceGenerators('3');
		break;
	case '4':
		particleSystem->ControlForceGenerators('4');
		break;
	case '5':
		particleSystem->ControlForceGenerators('5');
		break;
	case '6':
		particleSystem->ControlForceGenerators('6');
		break;
	case '7':
		particleSystem->ControlForceGenerators('7');
		break;
	case '8':
		particleSystem->ControlForceGenerators('8');
		break;
	case '9':
		particleSystem->ControlForceGenerators('9');
		break;*/
	case 'J':
	case 'K':
	case 'L':
	case 'M':
		worldManager->InputActions(tolower(key));
		break;
			
	case 'W':
	case 'A':
	case 'S':
	case 'D':
		player->addForce(tolower(key));
		break;
	case 'B':
		player->resetPosition();
		break;
	default:
		particleSystem->ControlForceGenerators(tolower(key));
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}