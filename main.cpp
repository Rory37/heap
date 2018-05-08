#include <iostream>
#include <cstring>
#include <ctype.h>
#include <cstdio>
#include <fstream>//for file in
#include <stdlib.h> 

using namespace std;

void maxHeap(int*, int); //Calls with length and array
void create(int*, int, int); //Actually forms max heap
int insert(int*, int); // inserts element into heap
int deletenode(int*, int);//delete element from heap
void print(int*, int, int, int); //Prints max heap rotated 90 degrees left

int main() {
  cout << "This is the heap program" << endl;
  char c [80];
  bool b = true;
  while ( b == true) {//runs the input until valid
    cout << "Please input a input method (series or filename)" << endl;
    cin >> c;//takes method
    int heap [100];//creates array for heap
    for(int i = 0; i < 100; i++) {//sets everything in array to val 0 (was issue at home computer)
      heap[i] = 0;
    }
    if (strcmp(c, "series") == 0) {//If the input is series
      b = false;//Proper input
      bool stillIn = true;//While still adding
      int count = 0;//spot to put new number
      cin.ignore(); //ignores previous cin in
      while(stillIn == true) {
	cout << "Please input a number to be in your heap, or END to construct your heap" << endl;
	char input [1000];//can hold number for input
	cin.getline(input,1000);//gets input
	if(strcmp(input, "END") == 0) { //Once end is typed, quits
	  stillIn = false;
	}
	else{
	  heap[count] = atoi(input); //take input, convert to int and add to array
	  count++;//increment spot to put int
	}
      }
    }
    else if (strcmp(c, "filename") == 0) {//if file
      cout << "Please input the list in the given input method" << endl;
      char filename[80];//for name of file
      cin.ignore();//ignores past cin 
      cin.getline(filename, 80);//takes in the name
      ifstream newFile; //new file
      newFile.open(filename);//opens file with the name put in
      if (newFile == NULL) {//if file doesn't exist
      	cout << "There was an error reading the file" << endl;
      }
      else {
	b = false;//input method correct
	int i = 0; //keeps track of spots in heap
	while (newFile.eof() != true) {//while not end of file
	  newFile >> heap[i];//puts each number seperated by whitespace in
	  i++;
	}
      }
      newFile.close();//closes file
    }
    if (b == false) {//provided proper input
      int length;
      for (int i = 0; i < sizeof(heap)/sizeof(heap[0]); i++) {//calculates elements in int array, puts in length
	if (heap[i] == 0) {
	  length = i;
	  break;
	}
      }
      cout << endl;
      maxHeap(heap, length); //runs max heap with array and length
      print(heap, length, 0, 1); //prints the heap, with heap, length, a counter, and an i value
      bool s = true;
      while(s == true) {//repeats till quit is typed
	cout << "Please choose to either insert, delete, print or quit" << endl;
	char input [80];
	cin >> input;
	if (strcmp(input, "insert") == 0) {
	  length = insert(heap, length);//runs insert
	}
	else if (strcmp(input, "quit") == 0) {
	  s = false;//exits loop and program
	}
	else if (strcmp(input, "delete") == 0) {
	  length = deletenode(heap, length);//runs delete
	}
	else if (strcmp(input, "print") == 0) {
	  print(heap, length, 0, 1);//prints the max heap
	}
      }
    }
  }
}



void maxHeap(int* heap, int length) { //initiates the recursive create
  for (int i = (length+1)/2; i >= 0; i--) {//will run create for the latter half of the heap
    create(heap, i+1, length);
  }

}

void create(int* heap, int i, int length) {
  //array is organized so each child will be twice the value of the position of the parent(starting at 1)
  int leftpos = 2*i;//establishes left child pos
  int rightpos = 2*i+1;//establishes right child pos
  int largest = i;//will hold the largest of the two
  if (leftpos <= length && heap[leftpos-1] > heap[i-1]) {// If the left pos is not off the array and the value
    //of left pos is greater
    largest = leftpos;//largest is the left child
  }
  if (rightpos <= length && heap[rightpos-1] > heap[largest-1]) {//If right pos is not off array and its value is
    //greater than parent
    largest = rightpos;//largest is the right child
  }
  if (largest != i){//if a child is greater
    //swaps parent and child
    int temp = heap[largest-1];
    heap[largest-1] = heap[i-1]; 
    heap[i-1] = temp;
create(heap, largest, length);//recursively runs with new parent
  }
   
}

int insert (int* heap, int length) {
  length ++;//Increases length
  cout << "What number do you wish to insert?" << endl;
  cin.ignore();
  int insert;
  cin >> insert;//takes in val to insert
  heap[length - 1] = insert;//puts that into the next open spot in heap
  maxHeap(heap, length);//runs max heap with this new array
  print(heap, length, 0, 1);//prints new heap
  return length;//returns length to remain consistent

}

int deletenode (int* heap, int length) {
  cout << "What number should be deleted" << endl;
  int todel;
  cin.ignore();
  cin >> todel;//Takes number to delete
  int count =0;
  for (int i = 0; i < length; i++ ) {//for entirety of array
    if (heap[i] == todel) {//if val is to be deleted
      count++;//records how many were deleted
      heap[i] = 0;//spot equals 0
      for (int j = i; j < length; j++) {//Shifts all zeros to end
	int temp = heap[j+1];//swaps zero and num next to it
	heap[j+1] = heap[j];
	heap[j] = temp;
      }
    }
  }
  length -= count;//subtract number deleted from length
  maxHeap(heap, length);//runs max heap with new delete
  print(heap, length, 0, 1);//prints new heap
  return length;//returns the length for later runs
}

void print(int* heap, int length, int count, int i) {
  int leftpos = 2*i;//determines each child
  int rightpos = 2*i+1;
  if (rightpos <= length){//if in array length
    print(heap, length, count + 1, rightpos);//run print for right child with 1 more count and one more tab
  }
  int temp = count;
  //once rightmost
  while (count > 0) {
    cout << "    ";//prints out tabs equivalent to layer of heap
    count --;
  }
  cout << heap[i-1] << endl;//prints the actual value in heap
  if (leftpos <= length){//if left in heap length
    print(heap, length, temp + 1, leftpos);//run print for the left child
  }
}
