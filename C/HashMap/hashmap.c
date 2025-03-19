#include <stdlib.h> //malloc
#include "../DoubleLinkedList/dlist.h"
#include "hashmap.h"

#define HASH_FUNC _map->m_hashFunction
#define MAP_CAPACITY _map->m_capacity
#define HASH_EQUALITY _map->m_equalityFunction
#define MAP_DATA _map->m_data
#define MAP_NUM_OF_ITEMS _map->m_numOfItems

struct HashMap {
    List** m_data;
    size_t (*m_hashFunction)(void* _data);
    int (*m_equalityFunction)(void* _firstData, void* _secondData);
    size_t m_hashSize; /*original size given by the client*/
    size_t m_capacity; /*real hash size */
    size_t m_numOfItems; /*number of occupied places in the table*/
};

typedef struct {
    void* key;
    void* value;
}Item;

static size_t isPrimeNumber(int num);
static size_t FindInitialSize(size_t _capacity);
static int FindVal(void* _element, void* _context);
static void* SearchInList(List* _list, Item* _item, HashMap* _map);
static int ComapreItems(void* _item1, void* _item2);

HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc) {

    if(_capacity < 0) {
        return NULL;
    }

    HashMap* map = (HashMap*)malloc(sizeof(HashMap));

    if(map == NULL) {
        return NULL;
    }
    map->m_capacity = FindInitialSize(_capacity);
    map->m_data = (List**)calloc(map->m_capacity, sizeof(List*));

    if(map->m_data == NULL) {
        return NULL;
    }

    map->m_numOfItems = 0;
    map->m_hashSize = _capacity;
    map->m_hashFunction = _hashFunc;
    map->m_equalityFunction = _keysEqualFunc;

    return map;
}

void HashMap_Destroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value)) {

    if(_map == NULL || *_map == NULL) {
        return;
    }

    Item* item;
    size_t i = 1;
    HashMap* mptr = *_map;

    item->key = _keyDestroy;
    item->value = _valDestroy;

    while (i < mptr->m_capacity) {

        if(mptr->m_data[i] == NULL) {
            ++i;
            continue;
        }

        ListDestroy(&mptr->m_data[i], free);
        i++;
    }

    if(mptr->m_data[0] != NULL) {
        ListDestroy(&mptr->m_data[0], free);
    }

    free(mptr);
    *_map = NULL;
}

Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value) {

    if(_map == NULL) {
        return MAP_UNINITIALIZED_ERROR;
    }

    if(_key == NULL) {
        return MAP_KEY_NULL_ERROR;
    }

    Item* item;

    item->key = _key;
    item->value = _value;

    size_t index = HASH_FUNC(_key);
    index = index % MAP_CAPACITY;

    if(MAP_DATA[index] == NULL) {
        MAP_DATA[index] = ListCreate();
        ListPushHead(MAP_DATA[index], item);
        MAP_NUM_OF_ITEMS += 1;
    } else if (SearchInList(MAP_DATA[index], item, _map)) {
        ListPushTail(MAP_DATA[index], item);
        MAP_NUM_OF_ITEMS++;
    } else {
        return MAP_KEY_DUPLICATE_ERROR;
    }

    return MAP_SUCCESS;
}

Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue) {

    Item* item;
    size_t index = HASH_FUNC(_searchKey);
    item->key = _searchKey;
    void* elementToRemove;

    if(_map == NULL) {
        return MAP_UNINITIALIZED_ERROR;
    }

    if(_searchKey == NULL) {
        return MAP_KEY_NULL_ERROR;
    }

    elementToRemove = SearchInList(MAP_DATA[index], item, _map);

    if(elementToRemove) {
        ListItrRemove(elementToRemove);
    } else {
        return MAP_KEY_NOT_FOUND_ERROR;
    }

    return MAP_SUCCESS;
}

Map_Result HashMap_Find(const HashMap* _map, const void* _key, void** _pValue) {

    Item* item;
    size_t index = HASH_FUNC(_key);
    item->key = _key;
    void* element;

    if(_map == NULL) {
        return MAP_UNINITIALIZED_ERROR;
    }

    if(_key == NULL) {
        return MAP_KEY_NULL_ERROR;
    }

    element = SearchInList(MAP_DATA[index], item, _map);

    if(element) {
        *_pValue = ListItrGet(element);
    } else {
        return MAP_KEY_NOT_FOUND_ERROR;
    }

    return MAP_SUCCESS;

}

size_t HashMap_Size(const HashMap* _map) {

    if(_map == NULL) {
        return 0;
    }

    return MAP_NUM_OF_ITEMS;
}

//--private functions -----------------------

void Hash(void* _key) {

}

static int ComapreItems(void* _item1, void* _item2) {

    Item* item1 = (Item*)_item1;
    Item* item2 = (Item*)_item2;

    return *(int*)item1->key == *(int*)item2->key;
}

static void* SearchInList(List* _list, Item* _item, HashMap* _map) {

    void* element = ListItrBegin(_list);
    void* lastElement = ListItrEnd(_list);
    void* value;

    while(element != lastElement) {

        value = ListItrGet(element);
        if(HASH_EQUALITY(value, _item)) {
            return element;
        }
        element = ListItrNext(element);
    }

    return NULL;

}

static size_t FindInitialSize(size_t _capacity) {

    while(isPrimeNumber(_capacity)) {
        _capacity++;
    }

    return _capacity;
}

static size_t isPrimeNumber(int num) {

    if(num % 2 == 0) {
        return FAILED; //if number is even its defenitly not prime
    }

    for (int i = 3; i < num / 2; i +=2) {
        if (num % i == 0) {
            return FAILED;
        }
    }

    return OK;
}

static int FindVal(void* _element, void* _context) {

    return *(int*)_element == *(int*)_context;
}