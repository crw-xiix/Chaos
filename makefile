#####################################
# SirFelixDelazar's Simple makefile #
# Last edit: 2020.07.15             #
#####################################

# Configuration
CC := g++
SRC_EXT := cpp

SRC_DIR := ./StrategyGame
OBJ_DIR := ./obj

LDFLAGS := `sdl2-config --cflags -libs` -lSDL2 -lSDL2_image
CFLAGS := -I$(SRC_DIR)/src -I$(SRC_DIR)/3rd -I/usr/include/SDL2 -std=c++17

EXEC_NAME := main

RM := rm -rf
MKDIR := mkdir -p

# DONT TOUCH THAT IF YOU CANT UNDERSTAND WHAT ARE HAPPENING
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRC_FILES := $(call rwildcard,$(SRC_DIR),*.$(SRC_EXT))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: clean build

clean:
	$(RM) $(OBJ_DIR)/* $(EXEC_NAME)

build: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(EXEC_NAME) $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.$(SRC_EXT)
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<