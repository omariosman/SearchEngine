#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include <bits/stdc++.h>
#include<stdio.h>
#include "Graph.h"
#include "Website.h"
#include "Stats.h"
using namespace std;

//
void talk_to_user(Website *temp_websites, int temp_counter);

//print results to user
void display_results(Website *temp_websites, int temp_counter){
	
	int display_counter = 1;
	//printing resuts to user
	cout << endl << "Search Results: " << endl;
	for (int i = 0; i < temp_counter; i++){
		cout << display_counter++ << ". " << temp_websites[i].get_url() << endl;
	}
}




void calculate_normalized_rank(Website *temp_websites, Stats my_stats, int counter){
	for (int i = 0;i < counter; i++){
		float this_rank;
		float numerator = temp_websites[i].get_rank() - my_stats.get_min();
		float denominator = my_stats.get_max() - my_stats.get_min();
		this_rank = numerator / denominator;
		temp_websites[i].set_normalized_rank(this_rank);

	}
}

void insertion_sort(Website* arr, int n)  
{  
    float key;
    int i, j;  
    for (i = 1; i < n; i++) 
    {  
        key = arr[i].get_normalized_rank();  
        j = i - 1;  
  
      do {
          
          if (j >= 0 && arr[j].get_normalized_rank() > key){
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }
      } while(j >= 0 && arr[j].get_normalized_rank() > key);
   
        arr[j + 1].set_normalized_rank(key);  
    }  
   
} 
void reverseArray(Website *myArr, int n){
    Website *tempArr;
    tempArr = new Website[n];
    int k = n - 1;
    for (int i = 0; i < n; i++){
        tempArr[i] = myArr[k];
        k--;
    }
    
    for (int i = 0; i < n; i++){
        myArr[i] = tempArr[i];
    }
}


void calculate_PageRank(Website **container, int total_numbers, Graph my_graph){

	float current_rank = 0.0;
	for (int i = 0; i < total_numbers; i++){
		container[i]->set_rank(1.0/total_numbers);
	}
		
	
	for (int i = 1; i < total_numbers; i++){
	current_rank=0;
		float previous_rank = container[i-1]->get_rank(); 
		vector <int> temp_vector = my_graph.getIncomingNodes(container[i-1]->get_key());
		if (!temp_vector.empty()) {
			for (int j = 0; j < temp_vector.size(); j++){
				int out_nodes = my_graph.getNumberOfOutgoingEdges(temp_vector[j]);
				current_rank += (previous_rank / out_nodes);
				container[i-1]->set_rank(current_rank);
			}
		}
	}
	
}

vector<string> Unsorted_Results(vector<string> query, vector<vector<string>> all_data, int sign){
    
    vector<string> result;
    
    vector<vector<string> >::iterator col;
    vector<string>::iterator row;
    
   vector<string>::iterator qit;
    int and_count=0;
    
    if(sign=20){ //and logic
        
        for (int j=0; j<all_data.size(); j++){
        for (int i=0;i<all_data[j].size(); i++){
        
        for (int k=0;k<query.size();k++){
            if (std::find(query.begin(), query.end(),query[k])!=query.end()) {
                result.push_back(all_data[j][i]);
                and_count++;
            }
            if(and_count!=query.size()){
                result.pop_back();
            }}}}}
      

 if(sign=10){ //or logic
        
        for (int j=0; j<all_data.size(); j++){
        for (int i=0;i<all_data[j].size(); i++){
        
        for (int k=0;k<query.size();k++){
            if (query[k]==all_data[j][i]) {
                result.push_back(all_data[j][0]);
            }
            }}}}

 
    result.erase( unique( result.begin(), result.end() ), result.end() );
    return result;
}

vector<string> to_vector(string search){
string s =search; 
vector<std::string> result; 
istringstream iss(s); 
for(std::string s; iss >> s; ) 
    result.push_back(s);

    
    return result;
}

