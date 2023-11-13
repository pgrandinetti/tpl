#include <stdio.h>
#include <stdlib.h>

#define allocfail do {printf("memory allocation failed\n"); return 1;} while (0)

struct ListElement {
    char elem;
    struct ListElement *next;
};

struct CircularList {
    struct ListElement *head;
    struct ListElement *ptr;
};

void free_CircularList (struct CircularList *l) {
    l->ptr->next = NULL;
    struct ListElement *iter;
    iter = l->head;
    while (iter != NULL) {
        iter = iter->next;
        free(l->head);
        l->head = iter;
    }
}

void print_ListElement (struct ListElement *e) {
    if (e == NULL)
        printf("| NULL |");
    else
        printf("| %c |", e->elem);
}

void print_CircularList (struct CircularList *l) {
    struct ListElement *iter = l->head;
    while (iter != NULL) {
        print_ListElement(iter);
        printf(" -> ");
        iter = iter->next;
        if (iter == l->head)
            break;
    }
    printf(" | END (loop) |\n");
}

void append_right (struct CircularList **l, struct ListElement *new) {
    if ((*l)->head == NULL) {
        (*l)->head = new;
        (*l)->ptr = new;
        new->next = new;
    }
    else {
        new->next = (*l)->ptr->next;
        (*l)->ptr->next = new;
        (*l)->ptr = new;
    }
}

int main() {
    struct CircularList *l;
    l = malloc(sizeof(struct CircularList));
    l->head = NULL;
    l->ptr = NULL;

    printf("Begin:\n");
    print_CircularList(l);

    struct ListElement *first;
    first = malloc(sizeof(struct ListElement));
    if (first == NULL) 
        allocfail;
    first->elem = 'A';

    append_right(&l, first);

    printf("After first element:\n");
    print_CircularList(l);

    struct ListElement *sec;
    sec = malloc(sizeof(struct ListElement));
    if (sec == NULL)
        allocfail;
    sec->elem = 'B';

    append_right(&l, sec);

    printf("After second element:\n");
    print_CircularList(l);

    free_CircularList(l);
    free(l);
}

/*
 * Usage:
 * $ gcc -Wall -Wextra -o a.out strings-lists.c
 * $ ./a.out
 *
 * Optional:
 * $ valgrind --leak-check=full \
 *     --show-leak-kinds=all \
 *     --track-origins=yes \
 *     --verbose \
 *     ./a.out
 */
