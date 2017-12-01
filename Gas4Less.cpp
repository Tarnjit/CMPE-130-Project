#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

void Merge(double *a, int l, int r, int m);

void MergeSort(double *a, int l, int r);

int choose_Octane();

int cheapest_Gas(int oct, char *file);

int value = 0;

char file1[] = "Chevron.txt";
char file2[] = "Shell.txt";
char file3[] = "76.txt";
char file4[] = "Valero.txt";
char file5[] = "Arco.txt";
char file6[] = "RottenRobbie.txt";

int main() {

	char choice;
	int oct = 0;
	int y = 0;

	do {
		cout << "     GAS 4 LESS " << endl;
		cout << "=====================================" << endl;
		cout << "What brand gasoline would you like?\n" << endl;
		cout << " 1. Chevron" << endl;
		cout << " 2. Shell" << endl;
		cout << " 3. 76" << endl;
		cout << " 4. Valero" << endl;
		cout << " 5. Arco" << endl;
		cout << " 6. Rotten Robbie" << endl;
		cout << " 7. Exit   " << endl;
		cout << "=====================================" << endl;
		cout << "\nEnter Your Choice: ";
		cin >> choice;
		switch (choice) {
		case '1':
			cout << "You chose Chevron.\n" << endl;
			oct = choose_Octane();
			y = cheapest_Gas(oct, file1);					// uses MergeSort to find cheapest priced gasoline based on desired octane
			break;

		case '2':
			cout << "You chose Shell. " << endl;
			oct = choose_Octane();
			y = cheapest_Gas(oct, file2);
			break;

		case '3':
			cout << "You chose 76. " << endl;
			oct = choose_Octane();
			y = cheapest_Gas(oct, file3);
			break;

		case '4':
			cout << "You chose Valero. " << endl;
			oct = choose_Octane();
			y = cheapest_Gas(oct, file4);
			break;

		case '5':
			cout << "You chose Arco. " << endl;
			oct = choose_Octane();
			y = cheapest_Gas(oct, file5);
			break;

		case '6':
			cout << "You chose Rotten Robbie. " << endl;
			oct = choose_Octane();
			y = cheapest_Gas(oct, file6);
			break;

		case '7':
			y = 1;
			break;

		default:
			cout << "Enter a Valid Choice." << endl;

		}
		cout << endl;

	} while (y != 1);

	return 0;
	// main()

}

// Merges two halves to become sorted data.
void Merge(double *a, int l, int r, int m) {
	// Sorted left to middle section of data and middle+1 to right section of data
	int i, j, k;
	double temp[r - l + 1];
	i = l;
	k = 0;
	j = m + 1;

	// Merge two parts.
	while (i <= m && j <= r) {
		if (a[i] < a[j]) {
			temp[k] = a[i];
			k++;
			i++;
		} else {
			temp[k] = a[j];
			k++;
			j++;
		}
	}


	while (i <= m) {
		temp[k] = a[i];
		k++;
		i++;
	}


	while (j <= r) {
		temp[k] = a[j];
		k++;
		j++;
	}

	// Store sorted data into array a.
	for (i = l; i <= r; i++) {
		a[i] = temp[i - l];
	}
}

// Divides array into two sections.
void MergeSort(double *a, int l, int r) {

	int m;

	if (l < r) {
		m = (l + r) / 2;
		// Divides data into two halves.
		MergeSort(a, l, m);
		MergeSort(a, m + 1, r);

		// Merges data for the final sorted array.
		Merge(a, l, r, m);
	}
}

int choose_Octane() {
	int choice;

	cout << "What octane gas would you like?\n" << endl;

	cout << " 1. Octane 87" << endl;
	cout << " 2. Octane 89" << endl;
	cout << " 3. Octane 91" << endl;

	cin >> choice;

	if (choice == 1)
		cout << "You chose 87.\n" << endl;

	if (choice == 2)
		cout << "You chose 89.\n" << endl;

	if (choice == 3)
		cout << "You chose 91.\n" << endl;

	choice -= 1;

	return choice;
}

int cheapest_Gas(int oct, char *file) {

	int choice = 0;
	int row = 0;
	int col = 0;
	int maxRow = 0;					// Number of available gasoline stations initialized to 0
	int maxCol = 3;					// Number of octane gasolines (87, 89, 91)

	string sRow = "\0";

	ifstream myfile;
	myfile.open(file);

	if (myfile.fail()) {
		cout << file << " open failure" << endl;
		exit(1);
	}

	//Acquiring number of available gasoline stations.
	getline(myfile, sRow, '\n');

	// Convert row string to int
	string s = "\0";

	s = sRow;
	stringstream vertRow(s);
	vertRow >> maxRow;

	string gas[maxRow][maxCol];			// Holds gasoline prices of different octane, col 0 = 87, col 1 = 89, col 2 = 91
	double gas2[maxRow][maxCol];		// Holds converted string data to double data used for MergeSort
	string address[maxRow];				// Holds location of gasoline stations
	double price[maxRow];				// Holds gasoline prices of desired octane

	// Read data in as strings
	for (row = 0; row < maxRow; row++) {

		getline(myfile, address[row], '\n');
		for (col = 0; col < maxCol; col++) {
			getline(myfile, gas[row][col]);
		}
	}

	// Convert gas prices into doubles
	for (row = 0; row < maxRow; row++) {

		for (col = 0; col < maxCol; col++) {
			string s = "\0";
			s = gas[row][col];

			stringstream vert(s);

			vert >> gas2[row][col];

		}
	}

	// Store all prices of desired octane gasoline into single array
	for (row = 0; row < maxRow; row++) {
		price[row] = gas2[row][oct];
	}

	// Mergesort single array
	MergeSort(price, 0, maxRow - 1);

#if 0
	// Print out sorted gasoline prices
	for (row = 0; row < maxRow; row++) {
		cout << price[row] << fixed << setprecision(2) << endl;
	}

#endif

	// Grab cheapest price
	double min = price[0];
	cout << "Cheapest price: $" << min << endl;

	// Match it with address using two-dimensional array gas2

	for (row = 0; row < maxRow; row++) {

		for (col = 0; col < maxCol; col++) {

			if (gas2[row][oct] == min) {
				cout << "Located at: " << address[row] << endl << endl;
				break;
			}

		}
	}

	myfile.close();

	cout << "Try again with a different brand gasoline?" << endl;
	cout << "1. Yes." << endl;
	cout << "2. No." << endl;

	cin >> choice;

	if (choice == 2)
		return 1;

	else
		return 0;

}

