#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <random>
#include <ctime>
#define N 100

void RandomizeLider(int arr[], int size, int range)
{
    int x = rand()% range;
    for (int i =0; i < size; i++)
        if(rand()%2==0)
            arr[i] = rand()% range;
        else
            arr[i]=x;
}

void Randomize(int arr[], int size, int range)
{
    for (int i = 0; i < size; i++)
        arr[i] = rand() % range;
}

void Wypisz(int arr[], int size, int dec)
{
    for(int i = 0; i <size; i++)
        std::cout<< std::setw(dec) << arr[i] << '\n';
    std::cout<< '\n' << '\n';
}

int LiderHashMap(bool arr[], int size)
{
    std::unordered_map<int, int> m;
    for(int i = 0; i < size; i++)
        m[arr[i]]++;
    int count = 0;
    for(auto i : m)
        if(i.second > size / 2)
            return i.first;
    return -1;
}

int Idol(bool arr[][N]) 
{
    int k = 0, i = 1;
    while (i<N) 
    {
        if (arr[k][i])
            k = i;
        i++;
    }
    i = 0;
    arr[k][k] = false;
    while (i < N && !arr[k][i])
        i++;
    if (i < N)
        return -1;
    i = 0;
    while (i < N && arr[i][k])
        i++;
    if (i == N)
        return k;
    else
        return -1;
}

(int,int) maxSubArraySum(int arr[], int size)
{
    int max = INT_MIN, maxEd = 0;
    int max_idx = 0 , idx = 0;

    for (int i = 0; i < size; i++)
    {
        maxEd = maxEd + arr[i];
        if (max < maxEd) {
            max_idx = idx;
            max = maxEd;
        }

        if (maxEd < 0) {
            maxEd = 0;
            idx=i+1;
        }
    }
    return (max,max_idx);
}

int NSPNM(int arr[], int size) 
{
    int maxDl = 1, dl = 1, maxIdx = 0, idx = 0, i;
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] > arr[i - 1]) 
        {
            dl++;
            if(dl>maxDl){
                maxDl = dl;
                maxIdx = idx;
            }     
        }
        else 
        {
            idx = i;
            dl = 1;
        }
    }
    return maxIdx;
}

int main()
{
    srand(time(0));
    int tab[N];
    return 0;
}
