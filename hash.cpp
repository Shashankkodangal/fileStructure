// C++ program to store and retrieve geographical data from file using hashing. Use any collision resolution technique.

#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>

#include <time.h>

using namespace std;
double seconds;

class earth
{
	public:
		string Accidentid, Name, latitude,longitude;
		void printhash();
		void enter_data();
		void display_data();
		void pack();
		void unpack();
}s;
fstream fp;
int hash(string);
void search();
//void d();
void error(int);
int succ_cnt = 0;




int main()
{


	int choice;
	system("clear");
	fp.open("acc.txt", ios::out|ios::app);
	fp.close();

	while(1)
	{

		cout<<"\n1.print hash\n2.Insert a Record\n3.Search for a record\n4.Exit \nEnter choice : ";
		cin>>choice;
		time_t now;
		time_t later;
		double seconds;
		switch(choice)
		{

			case 1: time(&now);
			        s.printhash();
			        time(&later);
			        seconds = difftime(later,now);
			        cout<<seconds<<endl;
					break;
			case 2: time(&now);
				    s.enter_data();
				    s.pack();
				    time(&later);
			        seconds = difftime(later,now);
			        cout<<seconds<<endl;
				    break;
			case 3:
				search();
				break;
					default: exit(0);

		   // case 3:
			  //  d();

		}
	}
}

int hash(string Accidentid)

{


   int seed = 131,c;
  unsigned long hash = 0;
       for (int k = 0; k <Accidentid.length(); k++)
        {
        	 hash = (hash * seed) + Accidentid[k];// to multiply with a value and add the position of the id

		}
        c= hash % 35000;
    hash = c*300;
    return c+hash;
}
void earth::printhash()
{
		ifstream ip("acc.csv");

  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

  while(ip.good()){

    getline(ip,Accidentid,',');
    getline(ip,Name,',');
    getline(ip,latitude,',');
    getline(ip,longitude,'\n');


    pack();
  }
    cout<<"Total: "<<succ_cnt<<endl;
   	ip.close();
}

void earth::enter_data()
{

	cout<<"\nEnter Accidentid: ";
	cin>>Accidentid;
	cout<<"\nEnter Name: ";
	cin>>Name;
    cout<<"\nEnter latitude: ";
    cin>>latitude;
    cout<<"\nEnter longitude: ";
	cin>>longitude;

}

void earth::pack()
{
	int cnt,pos;
	string temp;

    	string buf = Accidentid + "|" + Name + "|" + latitude + "|" + longitude + "|";
	if(buf.length() > 100)
	{	error(2);
		return;
	}
	while(buf.length()<100)
		buf += '_';

	pos = hash(Accidentid);
	fp.open("acc.txt",ios::in);

	if(!fp)
		error(1);
	fp.seekg(pos,ios::beg);
	getline(fp,temp);
	fp.close();
	cnt = temp[0]-48;
	if(cnt == 3)
	{
		error(3);
		return;
	}
	fp.open("acc.txt",ios::out|ios::in);
	if(!fp)
		error(1);
			time_t now;
		    time_t later;
		    time(&now);
	if(cnt<0)
	{
		fp.seekp(pos,ios::beg);
		fp.put('1');
		pos=pos+1;

	}
	else if(cnt==1)
	{
		fp.seekp(pos,ios::beg);
		fp.put('2');
		pos=pos+101;

	}
	else if(cnt==2)
	{
		fp.seekp(pos,ios::beg);
		fp.put('3');
		pos=pos+201;
	}
    
cout<<"inserting at :"<<pos;
	
	succ_cnt++;
	fp.seekp(pos,ios::beg);
	fp<<buf<<endl;
	fp.close();



	if(succ_cnt%10000==0){
		  cout<<succ_cnt<<endl;
	}
}

void search()
{
	string Accidentid_srch,temp;
	int cnt, flag =0, pos, i;
	cout<<"\nEnter the id of the city to search: ";
	cin>>Accidentid_srch;
	pos = hash(Accidentid_srch);
	fp.open("acc.txt",ios::in);
	fp.seekg(pos,ios::beg);
	getline(fp,temp);
	cnt = temp[0]-48;
	int pos1;
	time_t now;
	time_t later;
	double seconds;
	time(&now);
	for(i=1;i<=cnt;i++)
	{
		 if(i==1)
	{
		pos1=pos+1;
	}
	else if(i==2)
	{
		pos1=pos+101;
	}
	else if(i==3)
	{
		pos1=pos+201;
	}
	fp.seekg(pos1,ios::beg);
		s.unpack();
		if(Accidentid_srch == s.Accidentid)
		{
			flag=1;
			break;
		}
	}
	fp.close();
	if(!flag)
	{
		cout<<"Record Not Found!\n";
		return;
	}
	else
	{
		cout<<"Record Found\n";
		s.display_data();
	}
	time(&later);
	seconds = difftime(later,now);
	cout.precision(17);
	cout<<fixed<<seconds<<endl;
}

void earth::unpack()
{
		string seg;
		getline(fp,Accidentid,'|');
		getline(fp,Name,'|');
		getline(fp,latitude,'|');
		getline(fp,longitude,'|');
		getline(fp,seg);
}

void earth::display_data()
{
	cout<<"\nName: "<<Name<<"\nAccidentid: "<<Accidentid<<"\nlatitude: "<<latitude<<"\nlongitude:"<<longitude<<endl;
}

void error(int error_type)

 {
	switch(error_type)
	{
		case 1: cout<<"\nFATAL ERROR!: Unable to open the record File\n";
			exit(0);
	case 2:	cout<<"\n ERROR!: Data exceeds record length\n";
			return;
	case 3:	cout<<"\n ERROR!: Cannot insert!: Maximum no of collisions allowed = 3";
			return;
	}

}





