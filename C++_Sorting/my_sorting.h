#ifndef MY_SORTING_H
#define MY_SORTING_H
#include "TestingFramework.h"
// Insertion Sort
// Selection Sort
// Quick Sort


// Merge Sort
// Heap Sort
// Counting Sort
// Radix Sort

template<class T>
bool is_sorted_b(T input[])	{
	bool sorted = true;

	for ( int z = 0; z < INPUT_SIZE-1; z++ )	{
		if (input[z] > input[z+1])	{
			sorted = false;
			return sorted;
		}
	}
	
	return sorted;
}
template<class T> // No bounds checking, rather dangerous.
void swap(T* input, int a, int b) {
	T temp;
	temp = input[a];
	input[a] = input[b];
	input[b] = temp;
}
// Helper Function
template<class T>	// Useful for testing with INPUT_SIZE = 20
void temp_print(T input[])	{
	for(int i = 0; i<INPUT_SIZE; i++)	{
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}

template<class T>
void temp_print2(T input[], int end)	{
	for(int i = 0; i<end; i++)	{
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}


// Sorting methods

// Will want to rewrite insertion and selection structs as classes that take
// min/max initializer values like Quick Sort, rather than depending on 
// compiler magic for max with INPUT_SIZE global constant.
struct insertion	{
	template<class T>
	void operator()(T* input){
		for ( T j=1; j < INPUT_SIZE; j++ )	{
			T key = input[j];
			T i = j-1;

			while ( i>=0 && input[i] > key )	{
				input[i+1] = input[i];
				i = i-1;
			}

			input[i+1] = key;
		}
	}
};
struct selection	{
	template<class T>
	void operator()(T* input){
		if ( is_sorted_b(input) )
			return;

		T smallest	= input[0];
		int temp		= 0;
		for(T pos = 0; pos < INPUT_SIZE; pos++)	{
			smallest = pos;
			// Finding the smallest number
			for (T i = pos+1; i < INPUT_SIZE; i++)	{
				if (input[i] < input[smallest])	{
					smallest = i;
				}
			}

			// Swapping
			if (smallest != pos)	{
				temp = input[pos];
				input[pos] = input[smallest];
				input[smallest] = temp;
			}
		}
	}
};
class S_Quick	{
private:
	int p;
	int r;

public:
	S_Quick(int left, int right)	{
		p = left;
		r = right;
	}

	int partition(int* input, int p, int r) {
		int x = input[r];
		int i = p - 1;
		for (int j = p; j <= r-1; j++) {
			if (input[j] <= x) {
				i = i+1;
				// swapping A[i] with A[j]
				swap(input, i, j);
			}
		}
		// swapping A[i+1] with A[r]
		swap(input, i+1, r);
		return i+1;
	}

	// Recursive, does not work for large inputs.
	void quick(int* input, int p, int r) {
		int q;
		if (p < r) {
			q = partition(input, p ,r);
			quick(input, p, q-1);
			quick(input, q+1, r);
		}
	}

	void operator()(int* input)	{
		if (is_sorted_b(input))
			return;

		quick(input, p, r);
	}
};

// I have next to no idea of to translate the sudo code into working code.
class S_Merge{
private:
	int left;
	int right;
	// Terribly oversized arrays.
	int L[INPUT_SIZE];
	int R[INPUT_SIZE];
public:
	S_Merge(int p, int r)	{
		left = p;
		right = r;
	}
	
	template<typename T>
	void merge(T* input, int p, int q, int r)	{
		cout << p << " | " << q << " | " << r << endl;
		int n1 = 0;
		int n2 = 0;

		n1 = q - p + 1;
		n2 = r - q;

		// Set up two sub-arrays for comparison
		for (int i = 0; i < n1; i++)	{
			L[i] = input[p+i-1];
		}
		for (int j = 0; j < n2; j++)	{
			R[j] = input[q+j];
		}
		// Sentinels, not really sure what good they are.
		//L[n2] = MERGE_MAX;
		//R[n2] = MERGE_MAX;

		//print_array(input);
		cout << n1 << " | " << n2 << endl;
		int i = 0;
		int j = 0;
		for (int k = p; k <= r; k++)	{
			if (L[i] <= R[j])	{
				input[k] = L[i];
				i++;
			}
			else	{
				input[k] = R[j];
				j++;
			}
		}
	}

	template<typename T>
	void sort(T* input, int p, int r)	{
		if (p < r)	{
			int q = (p + r) / 2;
			sort(input, p, q);
			sort(input, q+1,r);
			merge(input, p, q, r);
		}
		cout << endl;
	}

	template<typename T>
	void operator()(T* input)	{
		if (is_sorted_b(input))
			return;

		sort(input, left, right);
	}
};
class Heap{};

//template<class T>
template<class T>
class S_Counting{
private:
	T sorted[INPUT_SIZE];
	T temp[MAX_INT+1];

public:
	//template<typename T>
	void operator()(T* input)	{
		for (int i = 0; i <= MAX_INT; i++)	{
			temp[i] = 0;
		}
		for (int j = 0; j < INPUT_SIZE; j++)	{
			temp[input[j]] = temp[input[j]]+1;
		}
		for (int i = 1; i <= MAX_INT; i++)	{
			temp[i] = temp[i]+temp[i-1];
		}
		for (int j = INPUT_SIZE-1; j >= 0; j--)	{
			sorted[temp[input[j]]-1] = input[j];
			temp[input[j]] = temp[input[j]]-1;
		}
		for (int i = 0; i < INPUT_SIZE; i++)	{
			input[i] = sorted[i];
		}
	}
};
class Radix{};
#endif