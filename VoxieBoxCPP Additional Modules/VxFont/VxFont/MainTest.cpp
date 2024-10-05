#include "vxCPP.h"
#include "VxFont.h"

int main(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmdline, int ncmdshow)
{
	HINSTANCE _Notnull_ hVoxieDLL = LoadLibrary("vxCpp.dll");
	CREATE_VOXIEBOX pEntryFunction = (CREATE_VOXIEBOX)GetProcAddress(hVoxieDLL, "CreateVoxieBoxObject");
	IVoxieBox* voxie = pEntryFunction();

	VxFont font3d(voxie, (char*)"Font");
	VxFont font3d2(voxie, (char*)"Font3");
	VxFont font3d3(voxie, (char*)"Font4");
	point3d pp = { -0.8, -0.8, 0 };
	voxie->setBorder(true);

	font3d.calcExtents('H');
	font3d2.calcExtents('H');
	font3d3.calcExtents('H');

	while (voxie->breath())
	{
		voxie->startFrame();

		/*
		char filebuff[20];

		strcpy(filebuff, (char*)"Font");
		strcat(filebuff, (char*)"/");

		strcat(filebuff, (char*)(char)64);

		strcat(filebuff, (char*)".obj");
		*/
	

		pp.z = 0;
		pp.y = -0.8;

		font3d.draw(&pp, 0.25, 0, 0, 0, 0xffffff, "Happy");

		pp.y += 0.5;

		pp.z += 0.2;
	
		font3d2.draw(&pp, 0.25, 0, 0, 0, 0xffffff, "Happy");

		pp.y += 0.3;

		pp.z += 0.2;

		font3d3.draw(&pp, 0.25, 0, 0, 0, 0xffffff, "Happy");


		pp.y += 0.3;
		
		font3d.draw(&pp, 0.06, 0, 0, 0, 0xffffff, "the quick brown fox jumps over\nthe lazy dog\n\nTHE QUICK BROWN FOX JUMPS\nOVER THE LAZY DOG");
		/*
	//	pp.y += 0.4;

		font3d.draw(&pp, 0.1, 0, 0, 0, 0xffffff, "the quick brown fox\njumps over the lazy dog\n\nTHE QUICK BROWN FOX\nJUMPS OVER THE LAZY DOG");
		*/

		voxie->showVPS();
		font3d.report(100, 100);
		voxie->endFrame();
	}

	voxie->quitLoop();
	delete voxie;
	return 0;
}
