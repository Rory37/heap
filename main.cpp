#include <iostream>
#include <cstring>
#include <ctype.h>
#include <cstdio>
#include <fstream>
#include <stdlib.h> 

using namespace std;

void maxHeap(int*, int);
void create(int*, int, int);
int insert(int*, int);
int deletenode(int*, int);
void print(int*, int, int, int);

int main() {
  cout << "This is the heap program" << endl;
  char c [80];
  bool b = true;
  while ( b == true) {
    cout << "Please input a input method (series or filename)" << endl;
    cin >> c;
    int heap [100];
    for(int i = 0; i < 100; i++) {
      heap[i] = 0;
    }
    if (strcmp(c, "series") == 0) {
      b = false;
      bool stillIn = true;
      int count = 0;
      cin.ignore();
      while(stillIn == true) {
	cout << "Please input a number to be in your heap, or END to construct your heap" << endl;
	char input [1000];
	cin.getline(input,1000);
	if(strcmp(input, "END") == 0) {
	  stillIn = false;
	}
	else{
	  heap[count] = atoi(input);
	  count++;
	}
      }
    }
    else if (strcmp(c, "filename") == 0) {
      cout << "Please input the list in the given input method" << endl;
      char filename[80];
      cin.ignore();
      cin.getline(filename, 80);
      ifstream newFile;
      newFile.open(filename);
      //if (newFile == NULL) {
      //	cout << "There was an error reading the file" << endl;
      //}
      //else {
	b = false;
	int i = 0;
	while (newFile.eof() != true) {
	  newFile >> heap[i];
	  i++;
	}
	//}
      newFile.close();
      }
    int length;
    for (int i = 0; i < sizeof(heap)/sizeof(heap[0]); i++) {
      if (heap[i] == 0) {
	length = i;
	break;
      }
    }
    cout << endl;
    maxHeap(heap, length);
    print(heap, length, 0, 1);
    bool s = true;
    while(s == true) {
      cout << "Please choose to either insert, delete, print or quit" << endl;
      char input [80];
      cin >> input;
      if (strcmp(input, "insert") == 0) {
	length = insert(heap, length);
      }
      else if (strcmp(input, "quit") == 0) {
	s = false;
      }
      else if (strcmp(input, "delete") == 0) {
	length = deletenode(heap, length);
      }
      else if (strcmp(input, "print") == 0) {
	print(heap, length, 0, 1);
      }
    }
  }
}



void maxHeap(int* heap, int length) {
  char* newHeap = new char[100];
  for (int i = (length+1)/2; i >= 0; i--) {
    create(heap, i+1, length);
  }

}

void create(int* heap, int i, int length) {
  int leftpos = 2*i;
  int rightpos = 2*i+1;
  int largest = i;
  if (leftpos <= length && heap[leftpos-1] > heap[i-1]) {
    largest = leftpos;
  }
  if (rightpos <= length && heap[rightpos-1] > heap[largest-1]) {
    largest = rightpos;
  }
  if (largest != i){
    int temp = heap[largest-1];
    heap[largest-1] = heap[i-1]; 
    heap[i-1] = temp;
    create(heap, largest, length);
  }
   
}

int insert (int* heap, int length) {
  length ++;
  cout << "What number do you wish to insert?" << endl;
  cin.ignore();
  int insert;
  cin >> insert;
  heap[length - 1] = insert;
  maxHeap(heap, length);
  print(heap, length, 0, 1);
  return length;

}

int deletenode (int* heap, int length) {
  cout << "What number should be deleted" << endl;
  int todel;
  cin.ignore();
  cin >> todel;
  int count =0;
  for (int i = 0; i < length; i++ ) {
    if (heap[i] == todel) {
      count++;
      heap[i] = 0;
      for (int j = i; j < length; j++) {
	int temp = heap[j+1];
	heap[j+1] = heap[j];
	heap[j] = temp;
      }
    }
  }
  length -= count;
  maxHeap(heap, length);
  print(heap, length, 0, 1);
  return length;
}

void print(int* heap, int length, int count, int i) {
  int leftpos = 2*i;
  int rightpos = 2*i+1;
  if (rightpos <= length){
    print(heap, length, count + 1, rightpos);
  }
  int temp = count;
  while (count > 0) {
    cout << "    ";
    count --;
  }
  cout << heap[i-1] << endl;
  if (leftpos <= length){
    print(heap, length, temp + 1, leftpos);
  }
}
