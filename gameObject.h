#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;


class gameObject : public Sprite {
public:
	gameObject();
	gameObject(Vector2f gamePos);
	gameObject(Texture &t, Vector2f gamePosition = Vector2f());

	Vector2f getGamePos();
	void setGamePos(Vector2f gamePosition);
	int getGravity();
	void setGravity(int gravity);
	Vector2f getVelocity();
	void setVelocity(Vector2f velocity);
	int getDirection();
    void setDirection(int direction);
	int getAnimationRow();
    void setAnimationRow(int row);
	int getAnimationColumn();
    void setAnimationColumn(int column);
	float getDt();
	void setDt(float dt);

	float getWalkAcc();
	float getMaxWalkSpd();
	float getRunAcc();
	float getMaxRunSpd();
	float getStopAcc();
	void setWalkAcc(float walkAcceleration);
	void setMaxWalkSpd(float maxWalkSpeed);
	void setRunAcc(float runAcceleration);
	void setMaxRunSpd(float maxRunSpeed);
	void setStopAcc(float stopAcceleration);

	int getGameState();
	void setGameState(int gameState);
	float getRotationSpeed();
	void setRotationSpeed(float roatationSpeed);

	

	bool isIntersecting(RectangleShape r);
    bool isIntersecting(Vector2f gamePos);
    RectangleShape getHitbox();

	enum movementUpdateType { none = 0, forwardWalk = 1, forwardRun = 2, backwardWalk = -1, backwardRun = -2, dontUpdate = NULL };
    void undoMovementUpdate(float cameraOffset);
	void movementUpdate(float deltat, float cameraOffset, movementUpdateType e = dontUpdate);

private:
	Vector2f myGamePos;
	Vector2f myVelocity;
	int myGravity, myDirection, myAniRow, myAniColumn, myGameState;
	float myDt, myWalkAcc, myMaxWalkSpd, myRunAcc, myMaxRunSpd, myStopAcc, myRotationSpeed;
};

gameObject::gameObject() {
	myGamePos = Vector2f();
	myGravity = 0;
	myVelocity = Vector2f();
	myDirection = 1;
	setScale(3, 3);
	myDt = 0;
	myWalkAcc = 0;
	myMaxWalkSpd = 0;
	myRunAcc = 0;
	myMaxRunSpd = 0;
	myStopAcc = 0;
	myAniRow = 0;
    myAniColumn = 0;
	myGameState = 0;
	myRotationSpeed = 0;
}

gameObject::gameObject(Vector2f gamePosition) {
	myGravity = 0;
	myVelocity = Vector2f();
	myGamePos = gamePosition;
	myDirection = 1;
	setScale(3, 3);
	myDt = 0;
	myWalkAcc = 0;
	myMaxWalkSpd = 0;
	myRunAcc = 0;
	myMaxRunSpd = 0;
	myStopAcc = 0;
	myAniRow = 0;
    myAniColumn = 0;
	myGameState = 0;
	myRotationSpeed = 0;
}

gameObject::gameObject(Texture &t, Vector2f gamePosition) {
	setTexture(t);
	myGravity = 0;
	myVelocity = Vector2f();
	myGamePos = gamePosition;
	myDirection = 1;
	setScale(3, 3);
	myWalkAcc = 0;
	myMaxWalkSpd = 0;
	myRunAcc = 0;
	myMaxRunSpd = 0;
	myStopAcc = 0;
	myAniRow = 0;
    myAniColumn = 0;
	myGameState = 0;
	myRotationSpeed = 0;
}


//
//sets and gets

Vector2f gameObject::getGamePos() {
	return myGamePos;
}
void gameObject::setGamePos(Vector2f gamePosition) {
	myGamePos = gamePosition;
}
int gameObject::getGravity() {
	return myGravity;
}
void gameObject::setGravity(int gravity) {
	myGravity = gravity;
}
Vector2f gameObject::getVelocity() {
	return myVelocity;
}
void gameObject::setVelocity(Vector2f velocity) {
	myVelocity = velocity;
}
int gameObject::getDirection() {
	return myDirection;
}
int gameObject::getAnimationRow() {
	return myAniRow;
}
int gameObject::getAnimationColumn() {
	return myAniColumn;
}
float gameObject::getDt() {
	return myDt;
}
void gameObject::setDt(float dt) {
	myDt = dt;
}
float gameObject::getWalkAcc() {
	return myWalkAcc;
}
float gameObject::getMaxWalkSpd() {
	return myMaxWalkSpd;
}
float gameObject::getRunAcc() {
	return myRunAcc;
}
float gameObject::getMaxRunSpd() {
	return myMaxRunSpd;
}
float gameObject::getStopAcc() {
	return myStopAcc;
}
void gameObject::setWalkAcc(float walkAcceleration) {
	myWalkAcc = walkAcceleration;
}
void gameObject::setMaxWalkSpd(float maxWalkSpeed) {
	myMaxWalkSpd = maxWalkSpeed;
}
void gameObject::setRunAcc(float runAcceleration) {
	myRunAcc = runAcceleration;
}
void gameObject::setMaxRunSpd(float maxRunSpeed) {
	myMaxRunSpd = maxRunSpeed;
}
void gameObject::setStopAcc(float stopAcceleration) {
	myStopAcc = stopAcceleration;
}
int gameObject::getGameState() {
	return myGameState;
}
void gameObject::setGameState(int gameState) {
	myGameState = gameState;
}
void gameObject::setDirection(int direction){
    myDirection = direction;
}
void gameObject::setAnimationRow(int row){
    myAniRow = row;
}
void gameObject::setAnimationColumn(int column){
    myAniColumn = column;
}
float gameObject::getRotationSpeed() {
	return myRotationSpeed;
}
void gameObject::setRotationSpeed(float roatationSpeed) {
	myRotationSpeed = roatationSpeed;
}



