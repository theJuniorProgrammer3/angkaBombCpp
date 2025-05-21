
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

// Fungsi untuk membersihkan layar
void clsc() {
        cout << "\033[2J\033[H"; // Menggunakan escape sequence untuk membersihkan layar
}

// Fungsi untuk mode Traitor
void traitor(int player) {
        // Memeriksa jumlah pemain
        if(player < 1) {
                if(player == 0) {
                        cerr << "Zero player?"; // Menangani kasus pemain nol
                } else {
                        cerr << "Negative player?"; // Menangani kasus pemain negatif
                }
                cerr << " Apa maksudmu?" << endl; // Menampilkan pesan kesalahan
                exit(0); // Keluar dari program
        } else if(player < 3) {
                cerr << "Setidaknya ada 3 pemain. " << endl; // Memastikan ada cukup pemain
                exit(0); // Keluar dari program
        }
        
        random_device rd; // Membuat objek random_device untuk menghasilkan angka acak
        mt19937 gen(rd()); // Menginisialisasi generator angka acak
        uniform_int_distribution<int> dist(2, 9999); // Mendefinisikan distribusi angka acak antara 2 dan 9999
        
        // 0 = player biasa, 1 = ketua, 2 = impostor
        vector<int> role(player); // Membuat vektor untuk menyimpan peran pemain
        role[0] = 1; // Menetapkan peran ketua untuk pemain pertama
        role[1] = 2; // Menetapkan peran impostor untuk pemain kedua
        shuffle(role.begin(), role.end(), gen); // Mengacak peran pemain
        
        int angkaBomb = dist(gen); // Menghasilkan angka bom acak
        for(int i = 0; i < player; i++) {
                if(i != 0) {
                        cout << "Berikan ke player selanjutnya" << endl; // Memberitahu untuk melanjutkan ke pemain berikutnya
                }
                cout << "Role player" << i << " adalah: " << endl; // Menampilkan peran pemain
                cin.get(); // Menunggu input dari pengguna
                cout << (role[i] == 0 ? "Pemain biasa" : (role[i] == 1 ? "Ketua" : "Pengkhianat. Angka bomb: " + to_string(angkaBomb))) << "." << endl; // Menampilkan peran pemain
                cout << "Enter untuk melanjutkan."; // Meminta pengguna untuk menekan enter
                cin.get(); // Menunggu input dari pengguna
                clsc(); // Membersihkan layar
        }
        
        int rAwal = 1; // Batas awal untuk angka
        int rAkhir = 10000; // Batas akhir untuk angka
        int jawab = 0; // Variabel untuk menyimpan jawaban pemain
        bool PengkhianatMenang; // Variabel untuk menentukan apakah pengkhianat menang
        vector<bool> eliminated(player); // Vektor untuk menyimpan status eliminasi pemain
        vector<int> jawaban(player); // Vektor untuk menyimpan jawaban pemain
        int tmp; // Variabel sementara
        clsc(); // Membersihkan layar

        while(true) {
                // Memeriksa apakah angka bom terkurung
                if(rAwal + 1 == angkaBomb && rAkhir - 1 == angkaBomb) {
                        PengkhianatMenang = false; // Menetapkan bahwa pengkhianat tidak menang
                        break; // Keluar dari loop
                }
                
                for(int i = 0; i < player; i++) {
                        if(!eliminated[i]) { // Memeriksa apakah pemain belum dieliminasi
                                cout << "Pilih angka persempit (" << rAwal << " - " << rAkhir << ") " << (role[i] == 0 || role[i] == 2 ? "player" + to_string(i) : "ketua (player: " + to_string(i) + ")") << " adalah: "; // Meminta pemain untuk memilih angka
                                cin >> jawaban[i]; // Menyimpan jawaban pemain
                        }
                        if(i == player - 1) { // Jika ini adalah pemain terakhir
                                cout << "Serahkan ke ketua, dan diskusikan angka yang akan digunakan untuk angka akhir!" << endl; // Meminta pemain untuk berdiskusi
                                cout << "Angka akhir, pilihan player: "; // Meminta input angka akhir
                                cin >> tmp; // Menyimpan pilihan pemain
                                cin.ignore(); // Mengabaikan karakter newline
                                jawab = jawaban[tmp]; // Menyimpan jawaban akhir
                        }
                }
                
                // Memeriksa apakah jawaban valid
                if(jawab <= rAwal || jawab >= rAkhir || eliminated[tmp]) {
                        if(eliminated[tmp]) {
                                cout << "Player " << tmp << " udah keluar, "; // Menampilkan pesan jika pemain sudah keluar
                        }
                        cout << "Yang benar donk!" << endl; // Menampilkan pesan kesalahan
                        exit(0); // Keluar dari program
                }
                
                // Memeriksa apakah jawaban tidak sama dengan angka bom
                if(jawab != angkaBomb) {
                        if(jawab < angkaBomb) {
                                rAwal = jawab; // Memperbarui batas awal
                        } else {
                                rAkhir = jawab; // Memperbarui batas akhir
                        }
                        cout << "Kurungan terus menyempit! Terus sempitkan!" << endl; // Memberitahu pemain untuk terus mempersempit
                } else {
                        PengkhianatMenang = true; // Menetapkan bahwa pengkhianat menang
                        break; // Keluar dari loop
                }
                
                // Memeriksa jika ada pemain yang akan dieliminasi
                if(player >= 5) {
                        cout << "Siapa yang SUS? Nomor pemain yang akan dieliminasi (angka negatif untuk tidak ada: "; // Meminta input pemain yang akan dieliminasi
                        int n; // Variabel untuk menyimpan nomor pemain
                        cin >> n; // Menyimpan input pemain
                        if(n > 0) { // Memeriksa apakah input valid
                                if(!eliminated[n]) { // Memeriksa apakah pemain belum dieliminasi
                                        eliminated[n] = true; // Menandai pemain sebagai dieliminasi
                                        if(role[n] == 2) { // Memeriksa apakah pemain yang dieliminasi adalah pengkhianat
                                                PengkhianatMenang = false; // Menetapkan bahwa pengkhianat tidak menang
                                                break; // Keluar dari loop
                                        }
                                } else {
                                        cout << "Pemain itu sudah dieliminasi." << endl; // Menampilkan pesan jika pemain sudah dieliminasi
                                }
                        }
                }
        }
        
        // Menampilkan hasil akhir
        cout << (PengkhianatMenang ? "Pengkhianat" : "Pejuang") << " menang!" << endl; // Menampilkan siapa yang menang
}

