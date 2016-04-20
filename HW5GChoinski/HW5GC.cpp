#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>

using namespace std;

void OneRun(string fileName);
bool ReadFile(string fileName, vector<int> &getWords);
void BubbleSort(vector<int> &getWords, int &numOfComp, int &numOfSwaps);
void InsetrionSort(vector<int> &getWords, int &numOfComp, int &numOfSwaps);
void Quicksort(vector<int> &getWords, int left, int right, int &numOfComp, int &numOfSwaps);
void ShellSort(vector<int> &getWords, int &numOfComp, int &numOfSwaps);
void MergeSort(vector<int> &getWords, int low, int high, int &numOfComp, int &numOfSwaps);

void main()
{
	string fileName;
	//cout << "Enter the file name: " << endl;	//asks user for the file name and opens it	
	//cin >> fileName;
	OneRun("test.txt");	//executes function OneRun for particular file
	OneRun("test2.txt");
	OneRun("test3.txt");
	OneRun("Random.txt");
	OneRun("Reversed.txt");
	OneRun("NearlySorted.txt");
	OneRun("FewUnique.txt");
}
void OneRun(string fileName)	//this function reads provided file, sets number of comparisons and swaps to 0 and launches 5 types of sorts 
{								//it prints out to the console name of the sort, name of the file and number of comparisons and swaps
	vector<int> getWords;	//creates vector for integers
	ReadFile(fileName, getWords);	//launches function ReadFile
	int numOfComp = 0;	//sets number of comparisons to 0
	int numOfSwaps = 0;	//sets number of swaps (exchanges) to 0
	BubbleSort(getWords, numOfComp, numOfSwaps);	//launches Bubble sort
	cout << "Bubble Sort for " << fileName << " took " << numOfComp << " comparisons and " << numOfSwaps << " swaps." << endl;	//prints out for which file how many comparisons and swaps were made
	
	getWords.clear();	//clears vector getWords
	ReadFile(fileName, getWords);
	numOfComp = 0;
	numOfSwaps = 0;
	InsetrionSort(getWords, numOfComp, numOfSwaps);
	cout << "Insetrion Sort for " << fileName << " took " << numOfComp << " comparisons and " << numOfSwaps << " swaps." << endl;

	getWords.clear();
	ReadFile(fileName, getWords);
	numOfComp = 0;
	numOfSwaps = 0;
	Quicksort(getWords, 0, getWords.size() - 1, numOfComp, numOfSwaps);
	cout << "Quick Sort for " << fileName << " took " << numOfComp << " comparisons and " << numOfSwaps << " swaps." << endl;
	
	getWords.clear();
	ReadFile(fileName, getWords);
	numOfComp = 0;
	numOfSwaps = 0;
	ShellSort(getWords, numOfComp, numOfSwaps);
	cout << "Shell Sort for " << fileName << " took " << numOfComp << " comparisons and " << numOfSwaps << " swaps." << endl;

	getWords.clear();
	ReadFile(fileName, getWords);
	numOfComp = 0;
	numOfSwaps = 0;
	MergeSort(getWords, 0, getWords.size() - 1, numOfComp, numOfSwaps);
	cout << "Merge Sort for " << fileName << " took " << numOfComp << " comparisons and " << numOfSwaps << " swaps.\n" << endl;
}

bool ReadFile(string fileName, vector<int> &getWords)	//reads from the file and put integers into a vector
{
	ifstream in;
	in.open(fileName);	//opens provided file
	if (!in.is_open())	//if could not find the file will let the user know
	{
		cout << "I could not find " << fileName << endl;
		return false;
	}
	int word;
	while (in.peek() != EOF)	//while file is open reads the file and push integers to the vector
	{
		in >> word;
		getWords.push_back(word);
	}
	in.clear();
	in.close();	
	return true;
}

void BubbleSort(vector<int> &getWords, int &numOfComp, int &numOfSwaps)
{
	int i, j, tmp;
	for (i = 1; i < getWords.size(); i++)	//number of passes
	{
		for (j = 0; j < getWords.size() - 1; j++)	//j varies from 0 to size-1
		{
			if (getWords[j] > getWords[j + 1])	//compare two successive numbers
			{
				tmp = getWords[j];	//swap getWords[j] with getWords[j+1]
				getWords[j] = getWords[j + 1];
				getWords[j + 1] = tmp;
				numOfSwaps++;	//increases number of swaps
			}
			numOfComp++;	//increases number of comparisons
		}
	}
}

