#include <stdio.h>
#include <stdlib.h>

struct node {
    int coeff;
    int x_pow;
    int y_pow;
    struct node *next, *prev;
};

struct node* create(int coeff, int x_pow, int y_pow, struct node *head) {
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->coeff = coeff;
    temp->x_pow = x_pow;
    temp->y_pow = y_pow;
    
    if (head == NULL) {
        head = temp;
        head->next = temp;
        head->prev = temp;
    } else {
        struct node *tail = head->prev;
        tail->next = temp;
        temp->prev = tail;
        temp->next = head;
        head->prev = temp;
    }
    return head;
}

struct node* add(struct node *h1, struct node *h2) {
    struct node *t1 = h1, *t2 = h2, *result = NULL;
    
    do {
        if (t1->x_pow < t2->x_pow || (t1->x_pow == t2->x_pow && t1->y_pow < t2->y_pow)) {
            result = create(t2->coeff, t2->x_pow, t2->y_pow, result);
            t2 = t2->next;
        } else if (t1->x_pow > t2->x_pow || (t1->x_pow == t2->x_pow && t1->y_pow > t2->y_pow)) {
            result = create(t1->coeff, t1->x_pow, t1->y_pow, result);
            t1 = t1->next;
        } else {
            result = create(t1->coeff + t2->coeff, t1->x_pow, t1->y_pow, result);
            t1 = t1->next;
            t2 = t2->next;
        }
    } while (t1 != h1 && t2 != h2);

    while (t1 != h1) {
        result = create(t1->coeff, t1->x_pow, t1->y_pow, result);
        t1 = t1->next;
    }
    while (t2 != h2) {
        result = create(t2->coeff, t2->x_pow, t2->y_pow, result);
        t2 = t2->next;
    }

    return result;
}

void print(struct node *head) {
    if (head == NULL) return;
    struct node *temp = head;
    
    do {
        printf("%dx^%dy^%d", temp->coeff, temp->x_pow, temp->y_pow);
        temp = temp->next;
        if (temp != head) printf(" + ");
    } while (temp != head);
    
    printf("\n");
}

int main() {
    struct node *h1 = NULL, *h2 = NULL;
    int n1, n2;
    
    printf("Enter the number of terms in the first polynomial:\n");
    scanf("%d", &n1);
    printf("Enter the coefficients and powers of x and y for the first polynomial:\n");
    for (int i = 0; i < n1; i++) {
        int coeff, x_pow, y_pow;
        scanf("%d %d %d", &coeff, &x_pow, &y_pow);
        h1 = create(coeff, x_pow, y_pow, h1);
    }
    
    printf("Enter the number of terms in the second polynomial:\n");
    scanf("%d", &n2);
    printf("Enter the coefficients and powers of x and y for the second polynomial:\n");
    for (int i = 0; i < n2; i++) {
        int coeff, x_pow, y_pow;
        scanf("%d %d %d", &coeff, &x_pow, &y_pow);
        h2 = create(coeff, x_pow, y_pow, h2);
    }
    
    printf("The sum of the two polynomials is:\n");
    struct node *result = add(h1, h2);
    print(result);
    
    return 0;
}
