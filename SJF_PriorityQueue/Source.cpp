/*SJF with priority queue*/
/*Source: https://www.geeksforgeeks.org/implementation-of-non-preemptive-shortest-job-first-using-priority-queue/ */
/*YTUCE DSA 2022*/


using namespace std;

#include <queue>
#include <stdio.h>
#include <iostream>

#define SIZE 4

typedef struct ProcessInfo
{
	string pname;
	int atime;
	int btime;
};

typedef struct cmpBtime {
	int operator()(const ProcessInfo& p1, const ProcessInfo& p2)
	{
		return p1.btime > p2.btime;
	}
}cmpBtime;

void SortbyArrivalTime(ProcessInfo* arr)
{
	int index = 0;

	for (int i = 0; i < SIZE-1; i++)
	{
		index = i;
		for (int j = i+1 ; j < SIZE; j++)
		{
			if (arr[j].atime < arr[index].atime)
				index = j;
		}
		swap(arr[i], arr[index]);
	}
}

void printHeaders()
{
	cout << "Process id" << "\t";
	cout << "Arrival time" << "\t";
	cout << "Burst time" << "\t";
	cout << endl;
}

void printProcessInfo(ProcessInfo p)
{
	cout << "\t";
	cout << p.pname << "\t\t";
	cout << p.atime << "\t\t";
	cout << p.btime << "\t\t";
	cout << endl;
}


void SJF(ProcessInfo* arr)
{
	priority_queue<ProcessInfo, vector<ProcessInfo>, cmpBtime> wait;
	//TODO: implement heap based custom priority queue

	SortbyArrivalTime(arr);

	printHeaders();

	int currentTime = 0;
	currentTime += arr[0].atime;
	wait.push(arr[0]);
	arr[0].atime = -1;

	while (!wait.empty())
	{
		ProcessInfo pi = wait.top();
		wait.pop();

		printProcessInfo(pi);

		currentTime += pi.btime;

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
	ProcessInfo arr[SIZE];

	arr[0] = { "p1", 4, 3 };
	arr[1] = { "p2", 0, 8 };
	arr[2] = { "p3", 5, 4 };
	arr[3] = { "p4", 9, 2 };

	SJF(arr);
}