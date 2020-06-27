clear
g++ -I/usr/include/SDL2 -I. game.cpp assetmgr.cpp pathfind.cpp map.cpp unit.cpp gameplayer.cpp viewport.cpp perlinmap.cpp display.cpp maptile.cpp main.cpp -o main `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image
./main

