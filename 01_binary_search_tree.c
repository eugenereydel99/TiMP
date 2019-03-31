#include <stdio.h>
#include <stdlib.h>

//создание структуры дерева
typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
    struct node *parent;

}node;

typedef struct tree
{
    int count;
    node *root;

}tree;

void init_tree(tree *t)
{
    t->root=NULL;
    t->count=0;
}

//создание структуры очереди
typedef struct node_queue
{
    node *cursor;
    struct node_queue *next;
}node_queue;

typedef struct queue
{
    node_queue *head;
    node_queue *tail;
}queue;

void init_queue(queue *q)
{
    q->head=NULL;
    q->tail=NULL;
}

int push(queue *q,node *n)
{
    node_queue *temp = malloc(sizeof(node_queue));
    temp->cursor = n;
    temp->next = NULL;

    if (q->head)
        q->tail->next = temp;
    else
        q->head = temp;
    q->tail = temp;

    return 0;
}

node *pop(queue *q)
{
    if (q->head)
    {
        node_queue *nq;
        node *tmp = NULL;
        tmp = q->head->cursor;
        nq = q->head;
        q->head = q->head->next;
        if (q->head == NULL)
            q->tail = NULL;
        free(nq);
        return tmp;
    }
    else return NULL;
}

void clear_queue(queue *q)
{
    node_queue *tmp, *nq;
    tmp = q->head;
    do
    {
        nq = tmp;
        tmp = tmp->next;
        free(nq);

    }while(tmp);

    q->head = NULL;
    q->tail = NULL;
}


//------------------------------------------------------------------//


//вставка элемента в дерево
int insert(tree *t, int value)
{
    node *tmp = malloc(sizeof(node));
    if (tmp == NULL)
        return 2;
    node *p = t->root;
    node *q = NULL;
    if (p)
    {
        while(p)
        {
            if (value < p->value)
            {
                q = p;
                p = p->left;
            }
            else if (value > p->value)
            {
                q = p;
                p = p->right;
            }
            else
                return 1;
        }
        tmp->value = value;
        tmp->left = tmp->right = NULL;
        tmp->parent = q;
        if (tmp->value > q->value)
            q->right = tmp;
        else
            q->left = tmp;
        t->count++;
        return 0;
    }
    else
    {
        t->root = tmp;
        t->root->value = value;
        t->root->parent = NULL;
        t->root->left = t->root->right = NULL;
        t->count++;
        return 0;
    }
}

//поиск элемента по значению
int find(tree *t,int value,node **n)
{
    node *tmp=t->root;
    while (tmp) {
        if (value<tmp->value){
            tmp=tmp->left;
        }else if (value>tmp->value) {
            tmp=tmp->right;
        }else {
            *n=tmp;
            return 0;
        }
    }
    *n=tmp;
    return 1;
}

//удаление элемента из дерева
int _remove(tree *t, int value)
{
    node *tmp = t->root;
    while (tmp->value != value)
    {
        if (value < tmp->value)
            tmp = tmp->left;
        else if (value > tmp->value)
            tmp = tmp->right;
    }
    if (tmp == NULL)
        return 1;
    if (tmp->left == NULL && tmp->right == NULL)
    {
        if (tmp->parent->value > value)
            tmp->parent->left = NULL;
        else
            tmp->parent->right = NULL;
        free(tmp);
    }
    else if (tmp->left != NULL && tmp->right == NULL)
    {
        tmp->left->parent = tmp->parent;
        if (tmp->parent->value > value)
            tmp->parent->left = tmp->left;
        else
            tmp->parent->right = tmp->left;
        free(tmp);
    }
    else if (tmp->left == NULL && tmp->right != NULL)
    {
        tmp->right->parent = tmp->parent;
        if (tmp->parent->value > value)
            tmp->parent->left = tmp->right;
        else
            tmp->parent->right = tmp->right;
        free(tmp);
    }
    else if (tmp->left != NULL && tmp->right != NULL)
    {
        node *p = tmp->right;
        if (p->left == NULL)
        {
            tmp->value = p->value;
            if (p->right == NULL)
            {
                tmp->right = NULL;
                free(tmp->right);
            }
            else
            {
                tmp->right = tmp->right->right;
                p->right->parent = tmp;
                free(p);
            }
        }
        else
        {
            while(p->left)
                p = p->left;
            tmp->value = p->value;
            if (p->right)
            {
                tmp->value = p->value;
                p->value = p->right->value;
                tmp->right = NULL;
                free(p->right);
            }
            else
            {
                tmp->value = p->value;
                p->parent->left = NULL;
                free(p);
            }
        }
    }

    t->count--;

    return 0;
}


//поиск минимального значения
node *min(node *root)
{
    node *l=root;
    while (l->left!=NULL)
        l=l->left;
    return l;
}

//поиск следующего элемента
node *next(node *root)
{
    node *p = malloc(sizeof(node));
    p=root->parent;
    node *l = NULL;

    if (p->right!=NULL){
        return min(p->right);
    }
    l=p->parent;
    while ((l != NULL) && (p == l -> right)){
        p=l;
        l=l->parent;
    }
    return l;
}

