// C libs
#include <stdio.h>

// Project libs
#include "../include/ansilib.h"
#include "../include/colorslib.h"
#include "../include/tableslib.h"

void print_table()
{
  printf(ANSI_COLOR_CYAN);
  print_column_header(4, "Columna 1", "Columna 2", "Columna 3", "Columna n...");
  printf(ANSI_COLOR_RESET);
  printf("\n");
}

