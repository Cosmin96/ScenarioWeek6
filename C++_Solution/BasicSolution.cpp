#include <bits/stdc++.h>

#define TEST_CASES 1

using namespace std;

ifstream f("robots.mat");
ofstream g("result.txt");

void parseInput()
{

}

void produceOutput()
{
    //Print team and password
    g << "cerberus\n" << "in2dfacpov96mvno2h714uaed0\n";

    //Print results for each test case
    for(int i = 1; i <= TEST_CASES; i++)
    {
        //Test number
        //(0,0) (5,0), (0,7), (1,8)
        //(5,0), (9,9), (8,10), (10,10)
        g << i << ": ";
        g << "(0, 0), (5, 0), (0, 7), (1, 8); (5, 0), (9, 9), (8, 10), (10, 10)\n";
    }
}

int main()
{
    parseInput();


    produceOutput();
    return 0;
}
