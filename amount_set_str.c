#include "amount_set_str.h"
#include <stdlib.h>

typedef struct AmountSet {
    char* description;
    double item_amount;
    struct amount_set* current;
    struct amount_set* next;
    struct amount_set* previous;
} *AmountSet;


AmountSet asCreate() {
    AmountSet set = malloc(sizeof(AmountSet)); // לא סגורה פה על הסייזאוף
    if (set == NULL) return NULL;
    return set;
}

void asDestroy(AmountSet set){
    if(set==NULL) {
        return;
    }
    asClear(set);
    free(set->description); // האם נחוץ
    free(set);
}

AmountSet asCopy(AmountSet set){ //צריך לפתור
    if (set=NULL) {
        return NULL;
    }
    int size = asGetSize(set);
    AmountSet new_set = asCreate;
    if (new_set==NULL) {
        return NULL;
    }
    AmountSet temp_point_old = set;
    AmountSet temp_point_new = new_set;
    for (int i=0; i<=size; i++){
        temp_point_new->description;
    }
}

int asGetSize(AmountSet set) {
    if (set==NULL){
        return -1;
    }
    int size = 1;
    while (set->next != NULL) {
        size++;
        set = set->next;
    }
    return size;
}

bool asContains(AmountSet set, const char* element) { //האם כאן ניתן להניח שקיבלתי ערכים תקינים כי לא מצויין
    AmountSet temp_pointer = set;
    while (temp_pointer->next != NULL) {
        if ((strcmp (element, temp_pointer->description))==0){
            return true;
        }
        temp_pointer == set->next;
    }
     return false;
}

 int strcmp(const char *str1, const char *str2)
    {
        while (*str1)
        {
            if (*str1 != *str2) {
                break;
            }
            str1++;
            str2++;
        }
    
        return *(const unsigned char*)str1 - *(const unsigned char*)str2;
    }

AmountSetResult asGetAmount(AmountSet set, const char* element, double* outAmount){
    if (set==NULL || outAmount==NULL || element == NULL) {
        return AS_NULL_ARGUMENT;
    }
    AmountSet temp_pointer = set;
    if (!asContains) {
        return AS_ITEM_DOES_NOT_EXIST;
    }
    while ((strcmp(temp_pointer->description, element)!=0)) {
        temp_pointer = temp_pointer->next;
    }
    outAmount = temp_pointer->item_amount;
    return AS_SUCCESS;
}
