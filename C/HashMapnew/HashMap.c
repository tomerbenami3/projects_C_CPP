#include <stdlib.h> /*MALLOC FREE*/
#include <stdio.h>
#include "HashMap.h"
#include"../DoubleLinkedList/dlist.h"

#define HASHFUNC _map->m_hashFunction
#define CAPACITY _map->m_capacity
#define EQUAL _map->m_equalityFunction
#define DATA _map->m_data
#define NUMOFITEMS _map->m_numOfItems
struct HashMap
{
    List** m_data;
    size_t (*m_hashFunction)(void* _data);
    int (*m_equalityFunction)(void* _firstData, void* _secondData);
    size_t m_hashSize; /*original size given by the client*/
    size_t m_capacity; /*real hash size */
    size_t m_numOfItems; /*number of occupied places in the table*/
};

struct Item{
    void* key;
    void* val;
};



/*----------------------------------- HASHMAP CREATE -----------------------------------*/

static size_t IsPrime(size_t _num);
static size_t FindCapacity(size_t _capacity);

HashMap* HashMapCreate(size_t _size, HashFunction _hashFunc,EqualityFunction _keysEqualFunc){
    HashMap* map;
    if(_size == 0 || _hashFunc == NULL || _keysEqualFunc == NULL){
        return NULL;
    }
    map = (HashMap*)malloc(sizeof(HashMap));
    if (map == NULL){
        return NULL;
    }
    map->m_capacity = FindCapacity(_size);
    map->m_data = (List**)calloc(map->m_capacity, sizeof(List*));
    if(map->m_data == NULL){
        free(map);
        return NULL;
    }
    
    map->m_hashSize = _size;
    map->m_equalityFunction = _keysEqualFunc;  
    map->m_hashFunction = _hashFunc;
    map->m_numOfItems = 0;

    return map;
}

/*----------------------------------- HASHMAP DESTROY -----------------------------------*/

void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void(*_valDestroy)(void* _value)){
    size_t idx;
    HashMap* map;
    void* listItr, *end;
    if(_map == NULL || *_map == NULL){
        return;
    }
    map = *_map;
    for (idx = 0; idx<map->m_capacity; idx++){
        if (map->m_data[idx] != NULL){
            listItr = ListItrBegin(map->m_data[idx]);
            while(listItr != ListItrNext(listItr)){
                if(_keyDestroy != NULL){
                    _keyDestroy(ListItrGet(listItr));
                }
                if(_valDestroy != NULL){                   
                    _valDestroy(ListItrGet(listItr));
                }
                listItr = ListItrNext(listItr);
            }
            ListDestroy(map->m_data[idx],free);
        }
    }
    free(map);
    *_map = NULL;
}

/*----------------------------------- HASHMAP FIND -----------------------------------*/
static void* InList(List* _list, Item* _item, HashMap* _map);

Map_Result HashMapFind(const HashMap* _map, const void* _key, void**_pValue){
    size_t idx;
    Item* item = malloc(sizeof(Item)),*out = malloc(sizeof(Item));
    void* value;
    if (_map == NULL){
        return MAP_UNINITIALIZED_ERROR;
    }
    if(_key == NULL){
        MAP_KEY_NULL_ERROR;
    }
    item->key = _key;
    idx = HASHFUNC(_key);
    idx = idx % CAPACITY;
    out = ListItrForEach(ListItrBegin(DATA[idx]),ListItrEnd(DATA[idx]),EQUAL,item);
    if(out == ListItrEnd(DATA[idx])){
        return MAP_KEY_NOT_FOUND_ERROR;
    }
    out = ListItrGet(out);
    *_pValue = out->val;
    return MAP_SUCCESS;
}


/*----------------------------------- HASHMAP INSERT -----------------------------------*/

Map_Result HashMapInsert(HashMap* _map, const void* _key, const void* _value){
    size_t idx;
    Item* item = malloc(sizeof(Item));
    if (_map == NULL){
        return MAP_UNINITIALIZED_ERROR;
    }
    if(_key == NULL){
        MAP_KEY_NULL_ERROR;
    }
    item->key = _key;
    item->val = _value;
    idx = HASHFUNC(_key);
    idx = idx % CAPACITY;
    
    if(DATA[idx] == NULL){
        DATA[idx] = ListCreate();
        ListPushTail(DATA[idx], item);
        NUMOFITEMS++;
    }
    else{
        if(InList(DATA[idx],item,_map) == NULL){
            ListPushTail(DATA[idx], item);
            NUMOFITEMS++;
        }
        else{
            return MAP_KEY_DUPLICATE_ERROR;
        }
    }
    return MAP_SUCCESS;
}

/*----------------------------------- HASHMAP REMOVE -----------------------------------*/

Map_Result HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue){
    size_t idx;
    Item* item = malloc(sizeof(Item)),*out = malloc(sizeof(Item));
    void* value;
    if (_map == NULL){
        return MAP_UNINITIALIZED_ERROR;
    }
    if(_searchKey == NULL){
        MAP_KEY_NULL_ERROR;
    }
    item->key = _searchKey;
    idx = HASHFUNC(_searchKey);
    idx = idx % CAPACITY;
    out = ListItrForEach(ListItrBegin(DATA[idx]),ListItrEnd(DATA[idx]),EQUAL,item);
    if(out == ListItrEnd(DATA[idx])){
        return MAP_KEY_NOT_FOUND_ERROR;
    }
    item = ListItrGet(out);  
    *_pKey = item->key;
    *_pValue = item->val;
    ListItrRemove(out);
    NUMOFITEMS--;
    return MAP_SUCCESS;
}


/*----------------------------------- HASHMAP SIZE -----------------------------------*/

size_t HashMapSize(const HashMap* _map){
    if(_map == NULL){
        return 0;
    }
    return NUMOFITEMS;
}


/*------------------------------------------------------------------------------------------*/

static void* InList(List* _list, Item* _item, HashMap* _map){
    void* curElement, *lastElemnt, *curItem;

    curElement = ListItrBegin(_list);
    curItem = ListItrGet(curElement);
    lastElemnt = ListItrEnd(_list);

    while(curElement != lastElemnt){
        if(EQUAL(_item, curItem)){
            return curElement;
        }
        curElement = ListItrNext(curElement);
        curItem = ListItrGet(curElement);
    }
    return NULL;
}

static size_t IsPrime(size_t _num){
    int check;
    if(_num%2 == 0){
        return 0;
    }
    for(check = 3; check < _num; check += 2){
        if(_num%check == 0){
            return 0;
        }
    }
    return 1;
}

static size_t FindCapacity(size_t _capacity){
    while(!IsPrime(_capacity)){
        ++_capacity;
    }
    return _capacity;
}
/*----------------------------------- HASHMAP REHASH -----------------------------------*/
/* NOT MANDATORY */
Map_Result HashMapRehash(HashMap *_map, size_t newCapacity);
/*----------------------------------- HASHMAP FOREACH -----------------------------------*/
/* NOT MANDATORY */
size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action,void* _context);
