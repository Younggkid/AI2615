// k-th Smallest Number.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include<stdlib.h>
#include<time.h>
#include<iomanip>
using namespace std;
const int N = 4e7 + 1;
int n, k;
int a[N];
#define random(a,b) (((double)rand()/RAND_MAX)*(b-a)+a)
void read_input_data() {
    int m;
    cin >> n >> k >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    unsigned int z = a[m];
    for (int i = m + 1; i <= n; i++) {
        z ^= z << 13;
        z ^= z >> 17;
        z ^= z << 5;
        a[i] = z & 0x7fffffff;
    }
}// xorshift 随机生成器

int select(int a[], int k, int start, int end)
{
    if (k==1&&start==end) return a[start];
    srand((int)time(0));
    int v = random(start, end);
    int value = a[v];
    int num = end - start + 1;
    int* Left = new int[num];
    int* Mid = new int[num];
    int* Right = new int[num];
    int l = 0, m = 0, r = 0;
    for (int i = start; i <= end; ++i)
    {
        if (a[i] < value)
        {
            Left[l] = a[i];
            ++l;
        }
        else if (a[i] == value)
        {
            Mid[m] = a[i];
            ++m;
        }
        else
        {
            Right[r] = a[i];
            ++r;
        }
    }//divide
    int s = start;
    for (int i = 0; i < l; ++i)
    {
        a[s] = Left[i];
        ++s;
    }
    for (int i = 0; i < m; ++i)
    {
        a[s] = Mid[i];
        ++s;
    }
    for (int i = 0; i < r; ++i)
    {
        a[s] = Right[i];
        ++s;
    }
    delete[] Left;
    delete[] Right;
    delete[] Mid;
    if (k <= l)
    {
        return select(a, k, start, start+l - 1);
    }
    else if (l < k && k<= l + m) return value;
    else if (k > l + m) return select(a, k - l - m,end-r+1,end);
    
}
int main()
{
    read_input_data();
    int result = select(a, k, 1, n);
    cout << result;
    return 0;

}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
