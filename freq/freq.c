#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct wordlist_t
{
    char **list;
    int *count;
    int length;

};

struct wordlist_t *create_list(){
    struct wordlist_t *list = malloc(sizeof(struct wordlist_t));
    //list->list = (char **)malloc(sizeof(char*));
    //list->count = (int *)malloc(sizeof(int));
    list->list = NULL;
    list->count = NULL;
    list->length = 0;
    //list.list[0] = (char *)malloc(20 * sizeof(char)); Not needed
    return list;
}

void free_list(struct wordlist_t *list){
    for (int i = 0; i < list->length; i++)
    {
        free(list->list[i]);
    }
    free(list->list);
    free(list->count);
    free(list);
}

int addToList(struct wordlist_t *list, char *word){
    for (int i = 0; i < list->length; i++)
    {
        if (strcmp(word, list->list[i]) == 0)
        {
            list->count[i]++;
            return 1;
        }
    }
    //printf("List length: %d\n", list->length);
    list->count = realloc(list->count, (list->length + 1) * sizeof(int));
    list->list = realloc(list->list, (list->length +1 ) * sizeof(char *));
    list->list[list->length] = malloc((strlen(word) + 1) * sizeof(char));
    strcpy(list->list[list->length], word);
    list->count[list->length] = 1;
    list->length++;
    return 0;
}

int removeFromList(struct wordlist_t *list, char *word){
    for (int i = 0; i < list->length; i++)
    {
        if (strcmp(word, list->list[i]) == 0)
        {
            free(list->list[i]);
            for (int j = i; j < list->length -1; j++)
            {
                list->count[j] = list->count[j+1];
                list->list[j] = list->list[j+1];
            }
            list->count[list->length -1] = 0;
            list->count = realloc(list->count, (list->length - 1) * sizeof(int));
            //free(list->list[list->length -1]);
            list->list[list->length -1] = NULL;
            list->list = realloc(list->list, (list->length - 1 ) * sizeof(char*));
            list->length--;
            return 1;
        }
    }
    return 0;
}

int mostFrequent(struct wordlist_t * list){
    int index = 0;
    int biggest = 0;
    for (int i = 0; i < list->length; i++)
    {
        if(list->count[i] > biggest){
            biggest = list->count[i];
            index = i;
        }
    }
    return index;
    
}

int isPrime(int num){
    int prime = 1;

    for (int i = 2; i < num; i++)
    {
        if(num % i == 0){
            prime = 0;
        }
    }

    if(num == 1){
        prime = 0;
    }
    return prime;
}

int main(void){
    int line = 1;
    char word[20] = "";
    struct wordlist_t *list = create_list();

    while(fgets(word, 20, stdin) != NULL){
        //printf("Length: %d\n", list->length);
        word[strcspn(word, "\n")] = 0;
        if(isPrime(line)){
            printf("trying to delete %s: ", word);
            int found = removeFromList(list, word);
            found == 1 ? printf("deleted\n") : printf("not found\n");
        }else{
            int found = addToList(list, word);
            found == 1 ? printf("counted %s\n", word) : printf("added %s\n", word);
        }
        line++;
    }
    int index = mostFrequent(list);
    //printf("Index: %d\n", index);
    printf("result: %s %d\n", list->list[index], list->count[index]);

    free_list(list);
}