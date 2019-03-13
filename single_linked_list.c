#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    struct node *next;
}node_t;

typedef struct list{
    struct node* head;
}list;

void init(list *l)
{
    l->head=NULL;
}

//проверка на пустоту списка
int isEmpty(list* l) {
    return l->head == NULL;
}

//удалить все элементы из списка
void clear(list* l) {
    node_t* tmp;
    node_t* p = l->head;

    while (p){
        tmp=p->next;
        free(p);
        p=tmp;
    }
    l->head=NULL;
}

//поиск элемента по значению
node_t* find(list* l, int value) {
    node_t *cursor = l->head;

    while (cursor->value != value) {
        if (cursor->next != NULL)
            cursor = cursor->next;
        else return NULL;
    }
    return cursor;
}

node_t* getNode(int value)
{
    node_t* tmp = malloc(sizeof(node_t));
    tmp->value=value;
    tmp->next=NULL;
    return tmp;
}

//вставка значения в конец списка,вернуть 0 если успешно
int push_back(list* l, int value)
{
    node_t *tmp = l->head;
    if (tmp==NULL){
        l->head=getNode(value);
        return 0;
    }
    while (tmp->next){
        tmp=tmp->next;
    }
    tmp->next=getNode(value);
    return 0;
}

//вставка значения в начало списка,вернуть 0 если успешно
int push_front(list* l, int value)
{
    node_t *tmp = malloc(sizeof(node_t));
    tmp->value = value;
    tmp->next = l->head;
    l->head = tmp;
    return 0;
}

int removeFirst(list *l, int value)
{
    node_t *tmp = l->head;
    node_t *prev = l->head;
    while (tmp && tmp->value != value)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp)
    {
        if (tmp == l->head)
            l->head = l->head->next;
        else
            prev->next = tmp->next;
        free(tmp);
    }
    return 0;
}

//вставка значения после указанного узла
int insertAfter	(list* l, unsigned n, int value) {
    node_t *cursor = malloc(sizeof(node_t));
    cursor->value = value;

    node_t* tmp = l->head;
    node_t* prev = l->head;

    for (int i = 1; i < (n + 1); i++) {
        prev = tmp;
        tmp = tmp->next;

        if (tmp == NULL)
            return -1;
    }

    prev->next = cursor;
    cursor->next = tmp;

    return 0;
}

//вывод всех значения из списка в прямом порядке
void print(list* l) {
    node_t* cursor = l->head;

    while (cursor->next != NULL) {
        printf("%d ", cursor->value);
        cursor = cursor->next;
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
    print(&l);

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
    print(&l);

    //удаление определенного элемента
    int z;
    printf("Введите число z:"); scanf("%d",&z);
    removeFirst(&l,z);
    print(&l);

    //очистка списка
    clear(&l);
    print(&l);

    return 0;
}
