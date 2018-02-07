/*******************************************************************************************
* Programmer: Noah Taylor                                                               *
* Class: CptS 122, Fall  2017; Lab Section 7                                           *
* Programming Assignment: PA3                                      *
* Date: September 21, 2017
* Contributers: Stack exchange for suggesting fgets and Windows.h but no actual code
* Description: The program reads inputs from csv file containing song data and puts the data into a
* doubly linked lists and allows the user to edit rate play insert delete shuffle sort and restore the info into the csv file
* in the same format
*******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
typedef enum boolean
{
	FALS, TRU
} Boolean;

typedef struct duration {
	int minutes;
	int seconds;
}Duration;

typedef struct record {
	char artist[100];
	char albumTitle[100];
	char songTitle[100];
	char genre[20];
	Duration duration;
	int timesPlayed;
	int rating;
}Record;

typedef struct node {
	Record info;
	struct node* pNext;
	struct node* pPrev;
}Node;
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: makeNode
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes in a Record and stores the data into a node and returns a pointer to that node
* Prereq: The Record must not be null
* Postreq: A node is created with the records data
*******************************************************************************************/
Node * makeNode(Record data);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: insertFront
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes in a Record and the List that we will be manipulating and it creates a
* node using makeNode and inserts it into the front of our doubly linked list
* Prereq: The Record must not be NULL
* Postreq: A node is created with the records data from make Node and that node is added to the front of our list
*******************************************************************************************/
Boolean insertFront(Node **pList, Record newData);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: searchList
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes our list and finds a specific node using user input
* Prereq: The List must be loaded 
* Postreq: A pointer to the user specified node is found and returned
*******************************************************************************************/
Node* searchList(Node* pList);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: displayMenu
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function displays our users menu
* Prereq: none
* Postreq: the menu is displayed
*******************************************************************************************/
void displayMenu(void);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: getSongInfo
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes in a line from the csv file and formats it and places the data into a record
* Prereq: load must be selected
* Postreq: a record stores the data of the song
*******************************************************************************************/
void getSongInfo(char* string, Record* songData);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: storeFiles
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes in a inFile and our linked list and reformats all the data and stores it back to the csv file
* Prereq: The linked list had to be loaded
* Postreq: our csv file stores the contents of the list in the original format 
*******************************************************************************************/
void storeFiles(FILE* infile, Node* pList);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: displayRecords
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function uses our searchList function to find and display the contents of a song or the
* contents of all the songs
* Prereq: The linked list has to be loaded
* Postreq: Displays all or a certain songs info
*******************************************************************************************/
void displayRecords(Node* pList);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: editRecord
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes in our list and uses our searchList function to find a song
* then allows the user to change the contents of the record.
* Prereq: our list has to be loaded
* Postreq: the node is altered
*******************************************************************************************/
void editRecord(Node* pList);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: rateRecord
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes our list and displays all the songs and lets the user chose the song and rating for the song
* Prereq: list needs to be loaded
* Postreq: the songs rating changes
*******************************************************************************************/
void rateRecord(Node* pList, int length);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: printList
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes in the list and prints its contents 
* Prereq: The list needs to be loaded
* Postreq: our list is displayed
*******************************************************************************************/
void printList(Node* pList);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: playSong
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes in our list and lets the user see the data of all the songs
* for a short amount of time from either all the songs or from a certain song to the end
* Prereq: the list needs to be loaded
* Postreq: the data of the songs are displayed until the end is reached
*******************************************************************************************/
void playSongs(Node* pList);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: getRecord
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 21, 2017                                                                      *
* Description: This function has the user input new data and stores it into a record
* Prereq: a Record pointer must exists 
* Postreq: the record is full of user inputed data
*******************************************************************************************/
void getRecord(Record* data);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: sortRecords
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 21, 2017                                                                      *
* Description: The user has a choice to sort the list in 1 of 4 ways
* Prereq: the list needs to be loaded
* Postreq: the list is sorted
*******************************************************************************************/
Boolean sortRecords(Node *pList);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: deleteRecord
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 21, 2017                                                                      *
* Description: The user selects a record using the search function and the record is removed from the list
* Prereq: the list needs to be loaded
* Postreq: the item is deleted from the list
*******************************************************************************************/
void deleteRecord(Node**pList, Node* pDel);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: random
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 21, 2017                                                                      *
* Description:  A random integer from 0 to the length of the list -1 is returned
* Prereq: none
* Postreq:  A random integer from 0 to the length of the list -1 is returned
*******************************************************************************************/
int random(int length);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: bubbleSwap
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 21, 2017                                                                      *
* Description: an array is passed through and the contents that are not equal to zero are randomly
* re ordered
* Prereq: the array needs to be initilized
* Postreq:  the array is randomized
*******************************************************************************************/
void bubbleSwap(int arr[], int length);
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: shuffle
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 21, 2017                                                                      *
* Description:  The contents of each song is displayed to the user at random
* Prereq: the list needs to be loaded and the array in the function needs to be reorders
* Postreq:  the contents are displayed at random
*******************************************************************************************/
void shuffle(Node* pList);