void InsetrionSort(vector<int> &getWords, int &numOfComp, int &numOfSwaps)
{
	int i, j, el;
	for (i = 1; i < getWords.size(); i++)
	{
		el = getWords[i];	//insert ith element in  0 to i-1 array
		j = i;	
		while ((j > 0) && (getWords[j - 1] > el))	//compare if getWords[j-1]>element
		{
			getWords[j] = getWords[j - 1];	//shift elements
			j = j - 1;
			numOfSwaps++;	//increases number of swaps
			numOfComp++;	//increases number of comparisons
		}
		getWords[j] = el;	//place element at jth position
		if (j > 0)
		{
			numOfComp++;	//increases number of comparisons
		}
	}
}

int Partition(vector<int> &getWords, int left, int right, int pivotIndex, int &numOfComp, int &numOfSwaps)
{
	int pivot = getWords[pivotIndex];
	do
	{
		while (getWords[left] < pivot)
		{
			left++;
			numOfComp++;	//increases number of comparisons
		}
		numOfComp++;
		while (getWords[right] > pivot)
		{
			right--;
			numOfComp++;	//increases number of comparisons
		} 
		numOfComp++;
		if (left < right && getWords[left] != getWords[right])
		{
			swap(getWords[left], getWords[right]);
			numOfSwaps++;	//increases number of exchanges
		}
		else
		{
			return right;
		}
	} while (left < right);
	return right;
}
void Quicksort(vector<int> &getWords, int left, int right, int &numOfComp, int &numOfSwaps)
{
	if (left < right)
	{
		int pivot = (left + right) / 2; // middle
		int pivotNew = Partition(getWords, left, right, pivot, numOfComp, numOfSwaps);
		Quicksort(getWords, left, pivotNew - 1, numOfComp, numOfSwaps);
		Quicksort(getWords, pivotNew + 1, right, numOfComp, numOfSwaps);
	}
}

void ShellSort(vector<int> &getWords, int &numOfComp, int &numOfSwaps)
{
	int tmp, gap, i;
	int swapped;
	gap = getWords.size() / 2;
	do
	{
		do
		{
			swapped = 0;
			for (i = 0; i < getWords.size() - gap; i++)
			{
				if (getWords[i] > getWords[i + gap])
				{
					tmp = getWords[i];
					getWords[i] = getWords[i + gap];
					getWords[i + gap] = tmp;
					swapped = 1;
					numOfSwaps++;	//increases number of swaps
				}
				numOfComp++;	//increases number of comparisons
			}
		} while (swapped == 1); 
	} while ((gap = gap / 2) >= 1);
}

void Merge(vector<int> &getWords, int low, int high, int mid, int &numOfComp, int &numOfSwaps)
{
	int i, j, k;
	vector<int> C;
	C.resize(getWords.size());
	i = low;	//index for first part
	j = mid + 1;	//index for second part
	k = 0;	//index for array C
	while ((i <= mid) && (j <= high))	//merge vectors getWords in C
	{
		if (getWords[i] < getWords[j])
		{
			C[k] = getWords[i++];
			numOfSwaps++;	//increases number of swaps
		}
		else
		{
			C[k] = getWords[j++];
			numOfSwaps++;	//increases number of swaps
		}
		numOfComp++;	//increases number of comparisons
		k++;
	}
	while (i <= mid)
	{
		C[k++] = getWords[i++];
		numOfSwaps++;	//increases number of swaps
	}
	while (j <= high)
	{
		C[k++] = getWords[j++];
		numOfSwaps++;	//increases number of swaps
	}
	for (i = low, j = 0; i <= high; i++, j++)
	{
		getWords[i] = C[j];	//copy vector C contents back to vector getWords
	}
}
void MergeSort(vector<int> &getWords, int low, int high, int &numOfComp, int &numOfSwaps)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		MergeSort(getWords, low, mid, numOfComp, numOfSwaps);
		MergeSort(getWords, mid + 1, high, numOfComp, numOfSwaps);
		Merge(getWords, low, high, mid, numOfComp, numOfSwaps);
	}
}