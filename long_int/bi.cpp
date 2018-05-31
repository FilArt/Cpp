#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void RemoveZeros(string&  a) // удаление нолей в начале числа
{
    while(a.size() > 1 && a[0] == '0')
    {
        a.erase(0, 1);
    }
}

bool IsEqualInts(string  a, string  b) // сравнение длин чисел
{
    RemoveZeros(a);
    RemoveZeros(b);
    return  a.size() == b.size() ? a < b : a.size() < b.size();
}

void Reduce(string&  a, const string&  b) // a - b, если a < b, то вычитает так: a - b + 10
{
    for(size_t  current = 0; current < b.size(); ++current)
    {
        size_t  aCurrent = a.size() - 1 - current;
        size_t  bCurrent = b.size() - 1 - current;

        string::reference aCurrentDigit = a [aCurrent];
        const char&  bCurrentDigit = b [bCurrent];

        if(aCurrentDigit >= bCurrentDigit)
        {
            aCurrentDigit -= bCurrentDigit - '0';
        }
        else
        {
            (aCurrentDigit -= bCurrentDigit - '0') += 10;

            int i = 1;
            while(true)
            {
                if(a[aCurrent - i] == '0')
                {
                    a[aCurrent - i] = '9';
                    ++i;
                }
                else
                {
                    --a[aCurrent - i];
                    break;
                }
            }
        }
        RemoveZeros(a);
    }
    RemoveZeros(a);
}

void Increment(std::string&  a) // увелич. число на единицу
{
    for (size_t i = a.size() - 1; i >= 0; --i)
    {
        if (a[i] == '9')
        {
            a[i] = '0';
        }
        else
        {
            ++a[i];
            return;
        }
    }
    a.insert(0, "1");
    return;
}



string DivAndMod(string&  a, const string&  b) // целоч-ое деление и остаток
{
    if(b == "0") { return  "ZeroDivision Error"; }

    string  res = "0";
    string  sub  = b;

    while(sub.size() < a.size())
    {
        sub += '0';
    }

    while(true)
    {
        while(!IsEqualInts(a, sub))
        {
            Reduce(a, sub);
            Increment(res);
        }
        if(sub.size() <= b.size())
        {
            break;
        }

        sub.erase(sub.size() - 1);
        res += '0';
        RemoveZeros(res);
    }
    return res + "\n" + a;
}

int main()
{
    string a;
    string b;

    ifstream fin("input.txt");
    fin >> a;
    fin >> b;
    fin.close();

    ofstream fout("output.txt");
    fout << DivAndMod(a, b) << endl;
    fout.close();

    // string a = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    // string b = "999999999999999999999999999999999999999999999999999";
    // cout << DivAndMod(a, b) << endl;
    // cout << "13580246791358024679135802467913580246791358024679";
    // cout << DivAndMod(0, 9) << endl;
}
