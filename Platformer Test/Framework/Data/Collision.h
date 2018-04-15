#ifndef COLLISION_H
#define COLLISION_H

#include "Shapes.h"

//	NOTE: if adding line<->AABB or line<->circle collisions it should be very simple
//		project the AABB/circle onto the vector and normal vector of the line
//		for the normal projection, check if the AABB/circle overlaps against the thickness of the line
//		for the vector projection, check if the AABB/circle overlaps against the length of the line (skip if infinite length)

class AABBMask;
class CircleMask;

struct CollisionResults
{
	CollisionResults();
	CollisionResults(bool collided, Vec overlap);

	bool _Collided;		//	Did a collision occur?
	Vec _Overlap;		//	What is the overlap on each axis?
};
//	The entity that called Collide() should add _Overlap to separate. The entity that Collide() was called on should subtract it.

class CollisionMask
{
public:

	virtual CollisionResults Collide(CollisionMask& mask) = 0;

	virtual CollisionResults CollideWith(AABBMask& mask) = 0;
	virtual CollisionResults CollideWith(CircleMask& mask) = 0;
};

class AABBMask : public CollisionMask
{
public:

	AABBMask(AABB box = AABB());

	CollisionResults Collide(CollisionMask& mask);

	CollisionResults CollideWith(AABBMask& mask);
	CollisionResults CollideWith(CircleMask& mask);
	
	AABB _Mask;
};

class CircleMask : public CollisionMask
{
public:

	CircleMask(Circle circ = Circle());

	CollisionResults Collide(CollisionMask& mask);

	CollisionResults CollideWith(AABBMask& mask);
	CollisionResults CollideWith(CircleMask& mask);

	Circle _Mask;
};

#endif