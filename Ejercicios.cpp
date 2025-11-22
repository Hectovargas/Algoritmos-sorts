#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;

void bubbleSort(vector<int> &arr) {
  int n = arr.size();
  int temp;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        temp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

void selectionSort(vector<int> &arr) {
  int n = arr.size();
  int temp;

  for (int i = 0; i < n; i++) {
    int menorindex = i;
    int menor = arr[i];

    for (int j = i + 1; j < n; j++) {
      if (arr[j] < menor) {
        menorindex = j;
        menor = arr[j];
      }
    }

    if (menorindex != i) {
      temp = arr[i];
      arr[i] = menor;
      arr[menorindex] = temp;
    }
  }
}

void insertionSort(vector<int> &arr) {
  int n = arr.size();
  int temp;

  for (int i = 1; i < n; i++) {          
    int temp = arr[i]; 
    int j = i - 1;
  
    while (j >= 0 && arr[j] > temp) {
      arr[j + 1] = arr[j]; 
      j--;
    }

    arr[j + 1] = temp; 
  }
}

void merge(vector<int> &arr, int left, int mid, int right) {
   int list1 = mid - left + 1;
   int list2 = right - mid;

   vector<int> L(list1), R(list2);
   
   for (int i = 0; i < list1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < list2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < list1 && j < list2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < list1) {
        arr[k] = L[i];
        i++; k++;
    }
    while (j < list2) {
        arr[k] = R[j];
        j++; k++;
    }
}

void mergeSortHelper(vector<int> &arr, int left, int right) {
 if(left < right){  
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid+1, right);
    merge(arr,left,mid,right);
 }
}

void mergeSort(vector<int> &arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

int partition(vector<int> &arr, int low, int high) {
  int pivot = arr[high]; 
  int i = (low - 1); 

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] <= pivot) {
      i++; 
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]);
  return (i + 1);
}

void quickSortHelper(vector<int> &arr, int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);

    quickSortHelper(arr, low, pi - 1);
    quickSortHelper(arr, pi + 1, high);
  }
}

void quickSort(vector<int> &arr) { 
  quickSortHelper(arr, 0, arr.size() - 1); 
}

void heapify(vector<int> &arr, int n, int i) {
  int largest = i; 
  int left = 2 * i + 1; 
  int right = 2 * i + 2; 

  if (left < n && arr[left] > arr[largest])
    largest = left;

  if (right < n && arr[right] > arr[largest])
    largest = right;

  if (largest != i) {
    swap(arr[i], arr[largest]);

    heapify(arr, n, largest);
  }
}

void heapSort(vector<int> &arr) {
  int n = arr.size();

  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  for (int i = n - 1; i > 0; i--) {
    swap(arr[0], arr[i]);

    heapify(arr, i, 0);
  }
}

vector<int> generateRandomArray(int size) {
  vector<int> arr(size);
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1, 1000000);
  for (int i = 0; i < size; i++) {
    arr[i] = dis(gen);
  }
  return arr;
}

double measureTime(void (*sortFunc)(vector<int> &), vector<int> arr) {
  auto start = high_resolution_clock::now();
  sortFunc(arr);
  auto end = high_resolution_clock::now();
  duration<double, milli> duration = end - start;
  return duration.count();
}

void runAlgorithm(void (*sortFunc)(vector<int> &),const string &algorithmName) {
  int size;
  cout << "\nelementos a ordenar:";
  cin >> size;

  vector<int> testArray = generateRandomArray(size);
  cout << "\ndatos generados";

  cout << "\nEjecutando " << algorithmName << " con " << size << " elementos..." << endl;

  double time = measureTime(sortFunc, testArray);

  cout << "Tiempo de ejecucion: " << fixed << setprecision(2) << time << "ms" << endl;
}

void runAutomaticTests() {
    cout << "\n========================================" << endl;
    cout << "   PRUEBAS AUTOMATICAS" << endl;
    cout << "========================================" << endl;
    
    vector<int> testSizes = {1000, 100000, 1000000};
    vector<void (*)(vector<int> &)> algorithms = {bubbleSort, selectionSort, insertionSort, mergeSort, quickSort, heapSort};
    vector<string> algorithmNames = {"Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort", "Quick Sort", "Heap Sort"};
    
    for (size_t i = 0; i < algorithms.size(); i++) {

        cout << "\n--- " << algorithmNames[i] << " ---" << endl;
        
        for (int size : testSizes) {
            cout << "\nGenerando " << size << " elementos";
            vector<int> testArray = generateRandomArray(size);
            
            cout << "\nEjecutando " << algorithmNames[i] << " con " << size << " elementos" << endl;
            for(int j = 0; j < 5; j++){
            double time = measureTime(algorithms[i], testArray);
            cout << "Tiempo: " << fixed << setprecision(2) << time << " ms" << endl;
            }
            
        }
    }
    
    cout << "\n========================================" << endl;
    cout << "   PRUEBAS COMPLETADAS" << endl;
    cout << "========================================" << endl;
}

void displayMenu() {
  cout << "\n========================================" << endl;
  cout << "   ALGORITMOS DE ORDENAMIENTO" << endl;
  cout << "========================================" << endl;
  cout << "1. Bubble Sort" << endl;
  cout << "2. Selection Sort" << endl;
  cout << "3. Insertion Sort" << endl;
  cout << "4. Merge Sort" << endl;
  cout << "5. Quick Sort" << endl;
  cout << "6. Heap Sort" << endl;
  cout << "7. Pruebas Automaticas" << endl;
  cout << "8. Salir" << endl;
  cout << "========================================" << endl;
  cout << "Seleccione una opcion: ";
}

int main() {
  int option = 0;  

  while (option != 8) {
    displayMenu();
    cin >> option;

    switch (option) {
    case 1:
      runAlgorithm(bubbleSort, "Bubble Sort");
      break;
    case 2:
      runAlgorithm(selectionSort, "Selection Sort");
      break;
    case 3:
      runAlgorithm(insertionSort, "Insertion Sort");
      break;
    case 4:
      runAlgorithm(mergeSort, "Merge Sort");
      break;
    case 5:
      runAlgorithm(quickSort, "Quick Sort");
      break;
    case 6:
      runAlgorithm(heapSort, "Heap Sort");
      break;
    case 7:
      runAutomaticTests();
      break;
    case 8:
      cout << "\nHasta luego" << endl;
      break;
    default:
      cout << "\nOpcion invalida. Por favor intente de nuevo." << endl;
    }

    if (option != 8) {
      cout << "\nPresione Enter para continuar...";
      cin.ignore();
      cin.get();
    }
  }

  return 0;
}