#ifndef CACHE_H
#define CACHE_H

#include "cut_list.h"

void cache_init();
void cache_free();
CutList *cache_get(int rod_length);
void cache_put(int rod_length, CutList *cl);

#endif // CACHE_H
