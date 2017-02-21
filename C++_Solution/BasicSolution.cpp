#include <bits/stdc++.h>

#define TEST_CASES 30
#define NMAX 10001

using namespace std;

ifstream f("robots.mat");
ofstream g("result.txt");

string s;
vector <string>parts;
vector <string>robotsRaw;
vector <string>polygonRaw;
vector <string>polygonRawString;

struct point{
    double x, y;
};

vector <point>robots;
vector <point>polygons[NMAX];

int polyNo;

vector<string> spliting(string str, char delim) {
    vector<string> elems;
    int lastPos = 0;
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == delim)
        {
            elems.push_back(str.substr(lastPos, i - lastPos));
            lastPos = i + 1;
        }
    }
    if(lastPos < str.length())
        elems.push_back(str.substr(lastPos, str.length()));
    return elems;
}

double getValue(string str)
{
    //Returning the double from the string token
    int startPos = -1, endPos = -1;
    for(int i = 0; i < str.length(); i++)
    {
        //Check for digits and mark the range of the number
        if((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
        {
            //Mark the startPos of the number
            if(startPos == -1)
                startPos = i;
        }
        else if(str[i] != '.')
        {
            //Mark the endPos
            if(startPos != -1)
                endPos = i;
        }
    }

    if(endPos == -1)
        endPos = str.length();
    //Move to an auxiliary char array to apply atof and get the number
    string temp = str.substr(startPos, endPos - startPos);
    int k = 0; char aux[temp.length() + 1];
    for(int i = 0; i < temp.length(); i++)
    {
        aux[k++] = temp[i];
    }

    //return the result
    aux[k] = '\0';
    return atof(aux);
}

void parseInput(int test)
{
    getline(f, s);

    //get rid of test case number
    if(test > 9)
        s = s.substr(4, s.length() - 4);
    else
        s = s.substr(3, s.length() - 3);

    //Split in robots and obstacles
    parts = spliting(s, '#');

    //Split robots
    robotsRaw = spliting(parts[0], ',');

    //Get robots as points
    for(int i = 0; i < robotsRaw.size() - 1; i += 2)
    {
        point p;
        p.x = getValue(robotsRaw[i]);
        p.y = getValue(robotsRaw[i + 1]);
        robots.push_back(p);
    }

    if(parts.size() > 1){
        //Get polygons
        polygonRaw = spliting(parts[1], ';');
        polyNo = polygonRaw.size();
        for(int i = 0; i < polygonRaw.size(); i++)
        {
            polygonRawString = spliting(polygonRaw[i], ',');
            //Get polygon as points
            for(int j = 0; j < polygonRawString.size() - 1; j += 2)
            {
                point p;
                p.x = getValue(polygonRawString[j]);
                p.y = getValue(polygonRawString[j + 1]);
                polygons[i].push_back(p);
            }
            polygonRawString.clear();
        }
    }


    //Split robots and obstacles

}

void printHeader()
{
    //Print team and password
    g << "cerberus\n" << "in2dfacpov96mvno2h714uaed0\n";
}

void printOutput(int test)
{
    g << test << ": ";
    g << "(0, 0), (5, 0), (0, 7), (1, 8); (5, 0), (9, 9), (8, 10); (8, 10), (10, 10)\n";

    /*for(int j = 0; j < polyNo; j++)
    {
        g << "{ " ;
        for(int i = 0; i < polygons[j].size(); i++)
            g << setprecision(15) << "[" << polygons[j][i].x << "," << polygons[j][i].y << "], ";
        g << " }" << '\n';
    }
    g<< '\n';*/
}

void clearGlobals()
{
    parts.clear();
    robotsRaw.clear();
    robots.clear();
    polygonRaw.clear();

    for(int j = 0; j < polyNo; j++)
        polygons[j].clear();

    polyNo = 0;
}

void solve()
{
    //Solving here!!!
}

int main()
{
    //Print team details
    printHeader();

    //Iterate the test cases
    for(int t = 1; t <= TEST_CASES; t++)
    {
        //Parse input and put in graph
        parseInput(t);

        //Generate solution
        solve();

        //Print output from solution
        printOutput(t);

        //Clear all variables for the next test
        clearGlobals();
    }
    return 0;
}
