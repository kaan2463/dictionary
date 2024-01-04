#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_LETTER 32
#define SPACE_INDEX 26
#define DASH_INDEX 27
#define APPOSTOPE_INDEX 28
#define SLASH_INDEX 29
#define BACK_SLASH_INDEX 30
#define DOT_INDEX 31

int getIndex(char c){
    if(c == ' '){
        return SPACE_INDEX;
    }

    if(c == '-'){
        return DASH_INDEX;
    }

    if(c == '\''){
        return APPOSTOPE_INDEX;
    }
    
    if(c == '\\'){
        return BACK_SLASH_INDEX;
    }
    
    if(c == '/'){
        return SLASH_INDEX;
    }

    if(c == '.'){
        return DOT_INDEX;
    }


    if(c>='A' && c<='Z'){
        return (int)(c-'A');
    }

    return (int)(c-'a');
}

char alphabet[NUMBER_OF_LETTER] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ', '-', '\'', '/', '\\', '.'};


typedef struct linkedNode{
    char * data;
    struct linkedNode * next;
}linkedNode;

linkedNode * createLinkedList(char * data){
    linkedNode * node = (linkedNode*)malloc(sizeof(linkedNode));
    node->data = data;
    node->next = NULL;
}


typedef struct trieNode{
    char * description;
    struct trieNode * nodes[NUMBER_OF_LETTER]; 
}trieNode;

trieNode * createNode(){
    trieNode * node = (trieNode*) malloc(sizeof(trieNode)); 
    node->description = NULL;
    for(int i=0;i<NUMBER_OF_LETTER;i++){
        node->nodes[i] = NULL;
    }

    return node;
}

void appendNode(trieNode * node, char * key, char * description){
    if(key == NULL || description == NULL | node == NULL){
        return;
    }

    if(*key == '\0'){
        node->description = description;
        return;
    }

    if(node->nodes[getIndex(*key)] == NULL){
        node->nodes[getIndex(*key)] = createNode();
    }

    appendNode(node->nodes[getIndex(*key)], key+1, description);

}

char * findDescription(trieNode * node, char * key){
    if(node == NULL || key == NULL){
        return NULL;
    }


    if(*key == '\0'){
        return node->description;
    }
    
    printf("%c %d\n", *key, getIndex(*key));

    return findDescription(node->nodes[getIndex(*key)], key+1);
}


int main(int argc, char ** argv){

    trieNode * head = createNode();

    FILE *fp = fopen("data.txt", "r");
    if(fp == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    
    char *key;
    char * buffer;

    size_t sz = 0;

    sz = getline(&line, &len, fp);
    int lineNum = 1;
    while(sz != -1) {
        printf("%d %ld ",lineNum ,sz);

        key = strtok(line,"@");
        buffer=(char*)malloc(sizeof(char)*sz);
        char * des = strtok(NULL,"@");
        strcpy(buffer, des);
        printf("%p %s %s\n", buffer, key, des);
        appendNode(head, key, buffer);
        sz = getline(&line, &len, fp);
        lineNum++;
    }

    fclose(fp);
    free(line);

    char word[50];

    while(1){
        scanf("%s", word);
        printf("%s: ", word);
        char * found = findDescription(head, word);
        if(found == NULL){
            printf("NOT FOUND \n");
        } else{
            printf("%s \n", found);
        }
    }

    return 0;
}
