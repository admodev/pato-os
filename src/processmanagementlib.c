// C libs
#include <stdio.h>
#include <unistd.h>

// Project libs
#include "../include/processmanagementlib.h"

int schedule_process()
{
  fork();
  printf("Hello, World! %d\n", getpid());

  return 0;
}
