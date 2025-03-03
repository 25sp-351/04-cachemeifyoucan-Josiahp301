#include "cache.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CACHE 10
//Make a cache structure using Least Recently Used


typedef struct {
    int rod_length;
    CutList *cl;
} CacheEntry;
CacheEntry *cache_a;

void cache_init() {
    cache_a = malloc(MAX_CACHE * sizeof(CacheEntry));
    for (int i = 0; i < MAX_CACHE; i++) {
        cache_a[i].rod_length = -1;
        cache_a[i].cl = NULL;
    }
}

void cache_free() {
    cache_a = NULL;
    free(cache_a);
}

CutList *cache_get(int rod_length) {
    for (int i = 0; i < MAX_CACHE; i++) {
        if (cache_a[i].rod_length == rod_length) {
            return cache_a[i].cl;
        }
    }
    return NULL;
}

void cache_put(int rod_length, CutList *cl) {
    for (int i = 0; i < MAX_CACHE; i++) {
        if (cache_a[i].rod_length == -1) {
            cache_a[i].rod_length = rod_length;
            cache_a[i].cl = cl;
            return;
        }
    }
    fprintf(stderr, "Cache is full\n");
    exit(1);
}
