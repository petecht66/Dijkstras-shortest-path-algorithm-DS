/*
 * graphMain.cpp
 *
 *  Created on: May 6, 2022
 *      Author: 13027
 */



#include "Dijkstra.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main() {
 	Dijkstra("MapSmaller.txt"); //1 as start, 7 as end
	Dijkstra("MapSmaller.txt"); //0 as start, 4 as end
	Dijkstra("MapSmaller.txt"); //6 as start, 2 as end


	Dijkstra("MapSmall.txt"); //0 as start, 6 as end
	Dijkstra("MapSmall.txt"); //0 as start, 14 as end
	Dijkstra("MapSmall.txt"); //13 as start, 2 as end


	Dijkstra("MapLrg.txt"); //4 as start, 34 as end
	Dijkstra("MapLrg.txt"); //5 as start, 36 as end
	Dijkstra("MapLrg.txt"); //24 as start, 14 as end
}

