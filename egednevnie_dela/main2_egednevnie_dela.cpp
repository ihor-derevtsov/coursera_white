#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector< std::vector<std::string> > getNextMonth();
void addNewTask();
void dumpMonth();
void nextMonth();

int n{0};
std::string command;
int month_counter{0};
int month_number{0};
int next_month_number{1};
std::vector<int> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
std::vector< std::vector<std::string> > now(months[month_number]);

int main() {
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> command;
        if (command == "ADD") { addNewTask(); }
        else if (command == "DUMP") { dumpMonth(); }
        else if (command == "NEXT") { nextMonth(); }
        else { 
            --i;
            continue;
        }
    }

    return 0;
}

void addNewTask() {
    int i;
    std::string s;
    std::cin >> i >> s;
    if (i <= now.size()) {
        now[i-1].push_back(s);
    }
    else {
        std::cout << "ERROR" << std::endl;
        --i;
    }
}

void dumpMonth() {
    int i;
    std::cin >> i;
    if (i <= now.size()) {
        std::cout << now[i-1].size();
        for (auto s : now[i-1]) { std::cout << " " << s; }
        std::cout << std::endl;
    }
    else {
        std::cout << "ERROR" << std::endl;
        --i;
    }
}

void nextMonth() {
    if (month_counter < 11) { 
        ++month_counter;
        now = getNextMonth();
        ++month_number;
        next_month_number = month_number + 1;
        
     }
    else { 
        month_counter = 0;
        month_number = 0;
        next_month_number = 1;
     }
 }

std::vector< std::vector<std::string> > getNextMonth() {
    if (months[month_number] == months[next_month_number]) { return now; }
    else if (months[month_number] < months[next_month_number]) {
        auto difference = months[next_month_number] - months[month_number];
        std::vector<std::string> empt{};
        for (int i = 0; i < difference; ++i) { now.push_back(empt); }
        return now;
    }
    else {
        auto difference = months[month_number] - months[next_month_number];
        std::vector< std::vector<std::string> > result{};
        for (int i = 0; i < months[next_month_number]; ++i) { result.push_back(now[i]); }
        auto index = now.size() - difference - 1;
        for (int i = index; i < now.size(); ++i) {
            for (auto s : now[i]) {
                auto found = find(result.back().begin(), result.back().end(), s);
                if (found == result.back().end()) {
                result.back().push_back(s);
                }
            }
        }
        return result;
    }
}
