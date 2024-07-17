#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define keyType int
#define valueType int

typedef struct hashMapNode {
    keyType key;
    valueType value;
} hashMapNode;

typedef struct Hashmap {
    int size;
    hashMapNode *map;
    void (*add)(struct Hashmap*, keyType, keyType);
    valueType (*get)(struct Hashmap*, keyType);
    valueType (*pop)(struct Hashmap*, keyType);
} Hashmap;

void hashAdd(Hashmap* map, keyType key, valueType value) {
    int index = hashGetIndex(map->size, key);
    hashMapNode working = map->map[index];
    working.value = value;
    working.key = key;
}
valueType hashPop(Hashmap* map, keyType key) {
    hashMapNode working = map->map[hashGetIndex(map->size, key)];
    valueType value = working.value;
    working.value = NULL;
    working.key = NULL;
    return value;
}
valueType hashGet(Hashmap* map, keyType key) {
    return map->map[hashGetIndex(map->size, key)].value;
}
int hashGetIndex(int size, keyType key) {
    char keyString[50];
    sprintf(keyString, "%f", key);
    char* s = keyString;
    int n = sizeof(key)/sizeof(keyString[0]);
    long long p = 31, m = 1e9 + 7;
    long long hash = 0;
    long long p_pow = 1;
    for(int i = 0; i < n; i++) {
        hash = (hash + (s[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return -hash & (size-1);
}
Hashmap* initHash(const int Size) { 
    Hashmap* hashmap = (Hashmap*)malloc(sizeof(Hashmap));
    hashmap->size = Size;
    hashmap->map = (hashMapNode*)malloc(Size * sizeof(hashMapNode));
    hashmap->add = hashAdd;
    hashmap->pop = hashPop;
    hashmap->get = hashGet;
}

#endif