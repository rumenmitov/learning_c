#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* args[]) {
  if (argc == 1) {
    printf("Please provide a filename!\n");
    return 1;
  }

  if (argc > 2) {
    printf("The program supports only one filename at a time!\n");
    return 1;
  }

  if (access(args[1],F_OK) == -1) {
    printf("The provided file does not exist!\n");
    return 1;
  }

  char command[255] = "prettier "; 
  strcat(command, args[1]);
  strcat(command, " > temp");
  system(command);

  strcpy(command, "cat temp > ");
  strcat(command, args[1]);
  strcat(command, " && rm temp");
  system(command);

  return 0;
}
