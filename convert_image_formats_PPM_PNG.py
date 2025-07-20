from PIL import Image

def read_ppm(filename):
    with open(filename, 'r') as f:
        assert f.readline().strip() == 'P3'  # Make sure it's a P3 PPM
        while True:
            line = f.readline()
            if line[0] != '#':
                break
        width, height = map(int, line.strip().split())
        max_val = int(f.readline().strip())
        data = []
        for line in f:
            data.extend(map(int, line.strip().split()))
        pixels = [tuple(data[i:i+3]) for i in range(0, len(data), 3)]
        return width, height, pixels

def save_as_image(ppm_file, output_file):
    width, height, pixels = read_ppm(ppm_file)
    img = Image.new("RGB", (width, height))
    img.putdata(pixels)
    img.save(output_file)
    print(f"Saved: {output_file}")

# 🖼️ Convert 'output.ppm' to 'output.png' or 'output.bmp'
save_as_image("output.ppm", "output.png")  # Or use "output.bmp"
