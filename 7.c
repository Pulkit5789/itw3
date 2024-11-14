#include <stdio.h>
#include <stdlib.h>

struct node {
    int coeff;
    int powX;
    int powY;
    struct node *next, *prev;
};

struct node* create(int a, int b, int c, struct node* head) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->coeff = a;
    temp->powX = b;
    temp->powY = c;

    if (head == NULL) {
        head = temp;
        head->next = temp;
        head->prev = temp;
    } else {
        struct node* tail = head->prev;
        tail->next = temp;
        temp->prev = tail;
        temp->next = head;
        head->prev = temp;
    }
    return head;
}

struct node* remove_even_exponents(struct node* head) {
    if (head == NULL) return NULL;

    struct node* temp = head;
    struct node* to_delete;

    do {
        int sum_pow = temp->powX + temp->powY;
        if (sum_pow % 2 == 0) {
            to_delete = temp;
            if (to_delete->next == to_delete) {
                free(to_delete);
                return NULL;
            }
            to_delete->prev->next = to_delete->next;
            to_delete->next->prev = to_delete->prev;
            if (to_delete == head) head = to_delete->next;
            temp = to_delete->next;
            free(to_delete);
        } else {
            temp = temp->next;
        }
    } while (temp != head);

    return head;
}

void print(struct node* head) {
    if (head == NULL) {
        printf("Polynomial is empty.\n");
        return;
    }
    struct node* temp = head;
    do {
        printf("%dx^%dy^%d", temp->coeff, temp->powX, temp->powY);
        temp = temp->next;
        if (temp != head) printf(" + ");
    } while (temp != head);
    printf("\n");
}

int main() {
    struct node* h1 = NULL;
    int n;

    printf("Enter the number of terms in the polynomial:\n");
    scanf("%d", &n);
    printf("Enter the coefficients and powers of x and y for each term:\n");
    for (int i = 0; i < n; i++) {
        int coeff, powX, powY;
        scanf("%d %d %d", &coeff, &powX, &powY);
        h1 = create(coeff, powX, powY, h1);
    }

    printf("Original polynomial:\n");
    print(h1);

    h1 = remove_even_exponents(h1);

    printf("Polynomial after removing terms with even exponents (sum of x and y exponents):\n");
    print(h1);

    return 0;
}
