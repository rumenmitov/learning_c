#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* args[]) {
    if (argc == 1) {
        fprintf(stderr, "Please provide a filename!\nE.g. pretty <myfile>\n");
        return 1;
    }

    if (argc > 2) {
        fprintf(stderr, "The program supports only one filename at a time!\n");
        return 1;
    }

    if (access(args[1],F_OK) == -1) {
        fprintf(stderr, "The provided file %s does not exist!\n", args[1]);
        return 1;
    }

    char command[255] = "prettier "; 
    strcat(command, args[1]);
    strcat(command, " > temp");
    system(command);

    FILE* temp = fopen("temp", "r");
    FILE* userFile = fopen(args[1], "w");

    char line[255];
    while(fgets(line, 255, temp)) {
        fprintf(userFile, "%s", line);
    }

    fclose(temp);
    fclose(userFile);

    remove("temp");
    return 0;
}
