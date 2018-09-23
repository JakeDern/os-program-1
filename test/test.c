#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  // char arr[] = "something";
  // arr = "something";
  // printf("%s\n", arr);

  char *base = "something";
  char *path = "/something longer";
  char *file_path = malloc(sizeof(base) + sizeof(path));
  strcpy(file_path, base);
  strcat(file_path, path);
  printf("%s\n", file_path);
  
}