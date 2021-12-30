#include <stdio.h>
#include <stdlib.h>

typedef enum Status {
    False, True
} Boolean;
typedef struct {
    int arrive;
    int treat;//客户的信息结构
} People;

typedef struct node {
    People people;
    struct node *next;//队列中的元素信息
} LNODE, *QueuePtr;

typedef struct { //链队列类型
    QueuePtr front;   //队头指针
    QueuePtr rear;   //队尾指针
    int size;
} LinkQueue;

void initQueue(LinkQueue *linkQueue) {
    linkQueue->front = linkQueue->rear = (LNODE *) malloc(sizeof(LNODE));//同一块空间
    linkQueue->front->next = NULL;
    linkQueue->size = 0;
}

void push(LinkQueue *linkQueue, People people) {
    LNODE *l = (LNODE *) malloc(sizeof(LNODE));
    l->people = people;
    l->next = NULL;
     linkQueue->rear->next = l;
    linkQueue->rear = l;
    linkQueue->size++;
}

Boolean isEmp(LinkQueue *linkQueue) {
    return linkQueue->size == 0 ? True : False;
}

int out(LinkQueue *linkQueue, People *people) {
    QueuePtr p ;
    if (isEmp(linkQueue)) {
        return 0;
    }
    *people = linkQueue->front->next->people;
    p = linkQueue->front->next;
    linkQueue->front->next = linkQueue->front->next->next;
    if (linkQueue->rear == p){
        linkQueue->rear = linkQueue->front;
    }
    free(p);
    linkQueue->size--;
    return 1;
}

int readFrom(People *people, FILE *fp) {
    int have;
    have = fscanf(fp, "%d %d", &people->arrive, &people->treat);
    return have;
}

static FILE *initFile(FILE *fp) {
    if ((fp = fopen("queue.txt", "r")) == NULL) {
        printf("文件打开出错");
        return 0;
    }
    return fp;
}

int main() {
    LinkQueue l;
    initQueue(&l);
    FILE *fp = NULL;
    fp = initFile(fp);
    int wait_sum_1 = 0, wait_sum_2 = 0;//1为业务员等待时间，2为客户等待时间
    int clock = 0;//当前时钟
    int nub = 0;//积累客户
    int have = 0;//判断是否还存在客户
    Boolean cs = True;
    People temp;
    have = readFrom(&temp, fp);
    People temp_2;
    do {
        if (have == 2 && isEmp(&l)) {
            wait_sum_1 += (temp.arrive - clock);
            clock = temp.arrive;
            push(&l, temp);
            have = readFrom(&temp, fp);

        }
        nub++;//客户数量累积
        out(&l, &temp_2);
        wait_sum_2 += (clock - temp_2.arrive);
        clock += temp_2.treat;
        while (temp.arrive <= clock && have == 2) {
            push(&l, temp);
            have = readFrom(&temp, fp);
        }
    } while (have == 2 || !isEmp(&l));

    printf("业务员等待时间为%d\n客户平均等待时间为%f", wait_sum_1, (float) wait_sum_2 / (float) nub);


    return 0;
}
