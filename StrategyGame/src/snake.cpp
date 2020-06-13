#pragma once

#include "pch.h"

/*USE FOR REFERENCE*/

const int DISPLAY_SCALE_FACTOR = 15;

typedef struct snake_xy {
	char x, y;
} snake_xy;

const int snake_size = 320;
const int grid_size = 42;
const int bait_size = 50;

snake_xy snake[snake_size];
snake_xy bait[bait_size];

int snake_head = 0;
int snake_tail = 0;

typedef enum snake_dir { Up, Left, Down, Right } snake_dir;
snake_dir cur_direction;

void start_snake() {
	snake[0].x = 10; snake[0].y = 10;
	snake[1].x = 10; snake[1].y = 9;
	snake[2].x = 10; snake[2].y = 8;
	snake_head = 0;
	snake_tail = 2;
	cur_direction = Down;
}

void clear_bait() {
	for (int y = 0; y < bait_size; y++) {
		bait[y].x = -1;
		bait[y].y = -1;
	}
}

void set_bait() {
	bait[0].x = 10;
	bait[0].y = 12;
}

void add_bait() {
	for (int i = 0; i < bait_size; i++) {
		if (bait[i].x == -1) {
			bait[i].x = rand() % grid_size;
			bait[i].y = rand() % grid_size;
			break;
		}
	}
}

void draw_snake(SDL_Renderer* ren) {
	char buffer[grid_size][grid_size];
	int thead = snake_head;
	for (;;) {
		int x = snake[thead].x;
		int y = snake[thead].y;
		buffer[y][x] = 'X';
		if (thead == snake_tail) break;
		thead++;
		if (thead > (snake_size - 1)) thead = 0;
	}
	for (int y = 0; y < bait_size; y++) {
		if (bait[y].x >= 0) {
			buffer[bait[y].y][bait[y].x] = '.';
		}
	}
	for (int y = 0; y < grid_size; y++) {
		for (int x = 0; x < grid_size; x++) {
			SDL_SetRenderDrawColor(ren, 128, 128, 128, 255);
			if (buffer[y][x] == 'X') {
				SDL_SetRenderDrawColor(ren, 255, 128, 128, 255);
			}
			if (buffer[y][x] == '.') {
				SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
			}
			SDL_RenderDrawPoint(ren, x, y);
		}
	}
}

//Return true if we died....
int move_snake(snake_dir dir) {
	snake_xy cur = snake[snake_head];
	snake_xy temp = cur;
	switch (dir) {
	case Up:
		temp.y--;
		break;
	case Down:
		temp.y++;
		break;
	case Left:
		temp.x--;
		break;
	case Right:
		temp.x++;
		break;
	}
	snake_head--;

	if (snake_head < 0) snake_head += snake_size;
	snake[snake_head] = temp;
	for (int i = 0; i < bait_size; i++) {
		if ((bait[i].x == temp.x) && (bait[i].y == temp.y)) {
			//Remove the bait.
			bait[i].x = -1;
			bait[i].y = -1;
			//Early return - stinks - code smell
			return 0;
		}
	}
	snake_tail--;
	if (snake_tail < 0)  snake_tail += snake_size;
	return 0;
}


int snake_main(int argc, char* argv[])
{
	SDL_Window* win;
	SDL_Renderer* ren;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("SDL initialization failed... %s", SDL_GetError());
	}

	if (SDL_CreateWindowAndRenderer(grid_size * DISPLAY_SCALE_FACTOR, grid_size * DISPLAY_SCALE_FACTOR, 0,
		&win, &ren) < 0) {
		SDL_Log("SDL window or renderer creation failed... %s", SDL_GetError());
	}

	SDL_RenderSetScale(ren, DISPLAY_SCALE_FACTOR, DISPLAY_SCALE_FACTOR);

	char buffer[20];
	start_snake();
	clear_bait();
	set_bait();

	for (;;) {
		SDL_Event e;
		uint32_t delay, timer_end, timer_start = SDL_GetTicks();
		const uint8_t* ks = SDL_GetKeyboardState(NULL);
		SDL_PollEvent(&e);

		if (ks[SDL_SCANCODE_W]) {
			if (cur_direction != Down)
				cur_direction = Up;
		}
		if (ks[SDL_SCANCODE_S]) {
			if (cur_direction != Up)
				cur_direction = Down;
		}
		if (ks[SDL_SCANCODE_A]) {
			if (cur_direction != Right)
				cur_direction = Left;
		}
		if (ks[SDL_SCANCODE_D]) {
			if (cur_direction != Left)
				cur_direction = Right;
		}
		move_snake(cur_direction);
		draw_snake(ren);
		SDL_RenderPresent(ren);
		SDL_Delay(100);
		add_bait();
	}
}