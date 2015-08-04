#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <math.h>
#include "basic_circuit.h"
#include "parameter.h"
using namespace std;
#define endl '\n'

OtherTech  g_ot;
OtherTech::OtherTech() {
  cout<< "constructor sign" <<endl;
  othertech_en=false;
  //importdata();
}
void importdata() {
  //The input data from spectre is float type. I convert the size, inrftime and loadcap to integer
  //because float number can hard to be exactly the same as keys, which is easier for looking for value
  //in the unordered_map.
  float size;
  float inrftime;
  float loadcap;

  float outdelay;
  float outenergy;
  float outrftime;
  ifstream ifs("othertech/ibm45.dat");
  //ifs.open("othertech/ibm45.dat",ifstream::in);
  //cout << ifs.good();
  int n;
  while(!ifs.eof()) {
    ifs >> size >> inrftime >> loadcap >> outdelay >> outenergy >> outrftime;
    cout << size << " "<<inrftime << " "<<loadcap << " "<<outdelay << " "<<outenergy << " "<<outrftime <<endl;
    g_ot.ifs_delay[size][inrftime][loadcap]=outdelay;
    g_ot.ifs_energy[size][inrftime][loadcap]=outenergy;
    g_ot.ifs_rftime[size][inrftime][loadcap]=outrftime;
    //n=g_ot.ifs_data.bucket_count();
    //cout <<n <<endl;
  }
  g_ot.othertech_en=true;
  g_ot.gatecap_per_um=6.3e-17;
  g_ot.wirecap_per_um=1.6e-17;
  g_ot.width_max=970;
  g_ot.width_min=70;
  g_ot.rftime_max=10;
  g_ot.rftime_min=1;
  g_ot.cap_max=10;
  g_ot.cap_min=1;

  cout << g_ot.ifs_delay[70][1][1] <<endl;
  cout << g_ot.ifs_energy[70][1][1] <<endl;
  cout << g_ot.ifs_rftime[70][1][1] <<endl;
}
float getdelay(float width, float rftime, float cap) {
  unsigned int inwidth;
  unsigned int inrftime;
  unsigned int incap;
  float outdelay;
  inwidth=inputadjust(width*1e9,g_ot.width_max,g_ot.width_min,100)+70;
  inrftime=inputadjust(rftime*1e12,g_ot.rftime_max,g_ot.rftime_min,1);
  incap=inputadjust(cap*1e15,g_ot.cap_max,g_ot.cap_min,1);
  cout<<inwidth<<inrftime<<incap<<endl;
  outdelay=g_ot.ifs_delay[inwidth][inrftime][incap]*1e-12;
  cout<<outdelay<<endl;
  cout<<"getdelay successfully"<<endl;
  return outdelay;
}

float getenergy(float width, float rftime, float cap) {
  unsigned int inwidth;
  unsigned int inrftime;
  unsigned int incap;
  float outenergy;
  inwidth=inputadjust(width*1e9,g_ot.width_max,g_ot.width_min,100)+70;
  inrftime=inputadjust(rftime*1e12,g_ot.rftime_max,g_ot.rftime_min,1);
  incap=inputadjust(cap*1e15,g_ot.cap_max,g_ot.cap_min,1);
  cout<<inwidth<<inrftime<<incap<<endl;
  outenergy=g_ot.ifs_energy[inwidth][inrftime][incap]*1e-15;
  cout<<outenergy<<endl;
  cout<<"getenergy successfully"<<endl;
  return outenergy;
}

float getrftime(float width, float rftime, float cap) {
  unsigned int inwidth;
  unsigned int inrftime;
  unsigned int incap;
  float outrftime;
  inwidth=inputadjust(width*1e9,g_ot.width_max,g_ot.width_min,100)+70;
  inrftime=inputadjust(rftime*1e12,g_ot.rftime_max,g_ot.rftime_min,1);
  incap=inputadjust(cap*1e15,g_ot.cap_max,g_ot.cap_min,1);
  cout<<inwidth<<inrftime<<incap<<endl;
  outrftime=g_ot.ifs_rftime[inwidth][inrftime][incap]*1e-12;
  cout<<outrftime<<endl;
  cout<<"getrftime successfully"<<endl;
  return outrftime;
}

unsigned int inputadjust(float in, unsigned max, unsigned min, unsigned denom) {
  unsigned int out;
  unsigned int int_in=in;
  if(int_in<=min)
    out=min;
  else if(int_in>=max)
    out=max;
  else {
    out=int_in-int_in%denom;
  }
  cout << "adjusted value is " << out <<endl;
  return out;
}

/*
int main() {
  importdata();
  getdelay(3.0e-7,1.2e-12,1.3e-15);
  getenergy(3.0e-7,1.2e-12,1.3e-15);
  getrftime(3.0e-7,1.2e-12,1.3e-15);
}
*/
