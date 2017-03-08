#include "../shell.h"

int main(int argc, char **argv, char **envp) {

  char c = '\0';
  while (c != EOF) {
    printf("[Iterate_Shell] ");
    get_command();
    switch(get_status()) {
      case 1 :
        if (fork() == 0)
        {
          execve("/bin/ls", argv, envp);
        }
        else{
          wait(NULL);
        }
        break;
      case 2 :
        if (fork() == 0)
        {
          execve("/usr/bin/clear", argv, envp);
        }
        else{
          wait(NULL);
        }
        break;
      default:
        break;
    }
    status = 0;
  }
  return 0;
}
