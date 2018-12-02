//Scratch
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <fstream> 
using namespace std;

/////////////////  D E F I N I T I O N S /////////////////
//Definition of the struct
struct node
{
    string origin;
    string destination;
    int trip_length;
};

//Operator overloading
ostream& operator << (ostream& os, const node& n)
{
    os << "Origin: " << n.origin << endl;
    os << "Destination: " << n.destination << endl;
    os << "Trip Length: " << n.trip_length << endl;
    return os;
}
//////////////////////////////////////////////////////////

vector<node> breakup(string filename);


int main()
{
    //Simulation object
    string line = "Washington;Atlanta;300\nDallas;Vancouver;729\nDouglasville;New York;1002";

    //Tmp: for use until we add the command line entries 
    string filename = "ginfile1.dat"; 

    vector<node> node_list = breakup( filename );
    
    for( int x = 0; x < node_list.size(); x++ )
    {
        cout << node_list[x] << endl;
    }
    
    
   
    
    
    
    
    return 0;
}

vector<node> breakup(string filename)
{
   //Open up the filestream 
   ifstream file( filename.c_str() ); 

    //A string we will be using to push onto the vector
    string container;
   
    //String object to store all tokens
    vector<string> tokens;
    
    //Creates the 'table' from the file
    vector<node> results;
    
    //SS for getting the string parsed
    istringstream ss( container ); 
    
    //Get all the lines from file and make a vector of all the lines 
    while( getline( file, container, '\n'))
        tokens.push_back( container );
    
    //Vector to hold the specific elements that will go into the node
    vector<string> node_info;
    
    //This for loop will take each line and break it up into specific elements
    for( int pos = 0; pos < tokens.size(); pos++ )
    {
        stringstream nodeSS( tokens[ pos ] );
        
        while( getline( nodeSS, container, ';') )
            node_info.push_back( container );
    }
    
    //This for loop will create nodes with the lines and put them into a new vector
    for( int x = 0; x < node_info.size() ; x++ )
    {
        node new_node;
        
        new_node.origin = node_info[x];
        new_node.destination = node_info[x+1];
        new_node.trip_length = atoi( ( node_info[x+2] ).c_str() );
        
        results.push_back( new_node );
        x += 2;
    }
    
    //Return a vector of loaded nodes
    return results;
}