int Search_Signal_Remover(string &search){
   
    int sign=0;
    string AND="AND";
    string OR="OR";
    char QUOT='"'; 
    size_t pos = std::string::npos;
  
  
  if (search.find("OR") != std::string::npos) {
    sign=10;
 
 
 while ((pos  = search.find(OR) )!= std::string::npos)
    {
        // If found then erase it from string
        search.erase(pos, OR.length());
    }
 
 
}
    
    
    
   else if (search.find("AND") != std::string::npos) {
    sign=20;
    
    while ((pos  = search.find(AND) )!= std::string::npos)
    {
        // If found then erase it from string
        search.erase(pos, AND.length());
    }
 
    
    
    
}
    
    
     else if (search.find(QUOT) != std::string::npos) {
    sign=30;
    
    
   while ((pos  = search.find(QUOT) )!= std::string::npos)
    {
        // If found then erase it from string
        search.erase(pos, 1);
    }
    
}
    
    return sign;
    
}

void display_urls(int n, Website **container){
	for (int i = 0; i < n; i++){
		cout <<i+1 << ". " << container[i]->get_url() << endl;
	}
}





int main() {


	map <string, int> websites2; 
	map <int, string> IdToName; 
	ifstream newFile;
	newFile.open("websites_names.csv");
	int new_value = 0;
	while (newFile.good()) {
		string new_line;
		getline(newFile, new_line, ',');
		websites2[new_line] = new_value;
		IdToName[new_value] = new_line;
		new_value++;
	}

	//initialize new Graph
	
	Graph my_graph(new_value - 1);

	string line1, line2;
	//building the graph
	ifstream myFile;
	myFile.open("web_graph.csv");
		while (myFile.good()) {
		
		getline(myFile, line1,',');
		getline(myFile, line2,',');

		int src =  websites2[line1];
		int dest = websites2[line2];


		my_graph.addEdge(src, dest);
	}
	string full_line;
	map <string , int> impressions_map;
	ifstream impressionFile;
	impressionFile.open("impressions.csv");
		while(impressionFile.good()) {
			getline(impressionFile, full_line);
			stringstream mystream(full_line);
		
			getline(mystream, line1, ',');
			if (line1 == "") break;
			getline(mystream, line2, ',');
		
		
			//stringstream my_stream(line2); 
  
    
    		//int line2_num = 0; 
    		//my_stream >> line2_num; 
			impressions_map[line1] = stoi(line2);
			
		}
		
		
		/*** START READ keywords file ***/
		 vector <vector <string>> data;
  		ifstream keywordFile( "keywords.csv" );



		  while (keywordFile)
		  {
			string s;
			if (!getline( keywordFile, s )) break;

			stringstream ss( s );
			vector <string> record;

			while (ss)
			{
			  string s;
			  if (!getline( ss, s, ',' )) break;
			  record.push_back( s );
			}

			data.push_back( record );
		  }
		  if (!keywordFile.eof())
		  {
			cerr << "\n";
		  }
		  
		
		  
	/*** END READ keywords file ***/
  	

	
	
	
	
	
	/*** START READ website names ***/
		 vector <string> names;
  		ifstream namesFile( "websites_names2.csv" );



		  while (namesFile)
		  {
			string webname;
			if (!getline( namesFile, webname )) break;

			names.push_back(webname);	

			
		  }
		  if (!namesFile.eof())
		  {
			cerr << "\n";
		  }
		  
	/* ALLOCATE websites ojects in the memory */
	Website **container = new Website*[names.size()];
	for (int i = 0; i < names.size(); i++){
		container[i] = new Website();
	}
	

	
	/* POPULATING websites ojects */
	
	vector<string> vector_placeholder;
	for (int i = 0; i < names.size(); i++){
	
			container[i] = new Website[1];
			container[i]->set_url(IdToName[i]);
			container[i]->set_key(websites2[IdToName[i]]);
			container[i]->set_impression(impressions_map[IdToName[i]]);
			container[i]->set_rank(0);
			/* Loop to get keywords vector of the website */
			
	    	for (int j = 0; j < data.size(); j++){
  				for (int k = 0; k < data[j].size(); k++){
  					if (data[j][k] == container[i]->get_url()) {
  						vector_placeholder = data[j];
  					}
  				} 	
			}
			container[i]->set_keywords(vector_placeholder);
			vector_placeholder.clear();
	
	}
	
	//printing website informtion.
	/*
	for (int i = 0; i < names.size(); i++){
		container[i]->printInfo();
	}
	*/
	
		
		
	cout << "Welcome!" << endl;
	cout << "What would you like to search about?" << endl;
	string search;
					
   std::getline(std::cin, search);
  int sign= Search_Signal_Remover(search);
 
vector<string> query = to_vector(search);


vector<string> available_pages=Unsorted_Results(query,data, sign );


//my_graph.print();

calculate_PageRank(container, names.size(), my_graph);

//getting results websites in an array
Website *temp_websites = new Website[4];
int temp_counter = 0;
for (int i = 0; i < names.size(); i++){
	for (int j = 0; j < available_pages.size(); j++){
		if (available_pages[j] == container[i]->get_url()){
		
			temp_websites[temp_counter] = *(container[i]);
			temp_counter++;
			}	
	}
}
//sorting them.

insertion_sort(temp_websites, temp_counter);

reverseArray(temp_websites, temp_counter);

//set min and max rank in the stats object
Stats my_stats;

my_stats.set_max(temp_websites[0].get_rank());
my_stats.set_min(temp_websites[temp_counter-1].get_rank());

//calculate normalized rank

calculate_normalized_rank(temp_websites, my_stats, temp_counter);


//calculate score

for (int i = 0; i < temp_counter; i++){
	temp_websites[i].calculate_score();

}

//display_results
display_results(temp_websites, temp_counter);

//talk to user
talk_to_user(temp_websites, temp_counter);

/*
cout << endl << endl;
for(int i=0;i <available_pages.size(); i++){

    cout<< available_pages[i]<<endl;
    
}
*/





	
	/*

		for (auto itr = IdToName.begin(); itr != IdToName.end(); ++itr) {
	
			cout << itr->first << "  " << itr->second;
		cout << endl;
		}
	*/
	/*
	cout << "What would you like to do?" << endl;
	cout << "1. New Search" << endl;
	cout << "2. Exit" << endl;
	int choice;
	cin >> choice;
	switch (choice) {
		case(1):
			//dsipalying urls
			
			take_user_input(data);

			
			
		
			break;
		case (2):
			exit(0);
			break;
		default:
			cout << "Wrong Input";
	}
	*/
	

	
	
}




