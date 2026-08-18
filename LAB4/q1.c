#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int num;
    char col;
}Item;
int code(char c)
{
    if(c=='R')return 0;
    if(c=='B')return 1;
    return 2;
}
void sortbycolor(Item a[],int n)
{
    int cnt[3]={0,0,0};
    int pos[3];
    Item *out=malloc(n*sizeof(Item));

    for(int i=0;i<n;i++)
    cnt[code(a[i].col)]++;

    pos[0]=0;
    pos[1]=cnt[0];
    pos[2]=cnt[0]+cnt[1];

    for(int i=0;i<n;i++)
    {
        int c=code(a[i].col);
        out[pos[c]]=a[i];
        pos[c]++;
    }
    for(int i=0;i<n;i++)
    a[i]=out[i];

    free(out);
}
void printitems(Item a[],int n)
{
    for(int i=0;i<n;i++)
    printf("(%d,%c)",a[i].num,a[i].col);
printf("\n");
}
int main(void)
{
    Item a[] = {
        {1, 'Y'}, {2, 'B'}, {3, 'R'}, {4, 'B'},
        {5, 'Y'}, {6, 'R'}, {7, 'R'}, {8, 'Y'}, {9, 'B'}
    };
    int n=sizeof(a)/sizeof(a[0]);
    printf("Before: ");
    printitems(a,n);
    sortbycolor(a,n);
    printf("After: ");
    printitems(a,n);
    return 0;
}
