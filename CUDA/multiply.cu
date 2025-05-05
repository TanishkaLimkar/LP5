#include <iostream>
#include <cuda_runtime.h>

__global__ void matmul(float *a, float *b, float *c, int N)
{
    int row = threadIdx.y, col = threadIdx.x;
    if (row < N && col < N)
    {
        float val = 0;
        for (int i = 0; i < N; ++i)
            val += a[row * N + i] * b[i * N + col];
        c[row * N + col] = val;
    }
}

int main()
{
    const int N = 3, SIZE = N * N * sizeof(float);
    float a[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, b[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1}, c[9];

    float *d_a, *d_b, *d_c;
    cudaMalloc(&d_a, SIZE);
    cudaMalloc(&d_b, SIZE);
    cudaMalloc(&d_c, SIZE);
    cudaMemcpy(d_a, a, SIZE, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, SIZE, cudaMemcpyHostToDevice);

    matmul<<<1, dim3(N, N)>>>(d_a, d_b, d_c, N);
    cudaMemcpy(c, d_c, SIZE, cudaMemcpyDeviceToHost);

    for (int i = 0; i < 9; ++i)
    {
        std::cout << c[i] << (i % N == N - 1 ? "\n" : " ");
    }

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    return 0;
}
