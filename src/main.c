// C libs
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// Project libs
#include "../include/ansilib.h"
#include "../include/tableslib.h"
#include "../include/processmanagementlib.h"

// Type definitions
typedef struct
{
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

typedef enum
{
  CMD_EXIT,
  CMD_EMPTY,
  CMD_HELP,
  CMD_CLEARSC,
  CMD_TPROCS,
  CMD_CREATEPROC,
  CMD_CPUINFO,
  CMD_UNKNOWN
} Command;

Command get_command(const char *input)
{
  if (strcmp(input, "exit") == 0)
  {
    return CMD_EXIT;
  }
  else if (strcmp(input, "") == 0)
  {
    return CMD_EMPTY;
  }
  else if (strcmp(input, "helpme") == 0)
  {
    return CMD_HELP;
  }
  else if (strcmp(input, "clearsc") == 0)
  {
    return CMD_CLEARSC;
  }
  else if (strcmp(input, "tprocs") == 0)
  {
    return CMD_TPROCS;
  }
  else if (strcmp(input, "createproc") == 0)
  {
    return CMD_CREATEPROC;
  }
  else if(strcmp(input, "cpuinfo") == 0)
  {
    return CMD_CPUINFO;
  }
  else
  {
    return CMD_UNKNOWN;
  }
}

// End of type definitions

InputBuffer* new_input_buffer()
{
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void print_help_message()
{
  printf("Available commands are: exit, clearsc, tprocs, createproc, cpuinfo.\n");
}

// DON'T TOUCH IDENTATION OF THIS PRINT STATEMENTS...
void print_sys_name()
{
  printf(" _ __   __ _| |_ ___   ___  ___ \n");
  printf("| '_ \\ / _` | __/ _ \\ / _ \\/ __|\n");
  printf("| |_) | (_| | || (_) | (_) \\__ \\\n");
  printf("| .__/ \\__,_|\\__\\___/ \\___/|___/\n");
  printf("|_|\n");
}

void print_prompt()
{
  printf("> ");
}

void read_input(InputBuffer* input_buffer)
{
  ssize_t bytes_read =
    getline(&(input_buffer->buffer), &(input_buffer->buffer_length), 
        stdin);

  if (bytes_read <= 0)
  {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  input_buffer->input_length = bytes_read - 1;
  //-1 to Ignore trailing newline
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer)
{
  free(input_buffer->buffer);
  free(input_buffer);
}

int main(int argc, char* argv[])
{
  InputBuffer* input_buffer = new_input_buffer();

  print_sys_name();
  while (true)
  {
    print_prompt();
    read_input(input_buffer);

    switch (get_command(input_buffer->buffer))
    {
      case CMD_EXIT:
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
        break;
      case CMD_EMPTY:
        break;
      case CMD_HELP:
        print_help_message();
        break;
      case CMD_CLEARSC:
        clear_screen();
        break;
      case CMD_TPROCS:
        print_table();
        break;
      case CMD_CREATEPROC:
        schedule_process();
        break;
      case CMD_CPUINFO:
        cpuinfo_table();
        break;
      default:
        printf("Unrecognized command '%s'. To get help on how to use this system use: helpme\n", input_buffer->buffer);
        break;
    }
  }
}

