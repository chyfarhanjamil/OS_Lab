#include<iostream>
#include<algorithm>

using namespace std;

int k = 0, f = 0, r = 0;

struct node
{
    char pname;
    int btime;
    int atime;
    int restime=0;
    int ctime=0;
    int wtime=-1;
} a[100], b[100], c[100];

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
        a[i].wtime =- a[i].atime;
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

void printResults(int rtime, int tArray[5], int nop)
{
    int i, j;

    float averageWaitingTime = 0;
    float averageResponseTime = 0;
    float averageTAT = 0;

    cout<<"\nRound Robin (quantum = 4) Scheduling:";
    for (i = 0; i < k + 1 && i < 20; i++)
    {
        if(i != k)
            cout << " -> P" << c[i].pname;
    }

    cout << "\n\nGantt Chart:\n\n";

    rtime = 0;
    for (i = 0; i < k + 1 && i < 20; i++)
    {
        if(i != k)
            cout<<"|   "<<'P'<< c[i].pname << "   ";
        rtime += c[i].btime;
        for(j = 0; j < 6; j++)
        {
            if(a[j].pname == c[i].pname)
                a[j].ctime = rtime;
        }
    }
    cout<<"\n";

    rtime = 0;
    for (i = 0; i < k+1 && i < 20; i++)
    {
        if (rtime >= 10)
        {
            cout << rtime << "       ";
        }
        else
        {
            cout << rtime << "        ";
        }

        tArray[i] = rtime;
        rtime += c[i].btime;
    }

    cout<<"\n";
    cout<<"\n";
    cout<<"Process ID\tArrival Time\tBurst Time\tStart Time\tEnd Time\tWaiting Time\tResponse Time\n";

    int startTime;
    for (i = 0; i < 6 && i < nop && a[i].pname != 'i'; i++)
    {
        if(a[i].pname == '\0')
            break;
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
        cout << a[i].ctime << "\t\t";
        cout << a[i].wtime + a[i].ctime - rtime << "\t\t";
        cout << a[i].restime - a[i].atime << "\t\t";
        cout <<"\n";

        averageWaitingTime += a[i].wtime + a[i].ctime - rtime;
        averageResponseTime += a[i].restime - a[i].atime;
    }

    cout<<"\nAverage Response time: " << (float)averageResponseTime/(float)nop << endl;
    cout<<"Average Waiting time: " << (float)averageWaitingTime/(float)nop << endl;
}

void calculations(int nop, int qt)
{
    int n = nop, q;

    sort(a, a+n, atimeSort);

    int ttime = 0, i;
    int j, tArray[n];
    int alltime = 0;

    bool moveLast = false;

    for(i = 0; i < n; i++)
    {
        alltime += a[i].btime;
    }

    alltime += a[0].atime;

    for(i = 0; ttime <= alltime;)
    {
        j = i;
        while(a[j].atime <= ttime && j != n)
        {
            b[r] = a[j];
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
            b[r] = b[f];
            f++;
            r++;
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
        }
        if(f == r && i >= n)
            break;
    }

    tArray[i] = ttime;
    ttime += a[i].btime;

    int rtime = 0;
    for(j = 0; j < n && j < 6; j++)
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

    printResults(rtime, tArray, nop);
}

int main()
{
    int numberOfProcess = 5;
    int quantam = 4;

    insert(numberOfProcess);
    calculations(numberOfProcess, quantam);

    return 0;
}
