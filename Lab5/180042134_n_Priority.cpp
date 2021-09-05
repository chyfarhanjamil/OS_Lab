#include<iostream>
#include<algorithm>

using namespace std;

int n = 5;

struct node
{
    char pname;
    int btime;
    int atime;
    int priority;
    int restime = 0;
    int ctime = 0;
    int wtime = 0;
} a[1000], b[1000], c[1000];

void insert(int n)
{

    a[0].atime = 2;
    a[1].atime = 0;
    a[2].atime = 1;
    a[3].atime = 3;
    a[4].atime = 5;

    a[0].btime = 13;
    a[1].btime = 1;
    a[2].btime = 2;
    a[3].btime = 16;
    a[4].btime = 7;

    a[0].priority = 3;
    a[1].priority = 1;
    a[2].priority = 3;
    a[3].priority = 4;
    a[4].priority = 2;

    a[0].pname = '1';
    a[1].pname = '2';
    a[2].pname = '3';
    a[3].pname = '4';
    a[4].pname = '5';

    for(int i = 0; i < n; i++)
    {
        a[i].wtime =- a[i].atime + 1;
    }
}

bool btimeSort(node a,node b)
{
    return a.btime < b.btime;
}

bool atimeSort(node a,node b)
{
    return a.atime < b.atime;
}

bool prioritySort(node a,node b)
{
    return a.priority < b.priority;
}

void calculations(int nop, int qt)
{
    int n = nop, q;

    sort(a, a+n, atimeSort);

    int ttime = 0, i;
    int j, tArray[n];

    for(i = 0; i < n; i++)
    {
        j = i;

        while(a[j].atime <= ttime && j != n)
        {
            j++;
        }

        sort(a+i, a+j, prioritySort);

        tArray[i] = ttime;
        ttime += a[i].btime;
    }

    tArray[i] = ttime;

    float averageWaitingTime = 0;
    float averageResponseTime = 0;
    float averageTAT = 0;

    cout<<"\nNon-preemptive Priority Scheduling:";
    for (i = 0; i < n; i++)
    {
        cout << " --> P" << a[i].pname;
    }

    cout<<"\n\nGantt Chart:\n\n";
    for (i = 0; i < n; i++)
    {
        cout <<"|   "<< "P" << a[i].pname << "   ";
    }
    cout<<"\n";

    for (i = 0; i < n+1; i++)
    {
        cout << tArray[i] << "        ";
    }
    cout<<"\n";

    cout<<"\nProcess ID\tPriority\tArrival Time\tBurst Time\tEnd Time\tStart Time\tWaiting Time\tResponse Time\n";

    int startTime;
    for (i = 0; i < nop && a[i].pname != 'i'; i++)
    {
        if(a[i].pname == '\0')
            break;

        if (i == 0)
        {
            startTime = a[i].atime;
        }
        else
        {
            startTime = tArray[i] ;
        }

        cout <<'P'<< a[i].pname << "\t\t";
        cout << a[i].priority << "\t\t";
        cout << a[i].atime << "\t\t";
        cout << a[i].btime << "\t\t";
        cout << tArray[i+1] << "\t\t";
        cout << startTime << "\t\t";
        cout << tArray[i] - a[i].atime << "\t\t";
        cout << tArray[i] - a[i].atime << "\t\t";
        cout << "\n";

        averageWaitingTime += tArray[i] - a[i].atime;
        averageResponseTime += tArray[i] - a[i].atime;
    }

    cout<<"\nAverage Response time: "<< (float)averageResponseTime/(float)n<<endl;
    cout<<"Average Waiting time: "<< (float)averageWaitingTime/(float)n<<endl;
}

int main()
{

    insert(n);
    calculations(n, 1);

    return 0;
}
