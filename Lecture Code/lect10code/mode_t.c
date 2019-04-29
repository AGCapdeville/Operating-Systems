/*
   From: https://jameshfisher.com/2017/02/24/what-is-mode_t.html
   Snapshot taken on 11/14/17
*/

#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>

enum class { CLASS_OWNER, CLASS_GROUP, CLASS_OTHER };
enum permission { PERMISSION_READ, PERMISSION_WRITE, PERMISSION_EXECUTE };

const mode_t EMPTY_MODE = 0;

mode_t perm(enum class c, enum permission p) { return 1 << ((3 - p) + (2 - c) * 3); }

bool mode_contains(mode_t mode, enum class c, enum permission p) { return mode & perm(c, p); }

mode_t mode_add(mode_t mode, enum class c, enum permission p) { return mode | perm(c, p); }

mode_t mode_rm(mode_t mode, enum class c, enum permission p) { return mode & ~perm(c, p); }

// buf must have at least 10 bytes
void strmode(mode_t mode, char * buf) {
  const char chars[] = "rwxrwxrwx";
  for (size_t i = 0; i < 9; i++) {
    buf[i] = (mode & (1 << (8 - i))) ? chars[i] : '-';
  }
  buf[9] = '\0';
}

int main(void) {
  char buf[10];
  mode_t examples[] = { 0, 0666, 0777, 0700, 0100, 01, 02, 03, 04, 05, 06, 07 };
  size_t num_examples = sizeof(examples) / sizeof(examples[0]);
  for (size_t i = 0; i < num_examples; i++) {
    strmode(examples[i], buf);
    printf("%04o is %s\n", examples[i], buf);
  }
  return 0;
}