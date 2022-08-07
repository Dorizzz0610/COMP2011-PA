#include <iostream>
using namespace std;
//you are NOT allowed to include any additional library
const int ARRAY_MAX_SIZE = 12;

//given; do NOT modify; please refer to the webpage description
void printArray(int array[], int arraySize, int currentPosition)
{
    cout << array[currentPosition];
    if(currentPosition < arraySize-1)
    {
        if(array[currentPosition+1] > 0)
            cout << "+";
        printArray(array, arraySize, currentPosition+1);
    }
    else
        cout << endl;
}

//given; do NOT modify; please refer to the webpage description
void printArray(int array[], int arraySize)
{
    printArray(array, arraySize, 0);
}

void copyArray(int original[], int result[], int size, int currentPosition)
{
    if(currentPosition < size)
    {
        result[currentPosition] = original[currentPosition];
        copyArray(original, result, size, currentPosition + 1);
    }
}

void copyArray(int original[], int result[], int size)
{
    copyArray(original, result, size, 0);
}


//***** Only write your code below this line, remember that NO loop is allowed! ***** 
int arraySum(int array[], int arraySize, int currentPosition, int currentSum)
{
    if(currentPosition < arraySize)
    {
        currentSum += array[currentPosition];
        arraySum(array, arraySize, currentPosition + 1, currentSum);
    }
    else
    {
        return currentSum;
    }
    
}

