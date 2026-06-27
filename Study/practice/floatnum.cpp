// floatnum.cpp -- floating-point types
#include <iostream>
int main()
{
    using namespace std; 
    cout.setf(ios_base::fixed, ios_base::floatfield); // 设置定点输出
    float tub = 10.0 / 3.0;      // 单精度，大约能精确到 6 位小数
    double mint = 10.0 / 3.0;    // 双精度，大约能精确到 15 位小数
    const float million = 1.0e6;

    cout << "tub = " << tub;
    cout << ", a million tubs = " << million * tub;
    cout << ",\nand ten million tubs = ";
    cout << 10 * million * tub << endl;

    cout << "mint = " << mint << " and a million mints = ";
    cout << million * mint << endl;

    return 0;
}