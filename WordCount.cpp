#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h> 
#include <errno.h> 

int countCharacters(const char* fileName) {
    FILE* file;
    errno_t err = fopen_s(&file, fileName, "r");
    if (err != 0) {
        perror("Error opening file");
        return -1;
    }

    int count = 0;
    while (fgetc(file) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}

int countWords(const char* fileName) {
    FILE* file;
    errno_t err = fopen_s(&file, fileName, "r");
    if (err != 0) {
        perror("Error opening file");
        return -1;
    }

    int count = 0;
    bool inWord = false;
    int c;

    while ((c = fgetc(file)) != EOF) {
        if (isspace(c)) {
            inWord = false;
        }
        else if (!inWord) {
            inWord = true;
            count++;
        }
    }
    fclose(file);
    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c|-w] <input_file>\n", argv[0]);
        return 1;
    }

    const char* param = argv[1];
    const char* fileName = argv[2];

    if (strcmp(param, "-c") == 0) {
        int characters = countCharacters(fileName);
        printf("Characters: %d\n", characters);
    }
    else if (strcmp(param, "-w") == 0) {
        int words = countWords(fileName);
        printf("Words: %d\n", words);
    }
    else {
        fprintf(stderr, "Invalid parameter. Use '-c' for characters or '-w' for words.\n");
        return 1;
    }

    return 0;
}