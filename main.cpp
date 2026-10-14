#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
using namespace std;

void showWelcomeScreen() {
	system("cls");
	cout << "==================================================" << endl;
	cout << "          WELCOME TO ROCK PAPER SCISSORS       " << endl;
	cout << "==================================================" << endl;
	cout << "                    Rules:                        " << endl;
	cout << "             Stone   beats   Scissor                   " << endl;
	cout << "             Scissor beats   Paper                   " << endl;
	cout << "             Paper   beats   Stone                    " << endl;
	cout << "==================================================" << endl;


}

enum enchoisecomputer { stone = 1, paper = 2, scissor = 3 };

struct stinfo {
	int coumputer = 0;
	int user = 0;
	int equal = 0;
	int round = 0;
};

int readpositivenumber() {
	int num;
	do {
		cout << "enter the number of round from 1 to 10 : ";
		cin >> num;
	} while (num < 1 || num>10);
	return num;
}

int randomnumber(int from, int to) {
	int random = rand() % (to - from + 1) + from;
	return random;
}

enchoisecomputer choisecomputer() {
	int randNum = randomnumber(1, 3);
	return (enchoisecomputer)randNum;
}

string GetChoiceName(enchoisecomputer choice) {
	switch (choice) {
	case enchoisecomputer::stone:   return "Stone";
	case enchoisecomputer::paper:   return "Paper";
	case enchoisecomputer::scissor: return "Scissor";

	}
}

int choiseuser() {
	int ch;
	do {
		cout << " please stone[1] or paper[2] or scissor[3] ? ";
		cin >> ch;
	} while (ch < 1 || ch > 3);
	return ch;
}

int checkwin(enchoisecomputer choice, int ch) {
	int a;
	if (choice == enchoisecomputer::stone) {
		if (ch == 1) {
			a = 0;
			return a;
		}
		else if (ch == 2) {
			a = 1;
			return a;
		}
		else if (ch == 3) {
			a = -1;
			return a;
		}
	}
	else if (choice == enchoisecomputer::paper) {
		if (ch == 1) {
			a = -1;
			return a;
		}
		else if (ch == 2) {
			a = 0;
			return a;
		}
		else if (ch == 3) {
			a = 1;
			return a;
		}
	}
	else if (choice == enchoisecomputer::scissor) {
		if (ch == 1) {
			a = 1;
			return a;
		}
		else if (ch == 2) {
			a = -1;
			return a;
		}
		else if (ch == 3) {
			a = 0;
			return a;
		}
	}
}

void printwin(int a, stinfo& info, enchoisecomputer choice) {
	if (a == 1) {

		cout << " --------user win-------- " << endl;
		cout << " the choise of computer : " << GetChoiceName(choice) << endl << endl;
		system("color 2f");
		info.user++;
	}
	else if (a == 0) {
		cout << " --------Draw-------- " << endl;
		cout << " the choise of computer : " << GetChoiceName(choice) << endl << endl;
		system("color 6f");
		info.equal++;
	}
	else if (a == -1) {
		system("color 4f");
		cout << " --------computer win-------- " << endl;
		cout << "\a";
		cout << " the choise of computer : " << GetChoiceName(choice) << endl << endl;
		info.coumputer++;
	}
}

void playRounds(int num, stinfo& info) {
	info.round = num;
	for (int i = 1; i <= num; i++) {

		cout << "\n\n______________ Round " << i << "__________________\n";

		enchoisecomputer computerChoice = choisecomputer();

		int userChoice = choiseuser();
		cout << "Computer chose: " << GetChoiceName(computerChoice) << endl;
		cout << "You chose: " << GetChoiceName((enchoisecomputer)userChoice) << endl;

		int result = checkwin(computerChoice, userChoice);

		printwin(result, info, computerChoice);
	}
}

void printinendgame(stinfo info) {
	system("cls");
	if (info.coumputer > info.user) {
		cout << "______________________________G A M E  O V E R _________________" << endl;
		system("color 4f");
		cout << "                              computer is winer ." << endl;
	}
	else if (info.coumputer < info.user) {
		cout << "______________________________perfect you win _________________" << endl;
		system("color 2f");
		cout << "                              YOU Are Winer ." << endl;
	}
	else if (info.coumputer == info.user) {
		cout << "______________________________The match ended in a DRAW _________________" << endl;
		system("color 6f");
	}
	cout << "____________________________________________________________________" << endl;
	cout << "			number of round  |" << info.round << endl << endl;
	cout << "			computer winer   |" << info.coumputer << endl << endl;
	cout << "			user winer       |" << info.user << endl << endl;
	cout << "			match draw       |" << info.equal << endl << endl;
}

bool again() {
	char letter;
	cout << "Do you want to play another round ?" << endl;
	cout << "YES[y]  OR  NO[n]  :" << endl;
	cin >> letter;
	if (letter == 'y' || letter == 'Y') {
		return 1;
	}
	else if (letter == 'n' || letter == 'N') return 0;
}

void start() {
	srand((unsigned)time(NULL));

	do {
		system("cls");
		showWelcomeScreen();
		int num = readpositivenumber();
		stinfo info;
		cout << GetChoiceName(choisecomputer());
		playRounds(num, info);
		printinendgame(info);
	} while (again());
	system("cls");
	cout << "========== End Game  ==========" << endl;

}

int main() {
	start();
	system("pause>0");
	return 0;
}
