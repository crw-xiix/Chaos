g++ -I/usr/include/SDL2 -I. action.cpp animation.cpp assetmgr.cpp display.cpp ../3rd/easywsclient.cpp button.cpp actionselectserver.cpp socketqueue.cpp actionintro.cpp game.cpp gameplayer.cpp main.cpp  map.cpp maptile.cpp pathfind.cpp pch.cpp console.cpp perlinmap.cpp unit.cpp viewport.cpp -o main `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image
mv main ..
cd ..
./main
cd src
