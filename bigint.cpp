#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
    string value;

    BigInt(string s = "0") {
        value = s;
    }

    bool isLess(BigInt other) {
        if (value.length() != other.value.length())
            return value.length() < other.value.length();
        return value < other.value;
    }

    BigInt operator+(BigInt other) {
        string res = "";
        int i = value.length() - 1, j = other.value.length() - 1, ostatok = 0;
        while (i >= 0 || j >= 0 || ostatok) {
            int v1 = 0;
            int v2 = 0;

            if (i >= 0) {
                v1 = value[i] - '0';
                i--;
            }

            if (j >= 0) {
                v2 = other.value[j] - '0';
                j--;
            }

            int sum = ostatok + v1 + v2;
            
            res += (char)((sum % 10) + '0'); 
            
            ostatok = sum / 10;
    }
        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    BigInt operator-(BigInt other) {
        string res = "";
        int i = value.length() - 1, j = other.value.length() - 1, zimaj = 0;
        while (i >= 0) {
            int v1 = value[i] - '0'; 
            i--;

            int v2 = 0; 
            if (j >= 0) {
                v2 = other.value[j] - '0';
                j--;
            }

            int sub = v1 - v2 - zimaj;

            if (sub < 0) {
                sub = sub + 10;
                zimaj = 1; 
            } else {
                zimaj = 0; 
            }

            res += (char)(sub + '0');
        }
        while (res.length() > 1 && res.back() == '0') res.pop_back();
        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    BigInt operator*(BigInt other) {
        int n = value.length(), m = other.value.length();
        vector<int> res(n + m, 0);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (value[i] - '0') * (other.value[j] - '0');
                int sum = mul + res[i + j + 1];
                res[i + j + 1] = sum % 10;
                res[i + j] += sum / 10;
            }
        }
        string s = "";
        for (int x : res) if (!(s.empty() && x == 0)) s += (char)(x + '0');
        return s.empty() ? BigInt("0") : BigInt(s);
    }

    BigInt operator/(BigInt other) {
        if (other.value == "0") return BigInt("Error");
        string res = "", currentStr = "";
        for (char c : value) {
            currentStr += c;
            while(currentStr.size() > 1 && currentStr[0] == '0') currentStr.erase(0, 1);
            
            BigInt current(currentStr);
            int count = 0;
            while (!(current.isLess(other))) {
                current = current - other;
                currentStr = (current.value == "0") ? "" : current.value;
                count++;
            }
            res += (char)(count + '0');
        }
        size_t first = res.find_first_not_of('0');
        return (first == string::npos) ? BigInt("0") : BigInt(res.substr(first));
    }
};

int main() {
    BigInt a("10000000000000000000");
    BigInt b("5000000000000000000");

    BigInt sum = a + b;
    BigInt div = a / b;
    BigInt sub = a-b;
    BigInt mul = a*b;

    cout << "A + B = " << sum.value << endl;
    cout << "A / B = " << div.value << endl;
    cout << "A - B = " << sub.value << endl;
    cout << "A * B = " << mul.value << endl;

    return 0;
}
