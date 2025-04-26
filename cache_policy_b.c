#include "cache.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




#define MAX_CACHE 10
//Make a cache structure using Least Recently Used

#define ENTRY_NOT_INUSE -1
typedef struct {
    int rod_length;
    CutList *cl;
    int usecounter;
} CacheEntry;
CacheEntry *cache_a;
int use_index = 0;

void cache_init() {
    cache_a = malloc(MAX_CACHE * sizeof(CacheEntry));
    for (int i = 0; i < MAX_CACHE; i++) {
        cache_a[i].rod_length = ENTRY_NOT_INUSE;
        cache_a[i].cl = NULL;
        cache_a[i].usecounter = 0;
    }
}

void cache_free() {
    for (int i = 0; i < MAX_CACHE; i++) {
        if(cache_a[i].cl != NULL) {
            cutlist_free(cache_a[i].cl);
        }
    }
    free(cache_a);
    cache_a = NULL;
}

CutList *cache_get(int rod_length) {
    for (int i = 0; i < MAX_CACHE; i++) {
        if (cache_a[i].rod_length == rod_length) {
            use_index++;
            cache_a[i].usecounter = use_index;
            printf("Found item at %d", i);
            return cache_a[i].cl;
        }
    }
    printf("Could not return any values");
    return NULL;
}


int highest_usecounter() {
    int highest = 0;
    for (int i = 0; i < MAX_CACHE; i++) {
        if (cache_a[i].usecounter > cache_a[highest].usecounter) {
            highest = i;
        }
    }
    return highest;
}  


int location_for_entry (void){
    for (int i = 0; i < MAX_CACHE; i++) {
        if (cache_a[i].rod_length == ENTRY_NOT_INUSE) {
            return i;
        }
    }
    printf("Cache is full");
    int thing_to_evict = highest_usecounter();
    printf("Going to evict %d", thing_to_evict);
    return thing_to_evict;
}

void cache_put(int rod_length, CutList *cl) {
    int new_entry_location = location_for_entry();
    
    if(cache_a[new_entry_location].cl != NULL)
        cutlist_free(cache_a[new_entry_location].cl);

    cache_a[new_entry_location].rod_length = rod_length;
    cache_a[new_entry_location].cl = cl;
    cache_a[new_entry_location].usecounter = ++use_index;
}
