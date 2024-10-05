#include "VxMenu.h"

VxMenu::VxMenu()
{
	resetLastUpdate();
}

VxMenu::~VxMenu()
{


}

 int VxMenu::menu_update(int id, char* st, double v, int how, void* userdata)
{
	
	 lastUpdate.id = id;
	 if (st == 0) {
		// strcpy_s(lastUpdate.nameField, sizeof(lastUpdate.nameField), (char*)"empty");
	 }
	 else {
		 strcpy_s(lastUpdate.nameField, sizeof(lastUpdate.nameField), st);
	 }
	 lastUpdate.v = v;
	 lastUpdate.how = how;

	 return 1;
}

 void VxMenu::reg_menu_function(IVoxieBox* voxiePtr)
 {
	 this->voxiePtr = voxiePtr;
	 voxiePtr->menuReset(this->menu_update, 0, 0);
 }


 menu_data_t VxMenu::getLastMenuData()
 {
	 menu_data_t thisLastUpdate = lastUpdate;
	 if (autoClear) resetLastUpdate();
	 return thisLastUpdate;
 }

 int VxMenu::getLastId()
 {
	 return lastUpdate.id;
 }

 char* VxMenu::getLastStr()
 {
	 return lastUpdate.nameField;
 }

 double VxMenu::getLastV()
 {
	 return lastUpdate.v;
 }

 int VxMenu::getLastHow()
 {
	 return lastUpdate.how;
 }

 void VxMenu::resetLastUpdate()
 {
	 lastUpdate.how = 0;
	 lastUpdate.id = -1;
	// strcpy_s(lastUpdate.nameField, sizeof(lastUpdate.nameField), (char*)"empty");
	 lastUpdate.v = 0;
 }

 bool VxMenu::isAutoClear()
 {
	 return autoClear;
 }

 void VxMenu::setAutoClear(bool choice)
 {
	 autoClear = true;
 }

 void VxMenu::resetStr()
 {
	 strcpy_s(lastUpdate.nameField, sizeof(lastUpdate.nameField), (char*)"empty");
 }

