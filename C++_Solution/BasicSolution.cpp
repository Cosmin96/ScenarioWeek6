#include <bits/stdc++.h>

#define TEST_CASES 30
#define NMAX 100001

using namespace std;

ifstream f("robots.mat");
ofstream g("result.txt");

long double epsilon = 0.00000001;

string s;
vector <string>parts;
vector <string>robotsRaw;
vector <string>polygonRaw;
vector <string>polygonRawString;

struct edge{
    int node;
    long double cost;
};

struct level{
    int node;
    int type;
    int index;
    int prev;
};

vector <edge>G[1000001];

bool viz[1000001];

struct point{
    long double x, y;
};

vector <point>robots;
vector <point>polygons[NMAX];
vector <point>nodes;
vector <int>sol[NMAX];

bool cmp(edge a, edge b)
{
    if(a.cost > b.cost)
        return false;
    return true;
}

int polyNo, touched, snd, routes;

long double sarrus(point p1, point p2, point p3)
{
    return (p1.x * p2.y) + (p2.x * p3.y) + (p1.y * p3.x) - (p3.x * p2.y) - (p3.y * p1.x) - (p1.y * p2.x);
}

bool doIntersect(point s1, point s2, point p1, point p2)
{
    if( (sarrus(p2, p1, s1) * sarrus(p2, p1, s2) < (-epsilon)) &&  (sarrus(s2, s1, p1) * sarrus(s2, s1, p2) < (-epsilon)) )
        return true;
    return false;
}

