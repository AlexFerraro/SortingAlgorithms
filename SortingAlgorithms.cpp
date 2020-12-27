#include <iostream>
#include <string>

using namespace std;

const int _size = 20000;

int* RandomVector()
{
    int* vector = (int*)malloc(_size * sizeof(int));

    srand(time(NULL));
    for (int index = 0; index < _size; index++, vector++)
    {
        *vector = rand();
    }
    vector -= _size;

    return vector;
}

void BubbleSort(int* vectorRandom)
{
    int i, j, helper, * vector;

    vector = vectorRandom;

    for (i = 0; i < (_size - 1); i++)
    {
        for (j = 0; j < (_size - i - 1); j++)
        {
            if (vector[j] > vector[j + 1])
            {
                helper = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = helper;
            }
        }
    }
}

void Insertionsort(int* vectorRandom)
{
    int temp, j, * vector = vectorRandom;

    for (int index = 1; index < _size; index++)
    {
        temp = vector[index];
        j = index - 1;
        while (j >= 0 && temp <= vector[j])
        {
            vector[j + 1] = vector[j];
            j = j - 1;
        }
        vector[j + 1] = temp;
    }
}

void Swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void SelectionSort(int* vectorRandom, int size)
{
    int i, j, imin, * vector = vectorRandom;

    for (i = 0; i < size - 1; i++)
    {
        imin = i;
        for (j = i + 1; j < size; j++)
        {
            if (vector[j] < vector[imin])
                imin = j;
        }
        Swap(vector[i], vector[imin]);
    }
}

void ShellSort(int* vectorRandom, int size)
{
    int temp, j, * vector = vectorRandom;

    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i += 1)
        {
            temp = vector[i];

            for (j = i; j >= gap && vector[j - gap] > temp; j -= gap)
                vector[j] = vector[j - gap];

            vector[j] = temp;
        }
    }
}

void Heapify(int* vectorRandom, int n, int i)
{
    int* vector = vectorRandom;
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && vector[l] > vector[largest])
        largest = l;

    if (r < n && vector[r] > vector[largest])
        largest = r;

    if (largest != i) {
        swap(vector[i], vector[largest]);

        Heapify(vector, n, largest);
    }
}

void HeapSort(int* vectorRandom, int n)
{
    int* vector = vectorRandom;

    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(vector, n, i);

    for (int i = n - 1; i > 0; i--) {

        swap(vector[0], vector[i]);

        Heapify(vector, i, 0);
    }
}

void Merge(int* vectorRandom, int l, int m, int r)
{
    int* vector = vectorRandom;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = vector[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = vector[m + 1 + j];

    int i = 0;

    int j = 0;

    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vector[k] = L[i];
            i++;
        }
        else {
            vector[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vector[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vector[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(int arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    int m = (l + r - 1) / 2;
    MergeSort(arr, l, m);
    MergeSort(arr, m + 1, r);
    Merge(arr, l, m, r);
}

void Swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int Partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void QuickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);

        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

string TimeOfExecution(clock_t Ticks[2])
{
    double time = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;

    return "\n Time spent ms: " + to_string(time);

}

void ShowVector(int* vector, string message)
{

    cout << "\n" + message << endl;
    cout << endl;;
    for (int index = 0; index < _size; index++, vector++)
    {
        cout << *vector << " ";
    }
    cout << endl;;
}

void ShowTime(string* timeToExecute)
{
    for (int index = 0; index < 7; index++, timeToExecute++)
    {
        cout << *timeToExecute << endl;
    }
}

int main()
{
    string timeToExecute[7], messageDefault = "Random Vector:", messageOrder = "Ordered Vector";
    clock_t Ticks[2];

    //Generates the random vector and assigns it to the pointer.
    int vectorHelper[_size], * vector = RandomVector();

    copy(vector, vector + _size, vectorHelper);

    ShowVector(vector, messageDefault);
    Ticks[0] = clock();
    BubbleSort(vector);
    Ticks[1] = clock();
    timeToExecute[0] = TimeOfExecution(Ticks) + " - BubbleSort";
    ShowVector(vector, messageOrder + " BubbleSort:");

    copy(vectorHelper, vectorHelper + _size, vector);
    ShowVector(vector, messageDefault);
    Ticks[0] = clock();
    Insertionsort(vector);
    Ticks[1] = clock();
    timeToExecute[1] = TimeOfExecution(Ticks) + " - Insertionsort";
    ShowVector(vector, messageOrder + " Insertionsort:");

    copy(vectorHelper, vectorHelper + _size, vector);
    ShowVector(vector, messageDefault);
    Ticks[0] = clock();
    SelectionSort(vector, _size);
    Ticks[1] = clock();
    timeToExecute[2] = TimeOfExecution(Ticks) + " - SelectionSort";
    ShowVector(vector, messageOrder + " SelectionSort:");

    copy(vectorHelper, vectorHelper + _size, vector);
    ShowVector(vector, messageDefault);
    Ticks[0] = clock();
    ShellSort(vector, _size);
    Ticks[1] = clock();
    timeToExecute[3] = TimeOfExecution(Ticks) + " - ShellSort";
    ShowVector(vector, messageOrder + " SelectionSort:");

    copy(vectorHelper, vectorHelper + _size, vector);
    ShowVector(vector, messageDefault);
    Ticks[0] = clock();
    HeapSort(vector, _size);
    Ticks[1] = clock();
    timeToExecute[4] = TimeOfExecution(Ticks) + " - HeapSort";
    ShowVector(vector, messageOrder + " HeapSort:");

    copy(vectorHelper, vectorHelper + _size, vector);
    ShowVector(vector, messageDefault);
    Ticks[0] = clock();
    MergeSort(vector, 0, _size - 1);
    Ticks[1] = clock();
    timeToExecute[5] = TimeOfExecution(Ticks) + " - MergeSort";
    ShowVector(vector, messageOrder + " MergeSort:");

    copy(vectorHelper, vectorHelper + _size, vector);
    ShowVector(vector, messageDefault);
    Ticks[0] = clock();
    QuickSort(vector, 0, _size - 1);
    Ticks[1] = clock();
    timeToExecute[6] = TimeOfExecution(Ticks) + " - QuickSort";
    ShowVector(vector, messageOrder + " QuickSort:");

    ShowTime(timeToExecute);

    return (0);
}