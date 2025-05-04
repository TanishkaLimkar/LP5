#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

long long arr_maxP(vector<long long> arr)
{
    long long maximum = arr[0];
    double start = omp_get_wtime();

#pragma omp parallel for reduction(max : maximum)
    for (long long i = 0; i < arr.size(); i++)
    {
        maximum = max(maximum, arr[i]);
    }
    double end = omp_get_wtime();
    cout << "Max : " << maximum << endl;
    cout << "Parallel Max time : " << end - start << endl;

    return maximum;
}
long long arr_max(vector<long long> &arr)
{
    long long maximum = arr[0];
    double start = omp_get_wtime();

    for (long long i = 0; i < arr.size(); i++)
    {
        maximum = max(maximum, arr[i]);
    }
    double end = omp_get_wtime();
    cout << "Max : " << maximum << endl;
    cout << "Sequential Max time : " << end - start << endl;

    return maximum;
}

long long arr_minP(vector<long long> &arr)
{
    long long minimum = arr[0];
    double start = omp_get_wtime();
#pragma omp parallel for reduction(min : minimum)
    for (long long i = 0; i < arr.size(); i++)
    {
        minimum = min(minimum, arr[i]);
    }
    double end = omp_get_wtime();
    cout << "Min : " << minimum << endl;
    cout << "Parallel MIn time : " << end - start << endl;

    return minimum;
}

long long arr_min(vector<long long> &arr)
{
    long long minimum = arr[0];
    double start = omp_get_wtime();

    for (long long i = 0; i < arr.size(); i++)
    {
        minimum = min(minimum, arr[i]);
    }
    double end = omp_get_wtime();
    cout << "Min : " << minimum << endl;
    cout << "MIn time : " << end - start << endl;

    return minimum;
}

long long arr_SumP(vector<long long> &arr)
{
    long long sum = 0;
    double start = omp_get_wtime();

#pragma omp parallel for reduction(+ : sum)
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    double end = omp_get_wtime();
    cout << "Parallel sum : " << sum << endl;
    cout << "Parallel sum time : " << end - start << endl;

    return sum;
}

long long arr_Sum(vector<long long> &arr)
{
    long long sum = 0;
    double start = omp_get_wtime();

    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    double end = omp_get_wtime();
    cout << "sum : " << sum << endl;
    cout << "sum time : " << end - start << endl;

    return sum;
}

double arr_avgP(vector<long long> &arr)
{
    long long sum = 0;
    double start = omp_get_wtime();
#pragma omp parallel for reduction(+ : sum)
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    double avg = (double)sum / arr.size();
    double end = omp_get_wtime();

    cout << "Avg : " << avg << endl;
    cout << "Parallel Avg time : " << end - start << endl;

    return avg;
}

double arr_avg(vector<long long> &arr)
{
    long long sum = 0;
    double start = omp_get_wtime();
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    double avg = (double)sum / arr.size();
    double end = omp_get_wtime();

    cout << "Avg : " << avg << endl;
    cout << "Avg time : " << end - start << endl;

    return avg;
}

int main()
{
    long long N = 90000000;
    vector<long long> arr = {9, 8, 4, 6, 7, 0, 4, 2, 3};

    for (int i = 0; i < N; i++)
    {
        arr.push_back(rand() % 1000);
    }
    arr_max(arr);
    arr_maxP(arr);
    cout << endl;

    arr_min(arr);
    arr_minP(arr);
    cout << endl;

    arr_Sum(arr);
    arr_SumP(arr);
    cout << endl;

    arr_avg(arr);
    arr_avgP(arr);
    cout << endl;

    return 0;
}