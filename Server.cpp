#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<iostream>
#include<iomanip>
#include<limits.h>

#define PORT 8000
#define MAX 200

using namespace std;
class Passenger {

	public:
	char name[MAX],phn_no[MAX],pickup_stop[MAX],dropoff_stop[MAX];
	int pickup_no,dropoff_no;
	static bool isdropped;
};
bool Passenger::isdropped=false;

Passenger* getDetails(Passenger p[],int no,int i) {

int soc,newsoc,child;
socklen_t sizeofpass;

struct sockaddr_in cab,pass;

cab.sin_family=AF_INET;
cab.sin_addr.s_addr=htonl(INADDR_ANY);
cab.sin_port=htons(PORT);

soc = socket(AF_INET,SOCK_STREAM,0);

if(soc<0) {

	cout<<"\n Failed to Create Socket"<<endl;
}
else {

	cout<<"\n ----------------------------------------------------";
	cout<<"\n  *************Waiting for "<<no<< " Passengers ***************";
	cout<<"\n ----------------------------------------------------";
}

bind(soc,(struct sockaddr*)&cab, sizeof(cab));

listen(soc,50);

if(i==0) {

	while(i<no) {

		sizeofpass = sizeof(pass);

		newsoc = accept(soc,(struct sockaddr*)&pass,&sizeofpass);

		read(newsoc,p[i].name,sizeof(p[i].name));

		read(newsoc,p[i].phn_no,sizeof(p[i].phn_no));

		read(newsoc,p[i].pickup_stop,sizeof(p[i].pickup_stop));

		read(newsoc,p[i].dropoff_stop,sizeof(p[i].dropoff_stop));

		cout<<"\n Data Received from Passenger "<<i+1<<endl;

	i++;
	close(newsoc);
	}
}
else {

		sizeofpass = sizeof(pass);

		newsoc = accept(soc,(struct sockaddr*)&pass,&sizeofpass);

		read(newsoc,p[i].name,sizeof(p[i].name));

		read(newsoc,p[i].phn_no,sizeof(p[i].phn_no));

		read(newsoc,p[i].pickup_stop,sizeof(p[i].pickup_stop));

		read(newsoc,p[i].dropoff_stop,sizeof(p[i].dropoff_stop));

		cout<<"\n Data Received from new Passenger "<<endl;

		close(newsoc);
}

close(soc);
return p;
}

void line(int n) {

	 for(int i=0;i<n;i++)
          cout<<"--";
}

void star(int n) {

	 for(int i=0;i<n;i++)
          cout<<"**";
}

int findStopNo(string Stops[],char stopName[]) {

	int no;
	for(int i=0;i<12;i++) {

		if(strcmp(Stops[i].c_str(),stopName)==0) {
			no = i;
		}
	}
return no;
}

void passDetails(string Stops[],Passenger p[],int pickup_stops[],int dropoff_stops[]) {

	line(40);
	cout<<"\n";
	cout<<setw(10)<<"Passenger Name"<<setw(20)<<"Mobile No"<<setw(20)<<"Pickup Point"<<setw(20)<<"Drop-off Point"<<endl;
	line(40);

	for(int i=0;i<3;i++) {

		cout<<"\n"<<setw(10)<<p[i].name;
	
		cout<<setw(20)<<p[i].phn_no;

		cout<<setw(20)<<p[i].pickup_stop;

		cout<<setw(20)<<p[i].dropoff_stop<<endl;
	}

	for(int i=0;i<3;i++) {

		p[i].pickup_no = findStopNo(Stops,p[i].pickup_stop);

		pickup_stops[i] = p[i].pickup_no;
	}	

	for(int i=0;i<3;i++) {

		p[i].dropoff_no = findStopNo(Stops,p[i].dropoff_stop);

		dropoff_stops[i] = p[i].dropoff_no;
	}
}

int minDistance(int dist[], bool sptSet[]) 
{ 
	int min = INT_MAX, min_index; 

	for (int v = 0; v < 12; v++) 
		if (sptSet[v] == false && dist[v] <= min) 
			min = dist[v], min_index = v; 
	return min_index; 
} 

void deletePassengers(Passenger p[],int picked_pass[],int k) {

	int index=picked_pass[k];
	
	cout<<"\n\n "<<p[index].name<<" Dropped at "<<p[index].dropoff_stop<<endl;

	for(int i=index;i<3;i++) {

		p[i] = p[i+1];
	}

	getDetails(p,1,2);
	p[0].isdropped=true;
}

