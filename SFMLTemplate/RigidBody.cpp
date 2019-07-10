#include "stdafx.h"
#include "RigidBody.h"


RigidBody::RigidBody(string material)
{
	mat = generateMaterial(material);

}

void RigidBody::init() {
	masterObj->masterScene->engine->addBody(this);
	setGravity(true);
}

RigidBody::~RigidBody()
{

}

void RigidBody::onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard) {

	//Vector2f newPos = masterObj->transform->position + velocity;
	//masterObj->transform->move(newPos);
}

void RigidBody::calcInertia(TransformComp* comp, float density, bool immov) {

	torque = 0.0f;

	if (immov) {
		mat.density = 0;
		mat.mass = 0;
		mat.massInv = 0;
		mat.inertia = 0;
		mat.inertInv = 0;
		return;
	}

	Vector2f centroid(0.0f, 0.0f); // centroid
	float area = 0.0f;
	float I = 0.0f;
	const float k_inv3 = 1.0f / 3.0f;

	for (int i1 = 0; i1 < comp->shape.points.size(); ++i1)
	{

		// Triangle vertices, third vertex implied as (0, 0)
		Vector2f p1(comp->shape.points[i1]);
		int i2 = i1 + 1 < comp->shape.points.size() ? i1 + 1 : 0;
		Vector2f p2(comp->shape.points[i2]);

		float D = CrossProduct(p1, p2);
		float triangleArea = 0.5f * D;

		area += triangleArea;

		centroid += triangleArea * k_inv3 * (p1 + p2);

		float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
		float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
		I += (0.25f * k_inv3 * D) * (intx2 + inty2);
	}

	centroid *= 1.0f / area;

	mat.density = density;
	//mat.mass = density * area;
	//mat.massInv = (mat.mass) ? 1.0f / mat.mass : 0.0f;
	mat.inertia = I * density;
	mat.inertInv = mat.inertia ? 1.0f / mat.inertia : 0.0f;
}

