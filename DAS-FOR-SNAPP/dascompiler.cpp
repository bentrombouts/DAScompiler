#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::ifstream inFile("compilefile.snapp");
    std::stringstream buffer;

    if (!inFile) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    buffer << inFile.rdbuf();  // Read entire file into buffer
    inFile.close();

    std::string content = buffer.str();
    std::string from = "var ";
    std::string to = "";
    std::string from1 = "v_";
    std::string to1 = "V";
    std::string from2 = "system.out";
    std::string to2 = "OUT";
    std::string from3 = " = ";
    std::string to3 = ".";
    std::string from4 = "nil";
    std::string to4 = "";
    std::string from5 = "+";
    std::string to5 = "ADD";
    std::string from6 = "-";
    std::string to6 = "SUB";
    std::string from7 = "/";
    std::string to7 = "DIV";
    std::string from8 = "*";
    std::string to8 = "MUL";
    std::string from9 = "function.create";
    std::string to9 = "FUNC";
    std::string from10 = "function.call";
    std::string to10 = "CALL";
    std::string from11 = "  ";
    std::string to11 = "";
    std::string from12 = " do";
    std::string to12 = "";
    std::string from13 = "if";
    std::string to13 = "IF";


    // Replace all occurrences
    size_t pos = 0;
    while ((pos = content.find(from, pos)) != std::string::npos) {
        content.replace(pos, from.length(), to);
        pos += to.length();
    }
    pos = 0;
    while ((pos = content.find(from1, pos)) != std::string::npos) {
        content.replace(pos, from1.length(), to1);
        pos += to1.length();
    }
    pos = 0;
    while ((pos = content.find(from2, pos)) != std::string::npos) {
        content.replace(pos, from2.length(), to2);
        pos += to2.length();
    }
    pos = 0;
    while ((pos = content.find(from3, pos)) != std::string::npos) {
        content.replace(pos, from3.length(), to3);
        pos += to3.length();
    }
    pos = 0;
    while ((pos = content.find(from4, pos)) != std::string::npos) {
        content.replace(pos, from4.length(), to4);
        pos += to4.length();
    }
    pos = 0;
    while ((pos = content.find(from5, pos)) != std::string::npos) {
        content.replace(pos, from5.length(), to5);
        pos += to5.length();
    }
    pos = 0;
    while ((pos = content.find(from6, pos)) != std::string::npos) {
        content.replace(pos, from6.length(), to6);
        pos += to6.length();
    }
    pos = 0;
    while ((pos = content.find(from7, pos)) != std::string::npos) {
        content.replace(pos, from7.length(), to7);
        pos += to7.length();
    }
    pos = 0;
    while ((pos = content.find(from8, pos)) != std::string::npos) {
        content.replace(pos, from8.length(), to8);
        pos += to8.length();
    }
    pos = 0;
    while ((pos = content.find(from9, pos)) != std::string::npos) {
        content.replace(pos, from9.length(), to9);
        pos += to9.length();
    }
    pos = 0;
    while ((pos = content.find(from10, pos)) != std::string::npos) {
        content.replace(pos, from10.length(), to10);
        pos += to10.length();
    }
    pos = 0;
    while ((pos = content.find(from11, pos)) != std::string::npos) {
        content.replace(pos, from11.length(), to11);
        pos += to11.length();
    }
    pos = 0;
    while ((pos = content.find(from12, pos)) != std::string::npos) {
        content.replace(pos, from12.length(), to12);
        pos += to12.length();
    }
    pos = 0;
    while ((pos = content.find(from13, pos)) != std::string::npos) {
        content.replace(pos, from13.length(), to13);
        pos += to13.length();
    }
    

    std::ofstream outFile("compiledfile.snas");  // Overwrite file
    outFile << content;
    outFile.close();

    std::cout << "File updated successfully.\n";
    return 0;
}