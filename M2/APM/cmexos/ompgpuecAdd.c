#include <stdio.h>
#include <omp.h>

#define N 1024

int main(void)
{
    float a[N], b[N], c[N];
    int on_host = 1;

    /* 1. 在 CPU 上初始化输入 */
    for (int i = 0; i < N; i++) {
        a[i] = (float)i;
        b[i] = 2.0f * (float)i;
    }

    /* 2. 将输入传到 GPU，并行计算，再取回结果 */
    #pragma omp target teams distribute parallel for \
        map(to: a[0:N], b[0:N]) \
        map(from: c[0:N], on_host)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];

        /* 只让负责 i == 0 的线程记录实际执行位置 */
        if (i == 0) {
            on_host = omp_is_initial_device();
        }
    }

    /* 3. 回到 CPU，检查执行位置和计算结果 */
    printf("Execution: %s\n", on_host ? "CPU" : "target device");

    int errors = 0;
    for (int i = 0; i < N; i++) {
        if (c[i] != 3.0f * (float)i) {
            errors++;
        }
    }

    printf("c[0] = %.1f\n", c[0]);
    printf("c[%d] = %.1f\n", N - 1, c[N - 1]);
    printf("Errors: %d\n", errors);

    return errors != 0;
}