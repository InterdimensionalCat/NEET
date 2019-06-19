#include "stdafx.h"
#include "RigidBody.h"


RigidBody::RigidBody(string material) : Component("RigidBody")
{
	mat = generateMaterial(material);
}

RigidBody::~RigidBody()
{

}

