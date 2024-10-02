#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? (-a) : (a))

char row1[28] = {'{', '}', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char row2[28] = {'[', ']', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char row3[12] = {'(', ')', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char row4[27] = {' ', '_', '@', '?', '!', '.', ',', ';', ':', '|', '&', '%', '$', '#', '*', '+', '-', '/', '\\', '"', '\'', '`', '~', '=', '<', '>', '^'};

typedef struct {
  int x, y;
} Vec2;

Vec2 get_pos(char c) {
  if (c == '{') {
    Vec2 v;
    v.x = 0;
    v.y = 0;
    return v;
  }
  if (c == '}') {
    Vec2 v;
    v.x = 1;
    v.y = 0;
    return v;
  }
  if (c < 91 && c > 64) {
    int p = c - 64 + 2;
    Vec2 v;
    v.x = p;
    v.y = 0;
    return v;
  }

  if (c == '[') {
    Vec2 v;
    v.x = 0;
    v.y = 1;
    return v;
  }
  if (c == ']') {
    Vec2 v;
    v.x = 1;
    v.y = 1;
    return v;
  }
  if (c < 123 && c > 96) {
    int p = c - 96 + 2;
    Vec2 v;
    v.x = p;
    v.y = 1;
    return v;
  }

  if (c == '(') {
    Vec2 v;
    v.x = 0;
    v.y = 2;
    return v;
  }
  if (c == ')') {
    Vec2 v;
    v.x = 1;
    v.y = 2;
    return v;
  }
  if (c < 58 && c > 47) {
    int p = c - 47 + 2;
    Vec2 v;
    v.x = p;
    v.y = 2;
    return v;
  }

  Vec2 v;
  v.x = -1;
  v.y = 3;
  for (size_t i = 0; i < 27; ++i) {
    if (c == row4[i]) {
      v.y = i;
      return v;
    }
  }
  return v;
}

size_t compare_char(char c1, char c2) {
  Vec2 pos1 = get_pos(c1), pos2 = get_pos(c2);
  double dx = ABS(pos1.x - pos2.x);
  double dy = ABS(pos1.y - pos2.y);
  double d = sqrt(dx * dx + dy * dy);
  char e1 = ' ', e2 = 'Z';
  Vec2 pose1 = get_pos(e1), pose2 = get_pos(e2);
  double edx = ABS(pose1.x - pose2.x);
  double edy = ABS(pose1.y - pose2.y);
  double val = sqrt(edx * edx + edy + edy) - d;
  return val < 10 ? 0 : (size_t)val;
}

size_t compare_strings(char *str1, size_t len1, char *str2, size_t len2) {
  size_t score = 0;
  size_t length = MIN(len1, len2);
  for (size_t i = 0; i < length; ++i) {
    score += compare_char(str1[i], str2[i]);
  }
  return score;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: %s <string1> <string2>\n", argv[0]);
    return -1;
  }
  size_t len1 = strlen(argv[1]);
  size_t len2 = strlen(argv[2]);
  size_t score = compare_strings(argv[1], len1, argv[2], len2);

  double true_score = score / (double)MIN(len1, len2);
  printf("score: %zu, %f\n", score, true_score);
}
