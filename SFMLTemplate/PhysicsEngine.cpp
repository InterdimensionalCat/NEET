#include "stdafx.h"
#include "PhysicsEngine.h"

float currentDT;
//Vector2f gravity(0.0f, 0.0f);
Vector2f gravity(0.0f, (-9.8f * 60.0f) / 6000.0f);


PhysicsEngine::PhysicsEngine(Scene* master)
{
	masterScene = master;
}


PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::addBody(RigidBody* body) {
	bodies.push_back(body);
}

void PhysicsEngine::generateCollisions() {
	for (auto body1 : bodies) {
		for (auto body2 : bodies) {
			if (body1 == body2) continue;
			collisions.push_back(collision(body1, body2));
		}
	}

	//cull dupes

	for (int i = 0; i < collisions.size() - 1; i++) {
		for (int j = 1; j < collisions.size(); j++) {
			if (collisions[i].A == collisions[j].B && collisions[i].B == collisions[j].A) {
				collisions.erase(collisions.begin() + i);
				//i--;
				//j--;
			}
		}
	}

	if (collisions[0].A == collisions[collisions.size() - 1].B && collisions[0].B == collisions[collisions.size() - 1].A) {
		collisions.erase(collisions.begin() + 0);
	}

	for (int i = 0; i < collisions.size(); i++) {
		if (collisions[i].A->mat.mass == 0 && collisions[i].B->mat.mass == 0) {
			collisions.erase(collisions.begin() + i);
		}
	}

}

void PhysicsEngine::applyGravity() {
	for (auto body : bodies) {
		if (body->gravity) {
			body->velocity -= gravity * body->mat.gravityScale;
		}
	}
}

void PhysicsEngine::integrateVelocity(float deltaTime) {
	for (auto body : bodies) {

		if (body->force.y != 0) {
			//cout << body->force.y << endl;
		}

		body->velocity += (body->mat.massInv * body->force) * deltaTime;
		body->angularVelocity += (body->torque * body->mat.inertInv);// *deltaTime;
		body->masterObj->transform->move(body->velocity * deltaTime, body->angularVelocity);
		body->force = Vector2f(0, 0);
		body->torque = 0.0f;

		if (body->velocity.y != 0) {
			//cout << body->velocity.x << " " << body->velocity.y << endl;
		}

		if (body->angularVelocity != 0) {
			//cout << body->angularVelocity << endl;
		}

		//if (magnitude(body->velocity)) {
		//	cout << body->masterObj->transform->position.x << " " << body->masterObj->transform->position.y << endl;
		//}
	}
}

void PhysicsEngine::step(float deltaTime) {

	currentDT = deltaTime;
	collisions.clear();

	//Broad Phase


	generateCollisions();


	//integrate velocity

	applyGravity();

	//for (auto body : bodies) {
	//	TransformComp* trans = body->masterObj->transform;
	//	trans->move(body->velocity);
	//}

	integrateVelocity(deltaTime);

	//resolve collisisons

	for (auto col : collisions) {
			if (SAT(&col)) {
				//resolveCollision(&col);
				rotationalResolution(&col);
			}
	}


}


