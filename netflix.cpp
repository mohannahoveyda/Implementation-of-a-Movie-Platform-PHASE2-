#include "netflix.h"
   User* Netflix :: get_currentUserPtr(){ return currentUserPtr;}
    void Netflix :: signup(string _email, string _username, string _password, int _age, bool _is_publisher){
     if (currentUserPtr==NULL)
     {
     	if(_is_publisher){
      users.push_back(new Publisher(_email,_username,RSHash(_password),_age,_is_publisher));
     }
     else{
      users.push_back(new User(_email,_username,RSHash(_password),_age,_is_publisher));
     }
     cout<< "OK"<<endl;
      int t=users.size()-1;
      currentUserPtr=users[t];
      users[t]->set_user_id(t+1);
     }
     else{
     	cout<< "ERROR"<<endl;
     }
    }
    void Netflix :: login(string _username, string _password){
      bool flag=false;

      if (currentUserPtr==NULL)
      {
      	if ( _username=="admin" && _password=="admin" ) {
      		is_admin=true;
      		cout<<"welcome admin"<<endl;

      	}else{
      		for (int i = 0; i < users.size(); i++) {
       			if (users[i]->login(_username, RSHash(_password)) ) {
         			cout<< "OK"<<endl;
         			currentUserPtr=users[i];
         			flag=true;
       			}
     		}
     		if (!flag) {
       			//cout<<"NOT FOUND!\n";
       			throw Not_Found();
     		}
     	}
     }
     else{
     	//cout<<"ERROR"<<endl;
     	throw Bad_Request();
     }
    }
    void Netflix ::logout(){
    	currentUserPtr=NULL;
    	cout << "OK"<<endl;
    	is_admin=false;
    }

    void Netflix :: follow(int user_id){
     // if (!users[user_id-1]->IsPublisher())
     // {
     //  cout<< "permission denied";
     // }
     //cout<<currentUserPtr->get_username()<<"wanted to follow "<< users[user_id-1]->get_username()<<"\n";
      currentUserPtr->add_following(users[user_id-1]);
      users[user_id-1]->add_follower(currentUserPtr);
      users[user_id-1]->add_notif("User "+ users[user_id-1]->get_username() + " with id " + to_string(users[user_id-1]->get_user_id())+ " follow you.");


    }
    void Netflix :: print_users(){
      for (int i = 0; i < users.size(); i++) {
       users[i]->print();
      }
    }
    void Netflix :: post_film(string film_name, int year, int length, int price, string summary, string director){
     Publisher* currentPublisherPtr= (Publisher*) currentUserPtr;
     currentPublisherPtr->post_film( film_name, year, length, price, summary, director, films, lastFilmID);
       lastFilmID++;
     }
     void Netflix :: edit_film(int film_id, string film_name, int year, int length, string summary, string director){
     Publisher* currentPublisherPtr= (Publisher*) currentUserPtr;
     currentPublisherPtr->edit_film_info( film_id,film_name, year, length, summary, director);
     cout << "OK"<<endl;
     }
    void Netflix :: delete_film(int film_id){
     Publisher* currentPublisherPtr= (Publisher*) currentUserPtr;
     currentPublisherPtr->delete_film(film_id,films);
    }
    void Netflix :: print_films(){
     cout<<"#. Film Id | Film Name | Film Length | Film Price | Rate | Production Year | Film Director"<<endl;
     cout<<"all films are:"<<"\n";

     for (int i = 0; i < films.size(); i++)
     {
       films[i]->print();
     }
    }
    void Netflix :: show_followers(int user_id){
     users[user_id-1]->show_followers();
    }

    void Netflix :: print_currentUserFilms(){
     Publisher* currentPublisherPtr= (Publisher*) currentUserPtr;
     cout<<"Publisher's films are:"<<"\n";
     currentPublisherPtr->print_myUploadedFilms();
    }
    void Netflix :: buy_film(int film_id){
    	if (currentUserPtr!=NULL)
    	{
    		network_cash+=currentUserPtr->buy_film(film_id,films);
      cout<<"OK"<<endl;
    	}
    	else{
    		throw Bad_Request();
    	}
      
    }
    
    void Netflix :: show_film_list(string film_name, int min_rate, int min_year, int price, int max_year, string director){
     Publisher* currentPublisherPtr= (Publisher*) currentUserPtr;
      currentPublisherPtr->show_film_list(film_name,min_rate, min_year, price, max_year, director);      
    }
    void Netflix :: rate_film(int film_id, float score){
      currentUserPtr->rate_film(film_id,score);
      cout<<"OK"<<endl;
    }
    void Netflix :: show_purchased_films(string name, int _price, int min_year,int max_year, string director){
      currentUserPtr->show_purchased_films(name, _price, min_year , max_year, director);
    }
  
    void Netflix :: print_film_detail(int film_id){
      for (int i = 0; i <films.size() ; i++)
      {
        if(films[i]->check_for_equal_filmID(film_id)){
          films[i]->print_film_detail();
        }
      }
      cout<< "Recommendation Film"<< endl;
      cout<< "#. Film Id | Film Name | Film Length | Film Director"<<endl;
      recommend_film(film_id);
    }
    //void Netflix :: recommend_film(){}
    void Netflix :: post_comment(int film_id, string _content){
     currentUserPtr->post_comment( film_id, lastCommentID, _content);
     cout<<"OK"<<endl;
       lastCommentID++;
    }
    void Netflix ::post_reply(int _film_id, int comment_id, string _content){
      Publisher* currentPublisherPtr= (Publisher*) currentUserPtr;
      currentPublisherPtr->post_reply(_film_id, comment_id , _content);  
     cout<<"OK"<<endl;

    }
    void Netflix :: delete_comment(int film_id, int comment_id){
      Publisher* currentPublisherPtr= (Publisher*) currentUserPtr;
     currentPublisherPtr->delete_comment( film_id, comment_id);
     cout<<"OK"<<endl;


    }
    void Netflix :: recommend_film(int film_id){
      
    	vector <int> line(lastFilmID-1,0);
    	vector< vector<int> > mojaverat(lastFilmID-1,line);
    	
    	for (int i = 0; i <users.size(); i++)
    	{
    		users[i]->add_mojaverat(mojaverat);
    	}
    	/*cout<<"MAtrix mojaverat is below:"<<endl;
    	for(int i=0;i<mojaverat.size();i++){
    		for(int j=0;j<mojaverat[i].size();j++){
    			cout<<"  "<<mojaverat[i][j];
    		}
    		cout<<endl;
    	}
    	cout<<"_________________________________"<<endl;*/
    	
      int f;
      vector <Film*> unwatched_films;
      for (int i = 0; i < films.size(); i++)
      {
        f=films[i]->get_film_id();
        if (!currentUserPtr->check_if_film_exists_in_purchased_films(f) && f!=film_id)
        {
          unwatched_films.push_back(films[i]);
        }
      }

      Film* best;
      int bestnumber;
      for (int k = 0; k < 4; k++)
      {
        bestnumber=0;
        if(unwatched_films.size()>0){
          best=unwatched_films[0];
          for(int j=1;j<unwatched_films.size();j++){
            //if(unwatched_films[j]->is_greater(best)){
            if( mojaverat[film_id-1][unwatched_films[j]->get_film_id()-1] > mojaverat[film_id-1][best->get_film_id()-1] ){	
             best=unwatched_films[j];
             bestnumber=j;
            }
          }
          unwatched_films.erase(unwatched_films.begin()+bestnumber);
          cout<< film_id<<". ";
          best->print();
        }
      }
    }

    void Netflix :: show_unread_notifications(){
      currentUserPtr->show_unread_notifications();

    }
    void Netflix :: show_all_notifications(int limit){
      currentUserPtr->show_all_notifications(limit+1);
    }
    void Netflix :: showFollowers(){
      currentUserPtr->show_followers();
    }

    void Netflix :: addCash(int amount){
      currentUserPtr->add_cash(amount);
      cout<<"OK"<<endl;
    }
    void Netflix :: show_cash(){
		currentUserPtr->show_cash();
    }
    void Netflix :: get_publisher_money(){
    	Publisher* currentPublisherPtr= (Publisher*) currentUserPtr;
     currentPublisherPtr->get_money(&network_cash);
     cout<<"OK"<<endl;
    }
    void Netflix :: search_films(string film_name, int min_rate, int min_year, int price, int max_year, string director){
    	currentUserPtr->search(film_name, min_rate, min_year, price, max_year, director, films);
    }
   void Netflix :: show_network_cash(){
   	cout<< network_cash<<endl ;
   }
   

