#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int Instruction_Execute(int instruction_length, long position, char *data);

int main(void)
{
    FILE* file = fopen("2022_day3_Input.txt", "rb");//file = file pointer/handle not specificaly location in moemory

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
                code_sum += Instruction_Execute(instruction_length, position-instruction_length, data);
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

    printf("%s\n", data);
    printf("final code = %i\n", code_sum);
    free(data);//clear memory requested to read file

    return 0;
}



int Instruction_Execute(int instruction_length, long startIdx, char *data) {
    printf("instruction length = %i, position = %ld\n",instruction_length,startIdx);

    int half_length = instruction_length / 2;
    char* array1 = data + startIdx;
    char* array2 = data + startIdx + half_length;

    /*
    xchar *array1 = malloc(half_length + 1);
    memcpy(array1, data + startIdx, half_length);
    array1[half_length] = '\0';

    char *array2 = malloc(half_length + 1);
    memcpy(array2, data + startIdx + half_length, half_length);
    array2[half_length] = '\0';
    */

    long letter_i = 0;
    char* pointer = 0;
    char letter = '0';
    int priority = 0;
    int total_priority = 0;
        while (letter_i<half_length) {
            letter = array1[letter_i];
            pointer = memchr(array2,letter,half_length );
            if (pointer != NULL) {
                priority = letter;
                if (priority <= 90) {
                    priority -= 38;
                    }
                else {
                    priority -= 96;
                }
                total_priority += priority;
                break;
            }
            letter_i++;
        }
//        free(array1);
//        free(array2);
    return total_priority;
}