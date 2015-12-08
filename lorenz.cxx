#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

void abl(double* const k,const double* para, const double x, const double y, const double z);
void RungeKutta(double* const vec,const double* k1, const double* k2, const double* k3, const double* k4, const double* para, const double dt);
void plot(const string daten, const double dt);

int main(void){
	const double TStart=0.;
	const double TEnde=100.;
	const double dt=0.5;
	const int N=(TEnde-TStart)/dt +1;
	const double para[3]={10.,28.,8./3.};
	double k1[3],k2[3],k3[3],k4[3];
	double vec[3]={1.,1.,1.};
	stringstream daten;
	daten.str("");	
	daten<<dt<<"_data.txt";
	ofstream out(daten.str().c_str());
	out<<TStart<<"\t"<<vec[0]<<"\t"<<vec[1]<<"\t"<<vec[2]<<endl;
	
	for (int i=1; i<N; i++){
		abl(k1,para,vec[0],vec[1],vec[2]);
		abl(k2,para,vec[0]+dt/2.*k1[0],vec[1]+dt/2.*k1[1],vec[2]+dt/2.*k1[2]);
		abl(k3,para,vec[0]+dt/2.*k2[0],vec[1]+dt/2.*k2[1],vec[2]+dt/2.*k2[2]);
		abl(k4,para,vec[0]+dt/2.*k3[0],vec[1]+dt/2.*k3[1],vec[2]+dt/2.*k3[2]);
		RungeKutta(vec,k1,k2,k3,k4,para,dt);
		out<<TStart+i*dt<<"\t"<<vec[0]<<"\t"<<vec[1]<<"\t"<<vec[2]<<endl;
	}
	plot(daten.str(),dt);
}

void abl(double* const k,const double* para, const double x, const double y, const double z){
	k[0]=para[0]*(y-x);
	k[1]=x*(para[1]-z)-y;
	k[2]=x*y-para[2]*z;
}
void RungeKutta(double* const vec,const double* k1, const double* k2, const double* k3, const double* k4, const double* para, const double dt){
	vec[0]+=dt/6.*(k1[0]+2*k2[0]+2*k3[0]+k4[0]);
	vec[1]+=dt/6.*(k1[1]+2*k2[1]+2*k3[1]+k4[1]);
	vec[2]+=dt/6.*(k1[2]+2*k2[2]+2*k3[2]+k4[2]);
}

void plot(const string daten, const double dt){
	stringstream befehle,speichern;
	befehle.str("");
	befehle<<dt<<"_plot.txt";
	speichern.str("");
	speichern<<dt<<"_plot.jpeg";
	ofstream plot(befehle.str().c_str());					
	
	plot<<"set terminal jpeg"<<endl;								
	plot<<"set output \""<<speichern.str()<<"\""<<endl;					
	plot<<"set st data line"<<endl;									
	plot<<"splot \""<<daten<<" \" u 2:3:4 t \""<<dt<<"\""<<endl;	
	plot<<"unset output"<<endl;
	plot.close();
	
	string befehl="gnuplot ";
	befehl.append(befehle.str());											//Systembefehl für Gnuplot erstellen (Eingabe wie in Konsole)
	system(befehl.c_str());	
}