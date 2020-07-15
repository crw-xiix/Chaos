SRC_DIR := ./src
OBJ_DIR := ./obj
TRD_DIR := ./3rd
OBJ_DIR_TRD := ./obj/3rd

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TRD_FILES := $(wildcard $(TRD_DIR)/*.cpp)
OBJ_FILES_TRD := $(patsubst $(TRD_DIR)/%.cpp,$(OBJ_DIR_TRD)/%.o,$(TRD_FILES))
LDFLAGS := `sdl2-config --libs` -lSDL2_image
CPPFLAGS := -I./src `sdl2-config --cflags`

all: main
	echo "AllDone"

clean:
	rm -rf ./obj main

main: $(OBJ_FILES) $(OBJ_FILES_TRD)
	g++ $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	g++ $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR_TRD)/%.o: $(TRD_DIR)/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<
