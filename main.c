#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "vector.h"

#define CUBE_WIDTH 10
#define WIDTH 30
#define HEIGHT 30
#define BG_CHAR ' '

char buffer[WIDTH * HEIGHT];
Vector3 vector_space[WIDTH * HEIGHT];

float angle_x = 0.0;
float angle_y = 0.0;
float angle_z = 0.0;


void clear_screen() {
    printf("\033[2J\033[1;1H");
}

void print_screen() {
    for(int i = 0; i < HEIGHT; i++) {
        printf("%c", buffer[i]);
    }
}

char get_brightness_char(float z) {
    char brighteness_array[] = " .,;~+O0#@$";
    return brighteness_array[(int)roundf(z)];
}

void reset_buffer() {
    for(int i = 0; i < (WIDTH * HEIGHT); i++) {
        buffer[i] = BG_CHAR;
    }
}

void reset_all_buffers() {
    for(int i = 0; i < (WIDTH * HEIGHT); i++) {
        buffer[i] = BG_CHAR;
        vector_space[i] = create_vector(0, 0, 0);
    }
}

void initialize_vector_space() {
    for(int x = 5; x < 25; x++) {
        for(int y = 5; y < 25; y++) {
            if(((15 - x)*(15 - x) + (15 - y)*(15 - y)) < 100)
                vector_space[x + y * WIDTH] = create_vector(x, y, 5);
        }
    }
}

int main() {
    reset_all_buffers();
    initialize_vector_space();

    // Game loop
    while(1) {
        usleep(100000);
        clear_screen();
        reset_buffer();

        // Based on vector space, write to buffer
        // TODO : Eliminate cases where one point overlaps the other
        // POSSIBLE SOLUTION : Take the point with highest 'z' value
        for(int i = 0; i < (WIDTH * HEIGHT); i++) {
            Vector3 vec = vector_space[i];
            buffer[(int)vec.x + (int)vec.y * WIDTH] = get_brightness_char(vec.z);
        }

        // Print buffer
        for(int i = 0; i < (WIDTH * HEIGHT); i++) {
            printf(((i % HEIGHT) == 0) ? "\n" : "");
            printf("%c", buffer[i]);
        }

        // Rotate the vectors
        for(int i = 0; i < (WIDTH * HEIGHT); i++) {
            if (!is_zero_vector(vector_space[i])) {
                vector_space[i] = get_relative_rotated_vector(10, 10, 10, vector_space[i], create_vector(WIDTH/2, HEIGHT/2, 5));
            }
        }
    }
}
