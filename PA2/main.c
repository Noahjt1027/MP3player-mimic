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
int main(void) {
	Node* pList = NULL;
	Node* pDel = NULL;
	FILE* infile = NULL;
	Record testRecord = { NULL }, newRecord = { NULL };
	char line[150] = "", copyLine[150] = "", artist[100] = "";
	int choice = 0, length = 0;



	do {
		displayMenu();
		scanf("%d", &choice);
		switch (choice) {//Prereq is 1 has to be selected first or it will crash
		case (1)://Load filesinto a doubly linked list
			infile = fopen("musicPlayList.csv", "r");

			while (!feof(infile)) {
				fgets(line, 150, infile);
				strcpy(copyLine, line);
				getSongInfo(copyLine, &testRecord);
				insertFront(&pList, testRecord);
				length++;

			}
			fclose(infile);
			system("pause");
			system("cls");
			break;
		case (2):
			infile = fopen("musicPlayList.csv", "w");
			storeFiles(infile,pList);
			fclose(infile);
			system("pause");
			system("cls");
			break;
		case(3):
			displayRecords(pList);
			system("pause");
			system("cls");
			break;
		case(4):
			getRecord(&newRecord);
			insertFront(&pList,newRecord);
			length++;
			system("pause");
			system("cls");
			break;
		case(5):
			pDel = searchList(pList);
			deleteRecord(&pList, pDel);
			length--;
			system("pause");
			system("cls");
			break;
		case(6):
			editRecord(pList);
			system("pause");
			system("cls");
			break;
		case(7):
			sortRecords(pList);
			system("pause");
			system("cls");
			break;
		case(8):
			rateRecord(pList, length);
			system("pause");
			system("cls");
			break;
		case(9):
			playSongs(pList);
			system("pause");
			system("cls");
			break;
		case(10):
			shuffle(pList);
			system("pause");
			system("cls");
			break;
		case(11)://exit
			system("pause");
			system("cls");
			break;
		default:
			printf("That is not a valid option please choose again.\n");
			system("pause");
			system("cls");
		}
	} while (choice != 11);
	
	return 0;
}