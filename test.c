#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "connect4.h"

int test(char* file_name)
{
    //get the file content
    FILE* input_file = fopen(file_name, "r");

    if (!input_file)
        exit(EXIT_FAILURE);

    struct stat sb;
    if (stat(file_name, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char* file_contents = malloc(sb.st_size);
    fread(file_contents, sb.st_size, 1, input_file);

    //make the tests
    int game_len;
    int file_pos = 0;
    while (1)
    {
        //calcule la longeur de la game
        game_len = 0;
        while (1)
        {
            if (file_contents[game_len+file_pos]=='\n')
            {
                file_pos+= game_len;
            }
            else if (file_contents[game_len+file_pos]==' ')
        }
    }

    fclose(input_file);
    free(file_contents);


    return 0;
}

int test_1()
{
    return test("connectfourtest/Test_L3_R1");
}