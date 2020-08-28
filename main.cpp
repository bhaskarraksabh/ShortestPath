#include<iostream>
#include<vector>
#include<unordered_map>
#include<list>
#include<queue>
using namespace std;
class newGraph
{
    int n;
    vector<pair<int,int>>matrix[1000];
    public:
    newGraph(int num)
    {
        this->n=num;
    }
    void displayGraph()
    {
        for(int i=0;i<n;i+=1)
        {
            for(auto it=matrix[i].begin();it!=matrix[i].end();++it)
            {
                cout<<i<<" "<<it->first<<" "<<it->second<<endl;
            }
        }
    }
    vector<int> dfs(int source,int dest,vector<int>path,vector<bool>&visited)
    {
        path.emplace_back(source);
        visited[source]=true;
        if(source==dest)
        {
            return path;
        }
        for(auto it=matrix[source].begin();it!=matrix[source].end();++it)
        {
            if(visited[it->first]==false)
            {
                path=dfs(it->first,dest,path,visited);
            }
        }
        if(path[path.size()-1]!=dest)
        path.erase(path.end()-1);
        return path;
    }
    vector<int>bfs(int source,int dest,vector<bool>&visited)
    {
        queue<vector<int>>q1;
        q1.push({source});
        while(!q1.empty())
        {
            vector<int>p1=q1.front();
            q1.pop();
            int s=p1[p1.size()-1];
            visited[s]=true;
            if(p1[p1.size()-1]==dest)
            return p1;
            for(auto it=matrix[s].begin();it!=matrix[s].end();++it)
            {
                if(visited[it->first]==false)
                {
                    vector<int>aux=p1;
                    aux.emplace_back(it->first);
                    q1.push(aux);
                }
            }
        }
        return q1.front();
    }
    int dijktras(int source,int dest)
    {
        priority_queue<pair<int,int>>q1;
        q1.push(make_pair(0,source));
        vector<bool>visited(n+1,false);
        vector<int>dist(n+1,99999);
        dist[source]=0;
        while(!q1.empty())
        {
            pair<int,int>p1=q1.top();
            q1.pop();
           // cout<<p1.first<<" "<<p1.second<<endl;
            if(p1.second==dest)
            continue;
            visited[p1.second]=true;
            for(auto it=matrix[p1.second].begin();it!=matrix[p1.second].end();++it)
            {
                if(visited[it->first]==false)
                {
                    if(dist[it->first]>dist[p1.second]+it->second)
                    {
                        dist[it->first]=dist[p1.second]+it->second;
                        q1.push(make_pair(dist[it->first],it->first));
                    }
                }
            }
        }
        return dist[dest];
    }
    void takeInput()
    {
        printf("Enter the connected vertices in the format\n");
        printf("Source destination cost\n");
        printf("End with 0 0 0\n");
        int a,b,c;
        while(1)
        {
            scanf("%d %d %d",&a,&b,&c);
            if(a==0 && b==0 && c==0)
            break;
            matrix[a].emplace_back(make_pair(b,c));
            matrix[b].emplace_back(make_pair(a,c));
        }
        while(1)
        {
            cout<<"1. DFS"<<endl;
            cout<<"2. BFS"<<endl;
            cout<<"3. DIJKTRAS"<<endl;
            cout<<"4. Exit"<<endl;
            int choice;
            scanf("%d",&choice);
            if(choice==1)
            {
                int s,d;
                cout<<"Enter source and destination vertex"<<endl;
                scanf("%d %d",&s,&d);
                vector<int>path;
                vector<bool>visited(n+1,false);
                path=dfs(s,d,path,visited);
                for(int i=0;i<path.size();i+=1)
                cout<<path[i]<<" ";
                cout<<endl;
            }
            else if(choice==2)
            {
                int s,d;
                cout<<"Enter source and destination vertex"<<endl;
                scanf("%d %d",&s,&d);
                vector<int>path;
                vector<bool>visited(n+1,false);
                path=bfs(s,d,visited);
                for(int i=0;i<path.size();i+=1)
                cout<<path[i]<<" ";
                cout<<endl;
            }
            else if(choice==3)
            {
                int s,d;
                cout<<"Enter source and destination vertex"<<endl;
                scanf("%d %d",&s,&d);
                int cost=dijktras(s,d);
                cout<<cost<<endl;
            }
            else 
            return;
        }
    }
};
int main()
{
    int n;
    printf("Enter the number of vertices\n");
    scanf("%d",&n);
    newGraph g(n);
    g.takeInput();
    return 0;
}