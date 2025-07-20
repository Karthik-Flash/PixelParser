//Flash logo in PPM format
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

    const int flashMatrix[100] = {
         0,0,0,0,1,0,0,0,0,0,
         0,0,0,1,1,0,0,0,0,0,
         0,0,1,0,1,0,0,0,0,0,
         0,1,0,0,1,0,0,0,0,0,
         1,0,0,0,1,0,0,0,0,0,
         0,0,0,1,0,0,0,0,0,0,
         0,0,1,0,0,0,0,0,0,0,
         0,1,0,0,0,0,0,0,0,0,
         1,0,0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0,0
    };

    for (int idx = 0; idx < WIDTH * HEIGHT; idx++) {
        int row = idx / WIDTH;
        int col = idx % WIDTH;

        if (flashMatrix[idx]) {
            // Flash pixel (bright yellowish)
            image[row][col].red   = 255;
            image[row][col].green = 255;
            image[row][col].blue  = 0;
        } else {
            // Background pixel (dark gray)
            image[row][col].red   = 30;
            image[row][col].green = 30;
            image[row][col].blue  = 30;
        }
    }

    // Save as ASCII PPM
    FILE *fp = fopen("flash.ppm", "w");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HEIGHT);

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
    printf("Saved Flash logo as 'flash.ppm'\n");
    return 0;
}