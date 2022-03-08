// 快速傅里叶变换.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 2e6 + 5;
const double Pi = 3.1415926535898;
int t, n, m, len = 1;

struct Compx {  
    double x, y;
    Compx(double t1 = 0, double t2 = 0) { x = t1, y = t2; }
}A[maxn * 2], B[maxn * 2], C[maxn * 2];
Compx operator +(Compx a, Compx b) { return Compx(a.x + b.x, a.y + b.y); }
Compx operator -(Compx a, Compx b) { return Compx(a.x - b.x, a.y - b.y); }
Compx operator *(Compx a, Compx b) { return Compx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }

void FFT(Compx* a, int n, int flag) {
    if (n == 1) return;  
    Compx* a1 = new Compx[n/2+1];
    Compx* a2 = new Compx[n/2+1];
    for (int i = 0; i < (n >> 1); ++i) a1[i] = a[i << 1], a2[i] = a[i << 1 | 1];
    FFT(a1, n >> 1, flag);
    FFT(a2, n >> 1, flag);
    Compx w1(cos(2 * Pi / n), flag * sin(2 * Pi / n)), w(1, 0);
    for (int i = 0; i < (n >> 1); ++i, w = w * w1) {
        a[i] = a1[i] + w * a2[i];
        a[i + (n >> 1)] = a1[i] - w * a2[i];
    }
    delete[] a1;
    delete[] a2;
    return;
}

int main() {
    scanf_s("%d%d", &n, &m); int x;
    for (int i = 0; i <= n; ++i) scanf_s("%lf", &A[i].x);
    for (int i = 0; i <= m; ++i) scanf_s("%lf", &B[i].x);
    while (len < n + m+1) len <<= 1;  
    FFT(A, len, 1); 
    FFT(B, len, 1);
    for (int i = 0; i < len; ++i) C[i] = A[i] * B[i];
    FFT(C, len, -1);  
    for (int i = 0; i <= n + m; ++i) {
        x = C[i].x / len + 0.5;
        printf("%d ", x);
    }
    return 0;
}

