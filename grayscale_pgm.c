//Grayscale Instensity
//in a pgm format   (portable gray map)
#include <stdio.h>

#define WIDTH 100
#define HEIGHT 100

typedef struct {
    unsigned char pixel; // Grayscale value (0-255)
} Pixel;

int main() {
    Pixel image[HEIGHT][WIDTH];

    // Fill the image with gradient values
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            image[i][j].pixel = (unsigned char)((255.0 / (WIDTH - 1)) * j); // Horizontal gradient
        }
    }

    // Save as PGM format (ASCII)
    FILE *fp = fopen("image.pgm", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    // PGM header
    fprintf(fp, "P2\n");
    fprintf(fp, "%d %d\n", WIDTH, HEIGHT);
    fprintf(fp, "255\n");

    // Pixel data
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            fprintf(fp, "%d ", image[i][j].pixel);
            // fprintf syntax int fprintf(FILE *stream, const char *format, ...);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("PGM image saved as 'image.pgm'\n");
    return 0;
}