void printPath(string Stops[],int parent[],int src,int stop_no,int picked_pass[],Passenger p[],int pass_no,bool tobedropped) 
{
	int path[12];
	int j=0;

	if (parent[stop_no] == - 1) 
		return; 


	printPath(Stops,parent,src,parent[stop_no],picked_pass,p,pass_no,tobedropped); 

	path[j] = stop_no;
	j++;

	if(tobedropped==false) {

		for(int i=0;i<j;i++) {

			cout<<" -> "<<Stops[path[i]];
		}
	}

	else if(picked_pass[pass_no-1]!=-1 && tobedropped==true) {

			for(int i=0;i<j;i++) {

				for(int k=1;k<pass_no;k++) {

					if(path[i]==p[picked_pass[k]].dropoff_no) {

						deletePassengers(p,picked_pass,k);
					}
				
				}	
			}
	}	
} 

void printSolution(int parent[],int src,int dist[], int stop_no,int picked_pass[],Passenger p[],int pass_no,bool tobedropped) 
{ 
		string Stops[12] = {"Baner","Aundh","Kothrud","Khadki","C.S.M Nagar","Nanded City","Viman Nagar","Shaniwar Wada","Rajiv Gandhi Zoological Park","Kondhwa","Hadapsar","Kharadi"};

		if(dist[stop_no]!=0) {

			printPath(Stops,parent,src,stop_no,picked_pass,p,pass_no,tobedropped); 
		}
}  

int dijkstra(int src, int des,int picked_pass[],Passenger p[],int pass_no,bool tobedropped) 
{ 
	int Stops[12][12] = {{0  , 4, 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  }, 
			  			 {4, 0  , 11 , 6, 7, 0  , 0  , 0  , 0  , 0  , 0  , 0  }, 
	    		   		 {0  , 11 , 0  , 0  , 0  , 8, 0  , 6  , 0  , 0  , 0  , 0  }, 
			 		     {0  , 6, 0  , 0  , 0  , 0  , 9, 8, 0  , 0  , 0  , 0  }, 
	    		  		 {0  , 7, 0  , 0  , 0  , 0  , 0  , 3  , 0  , 0  , 0  , 0  }, 
			   			 {0  , 0  , 8, 0  , 0  , 0  , 0  , 13 , 11 , 0  , 0  , 0  }, 
	    			     {0  , 0  , 0  , 9, 0  , 0  , 0  , 11 , 0  , 0  , 9, 5}, 
			 		     {0  , 0  , 6  , 8, 3  , 13 , 11 , 0  , 7, 8, 11 , 0  }, 
	    	    	     {0  , 0  , 0  , 0  , 0  , 11 , 0  , 7, 0  , 5, 0  , 0  }, 
			     		 {0  , 0  , 0  , 0  , 0  , 0  , 0  , 8, 5, 0  , 9  , 0  }, 
			   			 {0  , 0  , 0  , 0  , 0  , 0  , 9, 11 , 0  , 9  , 0  , 8}, 
			   			 {0  , 0  , 0  , 0  , 0  , 0  , 6, 0  , 0  , 0  , 8, 0  }};
	int no=12;
	int dist[no]; 
	bool sptSet[no]; 
	int parent[no]; 

	for (int i = 0; i < no; i++) 
	{ 
		parent[i] = -1; 
		dist[i] = INT_MAX; 
		sptSet[i] = false; 
	} 

	dist[src] = 0; 

	for (int count = 0; count < no - 1; count++) 
	{ 
		int u = minDistance(dist, sptSet); 
		sptSet[u] = true; 

		for (int v = 0; v < no; v++) 
			if (!sptSet[v] && Stops[u][v] && 
				dist[u] + Stops[u][v] < dist[v]) 
			{ 
				parent[v] = u; 
				dist[v] = dist[u] + Stops[u][v]; 
			} 
	} 
	printSolution(parent,src,dist,des,picked_pass,p,pass_no,tobedropped); 

return dist[des];
} 

int findDistance(int no,int pickup_stops[],int picked_pass[],int cab,Passenger p[],int pass_no) {

	string Stops[12] = {"Baner","Aundh","Kothrud","Khadki","C.S.M Nagar","Nanded City","Viman Nagar","Shaniwar Wada","Rajiv Gandhi Zoological Park","Kondhwa","Hadapsar","Kharadi"};

	int distance[no];

	int min_stop=-1,min_distance=INT_MAX;

	for(int i=0;i<no;i++) {
		
		cout<<"\n "<<Stops[cab];

		distance[i] = dijkstra(cab,pickup_stops[i],picked_pass,p,pass_no,false);

		cout<<"\n\n "<<Stops[pickup_stops[i]]<<" = "<<distance[i]<<"km"<<endl;

		if(distance[i] < min_distance) {
			
			min_distance = distance[i];
			min_stop = i;
		}
	}

return min_stop;	
}

void completedStops(int pickup_stops[],int pos,int no) {

	for(int i=pos;i<no;i++) {

		pickup_stops[i] = pickup_stops[i+1];
	}
}

