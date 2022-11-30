#include<stdio.h>
void insertsrt(int *a,int n){
    for(int i=1;i<n;i++)
    {
        int key = a[i];
        int j = i-1;
        while(a[j]>key&&j>=0)
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1] = key;
    }
}
void main(){  
    printf("Enter the length : ");
    int n;
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements: ");
    for(int i=0;i<n;i++)
        scanf("%d", &arr[i]);
    
    insertsrt(arr,n);

    printf("\nAfter sorting: ");
    for(int i=0;i<n;i++)
        printf("%d ", arr[i]);
}  