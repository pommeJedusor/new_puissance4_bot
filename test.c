#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "connect4.h"

int test(char* file_name)
{
    char raf;
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

    //printf("%s",file_contents);

    //make the tests
    int total_score=0;
    int total_test=0;
    int game_len;
    int file_pos = 0;
    int ex_file_pos;
    char is_first_part;
    int score = 0;
    char more_less;
    int result;
    while (1)
    {
        //calcule la longeur de la game et récupère le score
        ex_file_pos = file_pos;
        is_first_part = 1;
        game_len = 0;
        more_less = 1;
        score = 0;
        while (1)
        {
            if (file_contents[file_pos]=='\n')
            {
                file_pos++;
                break;
            }
            else if (file_contents[file_pos]==' ')
            {
                is_first_part = 0;
                if (file_contents[file_pos+1]=='-')
                {
                    more_less = -1;
                }
            }
            else if (file_contents[file_pos]!='-' && is_first_part==0)
            {
                score = score * 10 + (file_contents[file_pos]-48);
            }
            else if (is_first_part)
            {
                game_len++;
            }
            if (file_contents[file_pos]=='\0')
            {
                //printf("yop");
                break;
            }
            file_pos++;

        }
        result = connect4(file_contents+ex_file_pos, game_len, &raf);
        score*=more_less;

        total_test++;
        if (result==score)
        {
            total_score++;
            printf("1\n");
        }
        else printf("0\n");
        printf("%d / %d\n",total_score, total_test);


        if (file_contents[file_pos]=='\0')
        {
            break;
        }

    }

    fclose(input_file);
    free(file_contents);

    printf("test level 1: %d/%d de réussis\n",total_score,total_test);
    return 0;
}

int test_1()
{
    return test("connectfourtest/Test_L3_R1");
}
int test_2()
{
    return test("connectfourtest/Test_L2_R2");
}
int test_3()
{
    return test("connectfourtest/Test_L2_R1");
}
int test_4()
{
    return test("connectfourtest/Test_L1_R3");
}
int test_5()
{
    return test("connectfourtest/Test_L1_R2");
}
int test_6()
{
    return test("connectfourtest/Test_L1_R1");
}