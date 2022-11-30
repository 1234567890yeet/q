#include<stdio.h> 
void maxHeapify(int a[], int n, int i)
{
    int left = 2 * i + 1, right = 2 * i + 2;
    int largest = i;
    if (left < n && a[left] > a[largest])
        largest = left;
    if (right < n && a[right] > a[largest])
        largest = right;
    if (largest != i)
    {
        int temp = a[largest];
        a[largest] = a[i];
        a[i] = temp;
        maxHeapify(a, n, largest);
    }
}
void heapSort(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(a, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        maxHeapify(a, i, 0);
    }
}
void main()
{
    printf("Enter the length : ");
    int n;
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    heapSort(arr, n);
    printf("\nSorted: ");

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}