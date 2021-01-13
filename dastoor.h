#ifndef DASTOOR_H
#define DASTOOR_H
#include <iostream>
#include "functions.h"
#include "exceptions.h"

using namespace std;

class dastoor{
	private:
		string name;
		string summary;
		string director;
		string email;
		string username;
		string password;
		string content;
		int price;
		int min_year;
		int max_year;
		int year;
		int length;
		int age;
		int film_id;
		int comment_id;
		int user_id;
		int amount;
		int limit;
		bool is_publisher;
		float min_rate;
		float score;
	public:
		dastoor();
		////////
		string get_name();  
		string get_summary();
		string get_director();
		string get_email();
		string get_username();
		string get_password();
		string get_content();
		int get_price();
		int get_min_year();
		int get_max_year();
		int get_year();
		int get_length();
		int get_age();
		int get_film_id();
		int get_comment_id();
		int get_user_id();
		int get_amount();
		int get_limit();
		bool get_is_publisher();
		float get_min_rate();
		float get_score();
		////////
		void set_value(string parameter,string value);
		void print();
		
};
#endif