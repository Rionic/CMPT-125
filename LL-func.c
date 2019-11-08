#include <stdlib.h>
#include <stdio.h>
#include "LL.h"

// Post: nodes of list L are now reversed
void reverse(LL_t * L){
	node_t* prev = NULL;
	node_t* cur = L->head;
	node_t* frnt = NULL;
	node_t* last = L->head;
	while(cur!=NULL){
		frnt=cur->next; 	// increment node
		cur->next=prev; 	// make next node point to previous node
		prev=cur;			// increment prev to cur
		cur=frnt;			// increment cur to cur->next
		if(last->next!=NULL)// update tail
		last=last->next;
	}
	L->head=prev;
	L->tail=last;
	
}

// Post: inserts node with data x
// 		 into location i of list L
void spliceinto(LL_t * L, int x, int i){

	node_t* ind = L->head;
	int j=0;
	for (j=0; ind!=NULL; j++){	//element counters
		ind=ind->next;
	}

	if (L->head==NULL){	//empty list
		L->head=malloc(sizeof(node_t));
		L->head->data=x; L->head->next=NULL;
		L->tail=L->head;
	}

	else if(L->head->next==NULL){  //one node
		if(i==0){
			node_t* newnode=malloc(sizeof(node_t));
			newnode->data=x;
			newnode->next=L->head;
			L->head=newnode;
			L->tail=newnode->next;
			
		}
		if(i>=1){//i>=1 to combat inaccurate user input
			node_t* newnode=malloc(sizeof(node_t));
			newnode->data=x;
			L->head->next=newnode;
			L->tail=newnode;

		}
	}

	else if (i==0){	//index=0
		node_t* newnode = malloc(sizeof(node_t));
		newnode->data=x;
		newnode->next=L->head;
		L->head=newnode;

		if(L->head->next==NULL) //new tail
			L->tail=newnode;
		

	}

	else{	//most likely case
		node_t* newnode=malloc(sizeof(node_t));
		newnode->data=x;
		node_t* prev=L->head;
		node_t* cur=L->head->next;

		int k=0;
		while (cur!=NULL && k<i-1){
			prev=prev->next;
			cur=cur->next;
			k++;
		}
		newnode->next=cur;
		prev->next=newnode;
		if (cur==NULL)  //new tail
			L->tail=newnode;
		
	}

}

// Post: returns the number of even numbers from list L
unsigned int numberOfEvens (LL_t * L){
	node_t* cur=L->head;
	int counter=0;
	while(cur!=NULL){
		if(cur->data%2==0) //checking divisibility by 2
			counter++;
		cur=cur->next;
	}
	return counter;		
}
// Pre: L1 and L2 are ordered linked lists
// Post: L1 contains the merged (ordered) list of L1 and L2, L2 is freed
void merge(LL_t * L1, LL_t * L2){
	if(L2->head==NULL){ // empty L2
		free(L2);
		return;
	}
	else if(L1->head==NULL){ // empty L1
		*L1=*L2;
		free(L2);
		return;
	}

	node_t* node=L1->head;
	int mid=0;
	if(node->next!=NULL){
	for (mid=0; node->next!=NULL; mid++) //finds last index of L1
		node=node->next;
	}

	L1->tail->next=L2->head;
	L1->tail=L2->tail;
	node_t* ind = L1->head;
	free(L2);
	int len=0;
	for (len=0; ind!=NULL; len++) // finds num of items in list
		ind=ind->next;

	int arr[len];
	int newarr[len];
	node_t* cur= L1->head;

	for(int i=0; cur!=NULL; i++){ // creates array with list items
		arr[i]=cur->data;
		cur=cur->next;
	}

	int first=0;
	int last=len;
	int leftpos=0;
	int rightpos=mid+1;
	int newpos=0;

	//  insert elements to arr until a half of the array
	//  reaches mid or last
	while(leftpos<=mid && rightpos<=last-1){
		if(arr[leftpos]<arr[rightpos]){
			newarr[newpos++]=arr[leftpos++];
		}
		else
			newarr[newpos++]=arr[rightpos++];
	}
	// fills in the rest of the array
	while(leftpos<=mid)
		newarr[newpos++]=arr[leftpos++];
	while(rightpos<=last)
		newarr[newpos++]=arr[rightpos++];
	cur=L1->head;
	for(int j=0; j<len; j++){
		cur->data=newarr[j];
		cur=cur->next; 
	}
}

// Post:  removes data target from list L
unsigned int removeNumber(LL_t * L, int target){
	if (L->head==NULL)
		return 0;

	node_t* cur=L->head;
	int len=0;

	for (len=0; cur!=NULL; len++) // element counter
		cur=cur->next;

	cur=L->head;
	int arr[len];

	for (int i=0; i<len; i++){ // transferring elements to array
		arr[i]=cur->data;
		cur=cur->next;
	}
	cur=L->head;
	int newlen=0;
				
	for (int i=0; i<len; i++){ // transferring back to list
		if(arr[i]!=target){
			newlen++;
			if(newlen==1){
				L->head->data=arr[i];
				cur=cur->next;
				continue;
			}
			cur->data=arr[i];
			cur=cur->next;
		}
	}
	if(newlen==0){
		L->head=NULL;
		L->tail=NULL;
		return 1;
	}
	if(newlen==1){
		L->tail=L->head;
		return 1;
	}
	cur=L->head;

	for (int i=0; i<newlen; i++){ //cutting off elements after newlen
		if(i==newlen-1)
			break;
		cur=cur->next;
	}

	L->tail=cur;	//updating tail
	L->tail->next=NULL;
}
