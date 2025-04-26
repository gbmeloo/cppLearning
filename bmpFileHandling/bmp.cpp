#include "bmp.h"
#include <fstream>
#include <stdexcept>

void BMP::load(const std::string& filename) {
    // Step 1: READ Header data (Bitmap file and Bitmap info) into memory
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    inFile.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    inFile.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    check_format(); // Checking if format is valid in headers

    // Step 2: READ pixel data into pixels vector
    inFile.seekg(fileHeader.bfOffBits, std::ios::beg);

    int width = infoHeader.biWidth;
    int height = std::abs(infoHeader.biHeight);
    int rowSize = (width * 3 + 3) & ~3; // padded row size

    pixels.resize(width * height);

    for (int row = 0; row < height; ++row) {
        int rowIndex = (infoHeader.biHeight > 0) ? (height - 1 - row) : row;

        std::vector<uint8_t> buffer(rowSize);
        inFile.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

        for (int col = 0; col < width; ++col) {
            RGBTRIPLE& pixel = pixels[rowIndex * width + col];

            pixel.rgbtBlue  = buffer[col * 3 + 0];
            pixel.rgbtGreen = buffer[col * 3 + 1];
            pixel.rgbtRed   = buffer[col * 3 + 2];
        }
    }
}

void BMP::save(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Failed to create file: " + filename);
    }

    // Write headers
    outFile.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    outFile.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

    int width = infoHeader.biWidth;
    int height = std::abs(infoHeader.biHeight);
    int rowSize = (width * 3 + 3) & ~3; // padded row size

    std::vector<uint8_t> buffer(rowSize);

    for (int row = 0; row < height; ++row) {
        int rowIndex = (infoHeader.biHeight > 0) ? (height - 1 - row) : row;

        for (int col = 0; col < width; ++col) {
            const RGBTRIPLE& pixel = pixels[rowIndex * width + col];
            buffer[col * 3 + 0] = pixel.rgbtBlue;
            buffer[col * 3 + 1] = pixel.rgbtGreen;
            buffer[col * 3 + 2] = pixel.rgbtRed;
        }

        // Zero out any padding bytes
        for (int p = width * 3; p < rowSize; ++p) {
            buffer[p] = 0;
        }

        outFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    }
}

void BMP::check_format() const {
    if (fileHeader.bfType != 0x4D42 || fileHeader.bfOffBits != 54 || 
        infoHeader.biSize != 40 || infoHeader.biBitCount != 24 ||
        infoHeader.biCompression != 0)
    {
        throw std::runtime_error("Unsupported BMP file format.");
    }
}


void BMP::invert() {
    for (auto& pixel : pixels) {
        pixel.rgbtRed   = 255 - pixel.rgbtRed;
        pixel.rgbtGreen = 255 - pixel.rgbtGreen;
        pixel.rgbtBlue  = 255 - pixel.rgbtBlue;
    }
}
