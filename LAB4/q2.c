#include <stdio.h>
#include <stdlib.h>
int cmp(const void *a, const void *b)
{
    return *(int *)a-*(int *)b;
}
int findpair(int s1[],int n1,int s2[],int n2,int x, int *va,int *vb)
{
    qsort(s1,n1,sizeof(int),cmp);
    qsort(s2,n2,sizeof(int),cmp);
    int i=0,j=n2-1;
    while(i<n1 && j>=0)
    {
        int sum=s1[i]+s2[j];
        if(sum==x)
        {
            *va=s1[i];
            *vb=s2[j];
            return 1;
        }
        else if(sum<x)
        i++;
        else
        j--;
    }
    return 0;
}
int main()
{
    int s1[] = {8, 1, 4, 6, 10, 2};
    int s2[] = {5, 20, 3, 9, 7};
    int n1 = sizeof(s1) / sizeof(s1[0]);
    int n2 = sizeof(s2) / sizeof(s2[0]);
    int x=17;
    int va,vb;
    if(findpair(s1,n1,s2,n2,x,&va,&vb))
    printf("Found pair: %d (from S1) + %d (from S2) = %d\n", va, vb, x);
    else
        printf("No pair from S1 and S2 adds up to %d\n", x);

    return 0;
}
