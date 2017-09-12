#include <stdio.h>

#define RUN_SUCCESSFUL 0
#define MIN_ARGS 4
#define RUN_FAILURE 1

int main(int argc, char *argv[])
{
  // Relay error message if incorrect number of arguments were entered
  if (argc < MIN_ARGS)
  {
    printf("Incorrect number of arguments. You entered %d. You must enter 3.", argc);

    // Return error code
    return RUN_FAILURE;
  }
  // If correct number of arguments were entered, continue with execution
  else
  {
    // Make sure that the file format is either P3 or P6
    if (argv[1] == "3")
    {

    }
    else if (argv[1] == "6")
    {

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
