#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <fstream>
using namespace std;

const string FileName = "client.txt";

enum enclient {
	show = 1, add = 2, Delete = 3, update = 4,
	find = 5, transaction = 6, end = 7
};

void enchoise(enclient choosemenue);
int readpositivenumber();
void returnprograme();

struct stclient {
	string account;
	string name;
	string pin;
	string phone;
	double balance;
	bool mark = false;
};

vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord;
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}

stclient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	stclient client;
	vector<string> vclient;
	vclient = SplitString(Line, Seperator);
	client.account = vclient[0];
	client.pin = vclient[1];
	client.name = vclient[2];
	client.phone = vclient[3];
	client.balance = stod(vclient[4]);
	return client;
}

string ConvertRecordToLine(stclient client, string Seperator = "#//#") {
	string DataLine = "";
	DataLine += client.account + Seperator;
	DataLine += client.pin + Seperator;
	DataLine += client.name + Seperator;
	DataLine += client.phone + Seperator;
	DataLine += to_string(client.balance);
	return DataLine;
}

vector <stclient> LoadCleintsDataFromFile(string FileName)
{
	vector <stclient> vclient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		stclient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vclient.push_back(Client);
		}
		MyFile.close();
	}
	return vclient;
}

void SaveCleintsDataToFile(string FileName, vector<stclient> vclient)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (stclient C : vclient)
		{
			if (C.mark == false)
			{

				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	//return vclient;
}

void AddDataLineToFile(string FileName, string  stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{

		MyFile << stDataLine << endl;

		MyFile.close();
	}
}

string readaccount() {
	string account = "";
	cout << " Enter account number : ";
	cin >> account;

	return account;
}

bool findclientfromfile(string account, stclient& client) {

	vector<stclient>vclient = LoadCleintsDataFromFile(FileName);
	for (stclient c : vclient) {
		if (c.account == account) {
			client = c;
			return true;
		}
	}

	return false;
}

void printclientcard(stclient client) {
	cout << "Account Number of this Client : " << client.account << endl;
	cout << "Name of this Client : " << client.name << endl;
	cout << "PIN Code of this Client : " << client.pin << endl;
	cout << "Phone Number of this Client : " << client.phone << endl;
	cout << "Account balance of this Client : " << client.balance << endl;
	cout << endl;

}
//=================print menue===============

void print(stclient client) {
	cout << "|" << setw(16) << left << client.account;
	cout << "|" << setw(22) << left << client.name;
	cout << "|" << setw(10) << left << client.pin;
	cout << "|" << setw(15) << left << client.phone;
	cout << "|" << setw(17) << left << client.balance << "|";
	cout << endl;
	cout << "______________________________________________________________________________________" << endl;
	cout << endl;

}

void printallclient(stclient client, vector <stclient> vclient) {
	system("cls");
	cout << "______________________________________________________";
	cout << "________________________________" << endl;
	cout << "|" << setw(10) << left << " Account Number ";
	cout << "|" << setw(22) << left << " Name Client ";
	cout << "|" << setw(10) << left << " PIN code ";
	cout << "|" << setw(15) << left << " Phone Number";
	cout << "|" << setw(13) << left << " Account Balance " << "|";
	cout << endl;
	cout << "______________________________________________________";
	cout << "________________________________" << endl;
	for (stclient c : vclient) {
		print(c);
	}
}

void showprintallclient() {
	system("cls");
	stclient client;
	vector<stclient> vclient = LoadCleintsDataFromFile(FileName);
	printallclient(client, vclient);
}
//===============Add clients=================

stclient readdata() {
	stclient client;
	cout << " Enter Account Number : ";
	getline(cin >> ws, client.account);
	cout << "===============================" << endl;

	cout << " Enter Name : ";
	getline(cin >> ws, client.name);
	cout << "===============================" << endl;
	cout << " Enter PIN Code : ";
	getline(cin >> ws, client.pin);
	cout << "===============================" << endl;

	cout << " Enter Phone Number : ";
	getline(cin >> ws, client.phone);
	cout << "===============================" << endl;

	cout << " Enter Balance : ";
	cin >> client.balance;
	cout << "===============================" << endl;

	return client;
}

void addnewclient() {
	char ch = 'n';
	system("cls");
	cout << "================================" << endl;
	cout << "           ADD client screen    " << endl;
	cout << "================================" << endl;

	do {

		stclient client;
		client = readdata();
		AddDataLineToFile(FileName, ConvertRecordToLine(client));
		cout << " \n\nThe client has been added successfully " << endl;
		cout << " Do you want add new client enter [Y] / [y] : ";
		cin >> ch;
		cout << endl << endl;
	} while (toupper(ch) == 'Y');
}
//==============delete client================

void showdeleteclient() {
	system("cls");
	stclient client;
	vector<stclient>vclient = LoadCleintsDataFromFile(FileName);
	cout << "==================================" << endl;
	cout << "         Delete client screen     " << endl;
	cout << "==================================" << endl;
	string account = readaccount();
	char ch = 'n';

	if (findclientfromfile(account, client)) {
		printclientcard(client);
		cout << endl;
		cout << " Do you want delete this account ? Enter [Y] / [y] : ";
		cin >> ch;
		cin.ignore();
		if (toupper(ch) == 'Y') {

			for (stclient& c : vclient) {
				if (c.account == account) {
					c.mark = true;
					break;
				}
			}
			SaveCleintsDataToFile(FileName, vclient);
			cout << "\n==================================" << endl;
			cout << " The data was successfully deleted  " << endl;
			cout << "==================================" << endl;
		}
	}
	else {
		cout << "\nClient with Account Number (" << account << ") is Not Found!";
	}
}
//==============update client================

stclient changedata(stclient client) {


	cout << endl;
	cout << " Enter PIN Code : ";
	getline(cin >> ws, client.pin);
	cout << "===============================" << endl;

	cout << " Enter Name : ";
	getline(cin >> ws, client.name);
	cout << "===============================" << endl;

	cout << " Enter Phone Number : ";
	getline(cin >> ws, client.phone);
	cout << "===============================" << endl;

	cout << " Enter Balance : ";
	cin >> client.balance;
	cin.ignore();
	cout << "===============================" << endl;

	return client;
}

void showupdateclient() {
	system("cls");
	stclient client;
	vector<stclient>vclient = LoadCleintsDataFromFile(FileName);
	cout << "==================================" << endl;
	cout << "         UPDATE client screen     " << endl;
	cout << "==================================" << endl;
	string account = readaccount();
	char ch = 'n';

	if (findclientfromfile(account, client)) {
		printclientcard(client);
		cout << endl;
		cout << " Do you want update this account ? Enter [Y] / [y] : ";
		cin >> ch;
		cin.ignore();
		if (toupper(ch) == 'Y') {
			client = changedata(client);
			for (stclient& c : vclient) {
				if (c.account == account) {
					c = client;
					break;
				}
			}
			SaveCleintsDataToFile(FileName, vclient);
			cout << "\n==================================" << endl;
			cout << " The data was successfully updated " << endl;
			cout << "==================================" << endl;
		}
	}
	else {
		cout << "\nClient with Account Number (" << account << ") is Not Found!";
	}

}
//==============find client==================

void showfindclient() {
	system("cls");
	stclient client;
	vector<stclient>vclient = LoadCleintsDataFromFile(FileName);
	cout << "================================" << endl;
	cout << "         Find client screen     " << endl;
	cout << "================================" << endl;
	string account = readaccount();

	if (findclientfromfile(account, client)) {
		printclientcard(client);

	}
	else {
		cout << "\nClient with Account Number (" << account << ") is Not Found!";
	}
}
//==============transaction==================

enum entransaction {
	trans_withdraw = 1, trans_deposit = 2, trans_showmenue = 3
};

void printclienttowithdraw(stclient client) {
	cout << "Account Number of this Client : " << client.account << endl;
	cout << "Name of this Client : " << client.name << endl << endl;

}

bool truepin(stclient client, string pin) {
	if (client.pin == pin) {
		return true;
	}
	else return false;
}



void withdraw() {
	system("cls");
	stclient client;
	vector<stclient> vclient = LoadCleintsDataFromFile(FileName);
	cout << "================================" << endl;
	cout << "       Withdraw client screen   " << endl;
	cout << "================================" << endl;
	string account = readaccount();

	if (findclientfromfile(account, client)) {
		printclienttowithdraw(client);
		cout << " Do you want withdraw money from this account ? enter [y] : ";
		char ch = 'n';
		cin >> ch;

		if (toupper(ch) == 'Y') {
			cout << " Enter your PIN : ";
			string pin;
			cin >> pin;

			if (truepin(client, pin)) {
				double m = 0.0;
				cout << " Enter the amount you want to withdraw : ";
				cin >> m;

				if (m > 0 && m <= client.balance) {
					// هنا التعديل المهم: نعدل الرصيد في الـ vector
					for (stclient& c : vclient) {
						if (c.account == account) {
							c.balance = c.balance - m;
							break;
						}
					}
					// ونحفظ في الملف
					SaveCleintsDataToFile(FileName, vclient);

					cout << "\n==================================" << endl;
					cout << " Withdrawal completed successfully " << endl;
					cout << " New balance: " << client.balance - m << endl;
					cout << "==================================" << endl;
				}
				else if (m > client.balance) {
					cout << " Your account does not have this amount " << endl;
				}
				else {
					cout << " Invalid amount! " << endl;
				}
			}
			else {
				cout << " The PIN code is wrong, please try again." << endl;
			}
		}
	}
	else {
		cout << "\nClient with Account Number (" << account << ") is Not Found!";
	}
}

void showmenuetrans();

void returntrans() {
	system("cls");
	showmenuetrans();
}

void deposit() {
	system("cls");
	stclient client;
	vector<stclient> vclient = LoadCleintsDataFromFile(FileName);
	cout << "================================" << endl;
	cout << "       Deposit client screen    " << endl;
	cout << "================================" << endl;
	string account = readaccount();

	if (findclientfromfile(account, client)) {
		printclienttowithdraw(client);
		cout << " Do you want to deposit money to this account? Enter [Y] / [y] : ";
		char ch = 'n';
		cin >> ch;

		if (toupper(ch) == 'Y') {
			double m = 0.0;
			cout << " Enter the amount you want to deposit : ";
			cin >> m;

			if (m > 0) {
				// نعدل الرصيد في الـ vector
				for (stclient& c : vclient) {
					if (c.account == account) {
						c.balance = c.balance + m;
						break;
					}
				}
				// نحفظ في الملف
				SaveCleintsDataToFile(FileName, vclient);

				cout << "\n==================================" << endl;
				cout << " Deposit completed successfully " << endl;
				cout << " New balance: " << client.balance + m << endl;
				cout << "==================================" << endl;
			}
			else {
				cout << " Invalid amount! Amount must be greater than zero." << endl;
			}
		}
	}
	else {
		cout << "\nClient with Account Number (" << account << ") is Not Found!";
	}
}

void showtransaction(entransaction trans) {
	switch (trans) {
	case entransaction::trans_withdraw: {
		withdraw();
		system("pause>0");
		returntrans();
		break;
	}
	case entransaction::trans_deposit: {
		deposit();
		system("pause>0");
		returntrans();
		break;
	}
	case entransaction::trans_showmenue: {
		returnprograme();
		break;
	}
	}
}

void showmenuetrans() {
	system("cls");
	cout << "================================" << endl;
	cout << "_________transaction list_______" << endl;
	cout << "================================" << endl;
	cout << "   (1) Withdraw " << endl;
	cout << "   (2) Deposit " << endl;
	cout << "   (3) Show Menue " << endl;
	cout << " Enter choise between [1] to [3] : ";

	int choice = readpositivenumber();
	if (choice >= 1 && choice <= 3) {
		showtransaction((entransaction)choice);
	}
	else {
		cout << "Invalid choice!" << endl;
		system("pause>0");
		showmenuetrans();
	}
}
//===============end program=================

void endprogram() {
	system("cls");
	cout << " Finish program." << endl;
	cout << " Thank you" << endl;
}
//===============return on programe==========

void showmenue();

void returnprograme() {
	system("cls");
	showmenue();
}
//===========================================








void enchoise(enclient choosemenue) {

	switch (choosemenue) {
	case enclient::show: {
		showprintallclient();
		system("pause>0");

		returnprograme();
		break;
	}
	case enclient::add: {
		addnewclient();
		system("pause>0");

		returnprograme();
		break;
	}
	case enclient::Delete: {
		showdeleteclient();
		system("pause>0");

		returnprograme();
		break;
	}
	case enclient::update: {
		showupdateclient();
		system("pause>0");

		returnprograme();
		break;
	}
	case enclient::find: {
		showfindclient();
		system("pause>0");

		returnprograme();
		break;
	}
	case enclient::transaction: {
		showmenuetrans();
		system("pause>0");

		returnprograme();
		break;
	}
	case enclient::end: {
		endprogram();
		break;
	}

	}
}

int readpositivenumber() {
	int num;
	do {
		cin >> num;
	} while (num <= 0);
	return num;
}

void showmenue() {
	system("cls");
	cout << "===========================" << endl;
	cout << "_________Menue List________" << endl;
	cout << "===========================" << endl;
	cout << "   (1) Show Clients " << endl;
	cout << "   (2) Add Client " << endl;
	cout << "   (3) Delete Client " << endl;
	cout << "   (4) Update Client " << endl;
	cout << "   (5) Find Client " << endl;
	cout << "   (6) Transaction" << endl;
	cout << "   (7) Exit " << endl;
	cout << " Enter choise between [1] to [7] : ";

	enchoise((enclient)readpositivenumber());
}

int main() {
	showmenue();
	system("pause>0");
	return 0;
}