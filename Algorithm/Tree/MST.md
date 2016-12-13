# Min Spanning Tree

A minimum spanning tree (MST) is a **subset of the edges** of a connected, edge-weighted undirected graph that connects all the vertices together, without any cycles and with the minimum possible total edge weight.
最小生成树在图中找一个edge子集合，满足vertice coverage并且weight权重和最小。最终结果是**无环**强连通图。

常见的解决方法有

* Prim's algorithm, O(e* *log *v*) 适用于**edge**非常多的情况。邻接矩阵:O(n^2) 邻接表 + binary heap:O(e log *v*), 
* Kruskal's algorithm, O(*e* log* e*) time，适用于**vertex**较多而edge不多的情况。

**Prim's algorithm**

* 初始化：Vnew = {x}，x为集合V中的任一节点，Enew = {}, 为空；
* 重复下列操作，直到Vnew = V：
    * 在E中选取权值最小的边<u, v>，其中u为集合Vnew中的元素，而v不在Vnew集合当中，并且v∈V（如果存在有多条满足前述条件即具有相同权值的边，则可任意选取其中之一)
    * 将v加入集合Vnew中，将<u, v>边加入集合Enew中；

反证法：假设prim生成的不是最小生成树

* 设prim生成的树为G0
* 假设存在Gmin使得cost(Gmin) < cost(G0) 则在Gmin中存在<u,v>不属于G0
* 将<u,v>加入G0中可得一个环，且<u,v>不是该环的最长边(这是因为<u,v>∈Gmin)
* 这与prim每次生成最短边矛盾
* 故假设不成立，命题得证


**Kruskal's algorithm**

* 记Graph中有v个顶点，e个边
* 新建图Graphnew，Graphnew中拥有与原图中相同的e个顶点，但没有边
* 将原图Graph中所有e个边按权值从小到大排序
* 循环：从权值最小的边开始遍历每条边 直至图Graph中所有的节点都在同一个连通分量中
    *  if 这条边连接的两个节点于图Graphnew中不在同一个连通分量中
    *  添加这条边到图Graphnew中

证明，使用数学归纳法

## Prim's algorithm Implementation

注意，Prime在实现的时候，需要从所有已经遍历过的点出发，找到其中最优的edge加入已有的集合中。
idx:  node id
parent: 连接edge的 node id
distance: edge长度,** default is max float.**
时间复杂度: O(n^2)，但不包含判断edge是否合法所花的时间。

分析:
1: distance记录了距离当前node最近的node，所以内层j循环时，需要时刻更新。
2: 同时维护minIndex，记录这些边里面最小的边。在内层j循环结束时，做一次swap操作，改node已被加入集合中。
3: 最终的结果vector是一个path，但是MST需要根据parent和distance来找。
4: 用swap的方法，非常适合DFS来找greedy path.    [Graph 图](https://quip.com/1B0pAaKaGBOt) 

```
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
    // add constraints here, to remove invalid edges
    // in 281 Project 4, the constraint is that cages in wild area cannot connect 
    // outside directly, just remove those edges.
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
```

## **Kruskal's Implementation**

Sort + Union find
Time: O(eloge + mlogv)   e edge, v vertex, m operations on union find

```
//Amazon OA2, Kruskal's algorithm + union find
//edge: e, vertice: v, as e is at most V^2, thus loge = 2logv
//Time: O(eloge) 
public static class Connection{
    String node1;
    String node2;
    int cost;
    public Connection(String a, String b, int c){
        node1 = a;
        node2 = b;
        cost = c;
    }
}

private static int unionNum;
public static ArrayList<Connection> getLowCost(ArrayList<Connection> connections) {
    ArrayList<Connection> res = new ArrayList<>();
    if(connections==null || connections.size()==0)
        return res;
    Map<String, Integer> map = new HashMap<>();
    Collections.sort(connections, new Comparator<Connection>(){
       @Override
       public int compare(Connection c1, Connection c2){
           return c1.cost - c2.cost;
       }
    });

    unionNum = 0;
    for(Connection c : connections){
        String a = c.node1;
        String b = c.node2;
        if(union(map, a, b)){
            res.add(c);
        }
    }
    //check result
    String find = connections.get(0).node1;
    int union = map.get(find);
    for(String str : map.keySet()){
        if(map.get(str) != union)
            return new ArrayList<>();
    }

    //sort based on city name
    Collections.sort(res, new Comparator<Connection>(){
        @Override
        public int compare(Connection c1, Connection c2){
            if(c1.node1.equals(c2.node1)){
                return c1.node2.compareTo(c2.node2);
            }
            return c1.node1.compareTo(c2.node1);
        }
    });
    
    return res;
}

private static boolean union(Map<String, Integer> map, String a, String b){
    if(!map.containsKey(a) && !map.containsKey(b)){
        map.put(a, unionNum);
        map.put(b, unionNum);
        unionNum++;
        return true;
    }
    if(map.containsKey(a) && !map.containsKey(b)){
        int au = map.get(a);
        map.put(b, au);
        return true;
    }
    if(!map.containsKey(a) && map.containsKey(b)){
        int bu = map.get(b);
        map.put(a, bu);
        return true;
    }
    int au = map.get(a);
    int bu = map.get(b);
    if(au == bu) return false;
    for(String s : map.keySet()){
        if(map.get(s) == bu)
            map.put(s, au);
    }
    return true;
}
```

## Reference

* http://www.cnblogs.com/biyeymyhjob/archive/2012/07/30/2615542.html (Prim + K)


