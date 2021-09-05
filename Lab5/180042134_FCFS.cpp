#include<iostream>
#include<algorithm>
#include <stdlib.h>

using namespace std;

int i, j, ttime = 0, n = 5;
int tArray[5];

struct node
{
    char pname;
    int btime;
    int atime;
} a[50];

void insert()
{
    a[0].pname = '1';
    a[1].pname = '2';
    a[2].pname = '3';
    a[3].pname = '4';
    a[4].pname = '5';

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
}

bool atimeSort(node a,node b)
{
    return a.atime < b.atime;
}

void calculations(int n)
{

    sort(a, a+n, atimeSort);

    for(i = 0; i < n; i++)
    {
        j = i;

        while(a[j].atime <= ttime && j != n)
        {
            j++;
        }

        tArray[i] = ttime;
        ttime += a[i].btime;
    }

    tArray[i] = ttime;
}

void printResults(int n)
{
    float averageWaitingTime = 0;
    float averageResponseTime = 0;

    cout<<"\nFCFS Scheduling:";
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
        if (tArray[i] >= 10)
        {
            cout << tArray[i] << "       ";
        }
        else
        {
            cout << tArray[i] << "        ";
        }
    }
    cout<<"\n";

    cout<<"\nProcess ID\tArrival Time\tBurst Time\tStart Time\tEnd Time\tWaiting Time\tResponse Time\n";

    int startTime;
    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
            startTime = a[i].atime;
        }
        else
        {
            startTime = tArray[i];
        }

        cout << a[i].pname << "\t\t";
        cout << a[i].atime << "\t\t";
        cout << a[i].btime << "\t\t";
        cout << startTime << "\t\t";
        cout << tArray[i+1] << "\t\t";
        cout << tArray[i] - a[i].atime << "\t\t";
        cout << tArray[i] - a[i].atime << "\t\t";
        cout <<"\n";

        averageWaitingTime += tArray[i] - a[i].atime;
        averageResponseTime += tArray[i] - a[i].atime;
    }

    cout<<"\nAverage Response time: " << (float)averageResponseTime/(float)n << endl;
    cout<<"Average Waiting time: " << (float)averageWaitingTime/(float)n << endl;
}

// Driver code
int main()
{

    insert();
    calculations(n);
    printResults(n);

    return 0;
}
