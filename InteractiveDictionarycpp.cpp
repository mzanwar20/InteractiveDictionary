#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

//multimap where all the words and their definitions are kept to be 
//used in the search
multimap<string, string> dictionary;

//vector created based on user input
vector<string> currentVector;	

//boolean to check for valid second param word
bool posPresent = true;

//Function which returns an array of word and the POS
//associated with it as the first of each lines
string* getFirstWordAndPOS(string, int);

//Function to break string for multiple POS (Parts Of Speech)
string* breakPOS(string, int);

//Function to add formatted enteries for the dictionary map
void addToDictionary(string, string);

//Function which takes the input and returns an array
string* userInputParam(string);

//Function to get help commands
void printHelpCommands();

//populates the currentVector from the dictionary
void createCurrentVector(string key);

//puts the current vector enteries in reverse order
void reverseCurrentVector();

//outputs the current vector to the display
void printCurrentVector(string key);

//find and seperates the parts of speech from the input
void getCurrentPOS(string key);

//find and seperates similar definitions from the current vector
void getDistinct(string);

//Function to get the word
void checkFirstParam(string);

//Function to check for the second input param
void checkSecondParam(string);

//Function to check for the second input param
void checkThirdParam(string);

//Function to check for the second input param
void checkFourthParam(string);

//Function to check for the second input param
void setSecondParamBool(string);



