#include<stdio.h>
#include<stdlib.h>
struct node{
    int coeff;
    int pow;
    struct node *next,*prev;
};
struct node*create(int a,int b,struct node*head){
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->coeff=a;
    temp->pow=b;
    if(head==NULL){
        head=temp;
        head->next=temp;
        head->prev=temp;
    }else{
        struct node*tail=head->prev;
        tail->next=temp;
        temp->prev=tail;
        temp->next=head;
        head->prev=temp;
    }
    return head;
}
int power(int x,int p){
    int mul=1;
    while(p--){
        mul*=x;
    }
    return mul;
}
int value(struct node*head,int x){
    int sum=0;
    struct node*temp=head;
    while(temp->next!=head){
    sum+=temp->coeff*power(x,temp->pow);
    temp=temp->next;
    }
    sum+=temp->coeff*power(x,temp->pow);
    return sum;
}
int main(){
    struct node*h1=NULL;
    int n1,x;
    printf("Enter the number of terms in the first polynomial:\n");
    scanf("%d",&n1);
    printf("Enter the coefficients and powers of the polynomial:\n");
    for(int i=0;i<n1;i++){
        int coeff,pow;
        scanf("%d%d",&coeff,&pow);
        h1=create(coeff,pow,h1);
    }
    printf("enter value of x\n");
    scanf("%d",&x);
    int result=value(h1,x);
    printf("value of polynomial for x=%d is %d",x,result);
}