int arraySum(int array[], int arraySize)
{
    return arraySum(array, arraySize, 0, 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool solve(int input[], int size, int target, int result[], int& resultSize, int inputPosition) 
{
    
    if(inputPosition < size - 1)
    {
        /***
        //solved at this point
        if(arraySum(result, resultSize) == target)
        {
            return true;
        }
        ***/

        //not solved at this point
        int array_plus[size];
        copyArray(result, array_plus, resultSize);
        array_plus[resultSize] = input[inputPosition + 1];
        int resultSize_plus = resultSize + 1;
        if(solve(input, size, target, array_plus, resultSize_plus, inputPosition + 1))
        {
            resultSize = resultSize_plus;
            copyArray(array_plus, result, resultSize);
            return true;
        }

        int array_minus[size];
        copyArray(result, array_minus, resultSize);
        array_minus[resultSize] = - input[inputPosition + 1];
        int resultSize_minus = resultSize + 1;
        if(solve(input, size, target, array_minus, resultSize_minus, inputPosition + 1))
        {
            resultSize = resultSize_minus;
            copyArray(array_minus, result, resultSize);
            return true;
        }

        int array_empty[size];
        copyArray(result, array_empty, resultSize);
        if(solve(input, size, target, array_empty, resultSize, inputPosition + 1))
        {
            copyArray(array_empty, result, resultSize);
            return true;
        }
    }
    else
    {
        if(arraySum(result, resultSize) == target)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }

}

bool solve(int input[], int size, int target, int result[], int& resultSize) 
{
    int start_with_plus[size];
    int start_with_minus[size];
    int start_with_empty[size];
    int resultSize_plus = 1, resultSize_minus = 1, resultSize_empty = 0;
    start_with_plus[0] = input[0];
    start_with_minus[0] = -input[0];

    if(solve(input, size, target, start_with_plus, resultSize_plus, 0))
    {
        resultSize = resultSize_plus;
        copyArray(start_with_plus, result, resultSize);

        return true;
    }
    else if(solve(input, size, target, start_with_minus, resultSize_minus, 0))
    {
        resultSize = resultSize_minus;
        copyArray(start_with_minus, result, resultSize);
        
        return true;
    }
    else if(solve(input, size, target, start_with_empty, resultSize_empty, 0))
    {
        resultSize = resultSize_empty;
        copyArray(start_with_empty, result, resultSize);

        return true;
    }
    
    return false; 
}




void printString(const char str[], int currentPosition)
{
    
    if(str[currentPosition] != '\0')
    {
        cout << str[currentPosition];
        printString(str, currentPosition + 1);
    }
    else
    {
        cout << endl;
    }
    
}

void printString(const char str[])
{
    printString(str, 0);
}



int pow(int base, int exp, int result, int currentPos)
{
    if(currentPos < exp)
    {
        result *= base;
        pow(base, exp, result, currentPos + 1);
    }
    else
    {
        return result;
    }
    
}

int pow(int base, int exp)
{
    return pow(base, exp, 1, 0);
}



int getIntValue(const char str[], int start, int end, int currentPos, int result)
{
    if(currentPos < end)
    {
        int exp = end - currentPos;
        int currentNum = str[currentPos] - '0';
        result += currentNum * pow(10, exp);
        getIntValue(str, start, end, currentPos + 1, result);
    }
    else
    {
        int currentNum = str[currentPos] - '0';
        result += currentNum;
        return result;
    }

}


int getIntValue(const char str[], int start, int end)
{
    return getIntValue(str, start, end, start, 0); 
}



void findSign(const char str[], int signPosition[], int& signNum, int currentPosition)
{
    if(str[currentPosition] != '\0')
    {
        if(str[currentPosition] == '-' || str[currentPosition] == '+')
        {
            signPosition[signNum] = currentPosition;
            signNum += 1;
        }
        findSign(str, signPosition, signNum, currentPosition + 1);
    }
    else
    {
        signPosition[signNum] = currentPosition;
    }
}

void findSign(const char str[], int signPosition[], int& signNum)
{
    if(str[0] == '-')
    {
        signPosition[0] = 0;
    }
    else
    {
        signPosition[0] = -1;
    }
    signNum += 1;    
    findSign(str, signPosition, signNum, 1);
}


int evaluate(const char str[], int signPosition[], int signNum, int currentSignNum, int result)
{
    if(currentSignNum == signNum)
    {
        return result;
    }
    else
    {
        int currentSignPosition = signPosition[currentSignNum];
        if(str[currentSignPosition] == '+')
        {
            result += getIntValue(str, currentSignPosition + 1, signPosition[currentSignNum + 1] - 1);
        }
        else if(str[currentSignPosition] == '-')
        {
            result -= getIntValue(str, currentSignPosition + 1, signPosition[currentSignNum + 1] - 1);
        }
        evaluate(str, signPosition, signNum, currentSignNum + 1, result);
    }
}

int evaluate(const char str[])
{
    int signNum = 0;
    int signPosition[ARRAY_MAX_SIZE];
    findSign(str, signPosition, signNum);

    
    int result = 0;
    if(signPosition[0] == -1)
    {
        result += getIntValue(str, 0, signPosition[1] - 1);
    }
    else
    {
        result -= getIntValue(str, 1, signPosition[1] - 1);
    }


    return evaluate(str, signPosition, signNum, 1, result);  //change this line if you want
}




//***** Only write your code above this line, remember that NO loop is allowed! *****


int main()
{
    /***
    int result[ARRAY_MAX_SIZE];
    int resultSize = 0;
    int input[] = {1, 2};
    int size = 2;
    int target = 1;
    solve(input, size, target, result, resultSize);
    printArray(result, resultSize);
    ***/

    int testCase;
    cout << "Hi, recursion master! Which test case do you want to run?" << endl;
    cin >> testCase;

    cout << endl << "Test case " << testCase << " output:" << endl;
    cout << "===================================" << endl;

    if(testCase == 0) //this test case is used to show you how printArray works; it is NOT used to grade your work and it is NOT on ZINC; no mark is allocated to this; try it on your own computer if you want
    {
        int array1[] = {1, 2, 3};
        printArray(array1, 3);
        int array2[] = {1, 2, 3, -4};
        printArray(array2, 4);
        int array3[] = {-8, 2, 1, -4};
        printArray(array3, 4);
        int array4[] = {99};
        printArray(array4, 1);
        int array5[] = {-1199};
        printArray(array5, 1);
    }
    
    else if(testCase == 1) //test arraySum
    {
        int array[] = {1, 2, 3};
        cout << arraySum(array, 3) << endl;
    }
    else if(testCase == 2) //test arraySum
    {
        int array[] = {-1, -234, 33, 5};
        cout << arraySum(array, 4) << endl;
    }

    else if(testCase == 3) //test solve
    {
        int input[] = {1, 2, 3, 4};
        int size = 4;
        int target = 2;
        int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
        int resultSize = 0;
        if(solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if(testCase == 4) //test solve
    {
        int input[] = {1, 2, 3, 4};
        int size = 4;
        int target = -2;
        int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
        int resultSize = 0;
        if(solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if(testCase == 5) //test solve
    {
        int input[] = {1, 2, 3, 4};
        int size = 4;
        int target = -9;
        int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
        int resultSize = 0;
        if(solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if(testCase == 6) //test solve
    {
        int input[] = {8, 13, 1, 3, 5, 9};
        int size = 6;
        int target = 9;
        int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
        int resultSize = 0;
        if(solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if(testCase == 7) //test solve
    {
        int input[] = {88, 13, 1, 3, 5, 9};
        int size = 6;
        int target = 9;
        int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
        int resultSize = 0;
        if(solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if(testCase == 8) //test solve
    {
        int input[] = {888, 13333, 20000, 1, 99, 3, 5, 9, 33, 44, 55, 100};
        int size = 12;
        int target = -165;
        int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
        int resultSize = 0;
        if(solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }

    else if(testCase == 9) //test printString
    {
        printString("1+1-2+1234");
    }
    else if(testCase == 10) //test printString
    {
        printString("Wow this assignment is so much fun!!!");
    }

    else if(testCase == 11) //test getIntValue
    {
        char str[] = "567";
        cout << getIntValue(str, 0, 2) << endl;
    }
    else if(testCase == 12) //test getIntValue
    {
        char str[] = "567";
        cout << getIntValue(str, 0, 1) << endl;
    }
    else if(testCase == 13) //test getIntValue
    {
        char str[] = "567";
        cout << getIntValue(str, 0, 0) << endl;
    }
    else if(testCase == 14) //test getIntValue
    {
        char str[] = "abc567abc";
        cout << getIntValue(str, 4, 5) << endl;
    }
    
    else if(testCase == 15) //test evaluate
    {
        cout << evaluate("172") << endl;
    }
    else if(testCase == 16) //test evaluate
    {
        cout << evaluate("3+2") << endl;
    }
    else if(testCase == 17) //test evaluate
    {
        cout << evaluate("1+2-4") << endl;
    }
    else if(testCase == 18) //test evaluate
    {
        cout << evaluate("11+21-43") << endl;
    }
    else if(testCase == 19) //test evaluate
    {
        cout << evaluate("11+21-43+888") << endl;
    }
    else if(testCase == 20) //test evaluate
    {
        cout << evaluate("-21") << endl;
    }
   
    cout << "===================================" << endl;

    return 0;
}


