// Playlist.cpp -- MOST FUNCTIONS TO BE COMPLETED -- READ COMMENTS
// DO NOT INCLUDE ANYTHING OTHER THAN THESE LIBRARIES/CLASSES
#include <iostream>
#include "Playlist.h"
using namespace std;

// ************************** TO BE COMPLETED ******************************************
//Default and only constructor -- call private function init
Playlist::Playlist() {
	this->init();
}
// ************************** TO BE COMPLETED ******************************************
//Destructor -- call private function eraseList with head
Playlist::~Playlist() {
	this->eraseList(this->head);
}

// ************************** TO BE COMPLETED ******************************************
int Playlist::getNodeCount() {
	return this->nodeCount;
}

// ************************** TO BE COMPLETED ******************************************
//Add a SongNode to the front of the list
void Playlist::insertFront(SongNode* songNode) {
	SongNode* newSong = songNode;
	if (this->head == nullptr) {
		this->head = newSong;
	}
	else {
		newSong->setNext(this->head);
		this->head = newSong;
	}
	this->nodeCount += 1;
}
// ************************** TO BE COMPLETED ******************************************
//Remove an SongNode from the list; if the value doesn't exist in the list return false;
//   otherwise search for the SongNode, adjust pointers, and return true.
bool Playlist::remove(string id) {
	if (!contains(id)) {
		return false;
	}
	SongNode* curr = this->head;
	SongNode* prev = this->head;
	while (curr->getUniqueID() != id) {
		prev = curr;
		curr = curr->getNext();
	}
	if (curr == head) {
		head = curr->getNext();
		delete curr;
	}
	else {
		prev->setNext(curr->getNext());
		delete curr;
	}
	this->nodeCount -= 1;
	return true;
}

// ************************** TO BE COMPLETED ******************************************
//This function is the most complicated
//   songPosition and newPosition values have been validated in main
//		before this function is called
void Playlist::changeSongPosition(int songPosition, int newPosition) {
	// STEP 1: Find songNode that is at songPosition
	SongNode* fromPosNode = head;
	SongNode* prevNode;
	SongNode* insertPosNode;
	int listPos = 1;
	while ((fromPosNode != nullptr) && (listPos < songPosition)) {
		fromPosNode = fromPosNode->getNext();
		++listPos;
	}
	// STEP 2: Remove songNode at songPosition from list. Keep reference to that songNode.
	// If songPosition was 1, song being moved was the head of the list
	//		so change what head points to
	// otherwise
	//		find the node before songNode in the list and adjust that node's
	//		next pointer
	if (fromPosNode == head) {
		head = fromPosNode->getNext();
	}
	else {
		prevNode = head;
		while (prevNode->getNext() != fromPosNode) {
			prevNode = prevNode->getNext();
		}
		prevNode->setNext(fromPosNode->getNext());
	}
	// At this point songNode is no longer in the list
	// STEP 3: Insert song at newPosition
	//	If the newPosition was 1 ... the songNode will become the head of the list
	//		adjust pointers appropriately
	//	otherwise
	//		find the node that is before the newPosition
	//		it will be somewhere after original head position or at
	//		the end of the list
	//		call insertAfter
	if (newPosition == 1) {
		fromPosNode->setNext(head);
		head = fromPosNode;
	}
	else {
		prevNode = head;
		insertPosNode = head;
		if (insertPosNode == nullptr) {
			this->insertAfter(prevNode, fromPosNode);
		}
		else {
			for (int i = 1; i < newPosition - 1; ++i) {
				prevNode = prevNode->getNext();
			}
			this->insertAfter(prevNode, fromPosNode);
		}
	}
}


// ************************** TO BE COMPLETED ******************************************
// insertAfter ... inserts newNode after prevNode
void Playlist::insertAfter(SongNode* prevNode, SongNode* newNode) {
	newNode->setNext(prevNode->getNext());
	prevNode->setNext(newNode);
}

// ************************** TO BE COMPLETED ******************************************
// calculate total time in seconds in playlist
int Playlist::getTotalTime() {
	SongNode* curr = head;
	SongNode* succ;
	int runtime = 0;
	while (curr != nullptr) {
		succ = curr->getNext();
		runtime += curr->getSongLength();
		curr = succ;
	}
	return runtime;
}

// ************************** TO BE COMPLETED ******************************************
// Print out all nodes in the list
void Playlist::printPlaylist() {
	this->printTableHeadings();
	SongNode* curr = head;
	SongNode* succ;
	int songPos = 1;
	while (curr != nullptr) {
		succ = curr->getNext();
		this->printTableRow(curr, songPos);
		++songPos;
		curr = succ;
	}
}

// ************************** TO BE COMPLETED ******************************************
// Print out all nodes in the list with the artist's name
void Playlist::printByArtist(string artist) {
	this->printTableHeadings();
	SongNode* curr = head;
	SongNode* succ;
	int songPos = 1;
	while (curr != nullptr) {
		succ = curr->getNext();
		if (curr->getArtistName() == artist) {
			this->printTableRow(curr, songPos);
		}
		++songPos;
		curr = succ;
	}
}

// ************************** TO BE COMPLETED ******************************************
// Search to see if list contains the uniqueID
bool Playlist::contains(const string& id) {
	SongNode* curr = this->head;
	while (curr != nullptr) {
		if (id == curr->getUniqueID()) {
			return true;
		}
		else {
			curr = curr->getNext();
		}
	}
	return false;
}

// ************************** TO BE COMPLETED ******************************************
// Clear the list -- remove all nodes and initialize the playlist again
void Playlist::clearList() {
	this->init();
}

// ************************** TO BE COMPLETED ******************************************
// Set up linked list starting values
void Playlist::init() {
	this->head = nullptr;
	this->nodeCount = 0;
}

// ************************** TO BE COMPLETED ******************************************
// Delete all allocated objects
void Playlist::eraseList(SongNode* head) {
	SongNode* curr = head;
	SongNode* succ;
	while (curr != nullptr) {
		succ = curr->getNext();
		delete curr;
		curr = succ;
	}
}

// COMPLETED -- DO NOT CHANGE
// Print headings for playlist table
void Playlist::printTableHeadings() {
	cout << "\n\t------------------------- PLAYLIST ------------------------------" << endl;
	cout << "\t" << setw(5) << left << "Pos  ";
	cout << setw(12) << left << "Unique Id";
	cout << setw(20) << left << "Song";
	cout << setw(20) << left << "Artist";
	cout << setw(4) << left << "Time" << endl;
}

// COMPLETED -- DO NOT CHANGE
void Playlist::printTableRow(SongNode* song, int position) {
	cout << "\t" << setw(5) << left << position;
	cout << setw(12) << left << song->getUniqueID();
	cout << setw(20) << left << song->getSongName();
	cout << setw(20) << left << song->getArtistName();
	cout << setw(4) << right << song->getSongLength() << endl;
}