#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

void ema_search_str(const char *filename, const char *pattern, int repetitions) {
    std::ifstream file(filename);
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    std::string buffer;
    size_t pattern_len = strlen(pattern);
    for (int i = 0; i < repetitions; i++) {
        file.clear();
        file.seekg(0);
        while (std::getline(file, buffer)) {
            if (buffer.length() >= pattern_len && buffer.find(pattern) != std::string::npos) {
                std::cout << "Found pattern: " << buffer << std::endl;
            }
        }
    }
    file.close();
}