int startPickup(string Stops[],int pickup_stops[],int dropoff_stops[],int cab,Passenger p[]) {

	int minIndex,pass_no=1,i=3;
	int picked_pass[pass_no];

	while(i>0) {

		cout<<"\n";
		star(10);
		cout<<"Starting Next Pickup";
		star(10);
		cout<<endl;
		sleep(3);

		cout<<"\n Distance of Passengers from Cab :"<<endl;

		if(i==3) {

			picked_pass[pass_no-1] = -1;
		}
		else {

			for(int j=0;j<3;j++ ) {

				if(cab == p[j].pickup_no) {

					picked_pass[pass_no-1] = j;
					
				}
			}
		}

		minIndex = findDistance(i,pickup_stops,picked_pass,cab,p,pass_no);
		cab = pickup_stops[minIndex];

		if(i!=3) {

			int dis = dijkstra(p[picked_pass[pass_no-1]].pickup_no,pickup_stops[minIndex],picked_pass,p,pass_no,true);
		}

		if(p[0].isdropped==true) {

			passDetails(Stops,p,pickup_stops,dropoff_stops);

			p[0].isdropped=false;	
			
			if(i==1) {
			
				i++;

				completedStops(pickup_stops,minIndex,i);
			}
			else {
				i++;
			}					
		}

		for(int i=0;i<3;i++) {

			if(cab == p[i].pickup_no) {

				cout<<"\n\n"<<p[i].name<<" Picked from  "<<Stops[cab]<<endl;

				break;
			}
		}	

		cout<<"\n";
		star(10);
		cout<<"Cab is in "<<Stops[cab];
		star(10);
		cout<<endl;
		
		completedStops(pickup_stops,minIndex,i);	

	i--;
	pass_no++;	
	}
return cab;
}

void startDropoff(string Stops[],int dropoff_stops[],int cab,Passenger p[]) {

	int minIndex,pass_no=1,i=3;
	int picked_pass[pass_no];;

	while(i>0) {

		cout<<"\n";
		star(10);
		cout<<"Starting Next Dropoff";
		star(10);
		cout<<endl;
		sleep(3);

		cout<<"\n Distance of Passengers from Cab :"<<endl;

		if(i==3) {

			picked_pass[pass_no-1] = -1;
		}
		else {

			for(int j=0;j<3;j++ ) {

				if(cab == p[j].dropoff_no) {

					picked_pass[pass_no-1] = j;
				}
			}
		}

		minIndex = findDistance(i,dropoff_stops,picked_pass,cab,p,pass_no);

		cab = dropoff_stops[minIndex];
		
		for(int i=0;i<3;i++) {

			if(cab == p[i].dropoff_no) {

				cout<<"\n\n"<<p[i].name<<" Dropped at  "<<Stops[cab]<<endl;

				break;
			}
		}

		cout<<"\n";
		star(10);
		cout<<"Cab is in "<<Stops[cab];
		star(10);
		cout<<endl;

		completedStops(dropoff_stops,minIndex,i);	

	i--;
	pass_no++;	
	}
}

int main() {

string Stops[12] = {"Baner","Aundh","Kothrud","Khadki","C.S.M Nagar","Nanded City","Viman Nagar","Shaniwar Wada","Rajiv Gandhi Zoological Park","Kondhwa","Hadapsar","Kharadi"};

int cab = 0;
int pickup_stops[3],dropoff_stops[3];

Passenger p[3];

while(true) {

	getDetails(p,3,0);

	system("clear");

	passDetails(Stops,p,pickup_stops,dropoff_stops);

	cout<<"\n";
	line(40);
	cout<<"\n";
	star(10);
	cout<<" Starting Pickup... ";
	star(10);
	cout<<"\n";
	line(40);
	cout<<endl;

	sleep(3);

	cout<<"\n";
	star(10);
	cout<<"Cab is in "<<Stops[cab];
	star(10);
	cout<<endl;

	cab = startPickup(Stops,pickup_stops,dropoff_stops,cab,p);

	cout<<"\n";
	line(40);
	cout<<"\n";
	cout<<" \t\t Starting Drop-off... ";
	cout<<"\n";
	line(40);
	cout<<endl;

	startDropoff(Stops,dropoff_stops,cab,p);

	cout<<"\n";
	line(40);
	cout<<"\n";
	cout<<" \t\t Cab is Empty...";
	cout<<"\n";
	line(40);
	cout<<endl;

	int op;

	cout<<"\n Wait for new Passengers?"<<"\n 1.Yes \t 2.No"<<endl;
	cout<<"\n Choose Option : ";
	cin>>op;

	switch(op) {

		case 1:
		break;

		case 2:
		exit(1);

		default:
		cout<<"\n Incorrect Option..";
		exit(1);
	}
}

return 0;
}
