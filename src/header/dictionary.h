#ifndef DICTIONARY_H
#define DICTIONARY_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUMBER_OF_LETTER 35
#define SPACE_INDEX 26
#define DASH_INDEX 27
#define APPOSTOPE_INDEX 28
#define SLASH_INDEX 29
#define BACK_SLASH_INDEX 30
#define DOT_INDEX 31
#define BRA_INDEX 32
#define KET_INDEX 33
#define SHARP_INDEX 34

// char alphabet[NUMBER_OF_LETTER] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ', '-', '\'', '/', '\\', '.','(',')'};

typedef struct linkedNode{
    int data_size;
    char * data;
    struct linkedNode * next;
}linkedNode;

typedef struct trieNode{
    linkedNode * description;
    linkedNode * tail;
    struct trieNode * nodes[NUMBER_OF_LETTER]; 
}trieNode;
int indexMatch(char c);
int getIndex(char c);
linkedNode * createLink(char * data);
trieNode * createNode();
void appendNode(trieNode * node, char * key, char * description);
linkedNode * findDescription(trieNode * node, char * key);
void printLink(linkedNode * head);
char * linkToStr(linkedNode * head, int num);
trieNode * createDictionary(const char * file_path);
#endif
