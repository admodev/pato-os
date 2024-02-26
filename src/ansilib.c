// C libs
#include <stdio.h>
#include <stdarg.h>

// Project libs
#include "../include/ansilib.h"

void clear_screen()
{
  printf("\e[1;1H\e[2J");
}

void print_column_header(int headers, ...)
{ 
  va_list args;
  va_start(args, headers);

  for (int i = 0; i < headers; i++)
  {
    char *header_str = va_arg(args, char *);
    printf("%s ", header_str);
  }

  printf("\n");
  va_end(args);
}

