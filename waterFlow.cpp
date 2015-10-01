#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <list>
#include <map>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;

// Structure to represent a city
struct Node
{
    string sink;
    int pipelength;
    int totalOffPeriods;
    set<int> RangeOffPeriods;
};

struct MyStruct
{
    string sink;
    int pipelength;
    int totalOffPeriods;
    set<int> RangeOffPeriods;

    MyStruct(const string& s, int p, int t, set<int> R) : sink(s), pipelength(p), totalOffPeriods(t), RangeOffPeriods(R) {}
};

//To sort on the basis of pipe length
struct less_than_key
{
    inline bool operator() (const MyStruct& struct1, const MyStruct& struct2)
    {
        return (struct1.pipelength < struct2.pipelength);
    }
};

//To sort on the basis of the node name
struct less_than_key2
{
    inline bool operator() (const MyStruct& struct1, const MyStruct& struct2)
    {
        return (struct1.sink < struct2.sink);
    }
};

//To split a string based on the delimiter
vector<string> split(string str, char delimiter)
{
  vector<string> internal;
  stringstream ss(str);
  string tok;

  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}

//To check whether the node reached is goal or not
bool CheckForGoalState(string s, vector<string> EndingNodes)
{
    for(int i=0;i!= EndingNodes.size();i++)
    {
        if(EndingNodes[i] == s)
            return 1;
    }
    return 0;
}

//To find the goal node reached using Breadth First Search
void BFS(string StartingNode, vector<string> EndingNodes, vector<string> MiddleNodes, list<Node *> *adj, int StartTime, int pos, map<string,int> MapNodes,ofstream &outputFile)
{
    int level=0, value;
    bool *visited = new bool[pos];
    for(int i = 0; i < pos; i++)
        visited[i] = false;

    list<string> queue;

    value = MapNodes[StartingNode];
    visited[value] = true;
    queue.push_back(StartingNode);
    queue.push_back("##");

    bool IsItGoal = CheckForGoalState(StartingNode, EndingNodes);
            if(IsItGoal)
            {
                int finalPathTime=level+StartTime;
                if(finalPathTime>=24)
                    finalPathTime=finalPathTime%24;
                outputFile<<StartingNode<<" "<<finalPathTime;
                return;
            }

    list<Node *>::iterator i;
    int flag=0;
     while(queue.size()>1)
    {
        string s = queue.front();
        value = MapNodes[s];
        if(s == "##")
        {
            ++level;
            queue.pop_front();
            queue.push_back("##");
            continue;
        }
        queue.pop_front();
        vector<string> num;

        for(i = adj[value].begin(); i != adj[value].end(); ++i)
        {
            Node *q = *i;
            int value2 = MapNodes[q->sink];
            if(!visited[value2])
            {
                num.push_back(q->sink);
            }
        }
        sort(num.begin(),num.end());
        for(int n=0;n!= num.size();n++)
        {
            bool IsItGoal = CheckForGoalState(num[n], EndingNodes);
            if(IsItGoal)
            {
                int finalPathTime=level+StartTime+1;
                if(finalPathTime>=24)
                    finalPathTime=finalPathTime%24;
                outputFile<<num[n]<<" "<<finalPathTime;
                flag=1;
                return;
            }

            queue.push_back(num[n]);
            value = MapNodes[num[n]];
            visited[value] = true;
        }

    }
    if(flag == 0)
        outputFile<<"None";
}


//To find the goal node reached using Depth First Search
void DFS(string StartingNode, vector<string> EndingNodes, vector<string> MiddleNodes, list<Node *> *adj, int StartTime, int pos, map<string,int> MapNodes,ofstream &outputFile)
{
    int level=0, value;
    bool *visited = new bool[pos];
    for(int i = 0; i < pos; i++)
        visited[i] = false;

    list<string> queue;

    value = MapNodes[StartingNode];
    visited[value] = true;

    queue.push_front(StartingNode);

    list<Node *>::iterator i;
    int flag=0;
     while(!queue.empty())
    {
        string s = queue.front();
        if(s != "##")
        {
            bool IsItGoal = CheckForGoalState(s, EndingNodes);
            if(IsItGoal)
            {
                int finalPathTime=level+StartTime;
                if(finalPathTime>=24)
                    finalPathTime=finalPathTime%24;
                outputFile<<s<<" "<<finalPathTime;
                flag=1;
                return;
            }
        }
        if(s == "##")
        {
            level--;
            queue.pop_front();
            continue;
        }

        queue.pop_front();
        value = MapNodes[s];
        visited[value] = true;

        vector<string> num;
        for(i = adj[value].begin(); i != adj[value].end(); ++i)
        {
            Node *q = *i;
            int value2 = MapNodes[q->sink];
            if(!visited[value2])
            {
                num.push_back(q->sink);
            }
        }
        sort(num.rbegin(),num.rend());
        if(num.size()>0)
           {
               queue.push_front("##");
               level++;
           }

        for(int n=0;n!= num.size();n++)
        {
            queue.push_front(num[n]);
        }

    }
    if(flag == 0)
        outputFile<<"None";
}

