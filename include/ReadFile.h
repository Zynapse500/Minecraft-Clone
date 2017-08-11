//
// Created by chris on 11/08/2017.
//

#ifndef MINECRAFT_CLONE_READFILE_H
#define MINECRAFT_CLONE_READFILE_H

#include <fstream>

// Returns pointer to heap data containing file contents
char* readFile(const char* path) {
    char* data = nullptr;

    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if(file.is_open()) {
        std::streamsize size = std::streamsize(file.tellg());
        file.seekg(0);

        data = new char[size + 1];
        file.read(data, size);
        data[size] = '\0';
    }

    return data;
}


#endif //MINECRAFT_CLONE_READFILE_H
