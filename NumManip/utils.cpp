#include<string>
#include<iostream>
#include<sstream>

typedef unsigned __int32 u32;
typedef  __int32 s32;
typedef unsigned __int64 u64;
typedef  __int64 s64;
typedef  unsigned __int16 u16;
typedef __int16 s16;
typedef unsigned __int8 u8;
typedef __int8 s8;

inline static int Clamp(int val, int min, int max)
{
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

static int toDeci(std::string str, const int base)
{
    int pow = 1;
    int num = 0;

    int tempN;


    for (int i = str.size() - 1; i >= 0; i--) {

        if (int(str[i]) - 48 >= base) {
            return -1;
        }
        num += tempN * pow;
        pow *= base;
    }

    return num;
}

static char reVal(int num)
{
    if (num >= 0 && num <= 9)
        return (char)(num + '0');
    else
        return (char)(num - 10 + 'A');
}


static std::string fromDeci(int base, int inputNum)
{

    std::string res = "";

    while (inputNum > 0) {

        res += reVal(inputNum % base);
        inputNum /= base;
    }

    reverse(res.begin(), res.end()); // such efficient algorithm. TOTALLY couldn't be done better >_>

    return res;
}

static std::string convertBase(std::string s, int baseFrom, int baseTO)
{
    int num = toDeci(s, baseFrom);

    std::string res = fromDeci(baseTO, num);
    return res;
}