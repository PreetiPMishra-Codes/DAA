#include <stdio.h>
#include<stdlib.h>
int arr[1000],chosen[20];
int n,k;
long T;
int cmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}
int binSearch(int val,int used)
{
    int l=0,h=n-1;
    while(l<=h)
    {
        int mid=(l+h)/2;
        if(arr[mid]==val)
        {
            for(int i=0;i<used;i++)
                if(chosen[i]==mid)return -1;
                return mid;
        }
        else if(arr[mid]<val)
        l=mid+1;
        else
        h=mid-1;
    }
    return -1;
}
int solve(int start,int depth,long sum)
{
    if(depth==k-1)
    {
        long need=T-sum;
        int idx=binSearch((int)need,depth);
        if(idx!=1)
        {
            chosen[depth]=idx;
            return 1;
        }
        return 0;
    }
    for(int i=start;i<n;i++)
    {
        chosen[depth]=i;
        if(solve(i+1,depth+1,sum+arr[i]))
        return 1;
    }
    return 0;
}
int main()
{
   int input[] = {12, 3, 7, 1, 9, 15, 20, 5, 8, 2};
    n = sizeof(input) / sizeof(input[0]);
    for (int i = 0; i < n; i++) arr[i] = input[i];
    qsort(arr, n, sizeof(int), cmp);

    k = 4;
    T = 30;

    printf("Sorted set: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\nLooking for %d numbers that sum to %ld\n", k, T);

    if (solve(0, 0, 0)) {
        printf("Found: ");
        for (int i = 0; i < k; i++) printf("%d ", arr[chosen[i]]);
        printf("\n");
    } else {
        printf("No such %d elements found\n", k);
    }

    return 0;
}
