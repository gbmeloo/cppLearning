#include <iostream>
#include <cstring> // for strlen
#include <fstream> // for file operations

int main(int argc, char* argv[]) 
{

    if (argc < 2) {
        std::cout << "Please provide at least one word as an argument." << std::endl;
        return 1;
    }

    std::string stringConcat;
    std::string fileName;

    for (int i = 1; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
        std::cout << "Length of word: " << strlen(argv[i]) << std::endl;
        if (std::string(argv[i]) == "-o") {
            if (i + 1 < argc) {
                fileName = std::string(argv[i + 1]) + ".txt";
                std::cout << "Output file name: " << fileName << std::endl;
                continue;
            } else {
                std::cerr << "Error: No file name provided after -o command." << std::endl;
                return 1;
            }
        }
        stringConcat += argv[i];
        if (i < argc - 1) {
            stringConcat += " ";
        } else if (i == argc - 1) {
            stringConcat += ".";
        }        
    }

    std::cout << "Concatenated string: " << stringConcat << std::endl;

    // Write to file
    if (fileName.empty()) {
        std::ofstream outFile("output.txt");
        outFile << stringConcat;
        outFile.close();
        std::cout << "The text was written to the file: " << "output.txt" << std::endl;
        std::cout << fileName.empty() << std::endl; // Debugging if fileName is empty
    } else {
        std::ofstream outFile(fileName);
        outFile << stringConcat;
        outFile.close();
        std::cout << "The text was written to the file: " << fileName << std::endl;
    }

    return 0;
}