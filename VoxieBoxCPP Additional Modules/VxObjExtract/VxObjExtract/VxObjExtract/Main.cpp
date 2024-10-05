// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "ObjExtractor.h"
#include "../../../../Headers and DLLs/vxCpp.h"
using namespace std;


// readfile 
int main(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmdline, int ncmdshow)
{
    HINSTANCE _Notnull_ hVoxieDLL = LoadLibrary("vxCpp.dll");
    CREATE_VOXIEBOX pEntryFunction = (CREATE_VOXIEBOX)GetProcAddress(hVoxieDLL, "CreateVoxieBoxObject");
    IVoxieBox* voxie = pEntryFunction();

    int i = 0;
    point3d pos, rr = { 0.8,0,0 }, dd = { 0,0.8,0 }, ff = { 0,0,0.8 };

//    string fileName = "matt.obj";

    string fileName = "suzanne.obj";

   ObjExtractor objEx(fileName.c_str());
    
   
    
    objEx.convertToVXPoltex();

    objEx.convertToVXMesh();

    int fillMode = 2;
    

    while (voxie->breath())
    {
        voxie->startFrame();

        if (voxie->getKeyIsDown(KB_Space_Bar)) {
            voxie->drawModel(fileName.c_str(), &pos, &rr, &dd, &ff, 0x400000);
        }

        i = objEx.getPoltexNo();

        i = objEx.getMeshNo();


      
        voxie->drawMesh(0, objEx.getVXPoltex(), objEx.getPoltexNo(), objEx.getVXMesh(), objEx.getMeshNo(), fillMode, 0x004000);


        if (voxie->getKeyOnDown(KB_Q)) {
            
            objEx.scale(1.1, true);


        }

     

        if (voxie->getKeyOnDown(KB_A)) {

            objEx.scale(0.9, true);


        }


        if (voxie->getKeyOnDown(KB_W)) {

            fillMode++;


        }


        if (voxie->getKeyOnDown(KB_S)) {

            fillMode--;


        }


        if (voxie->getKeyOnDown(KB_Tab)) {
            i++;

        }

        voxie->showVPS();
        voxie->endFrame();
    }

    voxie->quitLoop();
    delete voxie;
    return 0;
}


    // OBJ Extractor -- gets the core data from an OBJ and turns it in a 









#if 0
    int main() {
    string currentLine;
    ifstream myfile("mineModel2022.obj");


    std::smatch matchArray;
    std::regex materailExpression("mtllib (.*)");
    std::regex objectExpression("o (.*)");   //  object
    std::regex verticeExpression("v (.*) (.*) (.*)");   // vertices
    std::regex verticeNormalsExpression("vn (.*) (.*) (.*)");               // lighting not needed for Ken's world
    std::regex indicesExpression("f (.*?)/(.*?)/(.*?) (.*?)/(.*?)/(.*?) (.*?)/(.*?)/(.*?)");   // f triangles or polys 
    std::regex uvExpression("vt(.*) (.*)");


    ObjExtractor objEx("mineModel2022.obj");

    currentLine = "hello";

    objEx.calcVerticesMaxMin();
    objEx.calcCentre();
    objEx.calcScalar();

    point3d pp;
    point3d pp1;

    pp.x = 54215.43;
    pp.y = 11749.741;
    pp.z = 9916.79;
    objEx.getPointOffset(pp, &pp1);

    point3d pp2;

    pp.x = 55249.473;
    pp.y = 12400.16;
    pp.z = 9293.115;
    objEx.getPointOffset(pp, &pp2);

    point3d pp3;

    pp.x = 55414.875;
    pp.y = 11814.046;
    pp.z = 10105.935;


    objEx.getPointOffset(pp, &pp3);
    
    pp.x = pp.x;

    pp = objEx.getModelCentre();

    std::cout << "Centres  (" << pp.x << "," << pp.y << "," << pp.z << ")" << std::endl; // print out the data

    std::cout << "Scalar" << objEx.getScalar() << std::endl;

    std::cout << "PP 1 (" << pp1.x << "," << pp1.y << "," << pp1.z << ")" << std::endl; // print out the data

    std::cout << "PP 2 (" << pp2.x << "," << pp2.y << "," << pp2.z << ")" << std::endl; // print out the data

    std::cout << "PP 3 (" << pp3.x << "," << pp3.y << "," << pp3.z << ")" << std::endl; // print out the data

    std::cin;



    if (myfile.is_open())
    {
        while (getline(myfile, currentLine))
        {
            /* Obj file consists of a link to a  Mtl files - materials 
             *
             * 
             *  "# Blender v3.0.1 OBJ File: 'ozminerals_all_obj.blend'
                # www.blender.org
                mtllib ozminerals_all_obj_not_centred.mtl
                o 140"
             *  o = name of object
             *  v = verticles
             *  vn = vertices normals (lighting)
             * 
             *  f = indices (vertces for making a triangle  format: f vertice index / uv index / normal index SPACE * 3 or more depending on shape triangle or polys 
             *  l = ?
             *  vt = texture mapping 
             *  
             */
            //
            // get vertices 


            if (currentLine[0] == 'o' && currentLine[1] == ' ') {

            }
           
            if (currentLine[0] == 'v' && currentLine[1] == ' ') {
              // cout << currentLine << '\n';

                // matchArray gets filled with temporary line data if it matches the verticeExpression defined above... 
               std::regex_search(currentLine, matchArray, verticeExpression);
               
                   if (!matchArray.empty()) {
                       std::cout << "(" << matchArray[1] << "," << matchArray[2] << "," << matchArray[3] << ")"; // print out the data
                        // write code to store the data here if need be 
                       // for VX go to poltex x,y,z later amend with uv data based from vt cords from the ob 
                       std::cout << std::endl;
                   }

            }

            // get triangles / polys - always indexes
            if (currentLine[0] == 'f' && currentLine[1] == ' ') {
                // cout << currentLine << '\n';

                  // matchArray gets filled with temporay line data if it matches the verticeExpression defined above... 
                std::regex_search(currentLine, matchArray, indicesExpression);

                if (!matchArray.empty()) {

                    // 1 is vertice index 2 is vt index 3 is normal index 
                    std::cout << matchArray[1] << "/" << matchArray[2] << "/" << matchArray[3] << "-1"; // print out the data
                    std::cout << matchArray[4] << "/" << matchArray[5] << "/" << matchArray[6] << "-1"; // print out the data
                    std::cout << matchArray[7] << "/" << matchArray[8] << "/" << matchArray[9] << "-1"; // print out the data

                     // write code to store the data here if need be 
                    // for for VX shapes just grab the vertice index go to int array   "matchArray[1] , matchArray[4], matchArray[7], -1" 

                    std::cout << std::endl;
                }

            }

           
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    return 0;
}
#endif