int main() {
	//Provided file path
	//string filePath = "C:\\Users\\MickeyMouse\\AbsolutePath\\DB\\Data.CS.SFSU.txt";
    string filePath = R"(E:\GoogleDrive\SFSU\Previous Semesters\CSC 340\Assignment 03\Assignment 3\InteractiveDictionary\Data.CS.SFSU.txt)";

	//open and read file variable
	ifstream file;

	//open the file
	cout << "! Opening data file... " << filePath << "\n";	
	file.open(filePath);
	
	//check to see if the file was able to open, if not
	//keep asking for proper directory to open the file
	while (!file.is_open()) {
		cout << "<!>ERROR<!> ===> File could not be opened.\n";
		cout << "<!>ERROR<!> ===> Provided file path: " << filePath << "\n";
		cout << "<!>Enter the CORRECT data file path: ";
		cin >> filePath;
		file.open(filePath);
	}
	cout << "! Loading Data ... \n";

	//variables used in the logic for getting words, definitions, and POS from the file
	string eachLine, words, *theWord, defi, *thePOSWord = {};
	int wordCounter = 0;	//how many words found in the file

	//once the file is open get the contents of the file
	//this is where data will be formatted and sent to be stored in 
	//the dictionary
	while (getline(file, eachLine)) {
		//getting words from each line
		stringstream wordsInLine(eachLine);
		
		//had to make this single loop so that I can send the first word of the string
		//to the getWord function to take out the first word of each line. 		
		for (int i = 0; i < 1; i++) {
			//break line into words		
			wordsInLine >> words;										
			//the first word and the location of | in it
			theWord= getFirstWordAndPOS(words, words.find("|"));	
		}
		
		//While loop for the remaining word wihtin each line after the first word and POS
		//are extracted in the above for loop
		while (wordsInLine >> words) {
			//If the word is an arrow, skip it
			if (words=="-=>>") {
				//do nothing
			}
			//if the word contains | within 15 charaacters of the word
			else if (words.find("|")<15) {
				//send the word to the breakPOS function to 
				//split the last word and the POS 
				thePOSWord=breakPOS(words, words.find("|"));
				
				//add the returned word into the variable which is saving all the 
				//definitions
				defi.append(thePOSWord[0]);
				defi.append(" ");	//add space between each word.

				//temp string to hold the POS and the definition
				//string tempPOS = theWord[0]+"-"+thePOSWord[1];
				string tempPOS = thePOSWord[1] + " : " + defi;

				//Finally, calls the function to add the word with the
				//POS attached to it and as definition the value for the key
				//addToDictionary(tempPOS, defi);
				addToDictionary(theWord[0], tempPOS);

				defi = " "; //resetting the string to be empty to take in new definition

			}
			//if no | is found after the first word, which is alway present
			else {
				//complete the definition by adding all the words
				defi.append(words);
				defi.append(" ");	//add space after each word
			}
		}
		//after each word is checked in the line
		//store the word with the first POS and add the
		//definition for it into the dictionary
		//this only applies for the entries that only
		//have 1 POS
		//string temp = theWord[0]+"-"+theWord[1]; //format for multimap
		string temp = theWord[1] + " : " + defi;
		//addToDictionary(temp, defi);			//add to multimap
		addToDictionary(theWord[0], temp);
		defi = " ";		//resetting the string to be empty to take in new definition

		//add to counter after going through each word of the file
		wordCounter++;
	}

	cout << "! Loading completed...\n";
	cout << "! Closing data file... " << filePath << "\n";
	file.close();

	cout << "\n====== DICTIONARY 340 C++ =====\n";
	cout << "------ Keywords: " << wordCounter << endl;
	cout << "------ Definitions: " << dictionary.size() << endl << endl;

	//Start of the dictionary seach function

	bool quit = false;
	int searchCounter = 1;
	string userInput, *inputArr;

	while (!quit) {

		cout << "Search [" << searchCounter << "]: ";
		getline(cin, userInput);

		//call function to turn user input into an array
		inputArr=userInputParam(userInput);

		//check for word presenst in the dictionary
		int count = dictionary.count(inputArr[0]);

		//creates the vector from the given user input word
		createCurrentVector(inputArr[0]);

		//if first cell is empty or has help command
		if (inputArr[0]=="!help" || inputArr[0]=="") {
			printHelpCommands();
		}
		
		//else check if user wants to quit the program
		else if (inputArr[0] == "!q") {
			cout << "-----THANK YOU-----";
			exit(0);
		}

		//if there is no match found of the word in dictionary, give not found message
		else if (count < 1) {
			cout << "\t|\n";
			cout << "\t <NOT FOUND> To be considered for the next release. Thank you." << endl;
			cout << "\t|\n";
		}

		//for the input word check each parameter
		else {
			//once all the quick end program are taken care of the 
			//input parameters are checked from highest to lowest or
			//from last to first. This way any input that isn't valid just gets ignored
			//and the program moves on the next parameter. 
			cout << "\t|\n";
			setSecondParamBool(inputArr[1]);				//check if 2nd parameter word exists
			checkFourthParam(inputArr[3]);					//check 4th param
			checkThirdParam(inputArr[2]);					//check 3rd param
			checkSecondParam(inputArr[1]);					//check 2nd param
			checkFirstParam(inputArr[0]);					//print the word+definition
			cout << "\t|\n";
		}

		posPresent = true;		//reset the boolean for next word
		currentVector.clear();	//erasing vector at the end to start again with new search
		searchCounter++;		//updates the number of search we are on.
	}
	
	return 0;
}//End Main

//The returns the first word and the first Part Of Speech with it.
string* getFirstWordAndPOS(string wordInLine, int location) {

	string* output = new string[2];
	//the word
	for (int i = 0; i < location; i++) {
		output[0] += wordInLine[i];
	}
	//the first POS 
	for (int i = location+1; i < wordInLine.length(); i++) {
		output[1] += wordInLine[i];
	}
	return output;
}

//exact copy of the above function - kept it seperate for sake of call simplicity
string* breakPOS(string wordInLine, int location) {
	string* output=new string[2];

	//the last word before the POS
	for (int i = 0; i < location; i++) {
		output[0] += wordInLine[i];
	}
	//the POS 
	for (int i = location + 1; i < wordInLine.length(); i++) {
		output[1] += wordInLine[i];
	}
	return output;
}

//Function to add the words, POS, and the definition into the dictionary multimap
void addToDictionary(string word, string definition) {
	dictionary.insert(pair<string, string>(word, definition));	
}

