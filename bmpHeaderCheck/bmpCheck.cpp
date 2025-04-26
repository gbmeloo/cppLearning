#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdint>

// Define the BMP header structs
#pragma pack(push, 1) // Ensure no padding bytes
struct BITMAPFILEHEADER {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BITMAPINFOHEADER {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop) // Restore normal packing

void check_bmp_format(const BITMAPFILEHEADER& bf, const BITMAPINFOHEADER& bi) {
    if (bf.bfType != 0x4D42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        throw std::runtime_error("Unsupported BMP file format.");
    }
}

int main() {
    try {
        std::ifstream inFile("courtyard.bmp", std::ios::binary);
        if (!inFile) {
            throw std::runtime_error("Failed to open input file.");
        }

        BITMAPFILEHEADER bf{};
        BITMAPINFOHEADER bi{};

        inFile.read(reinterpret_cast<char*>(&bf), sizeof(bf));
        inFile.read(reinterpret_cast<char*>(&bi), sizeof(bi));

        check_bmp_format(bf, bi);

        std::cout << "BMP file loaded successfully!" << std::endl;
        
        // Continue processing...
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
