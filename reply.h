#ifndef REPLY_H
#define REPLY_H
#include "exceptions.h"

#include <iostream>
using namespace std;
class  Reply{
private:
	string content;
public:
	Reply(string _content);
	void print();
};
#endif