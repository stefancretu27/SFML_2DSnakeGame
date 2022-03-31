/*
* https://www.sfml-dev.org/tutorials/2.3/start-cb.php
*
* The whole SFML implementation resides within sf namespace. It has 5 modules
*   1. Audio: depends on System 
*   2. Graphics: depends on Window and System (inherits from classes defined in this modules)
*   3. Network: depends on System 
*   4. System
*   5. Window: depends on System 
*
* Each class defined in SFML has a definition directive, that is a macro. For example, Window is defined as 
*       class SFML_WINDOW_API Window,
* In this particular case, the macro is defined as SFML_API_EXPORT, in Window/Export.hpp. Each module contains such a header
* named Export.hpp, which aliases a macro named for that module (SFML_WINDOW_API, SFML_GRAPHICS_API, SFML_NETWORK_API,
* SFML_AUDIO_API, SFML_SYSTEM_API) to SFML_API_EXPORT.
*
* Then, Config.hpp header from the main directory, defines a series of macros. Here, SFML_API_EXPORT is
* defined based on the platform SFML is compiled for (Linux, Win, Mac). 
*
* For Windows, the macro is aliased  to __declspec(dllexport), which is a directive that tells all public 
* data members and method of that class can be exported outside of the dll the class is compiled to. 
* This way, those names (of classes and members) become accessible by app developers.
* For Linux and Mac, the macro is aliased to an attribute definition, using __attribute__  keyword, which
* sets the visibility of librray symbols, using syntax __visibility__ ("default"), as explained in the article:
* https://gcc.gnu.org/wiki/Visibility.
*/

#include "Game.hpp"
#include <Windows.h>

int main()
{
    // char path[MAX_PATH];
    // GetCurrentDirectoryA(MAX_PATH,path);
    // MessageBoxA(NULL,path,"Current Directory",MB_OK);

    Game::getInstance().runGame();
    
    return 0;
}