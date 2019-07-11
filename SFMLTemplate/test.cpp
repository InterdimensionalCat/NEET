#pragma once
#include"stdafx.h"
#include"test.h"
#include "Scene.h"
#include "GameObject.h"
#include"ControlPoly.h"
#include "Terrain.h"

void inputTest(GameMouse* mouse, GameKeyboard* keyboard) {

	cout << "Keys Pressed:" << endl;

	for (Keyboard::Key key : keyboard->pressedKeys) {
		cout << key << endl;
	}

	cout << "Buttons Pressed:" << endl;

	for (Mouse::Button button : mouse->pressedButtons) {
		cout << button << endl;
	}
}

Scene* PhysicsTest() {
	Scene* testScene = new Scene("physics test");
	//vector<Vector2f> points = { Vector2f(0, 0), Vector2f(1, 0), Vector2f(1, 1), Vector2f(0, 1) };
	////testScene->createObject(new TestPolygon(Vector2f(125, 400 - 128), polygon(points), testScene, "test"));
	///*points = { Vector2f(0, 0), Vector2f(0.5f, 0.6f), Vector2f(1, 1), Vector2f(0, 1) };
	//testScene->createObject(new TestPolygon(Vector2f(200, 200), polygon(points), testScene, "test"));*/
	//points = { Vector2f(0, 0), /*Vector2f(0.3f,0.1f),*/ Vector2f(1, 1), Vector2f(0, 1) };
	//GameObject* ground = new TestPolygon(Vector2f(100, 500), polygon(points), testScene, "ground");
	//ground->transform->changeShape(points, Vector2f(100, 400), Vector2f(500, 400));
	//RigidBody* body = ground->getComponent<RigidBody>();
	//body->setGravity(false);
	////body->velocity += Vector2f(0, -25.0f);
	//testScene->createObject(ground);

	//points = { Vector2f(0, 1), /*Vector2f(0.3f,0.1f),*/ Vector2f(1, 0), Vector2f(1, 1) };
	//GameObject* ground2 = new TestPolygon(Vector2f(100, 500), polygon(points), testScene, "ground");
	//ground2->transform->changeShape(points, Vector2f(658, 400), Vector2f(500, 400));
	//RigidBody* body2 = ground2->getComponent<RigidBody>();
	//body2->setGravity(false);
	////body->velocity += Vector2f(0, -25.0f);
	//testScene->createObject(ground2);


	testScene->createObject(new ControlPoly(Vector2f(150, 150), testScene, 0.0f));
	testScene->createObject(new Terrain({ Vector2f(0, 0),/* Vector2f(1, 0),*/ Vector2f(1, 1), Vector2f(0, 1) }, Vector2f(0, 1080 - 300), Vector2f(1920,300), testScene, 0.0f));

	testScene->createObject(new Terrain({ Vector2f(0, 0), Vector2f(1, 0), /*Vector2f(1, 1),*/ Vector2f(0, 1) }, Vector2f(100, 0), Vector2f(1920 - 200, 100), testScene, 0.0f));


	testScene->createObject(new Terrain({ Vector2f(0, 0), Vector2f(1, 0), Vector2f(1, 1), Vector2f(0, 1) }, Vector2f(0, 0), Vector2f(100, 1080), testScene, 0.0f));
	testScene->createObject(new Terrain({ Vector2f(0, 0), Vector2f(1, 0), Vector2f(1, 1), Vector2f(0, 1) }, Vector2f(1920 - 100, 0), Vector2f(100, 1080), testScene, 0.0f));

	TransformComp* comp = new TransformComp();
	comp->changeShape({ Vector2f(0,0), Vector2f(0,1), Vector2f(1,1), Vector2f(1,0) }, Vector2f(100, 100), Vector2f(100, 100), 0.0f);
	TransformComp* comp1 = new TransformComp();
	comp1->changeShape({ Vector2f(0,0),  Vector2f(1,1), Vector2f(1,0) }, Vector2f(500, 500), Vector2f(100, 100), 0.0f);

	//boundTest(comp, comp1);


	return testScene;
}

void castTest() {
	A* atest = new B();
	if (B* btest = dynamic_cast<B*>(atest)) {
		cout << "success";
	}
}

void signArea() {

	vector<Vector2f> vec = { Vector2f(-1,-1), Vector2f(-1,1), Vector2f(1,1), };
	float a = signedArea(vec);
	cout << a << endl;
}

void centroidTest() {

	vector<Vector2f> vec = { Vector2f(0,0), Vector2f(1,1), Vector2f(0,1), };
	Vector2f a = centroid(vec);
	cout << a.x << " " << a.y << endl;
}

//void boundTest(TransformComp* A, TransformComp* B) {
//	A->localBounds();
//	B->localBounds();
//	A->localBounds(B->shape.points, B->position - A->position);
//	B->localBounds(A->shape.points, A->position - B->position);
//}