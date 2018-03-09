#include <iostream>
#include <stdlib.h>

/**
	Structure of linked-list
*/
struct Node{
    int value;
    Node *next;
};

/**
    Prints all values from list

    @param *list - pointer to first element of list
*/
void printList(Node* list){
	while(list!=NULL){
		std::cout << list->value;
		std::cout << " ";
		list = list->next;
	}
}

/**
    Adds element at the end of list

    @param *list - pointer to first element of list
    @param *value - value, that will be added to last element
*/
void addNode(Node* list, int value){
	while(list!=NULL){
		if(list->next == NULL){
			Node* newNode = new Node;
			newNode->value = value;
			newNode->next = NULL;
			list->next = newNode;
			return;
		}
		list = list->next;
	}
}



/**
    Merges two sorted lists (without guardian).

    @param *list1 - pointer to first element of first list
    @param *list2 - pointer to first element of second list
    
    @return a first pointer of new sorted list
*/
void mergeSortedListsRecursive(Node* lastNode, Node *list1, Node *list2){
	if(list1==NULL){
		lastNode->next=list2;
		return;
	}
	if(list2==NULL){
		lastNode->next=list1;
		return;
	}
	if(list1->value < list2->value){
		lastNode->next=list1;
		list1=list1->next;
		lastNode=lastNode->next;
		mergeSortedListsRecursive(lastNode, list1,list2);
	}
	else {
		lastNode->next=list2;
		list2=list2->next;
		lastNode=lastNode->next;
		mergeSortedListsRecursive(lastNode, list1,list2);
	}
}

/**
    Splits lists using "Tortoise and Hare Algorithm".
	Pointer in function argument will be a pointer of first "splited" list.

    @param *list - pointer to first element of list
    
    @return a pointer of second list
*/
Node* splitList(Node* list){
	Node* slow = list;
	Node* fast = list;
	while(fast->next != NULL && fast->next->next !=NULL){
		slow=slow->next;
		fast=fast->next->next;
	}
	Node* secondListPtr = slow->next;
	slow->next=NULL;
	return secondListPtr;
}

/**
    Sorts list (without guardian) using a recursive merge sort algorithm (and recursive merging algorithm)

    @param *list1 - pointer to first element of list
    
    @return a pointer to sorted list
*/
Node* mergeSort(Node* list1){
	if(list1!=NULL && list1->next!=NULL){ //list size is bigger than 1
		Node* list2 = splitList(list1);
		Node* sortedList1 = mergeSort(list1);
		Node* sortedList2 = mergeSort(list2);
		Node* guard = new Node;
		mergeSortedListsRecursive(guard,sortedList1,sortedList2);
		return guard->next;
	}
	return list1;
}
int main(int argc, char** argv) {
	//EXAMPLE USAGE OF ALGORITHM		
	Node* testList = new Node;
	testList->next=NULL; //must be NULL in order to detect end of list
	testList->value=0;
	for(int i = 0; i < 100; i++){
		addNode(testList,rand());
	}
	printList(testList);
	std::cout << std::endl << "SORTED ARRAY" << std::endl;

	Node* finalList = mergeSort(testList);
	printList(finalList);

	return 0;
}

