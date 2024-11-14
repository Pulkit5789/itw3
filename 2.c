#include <stdio.h>
#include <stdlib.h>

struct node {
    int pow;
    int coef;
    struct node *next, *prev;
};

struct node* create(int p, int c, struct node* head) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->pow = p;
    temp->coef = c;
    temp->next = NULL;
    temp->prev = NULL;
    if (head == NULL) {
        head = temp;
    } else {
        struct node* t = head;
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = temp;
        temp->prev = t;
    }
    return head;
}

struct node* sub(struct node* h1, struct node* h2) {
    struct node* t1 = h1;
    struct node* t2 = h2;
    
    while (t1 != NULL && t2 != NULL) {
        if (t1->pow < t2->pow) {
            t1 = t1->next;
        } else if (t1->pow > t2->pow) {
            t2 = t2->next;
        } else {
            t1->coef -= t2->coef;
            if (t1->coef == 0) {
                if (t1->prev != NULL) {
                    t1->prev->next = t1->next;
                }
                if (t1->next != NULL) {
                    t1->next->prev = t1->prev;
                }
                if (t1 == h1) {
                    h1 = t1->next;
                }
                struct node* temp = t1;
                t1 = t1->next;
                free(temp);
            } else {
                t1 = t1->next;
            }
            t2 = t2->next;
        }
    }

    while (t2 != NULL) {
        h1 = create(t2->pow, -t2->coef, h1);
        t2 = t2->next;
    }
    return h1;
}

void print(struct node* head) {
    struct node* temp = head;
    if (head != NULL) {
        printf("%dx^%d", head->coef, head->pow);
        temp = temp->next;
    }
    while (temp != NULL) {
        if (temp->coef > 0) {
            printf("+%dx^%d", temp->coef, temp->pow);
        } else {
            printf("%dx^%d", temp->coef, temp->pow);
        }
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct node *h1 = NULL, *h2 = NULL;
    int n1, n2;
    printf("Enter the number of terms in the first polynomial:\n");
    scanf("%d", &n1);
    printf("Enter the coefficients and powers of the first polynomial:\n");
    for (int i = 0; i < n1; i++) {
        int coeff, pow;
        scanf("%d%d", &coeff, &pow);
        h1 = create(pow, coeff, h1);
    }
    printf("Enter the number of terms in the second polynomial:\n");
    scanf("%d", &n2);
    printf("Enter the coefficients and powers of the second polynomial:\n");
    for (int i = 0; i < n2; i++) {
        int coeff, pow;
        scanf("%d%d", &coeff, &pow);
        h2 = create(pow, coeff, h2);
    }
    printf("The difference of the two polynomials is:\n");
    struct node* result = sub(h1, h2);
    print(result);
    return 0;
}