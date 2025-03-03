CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: rodcut_policy_a rodcut_policy_b

rodcut_policy_a: rodcut.o vec.o piece_values.o cut_list.o cache_policy_a.o lists.o
	$(CC) $(CFLAGS) -o rodcut_policy_a rodcut.o vec.o piece_values.o cut_list.o cache_policy_a.o lists.o

rodcut_policy_b: rodcut.o vec.o piece_values.o cut_list.o cache_policy_b.o
	$(CC) $(CFLAGS) -o rodcut_policy_b rodcut.o vec.o piece_values.o cut_list.o cache_policy_b.o

rodcut.o: rodcut.c
	$(CC) $(CFLAGS) -c rodcut.c

vec.o: vec.c
	$(CC) $(CFLAGS) -c vec.c

piece_values.o: piece_values.c
	$(CC) $(CFLAGS) -c piece_values.c

cut_list.o: cut_list.c
	$(CC) $(CFLAGS) -c cut_list.c

cache_policy_a.o: cache_policy_a.c
	$(CC) $(CFLAGS) -c cache_policy_a.c

cache_policy_b.o: cache_policy_b.c
	$(CC) $(CFLAGS) -c cache_policy_b.c

lists.o: lists.c
	$(CC) $(CFLAGS) -c lists.c

clean:
	rm -f *.o rodcut_policy_a rodcut_policy_b
