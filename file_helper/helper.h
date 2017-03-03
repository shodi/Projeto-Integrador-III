#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE 50
 
typedef struct config{

    int _id;
    int __arrival;
    char *__steps;

}Config;

Config* read_file(char *file_name, int id){
    Config* options = (Config *) malloc (1 * sizeof(Config));
    FILE *file;
    char str_id[ARR_SIZE];
    sprintf(str_id, "%d", id);
    char line[ARR_SIZE];
    char *__script_call = (char *)malloc(100 * sizeof(char));
    strcat(__script_call, "python ../scripts/reader.py ");
    strcat(__script_call, file_name);
    strcat(__script_call, " ");
    strcat(__script_call, str_id);
    printf("%s", __script_call);
    file = popen(__script_call, "r");
    
    if(file == NULL){
        printf("Erro na abertura do arquivo");
    }
    int counter;
    for(counter = 0; counter < 3; counter++){
        fgets(line, ARR_SIZE, file);
        switch(counter){
            case 0:
                options->_id = atoi(line);
                break;
            case 1:
                options->__arrival = atoi(line);
                break;
            case 2:
                options->__steps = line;
                break;
        }
    }

    fclose(file);

    return options;
}

// int main(int argc, char *argv[]){
    
//     Config* options;
//     options = read_file(argv[1], 1);
//     printf("id: %d", options->_id);
//     printf("arrival: %d", options->__arrival);
//     printf("Sequence: %s", options->__steps);
//     return 0;
// }