#pragma once

#include <string>
#include <cstdint>
#include <vector> 

#pragma pack(push, 1)

using BYTE  = uint8_t;
using WORD  = uint16_t;
using DWORD = uint32_t;
using LONG  = int32_t;

struct BITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
};

struct BITMAPINFOHEADER {
    DWORD biSize;
    LONG  biWidth;
    LONG  biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG  biXPelsPerMeter;
    LONG  biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
};

struct RGBTRIPLE {
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
};

#pragma pack(pop)

class BMP {
public:
    BMP() = default;
    void load(const std::string& filename);
    void save(const std::string& filename) const;
    void check_format() const;
    void invert();
    
private:
    BITMAPFILEHEADER fileHeader{};
    BITMAPINFOHEADER infoHeader{};
    std::vector<RGBTRIPLE> pixels; 
};
