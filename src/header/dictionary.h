#ifndef DICTIONARY_H
#define DICTIONARY_H

#define NUMBER_OF_LETTER 32
#define SPACE_INDEX 26
#define DASH_INDEX 27
#define APPOSTOPE_INDEX 28
#define SLASH_INDEX 29
#define BACK_SLASH_INDEX 30
#define DOT_INDEX 31

char alphabet[NUMBER_OF_LETTER] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ', '-', '\'', '/', '\\', '.'};

typedef struct linkedNode{
    char * data;
    struct linkedNode * next;
}linkedNode;

typedef struct trieNode{
    linkedNode * description;
    struct trieNode * nodes[NUMBER_OF_LETTER]; 
}trieNode;

int getIndex(char c);
linkedNode * createLink(char * data);
trieNode * createNode();
void appendNode(trieNode * node, char * key, char * description);
linkedNode * findDescription(trieNode * node, char * key);
void printLink(linkedNode * head);
#endif