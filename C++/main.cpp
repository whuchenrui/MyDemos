
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <getopt.h>
#include <iomanip>


using namespace std;


struct VertexMSP
{
    int index;
    int xCoordinate;
    int yCoordinate;
    int parent;
    float distance;
    bool wild;       //if is wild
    bool border;     //on border

    VertexMSP(int in, int xAxis, int yAxis, int pare, float dist, bool wi, bool bor):
            index(in), xCoordinate(xAxis), yCoordinate(yAxis), parent(pare), distance(dist), wild(wi), border(bor) {}
};

// MST --------------------------------------------------------------------------------------------------------------------------

float calcDistance(const VertexMSP &a, const VertexMSP &b)
{
    return (pow((a.xCoordinate-b.xCoordinate), 2) + pow((a.yCoordinate-b.yCoordinate),2));
}

void print_mst(const float weight, const vector<VertexMSP> &zooVertices)
{
    cout << weight << endl;
    cout << std::setprecision(2);
    cout << std::fixed;
    cout << endl;

    for (int i = 1; i<zooVertices.size(); i++)
    {
        cout << zooVertices[i].distance << " ";
        if (zooVertices[i].index < zooVertices[i].parent)
            cout << zooVertices[i].index << " " << zooVertices[i].parent << endl;
        else
            cout << zooVertices[i].parent << " " << zooVertices[i].index << endl;
    }
}


bool reachable(const VertexMSP &a, const VertexMSP &b){
    if(a.wild == true && b.wild == false && b.border == false)
        return false;
    if(a.wild == false && a.border == false && b.wild == true)
        return false;
    return true;
}

void mstPath(vector<VertexMSP> &zooVertices)
{
    float minDistance = 0.0;
    float minIndex = 0.0;
    float currentDistance = 0.0;
    zooVertices[0].distance = 0.0;

    for(int i = 0; i<zooVertices.size()-1; i++)
    {
        minDistance = MAXFLOAT;
        for (int j = i+1; j<zooVertices.size(); j++)  //check
        {
            if(reachable(zooVertices[i], zooVertices[j])) {
                currentDistance = calcDistance(zooVertices[i], zooVertices[j]);
                if ( currentDistance < zooVertices[j].distance)
                {
                    zooVertices[j].distance = currentDistance;
                    zooVertices[j].parent = zooVertices[i].index;
                }
            }

            if (minDistance > zooVertices[j].distance)
            {
                minDistance = zooVertices[j].distance;
                minIndex = j;
            }
        } //inner for loop
//        if(minDistance != MAXFLOAT) {
            zooVertices[minIndex].distance = minDistance;
            swap(zooVertices[i+1], zooVertices[minIndex]);
//        }
    } //outter for loop

    float weight = 0;
    for (int i = 0; i<zooVertices.size(); i++)
        weight += sqrt(zooVertices[i].distance);
    print_mst(weight, zooVertices);
}

//---------------------------------------------------------------------------------------------------------------------
int main(int argc, char * argv[])
{
    fstream readFile("sample-ab.txt");
    cin.rdbuf(readFile.rdbuf());
    int numberCage = 0;
    cin >> numberCage;

    VertexMSP vertex(0,0,0,-1,INT_MAX,false,false);
    vector<VertexMSP> zooVertices((size_t)numberCage,vertex);
    int index = 0;

    while (cin >> zooVertices[index].xCoordinate >> zooVertices[index].yCoordinate)
    {
        zooVertices[index].index = index;
        if (zooVertices[index].xCoordinate<0 && zooVertices[index].yCoordinate<0)
            zooVertices[index].wild = true;
        else if ((zooVertices[index].xCoordinate<=0 && zooVertices[index].yCoordinate==0) ||
                 (zooVertices[index].xCoordinate==0 && zooVertices[index].yCoordinate<=0))
            zooVertices[index].border = true;
        index++;
    }

    mstPath(zooVertices);
    return 0;
}
