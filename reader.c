#include <stdio.h>
#include "reader.h"

#define RUN_SUCCESSFUL 0
#define OPEN_FILE_ERR 2
#define DATA_STORE_ERR 3

// Struct declarations
typedef struct header header;

struct header {
  char *magic_number;
  int row;
  int cols;
  int max_color_val;
};

// Private forward declarations
void store_p3(FILE *file, char *file_contents, int *result);
void store_p6(FILE *file, char *file_contents, int *result);

// Central read methods. Calls submethods depending on conversion type
void read_file(char *file_name, char *file_contents, char *file_type, int *result)
{
  // Variable declarations
  FILE *file;
  header file_header = { "", 0, 0, 0 };

  // Start by attemping to open the file
  file = fopen(file_name, "r");

  // Check if file exists
  if (file)
  {
    *result = OPEN_FILE_ERR;
  }
  // If not, return error code
  else
  {
    *result = OPEN_FILE_ERR;
  }
}
