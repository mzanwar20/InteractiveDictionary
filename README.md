#InteractiveDictionary
Assignment for Programming Methodology (CSC340) Class at SFSU
By Muhammad Z. Anwar

Assignment description and requirements:
Design an interactive dictionary which takes input from users and uses the input as search key to look up values associated with the key.

Source: The program must read data from a file. 

Data Structure: Use existing data structure(s) or create new data structure(s) to store our dictionary’s data. 
Each keyword, each part of speech, and each definition must be stored in a separate data field. Do not combine them such as storing 
three parts in one String.

Data Loading: When our program starts, it loads all the original data from the Data Source into our dictionary’s data structure. 
The data source file is opened once and closed once per run. It must be closed as soon as possible. It must be closed before our 
program starts interacting with users.

User Interface: A program interface allows users to input search keys. This interface then displays returned results. 
Our program searches the dictionary’s data (not the data source text file) for values associated with the search keys.

Concluding Remarks:
I think there are ways to make the program more efficient. For example in the code on line 467 I have a function 
void setSecondParamBool(string key) { this function is an exact copy of the function void getDistinct(string key) 
on line 371. The only reason I reused this in a separate function is to update the Boolean which checks to see if 
the parameter entered into the second argument is valid. I was not able to make this simple Boolean update part of the 
getDistinct function and is something I would like to make more efficient. Aside from this I think there are few more 
places to make the program more efficient, however I would need to spend more time learning about built in library 
functions to be able to implement them where possible.
