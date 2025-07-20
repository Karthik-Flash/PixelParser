#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#pragma pack(push, 1)

typedef struct {
    uint16_t type;       // Magic identifier: 0x4D42
    uint32_t size;       // File size in bytes
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;     // Offset to image data in bytes from beginning of file
} BMPHeader;

typedef struct {
    uint32_t size;         // DIB Header size (40 bytes)
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerM;
    int32_t yPixelsPerM;
    uint32_t colorsUsed;
    uint32_t importantColors;
} DIBHeader;

#pragma pack(pop)

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Pixel;

int main() {
    FILE *bmp = fopen("input2.bmp", "rb");
    if (!bmp) {
        perror("Error opening BMP file");
        return 1;
    }

    BMPHeader bmpHeader;
    fread(&bmpHeader, sizeof(BMPHeader), 1, bmp);
    if (bmpHeader.type != 0x4D42) {
        printf("Not a valid BMP file.\n");
        return 1;
    }

    DIBHeader dibHeader;
    fread(&dibHeader, sizeof(DIBHeader), 1, bmp);

    if (dibHeader.bitsPerPixel != 24 || dibHeader.compression != 0) {
        printf("Only uncompressed 24-bit BMP files are supported.\n");
        return 1;
    }

    int width = dibHeader.width;
    int height = dibHeader.height;
    int rowSize = (3 * width + 3) & ~3; // Padded row size

    Pixel **pixels = malloc(height * sizeof(Pixel*));
    for (int i = 0; i < height; i++) {
        pixels[i] = malloc(width * sizeof(Pixel));
    }

    fseek(bmp, bmpHeader.offset, SEEK_SET);

    for (int y = height - 1; y >= 0; y--) { // BMP is bottom-up
        for (int x = 0; x < width; x++) {
            uint8_t bgr[3];
            fread(bgr, 3, 1, bmp);
            pixels[y][x].r = bgr[2];
            pixels[y][x].g = bgr[1];
            pixels[y][x].b = bgr[0];
        }
        fseek(bmp, rowSize - (3 * width), SEEK_CUR); // Skip padding
    }

    fclose(bmp);

    // Write to PPM (Portable Pixmap) format
    FILE *ppm = fopen("output.ppm", "w");
    if (!ppm) {
        perror("Error creating PPM file");
        return 1;
    }

    fprintf(ppm, "P3\n%d %d\n255\n", width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fprintf(ppm, "%d %d %d  ", pixels[y][x].r, pixels[y][x].g, pixels[y][x].b);
        }
        fprintf(ppm, "\n");
    }

    fclose(ppm);

    for (int i = 0; i < height; i++) {
        free(pixels[i]);
    }
    free(pixels);

    printf("Converted BMP to PPM successfully (output.ppm)\n");
    return 0;
}
