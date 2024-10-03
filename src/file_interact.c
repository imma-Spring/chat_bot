#include<stdio.h>
#include<string.h>

#include "file_interact.h"

void write_line(FILE *fp,char* line) {
  fprintf(fp, "%s\n", line);
}

void write_words(FILE *fp, char *line) {
  char *word;
  word = strtok(line, " ");
  while(word != NULL) {
    fprintf(fp, "%s\n", word);
    word = strtok(NULL, " ");
  }
}

void read_file(FILE *fp, char ***lines, size_t *num_lines) {
  char buffer[256];
  size_t count = 0;
  int capacity = 10;

  *lines = (char **)malloc(capacity * sizeof(char *));

  while (fgets(buffer, sizeof(buffer), fp)) {
    buffer[strcspn(buffer, "\n")] = 0;
    if (count >= capacity) {
      capacity *= 2;
      *lines = (char **)realloc(*lines, capacity * sizeof(char *)); 
    }

    (*lines)[count] = strdup(buffer);
    count++;
  }

  *num_lines = count;
}
