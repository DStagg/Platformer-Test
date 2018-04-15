#ifndef SAT_H
#define SAT_H

#include "Collision.h"
#include <vector>

//	Useful reading: http://www.dyn4j.org/2010/01/sat/#sat-mtv

std::vector<Vec> GenAABBNormals();			//	i.e. returns the x- and y-axis (1,0) and (0,1) as vectors
std::vector<Point> GenVertices(AABB box);	//	Returns the vertices (corners) for an AABB

std::vector<Vec> GenNormals(std::vector<Vec> vs);	//	Generate the list of normals to check from a list of a polygon's planes
std::vector<Vec> GenPlanes(std::vector<Point> ps);	//	Generate the planes of a polygon from a list of its points

PairFloat Project(std::vector<Point> vertices, Vec axis);	//	Returns the min & max for the projection of a shape onto an axis

bool Overlaps(PairFloat p1, PairFloat p2);	//	Returns if the max projection of 1 shape is greater than the min of the other (or vice versa)
float CalcOverlap(PairFloat p1, PairFloat p2);	//	Calculates the magnitude of the overlap

CollisionResults SATCheck(std::vector<Point> points1, std::vector<Point> points2);

#endif