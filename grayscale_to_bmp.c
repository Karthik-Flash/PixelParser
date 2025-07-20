// convertor code to convert grayscale values to BMP(bitmap) format
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define WIDTH 100
#define HEIGHT 100

int main() {
    // Step 1: Fill grayscale values (gradient)
    unsigned char image[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            image[i][j] = (unsigned char)((255.0 / (WIDTH - 1)) * j);  // horizontal gradient

    // Step 2: BMP metadata
    int rowSize = (WIDTH + 3) & (~3);  // rows padded to nearest multiple of 4 bytes
    int pixelArraySize = rowSize * HEIGHT;
    int fileSize = 14 + 40 + 256 * 4 + pixelArraySize;

    FILE *fp = fopen("image.bmp", "wb");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    // ----------------------------
    // BMP HEADER (14 bytes)
    // ----------------------------
    uint8_t fileHeader[14] = {
        'B', 'M',                      // Signature
        0, 0, 0, 0,                    // File size
        0, 0,                         // Reserved
        0, 0,                         // Reserved
        54 + 256 * 4, 0, 0, 0         // Offset to pixel data (54 + palette size)
    };
    *(int*)&fileHeader[2] = fileSize;
    fwrite(fileHeader, 1, 14, fp);
 //fwrite syntax is: "size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);"

    // ----------------------------
    // DIB HEADER (40 bytes)
    // ----------------------------
    uint8_t dibHeader[40] = {0};
    *(int*)&dibHeader[0]  = 40;           // Header size
    *(int*)&dibHeader[4]  = WIDTH;
    *(int*)&dibHeader[8]  = HEIGHT;
    *(short*)&dibHeader[12] = 1;          // Color planes
    *(short*)&dibHeader[14] = 8;          // Bits per pixel
    *(int*)&dibHeader[16] = 0;            // Compression
    *(int*)&dibHeader[20] = pixelArraySize;  // Image size
    *(int*)&dibHeader[24] = 2835;         // X pixels per meter (72 DPI)
    *(int*)&dibHeader[28] = 2835;         // Y pixels per meter
    *(int*)&dibHeader[32] = 256;          // Number of colors
    *(int*)&dibHeader[36] = 256;          // Important colors
    fwrite(dibHeader, 1, 40, fp);

    // ----------------------------
    // Grayscale Palette (256 entries)
    // ----------------------------
    for (int i = 0; i < 256; i++) {
        uint8_t color[4] = {i, i, i, 0}; // BGR0 format
        fwrite(color, 1, 4, fp); 
    }

    // ----------------------------
    // Pixel Data (bottom-up BMP)
    // ----------------------------
    for (int i = HEIGHT - 1; i >= 0; i--) {
        fwrite(image[i], 1, WIDTH, fp);

        // Padding
        for (int p = 0; p < rowSize - WIDTH; p++)
            fputc(0x00, fp);
    }

    fclose(fp);
    printf("Saved as image.bmp\n");
    return 0;
}