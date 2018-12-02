//DJIKSTRA'S ALGORITHM 
//
//This is a program that will run Djikstra's algorithm using 
//information from an external file. The External file will 
//include information to be used to build a graph, and then 
//run Djikstra's. Furthermore, we will then check to see if  
//there is a cycle within the graph and print out a cycle  
//if one is found. 

#include "queue.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.h"
#include <cstdlib>
#include <sstream>
#include <vector>
#include <climits>
#include <iomanip>
#include <stack>
#include <set>
using namespace std;

#include "HashTable.h"

//////////////////////////////////////////////////// E X T R A  D E C L A R A T I O N S /////////////////////////////////////////////////////

struct VertexType
{
	string name;
	bool marked;
	int distance;
	string previous;	
};

ostream& operator << (ostream& os, const VertexType& n) 
{ 
	os << "Name: " << n.name << endl; 
	os << "Marked: " << n.marked << endl; 
	os << "Distance: " << n.distance << endl;
	os << "Previous: " << n.previous << endl;  
	return os; 
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////// F U N C T I O N  P R O T O T Y P E S ///////////////////////////////////////////////////

void insertionSort(string cities[], int numVertices);
void checkInFile(int argc, char* argv[]);
void buildDGraph(Graph<string> &dGraph, string filename, string cities[], int &numVertices, int &numEdges, VertexType myVertices[]);
void printCities(Graph<string> dGraph, int numVertices, VertexType myVertices[], string cities[]);
string setStart(string start, int numVertices, VertexType myVertices[]);
void printRow(int location, VertexType myVertices[]);
int findMin(VertexType myVertices[], int numVertices);
void dijkstra(Graph<string> &dGraph, int numVertices, VertexType myVertices[]);
bool allMarked(int numVertices, VertexType myVertices[]);
int getPos( int numVertices, VertexType myVertices[], string begin ); 
bool isCyclic(); 
void DFS( VertexType &startVertex, Graph<string> dGraph, int numVertices, VertexType myVertices[], int flag, vector<string> &path ); 
void printPath( vector<string> path );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	//Clears the screen for the user to begin using the program	
	system("clear"); 

	//Checks to see if the fileName is given 
	checkInFile(argc, argv);	

	// Creation of Input File:
	string filename = argv[1];
    	
	//Construct the graph 
	Graph<string> dGraph; 
	
	//Objects that will be used for the algorithm 
	int numVertices;
	int numEdges = 0;
	VertexType myVertices [50];
	string cities [50];
	
	//Constructs the graph with vertices and edges 
	buildDGraph(dGraph, filename, cities, numVertices, numEdges, myVertices); 
	
	//Prints Cities found in the file 
	printCities(dGraph, numVertices, myVertices, cities);	
	
	//Computes Dijkstra's Algorithm 
	dijkstra(dGraph, numVertices, myVertices);	
}

// Checks to see if Filename is given:
void checkInFile(int argc, char* argv[])
{
    //Checks to see if user input the name of external file 
    if ( argc < 2 )
    {
        cout << "Not enough arguments were presented in command line. \nPlease include filename when calling program. " << endl;
        exit(1);
    }

    //Checks to see if the user input is the correct kind of file 
    string fileTag = ( argv[1] ); 
    fileTag = fileTag.substr( fileTag.length() - 4, 4 ); 
    
    if( fileTag != ".dat" )
	{ 
	    cout << "This is not the correct file extension. \nPlease enter a file with the extension '.dat' " << endl; 
	    exit(1); 
	}    
   cout << endl; 
}


void DFS( VertexType &startVertex, Graph<string> dGraph, int numVertices, VertexType myVertices[], int flag, vector<string> &path ) 
{ 
	//Add startVertex to stack and mark it as visited 
	path.push_back(startVertex.name); 
	startVertex.marked = true; 

	//For every unvisited U vertex adjacent to startingVertex, repeat function 
	//
	//Fill queue with all adjacent queues 
	Queue<string> q; 
	dGraph.GetToVertices( startVertex.name, q ); 

	while( !q.isEmpty() )
	{ 
		//Here, we get the location of the vertex on the myVertices array to access the 
		//	actual vertex structure 
		string qFront = q.getFront(); 
		int location = getPos( numVertices, myVertices, qFront ); 
		
		//If the vertex has not been marked, repeat the DFS function 
		if( myVertices[ location ].marked == false ) 
			DFS(myVertices[ location ], dGraph, numVertices, myVertices, flag, path ); 

		//If we run into the original startingVertex, then insert a "BREAK' 
		//into the vector so we know a cycle has been found when printing the 
		//path 
		if( q.getFront() == myVertices[ flag ].name ) 
		{ 
			path.push_back( "BREAK" ); 
			break; 
		}

		q.dequeue(); 
	}//End of while loop
}//End of DSF--  