//after main
//talk to user
void talk_to_user(Website *temp_websites, int temp_counter){
cout << endl <<"You can either: " << endl;
cout << "1. Choose a webpage to open" << endl;
cout << "2. Exit" << endl;

cout << endl << "Type your choice: ";
int choice;
cin >> choice;

switch(choice){
	case (1):
		cout << endl << "Type the number of the webpage you want to open" << endl;
		cout << "Type your choice: ";
		int page_choice;
		cin  >> page_choice;
		switch(page_choice){
			case (1):
				cout << endl << "You are now viewing " << temp_websites[page_choice - 1].get_url() << endl;
				
				cout << "Would you like to: " << endl;
				cout << "1. Back to search results" << endl;
				cout << "2. New Search" << endl;
				cout << "3. Exit" << endl;
				int choice2;
				cout << endl << "Type your choice: ";
				cin >> choice2;
				switch(choice2){
					case (1):
						display_results(temp_websites, temp_counter);
						talk_to_user(temp_websites, temp_counter);
						break;
					case (2):
						main();
						break;
					case (3):
						cout << "Extiing ...";
						exit(0);
						break;
				}
				break;
			case (2):
				cout << "You are now viewing " << temp_websites[page_choice - 1].get_url() << endl;
				break;
			case (3):
				cout << "You are now viewing " << temp_websites[page_choice - 1].get_url() << endl;
				break;
		}
		
		break;
	case (2):
		cout << "Exiting ... " << endl;
		exit(0);
		break;
	default:
		cout << "Wrong Input" << endl;
		break;
		
}
}
