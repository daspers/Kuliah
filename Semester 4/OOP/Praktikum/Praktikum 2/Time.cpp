#include <iostream>
#include "Time.h"

using namespace std;

Time::Time(){
	hour = 0;
	minute = 0;
	second = 0;
}


//ctor dengan parameter
Time::Time(int j, int m, int s){
	hour = j;
	minute = m;
	second = s;
}

//cctor
Time::Time(const Time& temp){
	hour = temp.hour;
	minute = temp.minute;
	second = temp.second;
}

//dtor
Time::~Time(){
	
}

//Setter & Getter
void Time::setHour(int j){
	hour = j;
}

void Time::setMinute(int m){
	minute = m;
}

void Time::setSecond(int d){
	second = d;
}

int Time::getHour() const{
	return hour;
}

int Time::getMinute() const{
	return minute;
}

int Time::getSecond() const{
	return second;
}

//Konversi ke detik
int Time::convertToSecond(){
	return hour*3600+minute*60+second;
}

//Menuliskan waktu ke layar (format: hh:mm:ss)
void Time::printTime(){
	if(hour<10)
		cout<<"0";
	cout<<hour<<":";
	if(minute<10)
		cout<<"0";
	cout<<minute<<":";
	if(second<10)
		cout<<"0";
	cout<<second<<"\n";
}

//Operator Overloading
Time Time::operator+(const Time& temp){
	Time t(hour+temp.getHour(), minute+temp.getMinute(), second+temp.getSecond());
	int mul;
	if(t.second > 59){
		mul = t.second/60;
		t.minute += mul;
		t.second -= mul*60;
	}
	if(t.minute > 59){
		mul = t.minute/60;
		t.hour += mul;
		t.minute -= mul*60;
	}
	t.hour%=24;
	return t;
}

Time Time::operator-(const Time& temp){
	if(*this < temp){
		Time t(hour, minute, second);
		return t;
	}
	Time t(hour-temp.getHour(), minute-temp.getMinute(), second-temp.getSecond());
	while(t.second<0){
		t.minute -= 1;
		t.second += 60;
	}
	while(t.minute < 0){
		t.hour -=1;
		t.minute +=60;
	}
	while(t.hour<0)
		t.hour+=24;
	return t;
}

Time& Time::operator=(const Time& temp){
	hour = temp.hour;
	minute = temp.minute;
	second = temp.second;
	return *this;
}

bool Time::operator<(const Time& temp){
	if(hour!= temp.hour)
		return hour < temp.hour;
	if(minute != temp.minute)
		return minute < temp.minute;
	return second < temp.second;
}

bool Time::operator>(const Time& temp){
	if(hour != temp.hour)
		return hour > temp.hour;
	if(minute != temp.minute)
		return minute > temp.minute;
	return second > temp.second;
}
