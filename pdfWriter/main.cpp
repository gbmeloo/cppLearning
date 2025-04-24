#include <iostream>
#include <fstream>

int main() {
    std::ofstream file("hello.pdf", std::ios::binary);

    std::string pdf = 
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
        "/Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 44 >>\n"
        "stream\n"
        "BT /F1 24 Tf 100 700 Td (Hello, World!) Tj ET\n"
        "endstream\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000010 00000 n \n"
        "0000000060 00000 n \n"
        "0000000116 00000 n \n"
        "0000000233 00000 n \n"
        "0000000324 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "390\n"
        "%%EOF\n";

    file << pdf;
    file.close();

    std::cout << "PDF 'hello.pdf' created successfully.\n";
    return 0;
}