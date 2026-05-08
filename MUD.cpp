//Andrew Bell
//abell87@vols.utk.edu
//Multi-User Dungeon

#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

//blueprint for the rooms, with its name, description, and the index values
//of the rooms bordering it. They are initialized to negative one and will
//only be changed if there is actually a room that exists in that direction.

struct room{
	string name;
	string desc;

	int northIndex = -1;
	int southIndex = -1;
	int eastIndex = -1;
	int westIndex = -1;
};

//this funtion counts the amount of rooms in the file. Since we know each
//room has 3 sections each seperated by a ~, we can scan the file 
//using a while loop and the getline function that counts up each time a 
//~ exists, them divide that number by 3 to get the number of rooms in the
//file.

int countRooms(string file){
	
	ifstream fin(file); // start scanning the file
	string data;
	int count = 0; // # of ~'s
	while (getline (fin, data, '~')){
		count++; //increment each time a ~ is encountered
	}
	fin.close(); // close the file
	return count/3; //return count of rooms
}

//this function is like a factory that creates a room each time it is called.
//first, it will use the getline funtion to assign the name and descripption
//to each room, with a ~ as the delineator. Then, it will take all the
//bordering room data into one string. we will use a while loop and a 
//string stream to parse through the data. there is a switch statement that
//compares the char that got read first by str to the different directions
//and will put the index value in the right direction.



room createRoom(ifstream &fin){ //pass fstream by reference so that we keep our spot in the file each time its called
	room tempRoom; // create room
	string coordinates; // 3rd section of room input
	char direction; // n, s, e, w
	int indexNum; //room num in that direction

	getline(fin, tempRoom.name, '~');
	getline(fin, tempRoom.desc, '~');
	getline(fin, coordinates, '~');

	stringstream str(coordinates);

	while (str >> direction){

		str >> indexNum; 
	
		switch(direction) { // conditionals
			case 'n':
				tempRoom.northIndex = indexNum;
				break;
			case 's':
				tempRoom.southIndex = indexNum;
				break;
			case 'e':
				tempRoom.eastIndex = indexNum;
				break;
			case 'w':
				tempRoom.westIndex = indexNum;
				break;
		}
	}

	return tempRoom; //return room once done
}

//this funtion will be called any time the use inputs 'l'. it takes the
//room the player is currently in and reads out all the info in that room
//instance. To Check the Exits, there are if statements that only print the
//exit directions that have a value that actually exists.
	
void look(room CurrentRoom){
	cout << CurrentRoom.name << endl;
	cout << CurrentRoom.desc << endl;

	cout <<"Exits: ";
	if (CurrentRoom.northIndex >= 0){
		cout << "n ";
	}
	if (CurrentRoom.southIndex >= 0){
        cout << "s ";
    }
	if (CurrentRoom.eastIndex >= 0){
        cout << "e ";
    }
	if (CurrentRoom.westIndex >= 0){
        cout << "w ";
    }
	cout << endl;

}

//void function, so we wont return anything. pass the player's position
//this function is going to compare the user's input to the values of 
//the indexes to see if they can move that direction, if they can the
//player's position will be updated and a statement indicating movement
//will print. if they cant, they will be told they cant move that way.
//the player's position will not be updated.

void move(room &CurrentRoom, char direction, int &playerPos){
	switch (direction){
		case 'n':
			if (CurrentRoom.northIndex >= 0){
				playerPos = CurrentRoom.northIndex;
				cout << "You moved North!" << endl;
			}
			else{ 
				cout << "You cant go North!" << endl;
			}
			break;
		case 's':
			if (CurrentRoom.southIndex >= 0){
				playerPos = CurrentRoom.southIndex;
				cout << "You moved South!" << endl;
			}
			else{
				cout << "You cant go South!" << endl;
			}
			break;
		case 'e':
			if (CurrentRoom.eastIndex >= 0){
				playerPos = CurrentRoom.eastIndex;
				cout << "You moved East!" << endl;
			}
			else{
				cout << "You can't go East!" << endl;
			}
			break;
		case 'w':
			if (CurrentRoom.westIndex >= 0){
				playerPos = CurrentRoom.westIndex;
				cout << "You moved West!" << endl;
			}
			else{
				cout << "You can't go West!" << endl;
			}
			break;
	}

}



int main(int argc, char* argv[]){
	string file = argv[1]; // string = to inputted file
	int numofRooms = countRooms(file); //count the rooms and assign it to an int
	ifstream fin(file); // initialize the fstream we will use to read the file
	room *arrPtr = new room[numofRooms]; //make a pointer to an array of rooms with size = to amount of rooms in file

	for (int i = 0 ; i < numofRooms; i++){ //loop through and make rooms = to num counted
		arrPtr[i] = createRoom(fin); //create a room and put it in the array at index i
	}

	fin.close(); // close file now that we're done with it
	
	int playerPos = 0; //start the player in the forst room
	char command; //variable to hold the command
	while(!(command == 'q')){ //create the player space, will run until the user inputs quit. then the program will exit
		cout << '>'; //prompt

		cin >> command; //read input

		switch(command){ //check what user input
			case 'l': //did they look?
				look(arrPtr[playerPos]);
				break;
			case 'n': //statements for direction
			case 's':
			case 'e':
			case 'w':
				move(arrPtr[playerPos], command, playerPos);
				break;
			}
	}


	return 0;
}



