// C libs
#include <stdio.h>

// Project libs
#include "../include/ansilib.h"

void clear_screen()
{
  printf("\e[1;1H\e[2J");
}

