#include "string.h"
#include "stdlib.h"
#include "stdio.h"

/*
WORD SEARCH
~~~~~~~~~~~

Purpose:
--------
Specify the known characters and their positions in the word.
All words matching the criteria will be written into "results.txt"
Words are searched for, from the universe file "words_universe.txt"

Input Specification:
--------------------
Characters can be specified from the start or from the end.

To specify from start (counting from the left):
Use actual positions to specify from the start.

To specify from last (counting from the right):
Use 0 to specify last character.
Use -1, -2... for penultimate, pre-penultimate characters and so on.
*/

int main(int argc, char *argv[])
{
    FILE *fs, *fd;
    int i, j, nulet, number = 0, pos[100];
    int check_len = 200, string_len;
    int found_match = 1;
    char ch, charac, string[200], check[check_len], system_command[50];
    char out_file[] = "results.txt";
    char univ_file[] = "words_universe.txt";
    char rules_file[] = "README.md";

    fd = fopen(out_file, "w");
    if(fd == NULL){
        printf("\nUnable to Open Output file");
        return(-1);
    }

    fs = fopen(univ_file, "r");
    if(fs == NULL){
        printf("\nUnable to Open Words Universe File");
        return(-1);
    }

    strcpy(system_command, "type ");
    strcat(system_command, rules_file);
    system(system_command);
    getch();
    printf("\n\nEnter the number of known characters in the word: ");
    scanf("%d", &nulet);

    for(j = 0; j < nulet; j++){
        int check_pos;
        int position;
        fflush(stdin);
        printf("\nEnter the character: ");
        scanf("%c", &charac);
        fflush(stdin);
        printf("Enter its position: ");
        scanf("%d", &position);
        if(position > 100 || position < -99){
            printf("\n\nSupported only for a maximum of 100 letters");
            printf("\nDiscounting this input. Please continue");
            j -= 1;
            continue;
        }
        pos[j] = position;
        check_pos = pos[j] - 1;
        if (check_pos < 0) check_pos += check_len;
        check[check_pos] = charac;
    }

    i = 0;
    j = 0;
    while(1){
        ch = fgetc(fs);
        if(ch == 32 || ch == 10 || ch == 13){
            string[i] = '\0';
            i = -1;
            found_match = 1;
            string_len = strlen(string);
            for(j = 0; j < nulet; j++){
                int string_pos = pos[j] - 1;
                if (string_pos < 0) string_pos += string_len;

                int check_pos = pos[j] - 1;
                if (check_pos < 0) check_pos += check_len;

                if(pos[j] > string_len){
                    found_match = 0;
                    break;
                }

                // Convert to upper case letter for case ignored comparison
                if(string[string_pos] >= 65 && string[string_pos] <= 90)
                    string[string_pos] -= 32;

                if(check[check_pos] >= 65 && check[check_pos] <= 90)
                    check[check_pos] -= 32;

                if(check[check_pos] != string[string_pos]) {
                    found_match = 0;
                    break;
                }
            }

            if(found_match == 1) {
                fprintf(fd, "\n%s", string);
                number++;
            }
        }

        if (ch == EOF)
            break;
        else {
            if(ch != 32 && ch != 10 && ch != 13)
                string[i] = ch;
        }

        i++;
    }

    fclose(fs);
    fclose(fd);
    printf("\n\n");
    printf("Total number of words matching your criteria :: %d \
           \nThe results are available in the file \"%s\"\n\n",
           number, out_file);
    return(0);
}
