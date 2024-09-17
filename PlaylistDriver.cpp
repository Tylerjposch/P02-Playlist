// PlaylistDriver.cpp -- MOST FUNCTIONS ARE COMPLETE -- "processMenuChoice" needs to be done
// DO NOT INCLUDE ANYTHING OTHER THAN THESE LIBRARIES/CLASSES
#include <iostream>
#include <string>
#include <limits>
#include "Playlist.h"

using namespace std;

// THE FOLLOWING FUNCTION DECLARATIONS ARE COMPLETE -- DO NOT CHANGE
char getMenuChoice();
void processMenuChoice(char, Playlist&);
int getInteger();
bool isInteger(const string& s);

// THE FOLLOWING FUNCTION IS COMPLETE -- DO NOT CHANGE
int main() {
	Playlist playlist;
	char choice = ' ';

	choice = getMenuChoice();

	while (choice != 'q') {
		processMenuChoice(choice, playlist);
		choice = getMenuChoice();
	}

	cout << "\n>>> Exiting Playlist <<<" << endl;
	cout << "\n>>> Playlist Destructor Called <<<" << endl;

	return 0;
}

// THE FOLLOWING FUNCTION IS COMPLETE -- DO NOT CHANGE
char getMenuChoice() {
	// Output menu option, prompt users for valid selection
	string menuOptions = "adpstocq";
	char choice = ' ';

	do {
		cout << "\n ************** PLAYLIST MENU **************************" << endl;

		cout << "\ta - Add song" << endl;
		cout << "\td - Remove song" << endl;
		cout << "\tp - Change position of song" << endl;
		cout << "\ts - Output songs by specific artist" << endl;
		cout << "\tt - Output total time of playlist (in seconds)" << endl;
		cout << "\to - Output full playlist" << endl;
		cout << "\tc - Clear playlist" << endl;
		cout << "\tq - Quit" << endl << endl;

		cout << "\tChoose option: ";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << " *******************************************************" << endl;

	} while (menuOptions.find(choice) == string::npos);

	return choice;
}

// ************************** TO BE COMPLETED ******************************************
void processMenuChoice(char choice, Playlist& playlist) {
	// Declaration of local variables needed for this function
	string uniqueID;
	string songName;
	string artistName;
	int songLength;

	// COMPLETE THE ACTIONS FOR EACH CHOICE
	// Call corresponding menu action -- don't forget to add "break" statements
	switch (choice) {
		case 'a':
		// Add song to playlist
		// Prompt user for song unique id
			cout << "Add Song - Enter song's unique ID: ";
			cin >> uniqueID;
		// if the playlist already contains this id
		//		print message and break
			if (playlist.contains(uniqueID)) {
				cout << "<<< Duplicate unique ID - not added! >>>" << endl;
				break;
			}
		// otherwise
		//		prompt for the rest of the song information
		//		create a new SongNode
		//		insert at the front of the playlist
		//		print the playlist
			else {
				cout << "           Enter song's name: ";
				cin.ignore();
				getline(cin, songName);
				cout << "           Enter artist's name: ";
				getline(cin, artistName);
				cout << "           Enter song's length (in seconds): ";
				cin >> songLength;
				SongNode* songPtr = new SongNode(uniqueID, songName, artistName, songLength, nullptr);
				playlist.insertFront(songPtr);
				playlist.printPlaylist();
				break;
			}
		case 'd':
		// Remove song from playlist
		// Prompt user for song unique id
		// call remove
		// print appropriate message based on results from remove
			cout << "Delete Song - Enter song's unique ID: ";
			cin >> uniqueID;
			cout << endl;
			if (playlist.contains(uniqueID) != true) {
				cout << "<<< Song with unique ID " << uniqueID << " is not in playlist! >>>" << endl;
				playlist.printPlaylist();
				break;
			}
			else {
				playlist.remove(uniqueID);
				cout << "<<< Successfully deleted song with unique ID " << uniqueID << " >>>" << endl;
				break;
			}
		// print the playlist
		case 'p':
		// Change song position in playlist
		// count the number of songs in the list
		// if the count <=1
		//		print appropriate message
			if (playlist.getNodeCount() <= 1) {
				playlist.printPlaylist();
				cout << ">>> Playlist is empty! <<<" << endl;
				break;
			}
		//	cout << "Change Song's Playlist Position -" << endl;
		//	cout << "        Current position (1 through " << playlist.getNodeCount() << "): ";
		// otherwise
		//		ask user for valid current position -- use getInteger() to get value
		//			if entry invalid break with appropriate message
		//		ask user for valid new position -- use getInteger() to get value
		//			if entry invalid break with appropriate message
		//
		//		call changeSongPosition
		//		print out message
		//		print playlist
			else {
				int currPos;
				int endPos;
				cout << "Change Song's Playlist Position -" << endl;
				cout << "        Current position (1 through " << playlist.getNodeCount() << "): ";
				cin >> currPos;
				if ((currPos < 1) || (currPos > playlist.getNodeCount())){
					cout << endl;
					cout << "<<< Invalid current position!  >>>" << endl;
					cout << endl;
					break;
				}
				cout << "        New position (1 through " << playlist.getNodeCount() << "): ";
				cin >> endPos;
				if ((currPos == endPos) || (endPos < 1) || (endPos > playlist.getNodeCount())) {
					cout << endl;
					cout << "<<< Invalid new position! >>>" << endl;
					cout << endl;
					break;
				}
				playlist.changeSongPosition(currPos, endPos);
				cout << endl;
				cout << "<<< Song moved from position " << currPos << " to position " << endPos << " >>>" << endl;
				cout << endl;
				playlist.printPlaylist();
				break;
			}
		case 's':
		// prompt the user for the artist's name
		// Output playlist for specific artist
			cout << "Search Playlist - Enter artist's name: ";
			getline(cin, artistName);
			playlist.printByArtist(artistName);
			break;
		case 't':
		// Output playlist total time
			cout << "Playlist Total Time - " << playlist.getTotalTime() << endl;
			break;
		case 'o':
		// Print the playlist
			playlist.printPlaylist();
			break;
		case 'c':
		// Clear the playlist
			playlist.clearList();
			cout << ">>> Playlist has been cleared! <<<" << endl;
			break;
	}
}

// THE FOLLOWING FUNCTIONS ARE COMPLETE.
// CAN BE USED TO GET AN INTEGER AND DO THE APPROPRIATE VALIDATION
//		getInteger() uses isInteger()
int getInteger() {
	string str = "";
	getline(cin, str);

	while (!(isInteger(str))) {
		cout << "\t\t\t>>> Invalid integer - please enter an integer: ";
		getline(cin, str);
	}

	// convert str to an int
	return stoi(str);
}

bool isInteger(const std::string& s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char* p; //stores the first location of non-integer character

	// The C library function long int strtol(const char *str, char **endptr, int base)
	//		converts the initial part of the string in str to a long int value according
	//		to the given base, which must be between 2 and 36 inclusive, or be the special value 0.
	strtol(s.c_str(), &p, 10);

	return (*p == 0); // will be true if s contains an integer
}