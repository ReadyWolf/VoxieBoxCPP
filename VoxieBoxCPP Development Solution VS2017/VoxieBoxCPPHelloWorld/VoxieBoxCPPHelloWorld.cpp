// CORE BARE BONES VERSION
/*
#include "vxCPP.h"

int main(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmdline, int ncmdshow)
{
	HINSTANCE _Notnull_ hVoxieDLL = LoadLibrary("vxCpp.dll");
	if (!hVoxieDLL) return 1;
	CREATE_VOXIEBOX pEntryFunction = (CREATE_VOXIEBOX)GetProcAddress(hVoxieDLL, (const char*)R"(CreateVoxieBoxObject)");
	if (pEntryFunction == 0) return 1;
	IVoxieBox* voxie = pEntryFunction();

	while (voxie->breath())
	{
		voxie->startFrame();
		voxie->showVPS();
		voxie->endFrame();
	}

	voxie->quitLoop();
	delete voxie;
	return 0;
}
*/

/************************************
* VxCpp Hello World Application
* (c) 2021-2023 Matthew Vecchio for Voxon.
*
* You may use this as a template to start creating your own volumetric applications.
*
*/

// VX++ APP HELLO WORLD EXAMPLE 
// You may use this as a template to start creating your own volumetric applications.


#include "pch.h"
#include "VxCpp.h"

int main(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmdline, int ncmdshow)
{
	// load in the VxCpp.dll so we can create the VoxieBox object...
	HINSTANCE _Notnull_ hVoxieDLL = LoadLibrary("VxCpp.dll");
	if (hVoxieDLL == NULL) return 1;
	// Access and call "CreateVoxieBoxObject" function from VxCpp.dll. The CreateVoxieBoxObject function creates a new VoxieBox object.
	CREATE_VOXIEBOX pEntryFunction = (CREATE_VOXIEBOX)GetProcAddress(hVoxieDLL, "CreateVoxieBoxObject");
	// Set a new IVoxieBox pointer to point to the entry function (the voxiebox object) now 'voxie' get access to the VoxieBox class
	IVoxieBox* voxie = pEntryFunction();

	// variables to setup text positions to display 'Hello World' -- feel free to delete this
	point3d textPos{ -0.9, -0.9, 0 };     // text positions x,y,z values
	point3d textWidth{ 0.1,  0, 0 };     // text rVector  x,y,z ... the x value determines the width of the text the other values deal with rotating text
	point3d textHeight{ 0, 0.15, 0 }; // text dVector  x,y,z ... the y value determines the height of the text the other values deal with rotating text

	float rotationAmount = 0;

	voxie->setBorder(true); // if true draws a border around the perimeter of the display

	// Update loop for program -- breath() -- is a complete volume sweep. Called once per volume.
	while (voxie->breath())
	{
		voxie->startFrame();   // The start of drawing the Voxieframe (all voxie draw calls need to be within this and the endFrame() function)

		voxie->drawText(&textPos, &textWidth, &textHeight, 0xffffff, "Hello World"); // draw text onto the volumetric display.

		voxie->debugText(35, 100, 0xffffff, -1, "Hello World On the Touch Screen!"); // draw text onto the secondary (touch) screen.


		

		// Draw Compass Demo... 
		voxie->getAspect();
		voxie_wind_t* vwl = voxie->getVoxieWindow();
		
	

		int i = 0, n = 0, j = 0;
		float r = vwl->aspr * .99;
		float rm = vwl->asprmin * 1.01;
		

	
			// Check if hardware is up/down or spinner  
			if (vwl->clipshape == 0) 	voxie->drawBox( -vwl->aspx + 1e-3f, -vwl->aspy + 1e-3f, -vwl->aspz, +vwl->aspx - 1e-3f, +vwl->aspy - 1e-3f, +vwl->aspz, 1, 0xffffff);
			else { // if spinner draw around the outside of the shape


				n = 64;
				for (j = -64; j <= 64; j++)
				{
					if (j == -62) j = 62;
					for (i = 0; i < n; i++)
					{
						voxie->drawLine(cos((float)(i + 0) * PI * 2.0 / (float)n) * (r), sin((float)(i + 0) * PI * 2.0 / (float)n) * (r), (float)j * vwl->aspz / 64.f,
							cos((float)(i + 1) * PI * 2.0 / (float)n) * (r), sin((float)(i + 1) * PI * 2.0 / (float)n) * (r), (float)j * vwl->aspz / 64.f, 0xffffff);

						if (vwl->asprmin == 0) continue;
						voxie->drawLine(cos((float)(i + 0) * PI * 2.0 / (float)n) * (rm), sin((float)(i + 0) * PI * 2.0 / (float)n) * (rm), (float)j * vwl->aspz / 64.f,
							cos((float)(i + 1) * PI * 2.0 / (float)n) * (rm), sin((float)(i + 1) * PI * 2.0 / (float)n) * (rm), (float)j * vwl->aspz / 64.f, 0xffffff);

					}
				}

				n = 32;
				for (i = 0; i < n; i++)
				{
					voxie->drawLine(cos((float)(i + 0) * PI * 2.0 / (float)n) * (r), sin((float)(i + 0) * PI * 2.0 / (float)n) * (r), -vwl->aspz,
						cos((float)(i + 0) * PI * 2.0 / (float)n) * (r), sin((float)(i + 0) * PI * 2.0 / (float)n) * (r), +vwl->aspz, 0xffffff);

			
				}


			}
			

















		voxie->showVPS(); //show VPS data and VxCpp.DLL version unto the touch screen.

		voxie->endFrame(); // the end of drawing to the volumetric display.
	}

	voxie->quitLoop(); // quitLoop() stops the hardware from physically moving and ends the breath() loop
	delete voxie;
	return 0;   // After the program quits the de-constructor for voxiebox frees the DLLs from memory if you wanted to do this manually call the voxie->Shutdown()
}