bool PhysicsEngine::SAT(collision* pair) {

	polygon A = pair->A->masterObj->transform->shape;
	polygon B = pair->B->masterObj->transform->shape;
	vector<Vector2f> Anormals = A.normals;
	vector<Vector2f> Bnormals = B.normals;
	float penA = -FLT_MAX;
	Vector2f normA;
	Vector2f normB;
	float penB = -FLT_MAX;
	int indexA;
	int indexB;

	//project both polygons onto all normals (of the terrain)

	for (unsigned int i = 0; i < Anormals.size(); i++) {
		Vector2f axis = Anormals[i];

		Vector2f ARange = A.projectPolygon(axis);
		Vector2f BRange = B.projectPolygon(axis);

		//note that penetration will be negative if the shapes overlap

		float penetration = intervalDistance(ARange, BRange);
		if (penetration >= 0) {
			return false; //early out
		}
		if (penetration > penA) {
			penA = penetration;
			normA = axis;
			indexA = i;
		}
		else if (penetration == penA) {
			Vector2f reletiveVelocity = pair->B->velocity - pair->A->velocity;
			float vel1 = dotProduct(reletiveVelocity, normA);
			float vel2 = dotProduct(reletiveVelocity, axis);
			if (vel2 < vel1) {
				penA = penetration;
				normA = axis;
				indexA = i;
			}

		}
	}

	for (unsigned int i = 0; i < Bnormals.size(); i++) {
		Vector2f axis = Bnormals[i];

		Vector2f ARange = A.projectPolygon(axis);
		Vector2f BRange = B.projectPolygon(axis);

		//note that penetration will be negative if the shapes overlap

		float penetration = intervalDistance(ARange, BRange);
		if (penetration >= 0) {
			return false; //early out
		}
		if (penetration > penB) {
			penB = penetration;
			normB = axis;
			indexB = i;
		}
		else if (penetration == penB) {
			Vector2f reletiveVelocity = pair->B->velocity - pair->A->velocity;
			float vel1 = dotProduct(reletiveVelocity, normB);
			float vel2 = dotProduct(reletiveVelocity, axis);
			if (vel2 < vel1) {
				penB = penetration;
				normB = axis;
				indexB = i;
			}

		}
	}

	//determine reference polygon

	int refIndex;
	bool flip;

	TransformComp* reference;
	TransformComp* incident;

	if (biasGreaterThan(penA, penB))
	{
		reference = pair->A->masterObj->transform;
		incident = pair->B->masterObj->transform;
		refIndex = indexA;
		flip = false;
	}

	else
	{
		reference = pair->B->masterObj->transform;
		incident = pair->A->masterObj->transform;
		refIndex = indexB;
		flip = true;
	}

	Vector2f incidentFace[2];
	FindIncidentFace(incidentFace, &reference->shape, &incident->shape, refIndex);


	Vector2f v1 = reference->shape.points[refIndex];
	refIndex = refIndex + 1 == reference->shape.points.size() ? 0 : refIndex + 1;
	Vector2f v2 = reference->shape.points[refIndex];

	Vector2f ref = normalize(v2 - v1);

	float offset = dotProduct(ref, v1);
	vector<Vector2f> cpoints = clip(incidentFace[0], incidentFace[1], ref, offset);
	if (cpoints.size() < 2) return false;

	float offset2 = dotProduct(ref, v2);
	cpoints = clip(cpoints[0], cpoints[1], -ref, -offset2);
	if (cpoints.size() < 2) return false;

	Vector2f refNorm = Vector2f(ref.y, -ref.x);
	if (flip) refNorm = refNorm * -1.0f;

	float maxVal = max(dotProduct(refNorm, incidentFace[0]), dotProduct(refNorm, incidentFace[1]));

	pair->contacts = cpoints;
	pair->contactCount = (int)pair->contacts.size();

	if (dotProduct(refNorm, pair->contacts[1]) - maxVal < 0.0f) {

		pair->contacts.erase(pair->contacts.begin() + 1);
		pair->contactCount--;
	}

	if (dotProduct(refNorm, pair->contacts[0]) - maxVal < 0.0f) {
		pair->contacts.erase(pair->contacts.begin() + 0);
		pair->contactCount--;
	}

	cout << pair->contactCount << endl;

	pair->normal = flip ? -refNorm : refNorm;
	pair->penetration = max(penA, penB);
	pair->penetration -= 0.05f;
	return true;
}

