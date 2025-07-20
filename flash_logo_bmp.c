//flash logo in BMP format
#include <stdio.h>
#include <stdint.h>

#define WIDTH 20
#define HEIGHT 20

#pragma pack(push, 1) // Ensure no padding in structures

typedef struct {
    uint16_t type;       // "BM"
    uint32_t size;       // File size
    uint16_t reserved1;  // Always 0
    uint16_t reserved2;  // Always 0
    uint32_t offset;     // Offset to pixel data
} BMPHeader;

typedef struct {
    uint32_t size;          // DIB header size
    int32_t width;          // Image width
    int32_t height;         // Image height (positive = bottom-up)
    uint16_t planes;        // Always 1
    uint16_t bitsPerPixel;  // 24 for RGB
    uint32_t compression;   // No compression = 0
    uint32_t imageSize;     // Can be 0 for BI_RGB
    int32_t xPixelsPerM;    // Resolution
    int32_t yPixelsPerM;
    uint32_t colorsUsed;
    uint32_t importantColors;
} DIBHeader;

#pragma pack(pop)

// 1 = yellow (255,255,0), 0 = black (0,0,0)
int lightning[20][20] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};



int main() {
    FILE *fp = fopen("flash_logo.bmp", "wb");
    if (!fp) {
        perror("Failed to create BMP file");
        return 1;
    }

    // Padding per row (each row must be a multiple of 4 bytes)
    int rowSize = (3 * WIDTH + 3) & ~3;
    int imageSize = rowSize * HEIGHT;

    // Write BMP Header
    BMPHeader bmp = {
        .type = 0x4D42,  // "BM"
        .size = sizeof(BMPHeader) + sizeof(DIBHeader) + imageSize,
        .reserved1 = 0,
        .reserved2 = 0,
        .offset = sizeof(BMPHeader) + sizeof(DIBHeader)
    };
    fwrite(&bmp, sizeof(bmp), 1, fp);

    // Write DIB Header (BITMAPINFOHEADER)
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

    // Write pixel data (bottom to top)
    uint8_t padding[3] = {0, 0, 0};
    int padSize = rowSize - WIDTH * 3;

    for (int y = HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < WIDTH; x++) {
            if (lightning[y][x] == 1) {
                uint8_t yellow[3] = {0, 255, 255}; // BGR format
                fwrite(yellow, 3, 1, fp);
            } else {
                uint8_t black[3] = {0, 0, 0};
                fwrite(black, 3, 1, fp);
            }
        }
        fwrite(padding, padSize, 1, fp);
    }

    fclose(fp);
    printf("BMP image 'flash_logo.bmp' created successfully.\n");
    return 0;
}

