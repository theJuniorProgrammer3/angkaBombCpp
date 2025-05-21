#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

void clsc() {
	cout << "\033[2J\033[H";
}
void traitor(int player) {
	if(player < 1) {
		if(player == 0) {
			cerr << "Zero player?";
		} else {
			cerr << "Negative player?";
		}
		cerr << " What's your mean?" << endl;
		exit(0);
	} else if(player < 3) {
		cerr << "At least 3 player" << endl;
		exit(0);
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(2, 9999);
	//0 = player biasa, 1 = ketua, 2 = impostor
	vector<int> role(player);
	role[0] = 1;
	role[1] = 2;
	shuffle(role.begin(), role.end(), gen);
	int angkaBomb = dist(gen);
	for(int i = 0; i < player; i++) {
		if(i != 0) {
			cout << "Give it to the next player." << endl;
		}
		cout << "player" << i << "'s role is: ";
		cin.get();
		cout << (role[i] == 0 ? "Common player" : (role[i] == 1 ? "Head" : "Traitor. Bomb number: " + to_string(angkaBomb))) << "." << endl;
		cout << "Enter to continue.";
		cin.get();
		clsc();
	}
	int rAwal = 1;
	int rAkhir = 10000;
	int jawab = 0;
	bool PengkhianatMenang;
	vector<bool> eliminated(player);
	vector<int> jawaban(player);
	int tmp;
	clsc();
	
	while(true) {
		if(rAwal + 1 == angkaBomb && rAkhir - 1 == angkaBomb) {
			PengkhianatMenang = false;
			break;
		}
	for(int i = 0; i < player; i++) {
		if(!eliminated[i]) {
		cout << "Select a narrowing number (" << rAwal << " - " << rAkhir << ") " << (role[i] == 0 || role[i] == 2 ? "player" + to_string(i) : "head (player: " + to_string(i) + ")") << "'s number is: ";
		cin >> jawaban[i];
		}
		if(i == player - 1) {
			cout << "Give it to Head, discuss to choice number from player to final number!" << endl;
			cout << "Final number, player number choice: ";
			cin >> tmp;
			cin.ignore();
			jawab = jawaban[tmp];
		}
	}
		if(jawab <= rAwal || jawab >= rAkhir || eliminated[tmp]) {
			if(eliminated[tmp]) {
				cout << "Player " << tmp << " is leave ";
			}
			cout << "Are you serious?" << endl;
			exit(0);
		}
		if(jawab != angkaBomb) {
			if(jawab < angkaBomb) {
				rAwal = jawab;
			} else {
				rAkhir = jawab;
			}
			cout << "The confinement is narrowing, keep narrowing!" << endl;
		} else {
			PengkhianatMenang = true;
			break;
		}
		if(player >= 5) {
			cout << "Who's SUS? Player number to eliminate (negative number to skip): ";
			int n;
			cin >> n;
			if(n > 0) {
				if(n >= player) {
				if(!eliminated[n]) {
						eliminated[n] = true;
						if(role[n] == 2) {
							PengkhianatMenang = false;
							break;
						}
					} else {
						cout << "Pemain itu sudah dieliminasi." << endl;
					}
				} else {
					cout << "Are you serious?" << endl;
					exit(0);
				}
			}
		}


	}
	cout << (PengkhianatMenang ? "Traitor" : "Fighters") << " win!" << endl;

}
	
	

void normal() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(2, 999);
	int angkaBomb = dist(gen);
	int rAwal = 1;
	int rAkhir = 1000;
	int jawab = 0;
	bool menang;
	cout << "Don't choice bomb number, until bom is locked!" << endl; 	
	while(true) {
		if(rAwal + 1 == angkaBomb && rAkhir - 1 == angkaBomb) {
			menang = true;
			break;
		} 
		cout << "Choice number between " << rAwal << " - " << rAkhir << ": ";p

		cin >> jawab;
		if(jawab <= rAwal || jawab >= rAkhir) {
			cout << "Are you serious?" << endl;
			exit(0);
		}
		if(jawab != angkaBomb) {
			if(jawab < angkaBomb) {
				rAwal = jawab;
			} else {
				rAkhir = jawab;
			}
			cout << "The confinement is narrowing, keep narrowing!" << endl;
		} else {
			menang = false;
			break;
		}
	}
	cout << "You're" << (menang ? "winner :)" : "loser :(") << " !" << endl;
}

int main() {
	cout << "BombNumber game! Now with traitor mode!" << endl;
	cout << "Choice:\n1: Classic Mode\n2: Traitor Mode" << endl;
	int choise;
	cin >> choise;
	if(choise != 1 && choise != 2) {
		cerr << "Are you serious?" << endl;
		return 0;
	}
	if(choise == 1) {
		normal();
	} else if (choise == 2) {
		int playerCount;
		cout << "Player count: ";
		cin >> playerCount;
		traitor(playerCount);
	} else {
		cout << "Choice is not valid." << endl;
	}
	cout << "Fun, right?" << endl;
	return 0;
}
