clear
g++ -I/usr/include/SDL2 -I. action.cpp animation.cpp assetmgr.cpp display.cpp easywsclient.cpp game.cpp gameplayer.cpp main.cpp  map.cpp maptile.cpp pathfind.cpp pch.cpp perlinmap.cpp unit.cpp viewport.cpp -o main `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image
./main

