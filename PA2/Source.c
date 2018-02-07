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
#include "Source.h"
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: displayMenu
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function displays our users menu
* Prereq: none
* Postreq: the menu is displayed
*******************************************************************************************/
void displayMenu(void) {
	printf("(1)  load\n");
	printf("(2)  store\n");
	printf("(3)  display\n");
	printf("(4)  insert\n");
	printf("(5)  delete\n");
	printf("(6)  edit\n");
	printf("(7)  sort\n");
	printf("(8)  rate\n");
	printf("(9)  play\n");
	printf("(10) shuffle\n");
	printf("(11) exit\n");
	printf("\n Please enter an option: \n");
}
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: makeNode
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes in a Record and stores the data into a node and returns a pointer to that node
* Prereq: The Record must not be null
* Postreq: A node is created with the records data
*******************************************************************************************/
Node * makeNode(Record data) {
	Node * pNode = NULL;
	pNode = (Node*)malloc(sizeof(Node));
	if (pNode != NULL) {
		pNode->pNext = NULL;
		pNode->pPrev = NULL;
		pNode->info = data;
		return pNode;
	}
}
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
Boolean insertFront(Node **pList, Record newData) {
	Node* pNode = NULL, *pCur = NULL;
	Boolean success = FALSE;
	pCur = *pList;
	pNode = makeNode(newData);
	if (pNode != NULL) {
		success = TRUE;
		pNode->pNext = pCur;
		if (pCur != NULL) {
			pCur->pPrev = pNode;
		}
		*pList = pNode;
	}
	return success;
}
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: getSongInfo
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes in a line from the csv file and formats it and places the data into a record
* Prereq: load must be selected
* Postreq: a record stores the data of the song
*******************************************************************************************/
void getSongInfo(char* string, Record* songData) {
	int index = 0, var = 0, n = 0, x = 0;
	char name[100] = "", firstName[100] = "", lastName[100] = "", copyLine[150] = "", finalName[100] = "";
	strcpy(copyLine, string);
	if (string) {
		if (string[0] == '\"') {
			copyLine[0] = ' ';
			strcpy(lastName, strtok(copyLine, ","));
			strcpy(firstName, strtok(NULL, "\""));
			strcat(name, firstName);
			//strcat(name, " ");
			strcat(name, lastName);
			for (n = 1; n < strlen(name); n++) {
				finalName[x] = name[n];
				x++;
			}
			strcpy(songData->artist, finalName);//name used for artist name
		}
		else {// No double quote names
			strcpy(name, strtok(copyLine, ","));
			strcpy(songData->artist, name);
		}
		//name will not be needed to copy the album name
		strcpy(songData->albumTitle, strtok(NULL, ","));
		strcpy(songData->songTitle, strtok(NULL, ","));
		strcpy(songData->genre, strtok(NULL, ","));
		//getting the duration
		strcpy(name, strtok(NULL, ":"));
		var = atoi(name);
		songData->duration.minutes = var;
		strcpy(name, strtok(NULL, ","));
		var = atoi(name);
		songData->duration.seconds = var;
		//times played
		strcpy(name, strtok(NULL, ","));
		var = atoi(name);
		songData->timesPlayed = var;
		//rating
		strcpy(name, strtok(NULL, ","));
		var = atoi(name);
		songData->rating = var;
	}
}
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: storeFiles
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes in a inFile and our linked list and reformats all the data and stores it back to the csv file
* Prereq: The linked list had to be loaded
* Postreq: our csv file stores the contents of the list in the original format
*******************************************************************************************/
void storeFiles(FILE* infile, Node* pList) {
	char name[100] = "", firstName[100] = "", lastName[100] = "";
	int index = 0, whiteSpace = 0, n = 0, z = 0;
	while (pList->pNext != NULL) {
		pList = pList->pNext;
	}
	while (pList != NULL) {
		strcpy(name, "");
		strcpy(firstName, "");
		strcpy(lastName, "");//reseting the variables that fix the format
		whiteSpace = 0;
		for (index = 0; index < strlen(pList->info.artist); index++) {//finding the space in an artists name
			if (pList->info.artist[index] == ' ') {
				whiteSpace = index;
				strncpy(firstName, pList->info.artist, whiteSpace);
				z = whiteSpace;
				for (; z < 100; z++) {
					firstName[z] = '\0';
				}
				whiteSpace++;
				for (n = 0; whiteSpace < strlen(pList->info.artist); n++) {// Puts the characters in the last name into a char array
					lastName[n] = pList->info.artist[whiteSpace];
					whiteSpace++;
				}
				for (; n < 100; n++) {
					lastName[n] = '\0';
				}
				strcat(name, "\"");//restoring original format of the name
				strcat(name, lastName);
				strcat(name, ", ");
				strcat(name, firstName);
				strcat(name, "\"");
			}
		}
		
		if (whiteSpace==0) {//no space
			fprintf(infile, "%s,%s,%s,%s,%d:%d,%d,%d", pList->info.artist, pList->info.albumTitle, pList->info.songTitle, pList->info.genre, pList->info.duration.minutes, pList->info.duration.seconds, pList->info.timesPlayed, pList->info.rating);
		}
		else {
			fprintf(infile, "%s,%s,%s,%s,%d:%d,%d,%d", name, pList->info.albumTitle, pList->info.songTitle, pList->info.genre, pList->info.duration.minutes, pList->info.duration.seconds, pList->info.timesPlayed, pList->info.rating);
			
		}
		if (pList->pPrev != NULL) {//prints a newline if its not the last song
			fprintf(infile, "\n");
		}
		pList = pList->pPrev;
		
	}
}
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: searchList
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes our list and finds a specific node using user input
* Prereq: The List must be loaded
* Postreq: A pointer to the user specified node is found and returned
*******************************************************************************************/
Node* searchList(Node* pList) {
	char artist[100] = "", song[100] = "";
	int appear = 0, index = 0;
	Node* pCopy = pList;
	Node* pSearch = NULL;
	printf("Please type the name of the Artist you would like to select (if the artist has one song in your playlist that song will be selected): ");
	getchar();//Get rid of the \n
	fgets(artist, 100, stdin);
	artist[strlen(artist) - 1] = '\0';
	while (pCopy != NULL) {//searches artist
		if (strcmp(pCopy->info.artist, artist) == 0) {
			appear++;
		}
		pCopy = pCopy->pNext;
	}
	pCopy = pList;
	if (appear > 1) {//multiple songs from the artist
		printf("\n%s has multiple songs: \n", artist);
		while (pCopy != NULL) {
			if (strcmp(pCopy->info.artist, artist) == 0) {
				index++;
				printf("Track %d:\nSong: %s\n", index, pCopy->info.songTitle);
			}
			pCopy = pCopy->pNext;
		}
		pCopy = pList;
		printf("Please type the name of the song you would like to select: \n");
		fgets(song, 100, stdin);
		song[strlen(song) - 1] = '\0';
		while (pCopy != NULL) {//finds the correct song
			if (strcmp(pCopy->info.songTitle, song) == 0) {
				pSearch = pCopy;
				break;
			}
			pCopy = pCopy->pNext;
		}

		
	}
	else {// 1 song by the artist
		while (pCopy != NULL) {
			if (strcmp(pCopy->info.artist, artist) == 0) {
				pSearch = pCopy;
				break;
			}
			pCopy = pCopy->pNext;
		}
	}
	return pSearch;
}
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
void displayRecords(Node* pList) {
	char artist[100] = "", song[100] = "";
	int choice = 0, appear = 0, index = 0;
	Node* pSearch = NULL;
	Node* pCopy = pList;
	do {//Choice of artist vs all
		printf("\n1.Display all records\n2.Display an Artist records\nPlease Select and option:\n");
		scanf("%d", &choice);
		if (choice <1 || choice > 2) {
			printf("\nPlease select a valid option (1 or 2)\n");
		}
	} while (choice <1 || choice > 2);
	switch (choice) {
	case(1): 
		printList(pList);
		break;
	case(2):
		pSearch = searchList(pList);
		printf("\nArtist: %s\nAlbum: %s\nSong: %s\nGenre: %s\nDuration: %d:%d\nTimes Played: %d\nRating: %d\n\n", pSearch->info.artist, pSearch->info.albumTitle, pSearch->info.songTitle, pSearch->info.genre, pSearch->info.duration.minutes, pSearch->info.duration.seconds, pSearch->info.timesPlayed, pSearch->info.rating);
				
				
	
		break;
	}
}
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
void editRecord(Node* pList) {
	Node* pSearch = NULL;
	char attribute[100] = "";
	int choice = 0, var = 0, min = 0, sec = 0;
	printList(pList);
	pSearch = searchList(pList);
	printf("\nWhich attribute would you like to change to the song:\n1. Artist Name\n2. Album Title\n3. Song Title\n4. Genre\n5. Duration\n6. Times Played\n7. Rating\n");
	do {//Get the choice of attribute
		scanf("%d", &choice);
		if (choice < 1 || choice >7) {
			printf("Please enter a valid choice (1-7)");
		}
	} while (choice < 1 || choice >7);
	switch (choice) {//Picking the attribute to  change
	case(1):
		printf("Please rename the artist:\n");
		getchar();
		fgets(attribute,100,stdin);
		attribute[strlen(attribute) - 1] = '\0';
		strcpy(pSearch->info.artist, attribute);
		break;
	case(2):
		printf("Please rename the Album:\n");
		getchar();
		fgets(attribute, 100, stdin);
		attribute[strlen(attribute) - 1] = '\0';
		strcpy(pSearch->info.albumTitle, attribute);
		break;
	case(3):
		printf("Please rename the Song:\n");
		getchar();
		fgets(attribute, 100, stdin);
		attribute[strlen(attribute) - 1] = '\0';
		strcpy(pSearch->info.songTitle, attribute);
		break;
	case(4):
		printf("Please rename the Genre:\n");
		getchar();
		fgets(attribute, 100, stdin);
		attribute[strlen(attribute) - 1] = '\0';
		strcpy(pSearch->info.songTitle, attribute);
		break;
	case(5):
		printf("Please change the duration(Format in 0:00):\n");
		scanf("%d:%d",&min,&sec);
		pSearch->info.duration.minutes = min;
		pSearch->info.duration.seconds = sec;
		
		break;
	case(6):
		printf("Please change the number of times played:\n");
		scanf("%d", &var);
		pSearch->info.timesPlayed = var;
		break;
	case(7):
		printf("Please change the number of rating:\n");
		scanf("%d", &var);
		pSearch->info.rating = var;
		break;
	}
	

}
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: rateRecord
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes our list and displays all the songs and lets the user chose the song and rating for the song
* Prereq: list needs to be loaded
* Postreq: the songs rating changes
*******************************************************************************************/
void rateRecord(Node* pList, int length) {
	int index = 0, choice = 0, rating = 0;
	while (pList->pNext != NULL) {
		pList = pList->pNext;
	}
	for (index = 1; index < length+1; index++) {//print all the options to the user
		printf("%d. Artist: %s, Album: %s, Song: %s, Genre: %s, Duration: %d:%d, Times Played: %d, Rating: %d\n",index, pList->info.artist, pList->info.albumTitle, pList->info.songTitle, pList->info.genre, pList->info.duration.minutes, pList->info.duration.seconds, pList->info.timesPlayed, pList->info.rating);
		if (pList->pPrev != NULL) {
			pList = pList->pPrev;
		}
	}
	while (pList->pNext != NULL) {
		pList = pList->pNext;
	}
	printf("Please enter a the option for the song you want to rate: \n");
	do {//get the option of the song the user would like to rate
		scanf("%d", &choice);
		if (choice == 0) {
			printf("\nPlease enter a valid option (1 - %d)", index);
		}
	} while (choice == 0);
	choice--;//Correct the "indice"
	while (choice!=0) {
		pList = pList->pPrev;
		choice--;
	}
	printf("\nPlease enter the rating (1-5) for the song \"%s\" by %s :\n", pList->info.songTitle, pList->info.artist);
	do {//Get valid rating
		scanf("%d", &rating);
		if (rating < 1 || rating > 5) {
			printf("\nPlease enter a valid option (1 - 5)");
		}
	} while (rating < 1 || rating > 5);
	pList->info.rating = rating;
}
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: printList
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 13, 2017                                                                      *
* Description: This function takes in the list and prints its contents
* Prereq: The list needs to be loaded
* Postreq: our list is displayed
*******************************************************************************************/
void printList(Node* pList) {
	while (pList->pNext != NULL) {//get to the "front"
		pList = pList->pNext;
	}
	
	printf("\n");
	while (pList != NULL) {
		printf("Artist: %s\nAlbum: %s\nSong: %s\nGenre: %s\nDuration: %d:%d\nTimes Played: %d\nRating: %d\n\n", pList->info.artist, pList->info.albumTitle, pList->info.songTitle, pList->info.genre, pList->info.duration.minutes, pList->info.duration.seconds, pList->info.timesPlayed, pList->info.rating);
		pList = pList->pPrev;
	}
	printf("\n");
}
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
void playSongs(Node* pList) {
	Node* pSearch = NULL;
	int choice = 0;
	printf("\n1.Play all songs\n2.Play a certain song\nPlease choose an option: ");
	do {
		scanf("%d", &choice);
		if (choice < 1 || choice >2) {
			printf("\nPlease choose option 1 or option 2:\n");
		}
	} while (choice < 1 || choice >2);
	system("cls");//Clear screen before "playing"
	switch (choice) {
	case(1):
		while (pList->pNext != NULL) {
			pList = pList->pNext;
		}
		while (pList != NULL) {
			printf("Artist: %s\nAlbum: %s\nSong: %s\nGenre: %s\nDuration: %d:%d\nTimes Played: %d\nRating: %d\n\n", pList->info.artist, pList->info.albumTitle, pList->info.songTitle, pList->info.genre, pList->info.duration.minutes, pList->info.duration.seconds, pList->info.timesPlayed, pList->info.rating);
			pList = pList->pPrev;
			Sleep(1000);
			system("cls");
		}
		break;
	case(2):
		pSearch = searchList(pList);
		pList = pSearch;
		while (pList != NULL) {
			printf("Artist: %s\nAlbum: %s\nSong: %s\nGenre: %s\nDuration: %d:%d\nTimes Played: %d\nRating: %d\n\n", pList->info.artist, pList->info.albumTitle, pList->info.songTitle, pList->info.genre, pList->info.duration.minutes, pList->info.duration.seconds, pList->info.timesPlayed, pList->info.rating);
			pList = pList->pPrev;
			Sleep(1000);
			system("cls");
		}
	}
}
void getRecord(Record* data) {
	char name[100] = "", songName[100] = "", albumName[100] = "", genre[20] = "";
	int min = 0, sec = 0, timesPlayed = 0, rating = 0;
	printf("Please enter the name of the artist:\n");
	getchar();
	fgets(name, 100, stdin);
	printf("Please enter the name of the album:\n");
	fgets(albumName, 100, stdin);
	printf("Please enter the name of the song:\n");
	fgets(songName, 100, stdin);
	printf("Please enter the name of the genre:\n");
	fgets(genre, 20, stdin);
	printf("Please enter the duration:\n");
	scanf("%d:%d", &min, &sec);
	printf("Please enter the times played:\n");
	scanf("%d",&timesPlayed);
	printf("Please enter the rating (1-5):\n");
	scanf("%d", &rating);
	name[strlen(name) - 1] = '\0';
	albumName[strlen(albumName) - 1] = '\0';
	songName[strlen(songName) - 1] = '\0';
	genre[strlen(genre) - 1] = '\0';

	strcpy(data->artist, name);
	strcpy(data->albumTitle, albumName);
	strcpy(data->songTitle, songName);
	strcpy(data->genre, genre);
	data->duration.minutes = min;
	data->duration.seconds = sec;
	data->timesPlayed = timesPlayed;
	data->rating = rating;
	
}
Boolean sortRecords(Node *pList) {
	int choice = 0, length = 0, runs = 0;
	Node* pCur = NULL, *pNext = NULL;
	Record temp = { NULL };
	do {
		printf("\n1. Sort based on artist (A-Z)\n2. Sort based on album title (A-Z)\n3. Sort based on rating (1-5)\n4. Sort based on times played (largest-smallest)\nPlease enter a choice for sorting: ");
		scanf("%d", &choice);
	} while (choice < 1 || choice >4);
	pCur = pList;
	while (pCur != NULL) {
		length++;
		pCur = pCur->pNext;
	}
	switch (choice) {
	case(1)://artist A-Z
		for (runs = 0; runs < length; runs++) {
			for (pCur = pList, pNext = pCur->pNext; pNext != NULL; pCur = pNext, pNext = pNext->pNext) {
				if (strcmp(pCur->info.artist, pNext->info.artist) < 0) {
					temp = pNext->info;
					pNext->info = pCur->info;
					pCur->info = temp;
				}
			}
		}
		break;
	case(2)://album A-z
		for (runs = 0; runs < length; runs++) {
			for (pCur = pList, pNext = pCur->pNext; pNext != NULL; pCur = pNext, pNext = pNext->pNext) {
				if (strcmp(pCur->info.albumTitle, pNext->info.albumTitle) < 0) {
					temp = pNext->info;
					pNext->info = pCur->info;
					pCur->info = temp;
				}
			}
		}
		break;
	case(3)://rating
		for (runs = 0; runs < length; runs++) {
			for (pCur = pList, pNext = pCur->pNext; pNext != NULL; pCur = pNext, pNext = pNext->pNext) {
				if (pCur->info.rating < pNext->info.rating) {
					temp = pNext->info;
					pNext->info = pCur->info;
					pCur->info = temp;
				}
			}
		}
		break;
	case(4)://times played
		for (runs = 0; runs < length; runs++) {
			for (pCur = pList, pNext = pCur->pNext; pNext != NULL; pCur = pNext, pNext = pNext->pNext) {
				if (pCur->info.timesPlayed > pNext->info.timesPlayed) {
					temp = pNext->info;
					pNext->info = pCur->info;
					pCur->info = temp;
				}
			}
		}
		break;
	}
}
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: deleteRecord
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 21, 2017                                                                      *
* Description: The user selects a record using the search function and the record is removed from the list
* Prereq: the list needs to be loaded
* Postreq: the item is deleted from the list
*******************************************************************************************/
void deleteRecord(Node**pList, Node* pDel) {
	Node* pCur = NULL, *pEnd = NULL, *pHead = NULL;
	pHead = *pList;//Used to check if the delete is at the front of the list
	pEnd = *pList;
	while (pEnd->pNext != NULL) {// Used for checking if the delete is at the end of the list
		pEnd = pEnd->pNext;
	}
	if (pDel == pHead) {
		pCur = pHead->pNext;
		pCur->pPrev = NULL;
		*pList = pCur;
		pHead = pCur;
		free(pDel);
	}
	else if (pDel == pEnd) {
		pCur = pEnd->pPrev;
		pCur->pNext = NULL;
		pEnd = pCur;
		free(pDel);
	}
	else {
		pCur = pHead;
		while (pCur->pNext != pDel && pCur != NULL) {
			pCur = pCur->pNext;
		}
		pCur->pNext = pDel->pNext;
		pDel->pNext->pPrev = pCur;
		free(pDel);
	}
}
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: random
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 21, 2017                                                                      *
* Description:  A random integer from 0 to the length of the list -1 is returned
* Prereq: none
* Postreq:  A random integer from 0 to the length of the list -1 is returned
*******************************************************************************************/
int random(int length) {
	int r = 0;
	r = (rand() % length)+1;
	return r;
}
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
void bubbleSwap(int arr[], int length) {
	int indexNum = 0, randomInt = 0, temp = 0;
	while (arr[indexNum] != 0) {
		randomInt = random(length)-1;
		temp = arr[indexNum];
		arr[indexNum] = arr[randomInt];
		arr[randomInt] = temp;
		indexNum++;
	}
}
/*******************************************************************************************
* Programmer: Noah Taylor
* Function name: shuffle
* Class:CptS 122, Fall  2017; Lab Section 7                                             *                                  *
* Date:  September 21, 2017                                                                      *
* Description:  The contents of each song is displayed to the user at random
* Prereq: the list needs to be loaded and the array in the function needs to be reorders
* Postreq:  the contents are displayed at random
*******************************************************************************************/
void shuffle(Node* pList) {
	int length = 0, index = 0, loc1 = 0, loc2 = 0, count = 1, arrayIndex = 0, dif = 0;
	int arr[1000] = { 0 };
	Node* pCount = NULL;
	pCount = pList;
	while (pCount != NULL) {
		length++;
		pCount = pCount->pNext;
	}
	if(length!=0){
		pCount = pList;
		if (length == 1) {
			printf("Artist: %s\nAlbum: %s\nSong: %s\nGenre: %s\nDuration: %d:%d\nTimes Played: %d\nRating: %d\n\n", pList->info.artist, pList->info.albumTitle, pList->info.songTitle, pList->info.genre, pList->info.duration.minutes, pList->info.duration.seconds, pList->info.timesPlayed, pList->info.rating);
		}
		else {
			for (index = 0; index < length; index++) {//initilize the existance of all the songs into the array;
				arr[index] = index + 1;
			}
			bubbleSwap(arr, length);//randomize the order
			pCount = pList;
			loc1 = arr[arrayIndex];
			loc2 = arr[arrayIndex + 1];
			index = 0;//keeps track of position
			while (count != loc1) {//load into the first position
				pCount = pCount->pNext;
				count++;
			}
			system("cls");
			while (loc1 != 0) {//the compare isnt zero
				printf("Artist: %s\nAlbum: %s\nSong: %s\nGenre: %s\nDuration: %d:%d\nTimes Played: %d\nRating: %d\n\n", pCount->info.artist, pCount->info.albumTitle, pCount->info.songTitle, pCount->info.genre, pCount->info.duration.minutes, pCount->info.duration.seconds, pCount->info.timesPlayed, pCount->info.rating);
				Sleep(2000);
				system("cls");
				dif = loc1 - loc2;
				if (dif > 0) {
					for (index = 0; index != dif; index++) {
						pCount = pCount->pPrev;
					}
					
				}
				else {
					for (index = 0; index != dif; index--) {
						pCount = pCount->pNext;
					}
				}
				arrayIndex++;
				loc1 = arr[arrayIndex];
				loc2 = arr[arrayIndex + 1];
			}


			


		}
	}
}