//To find the goal node reached using Uniform Cost Search
void UCS(string StartingNode, vector<string> EndingNodes, vector<string> MiddleNodes, list<Node *> *adj, int StartTime, int pos, map<string,int> MapNodes,ofstream &outputFile)
{
    int level=0, value;
    bool *visited = new bool[pos];
    for(int i = 0; i < pos; i++)
        visited[i] = false;

    vector < MyStruct > open;

    set<int> blankset;

    value = MapNodes[StartingNode];
    open.push_back(MyStruct(StartingNode, StartTime, 0,blankset));
    int flag=0;
     while(open.size()>0)
     {
         MyStruct node = open[0];
         open.erase (open.begin() + 0);
         bool IsItGoal = CheckForGoalState(node.sink, EndingNodes);
         if(IsItGoal)
            {
                int finalPathTime=node.pipelength;
                if(finalPathTime>=24)
                    finalPathTime=finalPathTime%24;
                outputFile<<node.sink<<" "<<finalPathTime;
                flag=1;
                return;
            }

         vector < MyStruct > children;
         value = MapNodes[node.sink];

         list<Node *>::iterator it;
         for(it = adj[value].begin(); it != adj[value].end(); ++it)
        {
            Node *q = *it;
            int value2 = MapNodes[q->sink];
            children.push_back(MyStruct(q->sink, q->pipelength, q->totalOffPeriods, q->RangeOffPeriods));
        }

        while(!children.empty())
        {
            MyStruct exactChild = children[0];
            children.erase (children.begin() + 0);

            int m, check=0;
            for(m=0; m<open.size();m++)
            {
                if(exactChild.sink == open[m].sink)
                {
                    check =1;
                    break;
                }

            }

            int value3 = MapNodes[exactChild.sink];

            if(check ==0 && !visited[value3])
            {
                if(exactChild.RangeOffPeriods.find( (node.pipelength%24) ) != exactChild.RangeOffPeriods.end());

                    else
                    {
                        exactChild.pipelength = exactChild.pipelength + node.pipelength;
                        open.push_back(exactChild);
                    }
            }

            else if(check == 1)
            {
                if( (exactChild.pipelength + node.pipelength) < open[m].pipelength)
                {
                    if(exactChild.RangeOffPeriods.find( (node.pipelength%24) )!= exactChild.RangeOffPeriods.end());

                    else
                    {
                      exactChild.pipelength = exactChild.pipelength + node.pipelength;
                      open.erase (open.begin() + m);
                      open.push_back(exactChild);
                    }

                }
            }


        }

        visited[value] = true;
        sort(open.begin(), open.end(), less_than_key2());
        sort(open.begin(), open.end(), less_than_key());

     }

     if(flag == 0)
        outputFile<<"None";
}

int main()
{
   string line, algo, StartingNode;
   int NoOfTestCases, NoOfPipes, StartTime ;
   ifstream myfile ("C:\\Users\\Koyel\\Downloads\\123.txt");
   ofstream outputFile("output.txt");
   if (myfile.is_open())
   {
      getline (myfile,line);
      NoOfTestCases = atoi(line.c_str());

      for(int j=1;j<=NoOfTestCases;j++)
      {
          map<string,int> MapNodes;
          int pos=0;

          getline (myfile,algo);

          getline (myfile,StartingNode);
          MapNodes.insert ( pair<string,int>(StartingNode,pos) );
          pos++;

          getline (myfile,line);
          vector<string> EndingNodes = split(line, ' ');
          for(int i = 0; i < EndingNodes.size(); ++i)
          {
              MapNodes.insert (pair<string,int>(EndingNodes[i],pos) );
              pos++;
          }


          getline (myfile,line);
          vector<string> MiddleNodes = split(line, ' ');
          for(int i = 0; i < MiddleNodes.size(); ++i)
          {
              MapNodes.insert ( pair<string,int>(MiddleNodes[i],pos) );
              pos++;
          }

          getline (myfile,line);
          NoOfPipes = atoi(line.c_str());

          list<Node *> *adj;
          adj = new list<Node *>[pos];

          for(int i=0;i<NoOfPipes;i++)
          {
             getline (myfile,line);

             vector<string> pipedata = split(line, ' ');
             string source = pipedata[0];
             string sink = pipedata[1];
             int pipelength = atoi(pipedata[2].c_str());
             int totalOffPeriods = atoi(pipedata[3].c_str());
             set<int> RangeOffPeriods;
             for(int d=1;d<=totalOffPeriods;d++)
             {
                 string offperiod = pipedata[d+3];
                 vector<string> splitOffPeriod = split(offperiod, '-');
                 int low = atoi(splitOffPeriod[0].c_str());
                 int high = atoi(splitOffPeriod[1].c_str());
                 for(int h = low; h<=high; h++)
                    RangeOffPeriods.insert(h);

             }

             Node *n1 = new Node;
             n1->sink = sink;
             n1->pipelength = pipelength;
             n1->totalOffPeriods = totalOffPeriods;
             n1->RangeOffPeriods = RangeOffPeriods;

             int value = MapNodes[source];

             adj[value].push_back(n1);


          }

          getline (myfile,line);
          StartTime = atoi(line.c_str());

          getline (myfile,line);

          if(algo == "BFS")
             BFS(StartingNode, EndingNodes, MiddleNodes, adj, StartTime, pos, MapNodes,outputFile);
          else if(algo == "DFS")
            DFS(StartingNode, EndingNodes, MiddleNodes, adj, StartTime, pos, MapNodes,outputFile);
          else if(algo == "UCS")
            UCS(StartingNode, EndingNodes, MiddleNodes, adj, StartTime, pos, MapNodes,outputFile);

            if(j!= NoOfTestCases)
                outputFile << endl;

      }

    myfile.close();
  }

  else cout << "Unable to open file";
    return 0;
}
