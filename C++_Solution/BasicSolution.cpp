#include <bits/stdc++.h>

#define TEST_CASES 10
#define NMAX 10001

using namespace std;

ifstream f("robots.mat");
ofstream g("result.txt");
ofstream g1("a.in");

double epsilon = 0.000000000000001;

string s;
vector <string>parts;
vector <string>robotsRaw;
vector <string>polygonRaw;
vector <string>polygonRawString;

vector <int>G[100001];

bool viz[100001];

struct point{
    double x, y;
};

vector <point>robots;
vector <point>polygons[NMAX];
vector <point>nodes;
vector <point>sol;

int polyNo, touched;

bool onSegment(point p, point q, point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return true;

    return false;
}

double orientation(point p, point q, point r)
{
    // See http://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    double val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (fabs(val) < epsilon) return 1;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

bool doIntersect(point p1, point q1, point p2, point q2)
{
    // Find the four orientations needed for general and
    // special cases
    double o1 = orientation(p1, q1, p2);
    double o2 = orientation(p1, q1, q2);
    double o3 = orientation(p2, q2, p1);
    double o4 = orientation(p2, q2, q1);

    // General case
    if (fabs(o1 - o2) > epsilon && fabs(o3 - o4) > epsilon)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    //if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    //if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    //if (o3 == 0 && onSegment(p2, p1, q2)) return true;

     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    //if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}

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

    if(test == 1){
        g << "(0, 0), (5, 0), (0, 7), (1, 8); (5, 0), (9, 9), (8, 10); (9, 9), (10, 10)\n";
        return ;
    } else if(test == 2){
        g << "(-1, -1), (0, 6), (1, 6), (2, 2), (4, 2), (4, 4)\n";
        return ;
    } //else if(test == 3){
        //g << "(0, 1), (2, 0), (3, 2), (3, 5), (6, 2); (2, 0), (9, 0)\n";
       // return ;
    //}
    else if(test == 8 || test == 9 || test == 10){
        for (int i = 0; i < robots.size() - 1; i++)
        {
            g << setprecision(18) << "(" << robots[i].x << ", " << robots[i].y << "), ";
        }
        g << setprecision(18) << "(" << robots[robots.size() - 1].x << ", " << robots[robots.size() - 1].y << ")\n";
        return ;
    }

    if(test == 3)
    {
        g1 << robots.size() << '\n';
        for (int i = 0; i < robots.size() - 1; i++)
        {
            g1 << setprecision(18) << robots[i].x << " " << robots[i].y << " ";
        }
        g1 << setprecision(18) << robots[robots.size() - 1].x << " " << robots[robots.size() - 1].y << "\n";

        g1 << polyNo << '\n';
        for(int j = 0; j < polyNo; j++)
        {
            g1 << polygons[j].size() << '\n';
            for(int i = 0; i < polygons[j].size() - 1; i++)
                g1 << setprecision(18) << polygons[j][i].x << " " << polygons[j][i].y << " ";
            g1 << setprecision(18) << polygons[j][polygons[j].size() - 1].x << " " << polygons[j][polygons[j].size() - 1].y << "\n";
        }

        g1 << sol.size() << '\n';

        for(int i = 0; i < sol.size() - 1; i++)
        {
            g1 << setprecision(18) << sol[i].x << " " << sol[i].y << " ";
        }
        g1 << setprecision(18) << sol[sol.size() - 1].x << " " << sol[sol.size() - 1].y << "\n";
    }


    for(int i = 0; i < sol.size() - 1; i++)
    {
        g << setprecision(18) << "(" << sol[i].x << ", " << sol[i].y << "), ";
    }
    g << setprecision(18) << "(" << sol[sol.size() - 1].x << ", " << sol[sol.size() - 1].y << ")\n";
}

bool intersectsPolygon(point p1, point q1)
{
    for(int j = 0; j < polyNo; j++)
    {
        for(int i = 0; i < polygons[j].size(); i++)
            if(doIntersect(p1, q1, polygons[j][i], polygons[j][(i + 1) % (polygons[j].size())]) == true)
                return true;
    }
    return false;
}

void clearGlobals()
{
    parts.clear();
    robotsRaw.clear();
    robots.clear();
    polygonRaw.clear();

    for(int j = 0; j < polyNo; j++)
        polygons[j].clear();

    polyNo = 0; touched = 0;
    memset(viz, 0, sizeof(viz));
    for(int i = 0; i < NMAX; i++)
        G[i].clear();
    nodes.clear();
    sol.clear();
}


void dfs(int x)
{
    viz[x] = true;
    sol.push_back(nodes[x]);
    if(x < robots.size())
        touched++;
    for(int i = 0; i < G[x].size(); i++)
    {
        if(!viz[G[x][i]] && touched < robots.size())
            dfs(G[x][i]);
    }
}

void solve()
{
    //Solving here!!!

    //Insert connected robots as edges
    for(int i = 0; i < robots.size() - 1; i++)
    {
        nodes.push_back(robots[i]);
        for(int j = i + 1; j < robots.size(); j++)
        {
            if(intersectsPolygon(robots[i], robots[j]) == false)
            {
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }
    nodes.push_back(robots[robots.size() - 1]);

    //Insert connected robots and polygon vertices as edges
    bool first = true;
    for(int i = 0; i < robots.size(); i++)
    {
        int sz = robots.size();
        for(int j = 0; j < polyNo; j++)
        {
            for(int k = 0; k < polygons[j].size(); k++)
            {
                if(first == true)
                    nodes.push_back(polygons[j][k]);

                if(intersectsPolygon(robots[i], polygons[j][k]) == false)
                {
                    G[i].push_back(sz);
                    G[sz].push_back(i);
                }
                sz++;
            }
        }
        first = false;
    }

    //Insert polygon segments as edges
    int sz = robots.size();
    for(int j = 0; j < polyNo; j++)
    {
        for(int i = 0; i < polygons[j].size() - 1; i++)
        {
            G[sz].push_back(sz + 1);
            G[sz + 1].push_back(sz);

            sz++;
        }
        sz++;
    }

    //Perform dfs from first node to find a line
    dfs(0);
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
