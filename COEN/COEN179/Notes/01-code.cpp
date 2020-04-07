#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void insertion_sort(vector<int> & V)
{
    for (int i = 1; i < V.size(); ++i)
        for (int j = i; j > 0 && V[j] < V[j-1]; --j)
            swap(V[j], V[j-1]);
}

unsigned f(unsigned n)
{
    if (n == 0)
        return 0;
    return 1 + f(n-1) + f(n-1);
}

unsigned gcd1(unsigned a, unsigned b)
{
    for (unsigned d = min(a, b); d > 0; --d)
        if (a % d == 0 && b % d == 0)
            return d;
    return max(a, b);
}

unsigned gcd2(unsigned a, unsigned b)
{
    while (b > 0)
    {
         unsigned temp = b;
         b = a % b;
         a = temp;
    }
    return a;
}

int main()
{
    unsigned a = 3210987654;
    unsigned b = 2109876543;
    
    cout << "Running gcd1 function" << endl;
    unsigned output;

    time_t first_time, second_time, total_time;
    first_time = time(NULL);
    output = gcd1(a, b);
    second_time = time(NULL);
    total_time = second_time - first_time;
    cout << output << " It also took: (in seconds) " << total_time << endl;
    
    cout << "Running gcd2 function" << endl;
    first_time = time(NULL);
    output = gcd2(a, b);
    second_time = time(NULL);
    total_time = second_time - first_time;
    cout << output << " It also took: (in seconds) " << total_time << endl;

    while (true)
    {
         unsigned n;
         cout << "Enter n: ";
         cin >> n;
         cout << f(n) << endl;
    }
    
    return 0;
}
