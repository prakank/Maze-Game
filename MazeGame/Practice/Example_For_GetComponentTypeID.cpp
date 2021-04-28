#include <bits/stdc++.h>
using namespace std;

inline int add()
{
    static int a = 0;    
    return a++;
}

template<typename T> int add() noexcept
{
    static int last = add();
    return last;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    auto x = add<int>();
    auto y = add<float>();
    auto z = add<double>();
    auto w = add<long long>();
    
    auto a = add<float>();
    auto b = add<double>();
    cout << x << endl << y << endl;
    cout << z << endl << w << endl;
    cout << a << endl << b << endl;
    
    // cout << typeid(x).name << endl;
    
    return 0;
}    