bool PhysicsEngine::enhancedSAT(collision* pair) {
	float penetration;
	Vector2f normal;

	TransformComp* A = pair->A->masterObj->transform;
	TransformComp* B = pair->B->masterObj->transform;

	// Check for a separating axis with A's face planes
	int faceA;
	float penetrationA = FindAxisLeastPenetration(&faceA, pair);
	if (penetrationA >= 0.0f)
		return false;

	// Check for a separating axis with B's face planes
	int faceB;
	float penetrationB = FindAxisLeastPenetration(&faceB, pair);
	if (penetrationB >= 0.0f)
		return false;

	int referenceIndex;
	bool flip; // Always point from a to b

	TransformComp* RefPoly; // Reference
	TransformComp* IncPoly; // Incident

	// Determine which shape contains reference face
	if (biasGreaterThan(penetrationA, penetrationB))
	{
		RefPoly = A;
		IncPoly = B;
		referenceIndex = faceA;
		flip = false;
	}

	else
	{
		RefPoly = B;
		IncPoly = A;
		referenceIndex = faceB;
		flip = true;
	}

	// World space incident face
	Vector2f incidentFace[2];
	FindIncidentFace(incidentFace, &RefPoly->shape, &IncPoly->shape, referenceIndex);

	// Setup reference face vertices
	Vector2f v1 = RefPoly->shape.points[referenceIndex];
	referenceIndex = referenceIndex + 1 == RefPoly->shape.points.size() ? 0 : referenceIndex + 1;
	Vector2f v2 = RefPoly->shape.points[referenceIndex];

	// Transform vertices to world space
	//v1 = RefPoly->u * v1 + RefPoly->position;
	//v2 = RefPoly->u * v2 + RefPoly->position;

	// Calculate reference face side normal in world space
	Vector2f sidePlaneNormal = Vector2f(v2.x - v1.x, v2.y - v1.y);
	sidePlaneNormal = normalize(sidePlaneNormal);

	// Orthogonalize
	Vector2f refFaceNormal(sidePlaneNormal.y, -sidePlaneNormal.x);

	// ax + by = c
	// c is distance from origin
	float refC = dotProduct(refFaceNormal, v1);
	float negSide = -dotProduct(sidePlaneNormal, v1);
	float posSide = dotProduct(sidePlaneNormal, v2);

	// Clip incident face to reference face side planes
	if (Clip(Vector2f(-sidePlaneNormal.x, -sidePlaneNormal.y), negSide, incidentFace) < 2)
		return false; // Due to floating point error, possible to not have required points

	if (Clip(sidePlaneNormal, posSide, incidentFace) < 2)
		return false; // Due to floating point error, possible to not have required points

	// Flip
	normal = flip ? Vector2f(refFaceNormal.x, refFaceNormal.y) : Vector2f(-refFaceNormal.x, -refFaceNormal.y);
	//normalize(normal);

	// Keep points behind reference face
	int cp = 0; // clipped points behind reference face
	float separation = dotProduct(refFaceNormal, incidentFace[0]) - refC;
	if (separation <= 0.0f)
	{
		pair->contacts[cp] = incidentFace[0];
		penetration = -separation;
		++cp;
	}
	else {
		penetration = 0;
	}

	separation = dotProduct(refFaceNormal, incidentFace[1]) - refC;
	if (separation <= 0.0f)
	{
		pair->contacts[cp] = incidentFace[1];

		penetration += -separation;
		++cp;

		// Average penetration
		penetration /= (float)cp;
	}

	//pair->penetration = penetration;
	pair->penetration = max(penetrationA, penetrationB);
	pair->normal = normal;

	pair->contactCount = cp;
	return true;

}

bool PhysicsEngine::biasGreaterThan(float a, float b)
{
	const float k_biasRelative = 0.95f;
	const float k_biasAbsolute = 0.01f;
	return a >= b * k_biasRelative + a * k_biasAbsolute;
}

