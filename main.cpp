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
using namespace std;


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
      
//std::find(all_data[j].begin(), all_data[j].end(),query[k])!=all_data[j].end()
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

/*
printVector2D(std::vector <std::vector<string>> data){
		    	for (int i = 0; i < data.size(); i++){
  	
  		for (int j = 0; j < data[i].size(); j++){
  			cout << data[i][j] << endl;
  		} 	
	}
}
printVector1D(std::vector<string> my_vector){
	for (int i = 0; i < my_vector.size(); i++){
		cout << my_vector[i] << endl;
	}
}
*/
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
			display_urls(names.size(), container);
			
			
		
			break;
		case (2):
			exit(0);
			break;
		default:
			cout << "Wrong Input";
	}
	*/
	
	string search;
   std::getline(std::cin, search);
  int sign= Search_Signal_Remover(search);
 
vector<string> query= to_vector(search);





vector<string> available_pages=Unsorted_Results(query,data, sign );




for(int i=0;i <available_pages.size(); i++){
    
    cout<< available_pages[i]<<endl;
    
}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
