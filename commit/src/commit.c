#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* args[]) {

  char commitMessage[255] = "git commit -m \"";

  for (int i = 1; i < argc; i++) {
    strcat(commitMessage, args[i]);
    strcat(commitMessage, " ");
  }

  commitMessage[strlen(commitMessage)-1] = '"';
  
  system(commitMessage);
  return 0;
}
