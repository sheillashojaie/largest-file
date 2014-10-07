/*----------------------------------------------------------------------------------

Reads input in the format of the command ls -l and returns the name and size of
the largest group-readable regular file. Takes two optional commandline arguments:
-g followed by a group name which is specified as a restriction on the files to be
considered.

Sheilla Shojaie
g3s
for CSC209 Fall 2014

----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#define BUFFER 32

int main(int argc, char *argv[]) {

        if ((argc != 1) && (argc != 3)) {
                printf("Expected 0 or 2 additional arguments.\n");
                return(0);
                }

        if ((argc == 3) && (strcmp(argv[1], "-g") != 0)) {
                printf("Invalid argument.\n");
                return(0);
                }

        char line[100];
        char *list_element;
        int largest_running_filesize = 0;
        char largest_running_filename[BUFFER] = "No file matches found."; /* Initialize with */
                                           /* this message in case no file matches are found */
        int is_first_line = 1;
        int is_largest;

        fgets(line, BUFFER * 5, stdin);  /* Skip the first line */

        while(fgets(line, BUFFER * 5, stdin)) { /* Read a line */
                is_largest = 0;
                list_element = strtok(line, " ");
                int column = 1; /* Column number */

                if (strncmp(list_element, "d", 1)==0) { /* If the permissions */ 
                        continue; /* indicate that this line is a directory, skip it */
                        }

                char group_read_permission[1];
                strcpy(group_read_permission, &list_element[4]);
                if (strncmp(group_read_permission, "r",1) != 0) { /* If this line is */
                        continue; /* not group-readable, skip it */
                        }

                while ((list_element != NULL) && (column != 10)){
                        list_element = strtok(NULL, " "); /* Read the next element */
                        column = column + 1;

                        if ((argc == 3 && column == 4) /* If column 4 indicates that */ 
                        && (strcmp(argv[2], list_element) != 0) ) {  /* this line is */
                                break; /* not in a specified group, skip it */
                        }

                        if (column == 5) {
                                int filesize;
                                filesize = atoi(list_element);
                                if ((is_first_line) /* If this is the first line or is */
                                 || (filesize > largest_running_filesize)) { /* the largest */
                                        largest_running_filesize = filesize; /* file so far, */
                                        is_largest = 1; /* set the largest file size to this */
                                        is_first_line = 0;
                                        }
                                }
        
                        if (column == 9 && is_largest) { /* If this is the largest file so far, */
                                strtok(list_element, "\n"); /* set the name of the largest file */
                                strcpy(largest_running_filename, list_element); /* to this */
                                }                      
                        
                        }
                }

        printf("%s      %d\n", largest_running_filename, largest_running_filesize);

        return(0);
        }
