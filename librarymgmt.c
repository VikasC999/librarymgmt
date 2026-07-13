#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book{
    int bookID;
    char title[100];
    char author[100];
    struct Book *next;
}Book;

typedef struct{ Book *top; }Stack;
typedef struct{ Book *front,*rear; }Queue;

Book* createBook(int id,const char*t,const char*a){
    Book*b=malloc(sizeof(Book));
    b->bookID=id;
    strcpy(b->title,t);
    strcpy(b->author,a);
    b->next=NULL;
    return b;
}
void initStack(Stack*s){s->top=NULL;}
void initQueue(Queue*q){q->front=q->rear=NULL;}

Book* searchBook(Book*h,int id){
    while(h){ if(h->bookID==id) return h; h=h->next; }
    return NULL;
}
void addBook(Book **h,Stack*s){
    int id; char t[100],a[100];
    printf("ID: "); scanf("%d",&id); getchar();
    if(searchBook(*h,id)){ printf("ID exists!\n"); return; }
    printf("Title: "); fgets(t,100,stdin); t[strcspn(t,"\n")]=0;
    printf("Author: "); fgets(a,100,stdin); a[strcspn(a,"\n")]=0;
    Book*n=createBook(id,t,a);
    n->next=*h; *h=n;
    Book*sn=createBook(id,t,a); sn->next=s->top; s->top=sn;
    printf("Book added.\n");
}
void display(Book*h){
    if(!h){ printf("Library empty.\n"); return; }
    while(h){
        printf("%d | %s | %s\n",h->bookID,h->title,h->author);
        h=h->next;
    }
}
void deleteBook(Book **h,int id){
    Book *cur=*h,*pre=NULL;
    while(cur && cur->bookID!=id){pre=cur;cur=cur->next;}
    if(!cur){printf("Not found\n");return;}
    if(pre) pre->next=cur->next; else *h=cur->next;
    free(cur); printf("Deleted.\n");
}
void updateBook(Book*h,int id){
    Book*b=searchBook(h,id);
    if(!b){printf("Not found\n");return;}
    getchar();
    printf("New title: "); fgets(b->title,100,stdin); b->title[strcspn(b->title,"\n")]=0;
    printf("New author: "); fgets(b->author,100,stdin); b->author[strcspn(b->author,"\n")]=0;
}
void sortBooks(Book*h){
    for(Book*i=h;i;i=i->next) for(Book*j=i->next;j;j=j->next)
    if(i->bookID>j->bookID){
        int id=i->bookID; char t[100],a[100];
        strcpy(t,i->title); strcpy(a,i->author);
        i->bookID=j->bookID; strcpy(i->title,j->title); strcpy(i->author,j->author);
        j->bookID=id; strcpy(j->title,t); strcpy(j->author,a);
    }
}
void printStack(Stack*s){ for(Book*t=s->top;t;t=t->next) printf("%d | %s\n",t->bookID,t->title); }
void enqueue(Queue*q,Book*b){
    Book*n=createBook(b->bookID,b->title,b->author);
    if(!q->rear){q->front=q->rear=n;} else {q->rear->next=n;q->rear=n;}
}
void borrow(Queue*q,Book*h){
    int id; printf("ID: "); scanf("%d",&id);
    Book*b=searchBook(h,id);
    if(!b){printf("Not found\n");return;}
    enqueue(q,b); printf("Borrowed.\n");
}
void ret(Queue*q){
    if(!q->front){printf("Queue empty\n");return;}
    Book*t=q->front; q->front=t->next; if(!q->front) q->rear=NULL;
    printf("Returned: %s\n",t->title); free(t);
}
int main(){
    Book*lib=NULL; Stack st; Queue q; initStack(&st); initQueue(&q);
    int ch,id;
    do{
        printf("\n1.Add\n2.Search\n3.Display\n4.Delete\n5.Update\n6.Sort\n7.Recent\n8.Borrow\n9.Return\n10.Exit\nChoice: ");
        scanf("%d",&ch);
        switch(ch){
            case 1:addBook(&lib,&st);break;
            case 2:printf("ID: ");scanf("%d",&id);{Book*b=searchBook(lib,id); if(b) printf("%d %s %s\n",b->bookID,b->title,b->author); else printf("Not found\n");}break;
            case 3:display(lib);break;
            case 4:printf("ID: ");scanf("%d",&id);deleteBook(&lib,id);break;
            case 5:printf("ID: ");scanf("%d",&id);updateBook(lib,id);break;
            case 6:sortBooks(lib);printf("Sorted.\n");break;
            case 7:printStack(&st);break;
            case 8:borrow(&q,lib);break;
            case 9:ret(&q);break;
        }
    }while(ch!=10);
    return 0;
}
