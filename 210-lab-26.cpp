// COMSC-210 | Lab 26 | Dainiz Almazan
// IDE used: CLion

#include <algorithm>
#include <iostream>
#include <chrono>
#include <list>
#include <set>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
using namespace std::chrono;

const int WIDTH = 15;
const int DEPTH = 15;
const int ROWS = 4;
const int COLS = 3;

// readingRace() reads data from a file to a set, std::list, and vector and outputs how long it took to read data to each.
// arguments: an empty set of type string, an empty std::list of type string, an empty vector of type string
// returns: nothing
void readingRace(set<string> &, list<string> &, vector<string> &, long [ROWS][COLS]);

// sortingRace() sorts data in a std::list and vector and outputs how long it took to perform the sort. Because sets are
//      already sorted, -1 is output as the duration value for sorting the set.
// arguments: a std::list of strings and a vector of strings
// returns: nothing
void sortingRace(list<string> &, vector<string> &);

// insertingRace() inserts the value "TESTCODE" into the middle of a std::list and vector and into a set, and outputs
//      how long it took to perform the operations.
// arguments: a set of strings, a std::list of strings, a vector of strings
// returns: nothing
void insertingRace(set<string> &, list<string> &, vector<string> &);

// deletingRace() deletes the value in the middle of a set, std::list, and vector and outputs how long it took to
//      perform the operations.
// arguments: a set of strings, a std::list of strings, a vector of strings
// returns: nothing
void deletingRace(set<string> &, list<string> &, vector<string> &);

// resetRacers() empties the data structures to prepare them for the next iteration of races
// arguments: a set of strings, a std::list of strings, a vector of strings
// returns: nothing
void resetRacers(set<string> &, list<string> &, vector<string> &);

int main() {
	set<string> set;
	list<string> list;
	vector<string> vector;

	// 3D array: depth, rows, columns
	// rows: types of races
	// columns: types of data structures
	// depth: each iteration of the test being conducted
	long resultsArray[DEPTH][ROWS][COLS];

	// Add placeholder values to array
	for (int i = 0; i < DEPTH; i++) {
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLS; col++) {
				resultsArray[i][row][col] = 0;
			}
		}
	}

	// RACE 1: READING
	readingRace(set, list, vector);

	// RACE 2: SORTING
	sortingRace(list, vector);

	// RACE 3: INSERTING
	insertingRace(set, list, vector);

	// RACE 4: DELETING
	deletingRace(set, list, vector);

	// RESETTING FOR NEXT SET OF RACES
	resetRacers(set, list, vector);

	cout << setw(WIDTH) << "Operation\tVector\tList\tSet" << endl;

	return 0;
}

void readingRace(set<string> &set, list<string> &list, vector<string> &vector, long round[ROWS][COLS]) {
	ifstream infile("codes.txt");
	string temp;

	// Reading to set
	auto start = high_resolution_clock::now();
	while (infile >> temp) {
		set.insert(temp);
	}
	auto end = high_resolution_clock::now();
	auto setDuration = duration_cast<microseconds>(end - start);

	// Resetting to start of file
	infile.clear();
	infile.seekg(0, ios::beg);

	// Reading to list
	start = high_resolution_clock::now();
	while (infile >> temp) {
		list.push_back(temp);
	}
	end = high_resolution_clock::now();
	auto listDuration = duration_cast<microseconds>(end - start);

	// Resetting to start of file
	infile.clear();
	infile.seekg(0, ios::beg);

	// Reading to vector
	start = high_resolution_clock::now();
	while (infile >> temp) {
		vector.push_back(temp);
	}
	end = high_resolution_clock::now();
	auto vectorDuration = duration_cast<microseconds>(end - start);

	infile.close();

	// Outputting results
	cout << setw(WIDTH) << "Read \t" << vectorDuration.count() << '\t' << listDuration.count() << '\t' << setDuration.
			count() << endl;
}

void sortingRace(list<string> &list, vector<string> &vector) {
	// Sorting list
	auto start = high_resolution_clock::now();
	list.sort();
	auto end = high_resolution_clock::now();
	auto listDuration = duration_cast<microseconds>(end - start);

	// Sorting vector
	start = high_resolution_clock::now();
	sort(vector.begin(), vector.end());
	end = high_resolution_clock::now();
	auto vectorDuration = duration_cast<microseconds>(end - start);

	// Outputting results
	cout << setw(WIDTH) << "Sort \t" << vectorDuration.count() << '\t' << listDuration.count() << "\t -1" << endl;
}

void insertingRace(set<string> &set, list<string> &list, vector<string> &vector) {
	// Inserting in set
	auto start = high_resolution_clock::now();
	set.insert("TESTCODE");
	auto end = high_resolution_clock::now();
	auto setDuration = duration_cast<microseconds>(end - start);

	// Inserting in middle of list
	start = high_resolution_clock::now();
	int middle = (list.size() / 2) - 1; // subtracting 1 because iterator begins at first element
	auto it = list.begin();
	advance(it, middle);
	list.insert(it, "TESTCODE");
	end = high_resolution_clock::now();
	auto listDuration = duration_cast<microseconds>(end - start);

	// Inserting in middle of vector
	start = high_resolution_clock::now();
	middle = (vector.size() / 2) - 1;
	vector.insert((vector.begin() + middle), "TESTCODE");
	end = high_resolution_clock::now();
	auto vectorDuration = duration_cast<microseconds>(end - start);

	// Outputting results
	cout << setw(WIDTH) << "Insert \t" << vectorDuration.count() << '\t' << listDuration.count() << '\t' << setDuration.
			count() << endl;
}

void deletingRace(set<string> &set, list<string> &list, vector<string> &vector) {
	// Deleting middle element in set
	auto start = high_resolution_clock::now();
	int middle = (set.size() / 2) - 1;
	auto it = set.begin();
	advance(it, middle);
	set.erase(it);
	auto end = high_resolution_clock::now();
	auto setDuration = duration_cast<microseconds>(end - start);

	// Deleting middle element in list
	start = high_resolution_clock::now();
	middle = (list.size() / 2) - 1;
	auto it2 = list.begin();
	advance(it2, middle);
	list.erase(it2);
	end = high_resolution_clock::now();
	auto listDuration = duration_cast<microseconds>(end - start);

	// Deleting middle element in vector
	start = high_resolution_clock::now();
	middle = (vector.size() / 2) - 1;
	vector.erase(vector.begin() + middle);
	end = high_resolution_clock::now();
	auto vectorDuration = duration_cast<microseconds>(end - start);

	// Outputting results
	cout << setw(WIDTH) << "Delete \t" << vectorDuration.count() << '\t' << listDuration.count() << '\t' << setDuration.
			count() << endl;
}

void resetRacers(set<string> &set, list<string> &list, vector<string> &vector) {
	set.clear();
	list.clear();
	vector.clear();
}
