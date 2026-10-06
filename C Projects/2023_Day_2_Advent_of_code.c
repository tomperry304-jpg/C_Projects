#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "HashMap.h"

void instruction_execute(int instruction_length, long startIdx, char* data, Hash_Map* Map1) {
    char* string = malloc(instruction_length + 1);
    memcpy(string, data + startIdx,instruction_length);
    string[instruction_length] = '\0';

    
    char* split = strchr(string, ':');

    *split = '\0';
    char* key = string;
    char* instructions = split + 1;

    int blue = 0;
    int red = 0;
    int green = 0;

    

    char* part = strtok(instructions, ",;");

        while (part != NULL) {
            int number = 0;
            char colour[20] = {0};
            sscanf(part, "%d %19s", &number, colour);

            if (strcmp(colour, "blue") == 0) {
                if (number > blue) {
                    blue = number;
                }
            }
            else if (strcmp(colour, "red") == 0) {
                if (number > red) {
                    red = number;
                }
            }
            else if (strcmp(colour, "green") == 0) {
                if (number > green) {
                    green = number;
                }
            }
            part = strtok(NULL, ",;");
        }
    int total = 0;
    if (red <= 12 && blue <= 14 && green <= 13) {
        sscanf(key, "Game %d", &total);
    }
    Hash_Map_Put(Map1, key, total);
    free(string);

}


int main(void) {
    FILE* file = fopen("2023_day2_Input.txt", "rb");//file = file pointer/handle not specificaly location in moemory

    if (file == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);//move the cursor to then end of the file curslor = L
    long size = ftell(file);//set size to cursour position
    rewind(file);//set file cursor ro the start of file

    char* data = malloc(size + 1);//add 1 so it can be null terminated

    fread(data, 1, size, file);//read the file into requested memory
    data[size] = '\0';

    fclose(file);

    //file has now been read into memory


    Hash_Map* Map1 = New_Hash_Map();

    char Letter = '0';

    long position = 0;
    int instruction_length = 0;
    bool Reading = true;
    int code_sum = 0;

    while (Reading)
    {
        if (position >= size) {
            Reading = false;
        }
        else {
            Letter = data[position];
            if (Letter == '\n') {
                printf("new instructin block ############\n");
                instruction_execute(instruction_length, position - instruction_length, data, Map1);
                instruction_length = 0;
            }
            else {
                printf("letter is %c\n", Letter);
                //note length of current instruction block
                instruction_length++;
            }
            position++;
        }

    }
    //if file did not end on newline
    if (instruction_length > 0) {
        instruction_execute(instruction_length,position - instruction_length,data,Map1);
    }

    // write a function to sum all the valuse of all numbers in the hash map
    int total = Hash_Map_Sum(Map1);
    printf("total = %i", total);
    Hash_Map_erase(Map1);
    free(data);//clear memory requested to read file
    return 0;
}