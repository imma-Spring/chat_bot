#include "chat_bot.h"
#include <math.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? (-a) : (a))
#define RAND(a, b) ((rand() % ((b) - (a) + 1)) + (a))

char row1[28] = {'{', '}', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char row2[28] = {'[', ']', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char row3[12] = {'(', ')', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char row4[27] = {' ', '_', '@', '?', '!', '.', ',', ';', ':', '|', '&', '%', '$', '#', '*', '+', '-', '/', '\\', '"', '\'', '`', '~', '=', '<', '>', '^'};

typedef struct {
  int x, y;
} Vec2;

static Vec2 get_pos(char c) {
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

static size_t compare_char(char c1, char c2) {
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

static size_t compare_strings(char *str1, size_t len1, char *str2, size_t len2) {
  size_t score = 0;
  size_t length = MIN(len1, len2);
  for (size_t i = 0; i < length; ++i) {
    score += compare_char(str1[i], str2[i]);
  }
  return score;
}

static char *generate_word() {
  char buffer[11];
  int n = 1;
  for (int i = 0; i < 10; ++i) {
    int row = RAND(0, 4);
    int col = 0;
    if (row == 0 || row == 1) {
      col = RAND(-1, 28);
      if (col == -1) break;
      if (row == 0) buffer[i] = row1[col];
      else buffer[i] = row2[col];
    } else if (row == 2) {
      col = RAND(-1, 12);
      if (col == -1) break;
      buffer[i] = row3[col];
    } else {
      col = RAND(-1, 27);
      if (col == -1) break;
      buffer[i] = row3[col];
    }
    n++;
  }
  buffer[n] = 0;
  return buffer;
}

static void combine_string(char *str1, char *str2, int space) {
  if (space == 0) {
    strcat(str1, " ");
  }
  strcat(str1, str2);
}

static float check_score(char *line1, char *line2, char *added_word, char **lines, size_t num_lines, int space) {
}

char *generate_line(char *input, char **lines, char **words, size_t num_lines, size_t num_words) {
  char *random_word = generate_word();
  float prev_avarage_score = 0;
  char response[256];
  for (int i = 0; i < 10; ++i) {
    float max_avg_score = -1;
    size_t n = -1;
    for (size_t j = 0; j < num_words; ++j) {
      float average_score = check_score(response, input, words[j], lines, num_lines, (i == 0 ? 0 : 1));
      if (average_score > max_average_score) {
        n = j;
        max_average_score = average_score;
      }
    }
    if (max_average_score < prev_average_score) {
      break;
    }
    prev_average_score = max_average_score;
  }
}
