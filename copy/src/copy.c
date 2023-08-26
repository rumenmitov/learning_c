#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char fileName[255];
    char baseName[255];
    char extName[255];
} File;

File createNewUserfile(char* currentFile);

int checkIfExtExists(char* filename);

void copyFile(File* userFile);

int main(int argc, char* args[]) {
    if (argc > 1) {
        for (size_t i = 1; i < argc; i++) {
            File userFile = createNewUserfile(args[i]);
            copyFile(&userFile);
        }

        return 0;
    } 
    printf("State the files you want to backup!(Maximum of 20 file names at a time.)\n");

    char input[255];
    fgets(input, 255, stdin);
    input[strlen(input)-1] = '\0';

    char* currentFile;

    currentFile = strtok(input, " ");
    while (currentFile != NULL) {
        File userFile = createNewUserfile(currentFile);
        copyFile(&userFile);
        currentFile = strtok(NULL, " ");
    }

    return 0;
}

File createNewUserfile(char* filename) {
    File userFile;
    strcpy(userFile.fileName, filename);
    userFile.baseName[0] = '\0';
    if (checkIfExtExists(filename)) {
        strcpy(userFile.extName, ".");
    } else {
        userFile.extName[0] = '\0';
    }

    return userFile;
}

int checkIfExtExists(char* filename) {
    int returnValue = 0;
    for (int i = 0; i < strlen(filename); i++) {
        if (filename[i] == '.') {
            returnValue = 1;
            break;
        }
    }

    return returnValue;
}

void copyFile(File* userFile) {
    // Finding baseName
    char* basename = (char*) malloc(sizeof(char));
    for (size_t i = 0; i < strlen(userFile->fileName); i++) {
        char currentChar = (*userFile).fileName[i];
        if (currentChar != '.') {
            basename[i] = currentChar;
            basename = (char*) realloc(basename, (strlen(basename)+1) * sizeof(char));
        } else {
            break;
        }
    }
    basename[strlen(basename)] = '\0';
    strcpy(userFile->baseName, basename);
    free(basename);
    basename = NULL;

    // Finding extName
    if (strcmp(userFile->extName, ".") == 0) {
        // NOTE when extension exists subtract extra byte for '.' and add byte for '\0'; net bytes = 0
        char* extname = (char*)
            malloc(sizeof(char) * (strlen(userFile->fileName) - strlen(userFile->baseName)));
        strcpy(extname, ".");

        int isExtension = 0;

        for (size_t i = 0; i < strlen(userFile->fileName); i++) {
            char currentChar = (*userFile).fileName[i];
            if (isExtension) {
                strncat(extname, &currentChar, sizeof(char));
            } else {
                if (currentChar != '.') {
                    continue;
                }

                isExtension = 1;
            }
        }

        strcpy(userFile->extName, extname);
        free(extname);
        extname = NULL;
    }


    FILE* file = fopen(userFile->fileName, "r");

    if (file == NULL) {
        fprintf(stderr, "Your file %s cannot be copied because it does not exist.\n", userFile->fileName);
        return;
    }

    char copied_name[255];
    strcpy(copied_name, userFile->baseName);
    strcat(copied_name, "_copy");
    if ((*userFile).extName[0] == '.') {
        strcat(copied_name, userFile->extName);
    }

    FILE* file_copy = fopen(copied_name, "w");

    char line[255];
    while(fgets(line, 255, file)) {
        fprintf(file_copy, "%s", line);
    }

    fclose(file);
    fclose(file_copy);

}