void PhysicsEngine::resolveCollision(collision* pair) {
	RigidBody* A = pair->A;
	RigidBody* B = pair->B;

	// Calculate relative velocity
	Vector2f reletiveVelocity = B->velocity - A->velocity;


	// Calculate relative velocity in terms of the normal direction
	float velAlongNormal = dotProduct(reletiveVelocity, pair->normal);

	// Do not resolve if velocities are separating
	if (velAlongNormal > 0) //should be  a >, but works with < (vel should be positive)
		return;

	// Calculate restitution
	float e = std::min(A->mat.restitution, B->mat.restitution);

	// Calculate impulse scalar
	float j = -(1 + e) * velAlongNormal;
	j /= (A->mat.massInv + B->mat.massInv);

	// Apply impulse
	Vector2f impulse = pair->normal * j;

	A->force -= A->mat.massInv * impulse;
	//A->angularVelocity += A->mat.inertInv * CrossProduct(contactVector, impulse);
	B->force += B->mat.massInv * impulse;

	applyFriction(pair, j);
	positionalCorrection(pair);

	return;
}


void PhysicsEngine::rotationalResolution(collision* pair) {
	RigidBody* A = pair->A;
	RigidBody* B = pair->B;


	for (int i = 0; i < pair->contactCount; i++) {

		Vector2f ra = pair->contacts[i] - A->masterObj->transform->position;
		Vector2f rb = pair->contacts[i] - B->masterObj->transform->position;

		// Calculate relative velocity
		Vector2f reletiveVelocity = B->velocity + CrossProduct(B->angularVelocity, rb) - A->velocity - CrossProduct(A->angularVelocity, ra);


		// Calculate relative velocity in terms of the normal direction
		float velAlongNormal = dotProduct(reletiveVelocity, pair->normal);

		// Do not resolve if velocities are separating
		if (velAlongNormal > 0) //should be  a >, but works with < (vel should be positive)
			return;

		float raxn = CrossProduct(ra, pair->normal);
		float rbxn = CrossProduct(rb, pair->normal);
		float invMassSum = A->mat.massInv + B->mat.massInv + raxn*raxn * A->mat.inertInv + rbxn*rbxn * B->mat.inertInv;

		// Calculate restitution
		float e = std::min(A->mat.restitution, B->mat.restitution);

		// Calculate impulse scalar
		float j = -(1 + e) * velAlongNormal;
		j /= invMassSum;
		j /= (float)pair->contactCount;

		// Apply impulse
		Vector2f impulse = pair->normal * j;

		A->force -= A->mat.massInv * impulse;
		A->angularVelocity -= A->mat.inertInv * 4 * CrossProduct(ra, impulse);
		B->force += B->mat.massInv * impulse;
		B->angularVelocity += B->mat.inertInv * 4 * CrossProduct(rb, impulse);

		//applyFriction(pair, j);
	}
	
	//cout << B->force.y << endl;

	positionalCorrection(pair);

	return;
}


void PhysicsEngine::positionalCorrection(collision* pair) {
	RigidBody* A = pair->A;
	RigidBody* B = pair->B;
	const float percent = 1.0f; // usually 20% to 80%
	const float slop = 0.00f;// usually 0.01 to 0.1
	float correctionFloat = std::max(-pair->penetration - slop, 0.0f) / (A->mat.massInv + B->mat.massInv) * percent;
	Vector2f correction = correctionFloat * pair->normal;
	A->masterObj->transform->move(-A->mat.massInv * correction, 0.0f);
	B->masterObj->transform->move(B->mat.massInv * correction, 0.0f);
}

