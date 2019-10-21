#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h> //srand and rand
#include <time.h> //time
#include "combolock.h" //combolock class

using namespace std;

class ComboProgram {
	int lockCodes[3];	
	string usrInput;
	int guess[3];

	int genCode(){
		return rand() % 40;
	}

	void enterCodes(){
		cout << "Guess numbers between 0 and 39:" << endl;
		cout << "Code 1: ";
		getline (cin, usrInput);
		stringstream(usrInput) >> guess[0];
		cout << "Code 2: ";
		getline (cin, usrInput);
		stringstream(usrInput) >> guess[1];
		cout << "Code 3: ";
		getline (cin, usrInput);
		stringstream(usrInput) >> guess[2];
		// cout << guess[0] << " " << guess[1] << " " << guess[2] << endl;
	}

	void mainLoop(){
		ComboLock lock(lockCodes[0], lockCodes[1], lockCodes[2]);
		bool open = false;		
		bool quit;
		bool invalid = false;
		do
		{
			enterCodes(); //get input from user
			quit = true;
			for (int i = 0; i < 3; i++)
			{
				if (guess[i] != 0 || quit == false) //if anything is nonzero, don't quit
				{
					quit = false;
				}

				if (! (guess[i] <= 39 && guess[i] >= 0)) //if anything is invalid warn the user and don't run lock test
				{
					invalid = true;
					cout << guess[i] << " is an invalid entry." << endl;
				}	
			
			}
			if (! (quit || invalid)) //enter codes if not zeros or out of bounds
			{
				lock.reset();
				lock.turnRight(40 - guess[0]); //turn to initial code value
				lock.turnLeft(40 + guess[1] - lock.getDialPosition()); //turn to second code value
				lock.turnRight(40 - guess[2] + lock.getDialPosition()); //turn to third code value
				open = lock.open(); //test if can unlock saving return

			}
			if (open)
			{
				cout << "Congrats, you win infinite money or something!" << endl;
			}
			else
			{
				if (!quit)
				{
					cout << "Try again sucka!" << endl;
				}
			}	

		} while (! (quit || open)); 
		if (quit)
		{
			cout << "What a quitter!" << endl;
		}	
	}


	public: ComboProgram(){
		srand (time(NULL));
		lockCodes[0] = genCode();
		lockCodes[1] = genCode();
		lockCodes[2] = genCode();
		cout << lockCodes[0] << " " << lockCodes[1] << " " << lockCodes[2] << endl;	
		mainLoop();
	}
};




int main(){
	ComboProgram test;	
	return 0;
}
