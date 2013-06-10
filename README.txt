Linkar amb SDL2

Com compil.lar la SDL2:
-----------
LINUX
-----------

sudo apt-get install build-essential
sudo apt-get install mercurial   	(instal.la el mercurial un gestor de repositoris similar al git (SDL fa servir aquest))
hg clone http://hg.libsdl.org/SDL  	(Clona el repo SDL)
cd SDL				
mkdir build
cd build		
../configure				(configura el SDL segons el SO)
make					(compil.la)
sudo make install			(instal.la)
sudo ldconfig                		(aixo actualitza el programa ld (el linker) per a que trobi la SDL2)

*** INFORMACIO ADICIONAL ***
Els fitxers de llibreria s'instal.len automaticament a /usr/local/lib/libSDL2.a
Els fitxers de capÃ§alera s'instal.len automaticament a /usr/local/include/SDL2

Quan vulguis incloure la llibreria SDL en un .cpp .h per exemple a l'ECLIPSE:

#include <SDL2/SDL.h>

i en les propietats del linker afegir que linki amb la llibreria:

SDL2


****** PER ACTUALITZARLO *****
es va a la carpeta on haguem fet el "hg clone http://hg.libsdl.org/SDL" i fem:

cd SDL
hg pull (retreu la nova Â¡nformacio del repo)
cd build
../configure
make
sudo make install
sudo ldconfig





---------
WINDOWS
---------

//TODO


Copiar el SDL source a: C:\MinGW\msys\1.0\home\Dani

dins la carpeta del source C:\MinGW\msys\1.0\home\Dani\SDLsource
fer:
mkdir build
cd build
../configure
make
make install

Això instal·larà la llibreria amb els libs i includes a /usr/local/ concretament:

C:\MinGW\msys\1.0\local\lib       -> libSDL2.a
C:\MinGW\msys\1.0\local\include   -> Fitxers que s'hauran d'incloure
C:\MinGW\msys\1.0\local\bin       -> SDL2.dll i sdl-config



ERRORS COMUNS A L'ECLIPSE AMB SDL
web important: http://wiki.libsdl.org/moin.cgi/FAQWindows

---- LA CONSOLA NO TREU OUTPUT / NO SEMBLA QUE FUNCIONI EL PROGRAMA ---
add a PATH variable to C:\MinGW\bin in the Run Configuration, then I saw stdout when running from a normal run configuration in the C+ view.


-- Si no funciona provar: 

go to Project->Properties. Under "C++ Build", select "Settings". Under "MinGW C++ Linker", select "Miscellaneous". Add "-static-libgcc" to the "Linker flags" field. You may have to do this for your other build configurations and projects.

-- SI TAMPOC FUNCIONA provar amb -static només.
go to Project->Properties. Under "C++ Build", select "Settings". Under "MinGW C++ Linker", select "Miscellaneous". Add "-static" to the "Linker flags" field. You may have to do this for your other build configurations and projects.


---- undefined reference to `WinMain@16' ---
-- EXPLICACIO http://wiki.libsdl.org/moin.cgi/FAQWindows
Under Visual C++, you need to link with SDLmain.lib. Under the gcc build environments including Dev-C++, you need to link with the output of "sdl-config --libs", which is usually: -lmingw32 -lSDLmain -lSDL -mwindows 
-- SOLUCIO

l'output de "./sdl-config --libs" dins de la carpeta "C:\MinGW\msys\1.0\local\bin" normalment es: 
-lmingw32 -lSDLmain -lSDL -mwindows  per tant al linker del projecte linkarem amb:

//AQUESTESSSSSSSSSSSS SOBRETOOOOOOOOOOOOT HAN DE QUEDAR EN AQUEST ORDREEEEEEEE:
mingw32
SDL2main
SDL2


SI AIXO NO FUNCIONA PROVAR DE FER: 
l'output de "./sdl-config --static-libs"

i sortiran un tou de llibreries que haurem de posar al linker tal com ho fariem amb -mwindows per exemple quedaria aixi:

${COMMAND} ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS} -mwindows -lm -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lversion -luuid



-- (AQUEST PAS NO L'ENTENC MOLT BÉ I DIRIA QUE ES OPCIONAL ) SOBRETOT AL MINGW C++ LINKER A LA DRETA A: COMMAND LINE PATTERN AFEGIR AL FINAL: 
-mwindows

Hauria de quedar similar a aixo: 
${COMMAND} ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS} -mwindows



---- undefined reference to `SDL_main' ----
Aquest error surt perque no tenim ben definit el int main(), assegurem que sigui:

int main(int argc, char *argv[]) 

i l'error marxarà



Amb això solucionem els errors.

pull this

