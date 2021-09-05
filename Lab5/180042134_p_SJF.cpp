#include <bits/stdc++.h>

#include<iostream>
#include<algorithm>
#include <stdlib.h>

using namespace std;

int n = 5, k = 0, f = 0, r = 0;

struct node
{
    char pname;
    int btime;
    int atime;
    int restime = 0;
    int ctime = 0;
    int wtime = 0;
} a[1000], b[1000], c[1000];

void insert(int n)
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

    for(int i = 0; i < n; i++)
    {
        a[i].wtime = -a[i].atime + 1;
    }
}

bool atimeSort(node a, node b)
{
    return a.atime < b.atime;
}

bool btimeSort(node a, node b)
{
    return a.btime < b.btime;
}

bool btimeOppSort(node a,node b)
{
    if(a.btime!=b.btime)
        return a.btime > b.btime;
    return a.atime < b.atime;
}

void printResults (int rtime, int tArray[5])
{
    float averageWaitingTime = 0;
    float averageResponseTime = 0;

    int i, j;

    cout<<"\nPreemptive SJF Scheduling:";
    for (i = 0; i < k; i++)
    {
        if(i != k)
        {
            cout << " --> P" << c[i].pname;
        }
    }

    cout << "\n\nGantt Chart:\n\n";

    rtime = 0;
    for (i = 0; i < k; i++)
    {
        if(i != k)
        {
            if (c[i].pname == 'i')
            {
                cout<<"| "<<"Free"<< "  ";
            }
            else
            {
                cout<<"|  "<<'P'<< c[i].pname << "   ";
            }
        }
        rtime += c[i].btime;

        for(j = 0; j < n; j++)
        {
            if(a[j].pname == c[i].pname)
                a[j].ctime = rtime;
        }
    }
    cout<<"\n";

    rtime = 0;
    int z = 0, stime[100];
    vector<char> p;

    for (i = 0; i < k+1; i++)
    {
        if (find(p.begin(), p.end(), c[i].pname) == p.end())
        {
            p.push_back(c[i].pname);
            stime[z] = rtime;
            z++;
        }

        cout << rtime << "\t";
        tArray[i] = rtime;
        rtime += c[i].btime;
    }
    cout<<"\n\n";
    /*for (int i = 0; i < n; i++)
    {
        cout<<p[i]<<" ";
    }
    cout<<"\n";
    for (int i = 0; i < n; i++)
    {
        cout<<stime[i]<<" ";
    }
    cout<<"\n";*/

    int startTime;
    cout<<"Process  Arrival Time\t  Burst Time\tStart Time    End Time\t Waiting Time\tResponse Time\n";
    for (i = 0; i < n && a[i].pname != 'i'; i++)
    {
        if(a[i].pname == '\0')
            break;

        for (int z = 0; z < n; z++)
        {
            if ( p[z] == a[i].pname )
                startTime = stime[z];
        }

        cout << 'P' << a[i].pname << "\t\t";
        cout << a[i].atime << "\t\t";
        cout << a[i].btime << "\t  ";
        cout << startTime << "\t\t";
        cout << a[i].ctime << "\t\t";
        cout << a[i].wtime + a[i].ctime - rtime << "\t\t";
        cout << a[i].restime - a[i].atime << "\t\t";
        cout << "\n";

        averageWaitingTime += a[i].wtime + a[i].ctime - rtime;
        averageResponseTime += a[i].restime - a[i].atime;
    }

    cout<<"\nAverage Response time: "<<(float)averageResponseTime/(float)n<<endl;
    cout<<"Average Waiting time: "<<(float)averageWaitingTime/(float)n<<endl;
}

void calculations(int qt)
{
    int q;

    sort(a, a+n, atimeSort);

    /*for (int i = 0; i < n; i++) {
        printf("%d ", a[i].atime);
    }*/

    int ttime = 0, i;
    int alltime = 0;
    int j, tArray[n];

    bool moveLast = false;

    for(i = 0; i < n; i++)
    {
        alltime += a[i].btime;
        //cout<<"start is "<<a[i].pname<<" to "<<ttime<<"\n";
    }

    alltime += a[0].atime;

    for(i = 0; ttime <= alltime;)
    {
        j = i;
        while(a[j].atime <= ttime && j != n)
        {
            //cout<<"less than atime is "<<a[j].pname<<" to "<<ttime<<"\n";
            b[r]=a[j];
            j++;
            r++;
        }

        if(r == f)
        {
            c[k].pname = 'i';
            c[k].btime = a[j].atime - ttime;
            c[k].atime = ttime;
            ttime += c[k].btime;
            k++;
            continue;
        }

        i = j;
        if(moveLast == true)
        {
            //cout<<"moving "<<b[f].pname<<" to "<<r<<"\n";
            sort(b+f, b+r, btimeSort);
            //sortBurstTime(n, f, r);
            // b[r]=b[f];
            // f++;
            // r++;
        }

        j = f;
        if(b[j].btime > qt)
        {
            c[k] = b[j];
            c[k].btime = qt;
            k++;
            b[j].btime = b[j].btime - qt;
            ttime += qt;

            moveLast = true;

            for(q = 0; q < n; q++)
            {
                if(b[j].pname != a[q].pname)
                {
                    a[q].wtime += qt;
                }
            }
        }
        else
        {
            c[k] = b[j];
            k++;
            f++;
            ttime += b[j].btime;
            moveLast = false;
            for(q = 0; q < n; q++)
            {
                if(b[j].pname != a[q].pname)
                {
                    a[q].wtime += b[j].btime;
                }
            }
            //cout<<"called for "<<b[j].pname<<" "<<b[j].btime<<"\n";
        }

        if(f == r && i >= n)
            break;
    }


    tArray[i] = ttime;
    ttime += a[i].btime;

    for(i = 0; i < k-1; i++)
    {
        if(c[i].pname == c[i+1].pname)
        {
            c[i].btime += c[i+1].btime;

            for(j = i+1; j<k-1; j++)
                c[j] = c[j+1];

            k--;
            i--;
        }
    }

    int rtime = 0;

    for(j = 0; j < n; j++)
    {
        rtime = 0;
        for(i = 0; i < k; i++)
        {
            if(c[i].pname == a[j].pname)
            {
                a[j].restime = rtime;
                break;
            }
            rtime += c[i].btime;
        }
    }

    printResults(rtime, tArray);
}

int main()
{

    insert(n);
    calculations(1);

    return 0;
}
