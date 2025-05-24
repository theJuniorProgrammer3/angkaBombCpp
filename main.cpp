#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include "tinyxml2.cpp"

using namespace std;
using namespace tinyxml2;

vector<string> strings;

void clsc() {
	cout << "\033[2J\033[H";
}
void traitor(int player) {
	cout << strings[12] << endl;
	if(player < 1) {
		if(player == 0) {
			cerr << strings[13];
		} else {
			cerr << strings[14];
		}
		cerr << ' ' << strings[15] << endl;
		exit(0);
	} else if(player < 3) {
		cerr << strings[16] << endl;
		exit(0);
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(2, 9999);
	//0 = player biasa, 1 = ketua, 2 = pengkhianat
	vector<int> role(player);
	role[0] = 1;
	role[1] = 2;
	shuffle(role.begin(), role.end(), gen);
	int angkaBomb = dist(gen);
	cin.ignore();
	clsc();
	for(int i = 0; i < player; i++) {
		if(i != 0) {
			cout << strings[17] << endl;
		}
		cout << strings[18] << i << strings[26];
		cin.get();
		cout << (role[i] == 0 ? strings[19] : (role[i] == 1 ? strings[20] : strings[21] + to_string(angkaBomb))) << "." << endl;
		cout << strings[22];
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
		cout << strings[23] << rAwal << " - " << rAkhir << ") " << (role[i] == 0 || role[i] == 2 ? strings[24] + to_string(i) : strings[25] + to_string(i) + ")") << strings[26];
		cin >> jawaban[i];
		}
	}
			cout << strings[27] << endl;
			while(true) {
			cout << strings[28];
			cin >> tmp;
			cin.ignore();
			jawab = jawaban[tmp];
		if(jawab <= rAwal || jawab >= rAkhir || eliminated[tmp]) {
			if(eliminated[tmp]) {
				cout << strings[24] << ' ' << tmp << strings[34];
			}
			cout << strings[2] << endl;
		} else {
			break;
		}
			}
		if(jawab != angkaBomb) {
			if(jawab < angkaBomb) {
				rAwal = jawab;
			} else {
				rAkhir = jawab;
			}
			cout << strings[7] << endl;
		} else {
			PengkhianatMenang = true;
			break;
		}
		if(player >= 5) {
			while(true) {
			cout << strings[29];
			int n;
			cin >> n;
			cin.ignore();
			if(n > 0) {
				if(n >= player) {
					if(!eliminated[n]) {
						eliminated[n] = true;
						if(role[n] == 2) {
							PengkhianatMenang = false;
						}
						break;
					} else {
						cout << strings[35] << endl;
					}
				} else {
					cout << strings[2] << endl;
					
				}
			}
			}
		}
		if(PengkhianatMenang) {
			break;
		}


	}
	cout << (PengkhianatMenang ? strings[31] : strings[32]) << strings[9] << "! " << strings[11] << angkaBomb << ")" << endl;

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
	cout << strings[4] << endl; 	
	while(true) {
		if(rAwal + 1 == angkaBomb && rAkhir - 1 == angkaBomb) {
			menang = true;
			break;
		}
		while(true) {
		cout << strings[5] << rAwal << strings[6] << rAkhir << ": ";

		cin >> jawab;
		cin.ignore();
		if(jawab <= rAwal || jawab >= rAkhir) {
			cout << strings[2] << endl;
		} else {
			break;
		}
		}
		if(jawab != angkaBomb) {
			if(jawab < angkaBomb) {
				rAwal = jawab;
			} else {
				rAkhir = jawab;
			}
			cout << strings[7] << endl;
		} else {
			menang = false;
			break;
		}
	}
	cout << "Anda " << (menang ? strings[9] + " :)" : strings[10] + " :(") << " ! " << strings[11] << angkaBomb << ")" << endl;
}

void invisibleR() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(2, 999);
	int angkaBomb = dist(gen);
	int rAwal = 1;
	int rAkhir = 1000;
	int jawab = 0;
	bool menang;
	cout << strings[33] << endl;
	while(true) {
		if(rAwal + 1 == angkaBomb && rAkhir - 1 == angkaBomb) {
			menang = true;
			break;
		}
		
		while(true) {
		cout << strings[5] << '1' << strings[6] << "1000." << endl;

		cin >> jawab;
		cin.ignore();
		if(jawab <= 1 || jawab >= 1000) {
			cout << strings[2]<< endl;
		} else {
			break;
		}
		}
		if(jawab != angkaBomb) {
			if(jawab < angkaBomb) {
				rAwal = jawab;
			} else {
				rAkhir = jawab;
			}
			cout << strings[7] << endl;
		} else {
			menang = false;
			break;
		}
	}
	cout << "Anda " << (menang ? strings[9] + " :)" : strings[10] + " :(") << " ! " << strings[11] << angkaBomb << ")" << endl;
}
int main() {
	XMLDocument doc;
	doc.LoadFile("strings.xml");
	for(int i = 1; i <= 36; i++) {
		string tmp = "d" + to_string(i);
		auto teks = doc.FirstChildElement("root")->FirstChildElement(tmp.c_str())->FirstChild()->ToText()->Value();
		string teks2 = string(teks);
		while (teks2.find("\\n") != string::npos) {
    			teks2.replace(teks2.find("\\n"), 2, "\n");
		}
		strings.push_back(teks2);
	}
	cout << strings[0] << endl;
	int choise;
	cin >> choise;
	if(choise > 3 || choise < 1) {
		cerr << strings[2] << endl;
		return 1;
	}
	if(choise == 1) {
		normal();
	} else if(choise == 2) {
		int playerCount;
		cout << strings[1];
		cin >> playerCount;
		traitor(playerCount);
	} else if(choise == 3) {
		invisibleR();
	} else {
		cout << strings[2] << endl;
	}
	cout << strings[3] << endl;
	return 0;
}