//удаление минимального значения
void clearMinNode(node *n)
{

    node *tmp = malloc(sizeof(node));
    tmp=n->parent;

    if ((n->left == NULL && n->right == NULL)){
        if (tmp->left==n){
            tmp->left=NULL;
        }
        if (tmp->right==n){
            tmp->right=NULL;
        }
    }
    else if (n->left == NULL || n->right == NULL) {
        if (n->left == NULL){
            if (tmp->left==n){
                tmp->left=n->right;
            }else {
                tmp->right=n->right;
            }
            n->right->parent=tmp;
        }
        else {
            if (tmp->left==n){
                tmp->left=n->left;
            }else{
                tmp->right=n->left;
            }
            n->left->parent=tmp;
        }
    }
    else {
        node *p = next(tmp);
        n->value=p->value;
        if (p->parent->left==p){
            p->parent->left=p->right;
            if (p->right!=NULL)
                p->right->parent=p->parent;
        }
        else {
            p->parent->right=p->left;
            if (p->left != NULL)
                p->right->parent=p->parent;
        }
    }
}

//очистка всего дерева
void clearTree(tree *t)
{

    while (t){
        if (t->root==NULL)
            break;
        else {
            clearMinNode(t->root);
            free(t);
        }
    }
    t->root=NULL;
    t->count=0;

}

//правое вращения поддерева
int rotateRight(node **n)
{
    node *tmp = (*n)->left;
    if (tmp == NULL)
        return 1;
    (*n)->left = tmp->right;
    tmp->right = (*n);
    tmp->parent = (*n)->parent;
    (*n)->parent = tmp;
    (*n) = tmp;
    return 0;
}

//левое вращение поддерева
int rotateLeft(node **n)
{
    node *tmp = (*n)->right;
    if (tmp == NULL)
        return 1;
    (*n)->right = tmp->left;
    tmp->left = (*n);
    tmp->parent = (*n)->parent;
    (*n)->parent = tmp;
    (*n) = tmp;
    return 0;
}

//вывод всех значений поддерева
void print(node *n) {

    if (n == NULL)
        printf("-\n");

    else {
        queue *queue1 = malloc(sizeof (queue));
        queue *queue2 = malloc(sizeof (queue));
        node *l = n->left;
        node *r = n->right;
        node *tmp;
        node_queue *nqueue;

        {
            queue1->head = queue1->tail = NULL;
            queue2->head = queue2->tail = NULL;
        }

        int i = 0,j = 0;

        push(queue1, n);

        while (!NULL)
        {
            while (queue1->head != NULL) {

                if (queue1->head != NULL) {
                    node_queue *ntmp = queue1->head;
                    node *p = queue1->head->cursor;
                    queue1->head = queue1->head->next;

                    if (queue1->head == NULL)
                        queue1->tail = NULL;
                    free(ntmp);

                    tmp = p;
                }
                else
                    tmp = NULL;

                if (queue1->head==NULL) {

                    if (tmp->value == n->value && i == 1)
                        printf("_\n");
                    else
                        printf("%d\n", tmp->value);
                }

                else if(tmp->value == n->value && i == 1)
                    printf("_ ");

                else
                    printf("%d ", tmp->value);

                if (tmp->left != NULL)
                    push(queue2, tmp->left);
                else
                    push(queue2, n);

                if (tmp->right != NULL)
                    push(queue2, tmp->right);
                else
                    push(queue2, n);
            }

            n->right = n->left = NULL;
            nqueue = queue2->head;
            i = 1;

            while (queue2->head->cursor->value == n->value) {
                queue2->head = queue2->head->next;

                if(queue2->head->next == NULL) {

                    if(queue2->head->cursor->value == n->value) {
                        j = 1;
                        n->left = l;
                        n->right = r;
                        pop(queue2);

                        break;
                    }
                }
            }

            queue2->head = nqueue;
            queue1->head = queue2->head;
            queue1->tail = queue2->tail;
            queue2->head = queue2->tail = NULL;
            queue2->tail = NULL;

            if(j == 1)
                break;
        }
    }
}

//вывод всех значений дерева t
void printTree(tree *t)
{
    print(t->root);
}


int main()
{

    tree t;
    init_tree(&t);

    int a;

    for (int i = 0; i < 4; i++)
    {
        scanf("%d", &a);
        insert(&t, a);
    }
    printTree(&t);

    for (int i = 0; i < 3; i++)
    {
        scanf("%d", &a);
        insert(&t, a);
    }
    printTree(&t);

    int m;
    for (int i = 0; i < 2; i++)
    {
        scanf("%d", &m);
        node *n = NULL;
        int k = find(&t, m, &n);
        if (k == 0)
        {
            if (n->parent)
                printf("%d ", n->parent->value);
            else printf("_ ");
            if (n->left)
                printf("%d ", n->left->value);
            else printf("_ ");
            if (n->right)
                printf("%d\n", n->right->value);
            else printf("_\n");
        }
        else printf("-\n");
    }

    scanf("%d", &m);
    _remove(&t, m);
    printTree(&t);


    while (rotateLeft(&t.root) == 0) {
        rotateLeft(&t.root);
    }
    printTree(&t);

    while (rotateRight(&t.root) == 0) {
        rotateRight(&t.root);
    }
    printTree(&t);

    printf("%d\n", t.count);

    clearTree(&t);
    printTree(&t);

    return 0;
}
