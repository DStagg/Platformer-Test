#include "Collision.h"

//	Collision Results

CollisionResults::CollisionResults()
{
	_Collided = false;
	_Overlap = Vec(0.f, 0.f);
};

CollisionResults::CollisionResults(bool collided, Vec overlap)
{
	_Collided = collided;
	_Overlap = overlap;
};

/////////////////////

//	Double Dispatch

AABBMask::AABBMask(AABB box)
{
	_Mask = box;
}

CollisionResults AABBMask::Collide(CollisionMask& mask)
{
	return mask.CollideWith(*this);
};
CollisionResults AABBMask::CollideWith(AABBMask& mask)
{
	//	Based off of: https://hamaluik.com/posts/simple-aabb-collision-using-minkowski-difference/
	//	TLDR: sum the two boxes toGether, if the result covers (0,0) then they intersect
	//			the minimum escape vector is then whichever cardinal direction is closest to 0

	AABB minkowski(_Mask.Left() - mask._Mask.Right(), _Mask.Top() - mask._Mask.Bottom(), _Mask._Width + mask._Mask._Width, _Mask._Height + mask._Mask._Height);
	if (!minkowski.Contains(0, 0))
		return CollisionResults(false, Vec());

	int minDist = Absolute(minkowski.Left());	//	Left
	Vec minVec((float)minkowski.Left(), 0.f);

	if (Absolute(minkowski.Right()) < minDist)	//	Right
	{
		minDist = Absolute(minkowski.Right());
		minVec = Vec((float)minkowski.Right(), 0.f);
	}
	if (Absolute(minkowski.Bottom()) < minDist)	//	Bottom
	{
		minDist = Absolute(minkowski.Bottom());
		minVec = Vec(0.f, (float)minkowski.Bottom());
	}
	if (Absolute(minkowski.Top()) < minDist)		//	Top
	{
		minDist = Absolute(minkowski.Top());
		minVec = Vec(0.f, (float)minkowski.Top());
	}

	return CollisionResults(true, minVec);
};
CollisionResults AABBMask::CollideWith(CircleMask& mask)
{
	Circle circ = mask._Mask;

	Point nearest(Max(_Mask.Left(), Min(circ._X, _Mask.Right())), Max(_Mask.Top(), Min(circ._Y, _Mask.Bottom())));

	float Distance = CalcDistance(nearest.GetX(), nearest.GetY(), circ._X, circ._Y);

	if (Distance > circ._Radius)
		return CollisionResults(false, Vec());

	Vec sepVec = Vec((float)nearest.GetX() - circ._X, (float)nearest.GetY() - circ._Y).UnitVec() * (Distance - circ._Radius);
	//	Need to make into  aunit vec and multiply by Distance - _Radius

	return CollisionResults(true, sepVec);
};

CircleMask::CircleMask(Circle circ)
{
	_Mask = circ;
};

CollisionResults CircleMask::Collide(CollisionMask& mask)
{
	return mask.CollideWith(*this);
};
CollisionResults CircleMask::CollideWith(AABBMask& mask)
{
	CollisionResults temp = mask.CollideWith(*this);
	temp._Overlap._X = -temp._Overlap._X;
	temp._Overlap._Y = -temp._Overlap._Y;
	return temp;
};
CollisionResults CircleMask::CollideWith(CircleMask& mask)
{
	float dist = (float)(_Mask._Radius + mask._Mask._Radius) - CalcDistance((float)_Mask._X, (float)_Mask._Y, (float)mask._Mask._X, (float)mask._Mask._Y);
	if (dist > 0.f)	//	i.e. if the distance between the centers is greater than the sum of the radii
	{
		Vec sepvec = (Vec((float)mask._Mask._X, (float)mask._Mask._Y) - Vec((float)_Mask._X, (float)_Mask._Y)).UnitVec() * dist;
		return CollisionResults(true, sepvec);
	}
	return CollisionResults();
};