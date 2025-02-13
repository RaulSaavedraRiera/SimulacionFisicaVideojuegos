
#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"


class Particle
{
	friend class ParticleGenerator;
	friend class GaussianParticleGenerator;
	friend class UniformParticleGenerator;

public:
	Particle(Vector3 pos_, Vector3 vel_, float size_, double tDestroy, Vector4 color = { 1, 1, 1, 1 },Vector3 acc_ = { 0, -2 , 0 }, float damping_ = 0.999, double mass = 20, bool implicit = true, bool colWithPlayer = false, bool forceSquareGeometry = false);
	Particle(Vector3 pos_, double size_, Vector4 color_, bool colPlayer = false);
	Particle(Vector3 pos_, double sizeXZ, bool colPlayer = false);
	Particle(Vector3 pos_, Vector3 size_, Vector4 color_, bool colPlayer = false);
	~Particle();


	virtual bool integrate(double t);

	virtual Particle* clone() const { return new Particle(pos.p, vel, size, timeDestroy, color, acc, damping, mass, implicit, colWithPlayer); };

	void clearForce() { force = { 0,0,0 }; };
	void addForce(const Vector3& f) { force += f; };

	void setMass(double m) { mass = m; inverseMass = 1 / mass;}
	void setPos(Vector3 newP) { pos.p =newP; }
	void setVel(Vector3 newV) { vel = newV; }
	void setVolume(double vol) { volume = vol; };
	void setCanColPlayer(bool to) { colWithPlayer = to; };

	void changePos(float x, float y, float z);


	const double getInverseMass() { return inverseMass; };
	const double getMass() { return mass; };
	const Vector3 getPos() { return pos.p; };
	const Vector3 getVel() { return vel; };
	const double getSize() { return size; };
	const double getVolume() { return volume; };
	const bool canColWithPlayer() { return colWithPlayer; };
	const bool isSphere() { return sphere; };

protected:
	physx::PxTransform pos;
	Vector3 vel;
	Vector3 force;
	Vector4 color;

	RenderItem* render;

	Vector3 acc;
	float damping;
	double timeDestroy, timePass;

	double size;
	double mass;
	double inverseMass;
	double volume;

	bool implicit;
	bool colWithPlayer;
	bool sphere;

	const float yMin = -10, yMax = 50, limitX = 50;
};

