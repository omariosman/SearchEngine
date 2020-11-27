#include "Graph.h"



Graph::Graph(int size) {

	numofvert = size;

	adjmat = new int* [size];

	for (int i = 0; i < size; i++) 

		adjmat[i] = new int[size];



	for (int i = 0; i < size; i++)

		for (int j = 0; j < size; j++)

			adjmat[i][j] = 0;



}

/*

Graph::~Graph() {



	for (int i = 0; i < numofvert; i++)

		delete[] adjmat[i];



	delete [] adjmat;



}

*/

void Graph::addEdge(int source, int destination){



	if (source >= 0 && source < numofvert && destination >= 0 && destination < numofvert)

		adjmat [source][destination] = 1;



}





void Graph::addEdge(edge myedge){



	if (myedge.source >= 0 && myedge.source < numofvert && myedge.destination >= 0 && myedge.destination < numofvert)

		adjmat[myedge.source][myedge.destination] = 1;



}





void Graph::addWeightedEdge(int source, int destination, int weight) {



	if (source >= 0 && source < numofvert && destination >= 0 && destination < numofvert)

		adjmat[source][destination] = weight;



}



void Graph::deleteEdge(int source, int destination) {



	if (source >= 0 && source < numofvert && destination >= 0 && destination < numofvert)

		adjmat[source][destination] = 0;





}





void Graph::deleteEdge(edge myedge) {

	if (myedge.source >= 0 && myedge.source < numofvert && myedge.destination >= 0 && myedge.destination < numofvert)

		adjmat[myedge.source][myedge.destination] = 0;





}



int Graph::sumOfLags() {

	int sum = 0;

	

	for (int i = 0; i < numofvert; i++) {

		for (int j = 0; j < numofvert; j++)

			sum = sum + adjmat[i][j];

	}





	return sum;

}



int Graph::getweight(int source, int destination) {



	return adjmat[source][destination];

}



int Graph::getweight(edge myedge){

	return adjmat[myedge.source][myedge.destination];

}



void Graph::addWeightedEdge(edge myedge, int weight){



	if (myedge.source >= 0 && myedge.source < numofvert && myedge.destination >= 0 && myedge.destination < numofvert)

		adjmat[myedge.source][myedge.destination] = weight;



}



bool Graph::checkAndDelete(int source, int destination, int weight) {

	

	for (int i = 0; i < numofvert; i++) {

		for (int j = 0; j < numofvert; j++) {

			if (adjmat[i][j] > weight)

			{

				deleteEdge(i, j);

				addEdge({source,destination});

				if (isAllconnected())

					return true;



			}



		}



	}



	return false;





}







int Graph::getNumberOfIncomingEdges(int vertex){



	if (vertex < numofvert && vertex >= 0) {

		

		int count(0);

		for (int i = 0; i < numofvert; i++) {

			if (adjmat[i][vertex] > 0)

				count++;



		}

		return count;

	}



	return -1;





}





int Graph::getNumberOfOutgoingEdges(int vertex){



	if (vertex < numofvert && vertex >= 0) {



		int count(0);

		for (int i = 0; i < numofvert; i++) {

			if (adjmat[vertex][i] > 0)

				count++;

		}



		return count;

	}



	return -1;



}



bool Graph::isAllconnected() {

	



	for (int i = 0; i < numofvert; i++) {

		for (int j = 0; j < numofvert; j++) {

			if (!isConnected(i))

				return false;

		}

	}



	return true;





}





vector<int> Graph::getIncomingNodes(int vertex){

	vector<int> res;

for (int i=0;i<numofvert;i++)

	if (adjmat[i][vertex]==1)

		res.push_back(i);





return res;





}





bool Graph ::isConnected(int vertex) {



	for (int i = 0; i < numofvert; i++) {

		if (adjmat[vertex][i] != 0)

			return true;

	}



	return false;



}



void Graph::DFSRec(int vertex, vector<bool>& visited) {



	if (visited[vertex] == true)

		return;

	visited[vertex] = true;

	cout << vertex << " ";



	for (int i = 0; i < numofvert; i++) {

		

		if (adjmat[vertex][i] > 0)

			DFSRec(i,visited);



	}







}



void Graph::DFS(){

	

	vector<bool> visited;

	visited.resize(numofvert, false);

	for (int i = 0; i < numofvert; i++)

		if (isConnected(i))

			DFSRec(i, visited);



}





void Graph::BFS(){



	vector <bool> visited;

	visited.resize(numofvert);



	for (int i = 0; i < numofvert; i++) {



		if (isConnected(i)) {

			if (visited[i] == false) {

				cout << i << " ";

				visited[i] = true;



				for (int j = 0; j < numofvert; j++) {



					if (adjmat[i][j] > 0) {



						if (visited[j] == false) {



							cout << j << " ";

							visited[j] = true;

						}

					}



				}





			}



		}



	}







}





void Graph::print(){

	

	for (int i = 0; i < numofvert; i++) {

	

		if (isConnected(i))

			

			for (int j = 0; j < numofvert; j++) {

			

				if (adjmat[i][j]>0)

					cout << "Source: " << i << "    "<< "Destination: "<< j<<endl;

		

			}





	}







}



void Graph::printWithWeights() {

	for (int i = 0; i < numofvert; i++) {



		if (isConnected(i))



			for (int j = 0; j < numofvert; j++) {



				if (adjmat[i][j] > 0)

					cout << "Source: " << i << "    " << "Destination: " << j << "    " <<"Weight: "<< adjmat[i][j]<< endl;



			}





	}





}
