#include "VxFont.h"


/*
void VoxieBox::debugCustomFont(int xpos, int ypos, int customFontIndex, const char* fmt, ...)
{


	int i = customFontIndex;
	tiletype src;
	va_list arglist;
	int c, xo, yo;
	char st[2048], * cptr;

	int s = 0;

	if ((!fmt) || !(customFontInit[i])) return;
	va_start(arglist, fmt);
	_vsnprintf(st, sizeof(st), fmt, arglist);
	va_end(arglist);

	src.x = customFont[i].x; src.y = customFont[i].y / 96; src.p = customFont[i].p;
	xo = 0; yo = 0;

	for (cptr = st; cptr[0]; cptr++)
	{
		c = (int)cptr[0];
		if ((c < 32) || (c >= 128))
		{
			if ((c == '\r') || (c == '\n')) { xo -= customFont[i].x * s; s = 0; yo += src.y; }
			else if (c == '\t') xo += customFont[i].x * 3;
			else if (c == '\b') xo += (customFont[i].x >> 1);
			continue;
		}
		src.f = (INT_PTR)((int)(c - 32) * src.y * customFont[i].p + customFont[i].f);
		this->debugDrawTile(&src, xo + xpos, yo + ypos + (*(char*)src.f));
		xpos += customFont[i].x;
		s += 1;
	}


*/

VxFont::VxFont(IVoxieBox* voxieBoxPtr, char* fontFolder)
{
	this->voxiePtr = voxieBoxPtr;
	strcpy(this->fontFolder, fontFolder);

}

VxFont::VxFont()
{
}

VxFont::~VxFont()
{
}

void VxFont::calcExtents(char value)
{
	
	char filebuff[MAX_PATH];
	
	int charInt = 72;//(int)value;
	strcpy(filebuff, this->fontFolder);
	strcat(filebuff, (char*)"/");

	sprintf(filebuff, (char*)"%s%d.obj", filebuff, charInt);
	
	
	

	fileFound = voxiePtr->drawModelGetExtents(filebuff, &fontExtents, modelFlags);
	forceScaleAmount = fontExtents.sc;
	extentsInited = fileFound;

}

void VxFont::draw(point3d *pos, float size, float hAngle, float vAngle, float twist, int col, const char* fmt, ...)
{
	if (voxiePtr == nullptr || voxiePtr == 0) return;
	if ((!fmt) ) return;
	va_list arglist;

	point3d pp{ pos->x, pos->y, pos->z };
	point3d rVec{ 1 * size, 0, 0 };
	point3d dVec{ 0, 1 * size, 0 };
	point3d fVec{ 0 ,0, 1 * size };
	char st[2048], * cptr;
	char filebuff[MAX_PATH];
	int charInt = 64;
	int c = 0;
	int s = 0;
	float f = 1; // forcescale amount set to 1 if forceScale isn't being used
	point3d offset{ 0, 0, 0 };


	if (!extentsInited) {
		calcExtents('H');
	}

	/*
	strcpy(filebuff, this->fontFolder);
	strcat(filebuff, (char*)"/");
	sprintf(filebuff, (char*)"%s%d.obj", filebuff, charInt);
	*/

	float ox = rVec.x * textSpacingOffset;
	float oy = dVec.y * textSpacingYOffset;

	va_start(arglist, fmt);
	_vsnprintf(st, sizeof(st), fmt, arglist);
	va_end(arglist);

	//voxiePtr->drawSphere(pp, 0.1, 1, 0x00ff00);


	for (cptr = st; cptr[0]; cptr++)
	{
		c = (int)cptr[0];

		if ((c < 32) || (c >= 128))
		{
			if ((c == '\r') || (c == '\n')) { pp.x -= ox * s; s = 0; pp.y += oy; }
			else if (c == '\t') { pp.x += ox * 3; s += 3; }
		//	else if (c == '\b') { pp.x += (ox >> 1);
			continue;
		}
		

		if (!forceScale) forceScaleAmount = 0;

		if (forceScale && extentsInited) {

			f = sqrt(double(rVec.x) * double(rVec.x) + double(rVec.y) * double(rVec.y) + double(rVec.z) * double(rVec.z)) * fontExtents.sc * .5f/*for avg below*/;
			pp.x -= (fontExtents.x0 + fontExtents.x1) * f;
			pp.y -= (fontExtents.z0 + fontExtents.z1) * f;
			pp.z += (fontExtents.y0 + fontExtents.y1) * f;

		}

		strcpy(filebuff, this->fontFolder);
		strcat(filebuff, (char*)"/");
		sprintf(filebuff, (char*)"%s%d.obj", filebuff, c);
		voxiePtr->drawSphere(pp, 0.025, 1, 0x00ff00);
//		voxiePtr->drawModel(filebuff, &pp, &rVec, &dVec, &fVec, col);

		//pp.x = 0; 
		//pp.y = 0;
		//pp.z = 0;

		voxiePtr->drawModelExt(filebuff, &pp, &rVec, &dVec, &fVec, col, forceScaleAmount, f, modelFlags);
	//	voxiePtr->drawModelExt("font/ant.stl", &pp, &rVec, &dVec, &fVec, col, forceScaleAmount, f, modelFlags);


//		voxiePtr->drawModelExt(filebuff, &pp, &rr, &dd, &ff, col, 0, 0, 0);
		pp.x += ox;
		s++;
	}


	
	//voxiePtr->drawSphere(pp, 0.1, 1, 0xff0000);
//	i= voxiePtr->drawModel("font/64.obj", &pp, &rr, &dd, &ff, 0xff00ff);
//	i = voxiePtr->drawModel(filebuff, &pp, &rr, &dd, &ff, 0x00ff00);



}

void VxFont::report(int posX, int posY)
{
	if (voxiePtr == nullptr || voxiePtr == 0) return;

	voxiePtr->debugText(posX, posY, 0x0080ff, -1, "VxFont\nVoxiePtr %d\nFont Folder %s\nextents: File : %d | inited : %d  SC %1.2f", this->voxiePtr, this->fontFolder, this->fileFound, this->extentsInited, this->fontExtents.sc);


}
