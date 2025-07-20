//convertorRGB - Converts a horizontal gradient RGB image to BMP format

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define WIDTH 1000
#define HEIGHT 1000

int main() {
    uint8_t red, green = 100, blue = 200;

    // BMP requires row size to be a multiple of 4 bytes
    int rowSize = (3 * WIDTH + 3) & (~3);
    int pixelArraySize = rowSize * HEIGHT;
    int fileSize = 14 + 40 + pixelArraySize;

    FILE *fp = fopen("rgb_image.bmp", "wb");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    // BMP Header (14 bytes)
    uint8_t fileHeader[14] = {
        'B', 'M',
        0, 0, 0, 0,      // File size
        0, 0, 0, 0,      // Reserved
        54, 0, 0, 0      // Pixel data offset
    };
    *(int*)&fileHeader[2] = fileSize;
    fwrite(fileHeader, 1, 14, fp);

    // DIB Header (40 bytes)
    uint8_t dibHeader[40] = {0};
    *(int*)&dibHeader[0]  = 40;      // Header size
    *(int*)&dibHeader[4]  = WIDTH;
    *(int*)&dibHeader[8]  = HEIGHT;
    *(short*)&dibHeader[12] = 1;     // Planes
    *(short*)&dibHeader[14] = 24;    // Bits per pixel
    *(int*)&dibHeader[16] = 0;       // Compression
    *(int*)&dibHeader[20] = pixelArraySize;
    *(int*)&dibHeader[24] = 2835;
    *(int*)&dibHeader[28] = 2835;
    fwrite(dibHeader, 1, 40, fp);

    // Write pixel data (bottom-up)
    uint8_t padding[3] = {0, 0, 0};
    int paddingSize = rowSize - WIDTH * 3;

    for (int i = HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            red = (uint8_t)((255.0 / (WIDTH - 1)) * j);
            fwrite(&blue, 1, 1, fp);
            fwrite(&green, 1, 1, fp);
            fwrite(&red, 1, 1, fp);
        }
        fwrite(padding, 1, paddingSize, fp);
    }

    fclose(fp);
    printf("Saved RGB BMP as 'rgb_image.bmp'\n");
    return 0;
}