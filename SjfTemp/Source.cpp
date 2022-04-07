using namespace std;
#include <iostream>
#include <stdio.h>
#include <queue>


#define SIZE 4


typedef struct processInfo {
    string pname;
    int atime;
    int ptime;

};

//Custom Comporator for C++ queue
typedef struct cmpPtime {
    int operator()(const processInfo& a,
        const processInfo& b)
    {
        return a.ptime > b.ptime;
    }
} cmpBtime;

void sortByArrivalTime(processInfo* arr){
    
    int index = 0;
    for (int i = 0; i < SIZE - 1; i++) {
        index = i;
        for (int j = i + 1; j < SIZE; j++) {
            if (arr[j].atime < arr[index].atime) {
                index = j;
            }
        }
        swap(arr[i], arr[index]);
    }
}

void printHeaders()
{
    cout << "Process id"<< "\t";
    cout << "Arrival time"<< "\t";
    cout << "Burst time" << "\t";
    cout << endl;
}

void printProcessed(processInfo p)
{
    cout << "\t";
    cout << p.pname << "\t\t";
    cout << p.atime << "\t\t";
    cout << p.ptime << "\t\t";
    cout << endl;
}

void sjf(processInfo* arr)
{
    sortByArrivalTime(arr);

    priority_queue<processInfo, vector<processInfo>, cmpPtime> wait;

    int currentTime = arr[0].atime;
    wait.push(arr[0]);
    arr[0].atime = -1;

    printHeaders();

    while (!wait.empty())
    {
        processInfo p = wait.top();
        wait.pop();
        currentTime += p.ptime;
        printProcessed(p);

        for (int i = 0; i < SIZE; i++)
        {
            if (arr[i].atime != -1 && arr[i].atime <= currentTime)
            {
                wait.push(arr[i]);
                arr[i].atime = -1;
            }
        }
    }
}

int main()
{
    // an array of process info structures.
    processInfo arr[SIZE];

    arr[0] = { "p1", 4, 3 };
    arr[1] = { "p2", 0, 8 };
    arr[2] = { "p3", 5, 4 };
    arr[3] = { "p4", 9, 2 };

    cout << "Process scheduling ";
    cout << "according to SJF is: \n"
        << endl;

    sjf(arr);
}