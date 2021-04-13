# CppProject11_SpaceDefense
 
This is my 11th Project and last project before Easter.

Brief description - 
   Tried to see if I could make a little game.
   Left and right keys to turn the turret and space to shoot.
   (Shush) Alt key lets you shoot every frame ;)

If you bring the .dlls from the main folder to the Release folder should run normally if you aren't bothered compiling.

Preview

![ezgif com-gif-maker (5)](https://user-images.githubusercontent.com/67654528/114614404-5a5fef80-9c9c-11eb-9382-745f8f516a37.gif)

Full video on Youtube -- https://youtu.be/a9ukZX3eA6Q



This uses the SFML library. -- I think its the 64bit Visual Studio 15 one.

Setup - (This is for myself in the future)

Go into Project Properties- Select all Configurations In C++ -> Additional Include Dicts add "c:\SFMLVS\INCLUDE" In Linker -> Additional Library Dicts "c:\SFMLVS\lib" In Linker, Linker Input -> Additional Dependencies "sfml-window.lib;sfml-system.lib;sfml-graphics.lib;sfml-audio.lib;sfml-network.lib;"

Apply <- Go into Debug Configuration In Linker, Linker Input -> "sfml-window-d.lib;sfml-system-d.lib;sfml-graphics-d.lib;sfml-audio-d.lib;sfml-network-d.lib;"

After that get SFMLVS Bin .dlls and add into solution with CPP files. --> Run
