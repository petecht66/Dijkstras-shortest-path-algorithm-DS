#include "Dijkstra.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

Dijkstra::Dijkstra(string fname) {
	readFile(fname);
	Interface();
    	runDijkstra();
    	printPath();
}

// WRITE THIS (10 pts)
void Dijkstra::runDijkstra(){
	distances[start] = 0; //distance to start is 0
	visited[start] = true; //starting vertex is visited

	int maxInt = INT_MAX; //create a maximum integer
	for (int i = 0; i < numOfCities; i++) { //loop through all cities
		distances[i] = matrixGraph[start][i]; //initialize the distances of going to each node
		if (matrixGraph[start][i] != maxInt && i != start) { //if not at starting index
			prev[i] = start; //set previous equal to start
		}
	}

	printInfoSoFar(); //printInfo to see starting arrays
	for (int count = 0; count < numOfCities - 1; count++) {
		int minDist = minDistance(); //use minDistance to find next unvisited matrix
		visited[minDist] = true;

		setDistances(minDist); //use setDistances to update distances for unvisited vertices
		printInfoSoFar(); //use printInfoSoFar to see all updates through process
	}
}

//WRITE THIS (12 pts)
void Dijkstra::setDistances(int latestVert) {
	int maxInt = INT_MAX; //define maximum integer
	for (int v = 0; v < numOfCities; v++) { //iterates through all cities
		if (visited[v]==false && matrixGraph[latestVert][v] != maxInt) { //checks if city hasn't been visited or if there is no valid edge
			int newDistance = distances[latestVert] + matrixGraph[latestVert][v]; //calculates new distance
			if (newDistance < distances[v]) { //if new distance is shorter
				distances[v] = newDistance; //sets new shortest distance in distances array
				prev[v] = latestVert; //update the previous array
			}
		}
	}
}

//WRITE THIS (8pts)
int Dijkstra::minDistance(){
	int minValue = INT_MAX; //create a minValue integer
	int minIndex = -1; //minIndex is -1

	for (int i = 0; i < numOfCities; i++) { //iterate through all cities
		if (visited[i]==false && distances[i] < minValue) { //if unvisited and distance is less than minValue
			minValue = distances[i]; //minValue is now changed
			minIndex = i; //minIndex is set equal to i
		}
	}

	visited[minIndex] = true; //set value in visited array at this index to true
	return minIndex; //return the index
}



//WRITE THIS (12 pts)
void Dijkstra::printPath() {
	int *p = new int[numOfCities]; //new array
	int x = 0;
	int currCity = end; //set current to end
	while (currCity != start) { //work backward to fill array
		p[x] = currCity;
		currCity = prev[currCity];
		x++; //increment x
	}
	cout << Cities[start] << "->"; //write first city
	for (int i = x - 1; i >= 0; i--) {
		cout << Cities[p[i]]; //output each city
		if (i != 0 ) {
			cout << "->"; //output an arrow if not the end
		}
	}
	cout << endl; //output end line
	delete p; //delete array
}


// A utility function to print the constructed distance array
void Dijkstra::printMatrix() {
	cout <<"********************************************" << endl << "Adjacency Matrix (of Cities and Distances):"<<endl;
	for (int i = 0; i< numOfCities;i++) {
		for (int j = 0; j < numOfCities; j++) {
			cout << matrixGraph[i][j] << "\t";
		}
		cout << endl;
	}
	cout <<"********************************************" << endl;
}

//Another utility method to print out the different arrays so far
//so you can see their content
void Dijkstra::printInfoSoFar() {
	cout <<"\t";
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t"<<i;
	}
	cout << endl;
	cout << "Dist:\t";
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t"<<distances[i];
	}
	cout << endl;
	cout << "Prev:\t";
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t"<<prev[i];
	}
	cout << endl;
	cout << "Visited:";
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t"<<visited[i];
	}
	cout << endl;
	cout << endl;
}





/*************************************************************/
/* This is the user interface that allows you to choose your 
/* start and end city you're traveling through.  You should not
/* need to touch this.
/*************************************************************/
void Dijkstra::Interface() {
	cout << "Choose from the following: "<<endl;
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t" << i << ": " << Cities[i] << endl;
	}
	cout << endl;
	cout << "Choose your starting city (with the city's corresponding number"<<endl;
	cin >> start;
	cout << "Choose your end destination (with the city's corresponding number"<< endl;
	cin >> end;
}

/*************************************************************/
/* This method reads in the different Map files and initializes 
/* all your arrays along with the adjacency matrix.  It
/* initializes the following:
/*
/* numOfCities: the number of cities in the adjacency matrix
/*
/* Cities: an array filled with the list of cities - the index in 
/* the array is the number corresponding with each city (which 
/* can be utilized when printing out the path
/* 
/* visited: set to false for all cities (indices) to start
/*
/* prev: set to -1 (aka no previous city) for each index to start
/*
/* distance: set to a really large number for all indices to 
/* start
/*
/* matrixGraph: this is your adjacency matrix that holds the 
/* distance from each city to each city.  It is initialized in 
/* here with values read in from the different Map***.txt files
/*
/* If you want to make sure you're reading in your files 
/* correctly (aka make sure the files are in the correct place),
/* there are a number of print statements in here you can 
/* uncomment out.  Otherwise You should not need to touch this.
/*************************************************************/
void Dijkstra::readFile(string fn) {
	ifstream file(fn.c_str());
	int numcities;
	file>>numcities;
	//cout << numcities<<endl;
	numOfCities = numcities;
	Cities = new string[numOfCities];
	visited = new bool[numOfCities];
	prev = new int[numOfCities];
	distances = new int[numOfCities];
	matrixGraph = new int*[numOfCities];
	for (int i = 0; i < numOfCities; i++) {
		matrixGraph[i] = new int[numOfCities];
        distances[i] = 100000;
    	visited[i] = false;
    	prev[i] = -1;
	}
	string abbr;
	string city;
	string abbrCity;
	for (int i = 0; i < numOfCities; i++) {
		file >> abbr;
		file >> city;
		abbrCity = abbr + " "+city;
		//cout << abbrCity << ", ";
		Cities[i] = abbrCity;
	}
	//cout << endl;
	for (int ct = 0; ct < numOfCities; ct++)  {
		file >> abbr;
		//cout << abbr << ", ";
		file>>city;
		//cout << city << ": ";
		for (int i = 0; i < numOfCities; i++) {
			int x;
			file >> x;
			//cout << x << ", ";
			if (x == -1) {
				matrixGraph[ct][i] = 100000;
			}
			else matrixGraph[ct][i] = x;
		}
		//cout << endl;
	}
	//cout << "here" << endl;
    printMatrix();
	return;
}







