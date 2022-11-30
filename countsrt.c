#include<stdio.h>
#include<stdlib.h>
int findMax(int*a,int n){
    int max=a[0];
    for (int i = 1; i < n; i++)
    {
        if (max<a[i])
            max=a[i];
    }
    return max;
}
int main(){
    int n;
    printf("Enter number of elements : ");
    scanf("%d",&n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter %d element : ",i+1);
        scanf("%d",&a[i]);
    }

    int cpy[n],indx[findMax(a,n)+1];
    for (int i = 0; i <= findMax(a,n); i++)
        indx[i]=0;
    for (int i = 0; i < n; i++)
        ++indx[a[i]];
    for (int i = 1; i <= findMax(a,n); i++)
        indx[i] +=indx[i-1];
    for (int i = n-1; i >=0; i++)
        cpy[indx[a[i]] - 1] = a[i];
    for (int i = 0; i < n; ++i)
        a[i] = cpy[i];
        printf("Final array : ");
    for (int i = 0; i < n; i++)
        printf("%d\t",a[i]);
    return 0;
}