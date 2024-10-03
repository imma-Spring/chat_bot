#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "file_interact.h"


int main(int argc, char **argv) {
  if (argc == 1) {
    printf("Usage %s, <n>\n", argv[0]);
    return -1;
  }
  //size_t len1 = strlen(argv[1]);
  //size_t len2 = strlen(argv[2]);
  //size_t score = compare_strings(argv[1], len1, argv[2], len2);

  //double true_score = score / (double)MIN(len1, len2);
  //printf("score: %zu, %f\n", score, true_score);
  char path1[256];
  char path2[256];
  const char *home = getenv("HOME");
  snprintf(path1, sizeof(path1), "%s/projects/chat_bot/lines", home);
  snprintf(path2, sizeof(path2), "%s/projects/chat_bot/words", home);
  FILE *fp1;
  fp1 = fopen(path1, "a");
  assert(fp1 && "Could not open file1");
  FILE *fp2;
  fp2 = fopen(path2, "a");
  assert(fp2 && "Could not open file2");
  int n = atoi(argv[1]);
  for (int i = 0; i < n; ++i) {
  char line[256];
  fgets(line, sizeof(line), stdin);

  line[strcspn(line, "\n")] = 0;

  //printf("%s\n", line);
  
  write_line(fp1, line);
  write_words(fp2, line);
  }
  fclose(fp1);
  fclose(fp2);
  char **lines;
  size_t num_lines = 0;
  char **words;
  size_t num_words = 0;
  char line[256];
  fgets(line, sizeof(line), stdin);
  fp1 = fopen(path1, "r");
  fp2 = fopen(path2, "r");

  read_file(fp1, &lines, &num_lines);
  read_file(fp2, &words, &num_words);

  fclose(fp1);
  fclose(fp2);

  printf("AI:\n");
  char *word = generate_word();
  char *line = generate_line(lines, words, num_lines, num_words, word);
  
  free(lines);
  free(words);
}
