/***Mustafa Saðlam
	150140129
	27.04.17
***/
#include <iostream>
//#include <string>

using namespace std;

struct Node{
	int data;
	Node *next, *prev;
};

class ARTraverser{
	public:
		Node* current;
		virtual bool hasNode(){};
		virtual Node* next(){};
};

class AdderRemover{
	protected:
		Node *head, *tail;
		string name;
		int nodeCount;
		ARTraverser* traverser;
	public:
		virtual void add(int){};
		virtual void remove(){};
		virtual void setTraverser(){};
		void display();
		void removeAll();
		void traverse();
};

class FAFR:public AdderRemover{
	public:
		FAFR() {head = tail = NULL; traverser = NULL; name = "FAFR"; nodeCount = 0;};
		void add(int);
		void remove();
		void setTraverser();
};
class LALR:public AdderRemover{
	public:
		LALR() {head = tail = NULL; traverser = NULL; name = "LALR"; nodeCount = 0;};
		void add(int);
		void remove();
		void setTraverser();
};
class FALR:public AdderRemover{
	public:
		FALR() {head = tail = NULL; traverser = NULL; name = "FALR"; nodeCount = 0;};
		void add(int);
		void remove();
		void setTraverser();
};
class LAFR:public AdderRemover{
	public:
		LAFR() {head = tail = NULL; traverser = NULL; name = "LAFR"; nodeCount = 0;};
		void add(int);
		void remove();
		void setTraverser();
};

class ARTF:public ARTraverser{
	public:
		ARTF() {current = NULL;};
		bool hasNode();
		Node* next();
};
class ARTL:public ARTraverser{
	public:
		ARTL() {current = NULL;};
		bool hasNode();
		Node* next();
};

void FAFR::add(int element){//first add fafr
	Node* newNode = new Node;
	newNode->data = element;
	if(head==NULL){
		head = newNode;
		head->next = NULL;
		head->prev = NULL;
		tail = head;
	}
	else{
		newNode->prev = NULL;
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		while(tail)
			tail = tail->next;//this way it is assured that the tail is certianly at the end of the list
	}
	nodeCount++;
}

void FAFR::remove(){//first remove fafr
	Node* toremove;
	if(head){
		toremove = head;
		head->next->prev = NULL;
		head = toremove->next;
		delete toremove;
		nodeCount--;
	}
}

void FAFR::setTraverser(){//set traverse method
	traverser = new ARTF;
	traverser->current = head;
}

void LALR::add(int element){//last add lalr
	Node* newNode = new Node;
	newNode->data = element;
	if(head==NULL){
		head = newNode;
		head->next = NULL;
		head->prev = NULL;
		tail = head;
	}
	else{
		while(tail->next)
			tail = tail->next;//this way it is assured that the tail is certianly at the end of the list
		newNode->next = NULL;
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	nodeCount++;
}

void LALR::remove(){//last remove lalr
	Node* toremove;
	if(head){
		toremove = tail;
		tail->prev->next = NULL;
		tail = tail->prev;
		delete toremove;
		nodeCount--;
	}
}

void LALR::setTraverser(){//set traverse method
	traverser = new ARTL;
	traverser->current = tail;
}

void FALR::add(int element){//first add falr
	Node* newNode = new Node;
	newNode->data = element;
	if(head==NULL){
		head = newNode;
		head->next = NULL;
		head->prev = NULL;
		tail = head;
	}
	else{
		newNode->prev = NULL;
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		while(tail->next)
			tail = tail->next;//this way it is assured that the tail is certianly at the end of the list
	}
	nodeCount++;
}
void FALR::remove(){//last remove falr
	Node* toremove;
	if(head){
		toremove = tail;
		tail->prev->next = NULL;
		tail = tail->prev;
		delete toremove;
		nodeCount--;
	}
}

void FALR::setTraverser(){//set traverse method
	traverser = new ARTF;
	traverser->current = head;
}

void LAFR::add(int element){//last add lafr
	Node* newNode = new Node;
	newNode->data = element;
	if(head==NULL){
		head = newNode;
		head->next = NULL;
		head->prev = NULL;
		tail = head;
	}
	else{
		while(tail->next)
			tail = tail->next;//this way it is assured that the tail is certianly at the end of the list
		newNode->prev = tail;
		newNode->next = NULL;
		tail->next = newNode;
		tail = newNode;
	}
	nodeCount++;
}
void LAFR::remove(){//first remove lafr
	Node* toremove;
	if(head){
		toremove = head;
		head->next->prev = NULL;
		head = toremove->next;
		delete toremove;
		nodeCount--;
	}
}

void LAFR::setTraverser(){//set traverse method
	traverser = new ARTL;
	traverser->current = tail;
}

bool ARTF::hasNode(){
	if(current) return true;
	else return false;
}

Node* ARTF::next(){
	if(hasNode()){
		Node* toreturn = current;
		current = current->next;
		return toreturn;
	}
}

bool ARTL::hasNode(){
	if(current) return true;
	else return false;
}

Node* ARTL::next(){
	if(hasNode()){
		Node* toreturn = current;
		current = current->prev;
		return toreturn;
	}
}

void AdderRemover::display(){
	Node* toDisplay = head;
	cout << name << " | NodeCount:" << nodeCount << endl << "------" << endl;
	
	if(toDisplay==NULL)
		cout << "There is no element to print" << endl << endl;
	
	while(toDisplay){
		cout << toDisplay->data << endl;
		toDisplay = toDisplay->next;
	}
}

void AdderRemover::removeAll(){
	Node* todelete = head;
	while(todelete){
		head = head->next;
		delete todelete;
		todelete = head;
	}
	delete traverser;//since i 'new'ed the traverser as ARTF or ARTL 
	head = tail = NULL;
	nodeCount = 0;
}

void AdderRemover::traverse(){
	cout << name << " | NodeCount:" << nodeCount << endl << "------" << endl;
	
	if(head==NULL)
		cout << "There is no element to print" << endl<< endl;
	
	while(traverser->hasNode()){
		cout << (traverser->next())->data << endl;	
	}
}
