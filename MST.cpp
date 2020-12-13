#include <iostream>
#include<bits/stdc++.h>
#include <queue>
#include <vector>

using namespace std;

//Declarations
const int MAX_SIZE = 500;
#define temp pair<int, int>
#define pb(x) push_back(x)

int arr[MAX_SIZE];

pair <long long, pair<int, int> > p[MAX_SIZE];
vector<pair<int,int>> G[MAX_SIZE];

//functions
void initialise();
int findParent(int x);
void unionXY(int x, int y);
long long kruskal(pair<long long, pair<int, int> > p[], int e, int n);
void dijkstra(int n, int e, int x, int y, int weight);

//struct to compare
struct compare
{
  bool operator()(const pair<int,int> &x, const pair<int,int> &y)
  {
    return (x.second > y.second);
  }
};

 priority_queue<pair<int,int>, vector<pair<int,int> >,compare> Q;

void initialise()
{
  for(int i = 0;i < MAX_SIZE;++i)
    arr[i] = i;
}

int findParent(int x)
{
  while(arr[x] != x)
  {
    arr[x] = arr[arr[x]];
    x = arr[x];
  }
  return x;
}

//Function for union
void unionXY(int x, int y)
{
  int a = findParent(x);
  int b = findParent(y);
  arr[a] = arr[b];
}

//function for kruskal
long long kruskal(pair<long long, pair<int, int> > p[], int e, int n)
{
  int x, y;
  int cost;
  int minCost = 0;

  sort(p, p + e);
  for(int i = 0;i < e;++i)
  {
    assert(e != n - 1);
    x = p[i].second.first;
    y = p[i].second.second;
    cost = p[i].first;
    if(findParent(x) != findParent(y))
    {
      minCost += cost;
      cout<<x<<" --> "<<y<<" : "<<p[i].first<<endl;//print the edges contain in spanning tree
      unionXY(x, y);
    }
  }
  return minCost;
}

// Function for Dijikstra
void dijkstra(int n, int e, int x, int y, int weight)
{
  int DISTANCE[MAX_SIZE];
  bool VISITED[MAX_SIZE];
  int start_node = 1;

  for (int i = 1; i <= n; i++)
    DISTANCE[i] = INT_MAX;

  DISTANCE[start_node] = 0;
  Q.push(pair<int,int>(start_node, 0));

  while (!Q.empty())
  {
    x = Q.top().first;
    Q.pop();

    for (int i = 0; i < G[x].size(); i++)
    {
      if(n > 0)
        assert(e = n - 1);

      y = G[x][i].first;
      weight = G[x][i].second;
      if (!VISITED[y] && DISTANCE[x] + weight < DISTANCE[y])
      {
        DISTANCE[y] = DISTANCE[x] + weight;
        Q.push(pair<int,int>(y, DISTANCE[y]));
      }
    }
    assert(e = n - 1);
    VISITED[x] = 1; // done with u
  }

 for (int i = 1; i <= n; i++)
   cout << i << " --> " << DISTANCE[i] << endl;
}

int main()
{
  int minCost;
  int x;
  int y;
  int weight;

  initialise();

  srand(time(NULL));

  int n = 1 + rand()% 20;
  int e = 1 + rand()% 30;

  cout << endl;
  cout << n << " " << e << endl;

  //random generation for nodes and edges
  for(int i = 0; i < e; i++)
  {
    x = rand() % n + 1;
    y = rand() % n + 1;
    weight = rand() % 30 + 1;

    G[x].pb(temp(y, weight));
    G[y].pb(temp(x, weight));
    cout << x << "--> "<< y << " : "<< weight << endl;
    p[i] = make_pair(weight, make_pair(x, y));
  }

  cout << endl;
  cout << "******Results for kruskal******" << endl;

  minCost = kruskal(p, e, n);
  cout <<"Minimum cost is "<< minCost << endl;

  cout << endl;
  cout << "******Results for Dijikstra******" << endl;
  dijkstra(n, e, x, y, weight);

  return 0;
 }
