//Preston Zimmerman
// 4/5/19
#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <vector>
#include "AvlTree.h"

using namespace std::chrono;

void buildTree(string fileName, AvlTree<string>* myAvl);

int main(int argc, char* argv[]){
	// Do many things here
	string fileName = argv[1];
	//BinarySearchTree<string> * myBst = new BinarySearchTree<string>();
	AvlTree<string> * myAvl = new AvlTree<string>();
	buildTree(fileName, myAvl);



	while(true){
		int userInput;
		cout << "Options: (1) display index, (2) search index, (3) save index, (4) quit" << endl;
		cin >> userInput;

		if(userInput < 1 || userInput > 4){
			if(cin.fail()){
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			}
			cout << "Please enter a valid input" << endl;

		}

		else if(userInput == 1){
			myAvl->printTree();
		}

		else if(userInput == 2){
			// Search and display word/ line numbers
			cout << "Enter a word to search: ";
			string in = "";
			cin >> in;

			vector<int> lineNums;
			int compar = 0;
			if(myAvl->contains(in, lineNums, compar) == true){
				cout << "Line Numbers<bst>: ";
				for(auto i = 0; i < lineNums.size(); i++){
					cout <<  lineNums[i];
					if(i != lineNums.size()-1){
						cout << ", ";
					}
				}
				cout << "\n" << compar << " key comparisons to find this word." << endl;
			}
			else {
				cout << "Word not found" << endl;
			}

		}
		else if(userInput == 3){
			// Write to file
			string outFile;
			cout << "Please enter a file name to save index too: ";
			cin >> outFile;
			myAvl->printTree(outFile);
		}
		else if(userInput == 4){
			break;
		}
	} // end while

	return 0;
}

void buildTree(string fileName, AvlTree<string>* myAvl){
	  //double finish_time;
	  //double start_time = clock();

		high_resolution_clock::time_point t1 = high_resolution_clock::now();

	ifstream file(fileName);
	string str;
	int wordCount = 0;
	int lineCount = 0;
	int compar = 0;
	int rotates = 0;

	while(getline(file, str)){
		lineCount++;
		string temp = "";
		for(int i = 0; i < str.length(); i++){
			if(isalpha(str[i]) || isdigit(str[i])){
				temp += str[i];
			}
			else if((isalpha(str[i+1]) || isdigit(str[i+1])) && isspace(str[i]) == false){
				temp += str[i];
			}
			else if(temp != ""){
				wordCount++;
				myAvl->insert( temp, lineCount, compar, rotates );
				temp = "";
			}
		} // end for
	} // end while

	//  finish_time = clock();
	//  double time;
	// // double time = (finish_time - start_time) / CLOCKS_PER_SEC;
	// time = (double) ((finish_time - start_time) / CLOCKS_PER_SEC);

	// cout << "start: " << std::fixed << start_time << endl;
	// cout << "end: " << finish_time << endl;
	// cout << "clocks: " << CLOCKS_PER_SEC << endl;'

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	cout << "Total number of words: " << wordCount << endl;
	cout << "Total number of distinct words: " << myAvl->countTreeNodes() << endl;
	cout << "Time taken to build index using BST was: " << time_span.count() << " seconds" << endl;
	cout << "Heigh of the Binary Search Tree is: " << myAvl->TreeHeight() << endl;
	cout << "Total number of key comparisons: " << compar << endl;
	cout << "Total number of rotations: " << rotates << endl;

} // end buildTree
