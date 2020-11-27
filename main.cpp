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
	for (int i = 0; i < names.size(); i++){
		container[i]->printInfo();
	}
	
	/*
	for (int i = 0; i < names.size(); i++){
		container[i].set_url();
	}
	*/
	/*** END READ website names ***/
	

 /**** CREATING OBJECTS *****/
 


 
				
		
		
		
		
	
	/*

		for (auto itr = IdToName.begin(); itr != IdToName.end(); ++itr) {
	
			cout << itr->first << "  " << itr->second;
		cout << endl;
		}
	*/
	
	
}
