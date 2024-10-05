#include "vxCPP.h"
#include "VxMenu.h"
#include <functional>

enum // menu names
{
	//Generic names
	MENU_UP, MENU_ONE, MENU_TWO, MENU_THREE, MENU_DOWN, MENU_VSLIDER_NAME, MENU_HSLIDER_NAME,
	MENU_GO, MENU_EDIT_DO_NAME, MENU_EDIT_NAME, MENU_TOGGLE_NAME, MENU_PICKFILE_NAME, MENU_LOAD, MENU_FILE_NAME, MENU_BROWSE,
	MENU_SAVE_FILE, MENU_SAVE_TEXTBOX,

};

// global values we are changing via the menu
float	gYHeightValue = 0.0f, gVSliderValue = 0;
int		gMenuChoiceValue = 0, gChoiceColourValue = 0x00ff00;
int		gHSliderValue = 0, gGoColour = 0xffffff;
int		gToggleValue = 0;
char*	gTestMessage = (char*)"Edit me using the menu!";


int main(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmdline, int ncmdshow)
{
	HINSTANCE _Notnull_ hVoxieDLL = LoadLibrary("vxCpp.dll");
	CREATE_VOXIEBOX pEntryFunction = (CREATE_VOXIEBOX)GetProcAddress(hVoxieDLL, "CreateVoxieBoxObject");
	IVoxieBox* voxie = pEntryFunction();


	/* 


	*/
	VxMenu menu;
	menu_data_t  lastUpdateTemp;

	point3d pp = { 0 }, rr = { 0 }, dd = { 0 }, ff = { 0 };
	int xPos  = 0, yPos = 0;

//	auto menu_update2 = std::mem_fn(&VxMenu::menu_update);
	//function<int(VxMenu&)> f = &VxMenu::menu_update;

	menu.reg_menu_function(voxie);

	//voxie->menuReset(menu.menu_update_ptr, 0, 0); // resets the menu tab
	voxie->menuAddTab((char*)"Test Name", 350, 0, 600, 500); // add a tab to the top of the menu be careful not to add more than 2 they will be hidden on the VX1's display

	// add text
	voxie->menuAddItem((char*)"Menu Text Example", 300, 20, 64, 64, 0, MENU_TEXT, 0, 0xFF0000, 0.0, 0.0, 0.0, 0.0, 0.0); // adding menu text

	// single button (MENU_BUTTON+3)
	voxie->menuAddItem((char*)"Up", 400, 50, 75, 50, MENU_UP, MENU_BUTTON_SINGLE, 0, 0x808000, 0.0, 0.0, 0.0, 0.0, 0.0);

	// group of butons (first button MENU_BUTTON+1, middle button just MENU_BUTTON, last button MENU_BUTTON+2)
	voxie->menuAddItem((char*)"1", 300, 110, 75, 50, MENU_ONE, MENU_BUTTON_FIRST, 0, 0xFF0000, 0.0, 0.0, 0.0, 0.0, 0.0);
	voxie->menuAddItem((char*)"2", 400, 110, 75, 50, MENU_TWO, MENU_BUTTON_MIDDLE, 1, 0x00FF00, 0.0, 0.0, 0.0, 0.0, 0.0);
	voxie->menuAddItem((char*)"3", 500, 110, 75, 50, MENU_THREE, MENU_BUTTON_LAST, 0, 0x0000FF, 0.0, 0.0, 0.0, 0.0, 0.0);

	// single button
	voxie->menuAddItem((char*)"Down", 400, 170, 75, 50, MENU_DOWN, MENU_BUTTON_SINGLE, 0, 0x008080, 0.0, 0.0, 0.0, 0.0, 0.0);

	// vertical slider the values at the end after the colour value are l
	// sider settings are after the colour value is starting starting value, lowest value, highest valuer, minimal adjustment, major adjustment
	voxie->menuAddItem((char*)"V Slider Text", 50, 85, 64, 150, MENU_VSLIDER_NAME, MENU_VSLIDER, 0.5, 0xFFFF80, .5, 2.0, .1, .1, .3);

	// horizontal slider
	// sider settings are after the colour value is starting starting value, lowest value, highest valuer, minimal adjustment, major adjustment
	voxie->menuAddItem((char*)"H Slider Text", 200, 270, 300, 64, MENU_HSLIDER_NAME, MENU_HSLIDER, 5, 0x808080, 5.0, 1.0, 20.0, 1.0, 3.0);

	// How to input a string
	voxie->menuAddItem((char*)"Menu Edit text", 50, 350, 500, 50, MENU_EDIT_NAME, MENU_EDIT, 0, 0x808080, 0.0, 0.0, 0.0, 0.0, 0.0);

	// Edit is like Edit Do does the next action when you press enter in this case will hit the Go button
	voxie->menuAddItem((char*)"Edit Do text", 50, 410, 400, 50, MENU_EDIT_DO_NAME, MENU_EDIT_DO, 0, 0x808080, 0.0, 0.0, 0.0, 0.0, 0.0);

	// A button which is linked to Edit Do
	voxie->menuAddItem((char*)"GO", 460, 410, 90, 50, MENU_GO, MENU_BUTTON_SINGLE, 0, 0x08FF80, 0.0, 0.0, 0.0, 0.0, 0.0);

	// A Toggle button use '\r' to seperate values each entry has its only value which gets passed to the menu_update function
	voxie->menuAddItem((char*)"Toggle Button\rPress Me\rTo Change\rValues", 175, 200, 175, 50, MENU_TOGGLE_NAME, MENU_TOGGLE, 0, 0xA080A0, 0.0, 0.0, 0.0, 0.0, 0.0);

	// add some more text
	voxie->menuAddItem((char*)"Matthew Vecchio / ReadyWolf for Voxon 2023", 40, 480, 64, 64, 0, MENU_TEXT, 0, 0xFF0000, 0.0, 0.0, 0.0, 0.0, 0.0);


	while (voxie->breath())
	{
		// Menu input check  check

		switch (menu.getLastId())
		{
		case MENU_VSLIDER_NAME: gVSliderValue = menu.getLastV();
			break;
		case MENU_HSLIDER_NAME: gHSliderValue = (int)menu.getLastV();
			break;
		case MENU_EDIT_NAME:
		case MENU_EDIT_DO_NAME:
			gTestMessage = menu.getLastStr();
			menu.resetStr();
			break;
		case MENU_UP:   gYHeightValue -= 0.05f; 														break;
		case MENU_ONE:  gMenuChoiceValue = 1;  gChoiceColourValue = 0xFF0000; 							break;
		case MENU_TWO:  gMenuChoiceValue = 2;  gChoiceColourValue = 0x00FF00;							break;
		case MENU_THREE: gMenuChoiceValue = 3; gChoiceColourValue = 0x0000FF; 							break;
		case MENU_DOWN:  gYHeightValue += 0.1f;  														break;
		case MENU_GO: gGoColour = ((rand() & 1) << 7) + ((rand() & 1) << 15) + ((rand() & 1) << 23);	break;
		case MENU_TOGGLE_NAME: gToggleValue = (int)menu.getLastV(); 									break;

		}
		// you could put a menu.resetLastUpdate(); here but since we want to see the report of what is happening wwe have to do it after the after the VXMenu report

		lastUpdateTemp = menu.getLastMenuData();
		voxie->startFrame();
	


		// Draw stuff on the display using variables from the menu

		pp.x = -voxie->getAspectX(); 					rr.x = 0.075f; dd.x = 0;
		pp.y = -voxie->getAspectY() + gYHeightValue;	rr.y = 0; dd.y = 0.1f;
		pp.z = cos(voxie->getTime()) / 10; 				rr.z = 0; dd.z = 0;
		voxie->drawText(&pp, &rr, &dd, gChoiceColourValue, "Choice:%d  gHSliderValue:%d ", gMenuChoiceValue, gHSliderValue);
		pp.y += 0.2;
		voxie->drawText(&pp, &rr, &dd, gChoiceColourValue, "gVSliderValue:%1.5f ", gVSliderValue);
		pp.y += 0.2;
		voxie->drawText(&pp, &rr, &dd, gChoiceColourValue, "Toggle value:%d", gToggleValue);
		pp.y += 0.2;
		voxie->drawText(&pp, &rr, &dd, gChoiceColourValue, gTestMessage);
		pp.y += 0.2;
		rr.x *= .60; dd.y *= .60; // resize text so its a smaller	
		//voxie->drawText(&pp, &rr, &dd, gChoiceColourValue, gFilecontents);

		pp.x = -0.4; pp.y += 0.2;
		rr.x = 0.8; rr.y = 0.0f; rr.z = 0.0f;
		dd.x = 0.0f; dd.y = 0.2f; dd.z = 0.0f;
		ff.x = 0.0;  ff.y = 0.0f; ff.z = 0.2f;

		voxie->drawCube(&pp, &rr, &dd, &ff, 2, gGoColour);
		
		voxie->showVPS();
		// report of what is happening in the VxMenu Last Update
		xPos = 100; yPos = 100;
		voxie->debugText(xPos, yPos, 0xffffff, -1, "VxMenu Report <=-\nLast id %d\nnameField %s\nmenuGetLastV %1.2f\nMeugetLastHow %d", menu.getLastId(), menu.getLastStr(), menu.getLastV(), menu.getLastHow());
		
		menu.resetLastUpdate();
		
		voxie->endFrame();
	}



	voxie->quitLoop();
	delete voxie;
	return 0;
}
