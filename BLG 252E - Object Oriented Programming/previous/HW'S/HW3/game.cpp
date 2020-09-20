#include "game.h"
#include <iostream>

using namespace std;

bool Game::isFinished(Container<Operator> op, Container<NonOperator> nop) const{
	//Controls all the people is on the right or not
	for(int i=0; i<op.getnumberOfElements(); i++){
		Person temp = op.getArray(i);
		if(temp.getPlace() == "left")
			return false;
	}
	for(int i=0; i<nop.getnumberOfElements(); i++){
		Person temp = nop.getArray(i);
		if(temp.getPlace() == "left")
			return false;
	}
	return true;
}

bool Game::sailAcrossFromLeftToRight(Person &op, Person &p2) {	//This function tries to across 2 people from Left side to Right side
	bool flag = true;
	try{	//Firstly, trying to Person 1 and Person 2 can get on the raft with or can not 
		op.canGetOnTheRaftWith(p2);
	}
	catch(char *s){		//If can not, then holding string exception
		cout<<s<<endl;	//Printing exception
		flag = false;
	}
	if(!flag)	return false;	//If exception is holded, then return false
	
	left.takeFromArray(op.getID());		//Taking 2 people from left container
	left.takeFromArray(p2.getID());
	try{	//2nd control is controlling left container inconsistency
		flag = isConsistency(left);		//Trying to inconsistency for left side container
	}
	catch(char *s){		//If exception is holded
		left.addToArray(op);	//Add back 2 people to left container
		left.addToArray(p2);
		cout<<s<<endl;;
		flag = false;
	}

	if(!flag)	return false;	//If exception is holded, then return false

	right.addToArray(op);		//Adding 2 people to right side container
	right.addToArray(p2);
	try{	//3rd control is controlling right container inconsistency
		flag = isConsistency(right);
	}
	catch(char *s){		//If exception is holded
		left.addToArray(op);		//Then all the changes are taken back
		left.addToArray(p2);
		right.takeFromArray(op.getID());
		right.takeFromArray(p2.getID());
		cout<<s<<endl;
		flag = false;
	}

	if(!flag)	return false;	//If any exception is holded, return false

	op.setPlace("right"),p2.setPlace("right");	//If 2 people can across sail without any inconsistencies, then their places set to right
	return true;
}

/*bool Game::sailAcrossLeftToRight(Operator &op){
	bool flag;
	left.takeFromArray(op.getID());
	try{
		flag = isConsistency(left);
	}
	catch(char *s){
		cout<<s<<endl;
		flag = false;
	}

	if(!flag)	return false;

	right.addToArray(op);
	try{
		flag= isConsistency(right);
	}
	catch(char *s){
		cout<<s<<endl;
		flag = false;
	}

	if(!flag)	return false;
	op.setPlace("right");
	return true;
}*/

bool Game::sailAcrossFromRightToLeft(Person &op, Person &p2){
	//This function is very similar to the sailAcrossFromLeftToRight function, so I will'not need same comments again
	bool flag = true;
	try{
		op.canGetOnTheRaftWith(p2);
	}
	catch(char *s){
		cout<<s<<endl;
		flag = false;
	}
	if(!flag)	return false;

	left.addToArray(op);
	left.addToArray(p2);
	try{
		flag = isConsistency(left);
	}
	catch(char *s){
		left.takeFromArray(op.getID());
		left.takeFromArray(p2.getID());
		cout<<s<<endl;
		flag = false;
	}

	if(!flag)	return false;

	right.takeFromArray(op.getID());
	right.takeFromArray(p2.getID());	
	try{
		flag = isConsistency(right);
	}
	catch(char *s){
		right.addToArray(op);
		right.addToArray(p2);
		left.takeFromArray(op.getID());
		left.takeFromArray(p2.getID());
		cout<<s<<endl;
		flag = false;
	}

	if(!flag)	return false;
	op.setPlace("left"),p2.setPlace("left");
	return true;
}

bool Game::sailAcrossRightToLeft(Person &op){
	//This function includes similar controls...
	bool flag;
	left.addToArray(op);
	Person p = right.takeFromArray(op.getID());
	try{
		flag = isConsistency(left);
	}
	catch(char *s){
		left.takeFromArray(op.getID());
		right.addToArray(p);
		cout<<s<<endl;
		flag = false;
	}

	if(!flag)	return false;

	try{
		flag= isConsistency(right);
	}
	catch(char *s){
		left.takeFromArray(op.getID());
		right.addToArray(p);
		cout<<s<<endl;
		flag = false;
	}

	if(!flag)	return false;
	op.setPlace("left");
	return true;
}

