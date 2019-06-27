#pragma once
#include "stdafx.h"
#include "Component.h"

struct polygon {
	vector<Vector2f> points;
	vector<Vector2f> normals;

	polygon() {
		points.push_back(Vector2f(0, 0));
		points.push_back(Vector2f(1, 0));
		points.push_back(Vector2f(1, 1));
		points.push_back(Vector2f(0, 1));
		normals = calculateNormals(points);

	}

	//using (dy, -dx) <- (-dy, dx)

	vector<Vector2f> calculateNormals(vector<Vector2f> points) {
		vector<Vector2f> normals;
		Vector2f p1;
		Vector2f p2;
		float dx;
		float dy;
		for (int i = 0; i < points.size() - 1; i++) {
			p1 = points.at(i);
			p2 = points.at(i + 1);
			dx = p2.x - p1.x;
			dy = p2.y - p1.y;
			normals.push_back(normalize(Vector2f(dy, -dx)));
		}

		p1 = points.at(points.size() - 1);
		p2 = points.at(0);

		dx = p2.x - p1.x;
		dy = p2.y - p1.y;
		normals.push_back(normalize(Vector2f(dy, -dx)));

		return normals;
	}

	Vector2f projectPolygon(Vector2f axis) { //to an axis

		Vector2f range(dotProduct(axis, points[0]), dotProduct(axis, points[0])); //in the form min max
		for (unsigned int i = 0; i < points.size(); i++) {
			float proj = dotProduct(axis, points[i]);
			if (proj < range.x) range.x = proj;
			if (proj > range.y) range.y = proj;
		}

		return range;
	}

};

class TransformComp : public Component
{
public:
	TransformComp(Vector2f posIn);
	TransformComp();
	~TransformComp();
	void move(Vector2f newPos);
	void changeShape(vector<Vector2f> points, Vector2f position, Vector2f scale);
	void changeShape(Vector2f position, Vector2f scale);
	//FloatRect* getMinAABB();
	polygon shape;
	Vector2f position;
};

