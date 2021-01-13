#include "netflix.h"
#include "film.h"
#include "user.h"
#include "publisher.h"
#include "comment.h"
#include "reply.h"
#include "functions.h"
#include "dastoor.h"
#include "exceptions.h"

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[])
{
  string fileAddress=argv[1];
  ifstream fff;
  fff.open(fileAddress);
  string newline;
  Netflix n;
  n.recommend_film(5);
  if(!fff){
  cerr << "Error: file could not be opened"<<endl;
  exit(1);
  }
  while( getline(fff,newline)){
  	try{
   n.process(newline);
   //cout<< "no error"<< endl;
  		
  	}catch(Bad_Request b){
  		cout<<"Bad Request"<<endl;
  	}catch(Permission_Denied p){
  		cout<<"Permission Denied"<<endl;
  	}catch(Not_Found n){
  		cout<<"Not Found"<<endl;
  	}
  }

  return 0;
}