void Netflix :: process(string newline){
	
	////////////////////////////////////////////////from here
	vector<string> parameters;
	vector<string> values;
	int i=newline.find(" ");
	int j=newline.find("?");
	string command=newline.substr(0,i);
	string type=newline.substr(i+1,j-i-1);
	if(type.find("notifications read")==string::npos){type=nospace(type);}else{ type ="notifications read";}
	string rest;
	if(newline.find("?")!=string::npos ){
		rest=newline.substr(j+1) ;
	}else{
		rest="";
	}
	bool flag=true;
	string temp;
	bool shouldbeparameter=true;
	while(flag){
		if(rest.find(" ")==string::npos ){ 
			flag=false;
		}
		i=rest.find(" ");
		temp= rest.substr(0,i);
		if(temp!=" " && temp!=""){
			if(shouldbeparameter){
				parameters.push_back(temp);
			}else{
				values.push_back(temp);
			}
			shouldbeparameter=!shouldbeparameter;
		}
		rest=rest.substr(i+1);
	}
	//if !shouldbeparameter ---> error
	/////////////////////////////////////////to here
	
	/*dastoor order;
	for(int k=1;k<parameters.size();k++){
		order.set_value(parameters[k],values[k]);
	}
	*/
	if(command=="POST"){
		if(type=="signup"){
			dastoor order;
			for(int k=0;k<parameters.size();k++){
				order.set_value(parameters[k],values[k]);
				// parameters should not be out of this list
				if(parameters[k]=="email" || parameters[k]=="username" || parameters[k]=="password" || parameters[k]=="age"|| parameters[k]=="publisher" ){}else{
					//cout<<"invalid parameter for this command";
					throw Bad_Request();
				}
				//cout<<"<"<<parameters[k]<<">:<"<<values[k]<<">"<<endl;
			}
			if( order.get_email()!="" && order.get_username()!="" && order.get_password()!="" && order.get_age()!=-10  ){ // mandatory parameters
				//cout<<"signup_user("<<order.get_email()<<","<<order.get_username()<<","<<order.get_password()<<","<<order.get_age()<<","<<order.get_is_publisher()<<")"<<endl;
				signup(order.get_email(),order.get_username(), order.get_password(), order.get_age(), order.get_is_publisher());
			}else{
				cout<<"Error1"<<endl;
			}
		}
		if(type=="login"){
			dastoor order;
			for(int k=0;k<parameters.size();k++){
				order.set_value(parameters[k],values[k]);
				// parameters should not be out of this list
				if( parameters[k]=="username" || parameters[k]=="password"  ){}else{
					//cout<<"invalid parameter for this command";
					throw Bad_Request();

				}
			}		
			if( order.get_username()!="" && order.get_password()!="" ){
				//cout<<"login("<<order.get_username()<<","<<order.get_password()<<")"<<endl;
				login(order.get_username(), order.get_password());
			}else{
				throw Bad_Request();
			}
		}

		if(type=="logout"){
				
			if (currentUserPtr!=NULL)
			{
				if( parameters.size()==0){
				logout();
			}else{
				//cout<<"Error3"<<endl;
				throw Bad_Request();
			}
			}else{
				throw Permission_Denied();
			}
		}
		if(type=="films"){
			if (currentUserPtr!=NULL && currentUserPtr->IsPublisher()==true)
			{
				dastoor order;
			for(int k=0;k<parameters.size();k++){
				order.set_value(parameters[k],values[k]);
				// parameters should not be out of this list
				if( parameters[k]=="name" || parameters[k]=="year"  || parameters[k]=="length" || parameters[k]=="price" || parameters[k]=="summary" || parameters[k]=="director"){}else{
					//cout<<"invalid parameter for this command";
					throw Bad_Request();

				}
				//cout<<"<"<<parameters[k]<<">:<"<<values[k]<<">"<<endl;
			}
			if(order.get_name()!="" && order.get_year()!=-10 && order.get_length()!=-10 && order.get_price()!=1000000 && order.get_summary()!="" && order.get_director()!="" ){
				//cout<<"post film("<<order.get_name()<<","<<order.get_year()<<","<< order.get_length()<<","<< order.get_price()<<","<<order.get_summary()<<","<<order.get_director()<<")"<<endl;
				post_film(order.get_name(), order.get_year(), order.get_length(), order.get_price(), order.get_summary(), order.get_director());
			}else{
				//cout<<"Error4"<<endl;
					throw Bad_Request();

			}
				
			}else{
				throw Permission_Denied();
			}
			
		}
		if(type=="money"){
			if(parameters.size()==0  ){
				//cout<<"post_money()"<<endl;
				if (currentUserPtr!=NULL && currentUserPtr->IsPublisher()==true){
					get_publisher_money();
				}else{
				throw Permission_Denied();
			}
				
			}
			// else{
			// 	throw Bad_Request();
			// }
			
			
		}
		if(type=="replies"){
			dastoor order;
		if (currentUserPtr!=NULL && currentUserPtr->IsPublisher()==true)
		{
				for(int k=0;k<parameters.size();k++){
				order.set_value(parameters[k],values[k]);
				// parameters should not be out of this list
				if( parameters[k]=="film_id" || parameters[k]=="comment_id"  || parameters[k]=="content" ){}else{
					//cout<<"invalid parameter for this command";
					throw Bad_Request();

				}
				//cout<<"<"<<parameters[k]<<">:<"<<values[k]<<">"<<endl;
			}
			if( order.get_film_id()!=-10 && order.get_comment_id()!=-10 && order.get_content()!="" ){
				//cout<<"reply_comment("<<order.get_film_id()<<","<<order.get_comment_id()<<","<<order.get_content()<<")"<<endl;
				post_reply(order.get_film_id(),order.get_comment_id(), order.get_content());
			}else{
				//cout<<"Error5"<<endl;
				throw Bad_Request();
			}
		}
		else{
			throw Permission_Denied();
		}
		}
		if(type=="followers"){
			dastoor order;
			if (currentUserPtr!=NULL)
			{
				for(int k=0;k<parameters.size();k++){
				order.set_value(parameters[k],values[k]);
				// parameters should not be out of this list
				if( parameters[k]=="user_id" ){}else{
					//cout<<"invalid parameter for this command";
					throw Bad_Request();

				}
			}
			if( order.get_user_id()!=-10 ){
				//cout<<"follow("<<order.get_user_id() <<")"<<endl;
				follow(order.get_user_id());
			}else{
				//cout<<"Error6"<<endl;
					throw Bad_Request();

			}
			}else{
				throw Permission_Denied();
			}
			
			
		}
		if(type=="money"){
			if(parameters.size()==1 && parameters[0]=="amount" ){
				//cout<<"add_cash("<<stooi(values[0]) <<")"<<endl;
				if (currentUserPtr!=NULL)
				{
				addCash(stooi(values[0]));
				}
				else 
				{
					throw Permission_Denied();
				}
			}else if(parameters.size()!=0){
				//cout<<"Error7"<<endl;
				throw Bad_Request();
			}
		}
		if(type=="buy"){
			if (currentUserPtr!=NULL)
			{
				if(parameters.size()==1 && parameters[0]=="film_id"  ){
				//cout<<"buy film("<<stooi(values[0]) <<")"<<endl;
				buy_film(stooi(values[0]) );
			}else{
				//cout<<"Error8"<<endl;
				throw Bad_Request();
			}
			}
			else{
				throw Permission_Denied();
			}
		}
		if(type=="rate"){
			dastoor order;
			if (currentUserPtr!=NULL)
			{
				for(int k=0;k<parameters.size();k++){
				order.set_value(parameters[k],values[k]);
				// parameters should not be out of this list
				if( parameters[k]=="film_id" || parameters[k]=="score" ){}else{
					//cout<<"invalid parameter for this command";
					throw Bad_Request();

				}
				//cout<<"<"<<parameters[k]<<">:<"<<values[k]<<">"<<endl;
			}
			if( order.get_film_id()!=-10 && order.get_score()!=-10){
				//cout<<"rate film("<< order.get_film_id()<<","<< order.get_score()<<")"<<endl;
				rate_film(order.get_film_id(), order.get_score());
			}else{
				//cout<<"Error9"<<endl;
				throw Bad_Request();
			}
			}else{
				throw Permission_Denied();
			}
		}
		if(type=="comments"){
			dastoor order;
			for(int k=0;k<parameters.size();k++){
				order.set_value(parameters[k],values[k]);
				// parameters should not be out of this list
				if( parameters[k]=="film_id" || parameters[k]=="content" ){}else{
					//cout<<"invalid parameter for this command";
					throw Bad_Request();

				}
				//cout<<"<"<<parameters[k]<<">:<"<<values[k]<<">"<<endl;
			}if (currentUserPtr!=NULL)
			{
				
				if( order.get_film_id()!=-10 && order.get_content()!=""){
				//cout<<"comment on film("<< order.get_film_id()<<","<< order.get_content()<<")"<<endl;
				post_comment( order.get_film_id(), order.get_content());
			}else{
				//cout<<"Error10"<<endl;
					throw Bad_Request();

			}
			}else{
				throw Permission_Denied();
			}
			
		}
		if(type=="put_films"){
			dastoor order;
			for(int k=0;k<parameters.size();k++){
				order.set_value(parameters[k],values[k]);
				// parameters should not be out of this list
				if( parameters[k]=="film_id" || parameters[k]=="name" || parameters[k]=="year" || parameters[k]=="length" || parameters[k]=="summary" || parameters[k]=="director" ){}else{
					//cout<<"invalid parameter for this command";
					throw Bad_Request();

				}
			}if (currentUserPtr!=NULL && currentUserPtr->IsPublisher()==true)
			{
				if( order.get_film_id()!=-10 ){
				//cout<<"edit_film("<<order.get_film_id()<<","<<order.get_name()<<","<<order.get_year()<<","<<order.get_length()<<","<<order.get_summary()<<","<<order.get_director()<<")"<<endl;
				edit_film(order.get_film_id(),order.get_name(),order.get_year(),order.get_length(),order.get_summary(),order.get_director());
			}else{
				//cout<<"Error11"<<endl;
				throw Bad_Request();
			}
			}else{
				throw Permission_Denied();
			}
			
		}
		if(type=="delete_films"){
			if (currentUserPtr!=NULL && currentUserPtr->IsPublisher()==true)
			{
				if(parameters.size()==1 && parameters[0]=="film_id"  ){
				//cout<<"delete_film("<<stooi(values[0]) <<")"<<endl;
				delete_film(stooi(values[0]) );
			}else{
				//cout<<"Error12"<<endl;
				throw Bad_Request();
			}
			}else{
				throw Permission_Denied();
			}
		}

		if(type=="delete_comments"){
			dastoor order;
			for(int k=0;k<parameters.size();k++){
				order.set_value(parameters[k],values[k]);
				// parameters should not be out of this list
				if( parameters[k]=="film_id" || parameters[k]=="comment_id" ){}else{
					//cout<<"invalid parameter for this command";
					throw Bad_Request();

				}
			}
			if (currentUserPtr!=NULL && currentUserPtr->IsPublisher()==true)
			{
				if( order.get_film_id()!=-10 && order.get_comment_id()!=-10 ){
				//cout<<"delete_comment("<<order.get_film_id() <<","<< order.get_comment_id()<<")"<<endl;
				delete_comment(order.get_film_id() , order.get_comment_id());
			}else{
					throw Bad_Request();
				
			}
		}else{
			throw Bad_Request();
			}
		}
		else if(type!="signup" && type!="login" && type!="logout" &&  type!="films" && type!="money" && type!="replies" && type!="followers" && type!="buy" && type!="comments" && type!="put_films" && type!="delete_films" && type!="delete_comments")
		{
			throw Not_Found();
		}
	}
	
	
	if(command=="GET"){
		if(type=="followers"){
			if (currentUserPtr!=NULL && currentUserPtr->IsPublisher()==true)
			{
				if(parameters.size()==0 ){
				//cout<<"get_followers()"<<endl;
				showFollowers();
			}else{
					throw Bad_Request();
				
			}
			}else{
				throw Permission_Denied();
			}
		}
		if(type=="published"){
			dastoor order;

			if (currentUserPtr!=NULL && currentUserPtr->IsPublisher()==true)
			{
				for(int k=0;k<parameters.size();k++){
				order.set_value(parameters[k],values[k]);
				// parameters should not be out of this list
				if( parameters[k]=="name" || parameters[k]=="min_rate" || parameters[k]=="min_year" || parameters[k]=="price" || parameters[k]=="max_year" || parameters[k]=="director" ){}else{
					//cout<<"invalid parameter for this command";
					throw Bad_Request();

				}
			}
			//order.print();
			//cout<<"show published films("<<order.get_name()<<","<<order.get_min_rate()<<","<<order.get_min_year()<<","<<order.get_price()<<","<<order.get_max_year()<<","<<order.get_director()<<")"<<endl;
			show_film_list(order.get_name(),order.get_min_rate(),order.get_min_year(),order.get_price(),order.get_max_year(),order.get_director());

			}else{
				throw Permission_Denied();
			}
		}
		if(type=="films"){
			dastoor order;
			if (currentUserPtr!=NULL)
			{
				for(int k=0;k<parameters.size();k++){
				order.set_value(parameters[k],values[k]);
				// parameters should not be out of this list
				if( parameters[k]=="name" || parameters[k]=="min_rate" || parameters[k]=="min_year" || parameters[k]=="price" || parameters[k]=="max_year" || parameters[k]=="director"  || parameters[k]=="film_id"){}else{
					//cout<<"invalid parameter for this command";
					throw Bad_Request();

				}
			}
			if(parameters.size()==1 && order.get_film_id()!=-10 ){
				//cout<<"get film detail("<<stooi(values[0])<<")"<<endl;
				print_film_detail(stooi(values[0]));
			}else if( order.get_film_id()==-10 ){
				//cout<<"search films("<<order.get_name()<<","<<order.get_min_rate()<<","<<order.get_min_year()<<","<<order.get_price()<<","<<order.get_max_year()<<","<<order.get_director()<<")"<<endl;
				search_films(order.get_name(),order.get_min_rate(),order.get_min_year(),order.get_price(),order.get_max_year(),order.get_director());
			}else{
				throw Bad_Request();
			}
			}else{
				throw Permission_Denied();
			}
		}
		if(type=="purchased"){
			dastoor order;
			if (currentUserPtr!=NULL)
			{
				/* code */
				for(int k=0;k<parameters.size();k++){
				order.set_value(parameters[k],values[k]);
				// parameters should not be out of this list
				if( parameters[k]=="name" || parameters[k]=="price" || parameters[k]=="min_year" ||  parameters[k]=="max_year" || parameters[k]=="director" ){}else{
					//cout<<"invalid parameter for this command";
					throw Bad_Request();

				}
			}
			//cout<<"show purchased films("<<order.get_name()<<","<<order.get_price()<<","<<order.get_min_year()<<","<<order.get_max_year()<<","<<order.get_director()<<")"<<endl;	
			show_purchased_films(order.get_name(),order.get_price(),order.get_min_year(),order.get_max_year(),order.get_director())	;	
	
			}else{
				throw Permission_Denied();
				}
			}
		
		if(type=="notifications"){
			if (currentUserPtr!=NULL)
			{
				if(parameters.size()==0 ){
				//cout<<"show_notifs()"<<endl;
				show_unread_notifications();

			}else{
				//cout<<"Error16"<<endl;
					throw Bad_Request();

			}
			}else{
				throw Permission_Denied();
			}
		}
		if(type=="notifications read"){
			if (currentUserPtr!=NULL)
			{
				if(parameters.size()==1 && parameters[0]=="limit" ){
				//cout<<"show notification even read ones with limit of"<< stooi(values[0])<<endl;
				show_all_notifications(stooi(values[0]));
			}else{
				//cout<<"Error17"<<endl;
					throw Bad_Request();

			}
			}
		}
		if(type=="money"){
			if(parameters.size()==0 ){
				//cout<<"get_followers()"<<endl;
				if(is_admin){
					//cout<<"network cash is: ";
					show_network_cash();
				}
				else{
					//cout<<"USER cash is: ";
					show_cash();
				}
			}else{
				//cout<<"Error18"<<endl;
					throw Bad_Request();

			}
		}
		else if(type!="money" && type!="notifications read" && type!="notifications" &&  type!="purchased" && type!="films" && type!="published" && type!="followers" ){
			throw Not_Found();
		}


	}


	else if(command!="POST" && command!="PUT" && command!="GET" && command!="DELETE"){
		throw Bad_Request();
	}


}