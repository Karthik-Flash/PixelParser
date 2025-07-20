//RGB Instensity
// note for grayscale its pgm format (portable gray map) but for RGB its ppm format (portable pixel map)
#include <stdio.h>

#define WIDTH 10
#define HEIGHT 10

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGBPixel;

int main() {
    RGBPixel image[HEIGHT][WIDTH];

    // Fill image with a horizontal red gradient, constant green, and constant blue
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            image[i][j].red   = (unsigned char)((255.0 / (WIDTH - 1)) * j);  // Horizontal red gradient
            image[i][j].green = 200;  // Constant green
            image[i][j].blue  = 100;  // Constant blue
        }
    }

    // Save image in PPM format (ASCII)
    FILE *fp = fopen("rgbimage.ppm", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    // PPM Header for ASCII format
    fprintf(fp, "P3\n");              // Magic number for ASCII PPM
    fprintf(fp, "%d %d\n", WIDTH, HEIGHT);
    fprintf(fp, "255\n");            // Max color value

    // Pixel Data
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            fprintf(fp, "%d %d %d ", 
                image[i][j].red, 
                image[i][j].green, 
                image[i][j].blue);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("PPM image saved as 'rgbimage.ppm'\n");
    return 0;
}