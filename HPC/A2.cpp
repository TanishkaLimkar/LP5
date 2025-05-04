#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

vector<int> deepCopy(vector<int> &arrSource)
{
    vector<int> arrDestination;

    for (int i = 0; i < arrSource.size(); i++)
    {
        arrDestination.push_back(arrSource[i]);
    }

    return arrDestination;
}

void printArr(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void BubbleSort(vector<int> &arr)
{
    int n = arr.size();

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void BubbleSortParallel(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
#pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
#pragma omp critical
                {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

void Merge(vector<int> &arr, int start, int end, int mid)
{
    vector<int> L;
    vector<int> R;

    for (int i = start; i <= mid; i++)
    {
        L.push_back(arr[i]);
    }

    for (int j = mid + 1; j <= end; j++)
    {
        R.push_back(arr[j]);
    }
    int i = 0;
    int j = 0;
    int k = start;
    while (i < L.size() && j < R.size())
    {
        if (L[i] <= R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    while (i < L.size())
    {
        arr[k++] = L[i++];
    }
    while (j < R.size())
    {
        arr[k++] = R[j++];
    }
}

void MergeSort(vector<int> &arr, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;

        MergeSort(arr, start, mid);
        MergeSort(arr, mid + 1, end);

        Merge(arr, start, end, mid);
    }
}

void MergeSortParallel(vector<int> &arr, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            MergeSortParallel(arr, start, mid);
#pragma omp section
            MergeSortParallel(arr, mid + 1, end);
        }

        Merge(arr, start, end, mid);
    }
}

int main()
{
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90, 77, 23, 10};

    for (int i = 0; i < 25; i++)
    {
        arr.push_back(rand() % 1000);
    }

    vector<int> arr1 = deepCopy(arr);

    double start = omp_get_wtime();
    BubbleSort(arr);
    double end = omp_get_wtime();
    cout << "Squential Bubble sort : ";
    printArr(arr);
    cout << "Time taken BS : " << end - start << endl;

    start = omp_get_wtime();
    BubbleSortParallel(arr1);
    end = omp_get_wtime();
    cout << "Parallel Bubble sort : ";
    printArr(arr1);
    cout << "Time taken PBS : " << end - start << endl;

    vector<int> arr2 = deepCopy(arr);
    start = omp_get_wtime();
    MergeSort(arr2, 0, arr.size() - 1);
    end = omp_get_wtime();
    cout << "Squential Merge sort : ";
    printArr(arr2);
    cout << "Time taken MS : " << end - start << endl;

    vector<int> arr3 = deepCopy(arr);
    start = omp_get_wtime();
    MergeSortParallel(arr3, 0, arr.size() - 1);
    end = omp_get_wtime();
    cout << "Parallel Merge sort : ";
    printArr(arr3);
    cout << "Time taken PMS : " << end - start << endl;
}
