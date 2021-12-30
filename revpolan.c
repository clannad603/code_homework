#include<stdio.h>
#define MaxSize 100
typedef struct stack
{
    char top;
    char list[MaxSize];
    int size;
}Stack;

void stackInitiate(Stack *L) /*初始化顺序表L*/
{
    L->size = 0; /*定义初始数据元素个数*/
}

int ListInsert(Stack*L, int i,char x)

{
    int j;
    if (L->size >= MaxSize)
    {
        printf("顺序表已满无法插入! \n");
        return 0;
    }
    else
    {
        for (j = L->size; j > i; j--)
            L->list[j] = L->list[j-1];
        L->list[i] = x;
        L->size++;
        return 1;
    }
}

int ListDelete(Stack *L, int i, char *x)

{
    int j;
    if (L->size <= 0)
    {
        printf("顺序表已空无数据元素可删! \n");
        return 0;
    }
    else
    {

        *x = L->list[i];
        for (j = i + 1; j <= L->size - 1; j++)
            L->list[j-1] = L->list[j];
        L->size--;
        return 1;
    }
}
int ListGet(Stack L, int i, char *x)
/*取顺序表L中第i个数据元素的值存于x中，成功则返回1，失败返回0*/
{

        *x = L.list[i];
        return 1;

}
void push(Stack* a,char data){
    ListInsert(a,a->size+1,data);
    a->top = data;
}

char pop(Stack* a){
    char result;
    ListGet(*a,a->size,&a->top);
    ListDelete(a,a->size,&result);
    return result;
}

int getIndex(char theta)   //获取theta所对应的索引
{
    int index = 0;
    switch (theta)
    {
        case '+':
            index = 0;
            break;
        case '-':
            index = 1;
            break;
        case '*':
            index = 2;
            break;
        case '/':
            index = 3;
            break;
        case '(':
            index = 4;
            break;
        case ')':
            index = 5;
            break;
        case '#':
            index = 6;
        default:break;
    }
    return index;
}


char getPriority(char theta1, char theta2)   //获取theta1与theta2之间的优先级
{
    const char priority[][7] =     //算符间的优先级关系
            {
                    { '>','>','<','<','<','>','>' },
                    { '>','>','<','<','<','>','>' },
                    { '>','>','>','>','<','>','>' },
                    { '>','>','>','>','<','>','>' },
                    { '<','<','<','<','<','=','0' },
                    { '>','>','>','>','0','>','>' },
                    { '<','<','<','<','<','0','=' },
            };

    int index1 = getIndex(theta1);
    int index2 = getIndex(theta2);
    return priority[index1][index2];
}
int isOp(char a){
    if(a =='+'||a=='-'||a=='*'||a=='/'||a=='('||a==')'||a=='#'){
        return 1;
    } else{
        return 0;
    }
}

int isDigit(char a){
    if(a<='9'&&a>='0'){
        return 1;
    }
    return 0;
}

int  input(char s[]){
    char c = 0;
    int count = 0;
    while (c!='#'){
        while ((c=getchar())==' ');
        s[count++]= c;
    }
    return count;
}

int get(int x,int y,char op){
    switch (op) {
        case '+':
            return x+y;
        case '-':
            return x-y;
        case '*':
            return x*y;
        case '/':
            return x/y;
        default:
            return 0;
    }
}
int main(){
    Stack opter;
    stackInitiate(&opter);
    push(&opter,'#');
    Stack opnd;
    stackInitiate(&opnd);
    char s[10]={0};
    int count = 0;
    count = input(s);
    char sum=0;
    for (int i = 0; i < count; ++i) {
        if(isOp(s[i])){
            switch (getPriority(opter.top,s[i])) {
                case '<':
                    push(&opter,s[i]);
                    break;
                case '=':
                    pop(&opter);
                    break;
                case '>':
                    while (getPriority(opter.top,s[i])=='>'){
                        int y = pop(&opnd)-'0';
                        int x = pop(&opnd)-'0';
                        char op = pop(&opter);
                        x = get(x,y,op);
                        push(&opnd,x+'0');
                    }
                    if(getPriority(opter.top,s[i])=='<'){
                        push(&opter,s[i]);
                    } else{
                        pop(&opter);

                    }
                    break;
                default:
                    printf('erro');
            }
        } else{
            push(&opnd,s[i]);
        }
    }
    sum = pop(&opnd);
    printf("%d",sum-'0');
    return 0;
}
