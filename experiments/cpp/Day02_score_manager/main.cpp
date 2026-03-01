#include <iostream>
#include <vector>
#include <limits>   // numeric_limits
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::vector;

void printMenu();
int  readInt(const string& prompt);                 // 带输入校验
void addScore(vector<int>& scores);                 // 添加成绩
void printScores(const vector<int>& scores);        // 打印成绩列表
double calculateAverage(const vector<int>& scores); // 平均分
int getMaxScore(const vector<int>& scores);         // 可选加分项
int getMinScore(const vector<int>& scores);         // 可选加分项

int main() {
    vector<int> scores;
    bool running = true;

    while (running) {
        printMenu();
        int choice = readInt("Choose an option: ");

        switch (choice) {
            case 1:
                addScore(scores);
                break;
            case 2:
                printScores(scores);
                break;
            case 3: {
                double avg = calculateAverage(scores);
                if (scores.empty()) {
                    cout << "No scores yet.\n";
                } else {
                    cout << "Average: " << avg << "\n";
                }
                break;
            }
            case 4: { // 加分项：max/min
                if (scores.empty()) {
                    cout << "No scores yet.\n";
                } else {
                    cout << "Max: " << getMaxScore(scores) << "\n";
                    cout << "Min: " << getMinScore(scores) << "\n";
                }
                break;
            }
            case 0:
                running = false;
                cout << "Bye!\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
                break;
        }
        cout << "\n";
    }

    return 0;
}

void printMenu() {
    cout << "===== Score Manager (Day02) =====\n";
    cout << "1) Add score\n";
    cout << "2) Show all scores\n";
    cout << "3) Show average\n";
    cout << "4) Show max & min (bonus)\n";
    cout << "0) Exit\n";
}

int readInt(const string& prompt) {
    while (true) {
        cout << prompt;

        int x;
        cin >> x;

        if (!cin.fail()) {
            return x;
        }

        // 输入失败：清理错误状态 + 丢弃本行残留输入
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input, please enter an integer.\n";
    }
}

void addScore(vector<int>& scores) {
    // TODO: 读入一个 0~100 的整数，否则提示重输
    // 提示：用 readInt，再用 while 判断范围
}

void printScores(const vector<int>& scores) {
    // TODO: 若为空提示；否则逐个打印（带序号）
}

double calculateAverage(const vector<int>& scores) {
    // TODO: 若为空返回 0 或者做特殊处理
    // 提示：用 long long sum 防溢出（习惯）
    return 0.0;
}

int getMaxScore(const vector<int>& scores) {
    // TODO: 返回最大值（假设非空）
    return 0;
}

int getMinScore(const vector<int>& scores) {
    // TODO: 返回最小值（假设非空）
    return 0;
}