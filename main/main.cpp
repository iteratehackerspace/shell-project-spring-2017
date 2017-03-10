#include "../shell.h"

int main(void) {

  char  line[128];
  char  *argv[128];
  char c = '\0';

  while (c != EOF) {
    printf("[Iterate_Shell] ");
    gets(line); //reads the line
    parse(line, argv);
    execute(argv);
  }
  return 0;
}
