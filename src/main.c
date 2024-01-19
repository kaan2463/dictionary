#include "header/dictionary.h"
#include "header/io.h"


#define FILE_LOCATION "resource/data.txt"

trieNode * head;


void foo(char * input, char * output, ssize_t i_sz, ssize_t *o_sz)
{
    char * key = (char*)malloc(i_sz * sizeof(char));
    memcpy(key, input, i_sz-1);
    key[i_sz-1] = '\0';

    linkedNode * found = findDescription(head, key);
    if(found == NULL){
        *o_sz = 11;
        memcpy(output,"NOT FOUND!\n", *o_sz);
    } else{
        int sz = 0;
        char * desc = linkToStr(found, &sz);
        *o_sz = sz + 1;
        memcpy(output, desc, *o_sz);
        output = desc;
        free(desc);
    }

}


int main(int argc, char ** argv){


    if(argc>1){
        head = createDictionary(argv[1]);
    } else{
        head = createDictionary(FILE_LOCATION);
    }


    int sockfd = createSocket(PORT, foo);

    close(sockfd);    

    return 0;
}
