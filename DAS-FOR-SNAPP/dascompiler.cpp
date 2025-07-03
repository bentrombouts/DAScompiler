#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>  // timing
#include <iomanip>  // for std::setprecision

void replace_all(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) return;
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();  // Move past the replacement
    }
}

int main() {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << inFile.rdbuf();
    inFile.close();

    std::string content = buffer.str();

    const std::vector<std::pair<std::string, std::string>> replacements = {
        {"var ", ""}, {"v_", "V"}, {"system.out", "OUT"}, {" = ", "."},
        {"nil", ""}, {"+", "ADD"}, {"-", "SUB"}, {"/", "DIV"},
        {"*", "MUL"}, {"function.create", "FUNC"}, {"function.call", "CALL"},
        {"  ", ""}, {" do", ""}, {"if", "IF"},
    };

    for (const auto& [from, to] : replacements) {
        replace_all(content, from, to);
    }

    std::ofstream outFile("compiledfile.snas");
    if (!outFile) {
        std::cerr << "Failed to write to file.\n";
        return 1;
    }

    outFile << content;
    outFile.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << std::fixed << std::setprecision(3) << "File updated successfully in " << duration.count() / 1000.0 << " seconds.\n";

    return 0;
}
