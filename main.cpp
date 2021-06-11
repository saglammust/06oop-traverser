/***Mustafa Saðlam
	150140129
	27.04.17
***/
#include"header.h" 

int main() {
    
  AdderRemover *myList[4];

  myList[0] = new FAFR();
  myList[1] = new LALR();
  myList[2] = new FALR();
  myList[3] = new LAFR();

  for(int j=0; j<4; j++) {
    for(int i=0; i<5; i++) 
      myList[j]->add(i);
  }
 
  for(int j=0; j<4; j++){
    myList[j]->remove();
    myList[j]->display();
    myList[j]->removeAll();
    myList[j]->display();
  } 
  
  cout << endl << "Test case for ARTraverser"<< endl;
  for(int j=0; j<4; j++) {
    for(int i=0; i<5; i++)
      myList[j]->add(i);
    myList[j]->remove();
  }

  for(int j=0; j<4; j++){
    myList[j]->setTraverser();
    myList[j]->traverse();
  }
  
  for(int k=0; k<4; k++){
	myList[k]->removeAll();//to get rid of all allocations
  }
  cout << "***Exited normally***" << endl;
  return 0;
}
