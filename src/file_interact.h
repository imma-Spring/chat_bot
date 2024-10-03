#pragma once
#include <stdio.h>
#include <stdlib.h>

void write_line(FILE *fp, char *line);
void write_words(FILE *fp, char *line);
void read_file(FILE *fp, char ***lines, size_t *num_lines);
