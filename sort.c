#include <stdio.h>
typedef int KeyType;
typedef struct seqList {
    KeyType key;
    int value;
} SeqList;

KeyType c[10] = {9,13,15,7,45,32,56,89,60,36};

KeyType d[11] = {5,7,9,12,15,18,20,22,25,30,100};

void initSeqList(SeqList seqList [], KeyType keyType[], int n){
    for(int i = 0; i<n;i++){
        seqList[i].key = keyType[i];
    }
}

int SeqSearch(SeqList R[], int n, KeyType k) {
    int i = 0;
    while (i < n && R[i].key != k) {
        printf("%d", R[i].key);
        i++;
    }
    if (i >= n)
        return -1;
    else {
        printf("%d", R[i].key);
        return i;
    }
}

int BinSearch(SeqList R[], int n, KeyType k) {
    int low = 0, high = n - 1, mid, count = 0;
    while (low <= high) {
        mid = (low + high) / 2;
        printf("第%d次查找：在[ %d ,%d]中找到元素R[%d]:%d\n ", ++count, low, high, mid, R[mid].key);
        if (R[mid].key == k)
            return mid;
        if (R[mid].key > k)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int main() {
    int result = 0;
    int key ;
    SeqList a[10],b[11];
    scanf("%d",&key);
    initSeqList(a,c,10);
    result = SeqSearch(a,10,key);
    printf("\n");
    if (result!=-1) printf("this seqList has this value which is located at %d \n ",result);
    else printf("this SeqList hasn't the value\n");

    int where_12 ,where_28;
    initSeqList(b,d,11);
    where_12 = BinSearch(b,10,12);
    where_28 = BinSearch(b,10,28);

    printf("12 is located at %d ,28 is located at %d",where_12,where_28);
    return 0;
}
