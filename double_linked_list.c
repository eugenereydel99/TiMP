#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    struct node *next;
    struct node *prev;
}node_t;

typedef struct list{
    struct node* head;
    struct node* tail;
}list;

//инициализация списка
void init(list *l)
{
    l->head=NULL;
    l->tail=NULL;
}

//удалить все элементы из списка
void clear(list* l) {
    node_t* tmp=l->head;
    node_t* p = NULL;

    while (tmp){
        p=tmp->next;
        free(tmp);
        tmp=p;
    }
    l->head=NULL;
    l->tail=NULL;
}

//проверка на пустоту списка
int isEmpty(list* l) {
    return l->head == NULL && l->tail==NULL;
}

//поиск элемента по значению
node_t* find(list* l, int value) {
    node_t *cursor = l->head;

    while (cursor->value!=value) {
        if (cursor->next != NULL)
            cursor = cursor->next;
        else return NULL;
    }
    return cursor;
}

//вставка значения в конец списка,вернуть 0 если успешно
int push_back(list* l, int value)
{
    node_t *tmp = malloc(sizeof(node_t));
    tmp->value=value;
    if (isEmpty(l)){
        tmp->next=NULL;
        tmp->prev=NULL;
        l->head=tmp;
        l->tail=tmp;
    }else{
        l->tail->next=tmp;
        tmp->next=NULL;
        tmp->prev=l->tail;
        l->tail=tmp;
    }
    return 0;
}

//вставка значения в начало списка,вернуть 0 если успешно
int push_front(list* l, int value)
{
    node_t *tmp = malloc(sizeof(node_t));
    tmp->value = value;
    l->head->prev=tmp;
    tmp->next = l->head;
    tmp->prev=NULL;
    l->head=tmp;
    return 0;
}

//удаление первого элемента из списка с указанным значением
int removeFirst(list *l, int value)
{
    node_t *tmp = l->head;
    node_t *p = l->head;
    while (tmp && tmp->value != value)
    {
        p = tmp;
        tmp = tmp->next;
    }
    if (tmp)
    {
        if (tmp == l->head){
            l->head = l->head->next;
            l->head->prev=NULL;
        }
        else if(tmp==l->tail){
            l->tail = l->tail->prev;
            l->tail->next=NULL;
        }
        else {
            p->next=tmp->next;
            tmp->next->prev=p;
        }
        free(tmp);
    }
    return 0;
}

//удаление последнего элемента из списка с указанным значением
int removeLast(list *l, int value)
{
    node_t* tmp = l->tail;
    node_t* p = l->tail;
    while(tmp && tmp->value != value)
    {
        p = tmp;
        tmp = tmp->prev;
    }
    if(tmp)
    {
        if (tmp == l->head)
            {
                l->head = l->head->next;
                l->head->prev = NULL;
            }
        else if (tmp == l->tail)
            {
                l->tail = l->tail->prev;
                l->tail->next = NULL;
            }
        else
            {
                p->prev = tmp->prev;
                tmp->prev->next = p;
            }
        free(tmp);
    }
    return 0;
}

//вставка значения после указанного узла
int insertAfter	(list* l, unsigned n, int value) {
    node_t *cursor = l->head;

    for (int i = 1; i < n; ++i) {
         cursor = cursor->next;

         if (cursor == NULL) return -1;
    }
    node_t* tmp = malloc(sizeof(node_t));
    tmp->value = value;
    tmp->next = cursor->next;
    tmp->prev = cursor;

    cursor->next->prev = tmp;
    cursor->next = tmp;

    return 0;
}

//вставка значения до указанного узла
int insertBefore(list* l, unsigned n, int value) {
    node_t *cursor = l->head;

    for (int i = 1; i < n; ++i) {
        cursor = cursor->next;

        if (cursor == NULL) return -1;
    }
    node_t *tmp = malloc(sizeof(node_t));
    tmp->value = value;
    tmp->prev = cursor->prev;
    tmp->next = cursor;

    cursor->prev = tmp;
    tmp->prev->next = tmp;

    return 0;
}

//вывод всех значений из списка в прямом порядке
void print(list* l) {
    node_t* cursor = l->head;
    
    if (cursor == NULL){
        return;
    }

    while (cursor->next != NULL) {
        printf("%d ", cursor->value);
        cursor = cursor->next;
    }
    printf("%d\n", cursor->value);
}

//вывод всех значений из списка в обратном порядке
void print_invers(list* l)
{
    node_t *cursor = l->tail;
    
    if (cursor == NULL){
        return;
    }
    
    while (cursor->prev!=NULL) {
        printf("%d ", cursor->value);
        cursor = cursor->prev;
    }
    printf("%d\n", cursor->value);
}

int main()
{
    //создаем экземпляр структуры list
    list l;

    //инициализируем список
    init(&l);

    int n,elm;
    printf("Введите количество элементов списка:");
    scanf("%d",&n);

    printf("Вводите элементы списка:\n");
    for (int i = 0 ; i < n ; i++) {
        scanf("%d/n",&elm);
        push_back(&l,elm);
    }
    print(&l);

    //находим элементы ki
    int k;
    printf("Введите три значения для поиска в списке:\n");
    for (int i=1;i<=3;i++) {
        scanf("%d",&k);
        if (find(&l,k)!=0){
            printf("1\n");
        }else {
            printf("0\n");
        }
    }

    //вставка в конец списка
    int m;
    printf("Введите число m:");
    scanf("%d",&m);
    push_back(&l,m);
    print_invers(&l);

    //вставка в начало списка
    int t;
    printf("Введите число t:");
    scanf("%d",&t);
    push_front(&l,t);
    print(&l);

    //вставка элемента z после j-го узла
    int j,x;
    printf("Введите число j:"); scanf("%d",&j);
    printf("Введите число x:"); scanf("%d",&x);
    insertAfter(&l,j,x);
    print_invers(&l);

    //вставка значения y перед указанным узлом u
    int u,y;
    printf("Введите число u:"); scanf("%d",&u);
    printf("Введите число y:"); scanf("%d",&y);
    insertBefore(&l,u,y);
    print(&l);

    //удаление первого встретившегося элемента со значением z
    int z;
    printf("Введите число z:");
    scanf("%d",&z);
    removeFirst(&l,z);
    print_invers(&l);

    //удаление последнего элемента со значением r
    int r;
    printf("Введите число r:");
    scanf("%d",&r);
    removeLast(&l,r);
    print(&l);

    //очистка списка
    clear(&l);
    print(&l);

    return 0;
}
