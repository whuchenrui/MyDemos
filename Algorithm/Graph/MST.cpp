/*
最小生成树在图中找一个edge子集合，满足vertice coverage并且weight权重和最小。最终结果是无环强连通图。

常见的解决方法有
1: Prim's algorithm, O(e log v) 适用于edge非常多的情况。邻接矩阵:O(n^2) 邻接表+binary heap:O(e log v), 
2: Kruskal's algorithm, O(e log e) time，适用于vertex较多而edge不多的情况。

- 记Graph中有v个顶点, V为点集，e个边，E为边集。 
**Prim's algorithm**
* 初始化：Vnew = {x}，x为集合V中的任一节点，Enew = {}, 为空；
* 重复下列操作，直到Vnew = V：
    * 在E中选取权值最小的边<u, v>，其中u为集合Vnew中的元素，而v不在Vnew集合当中，并且v∈V（random when tie exists)
    * 将v加入集合Vnew中，将<u, v>边加入集合Enew中；

**Kruskal's algorithm**
* 新建图Graphnew，Graphnew中拥有与原图中相同的v个顶点，但没有边
* 将原图Graph中所有e个边按权值从小到大排序
* 循环：从权值最小的边开始遍历每条边 直至图Graph中所有的节点都在同一个连通分量中
    *  if 这条边连接的两个节点于图Graphnew中不在同一个连通分量中
    *  添加这条边到图Graphnew中
 *
 * Reference: Personal note
 */

/*
 * Prim Algorithm Implementation
 */
struct VertexMST
{
    int idx;
    int x;
    int y;
    int parent;
    float distance;
    VertexMST(int in, int xAxis, int yAxis, int p, float dist): 
        idx(in), x(xAxis), y(yAxis), parent(p), distance(dist) {}
};

float calcDistance(const VertexMST &a, const VertexMST &b) {
    return (pow((a.x-b.x), 2) + pow((a.y-b.y), 2));
}

bool reachable(const VertexMST &a, const VertexMST &b){
    // Add constraints here, to remove invalid edges.
    // In 281 P4 Travelling Salesman problem, the constraint is that cages in wild area 
    // cannot connect outside directly, just remove those edges
    return true;
}

void printMSTPath(const double weight, const vector<VertexMSP> &zooVertices) {
    cout << std::setprecision(2) << std::showpoint << std::fixed;
    cout << weight << endl;
    for (int i = 1; i<(int)zooVertices.size(); i++) 
    {
        if (zooVertices[i].index < zooVertices[i].parent)
            cout << zooVertices[i].index << " " << zooVertices[i].parent << endl;
        else
            cout << zooVertices[i].parent << " " << zooVertices[i].index << endl;
    }
}

void mstPath(vector<VertexMST> &zooVertices) {
    float minDistance = MAXFLOAT;
    float minIndex = 0.0;
    float currentDistance = 0.0;
    zooVertices[0].distance = 0.0;

    for(int i = 0; i < zooVertices.size()-1; i++)
    {
        minDistance = MAXFLOAT;
        for (int j = i+1; j<zooVertices.size(); j++)
        {
            // if(reachable(zooVertices[i], zooVertices[j])) {
                currentDistance = calcDistance(zooVertices[i], zooVertices[j]);
                if ( currentDistance < zooVertices[j].distance)
                {
                    zooVertices[j].distance = currentDistance;
                    zooVertices[j].parent = zooVertices[i].index;
                }
            // }
            if (minDistance > zooVertices[j].distance)
            {
                minDistance = zooVertices[j].distance;
                minIndex = j;
            }
        }
        zooVertices[minIndex].distance = minDistance;
        swap(zooVertices[i+1], zooVertices[minIndex]);
    } 

    float weight = 0;
    for (int i = 0; i<zooVertices.size(); i++)
        weight += sqrt(zooVertices[i].distance);
    print_mst(weight, zooVertices);
}
/* 
-----------------------------------------------------------------------------------
*/
int main(int argc, char * argv[])
{
    fstream readFile("sample-ab.txt");
    cin.rdbuf(readFile.rdbuf());
    int numberCage = 0;
    cin >> numberCage;

    VertexMST vertex(0, 0, 0, 0, MAXFLOAT);
    vector<VertexMST> zooVertices((size_t)numberCage,vertex);
    int index = 0;

    while (cin >> zooVertices[index].xCoordinate >> zooVertices[index].yCoordinate)
    {
        zooVertices[index].index = index;
        index++;
    }
    mstPath(zooVertices);
    return 0;
}


/*
 * Kruskal Algorithm Implementation
 */