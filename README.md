# Alpha
2D game engine

Fyri at koyra spælið má ein fyrst koyra allar dll fílarnir í debug mappuni sum liggur í solution mappuni.
síðani má SDL, SDL_mixer og SDL_image paths leggjast afturat projektinum.
Hetta kann gerast soleiðis:
project -> properties -> vc++ Directories 
í teiginum Include Directories skrivar tú: 
$(SolutionDir)Flappy Bird\dependencies\SDL_Mixer\include;$(SolutionDir)Flappy Bird\dependencies\SDL_Image\include;$(SolutionDir)Flappy Bird\dependencies\SDL\include;$(IncludePath)

í teiginum Library Directories skrivar tú:
$(SolutionDir)Flappy Bird\dependencies\SDL_Mixer\lib\x86;$(SolutionDir)Flappy Bird\dependencies\SDL_Image\lib\x86;$(SolutionDir)Flappy Bird\dependencies\SDL\lib\x86;$(LibraryPath)

project -> properties -> Linker
Far síðani undir Linker og í teiginum Additional dependencies skrivar tú:
SDL2.lib;SDL2main.lib;SDL2_image.lib;SDL2_mixer.lib;%(AdditionalDependencies)

project -> properties -> System
At enda skalt tú fara undir System og í teiginum SubSystem velur tú Console(/SUBSYSTEM:CONSOLE)

Nú er spæli klárt at koyra. Lukka properties og trýst á F5 ella Local Windows Debugger
