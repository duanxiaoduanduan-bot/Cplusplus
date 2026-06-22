#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include <string>
#include <conio.h>
#include <cstdio>
#include <fstream>

using namespace std;

const string CONFIG_FILE = "clock_config.txt";

struct Config {
    string city;
};

void saveConfig(const Config& cfg) {
    ofstream file(CONFIG_FILE, ios::out | ios::trunc);
    if (file.is_open()) {
        file << cfg.city << endl;
        file.close();
    }
}

Config loadConfig() {
    Config cfg;
    cfg.city = "Beijing";
    ifstream file(CONFIG_FILE);
    if (file.is_open()) {
        string line;
        if (getline(file, line) && !line.empty()) {
            cfg.city = line;
        }
        file.close();
    }
    saveConfig(cfg);
    return cfg;
}

// 强制使用摄氏度：在 URL 末尾加 &m 或 ?m
string getWeather(const string& city) {
    if (city.empty()) return "城市名不能为空";
    // 使用 ?m 强制公制单位（摄氏度）
    string cmd = "curl -s --max-time 5 \"wttr.in/" + city + "?format=%C+%t&m\"";
    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) return "请安装 curl";
    char buffer[256];
    string result;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    int exitCode = _pclose(pipe);
    if (exitCode != 0) return "网络请求失败";
    while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
        result.pop_back();
    }
    return result.empty() ? "未获取到数据" : result;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    Config config = loadConfig();
    string city = config.city;
    string weather = getWeather(city);
    time_t lastWeatherUpdate = time(nullptr);

    cout << "========================================" << endl;
    cout << "   上次城市：" << city << "  单位：°C" << endl;
    cout << "   [C]切换城市  [Q]退出" << endl;
    cout << "========================================" << endl;
    Sleep(1500);

    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'c' || ch == 'C') {
                system("cls");
                cout << "╔══════════════════════════════════════════╗" << endl;
                cout << "║        🌍  切换天气城市              ║" << endl;
                cout << "╠══════════════════════════════════════════╣" << endl;
                cout << "║  当前城市：" << city << string(30 - city.length(), ' ') << "║" << endl;
                cout << "║  请输入新城市（拼音/英文，如 Shanghai）║" << endl;
                cout << "║  > ";
                cursorInfo.bVisible = true;
                SetConsoleCursorInfo(hConsole, &cursorInfo);
                string newCity;
                cin >> newCity;
                cursorInfo.bVisible = false;
                SetConsoleCursorInfo(hConsole, &cursorInfo);
                if (!newCity.empty()) {
                    city = newCity;
                    config.city = city;
                    weather = getWeather(city);
                    lastWeatherUpdate = time(nullptr);
                    saveConfig(config);
                }
                continue;
            }
            else if (ch == 'q' || ch == 'Q') {
                saveConfig(config);
                system("cls");
                cout << "\n👋 感谢使用，再见！" << endl;
                return 0;
            }
        }

        time_t now = time(nullptr);
        tm* local = localtime(&now);

        int hour   = local->tm_hour;
        int min    = local->tm_min;
        int sec    = local->tm_sec;
        int year   = local->tm_year + 1900;
        int month  = local->tm_mon + 1;
        int day    = local->tm_mday;
        int wday   = local->tm_wday;
        const char* weekdays[] = {"日", "一", "二", "三", "四", "五", "六"};

        // 每30分钟更新天气
        if (now - lastWeatherUpdate > 1800) {
            weather = getWeather(city);
            lastWeatherUpdate = now;
        }

        system("cls");

        cout << "╔══════════════════════════════════════════════╗" << endl;
        cout << "║          🌟  智 能 钟 表  🌟              ║" << endl;
        cout << "║                                              ║" << endl;
        cout << "║             "
             << setw(2) << setfill('0') << hour << ":"
             << setw(2) << setfill('0') << min << ":"
             << setw(2) << setfill('0') << sec
             << "              ║" << endl;
        cout << "║                                              ║" << endl;
        cout << "║   📅 " << year << "年" << month << "月" << day << "日"
             << "  星期" << weekdays[wday] << "                    ║" << endl;
        string weatherDisplay = weather;
        if (weatherDisplay.length() > 30) {
            weatherDisplay = weatherDisplay.substr(0, 28) + "..";
        }
        cout << "║   ☁️  📍" << city << "  " << weatherDisplay 
             << "                 ║" << endl;
        cout << "║                                              ║" << endl;
        cout << "║   [C]切换城市       [Q]退出                 ║" << endl;
        cout << "╚══════════════════════════════════════════════╝" << endl;

        Sleep(1000);
    }
    return 0;
}