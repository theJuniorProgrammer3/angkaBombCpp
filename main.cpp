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
		cerr << " Apa maksudmu?" << endl;
		exit(0);
	} else if(player < 3) {
		cerr << "Setidaknya ada 3 pemain. " << endl;
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
			cout << "Berikan ke player selanjutnya" << endl;
		}
		cout << "Role player" << i << " adalah: " << endl;
		cin.get();
		cout << (role[i] == 0 ? "Pemain biasa" : (role[i] == 1 ? "Ketua" : "Pengkhianat. Angka bomb: " + to_string(angkaBomb))) << "." << endl;
		cout << "Enter untuk melanjutkan.";
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
		cout << "Pilih angka persempit (" << rAwal << " - " << rAkhir << ") " << (role[i] == 0 || role[i] == 2 ? "player" + to_string(i) : "ketua (player: " + to_string(i) + ")") << " adalah: ";
		cin >> jawaban[i];
		}
		if(i == player - 1) {
			cout << "Serahkan ke ketua, dan diskusikan angka yang akan digunakan untuk angka akhir!" << endl;
			cout << "Angka akhir, pilihan player: ";
			cin >> tmp;
			cin.ignore();
			jawab = jawaban[tmp];
		}
	}
		if(jawab <= rAwal || jawab >= rAkhir || eliminated[tmp]) {
			if(eliminated[tmp]) {
				cout << "Player " << tmp << " udah keluar, ";
			}
			cout << "Yang benar donk!" << endl;
			exit(0);
		}
		if(jawab != angkaBomb) {
			if(jawab < angkaBomb) {
				rAwal = jawab;
			} else {
				rAkhir = jawab;
			}
			cout << "Kurungan terus menyempit! Terus sempitkan!" << endl;
		} else {
			PengkhianatMenang = true;
			break;
		}
		if(player >= 5) {
			cout << "Siapa yang SUS? Nomor pemain yang akan dieliminasi (angka negatif untuk tidak ada: ";
			int n;
			cin >> n;
			if(n > 0) {
				if(!eliminated[n]) {
					eliminated[n] = true;
					if(role[n] == 2) {
						PengkhianatMenang = false;
						break;
					}
				} else {
					cout << "Pemain itu sudah dieliminasi." << endl;
				}
			}
		}


	}
	cout << (PengkhianatMenang ? "Pengkhianat" : "Pejuang") << " menang!" << endl;

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
	cout << "Jangan mengenai bom, sampai bom sampai terkurung sempit!!" << endl; 	
	while(true) {
		if(rAwal + 1 == angkaBomb && rAkhir - 1 == angkaBomb) {
			menang = true;
			break;
		} 
		cout << "Pilih angka diantara " << rAwal << " sampai " << rAkhir << ": ";

		cin >> jawab;
		if(jawab <= rAwal || jawab >= rAkhir) {
			cout << "Yang benar donk!" << endl;
			exit(0);
		}
		if(jawab != angkaBomb) {
			if(jawab < angkaBomb) {
				rAwal = jawab;
			} else {
				rAkhir = jawab;
			}
			cout << "Kurungan terus menyempit! Terus sempitkan!" << endl;
		} else {
			menang = false;
			break;
		}
	}
	cout << "Anda " << (menang ? "menang :)" : "kalah :(") << " !" << endl;
}

int main() {
	cout << "Permainan angkaBomb! Sekarang dengan mode Traitor!" << endl;
	cout << "Pilih:\n1: Mode Biasa\n2: Mode Traitor" << endl;
	int choise;
	cin >> choise;
	if(choise != 1 && choise != 2) {
		cerr << "Yang benar donk!" << endl;
		return 0;
	}
	if(choise == 1) {
		normal();
	} else if (choise == 2) {
		int playerCount;
		cout << "Jumlah player: ";
		cin >> playerCount;
		traitor(playerCount);
	} else {
		cout << "Pilihan tidak valid." << endl;
	}
	cout << "Seru, kan?!" << endl;
	return 0;
}