void PhysicsEngine::applyFriction(collision* pair, float j) {
	RigidBody* A = pair->A;
	RigidBody* B = pair->B;

	// Calculate relative velocity
	Vector2f reletiveVelocity = B->velocity - A->velocity;
	Vector2f tangent = reletiveVelocity - dotProduct(reletiveVelocity, pair->normal) * pair->normal;
	tangent = normalize(tangent);
	float jt = -dotProduct(reletiveVelocity, tangent);
	jt /= (A->mat.massInv + B->mat.massInv);

	float mu = Distance(Vector2f(A->mat.staticFriction, 0), Vector2f(0, -B->mat.staticFriction));

	Vector2f friction;

	if (abs(jt) < j * mu) {
		friction = jt * tangent;
	}
	else {
		float dynamicFr = Distance(Vector2f(A->mat.dynamicFriction, 0), Vector2f(0, -B->mat.dynamicFriction));
		friction = -j * tangent * dynamicFr;
	}

	//float dynamicFr = Distance(Vector2f(A->mat.dynamicFriction, 0), Vector2f(0, -B->mat.dynamicFriction));
	//friction = -j * tangent * dynamicFr;

	if (abs(friction.x) > 105 || abs(friction.y) > 105) {
		cout << friction.x << " " << friction.y << endl;
	}

	A->force -= A->mat.massInv * friction;
	B->force += B->mat.massInv * friction;
}



pair<Vector2f, Vector2f> PhysicsEngine::findFeature(polygon polygon, Vector2f normal) {

	float max = -FLT_MAX;
	int index = 0;

	for (int i = 0; i < polygon.points.size(); i++) {
		float projection = dotProduct(normal, polygon.points[i]);
		if (projection > max) {
			max = projection;
			index = i;
		}
	}

	Vector2f vertex = polygon.points.at(index);
	Vector2f v1;
	if (index == 0) {
		v1 = polygon.points.at(polygon.points.size() - 1);
	}
	else {
		v1 = polygon.points.at(index - 1);
	}

	Vector2f v2;
	if (index == polygon.points.size() - 1) {
		v2 = polygon.points.at(1);
	}
	else {
		v2 = polygon.points.at(index + 1);
	}

	Vector2f leftFace = normalize(vertex - v2);
	Vector2f rightFace = normalize(vertex - v1);

	if (dotProduct(normal, rightFace) >= dotProduct(normal, leftFace)) {
		pair<Vector2f, Vector2f> rightEdge(vertex, v1);
		return rightEdge;
	}
	else {
		pair<Vector2f, Vector2f> leftEdge(vertex, v2);
		return leftEdge;
	}
}

vector<Vector2f> PhysicsEngine::clip(Vector2f min, Vector2f max, Vector2f normal, float offset) {
	vector<Vector2f> clippedPoints;
	float clip1 = dotProduct(min, normal) - offset;
	float clip2 = dotProduct(max, normal) - offset;
	if (clip1 >= 0) clippedPoints.push_back(min);
	if (clip2 >= 0) clippedPoints.push_back(max);

	//check opposing sides
	if (clip1 * clip2 < 0.0) {
		Vector2f edge = max - min;
		float u = clip1 / (clip1 - clip2);
		edge *= u;
		edge += min;
		clippedPoints.push_back(edge);
	}

	return clippedPoints;
}

vector<Vector2f> PhysicsEngine::collisionPoints(collision* pair) {
	//routines for determining contact Points

	std::pair<Vector2f, Vector2f> bestA = findFeature(pair->A->masterObj->transform->shape, pair->normal);
	std::pair<Vector2f, Vector2f> bestB = findFeature(pair->B->masterObj->transform->shape, -pair->normal);


	//find reference and incedent faces

	std::pair<Vector2f, Vector2f> reference, incident;
	bool flip = false;
	if (abs(dotProduct(bestA.second - bestA.first, pair->normal)) <= abs(dotProduct(bestB.second - bestB.first, pair->normal))) {
		reference = bestA;
		incident = bestB;
	}
	else {
		reference = bestB;
		incident = bestA;
		// we need to set a flag indicating that the reference
		// and incident edge were flipped so that when we do the final
		// clip operation, we use the right edge normal
		flip = true;
	}

	Vector2f refv = reference.first - reference.second;
	refv = normalize(refv);
	float offset1 = dotProduct(refv, reference.first);
	vector<Vector2f> clippedPoints = clip(incident.first, incident.second, refv, offset1);
	if (clippedPoints.size() < 2) return vector<Vector2f>();

	float offset2 = dotProduct(refv, reference.second);
	vector<Vector2f> clippedPoints2 = clip(clippedPoints[0], clippedPoints[1], -refv, -offset2);
	clippedPoints.insert(clippedPoints.end(), clippedPoints2.begin(), clippedPoints2.end());
	if (clippedPoints.size() < 2) return vector<Vector2f>();

	Vector2f refNorm = CrossProduct(reference.second - reference.first, -1.0f);
	if (flip) refNorm *= -1.0f;

	float max = std::max(dotProduct(refNorm, reference.first), dotProduct(refNorm, reference.second));

	int reduce = 0;

	if (dotProduct(refNorm, clippedPoints[0]) - max < 0.0f) {
		clippedPoints.erase(clippedPoints.begin());
		reduce++;
	}
	if (dotProduct(refNorm, clippedPoints[1 - reduce]) - max < 0.0f) {
		clippedPoints.erase(clippedPoints.begin() + 1 - reduce);
	}

	return clippedPoints;
}


