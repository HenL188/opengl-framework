#include "utils_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int get_file_size(char file_name[])
{
    // opening the file in read mode
    FILE* fp = fopen(file_name, "rb");
    if (fp == NULL) {
        printf("ERROR::%s::FAILED::TO::GET::SIZE", file_name);
        return 0;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file
    const long int file_size = ftell(fp);
    rewind(fp);
    // closing the file
    fclose(fp);

    return file_size;
}

const char* read_file(char* file_name) {
    FILE* fp = fopen(file_name, "rb");
    if (fp == NULL) {
        printf("ERROR::%s::FAILED::TO::OPEN", file_name);
        return nullptr;
    }

    long int file_size = get_file_size(file_name);

    if (file_size == 0) {
        return nullptr;
    }

    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "ERROR::MEMORY::ALLOCATION::FAILED\n");
        fclose(fp);
        return nullptr;
    }

    // 4. Read the entire file content at once using fread
    size_t bytes_read = fread(buffer, 1, file_size, fp);

    if (bytes_read < file_size) {
        if (ferror(fp)) {
            // A read error occurred (e.g., disk failure, permission issue)
            perror("Error reading file");
            return  nullptr;
        }
        if (feof(fp)) {
            // EOF was reached (this is the most likely case for your numbers)
            printf("Reached end of file early.\n");
            return  nullptr;
        }
    }

    if (bytes_read != (size_t)file_size) {
        fprintf(stderr, "ERROR::FILE::READ::FAILED. Read %zu of %ld bytes.\n", bytes_read, file_size);
        free(buffer);
        fclose(fp);
        return nullptr;
    }


    // 5. Null-terminate the buffer
    buffer[file_size] = '\0';

    fclose(fp);
    return buffer;
}
