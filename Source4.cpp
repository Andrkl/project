#include <iostream>
#include <string>

bool IsKPeriodic(const std::string& str, int k) {
    int length = str.length();

    if (k <= 0) {
        return false;
    }

    if (length % k != 0) {
        return false;
    }

    int period = length / k;

    for (int i = 0; i < period; i++) {
        for (int j = 0; j < k; j++) {
            if (str[i] != str[j * period + i]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    std::string str = "ABABAB";
    int k = 2;

    bool result = IsKPeriodic(str, k);
    std::cout << std::boolalpha << result << std::endl;

    return 0;
}