//function for dealing with user input
string* userInputParam(string input) {
	//input into lowercase
	transform(input.begin(), input.end(), input.begin(), ::tolower);

	string* output = new string[4];	//variable to return
	string words;					//variable for stringstream
	int i = 0;						//counter for # of words

	//set up string steam on the userInput
	stringstream wordsInInput(input);

	//add each word to its own array cell
	//if there are 4 than 4 enteries, the rest get ignored
	while (wordsInInput >> words && i<4) {
		output[i] = words;
		i++;
	}
	//display a message saying that the 5th+ enteries ignored
	if (i > 4) {
		cout << "\t <!> 5th(+) parameter in the input is ignored.";
		cout<<" Only 4 parameters are accepted. <!>\n";
		cout << "\t|\n";
	}
	return output;	
}

//Function to display help
void printHelpCommands() {
	cout << "\n\t|\n";
	cout << "\t PARAMETER HOW-TO, please enter:\n";
	cout << "\t 1. A search key -then 2. An optional part of speech -then\n";
	cout << "\t 3. An optional 'distinct' -then 4. An optional 'reverse'\n";
	cout << "\t|\n";
}

//creates this vector to be used for displaying and manipulating output
void createCurrentVector(string key) {//**referred to as the current vector in the comments**
	for (auto itr = dictionary.begin(); itr != dictionary.end(); itr++) {
		if (itr->first == key) {
			currentVector.push_back(itr->second);
		}
	}
	//sorts the vector in ascending order
	sort(currentVector.begin(), currentVector.end());
}

//function to diplay the vector in decending order
void reverseCurrentVector() {
	vector<string> temp;

	//using vector::rbegin()
	//Return reverse iterator to reverse beginning
	for (auto itr = currentVector.rbegin(); itr != currentVector.rend(); itr++) {
		temp.push_back(*itr);	//the end vector gets puts in the first spot
	}
	currentVector.clear();	//clear the currentVector
	currentVector = temp;	//transfers the temp vector into current vector
	temp.clear();			//clears the temp vector for next call
}		

//function to print out the current vector
void printCurrentVector(string key) {
	//simply prints out the current vector
	for (int i = 0; i < currentVector.size(); i++) {
		cout << "\t " << key << " " << currentVector.at(i) << endl;
	}
}

//function finds and seperates the POS asked by the user
void getCurrentPOS(string key) {
	vector<string> tempVector;
	string temp2, temp3;

	//for loop which goes through each entry of the current vector
	for (int i = 0; i < currentVector.size(); i++) {
		//stringstream used to take the vector at and turn 
		//the entire line into words
		stringstream pos(currentVector.at(i));

		//while loop for until there are words in the line
		//however, we are only interested in the first word
		while ((pos >> temp2) ) {
			//to get the first word we find the first space in the line
			//which would be after the POS in the string
			int loc = temp2.find_first_of(" ");
			//use the location found above and put that word into the 
			//a temp string variable
			temp3 = temp2.substr(0, loc);
			//now check the temp3 variable with the key in the function call
			//if the key matches, then put the currentvector into a temporary vector
			if (temp3 == key) {
				tempVector.push_back(currentVector.at(i));
			}			
		}//otherwise just go back and get the next vector		
	}

	currentVector.clear();			//clear the currentVector
	currentVector = tempVector;		//transfers the temp vector into current vector
	tempVector.clear();				//clears the temp vector for next call
}

//sorts out duplicate enteries from teh current vector
void getDistinct(string key) {
	vector<string> temp;

	//add the first value of current vector into the current vector
	temp.push_back(currentVector.at(0));

	//for loop to go through each entry in the current vector
	for (int i = 0; i < currentVector.size(); i++) {

		//if temp vector has a match for the current vector value at i
		if (find(temp.begin(), temp.end(), currentVector.at(i)) != temp.end()) {
			//do nothing
		}
		//if the value is not there, add that to the temp vector and go to the next
		//value in the current vector
		else {
			temp.push_back(currentVector.at(i));
		}
	}
	currentVector.clear();	//clear the currentVector
	currentVector = temp;	//transfers the temp vector into current vector
	temp.clear();			//clears the temp vector for next call
}

