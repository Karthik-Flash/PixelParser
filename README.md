# PixelParser
## Image Generation and Conversion in C & Python

This project demonstrates how to generate and save grayscale and RGB images using various formats like **PGM**, **PPM**, and **BMP**. It also includes sample logos like **Minecraft Sword**, created manually using matrix data. The final part includes C,Python scripts for converting between image formats.

---

## 📷 1. Grayscale Intensity Image in PGM & BMP Format

### PGM (Portable Gray Map)
A horizontal grayscale gradient (black to white) is created and stored using the ASCII-based `.pgm` format.

- [C Code: grayscale_pgm.c](./grayscale_pgm.c)

- **Image Format:** PGM (P2)
- **Resolution:** 100 x 100

### BMP Conversion
The same grayscale gradient is converted into **BMP** format with a grayscale color palette.

- [C Code: `grayscale_to_bmp.c`](./grayscale_to_bmp.c)
- **Image Format:** BMP (8-bit grayscale)

> ✅ Output generated: `image.pgm` and `image_1000x1000.bmp`  

<img width="642" height="615" alt="image" src="https://github.com/user-attachments/assets/1f0bf226-b1db-40d8-aaf7-2c61bedec129" />

---

## 🌈 2. RGB Gradient in PPM & BMP Format

### PPM (Portable Pixel Map)
Creates a 10x10 RGB image with a red gradient, constant green, and constant blue. Saved in ASCII `.ppm` format.

- [C Code: `rgb_gradient_ppm.c`](./rgb_gradient_ppm.c)
- **Image Format:** PPM (P3)
- **Resolution:** 10 x 10


### BMP Conversion
Generates a 1000x1000 RGB image with a red gradient and constant green/blue. Saved as `.bmp`.

- [C Code: `rgb_gradient_to_bmp.c`](./rgb_gradient_to_bmp.c)
- **Image Format:** BMP (24-bit RGB)

> 📸 **Preview of RGB Gradient (`rgb_image.bmp`)**  
> <img width="1000" height="1000" alt="image" src="https://github.com/user-attachments/assets/04eb62f3-af76-4745-9763-c0b3fc3cbee4" />
> ![RGB Gradient](./images/rgb_image.bmp)


---

## ⚡ 3. Flash Logo – PPM and BMP

The **Flash logo** is manually drawn using a `20x20` matrix. Yellow represents the lightning bolt, and black is the background(not accurate).

- [C Code: `flash_logo_ppm.c`](./flash_logo_ppm.c)
- [C Code: `flash_logo_bmp.c`](./flash_logo_bmp.c)
- **Image Formats:** PPM (P3), BMP (24-bit RGB)
- **Resolution:** 20 x 20

> 📸 **Flash Logo in BMP**  
> <img width="20" height="20" alt="image" src="https://github.com/user-attachments/assets/3150a04a-64c5-4313-8e4e-04c1f4f5bea8" />
*  


---

## 🗡️ 4. Minecraft Sword – BMP

A stylized Minecraft sword using a `12x10` matrix with indexed colors:
- **Cyan**, **Turquoise**, and **Brown** are used to depict the blade and handle.

- [C Code: `minecraft_sword_bmp.c`](./minecraft_sword_bmp.c)
- **Image Format:** BMP (24-bit RGB)
- **Resolution:** 12 x 10

> 📸 **Minecraft Sword in BMP**  
> <img width="12" height="10" alt="image" src="https://github.com/user-attachments/assets/fee28165-d45e-4ed9-87c8-9cafb104935c" />



---

## 🔁 5. Format Converters in C and Python

### a) BMP ➡️ PPM
Convert a `.bmp` file (grayscale or RGB) into a `.ppm` file.
- [C Code: `convert_image_formats_BMP_PPM.c`](./convert_image_formats_BMP_PPM.c)
#### example:
(i) BPM file -> [input.bpm](./otherfiles/input.bpm)  
<img width="860" height="981" alt="image" src="https://github.com/user-attachments/assets/33c90866-05a6-4dc3-af20-99a8ac5c545d" />

(ii) PPM file -> [output.ppm](./otherfiles/output.ppm)
<img width="1697" height="825" alt="image" src="https://github.com/user-attachments/assets/d6102167-7d63-4020-9aa2-a66d30c1e8d0" />

### b) PPM ➡️ PNG
Convert a `.ppm` file into a `.png` using Python libraries like `Pillow`.

- [Python Script: `convert_image_formats_PPM_PNG.py`](./convert_image_formats_PPM_PNG.py)
#### example:
(i) PPM same as above.
(ii) PNG -> [output.png](./otherfiles/output.png)

<img width="860" height="981" alt="image" src="https://github.com/user-attachments/assets/543045c5-f5e1-437c-b587-74837c08ce48" />
