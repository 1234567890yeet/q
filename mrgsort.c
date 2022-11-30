#include <stdio.h>
#include <stdlib.h>
void merge(int *arr, int p, int m, int q)
{
    int L = m - p + 1, R = q - m, j = 0, k = p;
    int lrr[L], rrr[R];
    for (int i = 0; i < L; i++)
        lrr[i] = arr[i + p];
    for (int i = 0; i < R; i++)
        rrr[i] = arr[i + m + 1];
    int i = 0;
    while (i < L && j < R)
    {
        if (lrr[i] < rrr[j])
        {
            arr[k] = lrr[i];
            i++;
        }
        else
        {
            arr[k] = rrr[j];
            j++;
        }
        k++;
    }
    while (i < L)
    {
        arr[k] = lrr[i];
        i++;
        k++;
    }
    while (j < R)
    {
        arr[k] = rrr[j];
        j++;
        k++;
    }
}
void merge_sort(int *arr, int p, int q)
{
    if (p < q)
    {
        int m = (q - p) / 2 + p;
        merge_sort(arr, p, m);
        merge_sort(arr, m + 1, q);
        merge(arr, p, m, q);
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

    merge_sort(a, 0, n - 1);

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
}
