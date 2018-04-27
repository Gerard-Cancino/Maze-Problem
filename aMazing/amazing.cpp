//Gerard Cancino
//Professor Ashok
//Extra Credit

/*Steps
1) Load file
2) Calc entrances on point
3) Go through run
4) This will close all paths that doesn't end with '$'
5) Now with close paths. Snake can go through and find '$'
6) Ends when snake reaches $
7) Prints out result
*/

/* or what if i do dis
8 24
xxxxxxxxxxxxxxxxxxxxxxxx
--------------------xxxx
-xxxxxxxxxx---xxxxxxxxxx
-xxxx--xx-----xx-x-----x
-xxxx--xxxxxx---x--xxx--
---xxx----xxxxx---xxxx--
-xxxxxxxxxxxxxxxx-xxxxxx
*xxxxxxxxxxxx$----xxxxxxE


8 24					
xxxxxxxxxxxxxxxxxxxxxxxx
22222222222333222221xxxx
2xxxxxxxxxx343xxxxxxxxxx
2xxxx--xx123342x-x22222x
2xxxx--xxxxxx232x22xxx32
321xxx----xxxxx223xxxx22
2xxxxxxxxxxxxxxxx2xxxxxx
*xxxxxxxxxxxx$2222xxxxxxE
*/
		


#include <string>
#include <iostream>
#include <fstream>
#include <istream>
using namespace std;

char maze[24][8];

//PreCondition for all: None.  Just shares char maze.
//PostCondition for all: None. They are all void. They return nothing.

//Reads the text file and places each data at x coordinate of array "line" into x,y coordinate in maze[x][y]
void reader();

//Reads each Coordinate to determine all entrances. (i.e. if there exist a '-' around it.)
void calc();

//Paths through the array starting from '*' this will close most paths
//Idea was that if it was a tunnel of 22222 then moving on it past this would make it 11111
//But if that path doesn't lead to '$', it would close the path making it 00000
void analyzer();

//Prints out array. I did this 3 times to check if the methods were truly working
void test();

//Similar to analyzer, but instead of decreasing the integer. it would replace it with '*'
void retriever();

int main() {
	int x; 

	//Methods used in main method
	reader();
	test();
	calc();
	//test();
	//analyzer();
	//test();
	//retriever();
	//test();

	//So you can see output
	cin >> x;
	return x;
	
}