// Fungsi untuk mode normal
void normal() {
        random_device rd; // Membuat objek random_device untuk menghasilkan angka acak
        mt19937 gen(rd()); // Menginisialisasi generator angka acak
        uniform_int_distribution<int> dist(2, 999); // Mendefinisikan distribusi angka acak antara 2 dan 999
        int angkaBomb = dist(gen); // Menghasilkan angka bom acak
        int rAwal = 1; // Batas awal untuk angka
        int rAkhir = 1000; // Batas akhir untuk angka
        int jawab = 0; // Variabel untuk menyimpan jawaban pemain
        bool menang; // Variabel untuk menentukan apakah pemain menang
        cout << "Jangan mengenai bom, sampai bom sampai terkurung sempit!!" << endl; // Menampilkan instruksi permainan
        
        while(true) {
                // Memeriksa apakah angka bom terkurung
                if(rAwal + 1 == angkaBomb && rAkhir - 1 == angkaBomb) {
                        menang = true; // Menetapkan bahwa pemain menang
                        break; // Keluar dari loop
                }
                
                cout << "Pilih angka diantara " << rAwal << " sampai " << rAkhir << ": "; // Meminta pemain untuk memilih angka
                cin >> jawab; // Menyimpan jawaban pemain
                
                // Memeriksa apakah jawaban valid
                if(jawab <= rAwal || jawab >= rAkhir) {
                        cout << "Yang benar donk!" << endl; // Menampilkan pesan kesalahan
                        exit(0); // Keluar dari program
                }
                
                // Memeriksa apakah jawaban tidak sama dengan angka bom
                if(jawab != angkaBomb) {
                        if(jawab < angkaBomb) {
                                rAwal = jawab; // Memperbarui batas awal
                        } else {
                                rAkhir = jawab; // Memperbarui batas akhir
                        }
                        cout << "Kurungan terus menyempit! Terus sempitkan!" << endl; // Memberitahu pemain untuk terus mempersempit
                } else {
                        menang = false; // Menetapkan bahwa pemain kalah
                        break; // Keluar dari loop
                }
        }
        
        // Menampilkan hasil akhir
        cout << "Anda " << (menang ? "menang :)" : "kalah :(") << " !" << endl; // Menampilkan hasil permainan
}

// Fungsi utama
int main() {
        cout << "Permainan angkaBomb! Sekarang dengan mode Traitor!" << endl; // Menampilkan judul permainan
        cout << "Pilih:\n1: Mode Biasa\n2: Mode Traitor" << endl; // Meminta pemain untuk memilih mode permainan
        int choise; // Variabel untuk menyimpan pilihan pemain
        cin >> choise; // Menyimpan input pilihan pemain
        
        // Memeriksa pilihan pemain
        if(choise != 1 && choise != 2) {
                cerr << "Yang benar donk!" << endl; // Menampilkan pesan kesalahan
                return 0; // Keluar dari program
        }
        
        // Menjalankan fungsi sesuai pilihan pemain
        if(choise == 1) {
                normal(); // Menjalankan mode normal
        } else if (choise == 2) {
                int playerCount; // Variabel untuk menyimpan jumlah pemain
                cout << "Jumlah player: "; // Meminta input jumlah pemain
                cin >> playerCount; // Menyimpan input jumlah pemain
                traitor(playerCount); // Menjalankan mode Traitor
        } else {
                cout << "Pilihan tidak valid." << endl; // Menampilkan pesan jika pilihan tidak valid
        }
        
        cout << "Seru, kan?!" << endl; // Menampilkan pesan penutup
        return 0; // Mengakhiri program
}

