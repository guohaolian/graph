// 冒泡排序
// 冒泡排序
void bubble_sort(int arr[], int len)
{
    int i, j, temp;
    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j]; // 交换
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
// 快速排序
void quick_sort(int arr[], int low, int high)
{
    int i = low, j = high, temp, base = arr[low];
    if (low < high)
    {
        while (i < j)
        {
            while (i < j && arr[j] >= base)
            {
                j--;
            }
            if (i < j)
            {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
            while (i < j && arr[i] <= base)
            {

                i++;
            }
            if (i < j)
            {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
        quick_sort(arr, low, i - 1);
        quick_sort(arr, i + 1, high);
    }
}