//Reader
void reader() {
	string line; //No nead to define cuz it would be defined with "getline(myFile, line)

	ifstream myFile; //myFile with data type ifstream.  (allowed to use methods within ifstream)
	myFile.open("test.txt"); //One of the methods. To open a text.  In this case this is text.txt

	if (myFile.is_open()) { //if successfully opened
		getline(myFile, line); //place first line in text into line
		for(int y=0;y<8;y++){ // Nested for loop!  y is height
			for (int x = 0; x < 24; x++) { //x is width
				maze[x][y] = line[x]; //Places each value into maze
			}
			//Retrieve next line
			getline(myFile, line);
		}
		myFile.close(); //Close file cuz ya don't need dat in memory
	}
	else
		//Just incase the file is missing
		//The only error that this would not check for is if u give me a >8 by >24 array.  The if statement would work. It would just capture the first 8 by 24 values
		cout << "error";
}
/*
void calc() {
	//Another nest
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 24; x++) {
			//k represents how many entrances
			int k = 0;
			//Calc entrances
			if (maze[x][y] == '-'){
				//Down
				if(y + 1<8)
					if ((maze[x][y + 1]) != 'x')
						k++;
				//Up
				if(y - 1>0)
					if ((maze[x][y - 1]) != 'x')
						k++;
				//Right
				if(x + 1<24)
					if ((maze[x + 1][y]) != 'x')
						k++;
				//Left
				if(x - 1>-1)
					if((maze[x - 1][y]) != 'x')
						k++;
				//wow int => chars!  cant do repeat = k.  this wont produce the same an integer in char
				//'0' is 48 in char and 0 in int is. I think NULL in char?
				char repeat = '0' + k;
				//Places char into coord
				maze[x][y] = repeat;
			}
		}
	}
}

//First playthrough of snake
void analyzer() {

	//Finds the start
	int x = 0;
	int y = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 24; j++) {
			if (maze[j][i] == '*') {
				x = j;
				y = i;
				break;
			}
		}
	}

	//I use a,b to keep track of where the pointer was before
	//its for up and down or right and left.  Its so the snake wont go down, and b/c there is now the option to go, go up.
	int a = -10;
	int b = -10;

	//I use left and down to counteract the if and else if statements.  Same reasons as a and b.  Its so the snake will thoroughly checks each passage.
	//After check each passage it will then repeat and go up or right
	bool left = false, down = false;
	bool error = false;
	while (maze[x][y] != '$' && error == false) {
		//If my professor is reading this. There better not be a better way of doing this cuz wth so much debugging
		//1Error going on 'x'
		//1Error pointer somehow going out of the array
		//1Error going down is succeeded with an up
		//Error prioritizing up more than left

		//Up
		//snake avoids 'x', '0', out of index char (maybe in memory).  Read up for why i use b, down and left
		if (maze[x][y - 1] != 'x' && maze[x][y - 1] != '0' && y - 1 > 0 && y - 1 != b && down == false && left == false) {
			a = x;
			b = y;
			y--;
			if (maze[x][y] != '$')
				maze[x][y]--;
		}
		//Right
		//Same explanation
		else if (maze[x + 1][y] != 'x' && maze[x + 1][y] != '0' && x + 1 < 24 && x + 1 != a && left == false) {
			a = x;
			b = y;
			x++;
			if (maze[x][y] != '$')
				maze[x][y]--;
		}
		//Down
		else if (maze[x][y + 1] != 'x' && maze[x][y + 1] != '0' && y + 1 < 8 && y + 1 != b) {
			down = true;
			left = false;
			a = x;
			b = y;
			y++;
			if (maze[x][y] != '$')
				maze[x][y]--;
		}
		//Left
		else if (maze[x - 1][y] != 'x' && maze[x - 1][y] != '0' && x - 1 > -1 && x-1!=a) {
			left = true;
			down = false;
			a = x;
			b = y;
			x--;
			if (maze[x][y] != '$')
				maze[x][y]--;
		}
		else if (down == true || left == true) {
			down = false;
			left = false;
		}
		//Fix for all sides being 'x' besides one side, which is an integer
		else if (x == a || y == b) {
			a = -10;
			b = -10;
		}
		//Cuz every case should be filled
		else {
			cout << "error";
			error = true;
		}
	}
}
*/
//Output
void test() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 24; j++) {
			cout << maze[j][i];
		}
		cout << endl;
	}
	cout << endl;
}
/*

//Second playthrough
//Now this time the paths will have '0' making it easier for the snake go through
//Almost the same code except the if statements says avoid '*' and will replace an integer with '*'
void retriever() {
	int x = 0;
	int y = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 24; j++) {
			if (maze[j][i] == '*') {
				x = j;
				y = i;
				break;
			}
		}
	}
	int a = -10;
	int b = -10;
	bool left = false, down = false;
	bool error = false;
	while (maze[x][y] != '$' && error == false) {
		//If my professor is reading this. There better not be a better way of doing this cuz wth so much debugging
		//1Error going on 'x'
		//1Error pointer somehow going out of the array
		//1Error going down is succeeded with an up
		//1Error prioritizing up more than left
		//Error pointer to '*'

		//Up
		if (maze[x][y - 1] != 'x' && maze[x][y - 1] != '0' && maze[x][y - 1] != '*' && y - 1 > 0 && y - 1 != b && down == false && left == false) {
			a = x;
			b = y;
			y--;
			if (maze[x][y] != '$')
				maze[x][y]='*';
		}
		//Right
		else if (maze[x + 1][y] != 'x' && maze[x + 1][y] != '0' && maze[x+1][y]!='*' && x + 1 < 24 && x + 1 != a && left == false) {
			a = x;
			b = y;
			x++;
			if (maze[x][y] != '$')
				maze[x][y] = '*';
		}
		//Down
		else if (maze[x][y + 1] != 'x' && maze[x][y + 1] != '0' && maze [x][y+1] != '*' && y + 1 < 8 && y + 1 != b) {
			down = true;
			a = x;
			b = y;
			y++;
			if (maze[x][y] != '$')
				maze[x][y] = '*';
		}
		//Left
		else if (maze[x - 1][y] != 'x' && maze[x - 1][y] != '0' && maze[x-1][y] != '*'&& x - 1 > -1 && x - 1 != a) {
			left = true;
			a = x;
			b = y;
			x--;
			if (maze[x][y] == '$') {
				break;
			}
			if (maze[x][y] != '$')
				maze[x][y] = '*';
		}
		else if (down == true || left == true) {
			down = false;
			left = false;
		}
		//Fix for all sides being 'x' besides one side, which is an integer
		else if (x == a || y == b) {
			a = -10;
			b = -10;
		}
		//Cuz every case should be filled
		else {
			cout << "error";
			error = true;
		}
	}
}
*/