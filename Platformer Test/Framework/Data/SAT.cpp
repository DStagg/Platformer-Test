#include "SAT.h"

std::vector<Vec> GenAABBNormals()
{
	std::vector<Vec> results;
	results.push_back(Vec(1, 0));
	results.push_back(Vec(0, 1));
	return results;
};

std::vector<Point> GenVertices(AABB box)
{
	std::vector<Point> results;
	results.push_back(Point(box.Left(), box.Top()));
	results.push_back(Point(box.Right(), box.Top()));
	results.push_back(Point(box.Right(), box.Bottom()));
	results.push_back(Point(box.Left(), box.Bottom()));
	return results;
};

std::vector<Vec> GenNormals(std::vector<Vec> vs)	//	Generate the list of normals to check from a list of a polygon's planes
{
	std::vector<Vec> results;
	for (int i = 0; i < (int)vs.size(); i++)
		results.push_back(Vec(-vs[i]._Y, vs[i]._X));
	return results;
};
std::vector<Vec> GenPlanes(std::vector<Point> ps)	//	Generate the planes of a polygon from a list of its points
{
	std::vector<Vec> results;
	for (int i = 0; i < (int)ps.size() - 1; i++)
		results.push_back(Vec((float)ps[i+1].GetX() - ps[i].GetX(),(float) ps[i+1].GetY() - ps[i].GetY()));
	results.push_back(Vec((float)ps[0].GetX() - ps[(int)ps.size()-1].GetX(),(float) ps[0].GetY() - ps[(int)ps.size()-1].GetY()));
	return results;
};

PairFloat Project(std::vector<Point> vertices, Vec axis)
{
	if ((int)vertices.size() == 0)
		return PairFloat(0.f,0.f);

	//	_A is min, _B is max, start both off as the projection of the first vertice
	PairFloat results(Vec((float)vertices[0].GetX(), (float)vertices[0].GetY()).DotProduct(axis), Vec((float)vertices[0].GetX(), (float)vertices[0].GetY()).DotProduct(axis));

	for (int i = 0; i < (int)vertices.size(); i++)
	{
		float p = Vec((float)vertices[i].GetX(), (float)vertices[i].GetY()).DotProduct( axis);
		if (p < results._A)
			results._A = p;
		else if (p > results._B)
			results._B = p;
	}
	
	return results;
};

bool Overlaps(PairFloat p1, PairFloat p2)
{
	//	_A is min, _B is max
	if (p1._B < p2._A) return false;
	if (p1._A > p2._B) return false;
	if (p2._B < p1._A) return false;
	if (p2._A > p1._B) return false;
	return true;
};

float CalcOverlap(PairFloat p1, PairFloat p2)
{
	float d1 = p1._B - p2._A;
	float d2 = p2._B - p1._A;

	return Min(Absolute(d1), Absolute(d2));
};

CollisionResults SATCheck(std::vector<Point> points1, std::vector<Point> points2)
{
	//	Based on: http://www.dyn4j.org/2010/01/sat/#sat-mtv

	std::vector<Vec> a1 = GenNormals(GenPlanes(points1));
	std::vector<Vec> a2 = GenNormals(GenPlanes(points2));

	Vec minAxis = a1[0];
	float minOver = 1000000.f;

	for (int i = 0; i < (int)a1.size(); i++)
	{
		PairFloat p1 = Project(points1, a1[i]);
		PairFloat p2 = Project(points2, a1[i]);

		if (!Overlaps(p1, p2))
			return CollisionResults(false, Vec());

		if (Absolute(CalcOverlap(p1, p2)) < minOver)
		{
			minOver = CalcOverlap(p1, p2);
			minAxis = a1[i];
		}
	}

	for (int i = 0; i < (int)a2.size(); i++)
	{
		PairFloat p1 = Project(points1, a2[i]);
		PairFloat p2 = Project(points2, a2[i]);

		if (!Overlaps(p1, p2))
			return CollisionResults(false, Vec());

		if (Absolute(CalcOverlap(p1, p2)) < minOver)
		{
			minOver = CalcOverlap(p1, p2);
			minAxis = a2[i];
		}
	}

	return CollisionResults(true, minAxis.UnitVec() * minOver);
};