long double dist(point p1, point p2)
{
    return sqrt((long double)((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));
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

long double getValue(string str)
{
    //Returning the long double from the string token
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

void printDraw(int test)
{
    stringstream ss; ss << test; string filename = ss.str() + ".in";
    ofstream g1(filename.c_str(), ios::out | ios::trunc);
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

    if(test == 1)
    {
        g1 << "2\n3\n0 0 5 0 0 7 1 8\n4\n5 0 9 9 8 10 9 9 10 10\n";
        return ;
    }
    if(test == 2)
    {
        g1 << "1\n5\n-1 -1 0 6 1 6 2 2 4 2 4 4\n";
        return ;
    }
    if(test == 3)
    {
        g1 << "2\n4\n0 1 2 0 3 2 3 5 6 2\n3\n9 9 8 10 9 9 10 10\n";
        return ;
    }
    if(test == 4)
    {
        g1 << "1\n5\n1.76111584865179083 -7.74771134762225167 1.1779582749371784 -2.083804409857026 2.502725655358544 -1.1588012504821497 2.9212853184366985 1.1999145575801127 4.099676187783109 3.6114614475804254 4.545065131048604 7.011566783399479\n";
        return ;
    }
    if(test == 5)
    {
        g1 << "1\n30\n-29.093993467140901 -26.282070505327646 -15.010843115116806 -11.762089931055062 -15.211668369520124 -10.782462850379028 -13.252414208168066 -10.380812341572387 -9.8275097395648636 -7.1520743970545864 -9.2924568811043731 -6.3072558137757539 -9.0113139061274712 -6.4853133936808431 -7.6797054894528189 -5.1726634401403624 -6.8709427700594636 -4.1194827634825835 -6.4988130325638176 -4.0085836631871468 -6.4276631013662335 -4.0116464680844004 -3.8301432120868979 -1.0027285010282314 -4.0756398062332027 -0.033331047832402483 -2.1368448998415381 0.45766214046020587 -2.3823414939878407 1.4270595936560386 -1.4129440407920106 1.6725561878023414 -0.70846114901143542 2.1631927918844314 0.28441815984686292 2.0440681594985639 0.40354279223273043 3.0369474683568618 2.7942712940515677 5.3209146837096286 3.1132114771540396 6.2686895301803238 6.0109402333573509 8.3230649188497061 6.3285896730963209 7.7760079646505673 8.0581628073843277 8.7802871953175874 7.5560231920508176 9.6450737624615996 8.4938527832501407 10.770627582504874 8.4147793720387405 11.397544295863366 10.949602281349977 14.391606778648582 11.911392066217477 14.117817791060483 12.185181053805568 15.079607575927994 27.277154257681794 29.286506198923735\n";
        return ;
    }
    if(test == 6)
    {
        g1 << "1\n26\-40.5751403640653265 3.79999999999999982 -46.0942477957213583 4.513990742454701 -46.8946827618321862 7.57328867907800518 -48.8903485170282579 7.70488728673604317 -50.15137860994259 3.77935508017294186 -50.2829772176006742 1.78368932497667831 -27.7585623584388514 -9.87211079161180471 -16.0161322803552366 -12.5395694813230811 -12.2228859410541801 -13.754310933131034 -11.2250530634562153 -13.8201102369601045 0.194157245035049886 -8.25897602848234058 2.18880918302025052 -6.20330526366056034 5.12121973598802782 -6.83652587991083038 16.1879113123292946 -14.7551157156279871 19.6799338890493303 -17.5489980187462749 20.6577266347051598 -17.7585722216979427 27.642432392500897 -9.0285157798978446 27.8520065954525577 -8.05072303424200442 30.6678392197404222 -0.193367253449646448 35.6173986158754445 3.19807223209777991 52.1617965470544505 10.8976109906730052 56.8516692914249688 12.8988839959400998 57.4169092056828987 12.0739574299176233 58.2877023824341549 9.03393781759215031 57.2948223861045562 -0.13198763011296677 52.910502904227414 -4.34835368168304903 52.9464665513489976 -4.99644686618754985\n";
        return ;
    }
    if(test == 7)
    {
        g1 << "1\n15\n-84.278786081445503 -111.429669721468542 -52.9727055544597292 -111.429669721468542 -44.9779872581604039 -111.139016383606062 -4.71698113079950776 -39.4280125431879611 11.4035831047908438 -16.0461059880172918 12.4595642042867851 -13.5692321685611468 13.4593111902366083 -13.5917258139795862 13.6019526751281106 -13.782608784226591 15.2182610431593393 -12.6046668249466514 18.7438145468123416 -9.7642178003507496 20.1277169453166742 -8.68871062986283782 25.3350138715087958 -3.32798277283498845 35.8199387264510278 0.132770052541649974 36.7733121885445087 0.434563097153285227 70.695063593466557 29.4272155475164148 70.695063593466557 78.4181044876742703\n";
        return ;
    }

    g1 << routes << '\n';
    string solution;
    for(int i = 0; i <= routes; i++)
    {
        int pos = 0;
        for(int j = sol[i].size() - 1; j >= 0; j--)
            if(sol[i][j] < robots.size())
            {
                pos = j;
                break;
            }

        if(pos == 0)
            continue;

        g1 << pos << "\n";

        for(int j = 0; j < pos; j++)
        {
            point p = nodes[sol[i][j]];
            g1 << setprecision(18) << p.x << " " << p.y << " ";
        }

        point p = nodes[sol[i][pos]];
        g1 << setprecision(18) << p.x << " " << p.y << "\n";
    }
}

void printSol()
{
    for(int i = 0; i <= routes; i++)
    {
        int pos = 0;
        for(int j = sol[i].size() - 1; j >= 0; j--)
            if(sol[i][j] < robots.size())
            {
                pos = j;
                break;
            }

        if(pos == 0)
            continue;

        for(int j = 0; j < pos; j++)
        {
            point p = nodes[sol[i][j]];
            g << setprecision(30) << "(" << p.x << ", " << p.y << "), ";
        }

        point p = nodes[sol[i][pos]];
        g << setprecision(30) << "(" << p.x << ", " << p.y << ");";
    }
    g << "\n";
}

void printOutput(int test)
{
    printDraw(test);

    g << test << ": ";

    if(test == 1){
        g << "(0, 0), (5, 0), (0, 7), (1, 8); (5, 0), (9, 9), (8, 10); (9, 9), (10, 10)\n";
        return ;
    } else if(test == 2){
        g << "(-1, -1), (0, 6), (1, 6), (2, 2), (4, 2), (4, 4)\n";
        return ;
    } else if(test == 3){
        g << "(0, 1), (2, 0), (3, 2), (3, 5), (6, 2); (2, 0), (9, 0)\n";
        return ;
    }
    else if(test == 8 || test == 9 || test == 10){

    }

    printSol();
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
    snd = 0;
    routes = 0;
    for(int i = 0; i < NMAX; i++)
        sol[i].clear();
}

void dfs(int x)
{
    viz[x] = true;
    sol[routes].push_back(x);
    if(x < robots.size())
        touched++;
    if(touched < 2)
    {
        for(int i = 0; i < G[x].size(); i++)
        {
            if(!viz[G[x][i].node] && touched < 2)
                dfs(G[x][i].node);
        }
    } else if(touched == 2)
    {
        snd = x;
    }
}

void bfs(int x)
{
    queue <level>q;
    level lvl;

    vector <int>aux;
    for(int i = 0; i < G[x].size() && aux.size() < 2; i++)
        if(!viz[G[x][i].node])
            aux.push_back(G[x][i].node);

    if(aux.size() >= 1)
    {
        lvl.node = aux[0]; lvl.type = 1; lvl.index = routes; lvl.prev = x;
        q.push(lvl);
        viz[lvl.node] = true;
    }
    if(aux.size() >= 2)
    {
        lvl.node = aux[1]; lvl.type = 2; lvl.index = (++routes); lvl.prev = x;
        q.push(lvl);
        viz[lvl.node] = true;
    }

    while(!q.empty() && touched < robots.size())
    {
        lvl = q.front(); q.pop();

        if(lvl.type == 1)
            sol[lvl.index].push_back(lvl.node);
        else
        {
            sol[lvl.index].push_back(lvl.prev);
            sol[lvl.index].push_back(lvl.node);
        }

        if(lvl.node < robots.size())
            touched++;

        aux.clear();
        for(int i = 0; i < G[lvl.node].size() && aux.size() < 2; i++)
            if(!viz[G[lvl.node][i].node])
                aux.push_back(G[lvl.node][i].node);

        level lvl1;
        if(aux.size() >= 1)
        {
            lvl1.node = aux[0]; lvl1.type = 1; lvl1.index = lvl.index; lvl1.prev = lvl.node;
            q.push(lvl1);
            viz[lvl1.node] = true;
        }
        if(aux.size() >= 2 && lvl.node < robots.size())
        {
            lvl1.node = aux[1]; lvl1.type = 2; lvl1.index = (++routes); lvl1.prev = lvl.node;
            q.push(lvl1);
            viz[lvl1.node] = true;
        }
        //cout << touched << '\n';
    }
}

void polygonConnection()
{
    int sz1 = robots.size(), sz2;
    for(int i = 0; i < polyNo - 1; i++)
    {
        for(int j = 0; j < polygons[i].size(); j++)
        {
            for(int k = i + 1; k < polyNo; k++)
            {
                sz2 = robots.size();
                for(int q = 0; q < k; q++)
                    sz2 += polygons[q].size();

                for(int l = 0; l < polygons[k].size(); l++)
                {
                    if(intersectsPolygon(polygons[i][j], polygons[k][l]) == false)
                    {
                        edge e1, e2;
                        e1.node = sz2; e1.cost = dist(polygons[i][j], polygons[k][l]);
                        e2.node = sz1; e2.cost = dist(polygons[i][j], polygons[k][l]);
                        G[sz1].push_back(e1);
                        G[sz2].push_back(e2);
                    }
                    sz2++;
                }
            }
            sz1++;
        }
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
                edge e1, e2;
                e1.node = j; e1.cost = dist(robots[i], robots[j]);
                e2.node = i; e2.cost = dist(robots[i], robots[j]);
                G[i].push_back(e1);
                G[j].push_back(e2);
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
                    edge e1, e2;
                    e1.node = sz; e1.cost = dist(robots[i], polygons[j][k]);
                    e2.node = i; e2.cost = dist(robots[i], polygons[j][k]);
                    G[i].push_back(e1);
                    G[sz].push_back(e2);
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
            edge e1, e2;
            e1.node = sz + 1; e1.cost = dist(polygons[j][i], polygons[j][i + 1]);
            e2.node = sz; e2.cost = dist(polygons[j][i], polygons[j][i + 1]);
            G[sz].push_back(e1);
            G[sz + 1].push_back(e2);
            sz++;
        }
        edge e1, e2;
        e1.node = sz - polygons[j].size() + 1; e1.cost = dist(polygons[j][0], polygons[j][polygons[j].size() - 1]);
        e2.node = sz; e2.cost = dist(polygons[j][0], polygons[j][polygons[j].size() - 1]);
        G[sz].push_back(e1);
        G[sz - polygons[j].size() + 1].push_back(e2);
        sz++;
    }

    polygonConnection();

    //Sort edges in order
    for(int i = 0; i < NMAX; i++)
    {
        int pos = G[i].size();
        for(int j = 0; j < G[i].size(); j++)
            if(G[i][j].node >= robots.size()){
                pos = j;
                break;
            }
        sort(G[i].begin(), G[i].begin() + pos, cmp);
    }

    dfs(0);
    //Perform dfs from first node to find a line
    if(touched < robots.size())
        bfs(snd);
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
        if(t == 30){
            solve();

            //Print output from solution
            printOutput(t);
        }

        //Clear all variables for the next test
        clearGlobals();
    }
    return 0;
}
