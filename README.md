VxCPP - VX++ "Friendly Voxon Development with classes" 



Official Git for VxCpp. The VX++ Framework for Voxon Volumetric Application Development 

Git Commit prefixes for changes:

- [Feat] -> Adding a feature
- [Bug] -> Bug Fix
- [Tweak] -> Adjustment/modification to code
- [Chore] -> Misc clean up / or adjustments / addition of files
- [Dep] -> Deprecation when something has been removed.

# Introduction

VxCPP or (VX++) is a C++ wrapper for the Voxiebox SDK (Voxiebox SDK by Ken Silverman). The VxCPP.dll allows the Voxon API to be used as a 'voxiebox class' making Voxon application development compatible with object oriented principles.

The VoxieBox class includes all the functions from the Voxon API, extra helper functions and quality of life changes. The intention of this project is to make development for Voxon Applications easier. In a nutshell, VX++ offers "friendly Voxon development with classes".

VxCPP.dll does not replace the voxiebox.dll. VX applications that use VxCPP still require access to voxiebox.dll to work.

Please note for users who have worked directly with the voxiebox.dll some of the original voxiebox.dll function names have been named differently, functions may behave differently (and call functions written in camelCase).

The compiled VxCpp.dll and associated files are released as public domain. However the source code for VxCPP / VX++ project is released with a CC BY licence. You may release your VX++ applications (even commercially) and distribute the compiled VxCPP.dll freely without accreditation. However, any adaption or code and built upon the source code from VxCPP requires accreditation for the original creators. (Matthew Vecchio & Voxon Photonics).

# Benefits of Using the VX++ Framework

```
          VxCpp.Dll / Developing VX++ App benefits:

           "Voxiebox as a class"

           * Presents VoxieBox as a class so Voxon Applications can be made using OO principles
           * Supports all function calls from VoxieBox.h / VoxieBox.dll


           "Quality of life features"   

           *  Embedded Hotkeys for rotation for emulator/simulator mode 
                 (use '[' and ']' to rotate the view. R Ctrl + '[' or ']' zooms in or out R Shift + '[' or ']' adjust vertical view)
           *  Automatically detect Up/Down or Spinner hardware
           *  Easier Debuging Reporting for Voxie Window, Voxie Frame and all inputs types
           *  Extended input function checks for mouse, keyboard, SpaceNav and gamepads all inputs have functions to check for onDown(), 
                 onUp(), duration(), and isDown()  
           *  Internally managed Input for Gamecontrollers and SpaceNav. More advanced Key stroke history. 
           *  Various boolean function calls to turn on/off features such as 'drawBorder' 'clipMouse' or 'invertZAxis'
           *  Embedded cursor (for mouse or otherwise) 
           *  DrawQuad() function to easily draw a textured Quad on the display. 
           *  All Quality of life features can be disabled / enabled independently. 


           "Included helper functions"

           *  Simple collision detection for sphere, box and 'is inside a box' 
           *  Color management included palette for the display, functions to tween color to color, color scroll, get a random color, 
                 color divide and color brighten.
           *  Simple Move To Point function for moving a position to another.
```

# Developing with VxCPP.dll and making your own VX++ App

Developing with VxCPP.dll is similar to developing with the voxiebox.dll. A VX application needs to load in the voxiebox.dll (Ken's Voxon SDK library) a VX++ application loads in the voxiebox.dll by an entry function in VxCPP.dll "CreateVoxieBoxObject" calling this function creates a new 'VoxieBox' an object Once the VoxieBox object is created it can be accessed using an pointer to the IVoxieBox interface.

A simple hello world example... 

```
           // VX++ APP HELLO WORLD EXAMPLE 
           // You may use this as a template to start creating your own volumetric applications.
           #include "vxCPP.h"
           int main(HINSTANCE hidistributenst, HINSTANCE hpinst, LPSTR cmdline, int ncmdshow)
           {

               // load in the vxCpp.dll so we can create the VoxieBox object...
               HINSTANCE hVoxieDLL = LoadLibrary("vxCpp.dll");

               // Access and call "CreateVoxieBoxObject" function from vxCpp.dll. The CreateVoxieBoxObject function creates a new VoxieBox object.
               CREATE_VOXIEBOX pEntryFunction = (CREATE_VOXIEBOX)GetProcAddress(hVoxieDLL, "CreateVoxieBoxObject");
               // Set a new IVoxieBox pointer to point to the entry function (the voxiebox object) now 'voxie' get access to the VoxieBox class
               IVoxieBox* voxie = pEntryFunction(); 

               // variables to setup text positions to display 'Hello World' -- feel free to delete this 
               point3d textPos     { -0.5, 0, 0 };     // text postions x,y,z values
               point3d textWidth   { 0.1,  0, 0 };     // text rVector  x,y,z ... the x value determines the width of the text the other values deal with rotating text
               point3d textHeight  { 0, 0.15, 0 }; // text dVector  x,y,z ... the y value determines the height of the text the other values deal with rotating text

               voxie->setBorder(true); // if true draws a border around the perimeter of the display

               // Update loop for program -- breath() -- is a complete volume sweep. Called once per volume. 
               while (voxie->breath()) 
               {
                   voxie->startFrame();   // The start of drawing the Voxieframe (all voxie draw calls need to be within this and the endFrame() function)
                   voxie->drawText(&textPos, &textWidth, &textHeight, 0xffffff, "Hello World"); // draw text onto the volumetric display.
                   textPos.z = cos(voxie->getTime()) / 5; // move the text's Z position over time using cos (creates a moving up and down effect)*                         
                   voxie->debugText(35, 100, 0xffffff, -1, "Hello World On the Touch Screen!"); // draw text onto the secondary (touch) screen.
                   voxie->showVPS(); //show VPS data and VXCPP.DLL version unto the touch screen.
                   voxie->endFrame(); // the end of drawing to the volumetric display.
               }

               voxie->quitLoop(); // quitLoop() stops the hardware from physically moving and ends the breath() loop
               delete voxie;
               return 0;   // After the program quits the deconstructor for voxiebox frees the DLLs from memory if you wanted to do this manually call the voxie->Shutdown()
           }
```

# Running Applications written using VX++ / VxCPP

A VX++ App (Voxon App developed with VxCPP.DLL) requires access to the VxCPP.dll. To do this you can copy VxCPP.dll to the local directory, place it in the Voxon runtime directory (C:\Voxon\System\Runtime) or set it up in your system's path variable.

# Updating / Where to get newer versions of VX++ / VxCPP.dll

VxCpp / VX++ public release (with source code) is available as part of the Voxon Content Developers Kit which can be obtained freely at https://github.com/Voxon-Photonics/Content-Developers-Kit

# Introduction

The compiled VXCpp.dll is public domain any application you make using VXCpp.dll is yours. Applications made with VX++ and the VxCpp.dll can be distributed with your applications freely without any accreditation needed. However. VX++ / VxCpp.dll's source code is released with a Creative Commons By Attribution (CC BY) license. This means that licensees may copy, distribute, display and perform the work and make derivative works and remixes based on it only if they give the author (Matthew Vecchio / Voxon Photonics ) proper accreditation

# Contact information

VxCPP / VX++ is maintained by Matthew Vecchio for Voxon Photonics. Contact me at [Matt@Voxon.co] for feature requests, code suggestions. bug reports, feedback, showing off cool stuff you have done or anything else you can contact me at [Matt@Voxon.co]

- 