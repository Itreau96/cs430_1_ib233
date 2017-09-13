#include <stdio.h>
#include <string.h>
#include "reader.h"
#include "writer.h"

#define RUN_SUCCESSFUL 0
#define MIN_ARGS 4
#define RUN_FAILURE 1

#define OPEN_FILE_ERR 2
#define DATA_STORE_ERR 3
#define FILE_WRITE_ERR 4

int main(int argc, char *argv[])
{
  // Variable declarations
  char *file_contents;
  int file_open_result;
  int file_store_result;
  int file_write_result;

  // Relay error message if incorrect number of arguments were entered
  if (argc < MIN_ARGS)
  {
    // Subtract 1 from arguments entered, since 1st argument is .exe
    printf("Incorrect number of arguments. You entered %d. You must enter 3.", argc - 1);

    // Return error code
    return RUN_FAILURE;
  }
  // If correct number of arguments were entered, continue with execution
  else
  {
    // Make sure that the file format is either P3 or P6
    if (strcmp(argv[1], "3") == 0 || strcmp(argv[1], "6") == 0)
    {
      // Read file contents
      read_file(argv[2], file_contents, argv[1], &file_open_result);

      // Determine if there was an error reading the file contents
      if (file_open_result == OPEN_FILE_ERR)
      {
        // If so, print message to user and terminate application
        printf("There was an error reading the file.");
        return RUN_FAILURE;
      }
      // Determine if there was an error storing the file contents
      else if (file_open_result == DATA_STORE_ERR)
      {
        // If so, print message to user and terminate application
        printf("There was an error storing the file contents.");
        return RUN_FAILURE;
      }
      // If read method ran successfully, write output to file
      else
      {
        // Call write method depending on the type
        write_file(argv[2], file_contents, argv[1], &file_write_result);

        // Determine if output file method failed to execute
        if (file_write_result == FILE_WRITE_ERR)
        {
          // If so, print message and terminate application
          printf("There was an error writing to the output file.");
          return RUN_FAILURE;
        }
        // If method ran successfully, print success message to user and terminate application
        else
        {
          printf("Conversion executed successfully!");
          return RUN_SUCCESSFUL;
        }
      }
    }
    // Otherwise value is incorrect
    else
    {
      // Display error message and return failure value
      printf("Incorrect file format. You entered %s. You must enter 3 or 6.", argv[1]);

      // Return error code
      return RUN_FAILURE;
    }
  }
}
