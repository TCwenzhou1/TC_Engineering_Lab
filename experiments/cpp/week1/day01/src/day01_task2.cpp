#include <iostream>
using namespace std;

int main()
{
    
    int arr[5] = {1,2,3,4,5};

    arr[5] = 999;        // 越界写
    cout << arr[0] << endl;
    cout << arr[4] << endl;
    cout << arr[5] << endl;  // 越界读（看是否变成999）

    

    return 0;
}