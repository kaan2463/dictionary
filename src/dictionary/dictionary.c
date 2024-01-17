#include "../header/dictionary.h"


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

linkedNode * createLink(char * data){
    linkedNode * node = (linkedNode*)malloc(sizeof(linkedNode));
    node->data = data;
    node->data_size = strlen(data);
    node->next = NULL;
    return node;
}


trieNode * createNode(){
    trieNode * node = (trieNode*) malloc(sizeof(trieNode)); 
    node->description = NULL;
    for(int i=0;i<NUMBER_OF_LETTER;i++){
        node->nodes[i] = NULL;
    }

    return node;
}

void appendNode(trieNode * node, char * key, char * description){
    if(key == NULL || description == NULL || node == NULL){
        return;
    }

    if(*key == '\0'){
        if(node->description == NULL){
            node->description = createLink(description);
        } else {
            linkedNode * link = createLink(description);
            link->next = node->description;
            node->description = link;
        }
        return;
    }

    if(node->nodes[getIndex(*key)] == NULL){
        node->nodes[getIndex(*key)] = createNode();
    }

    appendNode(node->nodes[getIndex(*key)], key+1, description);

}

linkedNode * findDescription(trieNode * node, char * key){
    if(node == NULL || key == NULL){
        return NULL;
    }


    if(*key == '\0'){
        return node->description;
    }

    return findDescription(node->nodes[getIndex(*key)], key+1);
}

void printLink(linkedNode * head){
    
    if(head == NULL){
        return;
    }

    printLink(head->next);

    printf("%d: %s\n",head->data_size, head->data);
}


trieNode * createDictionary(const char * file_path){
    trieNode * head = createNode();

    FILE *fp = fopen(file_path, "r");
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
    printf("Database is loading .");
    while(sz != -1) {

        key = strtok(line,"@");
        buffer=(char*)malloc(sizeof(char)*sz);
        char * des = strtok(NULL,"@");
        strcpy(buffer, des);
        appendNode(head, key, buffer);
        sz = getline(&line, &len, fp);
        if(lineNum % 10000 == 0){
            printf(".");
        }
        lineNum++;
    }

    printf("\n\n%d words has been read!\n\n", lineNum);

    fclose(fp);
    free(line);

    return head;
}

