#include "header/dictionary.h"

#define FILE_LOCATION "../resource/data.txt"

int main(int argc, char ** argv){

    trieNode * head;
    
    if(argc>1){
        head = createDictionary(argv[1]);
    } else{
        head = createDictionary(FILE_LOCATION);
    }


    char word[50];

    while(1){
        scanf("%s", word);
        printf("---------------------------------------------------------\n");
        printf("%s:\n\n", word);
        linkedNode * found = findDescription(head, word);
        if(found == NULL){
            printf("NOT FOUND!\n");
        } else{
            printLink(found);
        }
        printf("---------------------------------------------------------\n");
    }

    return 0;
}
