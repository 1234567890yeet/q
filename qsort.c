#include <stdio.h>
#include <stdlib.h>
int partition(int *a, int l, int u)
{
    int pivot = u;
    int i = l, temp;
    for (int j = l; j < u; j++)
    {
        if (a[j] < a[pivot])
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
        }
    }
    temp = a[i];
    a[i] = a[pivot];
    a[pivot] = temp;
    return i;
}
void quicksort(int *a, int l, int u)
{
    if (l < u)
    {
        int pivot = partition(a, l, u);
        quicksort(a, l, pivot - 1);
        quicksort(a, pivot + 1, u);
    }
}

void main()
{
    printf("Enter the length : ");
    int n;
    scanf("%d", &n);
    int a[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    quicksort(a, 0, n - 1);

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
}
