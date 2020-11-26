#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include <bits/stdc++.h>
#include<stdio.h>
#include "Graph.h"
#include "Website.h"
using namespace std;



int main() {


	map <string, int> websites2; 
	ifstream newFile;
	newFile.open("websites_names.csv");
	int new_value = 0;
	while (newFile.good()) {
		string new_line;
		getline(newFile, new_line, ',');
		websites2[new_line] = new_value;
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
			cout << "line1: " << line1 << endl;
			cout << "line2: " << line2 << endl;
		
			//stringstream my_stream(line2); 
  
    
    		//int line2_num = 0; 
    		//my_stream >> line2_num; 
			impressions_map[line1] = stoi(line2);
			
		}
	
	


		for (auto itr = impressions_map.begin(); itr != impressions_map.end(); ++itr) {
		cout << "here" << "   ";
			cout << itr->first << "  " << itr->second;
		cout << endl;
		}
		
	
	
}