bool Game::isConsistency( Container<Person> &liste) const{
	//This function controls if there is any inconsistency or not
	if( isHere(5,liste) && !isHere(2,liste))	// If Thief is here and Police is not
		throw "Thief-family inconsistency";		//Then throw exception
		
	if( isHere(1,liste)){	//If mother here
		if( isHere(3,liste)){	//If any son is here
			if( !isHere(0,liste) )	//And father is not here
				throw "Mother-Son inconsistency";	//Throw exception
		}
	}
	if( isHere(0,liste)){	//If father is here
		if( isHere(4,liste)){	//If any daughter is here
			if( !isHere(1,liste))	//And mother is not here
				throw "Father-daughter inconsistency";	//Throw exception 
		}
	}
	return true;
}

bool Game::isHere(int id, Container<Person> liste) const{
	for(int i=0; i<liste.getnumberOfElements(); i++){	//This loop is very clear to understand
	  Person temp = liste.getArray(i);
		if(id == temp.getID())
			return true;
	}

	return false;
}

void Game::addToLeft(Person p){
	left.addToArray(p);
}

void Game::addToRight(Person p){
	right.addToArray(p);
}

Person Game::takeFromLeft(){
	return left.takeFromArray(left.getnumberOfElements());
}

Person Game::takeFromRight(){
	return right.takeFromArray(left.getnumberOfElements());
}

bool Game::letsTry(Container<Operator> &op, Container<NonOperator> &nop){
	//Bu fonksiyon rek�rsiyonun bulundu�u fonksiyon olup oyunun ��z�m�n� bulan programd�r.
	bool controls=false;
	Person p1,p2;
	while(!isFinished(op,nop)){		//while all of them are not right
		if(placer){	//Raft is on the left side 
			p1 = left.getArray(counter1);
			p2 = left.getArray(counter2);
			cout<<"The raft is on the left carrying "<< p1.getName() << " and "<< p2.getName() <<endl;
			//Buray� t�rk�e a��klamay� hem kendi a��mdan hem de okuyan�n anlayabilmesi a��s�ndan daha uygun buldum.
			//Burada �nce sailacross'a left'ten alld���m�z bir operator ve nonoperator yolluyoruz, e�er kar��ya ge�ebiliyorlarsa ayn� fonksiyon kendini bir daha �a��r�yor ve bu sefer raft�n sa�dan sola ge�irilmesi �al���lacak
			//E�er kar��ya ge�emiyorlarsa, operator de�i�tirilip ayn� fonksiyon �a��r�lacak,
			//E�er t�m operat�rler i�in yanl�� de�er d�nd�r�l�yorsa, bu sefer ilk operat�rden ba�lay�p 2.nonoperat�r i�in denemeler yap�lacak
			//Sonra 3 ve 4.nonoperat�rler i�in de ayn� i�lem yap�lacak ve ge�erli bir yol bulunacakt�r.
			if(sailAcrossFromLeftToRight(p1,p2)){
				placer = false;
				letsTry(op,nop);
			}
			else if(counter1<2){
				counter1++;
				letsTry(op,nop);
			}
			else if(counter2<5){
				counter1 = 0;
				counter2++;
				letsTry(op,nop);
			}
			else{
				return false;
			}
		}
		if(!placer){	//Raft is on the right side
			if(!controls){	//Burada �nceli�imiz sa�dan sola bir tek ki�iyi ge�irmek olacakt�r.
				p1 = right.getArray(counter1);
				cout<< "The raft is on the right "<< p1.getName() <<endl;
				//Burada yukar�daki rek�rsiyona benzer i�lemler yap�lmakta oldu�u i�in anlatmaya gerek duymad�m.
			if(sailAcrossRightToLeft(p1)){
				placer = true;
				letsTry(op,nop);
			}
			else if(counter1<2){
					counter1++;
					letsTry(op,nop);
			}
			else if(counter2<5){
				counter1 = 0;
				counter2++;
				letsTry(op,nop);
			}
			counter1 = 0, counter2 = 3;
			}
			else{	//E�er tek bir ki�i hi�bir durumda kar��ya ge�emiyorsa(sa�dan sola)
				//2 ki�iyi ge�irmeyi deneyecek olan program ve yine benzer rek�rsiyon i�lemleri...
				controls =true;
				p1 = right.getArray(counter1);
				p2 = right.getArray(counter2);
				cout<< "The raft is on the right "<< p1.getName() << "and "<<  p2.getName() << endl;
					if(sailAcrossFromRightToLeft(p1,p2)){
						placer = true;
						letsTry(op,nop);
					}	
					else if(counter1<2){
						counter1++;
						letsTry(op,nop);
					}
					else if(counter2<5){
						counter1 = 1;
						counter2++;
						letsTry(op,nop);
					}
			}
			return false;
		}
	}
	cout<<"\n\n-----The GAME is finished successfully-----\n\n";
}

Game::Game(){	
	counter1 = 0;	//counter1 = 0 (for selecting first operator)
	counter2 = 3;	//counter2 = 3 (for selecting first nonoperator)
	placer = true;	//placer = true means the raft is on the left for the first case
}