float PhysicsEngine::FindAxisLeastPenetration(int *faceIndex, collision* pair)
{

	polygon A = pair->A->masterObj->transform->shape;
	polygon B = pair->B->masterObj->transform->shape;

	float bestDistance = -FLT_MAX;
	int bestIndex;

	for (int i = 0; i < A.points.size(); ++i)
	{
		// Retrieve a face normal from A
		Vector2f n = A.normals[i];

		// Retrieve support point from B along -n
		Vector2f s = B.getSupport(Vector2f(-n.x, -n.y));

		// Retrieve vertex on face from A, transform into
		// B's model space
		Vector2f v = A.points[i];

		// Compute penetration distance (in B's model space)
		float d = dotProduct(n, Vector2f(s.x - v.x, s.y - v.y));

		// Store greatest distance
		if (d > bestDistance)
		{
			bestDistance = d;
			bestIndex = i;
		}
	}

	*faceIndex = bestIndex;
	return bestDistance;
}

void PhysicsEngine::FindIncidentFace(Vector2f *v, polygon* RefPoly, polygon* IncPoly, int referenceIndex)
{
	Vector2f referenceNormal = RefPoly->normals[referenceIndex];

	// Find most anti-normal face on incident polygon
	int incidentFace = 0;
	float minDot = FLT_MAX;
	for (int i = 0; i < IncPoly->points.size(); ++i)
	{
		float dot = dotProduct(referenceNormal, IncPoly->normals[i]);
		if (dot < minDot)
		{
			minDot = dot;
			incidentFace = i;
		}
	}

	// Assign face vertices for incidentFace
	v[0] = IncPoly->points[incidentFace];
	incidentFace = incidentFace + 1 >= IncPoly->points.size() ? 0 : incidentFace + 1;
	v[1] = IncPoly->points[incidentFace];
}

int PhysicsEngine::Clip(Vector2f n, float c, Vector2f *face)
{
	int sp = 0;
	Vector2f out[2] = {
		face[0],
		face[1]
	};

	// Retrieve distances from each endpoint to the line
	// d = ax + by - c
	float d1 = dotProduct(n, face[0]) - c;
	float d2 = dotProduct(n, face[1]) - c;

	// If negative (behind plane) clip
	if (d1 <= 0.0f) out[sp++] = face[0];
	if (d2 <= 0.0f) out[sp++] = face[1];

	// If the points are on different sides of the plane
	if (d1 * d2 < 0.0f) // less than to ignore -0.0f
	{
		// Push interesection point
		float alpha = d1 / (d1 - d2);
		out[sp] = face[0] + alpha * (face[1] - face[0]);
		//out[sp] = Vector2f(face[0].x + alpha * (face[1].x - face[0].x), face[0].y + alpha * (face[1].y - face[0].y));
		++sp;
	}

	// Assign our new converted values
	face[0] = out[0];
	face[1] = out[1];

	return sp;
}

void PhysicsEngine::generateContacts(collision* pair) {

}
