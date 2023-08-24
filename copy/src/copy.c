// Stuff to add:
// 1. cli input
// 2. user specified '_copy' name



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char fileName[255];
  char baseName[255];
  char extName[255];
} File;

File createNewUserfile(char* currentFile);

void copyFile(File* userFile);

char* reverseString(char input[255]);

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
    printf("Copying file: %s\n", currentFile);
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
  strcpy(userFile.extName, ".");
  
  return userFile;
}

void copyFile(File* userFile) {
  // Finding baseName
  for (size_t i = 0; i < strlen(userFile->fileName); i++) {
    char currentChar = (*userFile).fileName[i];
    if (currentChar != '.') {
      (*userFile).baseName[i] = currentChar;
    } else {
      (*userFile).baseName[i] = '\0';
      break;
    }
  }

  // Finding extName
  char* extName_reverse = (char*) malloc( (strlen(userFile->extName)+1) * sizeof(char) );

  int isExtension = 0;

  for (size_t i = 0; i < strlen(userFile->fileName); i++) {
    char currentChar = (*userFile).fileName[i];
    if (isExtension) {
      extName_reverse[strlen(extName_reverse)] = currentChar;
    } else {
      if (currentChar != '.') {
        continue;
      }
      
      isExtension = 1;
    }
  }
  char* reversedExt = reverseString(extName_reverse);
  strcat(userFile->extName, reversedExt);
  free(reversedExt);
  reversedExt = NULL;

  FILE* file = fopen(userFile->fileName, "r");

  if (file == NULL) {
    printf("Your file %s cannot be copied because it does not exist.\n", userFile->fileName);
    return;
  }

  char copied_name[255];
  strcpy(copied_name, userFile->baseName);
  strcat(copied_name, "_copy");
  strcat(copied_name, userFile->extName);

  FILE* file_copy = fopen(copied_name, "w");

  char line[255];
  while(fgets(line, 255, file)) {
    fprintf(file_copy, "%s", line);
  }

  fclose(file);
  fclose(file_copy);

}

char* reverseString(char input[255]) {
  char* result = (char* ) malloc( ( strlen (input)+1 ) * sizeof(char) );

  const size_t lastIndex = strlen(input)-1;
  for (size_t i = 0; i <= lastIndex; i++) {
    result[i] = input[lastIndex-i];
  }

  result[strlen(input)] = '\0';

  return result;
}