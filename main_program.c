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
#define TRUE 1
#define FALSE 0
#define MAGIC_NUM_LEN 3
#define MAX_COLOR_STR_LEN 4

// Typedef declarations
typedef struct header header;
typedef struct file_content file_content;
typedef int bool;

struct header {
   char magic_number[2];
   int rows;
   int cols;
   int max_color_val;
};

struct file_content {
   int *content;
   int content_num;
};

// Private forward declarations
void read_file(char *file_name, file_content *file_content, char *file_type, header *file_head, int *result);
void store_file(FILE *file, header *file_head, file_content *file_content, char* type, int *result);
void write_file(char *file_name, header *file_header, file_content *file_content, char *out_type, int *result);

int main(int argc, char* argv[])
{
   // Variable declarations
   file_content file_content = { malloc(sizeof(int)), 0 };
   int file_open_result = RUN_SUCCESSFUL;
   int file_store_result = RUN_SUCCESSFUL;
   int file_write_result = RUN_SUCCESSFUL;
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
         read_file(argv[2], &file_content, argv[1], &file_header, &file_open_result);

         // Determine if there was an error reading the file contents
         if (file_open_result == OPEN_FILE_ERR)
         {
            // If so, print message to user and terminate application
            printf("There was an error reading the file.\n");
            return RUN_FAILURE;
         }
         // Determine if file was in incorrect format
         else if (file_open_result == WRONG_FILE_TYPE)
         {
            // Print error message and return value
            printf("The file is not the correct format.\n");
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
            write_file(argv[3], &file_header, &file_content, argv[1], &file_write_result);

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
void read_file(char *file_name, file_content *file_content, char *file_type, header *file_head, int *result)
{
   // Variable declarations
   FILE *file;

   // Start by attemping to open the file
   file = fopen(file_name, "r");

   // Check if file exists
   if (file)
   {
      // Read header contents
      store_file(file, file_head, file_content, file_type, result);

      // Determine if file type was incorrect
      if (*result == WRONG_FILE_TYPE)
      {
         *result = WRONG_FILE_TYPE;
      }
      // Otherwise, store success value
      else
      {
         *result = RUN_SUCCESSFUL;
      }

      fclose(file);
   }
   // If not, return error code
   else
   {
      *result = OPEN_FILE_ERR;
   }
}

// Method used to read in file contents and confirm correctness
void store_file(FILE *file, header *file_head, file_content *file_content, char* type, int *result)
{
   // Variable declarations
   bool reading = TRUE;
   char magic_num[MAGIC_NUM_LEN];
   char traverser = 0;
   char rows[MAX_COLOR_STR_LEN];
   char cols[MAX_COLOR_STR_LEN];
   char max_color[MAX_COLOR_STR_LEN];
   char temp_color[MAX_COLOR_STR_LEN];
   int index = 0;
   int col_ind = 0;

   // Get first value
   traverser = fgetc(file);
   
   // Locate magic number variable
   do
   {
      // If end of file is reached or white space is reached, break out of loop
      if(feof(file) || isspace(traverser) || index == MAGIC_NUM_LEN)
      {
         // Set end of string value
         magic_num[index] = '\0';

         reading = FALSE;
      }
      // Otherwise append value to magic_num string
      else
      {
         // Add character value
         magic_num[index] = traverser;            

         // Increment string index
         index++;  
      }

      // Get current value
      traverser = fgetc(file); 

   } while(reading == TRUE);

   // Ensure magic num is correct
   if (strcmp(magic_num, "P3") == 0 || strcmp(magic_num, "P6") == 0)
   {
      
      // Store magic number and reinitialize reading variables
      strncpy(file_head->magic_number, magic_num, MAGIC_NUM_LEN);
      reading = TRUE;
      index = 0;

      // First, strip white space
      while (isspace(traverser))
      {
         traverser=fgetc(file);
      }

      // Now, locate row size
      do
      {
         // If end of file is reached or white space is reached, break out of loop
         if(feof(file) || isspace(traverser) || index == MAX_COLOR_STR_LEN)
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
      while (isspace(traverser))
      {
         traverser=fgetc(file);
      }

      // Now, search for column value
      do
      {       
         // If end of file is reached or white space is reached, break out of loop
         if(feof(file) || isspace(traverser) || index == MAX_COLOR_STR_LEN)
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

      // Add variable to header and reset reader
      file_head->cols = atoi(cols);
      reading = TRUE;
      index = 0;

      // First, strip white space
      while (isspace(traverser))
      {
         traverser=fgetc(file);
      }

      // Now, search for max color value
      do
      {    
         // If end of file is reached or white space is reached, break out of loop
         if(feof(file) || isspace(traverser) || index == MAX_COLOR_STR_LEN)
         {
            // Set end of string value
            max_color[MAX_COLOR_STR_LEN] = '\0';

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

      // Add variable to header and reset reader
      file_head->max_color_val = atoi(max_color);
      reading = TRUE;

      // Now that we have rows and columns, set array size to number of rgb elements
      file_content->content_num = file_head->rows * file_head->cols * 3;
      file_content->content = malloc(file_content->content_num * sizeof(int));

      // Store differently depending on file type
      if (strcmp(file_head->magic_number, "P3") == 0)
      {
         do
         {  
            // Reset index value
            index = 0;
              
            // If end of file is reached or white space is reached, break out of loop
            if(feof(file))
            {
               reading = FALSE;
            }
            // Otherwise append value to max color string
            else
            {
               // First, strip white space
               while (isspace(traverser))
               {
                  traverser = fgetc(file);
               }

               // Now, search for next color
               do
               {    
                  // If end of file is reached or white space is reached, break out of loop
                  if(feof(file) || isspace(traverser))
                  {
                     // Set end of string value
                     //temp_color[index] = '\0';
                     break;
                  }
                  // Otherwise append value to max color string
                  else
                  {
                     // Set end of string value
                     temp_color[index] = traverser;
                     index++;
                     traverser = fgetc(file);
                  }

               } while(!feof(file));
         
               // Append color to int array
               file_content->content[col_ind] = atoi(temp_color);

               // Increment color value index
               col_ind++;

               // Null terminate temp string
               temp_color[0] = '\0';
            }

         } while(reading == TRUE);
      }
      // Store character by character if P6 file
      else
      {
         // Store while characters exist
         do
         {    
            // Store character at current index
            file_content->content[col_ind] = (int)traverser;
            
            // Store next character value
            traverser = fgetc(file);

            // Increment color counter
            col_ind++;

         } while(!feof(file));
      }

      // Now that the header has been read successfully, return success value
      *result = RUN_SUCCESSFUL;
   }
   // If not, return error value
   else
   {
      *result = WRONG_FILE_TYPE;
   }
}

// Method used to write file based on filetype
void write_file(char *file_name, header *file_header, file_content *file_content, char *out_type, int *result)
{
   // Variable declarations
   FILE *out_file;
   int index = 0;
   int row = 0;
   int col = 0;

   // Start by opening file
   if ((out_file = fopen(file_name, "w")) != NULL)
   {
      // Start by handling p6 output
      if (strcmp(out_type, "6") == 0)
      {
         // Start by writing header file
         fprintf(out_file, "%s\n%d %d\n%d\n", "P6", file_header->rows, file_header->cols, file_header->max_color_val);
         
         // Loop through each character and put character value
         for (index = 0; index < file_content->content_num; index++)
         {
            // Using the %c format converts the integer value to its ascii equivalent
            fprintf(out_file, "%c", file_content->content[index]);
         }
      }
      // Handle p3 output
      else
      {
         // Start by writing header file
         fprintf(out_file, "%s\n%d %d\n%d\n", "P3", file_header->rows, file_header->cols, file_header->max_color_val);
         
         // Loop through each character in the current row
         for (row = 0; row < file_header->rows; row++)
         {
            // Loop through each character in the current column
            for (col = 0; col < file_header->cols * 3; col++)
            {
               // Using the %d format converts the ascii value to its integer equivalent
               fprintf(out_file, "%d ", file_content->content[index]);

               index++;
            }

            // Append newline string to display new row
            fprintf(out_file, "\n");
         }
      }

      // Close file
      fclose(out_file);
   }
   // If error occurs opening file, return error
   else
   {
      *result = FILE_WRITE_ERR;
   }
}




