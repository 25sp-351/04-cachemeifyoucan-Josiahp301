#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include "piece_values.h"
#include "cut_list.h"
#include "vec.h"
#include "cache.h"

void usage(char *program_name);

int main(int argc, char *argv[]) {
    if (argc != 2 || !strcmp(argv[1], "-h"))
        usage(argv[0]);

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    Vec value_list = read_piece_values(file);
    fclose(file);

    if (value_list == NULL) {
        fprintf(stderr, "Error in value list.\n");
        return 1;
    }

    cache_init();

    int rod_length;
    while (scanf("%d", &rod_length) == 1) {
        CutList *cl = cache_get(rod_length);
        if (!cl) {
            cl = optimal_cutlist_for(value_list, rod_length);
            cache_put(rod_length, cl);
        }
        cutlist_print(cl);
        cutlist_free(cl);
    }

    vec_free(value_list);
    cache_free();

    return 0;
}

noreturn void usage(char *program_name) {
    fprintf(stderr,
            "Usage:\n"
            "%s [-h] file\n"
            "file = file containing length,value pairs\n",
            program_name);
    exit(1);
}
