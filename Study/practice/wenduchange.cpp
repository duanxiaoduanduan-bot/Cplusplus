#include <iostream>
#include <iomanip>
#include <limits>
#include <windows.h>

using namespace std;

// 摄氏度转华氏度
double celsiusToFahrenheit(double c) {
    return c * 9.0 / 5.0 + 32.0;
}

// 华氏度转摄氏度
double fahrenheitToCelsius(double f) {
    return (f - 32.0) * 5.0 / 9.0;
}

int main() {
    // 设置编码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    int choice;
    double temp, result;
    
    cout << "========================================" << endl;
    cout << "     欢迎使用温度转换器" << endl;
    cout << "========================================" << endl;
    
    while (true) {
        cout << "\n1. 摄氏度转华氏度" << endl;
        cout << "2. 华氏度转摄氏度" << endl;
        cout << "3. 退出" << endl;
        cout << "请选择：";
        cin >> choice;
        
        if (choice == 3) {
            cout << "再见！" << endl;
            break;
        }
        
        if (choice == 1) {
            cout << "请输入摄氏度：";
            cin >> temp;
            result = celsiusToFahrenheit(temp);
            cout << temp << "°C = " << result << "°F" << endl;
        } 
        else if (choice == 2) {
            cout << "请输入华氏度：";
            cin >> temp;
            result = fahrenheitToCelsius(temp);
            cout << temp << "°F = " << result << "°C" << endl;
        } 
        else {
            cout << "无效选择！" << endl;
        }
    }
    
    return 0;
}