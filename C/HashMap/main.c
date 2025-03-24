#include <stdio.h>
#include "HashMap.h"

struct Item{
    void* key;
    void* val;
};

// static void PrintTest(int cond){
//     static int count = 1;
//     if(cond == 1){
//         printf("Test number %d: PASSED!\n", count++);
//     }
//     else{
//         printf("Test number %d: FAILED!\n", count++);
//     }
// }

// static int compareItems(void* _item1, void* _item2){
//     Item* item1, *item2;
//     item1 = (Item*)_item1;
//     item2 = (Item*)_item2;
//     return *(int*)item1->key ==*(int*)item2->key;
// }

// static HashFunction HashFunc(void* _key){
//     return *(int*)_key;
// }


int main(){
    // void *out,*out2;
    // int key = 1, val = 5, val2 = 7;
    // HashMap* map = HashMapCreate(10,HashFunc,compareItems);
    // PrintTest(HashMapInsert(map,&key,&val) == MAP_SUCCESS);
    // PrintTest(HashMapRemove(map,&key,&out,&out2) == MAP_SUCCESS);
    // PrintTest(*(int*)out == key);
    // PrintTest(*(int*)out2 == val);
    // PrintTest(HashMapInsert(map,&key,&val2) == MAP_SUCCESS);
    // PrintTest(HashMapSize(map) == 1);
    // HashMapDestroy(&map,NULL,NULL);
    // PrintTest(map == NULL);
    return 0;
}