#include <cstdlib>
#include <random>
#include <iostream>
#include <chrono>

#define MAX 9999
using namespace std;
using namespace std::chrono;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, MAX);

void averageCase(int *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = dis(gen);
	}
}

void bestCase(int *arr, int n)
{
	arr[0] = abs(dis(gen));
	for (int i = 1; i < n; i++)
	{
		arr[i] = arr[i - 1] + abs(dis(gen));
	}
}

void worstCase(int *arr, int n)
{
	arr[n - 1] = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		arr[i - 1] = arr[i] + abs(dis(gen));
	}
}

void merge(int *arr, int left, int mid, int right)
{

	int nLeft = mid - left + 1;
	int nRight = right - mid;
	int Left[nLeft], Right[nRight];

	for (int i = 0; i < nLeft; i++)
		Left[i] = arr[left + i];

	for (int i = 0; i < nRight; i++)
		Right[i] = arr[mid + 1 + i];

	int i = 0, j = 0, k = left;
	while ((i < nLeft) && (j < nRight))
	{

		if (Left[i] <= Right[j])
		{
			arr[k] = Left[i];
			i++;
		}
		else
		{
			arr[k] = Right[j];
			j++;
		}
		k++;
	}

	while (i < nLeft)
	{
		arr[k] = Left[i];
		i++;
		k++;
	}

	while (j < nRight)
	{
		arr[k] = Right[j];
		j++;
		k++;
	}
}

void mergeSort(int *num, int left, int right)
{

	if (left < right)
	{
		int mid = left + (right - left) / 2;

		mergeSort(num, left, mid);
		mergeSort(num, mid + 1, right);
		merge(num, left, mid, right);
	}
}

int divide(int *arr, int low, int high)
{

	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{

		if (arr[j] <= pivot)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);

	return i + 1;
}

void quickSort(int *arr, int low, int high)
{

	if (low < high)
	{
		int idx = divide(arr, low, high);

		quickSort(arr, low, idx - 1);
		quickSort(arr, idx + 1, high);
	}
}

void printArray(int *arr, int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

int main()
{

	int sampleSize[6] = {10, 100, 1000, 5000, 10000, 30000};
	int *arrQ, *arrM;
	high_resolution_clock::time_point startQ, endQ, startM, endM;

	for (int i = 0; i < 6; i++)
	{

		int n = sampleSize[i];

		cout << "Sample size : " << n << endl;
		cout << " -------------------------------------------- " << endl;
		cout << " -------------------------------------------- " << endl;
		cout << "Best Case" << endl;
		cout << " -------------------------------------------- " << endl;

		arrQ = new int[n];
		arrM = new int[n];
		bestCase(arrQ, n);
		bestCase(arrM, n);

		cout << "Merge Sort : " << endl;
		startM = high_resolution_clock::now();
		mergeSort(arrM, 0, n - 1);
		endM = high_resolution_clock::now();
		auto timeM = duration_cast<microseconds>(endM - startM).count();
		cout << "Time taken to finish(us) : " << timeM << endl;

		cout << "Quick Sort : " << endl;
		startQ = high_resolution_clock::now();
		quickSort(arrQ, 0, n - 1);
		endQ = high_resolution_clock::now();
		auto timeQ = duration_cast<microseconds>(endQ - startQ).count();
		cout << "Time taken to finish(us) : " << timeQ << endl;

		//		delete arrQ;
		//		delete arrM;

		cout << "Worst Case" << endl;
		cout << " -------------------------------------------- " << endl;

		arrQ = new int[n];
		arrM = new int[n];
		worstCase(arrQ, n);
		worstCase(arrM, n);

		cout << "Merge Sort : " << endl;
		startM = high_resolution_clock::now();
		mergeSort(arrM, 0, n - 1);
		endM = high_resolution_clock::now();
		timeM = duration_cast<microseconds>(endM - startM).count();
		cout << "Time taken to finish(us) : " << timeM << endl;

		cout << "Quick Sort : " << endl;
		startQ = high_resolution_clock::now();
		quickSort(arrQ, 0, n - 1);
		endQ = high_resolution_clock::now();
		timeQ = duration_cast<microseconds>(endQ - startQ).count();
		cout << "Time taken to finish(us) : " << timeQ << endl;

		//		delete arrQ;
		//		delete arrM;

		cout << "Average Case" << endl;
		cout << " -------------------------------------------- " << endl;

		arrQ = new int[n];
		arrM = new int[n];
		averageCase(arrQ, n);
		averageCase(arrM, n);

		cout << "Merge Sort : " << endl;
		startM = high_resolution_clock::now();
		mergeSort(arrM, 0, n - 1);
		endM = high_resolution_clock::now();
		timeM = duration_cast<microseconds>(endM - startM).count();
		cout << "Time taken to finish(us) : " << timeM << endl;

		cout << "Quick Sort : " << endl;
		startQ = high_resolution_clock::now();
		quickSort(arrQ, 0, n - 1);
		endQ = high_resolution_clock::now();
		timeQ = duration_cast<microseconds>(endQ - startQ).count();
		cout << "Time taken to finish(us) : " << timeQ << endl;
	}
}
