#pragma once

#include "VxCpp.h"
/** \file vxInterfaces.h
 *
 * VX++ interface header contains interface definitions for creating VX++ related classes. 
 * This header is essential to developing VX++ applications using the VxCpp.DLL.
 * This file is kept separate to allow easy integration...
 *
 */

//! IVoxiePtr classes which inherit this interface require access to IVoxieBox pointer
/**
 * Classes which need the voxie pointer object will usually use variables or functions from the VoxieBox object
 * Usually when these classes are constructed the IVoxieBox pointer should be set.
 */

class IVoxiePtr {

public:
	virtual void setIVoxieBoxPtr(IVoxieBox * voxiePtr) { this->voxiePtr = voxiePtr; }
	virtual IVoxieBox *getIVoxieBoxPtr() { return voxiePtr; }

protected:
	IVoxieBox *voxiePtr = 0;

};

//! IActive interface allows a class to be 'active'. Set to true of false. 
class IActive {

public:

	bool isActive() { return active; };
	void setActive(bool option) {
		active = option;
	}
	bool getActive() {
		return active;
	}


protected:
	bool active = true;

};

//! IDrawable classes which inherit are 'drawable' interface can be added to the 'drawable' vector and drawn automatically by the VoxieBox class. 
class IDrawable: public IVoxiePtr {

public:
	virtual void draw() { ; }
	bool isDrawable() { 
		return drawable;
		};
	void setDrawable(bool option) {
		drawable = option;
	};
	bool getDrawable() {
		return drawable;
	}
protected:
	bool drawable = true;
};

//! IBreathable classes which inherit this interface can be added to the 'breathable' vector and updated automatically by the VoxieBox class during the breath() function call.
class IBreathable: public IVoxiePtr {

public:

	virtual void onBreath() { ; };
	bool isBreathable() {
		return breathable;
	};
	void setBreathable(bool option) {
		breathable = option;
	};
	bool getBreathable() {
		return breathable;
	}

protected:
	bool breathable = true;

};

//! Interface used to create 2D UIs
class IUI2D {

public:
	void moveTo(int newPosX, int newPosY) { posX = newPosX; posY = newPosY; }
	int  getPosX() { return posX; }
	int  getPosY() { return posY; }
	int  getGroupID() { return groupID; }
	void setGroupID(int newGroupID) { groupID = newGroupID;  }

protected:
	int posX = 0, posY = 0, groupID = -1;

};



