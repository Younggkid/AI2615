// Merge_counter.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
using namespace std;
void merge_count(int a[], int c[], int start, int end);
void merge_sort(int a[], int c[], int start, int end);
int main()
{
    int num_row = 0;
    cin >> num_row;
    int* row = new int[num_row];
    for (int i = 0; i < num_row; ++i) row[i] = 0;

    int* counter = new int[num_row];
    for (int i = 1; i <=num_row; ++i) counter[i] = 0;

    for (int i = 0; i < num_row; ++i) cin >> row[i];
    merge_sort(row, counter, 0, num_row - 1);
    for (int i = 1; i < num_row; ++i)
    {
        cout << counter[i];
        cout << ' ';
    }
    cout << counter[num_row];
    

    
    
    return 0;
}


void merge_count(int a[], int c[], int start, int end)
{
    int num = end - start + 1;
    int* tmp = new int[num];

    int i = 1, j = 1;
    int k = 0;
    int n = num / 2, m = num - n;
    while (i <= n && j <= m)
    {
        if (a[start + i - 1] < a[start + j - 1 + n])
        {
            tmp[k++] = a[start + i - 1];
            c[a[start + i - 1]]+=j-1;
            i++;
        }
        else
        {   

            tmp[k++] = a[start + j - 1 + n];
            c[a[start + j - 1 + n]]+=n-i+1;
            
            j++;
        }
    }
    while (i <= n)
    {
        c[a[start + i - 1]] += m;
        tmp[k++] = a[start + i - 1];
        i++;
    }
    while (j <= m)
    {

        tmp[k++] = a[start + j - 1 + n];
        j++;
    }
    for (int i = 0, k = start; k <= end;) a[k++] = tmp[i++];
    delete[] tmp;
}

void merge_sort(int a[], int c[], int start, int end)
{
    if (start == end) return;
    int num = end - start + 1;
    int n = num / 2, m = num - n;
    
    merge_sort(a, c, start, start+n-1);
    merge_sort(a, c, start+n, end);
    merge_count(a, c, start, end);

}