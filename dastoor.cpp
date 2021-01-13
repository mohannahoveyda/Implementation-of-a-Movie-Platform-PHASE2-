#include "dastoor.h"

		
		dastoor :: dastoor(){
			name="";
			summary="";
			director="";
			email="";
			username="";
			password="";
			content="";
			price=1000000;
			min_year=-10;
			max_year=10000;
			year=-10;
			length=-10;
			age=-10;
			film_id=-10;
			comment_id=-10;
			user_id=-10;
			amount=-10;
			limit=-10;
			is_publisher=false;
			min_rate=-10;
			score=-10;
		}
		////////
		string dastoor :: get_name(){ return name;  }
		string dastoor :: get_summary(){ return summary;  }
		string dastoor :: get_director(){ return director;  }
		string dastoor :: get_email(){ return email;  }
		string dastoor :: get_username(){ return username;  }
		string dastoor :: get_password(){ return password;  }
		string dastoor :: get_content(){ return content;  }
		int dastoor :: get_price(){ return price;  }
		int dastoor :: get_min_year(){ return min_year;  }
		int dastoor :: get_max_year(){ return max_year;  }
		int dastoor :: get_year(){ return year;  }
		int dastoor :: get_length(){ return length;  }
		int dastoor :: get_age(){ return age;  }
		int dastoor :: get_film_id(){ return film_id;  }
		int dastoor :: get_comment_id(){ return comment_id;  }
		int dastoor :: get_user_id(){ return user_id;  }
		int dastoor :: get_amount(){ return amount;  }
		int dastoor :: get_limit(){ return limit;  }
		bool dastoor :: get_is_publisher(){ return is_publisher;  }
		float dastoor :: get_min_rate(){ return min_rate;  }
		float dastoor :: get_score(){ return score;  }
		////////
		void dastoor ::set_value(string parameter,string value){
			if(parameter=="name"){ name=value;}
			else if(parameter=="summary"){ summary=value;}
			else if(parameter=="director"){ director=value;}
			else if(parameter=="price"){ price=stooi(value);}
			else if(parameter=="year"){ year=stooi(value);}
			else if(parameter=="min_year"){ min_year=stooi(value);}
			else if(parameter=="max_year"){ max_year=stooi(value);}
			else if(parameter=="length"){ length=stooi(value);}
			else if(parameter=="min_rate"){ min_rate=stoof(value);}
			else if(parameter=="publisher"){ 
				if(value=="true" || value=="TRUE" || value=="True"){ is_publisher=true;}else{ is_publisher=false;}
			}
			else if(parameter=="email"){ email=value;}
			else if(parameter=="username"){ username=value;}
			else if(parameter=="password"){ password=value;}
			else if(parameter=="content"){ content=value;}
			else if(parameter=="age"){ age=stooi(value);}
			else if(parameter=="film_id"){ film_id=stooi(value);}
			else if(parameter=="comment_id"){ comment_id=stooi(value);}
			else if(parameter=="user_id"){ user_id=stooi(value);}
			else if(parameter=="amount"){ amount=stooi(value);}
			else if(parameter=="limit"){ limit=stooi(value);}
			else if(parameter=="score"){ score=stoof(value);}
			else{
				//cout<<"invalid parameter:"<<parameter<<endl;
			}		
		}
		void dastoor ::print(){
			cout<<"order is:"<<endl;
			if(name!=""){cout<<"name:"<<name<<endl;}
			if(summary!=""){cout<<"summary:"<<summary<<endl;}
			if(director!=""){cout<<"director:"<<director<<endl;}
			if(email!=""){cout<<"email:"<<email<<endl;}
			if(username!=""){cout<<"username:"<<username<<endl;}
			if(password!=""){cout<<"password:"<<password<<endl;}
			if(content!=""){cout<<"content:"<<content<<endl;}
			if(price!=-10){cout<<"price:"<<price<<endl;}
			if(min_year!=-10){cout<<"min_year:"<<min_year<<endl;}
			if(max_year!=-10){cout<<"max_year:"<<max_year<<endl;}
			if(year!=-10){cout<<"year:"<<year<<endl;}
			if(length!=-10){cout<<"length:"<<length<<endl;}
			if(age!=-10){cout<<"age:"<<age<<endl;}
			if(film_id!=-10){cout<<"film_id:"<<film_id<<endl;}
			if(comment_id!=-10){cout<<"comment_id:"<<comment_id<<endl;}
			if(user_id!=-10){cout<<"user_id:"<<user_id<<endl;}
			if(amount!=-10){cout<<"amount:"<<amount<<endl;}
			if(limit!=-10){cout<<"limit:"<<limit<<endl;}
			if(1!=2){cout<<"is_publisher:"<<is_publisher<<endl;}
			if(min_rate!=-10){cout<<"min_rate:"<<min_rate<<endl;}
			if(score!=-10){cout<<"score:"<<score<<endl;}
			
		}
		