bool gameObject::isIntersecting(RectangleShape r) {
	Vector2f p[4];
	p[0] = Vector2f(myGamePos.x, myGamePos.y);
	p[1] = Vector2f(myGamePos.x + abs(getTextureRect().width) * getScale().x, myGamePos.y);
	p[2] = Vector2f(myGamePos.x, myGamePos.y + abs(getTextureRect().height)* getScale().y);
	p[3] = Vector2f(myGamePos.x + abs(getTextureRect().width) * getScale().x, myGamePos.y + abs(getTextureRect().height) * getScale().y);
	int i;
	for (i = 0; i <= 3; i++) {
		if (r.getPosition().x <= p[i].x &&
			r.getPosition().x + r.getSize().x >= p[i].x &&
			r.getPosition().y <= p[i].y &&
			r.getPosition().y + r.getSize().y >= p[i].y)
			return true;
	}
	return false;
}

bool gameObject::isIntersecting(Vector2f gamePos) {
    if (myGamePos.x <= gamePos.x &&
        myGamePos.x + abs(getTextureRect().width) * getScale().x >= gamePos.x &&
        myGamePos.y <= gamePos.y &&
        myGamePos.y + abs(getTextureRect().height) * getScale().y)
        return true;
	return false;
}


void gameObject::movementUpdate(float deltat, float cameraOffset, movementUpdateType e) {
	myDt = deltat;

	if (e == forwardRun) {
		myVelocity.x = myVelocity.x + myRunAcc * myDt;
		if (myVelocity.x > myMaxRunSpd) {
			myVelocity.x = myVelocity.x - myRunAcc * myDt - myStopAcc * myDt;
		}
	}
	if(e == forwardWalk) {
		myVelocity.x = myVelocity.x + myWalkAcc * myDt;
		if (myVelocity.x > myMaxWalkSpd) {
			myVelocity.x = myVelocity.x - myWalkAcc * myDt - myStopAcc * myDt;
		}
	}
	if (e == backwardRun) {
		myVelocity.x = myVelocity.x - myRunAcc * myDt;
		if (myVelocity.x < -1 * myMaxRunSpd) {
			myVelocity.x = myVelocity.x + myRunAcc * myDt + myStopAcc * myDt;
		}
	}
	if (e == backwardWalk){
		myVelocity.x = myVelocity.x - myWalkAcc * myDt;
		if (myVelocity.x < -1 * myMaxWalkSpd) {
			myVelocity.x = myVelocity.x + myWalkAcc * myDt + myStopAcc * myDt;
		}
	}
	if (e == none) {
		if (myVelocity.x > 0) {
			if (myVelocity.x - myStopAcc * myDt < 0)
				myVelocity.x = 0;
			else
				myVelocity.x = myVelocity.x - myStopAcc * myDt;
		}
		else if (myVelocity.x < 0) {
			if (myVelocity.x + myStopAcc * myDt > 0)
				myVelocity.x = 0;
			else
				myVelocity.x = myVelocity.x + myStopAcc * myDt;
		}
	}

	setRotation(getRotation() + myRotationSpeed * myDt);
	myVelocity.y = myVelocity.y + myGravity * myDt;

	if (myGamePos.x < 0) {
		myGamePos.x = 0;
	}

	myGamePos.x = myGamePos.x + myVelocity.x * myDt;
	myGamePos.y = myGamePos.y + myVelocity.y * myDt;
	setPosition(myGamePos.x - cameraOffset, myGamePos.y);
}

void gameObject::undoMovementUpdate(float cameraOffset) {//fix
	myGamePos.x = myGamePos.x - myVelocity.x * myDt;
	myGamePos.y = myGamePos.y - myVelocity.y * myDt;
	setPosition(myGamePos.x - cameraOffset, myGamePos.y);
}

RectangleShape gameObject::getHitbox() {
	RectangleShape r;
	r.setPosition(getGamePos());
	r.setSize(Vector2f(abs(getTextureRect().width) * getScale().x, abs(getTextureRect().height) * getScale().y));
	return r;
}

#endif