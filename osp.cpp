#include<iostream>
#include<unistd.h>
#include<stdio.h>
using namespace std;
//ARRIVAL TIME, BURST TIME, completion, time quantum, ready queue, count, state, flag, time, noe, pnt, burst_time, turnaround_time, wait_time
int arrival_t[100], burst_t[50], comple_t[50]={0}, quantum_t, ready_q[50]={0}, c=0, state, flag=0, time=0, noe=0, pnt=0, burst_tm[50]={0}, totaltime, wait_t;
float avg_tt, avg_wt;

void SearchStack01(int pnt,int time)
{
	for(int x=pnt+1;x<4;x++)
	{
		if(arrival_t[x]<=time)
		{
		ready_q[noe]=x+1;
		noe++;
		}
	}
}
void SearchStack02(int pnt, int time)
{
	for(int x=pnt+1;x<4;x++)
	{
	
		int fl=0;
		for(int y=0;y<noe;y++)
		{
			if(ready_q[y]==x+1)
			{
			fl++;
			}
			
		}
		if(arrival_t[x]<=time && fl==0 && burst_t[x]!=0)
		{
			ready_q[noe]=x+1;
			noe++;
		}
	}
}
void AddQue(int pnt)
{
	ready_q[noe]=pnt+1;
	noe++;
}


main()
{

	cout<<"AT = Arrival Time \nBT = Burst Time\nCT = Completion Time\nTT = Turnaround Time\nWT = Waiting Time\n\n";
	for(int x=0;x<4;x++){
	cout<<"\nProcess "<<x+1;
	cout<<"\nArrival Time=";
	cin>>arrival_t[x];
	cout << "Burst Time=";
	cin>>burst_t[x];
	burst_tm[x]=burst_t[x];}
	cout<<"\nEnter time quantum:";
	cin>>quantum_t;
	system("CLS");
	cout<<endl<<"GANTT CHART"<<endl<<arrival_t[0];
	do{
		if(flag==0)
		{
			state=arrival_t[0];
			if(burst_tm[0]<=quantum_t)
			{
				time=state+burst_tm[0];
				burst_tm[0]=0;
				SearchStack01(pnt,time);
			}
			else
			{
				burst_tm[0]=burst_tm[0]-quantum_t;
				time=state+quantum_t;
				SearchStack01(pnt,time);
				AddQue(pnt);
			}
		}
		else
		{
			pnt=ready_q[0]-1;
			state=time;
			for(int x=0;x<noe && noe!=1;x++)
			{
				ready_q[x]=ready_q[x+1];
			}
			noe--;
			if(burst_tm[pnt]<=quantum_t)
			{
				time=state+burst_tm[pnt];
				burst_tm[pnt]=0;
				SearchStack02(pnt, time);
			}
		else
		{
			burst_tm[pnt]=burst_tm[pnt]-quantum_t;
			time=state+quantum_t;
			SearchStack02(pnt, time);
			AddQue(pnt);
		}
		}
		if(burst_tm[pnt]==0)
		{
			comple_t[pnt]=time;
		}
		flag++;
		cout<<"]-P"<<pnt+1<<"-["<<time;
	}
	while(noe!=0);
	cout<<"\n\nPROCESS\t AT\t BT\t CT\t TT\t WT\n";
	for(int x=0;x<4;x++)
	{
		totaltime=comple_t[x]-arrival_t[x];
		wait_t=totaltime-burst_t[x];
		cout<<"P"<<x+1<<" \t "<<arrival_t[x]<<" \t "<<burst_t[x]<<" \t "<<comple_t[x]<<" \t "<<totaltime<<" \t "<<wait_t<<"\n";
		avg_wt=avg_wt+wait_t;
		avg_tt=avg_tt+totaltime;
	}
	cout<<"\nAVERAGE Total Time: "<<avg_tt/4<<"\nAVERAGE Wait Time: "<<avg_wt/4;
}