void printPath( vector<string> path )
{ 
	bool isCycle = false; 

	//Check to see if there are any cycle indicators in the paths found in the vector 
	for( int x = 0; x < path.size(); x++ ) 
		if( path[x] == "BREAK" ) 
			isCycle = true; 

	//If there is a cycle found, then print that path 
	if( isCycle == true ) 
          cout << "\n\n\tThe user selected starting point is a part of a cycle in the graph!" << endl; 
	else 
	  cout << "\n\n\tThe user selected starting point is not a part of a cycle in this graph " << endl; 

	cout << "===================================================================================\n" << endl; 
	
	if( isCycle == true ) 
	{ 
		//Printing the path 
		for( int x = 0; x < path.size(); x++ ) 
		{ 
			//Once we arrive to the cycle indicator, break out of the path printing 
			if( path[x] == "BREAK" ) 
				break; 
			else 
				cout << path[x] << endl; 
			
			cout << setw(3) << " |\n" << setw(3) << " |\n" << setw(3) << "  -->";
	
		}//End for loop 
		
		//Finally, printing the original vertex we have found the path to 
		cout << path[0] << endl; 
		cout << endl; 

	}//End second if statement 

}//End printPath-- 

// Computes Dijkstra's Algorithm:
void dijkstra(Graph<string> &dGraph, int numVertices, VertexType myVertices[])
{
	//String objects we will be using for the algorithm 
	string begin; 
	string userChoice = setStart( begin, numVertices, myVertices );   
	 
	//Decorative line 
	cout << "===================================================================================\n" << endl; 
	
	//Get the index of the first vertex and set it equal to the int variable 
	int firstVert = getPos( numVertices, myVertices, userChoice ) ; 
	
	//This will be used for later when finding if the graph is cyclic 
 	int originalPos = firstVert; 

	//Flush the first vertex 
	myVertices[ firstVert ].previous = "N/A"; 
	myVertices[ firstVert ].marked = true; 
	myVertices[ firstVert ].distance = 0; 

	//Queue used for the algorithm 
	Queue<string> links; 
	
	//Print the table headers 
	cout << setw(17) << "Vertex" << setw(17) << "Distance" << setw(17) << "Previous\n" << endl; 
	printRow( firstVert, myVertices ); 

	//Run the algorithm until all are marked 
	while( !allMarked( numVertices, myVertices ) )
	{
		dGraph.GetToVertices( myVertices[ firstVert ].name, links ); 
		while( !( links.isEmpty() ) )
		{ 
			string destination = links.dequeue(); 

			int secondVert = getPos( numVertices, myVertices, destination ); 
			int length = dGraph.WeightIs( myVertices[ firstVert ].name, destination ) + myVertices[ firstVert ].distance; 

			if( myVertices[ secondVert ].distance > length )
			{ 
				myVertices[ secondVert ].distance = length; 
				myVertices[ secondVert ].previous = myVertices[ firstVert ].name; 

			}
	}//End of the inner while loop 

	//Looks for the min vertex to continue through the algorithm 
	firstVert = findMin( myVertices, numVertices ); 

	if( firstVert == -1 )
	{ 
		for( int x = 0; x < numVertices; x++ )
		{ 
			if( !myVertices[x].marked )
				cout << setw(14) << myVertices[x].name << setw(22) << "Not on path" << setw(12) << "N/A" << endl; 
		}

		break; 
	}

	myVertices[ firstVert ].marked = true; 
	printRow( firstVert, myVertices ); 

      }//End of outer while loop 

	//Since our function depends on going through the vertices and marking them, 
	//  we have to clear them in order for it to work
	for( int x = 0; x < numVertices; x++ ) 
		myVertices[x].marked = false; 

	//Find if the graph is cyclic, and if it is, print that path 
	vector<string> path; 
	DFS( myVertices[ originalPos ], dGraph, numVertices, myVertices, originalPos, path ); 
	printPath(path); 

}//End dijkstra--  

// Checks to see if all Vertices have been marked:
bool allMarked(int numVertices, VertexType myVertices[])
{ 
	//Goes through all vertices. If a single one is not marked,  
	//	then all cannot be marked so we return false 
	for( int x = 0; x < numVertices; x++ )
	{ 
		if( !myVertices[x].marked ) 
			return false; 
	}

	return true;
}

