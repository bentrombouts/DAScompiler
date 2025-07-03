#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include <regex>

void replace_all(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) return;
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
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

    // First replace keywords
    const std::vector<std::pair<std::string, std::string>> replacements = {
        {"var ", ""}, {"v_", "V"}, {"system.out", "OUT"}, {" = ", "."},
        {"nil", ""}, {"+", "ADD"}, {"-", "SUB"}, {"/", "DIV"},
        {"*", "MUL"}, {"function.create", "FUNC"}, {"function.call", "CALL"},
        {"  ", ""}, {" do", ""}, {"if", "IF"},
    };
    for (const auto& [from, to] : replacements) {
        replace_all(content, from, to);
    }

    // Split lines
    std::stringstream ss(content);
    std::string line;
    std::vector<std::string> outputLines;
    std::unordered_map<std::string, int> vars;

    std::regex varDefRegex(R"(V(\w+)\.(\d+))");  // Matches Vname.value
    std::regex opRegex(R"(V(\w+)\.V(\w+)\s+(ADD|SUB|MUL|DIV)\s+V(\w+))");

    while (std::getline(ss, line)) {
        std::smatch match;

        // Match variable definition
        if (std::regex_match(line, match, varDefRegex)) {
            std::string varName = match[1];
            int value = std::stoi(match[2]);
            vars[varName] = value;
            outputLines.push_back(line);
            continue;
        }

        // Match operation
        if (std::regex_match(line, match, opRegex)) {
            std::string dest = match[1];
            std::string left = match[2];
            std::string op = match[3];
            std::string right = match[4];

            if (vars.count(left) && vars.count(right)) {
                int result = 0;
                if (op == "ADD") result = vars[left] + vars[right];
                else if (op == "SUB") result = vars[left] - vars[right];
                else if (op == "MUL") result = vars[left] * vars[right];
                else if (op == "DIV") result = vars[right] != 0 ? vars[left] / vars[right] : 0;

                vars[dest] = result;  // Save new var
                outputLines.push_back("V" + dest + "." + std::to_string(result));
                continue;
            }
        }

        // No match — just keep line
        outputLines.push_back(line);
    }

    // Output
    std::ofstream outFile("compiledfile.snas");
    if (!outFile) {
        std::cerr << "Failed to write to file.\n";
        return 1;
    }

    for (const std::string& outLine : outputLines) {
        outFile << outLine << '\n';
    }
    outFile.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << std::fixed << std::setprecision(3)
              << "File updated successfully in " << duration.count() / 1000.0 << " seconds.\n";
    return 0;
}
