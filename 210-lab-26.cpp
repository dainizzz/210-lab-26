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

const int WIDTH = 10;
// These three constants are used for the 3D results array
const int DEPTH = 15;
const int ROWS = 4;
const int COLS = 3;

// readingRace() reads data from a file to a set, std::list, and vector and saves how long it took to perform the operations to an array
// arguments: an empty set of type string, an empty std::list of type string, an empty vector of type string, an array
//		of size COLS and type long long
// returns: nothing
void readingRace(set<string> &, list<string> &, vector<string> &, long long [COLS]);

// sortingRace() sorts data in a std::list and vector and saves how long it took to perform the sort in an array. Because sets are
//      already sorted, -1 is output as the duration value for sorting the set.
// arguments: a std::list of strings and a vector of strings, an array of size COLS and type long long
// returns: nothing
void sortingRace(list<string> &, vector<string> &, long long [COLS]);

// insertingRace() inserts the value "TESTCODE" into the middle of a std::list and vector and into a set, and saves
//      how long it took to perform the operations in an array.
// arguments: a set of strings, a std::list of strings, a vector of strings, an array of size COLS and type long long
// returns: nothing
void insertingRace(set<string> &, list<string> &, vector<string> &, long long [COLS]);

// deletingRace() deletes the value in the middle of a set, std::list, and vector and saves how long it took to
//      perform the operations in an array.
// arguments: a set of strings, a std::list of strings, a vector of strings, an array of size COLS and type long long
// returns: nothing
void deletingRace(set<string> &, list<string> &, vector<string> &, long long [COLS]);

// resetRacers() empties the data structures to prepare them for the next iteration of races
// arguments: a set of strings, a std::list of strings, a vector of strings
// returns: nothing
void resetRacers(set<string> &, list<string> &, vector<string> &);

int main() {
	set<string> set;
	list<string> list;
	vector<string> vector;

	// 3D array: depth, rows, columns
	// depth: each iteration of the test being conducted
	// rows: each of the races (reading, sorting, etc.)
	// columns: each of data structures (set, etc.)
	long long resultsArray[DEPTH][ROWS][COLS] {};

	// Conducting 15 rounds of races and saving the results to resultsArray
	for (int i = 0; i < DEPTH; i++) {
		// RACE 1: READING
		readingRace(set, list, vector, resultsArray[i][0]); // 0 is the index for the reading race row

		// RACE 2: SORTING
		sortingRace(list, vector, resultsArray[i][1]); // 1 is the index for the sorting race row

		// RACE 3: INSERTING
		insertingRace(set, list, vector, resultsArray[i][2]); // 2 is the index for the inserting race row

		// RACE 4: DELETING
		deletingRace(set, list, vector, resultsArray[i][3]); // 3 is the index for the deleting race row

		// RESETTING FOR NEXT ROUND OF RACES
		resetRacers(set, list, vector);
	}

	// Initializing variables for holding the sums for each type of race and data structure.
	// The 1st letter refers to the type of race (e.g. R for reading) & the 2nd to the data structure (e.g. V for vector)
	long long sumRV = 0;
	long long sumRL = 0;
	long long sumRS = 0;
	long long sumSV = 0;
	long long sumSL = 0;
	long long sumSS = 0;
	long long sumIV = 0;
	long long sumIL = 0;
	long long sumIS = 0;
	long long sumDV = 0;
	long long sumDL = 0;
	long long sumDS = 0;

	// The for loop is going through each "slice" of the 3D array, i.e. each of the 15 rounds of races, and adding the
	// relevant data to the sum variables.
	for (int i = 0; i < DEPTH; i++) {
		// The first [] (i) represents the current round of races
		// The second [] represents the type of race: 0 for reading, 1 for sorting, 2 for inserting, 3 for deleting
		// The third [] represents the type of data structure: 0 for vector, 1 for list, 2 for set
		sumRV += resultsArray[i][0][0];
		sumRL += resultsArray[i][0][1];
		sumRS += resultsArray[i][0][2];
		sumSV += resultsArray[i][1][0];
		sumSL += resultsArray[i][1][1];
		sumSS += resultsArray[i][1][2];
		sumIV += resultsArray[i][2][0];
		sumIL += resultsArray[i][2][1];
		sumIS += resultsArray[i][2][2];
		sumDV += resultsArray[i][3][0];
		sumDL += resultsArray[i][3][1];
		sumDS += resultsArray[i][3][2];
	}

	cout << "Number of simulations: 15" << endl;
	cout << setw(WIDTH) << "Operation\tVector\tList\tSet" << endl;
	cout << setw(WIDTH) << "Read \t" << sumRV / 15 << '\t' << sumRL / 15 << '\t' << sumRS / 15 << endl;
	cout << setw(WIDTH) << "Sort \t" << sumSV / 15 << '\t' << sumSL / 15 << '\t' << sumSS / 15 << endl;
	cout << setw(WIDTH) << "Insert \t" << sumIV / 15 << '\t' << sumIL / 15 << '\t' << sumIS / 15 << endl;
	cout << setw(WIDTH) << "Delete \t" << sumDV / 15 << '\t' << sumDL / 15 << '\t' << sumDS / 15 << endl;

	return 0;
}

void readingRace(set<string> &set, list<string> &list, vector<string> &vector, long long results[COLS]) {
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

	// VECTOR / LIST / SET are the columns
	results[0] = vectorDuration.count();
	results[1] = listDuration.count();
	results[2] = setDuration.count();
}

void sortingRace(list<string> &list, vector<string> &vector, long long results[COLS]) {
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

	// VECTOR / LIST / SET are the columns
	results[0] = vectorDuration.count();
	results[1] = listDuration.count();
	results[2] = -1;
}

void insertingRace(set<string> &set, list<string> &list, vector<string> &vector, long long results[COLS]) {
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

	// VECTOR / LIST / SET are the columns
	results[0] = vectorDuration.count();
	results[1] = listDuration.count();
	results[2] = setDuration.count();
}

void deletingRace(set<string> &set, list<string> &list, vector<string> &vector, long long results[COLS]) {
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

	// VECTOR / LIST / SET are the columns
	results[0] = vectorDuration.count();
	results[1] = listDuration.count();
	results[2] = setDuration.count();
}

void resetRacers(set<string> &set, list<string> &list, vector<string> &vector) {
	set.clear();
	list.clear();
	vector.clear();
}
