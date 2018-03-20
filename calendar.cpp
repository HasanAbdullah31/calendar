#include <iostream>
#include <fstream>
using namespace std;

string months[12]={"January","February","March","April","May","June","July",
		   "August","September","October","November","December"};
int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
string week="Sun Mon Tue Wed Thu Fri Sat";
enum Week {SUN,MON,TUE,WED,THU,FRI,SAT};

void print(int size, ostream &out=cout) {
  for (int i=0; i<size; ++i) out<<' ';
}

void print(const string &s, int size, ostream &out=cout) {
  int num_spaces=(size-s.length())/2;
  print(num_spaces,out);
  out<<s<<endl;
}

void print(Week w, ostream &out=cout) {
  int ctr=w;
  int spaces=ctr*4-1;
  for (int i=0; i<12; ++i) {
    print(months[i],week.length(),out);
    out<<week<<endl;
    print(spaces,out);
    for (int j=1; j<=days[i]; ++j) {
      if (ctr==0)
        if (j<10) print(2,out); else print(1,out);
      else
	if (j<10) print(3,out); else print(2,out);
      out<<j; ++ctr;
      if (ctr==7) {
	out<<endl; ctr=0;
      }
    }
    out<<endl;
    spaces=ctr*4-1;
    if (ctr!=0) out<<endl;
  }
}

int main(int argc, char** argv) {
  int year;
  do {
    cout<<"Input year:"<<endl;
    cin>>year;
    cin.clear();
    cin.ignore(99,'\n');
  } while (year<2000 || cin.fail());
  if ((year-2000)%4==0)
    days[1]=29;   //leap year, February has 29 days instead of 28
  
  Week start_day; string str;
  do {
    cout<<"Input day of week of January 1 for year "<<year<<":"<<endl;
    cin>>str;
    cin.clear();
    cin.ignore(99,'\n');
  } while ((str!="Mon" && str!="Tue" && str!="Wed" && str!="Thu" && str!="Fri"
	    && str!="Sat" && str!="Sun") || cin.fail());
  if (str=="Mon")
    start_day=MON;
  else if (str=="Tue")
    start_day=TUE;
  else if (str=="Wed")
    start_day=WED;
  else if (str=="Thu")
    start_day=THU;
  else if (str=="Fri")
    start_day=FRI;
  else if (str=="Sat")
    start_day=SAT;
  else
    start_day=SUN;
  
  char choice;
  do {
    cout<<"Print to file or standard output? (F/S)"<<endl;
    cin>>choice;
    cin.clear();
    cin.ignore(99,'\n');
  } while ((choice!='F' && choice!='S') || cin.fail());
  switch (choice) {
  case 'S':
    print(start_day);   //cout
    break;
  case 'F':
    cout<<"Input name of output file:"<<endl;
    string file_name;
    cin>>file_name;
    try {
      ofstream file(file_name, ofstream::binary | ofstream::trunc);
      print(start_day,file);
      file.close();
    } catch (const exception &e) {
      cerr<<"Error outputting to "<<file_name<<"!"<<endl;
    }
    break;
  }
  return 0;
}
