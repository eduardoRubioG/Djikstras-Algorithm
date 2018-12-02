Djikstra's Algorithm 

Written by Eduardo Rubio 
-------------------------------------------------------------------------------------------------------------------------------
PROGRAM SUMMARY:  
---------------

This program will allow the user to input a file with outlined vertices. The program will then prompt the user to select a 
vertices in order to print out of a summary of all the vertices connected to the connected vertex. 

READING FROM THE INPUT FILE: 
--------------------------- 

We will be accessing the input file by opening up a filestream. We will also need to make sure we use a semi-colon as a delimiter. 
Since the user will need to type in the vertex of choice by name, we should write a function to convert strings to lowercase so 
that user inputs become case-insensitive. 

DJIKSTRA'S ALGORITHM: 
--------------------- 

1) Declare an int variable to keep track of how many vertices will be input 
2) Create struct for all the vertices. We can now essentially build an array of vertices.  
   The structs will include: 
	-Name
	-Boolean to represent whether the vertex has been visited 
	-Integers representing the total distance traveled 
	-String to indicate previous vertex 
3) Select starting vertex and flush its distance to 0. Print out the data with "N/A" as previous vertex 
4) Find adjacent vertices using function >GetToVertices< 
5) For each adjacent vertex, find the weight value between all -> current vertex. If distance for one is 
     greeater than weight of previous vertex plus distane within the table, then reset its distance value 
     to this smaller sum. Store the name of current vertex as the previous vertex of each adjacent vertex. 
6) Find min distance among all unmarked and set the vertex correspoding to the min distance as new current. 
   Then, mark it. 
7) Print out struct of current vertex 
8) Repeat 4-7 until all are marked 

Suggested: Do NOT write this all out as one function. Break it up into smaller functions. 
Suggested function allocations: 
	-Finding the index value of a given string in your array of strings 
	-Initialize your array 
	-Print given row in your summary table 	
	-Finding min value among your unmarked vertices 
	-Determining whether a string entered by user is a valid vertex 

CLASSES: 
-------- 

djikstra.cpp --> This file will the be where all the functions behind the algorithm will go 
graph.cpp    --> This file will be used for all the graph functions we may need within the implementation 
			of the program 
HashTable.cpp--> This file will contain the coding for a HashTable. We will be using a HashTable for quickly 
			being able to find our vertices as well as being able to determing if a vertex is marked 
LinkedList.cpp-> This is included for the implementation of the HashTable 
Queue.cpp    --> Queue is needed because we need some more specific and unique functionalities that the standard Queue 
			does not carry. This will be heavily used for the algorithm 
