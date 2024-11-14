#include <stdio.h>
#include <stdlib.h>

struct node {
    int coeff;
    int pow;
    struct node* next;
};

struct node* create(int a, int b, struct node* head) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->coeff = a;
    temp->pow = b;
    if (head == NULL) {
        head = temp;
        head->next = temp;
    } else {
        struct node* tail = head;
        while (tail->next != head) tail = tail->next;
        tail->next = temp;
        temp->next = head;
    }
    return head;
}

struct node* multiply(struct node* h1, struct node* h2) {
    struct node* t1 = h1, * result = NULL;
    do {
        struct node* t2 = h2;
        do {
            result = create(t1->coeff * t2->coeff, t1->pow + t2->pow, result);
            t2 = t2->next;
        } while (t2 != h2);
        t1 = t1->next;
    } while (t1 != h1);
    return result;
}

void print(struct node* head) {
    if (head == NULL) return;
    struct node* temp = head;
    do {
        printf("%dx^%d", temp->coeff, temp->pow);
        temp = temp->next;
        if (temp != head) printf(" + ");
    } while (temp != head);
    printf("\n");
}

int main() {
    struct node* h1 = NULL, * h2 = NULL;
    int n1, n2;
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) {
        int coeff, pow;
        scanf("%d %d", &coeff, &pow);
        h1 = create(coeff, pow, h1);
    }
    scanf("%d", &n2);
    for (int i = 0; i < n2; i++) {
        int coeff, pow;
        scanf("%d %d", &coeff, &pow);
        h2 = create(coeff, pow, h2);
    }
    struct node* result = multiply(h1, h2);
    print(result);
    return 0;
}
