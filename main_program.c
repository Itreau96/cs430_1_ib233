#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define RUN_SUCCESSFUL 0
#define MIN_ARGS 4
#define RUN_FAILURE 1
#define OPEN_FILE_ERR 2
#define DATA_STORE_ERR 3
#define FILE_WRITE_ERR 4
#define WRONG_FILE_TYPE 5
#define WRONG_COLOR_VAL 6
#define TRUE 1
#define FALSE 0
#define MAGIC_NUM_LEN 2
#define MAX_COLOR_STR_LEN 4

// Typedef declarations
typedef struct header header;

struct header {
   char magic_number[2];
   int rows;
   int cols;
   int max_color_val;
};

typedef int bool;

// Private forward declarations
void read_file(char *file_name, char *file_contents, char *file_type, header *file_head, int *result);
void store_header(FILE *file, header *file_head, char* type, int *result);
void store_p3(FILE *file, char *file_contents, int *result);
void store_p6(FILE *file, char *file_contents, int *result);

int main(int argc, char* argv[])
{
   // Variable declarations
   char *file_contents;
   int file_open_result;
   int file_store_result;
   int file_write_result;
   header file_header = { "", 0, 0, 0 };

   // Relay error message if incorrect number of arguments were entered
   if (argc < MIN_ARGS)
   {
      // Subtract 1 from arguments entered, since 1st argument is .exe
      printf("Incorrect number of arguments. You entered %d. You must enter 3.\n", argc - 1);

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
         read_file(argv[2], file_contents, argv[1], &file_header, &file_open_result);

         // Determine if there was an error reading the file contents
         if (file_open_result == OPEN_FILE_ERR)
         {
            // If so, print message to user and terminate application
            printf("There was an error reading the file.\n");
            return RUN_FAILURE;
         }
         // Determine if there was an error storing the file contents
         else if (file_open_result == DATA_STORE_ERR)
         {
            // If so, print message to user and terminate application
            printf("There was an error storing the file contents.\n");
            return RUN_FAILURE;
         }
         // If read method ran successfully, write output to file
         else
         {
            // Call write method depending on the type
            //write_file(argv[2], file_contents, argv[1], &file_write_result);

            // Determine if output file method failed to execute
            if (file_write_result == FILE_WRITE_ERR)
            {
               // If so, print message and terminate application
               printf("There was an error writing to the output file.\n");
               return RUN_FAILURE;
            }
            // If method ran successfully, print success message to user and terminate application
            else
            {
              printf("Conversion executed successfully!\n");
              return RUN_SUCCESSFUL;
            }
         }
      }
      // Otherwise value is incorrect
      else
      {
         // Display error message and return failure value
         printf("Incorrect file format. You entered %s. You must enter 3 or 6.\n", argv[1]);

         // Return error code
         return RUN_FAILURE;
      }
   }
}

// Central read methods. Calls submethods depending on conversion type
void read_file(char *file_name, char *file_contents, char *file_type, header *file_head, int *result)
{
   // Variable declarations
   FILE *file;

   // Start by attemping to open the file
   file = fopen(file_name, "r");

   // Check if file exists
   if (file)
   {
      // Read header contents
      store_header(file, file_head, file_type, result);
      
   }
   // If not, return error code
   else
   {
      *result = OPEN_FILE_ERR;
   }
}

// Method used to read in file header and confirm correctness
void store_header(FILE *file, header *file_head, char* type, int *result)
{
   // Variable declarations
   bool reading = TRUE;
   int iter;
   char magic_num[MAGIC_NUM_LEN];
   char traverser;
   char rows[MAX_COLOR_STR_LEN];
   char cols[MAX_COLOR_STR_LEN];
   char max_color[MAX_COLOR_STR_LEN];
   int index;

   // First while loop finds magic number value 
   for (iter = 0; iter < MAGIC_NUM_LEN; iter++)
   {
      magic_num[iter] = fgetc(file);    
   }

   // Ensure magic num is correct
   if (strcmp(magic_num, "P3") == 0 || strcmp(magic_num, "P6") == 0)
   {
      // Store magic number in heading struct
      strncpy(file_head->magic_number, magic_num, MAGIC_NUM_LEN);

      // First, strip white space
      while (isspace(traverser=fgetc(file)));

      // Now, locate row size
      do
      {       
         // If end of file is reached or white space is reached, break out of loop
         if(feof(file) || isspace(traverser) || index == MAX_COLOR_STR_LEN - 1)
         {
            // Set end of string value
            rows[index] = '\0';

            reading = FALSE;
         }
         // Otherwise append value to row string
         else
         {
            // Add character value
            rows[index] = traverser;            

            // Increment string index
            index++;  
         }

         // Get current value
         traverser = fgetc(file); 

      } while(reading == TRUE);

      // Add value to header and reset reading variable
      file_head->rows = atoi(rows);
      reading = TRUE;
      index = 0;

      // First, strip white space
      while (isspace(traverser=fgetc(file)));

      // Now, search for column value
      do
      {       
         // If end of file is reached or white space is reached, break out of loop
         if(feof(file) || isspace(traverser) || index == MAX_COLOR_STR_LEN - 1)
         {
            // Set end of string value
            cols[index] = '\0';

            reading = FALSE;
         }
         // Otherwise append value to col string
         else
         {
            // Add character value
            cols[index] = traverser;            

            // Increment string index
            index++;  
         }

         // Get current value
         traverser = fgetc(file); 

      } while(reading == TRUE);

      printf("%d", atoi(cols));

      // Add variable to header and reset reader
      file_head->cols = atoi(cols);
      reading = TRUE;
      index = 0;

      // First, strip white space
      while (isspace(traverser=fgetc(file)));

      // Now, search for max color value
      do
      {       
         // If end of file is reached or white space is reached, break out of loop
         if(feof(file) || isspace(traverser) || index == MAX_COLOR_STR_LEN - 1)
         {
            // Set end of string value
            max_color[index] = '\0';

            reading = FALSE;
         }
         // Otherwise append value to max color string
         else
         {
            // Add character value
            max_color[index] = traverser;            

            // Increment string index
            index++;  
         }

         // Get current value
         traverser = fgetc(file); 

      } while(reading == TRUE);

      printf("%d", atoi(max_color));

      // Add variable to header and reset reader
      file_head->max_color_val = atoi(max_color);
      
   }
   // If not, return error value
   else
   {
      printf("ERROR\n");
      *result = WRONG_FILE_TYPE;
   }
}