// Builds the Graph using the data from the External File:
void buildDGraph(Graph<string> &dGraph, string filename, string cities[], int &numVertices, int &numEdges, VertexType myVertices[])
{
    //Open the file
    ifstream file( filename.c_str() );
    
    //Create hashtable for duplicates
    const string NOT_FOUND = "ZZZ";
    HashTable<string> CitiesH(NOT_FOUND, 50);
    
    //string that will be used for temporary storage
    string tmp;
    
    //Vector used for storing individual lines of file
    vector<string> lines;
    
    //Stringstream used for parsing
    istringstream ss( tmp );
    
    //Get all the lines from file
    while (getline( file, tmp, '\n'))
        lines.push_back(tmp);
    
    //Vector to hold the specific elements that will go into the vertex
    vector<string> v_info;
    
    //This for loop will take each line and break it up into specific elements
    for( int pos = 0; pos < lines.size(); pos++ )
    {
        stringstream nodeSS( lines[ pos ] );
        
        while( getline( nodeSS, tmp, ';') )
            v_info.push_back( tmp );
    }
    
    //Create vertices to add to the array
    for( int p = 0; p < v_info.size(); p++ )
    {
        //Attributes of the given vertex
        string city = v_info[p];  
        string destination = v_info[p+1];
        int distance = atoi( (v_info[p+2]).c_str() );
        
        //Builds the graph
        //
        //Add Vertex one if it is not in the hashtable 
	
	if((CitiesH.find( city )) != city)
	{
		//Update our data structures with the new vertex 
		dGraph.AddVertex( city ); 
		CitiesH.insert( city ); 
		cities[ numVertices ] = city;
		
		//Set vertex information 
		myVertices[ numVertices ].name = city; 
		myVertices[ numVertices ].distance = INT_MAX; 
		myVertices[ numVertices ].previous = "N/A"; 
		myVertices[ numVertices ].marked = false; 
	
		//Increase numVertices 
		numVertices++;
	}
	
	//Add vertex two if it is not in the hashtable  
	if(( CitiesH.find( destination )) != destination)
        { 
		//Update our data structures with the new vertex 
		dGraph.AddVertex( destination ); 
		CitiesH.insert( destination ); 
		cities[ numVertices ] = destination;
 
		//Set vertex information 
		myVertices[ numVertices ].name = destination; 	
		myVertices[ numVertices ].distance = INT_MAX; 	
		myVertices[ numVertices ].previous = "N/A"; 	
		myVertices[ numVertices ].marked = false; 	
		
		//Increase numVertices 
		numVertices++;
	}

	//Add the edge between the two vertices 
        dGraph.AddEdge(city, destination, distance);
	numEdges++; 

        //Moves the vector positioning onto the next vertex
        p+=2;

        }

}//End buildGraph

// Prints Cities found in External File:
void printCities(Graph<string> dGraph, int numVertices, VertexType myVertices[], string cities[])
{ 
	cout << "\n====================================================================================\n" << endl; 
	cout << "====================== D I J K S T R A ' S  A L G O R I T H M ======================" << endl; 
	cout << "\n====================================================================================\n" << endl; 
	cout << endl; 

	insertionSort( cities, numVertices ); 

	for( int x = 0; x < numVertices; x++ )
	{ 

		cout << setw(21) << cities[ x ] << "\t"; 
		if( ( x+1 ) % 3 == 0 )
			cout << endl; 

	}

	cout << "\n\n"; 

}//End printCities--

// Sorts the Cities Alphabetically:
void insertionSort(string cities[], int numVertices)
{
    for( int pos = 1; pos < numVertices; pos++ )
    {
        string tmp = cities[ pos ];
        
        int j;
        for( j = pos; j > 0 && tmp < cities[ j -1 ]; j-- )
            cities[ j ] = cities[ j -1 ];
        
        cities[ j ] = tmp;
    }
}//End insertionSort-- 

//Sets the Starting Value in Dijsktra's Algorithm:
string setStart(string start, int numVertices, VertexType myVertices[])
{
	cout << " Please input your starting vertex: ";
	string response;
	getline(cin,response);
	bool isThere = false;
	for (int i = 0;	i < numVertices; i++)
	{
		if (myVertices[i].name.compare(response) == 0)
		{
			start = response;
			return start;
		}
	}
	while (!isThere)
	{
		cout << " Starting location does not exist..." << endl;
		cout << " Please input your new vertex: ";
        	string response;
        	cin >> response;
		for (int i = 0; i < numVertices; i++)
        	{
                	if (myVertices[i].name.compare(response) == 0)
                    {
                        	start = response;
                        	return start;
                	}
        	}
	}
}//End setStart-- 

// Finds the minimum non-marked values in VertexType Array:
int findMin(VertexType myVertices[], int numVertices)
{
 		int minWeight = INT_MAX - 1;
                int minThing = -1;
		for (int i = 0; i < numVertices; i++)
                {
                        if (myVertices[i].distance < minWeight && !myVertices[i].marked)
                        {
                                minWeight = myVertices[i].distance;
                                minThing = i;
                        }
			else if (myVertices[i].distance == minWeight && !myVertices[i].marked)
                        {
                                minWeight = myVertices[i].distance;
                                minThing = i;
                        }

		}        
		return minThing;
}//End printRow 

// Prints a given row in a Summary Table:
void printRow(int location, VertexType myVertices[])
{
	if (myVertices[location].distance != -1)
	cout << setw(14) << myVertices[location].name << setw(18) << myVertices[location].distance << setw(16) << myVertices[location].previous << endl;
	else
	 cout << setw(14) << myVertices[location].name << setw(18) << "Not On Path" << setw(16) << myVertices[location].previous << endl;
}//End printrow-- 

//Function that will return where in the vertex array a city is located 
int getPos( int numVertices, VertexType myVertices[], string begin )
{ 
	int pos = INT_MAX; 

	for( int x = 0; x < numVertices; x++ ) 
	{ 
		if( myVertices[x].name == begin )
			pos = x; 
	} 

	return pos; 
}//end getPos--




