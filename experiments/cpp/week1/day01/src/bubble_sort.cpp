// 需要传入数组，进行排序，无需返回值，按照我的理解来说
// 既然需要改变原数组的顺序，可能需要引入指针数组
// n作为arr[n],可能也不需要，我直接用len()获得
//之前学到使用终止符来提前终止，尝试使用

#include<iostream>
using namespace std;

void Bubble_sort(int arr[],int n)//尝试使用int*arr[]但是错误
{
    for(int i=0;i<n-1;i++)//本想通过len获取长度但是不会用
    {
        //终止符
        bool swapped = false;
        
        for(int j=0;j<n-1-i;j++)
        {
            if(arr[j]>arr[j+1])
            {
                int temp= arr[j] ;
                arr[j]=arr[j+1];
                arr[j+1]= temp;
                swapped=true;                
            }

        }

        cout << "Round " << i + 1 << ": ";
        for (int k = 0; k < n; k++) cout << arr[k] << " ";
        cout << endl;

        if(!swapped) break;
    }

}

int main()
{
    int arr[10];
    int n=10;
    

    cout << "Input 10 numbers:\n";
    for (int i = 0; i < n; i++) cin >> arr[i];

    Bubble_sort(arr, n);

    cout << "Final: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;

}