#pragma once

/*** 
 * VXFont an OBJ based 3D font for Voxon Photonics display 
 * 
 * fonts need to be OBJ files and named as their char represnetation
 * 
 * By Matthew Vecchio for Voxon
 */

#include "vxCpp.h"


class VxFont : IVoxiePtr, IDrawable 
{

	public:
		VxFont(IVoxieBox * voxieBoxPtr, char * fontFolder );
		VxFont();
		~VxFont();

		void calcExtents(char value);

		void setFontFolder(const char* filePath);
		char* getFontFolder();

		void draw(point3d *pos, float size, float hAngle, float vAngle, float twist, int col, const char* fmt, ...);
		void report(int posX, int posY);

	private:

		extents_t fontExtents = { 0 };
		bool extentsInited = false;

		IVoxieBox * voxiePtr = nullptr;
		char fontFolder[MAX_PATH] = { 0 }  ;
		float textSpacingOffset = 1;
		float textSpacingYOffset = 1.1;
		float forceScaleAmount = 0;
		int modelFlags = 0;
		bool forceScale = false ;
		int fileFound = 0;


};