//Function to get the word definition
void checkFirstParam(string key) {
	//since the first argument is always the word, 
	//it only has print the vector, which is made much earlier,
	//in the main. this just prints it out
	printCurrentVector(key);
}

//Function to check for the second input param
void checkSecondParam(string key) {
	if (key == "") {					//if no input just ignore
		//do nothing
	}
	else if (key == "distinct") {	
		getDistinct(key);
	}
	else if (key == "reverse") {
		reverseCurrentVector();
	}
	else if (posPresent==false) {		//if the POS doesn't exist then print out the error
		cout << "\t <The entered 2nd parameter '" << key << "' is NOT a part of speech.>\n";
		cout << "\t <The entered 2nd parameter '" << key << "' is NOT 'distinct'.>\n";
		cout << "\t <The entered 2nd parameter '" << key << "' is NOT 'reverse'.>\n";
		cout << "\t <The entered 2nd parameter '" << key << "' was disregarded.>\n";
		cout << "\t <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>\n";
		cout << "\t|\n";
	}
	else {								//if here then the second parameter must be a valid pos
		getCurrentPOS(key);				
	}
}

//Function to check for the third input param
void checkThirdParam(string key) {
	if (key == "") {
		//do nothing
	}
	else if (key == "distinct") {
		getDistinct(key);
	}
	else if (key == "reverse") {
		reverseCurrentVector();
	}
	else {
		cout << "\t <The entered 3rd parameter '" << key << "' is NOT 'distinct'.>\n";
		cout << "\t <The entered 3rd parameter '" << key << "' is NOT 'reverse'.>\n";
		cout << "\t <The entered 3rd parameter '" << key << "' was disregarded.>\n";
		cout << "\t <The 3rd parameter should be 'distinct' or 'reverse'.>\n";
		cout << "\t|\n";
	}
}

//Function to check for the fourth input param
void checkFourthParam(string key) {
	if (key == "") {
		//do nothing
	}
	else if (key == "reverse") {
		reverseCurrentVector();
	}
	else {
		cout << "\t <The entered 4th parameter '" << key << "' is NOT 'reverse'.>\n";
		cout << "\t <The entered 4th parameter '" << key << "' was disregarded.>\n";
		cout << "\t <The 4th parameter should be 'reverse'.>\n";
		cout << "\t|\n";
	}
}

//Function to check for seond param valid word
//if it doesnt exitst then updates the boolean to 
//false so that the checSecondParam function
//can display the error
void setSecondParamBool(string key) {
	/*
		This is an exact copy of the getCurrentPOS function.
		instead of writing new logic, all this is doing is changing
		the boolen to false if the size of tempoary vector is 0.
		all this does is sets the boolean so that it can be checked inside
		the checkSecondParam and can display the error message if the 
		input second param word is invalid
	*/

	vector<string> tempVector;
	string temp2, temp3;

	//for loop which goes through each entry of the current vector
	for (int i = 0; i < currentVector.size(); i++) {
		//stringstream used to take the vector at and turn 
		//the entire line into words
		stringstream pos(currentVector.at(i));

		//while loop for until there are words in the line
		//however, we are only interested in the first word
		while ((pos >> temp2)) {
			//to get the first word we find the first space in the line
			//which would be after the POS in the string
			int loc = temp2.find_first_of(" ");
			//use the location found above and put that word into the 
			//a temp string variable
			temp3 = temp2.substr(0, loc);
			//now check the temp3 variable with the key in the function call
			//if the key matches, then put the currentvector into a temporary vector
			if (temp3 == key) {
				tempVector.push_back(currentVector.at(i));
			}
		}//otherwise just go back and get the next vector		
	}
	//I'm puting a condition here to 
	//update the boolean to false if the second parameter is not a pos present
	//in the dictionary 
	if (tempVector.size() < 1) {
		posPresent = false;
	}
	tempVector.clear();		//clears the temp vector for next call
}