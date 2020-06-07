#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include<iomanip>
#include <string>
#include "Cost.h"
#define MAX 200
#define PORT 8000

using namespace std;

class Passenger{

	public:

	char pass_name[MAX],pass_mob[MAX],pickup_stop[MAX],dropoff_stop[MAX];

	int pickup_no,dropoff_no;

	string stops[12] = {"Baner","Aundh","Kothrud","Khadki","C.S.M Nagar","Nanded City","Viman Nagar","Shaniwar Wada","Rajiv Gandhi Zoological Park","Kondhwa","Hadapsar","Kharadi"};

	string stop;

	int soc,con;

	struct sockaddr_in pass,cab;
	
	void startConnection() {
		
		pass.sin_family = AF_INET;
		pass.sin_port = htons(PORT);
		inet_pton(AF_INET,"127.0.0.1",&pass.sin_addr);

		cab.sin_family = AF_INET;
		cab.sin_port = htons(PORT);
		inet_pton(AF_INET,"127.0.0.1",&cab.sin_addr);

		soc = socket(AF_INET,SOCK_STREAM,0);
		con = connect(soc,(struct sockaddr*)&cab,sizeof(cab));

		if (con<0) {

			cout<<"\n ************:( Sorry, No Seats available please wait for next cab************"<<endl;
			exit(1);
		}
		else {
	
			cout<<"\n ****************************************** ";
			cout<<"\n Cab Booked Successfully, Its on your way ";
			cout<<"\n ****************************************** ";
			
			write(soc,pass_name,sizeof(pass_name));
			write(soc,pass_mob,sizeof(pass_mob));
			write(soc,pickup_stop,sizeof(pickup_stop));
			write(soc,dropoff_stop,sizeof(dropoff_stop));
			close(soc);
			exit(1);
		}
	}

	void getName() {

	    cout<<"\n Enter your Name :";
        cin>>pass_name;
	}

	void getMobno() {

	    cout<<"\n Enter your Mob No :";
        cin>>pass_mob;
	}

	void getPickup(int no) {

		pickup_no = no-1;
	    stop = stops[no-1];
	    strcpy(pickup_stop,stop.c_str());
	}

	void getDropoff(int no) {

		dropoff_no=no-1;
	    stop = stops[no-1];
	    strcpy(dropoff_stop,stop.c_str());
	}
	
};

void line(int n) {
	 
	 for(int i=0;i<n;i++)
          cout<<"--";
}

void star(int n) {

	 for(int i=0;i<n;i++)
          cout<<"**";
}

int getStopNo() {

	    int stop;
	    
		cout<<"\n";
		line(20);
	    cout<<"\n Stop No"<<setw(15)<<"Stop Name \n";
		line(20);

	    cout<<"\n 1"<<setw(20)<<"Baner"<<endl
		<<"\n 2"<<setw(20)<<"Aundh"<<endl
		<<"\n 3"<<setw(20)<<"Kothrud"<<endl
		<<"\n 4"<<setw(20)<<"Khadki" <<endl
		<<"\n 5 "<<setw(20)<<"C.S.M Nagar"<<endl
		<<"\n 6"<<setw(20)<<"Nanded City"<<endl
		<<"\n 7"<<setw(20)<<"Viman Nagar"<<endl
		<<"\n 8"<<setw(20)<<"Shaniwar Wada"<<endl
		<<"\n 9 "<<setw(20)<<"Rajiv Gandhi Zoological Park"<<endl
		<<"\n 10"<<setw(20)<<"Kondhwa"<<endl
		<<"\n 11"<<setw(20)<<"Hadapsar"<<endl
		<<"\n 12"<<setw(20)<<"Kharadi"<<endl
		<<"\n\n Enter Stop No :";
        cin>>stop;

            switch(stop) {

                case 1:
                    return 1;
                    break;

                case 2:
                    return 2;
                    break;

                case 3:
                    return 3;
                    break;

                case 4:
                    return 4;
                    break;

				case 5:
		    		return 5;
		    		break;

				case 6:
   		    		return 6;
		    		break;

				case 7:
					return 7;
					break;

				case 8:
					return 8;
					break;

				case 9:
					return 9;
					break;

				case 10:
					return 10;
					break;

				case 11:	
					return 11;
					break;

				case 12:	
					return 12;
					break;

                default:
                    cout<<"\n Please Choose Correct Option!";
					exit(1);
	}

return 0;
}

void ticket(Passenger p) {

	int cost = Cost(p.pickup_no,p.dropoff_no);
	int distance = dijkstra(p.pickup_no,p.dropoff_no);

	int con;

	cout<<"\n Passenger Name :"<<setw(15)<<p.pass_name<<endl;
	cout<<"\n Passenger Mob No :"<<setw(12)<<p.pass_mob<<endl;
	cout<<"\n Pickup Point :"<<setw(15)<<p.pickup_stop<<endl;
	cout<<"\n Drop-off Point :"<<setw(14)<<p.dropoff_stop<<endl;
	cout<<"\n Total Distance :"<<setw(10)<<distance<<"Km"<<endl;
	cout<<"\n Fair :"<<setw(20)<<cost<<"Rs"<<endl;

	cout<<"\n\n *-*-*-*-*-*-*-*-HAPPY JOURNEY-*-*-*-*-*-*-*-*"<<endl;

	cout<<"\n Confirm Your Booking ?";
	cout<<"\n 1. Yes \t 2. No"<<endl;
	cout<<"\n Enter Choice :";
	cin>>con;

	if(con==1) {

		p.startConnection();
	}
	else if(con==2) {

		cout<<"\n";
		star(40);
    	cout<<"\n Thank You for Using our Service...\n";
		star(40);
        exit(1);
	}
	else {

		cout<<"\n Please Choose Correct Option!";
	}
}

int main() {

	Passenger p;

	int option;

	cout<<"\n";
	star(40);
    cout<<"\n \t \t \t Welcome to Cab Booking \n";
	star(40);

    cout<<"\n 1. Book a Cab"<<endl<<"\n 2. Exit"<<endl<<"\n Enter Choice :";
    cin>>option;

    switch(option) {

        case 1:
	    system("clear");

		cout<<"\n";
		star(40);
        cout<<"\n \t \t \t Enter Passenger Details \n";
		star(40);
	    p.getName();

	    p.getMobno();
	    system("clear");

		cout<<"\n";
		star(20);
		cout<<"\n\t Enter Pickup Point :\n";
		star(20);

	    p.getPickup(getStopNo());
		system("clear");

		cout<<"\n";
		star(10);
	    cout<<" Pickup Point "<<p.pickup_stop<<" Selected ";
		star(10);
	   
	   	cout<<"\n";
		star(20);
		cout<<"\n\t Enter Drop-off Point :\n";
		star(20);

	    p.getDropoff(getStopNo());
		system("clear");
		
		if(strcmp(p.pickup_stop,p.dropoff_stop)==0) {
			cout<<"\n";
			star(10);
			cout<<" Pickup Point and Dropoff Point Cannot be Same ";
			star(10);
			exit(1);
		}
		cout<<"\n";
		star(10);
	    cout<<" Drop-off Point "<<p.dropoff_stop<<" Selected ";
		star(10);

	    ticket(p);
        break;

        case 2:
		cout<<"\n";
		star(40);
    	cout<<"\n\t Thank You for Using our Service...\n";
		star(40);
        exit(1);
       	break;

        default:
        cout<<"\n Please Choose Correct Option!";
		exit(1);
    }

return 0;
}

