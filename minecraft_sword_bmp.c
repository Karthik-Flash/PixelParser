//MINECRAFT SWORD in BMP format
#include <stdio.h>
#include <stdint.h>

#define WIDTH 12
#define HEIGHT 10

#pragma pack(push, 1)

typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPHeader;

typedef struct {
    uint32_t size;
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

// 0 = black, 1 = cyan, 2 = turquoise, 3 = brown
int sword[12][10] = {
    {0,0,0,0,0,2,0,0,0,0},   // Tip
    {0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0},
    {0,0,0,2,2,3,2,2,0,0},
    {0,0,0,0,0,3,0,0,0,0},   // Cross guard
    {0,0,0,0,0,1,0,0,0,0}    // Bottom of cross
};

int main() {
    FILE *fp = fopen("sword.bmp", "wb");
    if (!fp) {
        perror("Failed to create BMP file");
        return 1;
    }

    int rowSize = (3 * WIDTH + 3) & ~3;
    int imageSize = rowSize * HEIGHT;

    BMPHeader bmp = {
        .type = 0x4D42,
        .size = sizeof(BMPHeader) + sizeof(DIBHeader) + imageSize,
        .reserved1 = 0,
        .reserved2 = 0,
        .offset = sizeof(BMPHeader) + sizeof(DIBHeader)
    };
    fwrite(&bmp, sizeof(bmp), 1, fp);

    DIBHeader dib = {
        .size = sizeof(DIBHeader),
        .width = WIDTH,
        .height = HEIGHT,
        .planes = 1,
        .bitsPerPixel = 24,
        .compression = 0,
        .imageSize = imageSize,
        .xPixelsPerM = 2835,
        .yPixelsPerM = 2835,
        .colorsUsed = 0,
        .importantColors = 0
    };
    fwrite(&dib, sizeof(dib), 1, fp);

    uint8_t padding[3] = {0, 0, 0};
    int padSize = rowSize - WIDTH * 3;

    for (int y = HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < WIDTH; x++) {
            uint8_t pixel[3];
            switch (sword[y][x]) {
                case 1:  // Cyan
                    pixel[0] = 255; pixel[1] = 255; pixel[2] = 0;
                    break;
                case 2:  // Turquoise (Green-Blue)
                    pixel[0] = 208; pixel[1] = 224; pixel[2] = 64;
                    break;
                case 3:  // Brown
                    pixel[0] = 42; pixel[1] = 42; pixel[2] = 165;
                    break;
                default: // Black
                    pixel[0] = 0; pixel[1] = 0; pixel[2] = 0;
                    break;
            }
            fwrite(pixel, 3, 1, fp);
        }
        fwrite(padding, padSize, 1, fp);
    }

    fclose(fp);
    printf("BMP image 'sword.bmp' created successfully.\n");
    return 0;
}
