// C libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Project libs
#include "../include/ansilib.h"
#include "../include/colorslib.h"
#include "../include/tableslib.h"

struct cpu_info {
    char *param;
    char *value;
};

void print_table()
{
  printf(ANSI_COLOR_CYAN);
  print_column_header(4, "Columna 1", "Columna 2", "Columna 3", "Columna n...");
  printf(ANSI_COLOR_RESET);
  printf("\n");
}

int cpuinfo_table()
{
  FILE *file;
  char line[MAX_LINE_LENGTH];
  struct cpu_info *info = NULL;
  int num_info = 0;
  int max_param_width = 0;
  int max_value_width = 0;

  file = fopen("/proc/cpuinfo", "r");

  if (NULL == file)
  {
    printf("File can't be opened.\n");
    return -1;
  }

  while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
  {
    char *param = strtok(line, ":");
    char *value = strtok(NULL, ":");

    if (param != NULL && value != NULL)
    {
      char *trimmed_value = strtok(value, "\n");
      while (*trimmed_value == ' ' || *trimmed_value == '\t')
      {
        trimmed_value++;
      }
      int len = strlen(trimmed_value);
      while (len > 0 && (trimmed_value[len - 1] == ' ' || trimmed_value[len - 1] == '\t'))
      {
        trimmed_value[--len] = '\0';
      }

      info = realloc(info, (num_info + 1) * sizeof(struct cpu_info));
      if (info == NULL)
      {
        printf("Memory allocation failed.\n");
        fclose(file);
        return -1;
      }
      info[num_info].param = strdup(param);
      info[num_info].value = strdup(trimmed_value);
      num_info++;

      // Update maximum column widths
      int param_width = strlen(param);
      int value_width = strlen(trimmed_value);
      if (param_width > max_param_width)
      {
        max_param_width = param_width;
      }
      if (value_width > max_value_width)
      {
        max_value_width = value_width;
      }
    }
  }

  fclose(file);
 
  printf(ANSI_COLOR_CYAN);
  printf("| %-*s | %-*s |\n", max_param_width, "Parameter", max_value_width, "Value");
  printf("|%-*s|%-*s|\n", max_param_width, "------------------", max_value_width, "------------------");
  printf(ANSI_COLOR_RESET);

  printf(ANSI_COLOR_BLUE);
  for (int i = 0; i < num_info; i++)
  {
    printf("| %-*s | %-*s |\n", max_param_width, info[i].param, max_value_width, info[i].value);
    free(info[i].param);
    free(info[i].value);
  }
  free(info);
  printf(ANSI_COLOR_RESET);

  return 0;
}

