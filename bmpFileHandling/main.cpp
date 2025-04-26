#include <iostream>
#include "bmp.h"


int main(int argc, char* argv[]) {

    // Closing if argument count is not satisfied
    if (argc < 2) {
        std::cout << "Usage: ./bmpInvert.out [imagePath] [imageOut]";
        return 1;
    }

    std::string inFile = argv[1];
    std::string outFile = argv[2];

    // Opening file and saving file 
    try {
        BMP bmp;
        bmp.load(inFile);
        std::cout << "File opened succesfully" << std::endl;
        bmp.invert();
        bmp.save(outFile);
        std::cout << "File saved successfully to: " << outFile << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    
}