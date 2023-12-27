#include <iostream>
#include <algorithm>
#include <string>
#include <random>

using namespace std;

int factorial(int number)
{
    if (number == 0 || number == 1)
    {
        return 1;
    }
    return number * factorial(number - 1);
}

string func(int* arr, int arrLength)
{
    int sum = 0;
    for (int i = 0; i < arrLength; i++)
    {
        sum += arr[i];
    }
    if (sum % 2 == 1)
    {
        return "-1";
    }
    int halfsum = sum / 2;

    int sumup, counter = 0;
    int swap_quantity = factorial(arrLength);

    random_device rd;
    default_random_engine eng(rd());
    
    do {
        if (counter > swap_quantity)
        {
            return "-1";
        }
        sumup = 0;
        shuffle(arr, arr + arrLength, eng);
        for (int i = 0; i < arrLength / 2; i++)
        {
            sumup += arr[i];
        }
    } while (sumup != halfsum);

    sort(arr, arr + arrLength / 2);
    sort(arr + arrLength / 2, arr + arrLength);

    string result = "{ ";
    for (int i = 0; i < arrLength - 1; ++i)
    {
        result += (to_string(arr[i]) + ", ");
    }
    result += (to_string(arr[arrLength - 1]) + " }");

    return result;
}

int main()
{
    int arr[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
    int arrLength = sizeof(arr) / sizeof(arr[0]);

    cout << func(arr, arrLength) << endl;


    return 0;
}
