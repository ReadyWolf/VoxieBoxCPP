#pragma once

#include <stdlib.h>   
#include <istream>
#include <vxCpp.h>


/* VxMenu is a class that can manage the Voxie Menu update which is a 
 * 
 *  it uses a static data type and static function embedded into a class as a workaround 
 * kept to be simple so it can be used with straight with the voxiebox.dll 
 */


//! 3D SpaceMouse / Space Navigator by 3DConnexion input state struct. Used to manage SpaceNav input
typedef struct menu_data_t {

	int id;
	char nameField[256] = "none";
	double v;
	int how;

} menu_data_t;

menu_data_t static lastUpdate;


//struct menuData
//	fields 

class VxMenu : public IVoxiePtr
{
public:
	VxMenu();
	~VxMenu();
	static int  menu_update(int id, char* st, double v, int how, void* userdata);
	void reg_menu_function(IVoxieBox * voxiePtr);
	menu_data_t getLastMenuData();
	int getLastId();
	char* getLastStr();
	double getLastV();
	int getLastHow();
	void resetLastUpdate();
	
	bool isAutoClear();
	void setAutoClear(bool choice);
	void resetStr();

private: 

	bool autoClear = true;
	IVoxieBox* voxiePtr; 

};
