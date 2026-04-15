#include <iostream>
#include <string>
#include <limits>
using namespace std;

// ============================================================
// STRUCT DATA
// ============================================================

struct DataBarang {
    string nama;
    float berat;
    string kategori;
    string inspektur;
};

string tentukanKategori(float berat) {
    return (berat <= 5.0) ? "Ringan" : "Berat";
}

// ============================================================
// CIRCULAR LINKED LIST (INSPEKTUR)
// ============================================================

struct NodeInspektur {
    string nama;
    int totalDisimpan;
    NodeInspektur* next;
};

class CircularLinkedList {
private:
    NodeInspektur* tail;
    NodeInspektur* current;

public:
    CircularLinkedList() {
        tail = current = nullptr;
    }

    void tambahInspektur(string nama) {
        NodeInspektur* newNode = new NodeInspektur{nama, 0, nullptr};

        if (!tail) {
            newNode->next = newNode;
            tail = current = newNode;
        } else {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void rotasi() {
        if (current) current = current->next;
    }

    string getInspekturAktif() {
        return current ? current->nama : "Tidak Ada";
    }

    void tambahCounterAktif() {
        if (current) current->totalDisimpan++;
    }

    void tampilInspektur() {
        if (!tail) {
            cout << "[!] Tidak ada inspektur.\n";
            return;
        }

        NodeInspektur* head = tail->next;
        NodeInspektur* cur = head;

        cout << "\n=== DAFTAR INSPEKTUR ===\n";

        do {
            cout << "[" << cur->nama << "]";
            if (cur == current) cout << " (AKTIF)";
            cout << " -> ";
            cur = cur->next;
        } while (cur != head);

        cout << "[" << head->nama << "]\n";
    }

    void tampilStatistik() {
        if (!tail) {
            cout << "[!] Tidak ada inspektur.\n";
            return;
        }

        NodeInspektur* head = tail->next;
        NodeInspektur* cur = head;
        NodeInspektur* terbaik = head;

        cout << "\n=== STATISTIK INSPEKTUR ===\n";

        do {
            cout << cur->nama << " : " << cur->totalDisimpan;
            if (cur == current) cout << " [AKTIF]";
            cout << endl;

            if (cur->totalDisimpan > terbaik->totalDisimpan)
                terbaik = cur;

            cur = cur->next;
        } while (cur != head);

        cout << "\n>> Inspektur Terproduktif: " << terbaik->nama
             << " (" << terbaik->totalDisimpan << " barang)\n";
    }
};

// ============================================================
// SINGLE LINKED LIST (RIWAYAT)
// ============================================================

struct NodeRiwayat {
    DataBarang data;
    NodeRiwayat* next;
};

class SingleLinkedList {
private:
    NodeRiwayat* head;

public:
    SingleLinkedList() { head = nullptr; }

    void tambahRiwayat(DataBarang d) {
        NodeRiwayat* newNode = new NodeRiwayat{d, nullptr};

        if (!head) head = newNode;
        else {
            NodeRiwayat* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    void tampilRiwayat() {
        if (!head) {
            cout << "[Riwayat kosong]\n";
            return;
        }

        NodeRiwayat* temp = head;
        int no = 1;

        cout << "\n=== SEMUA RIWAYAT ===\n";

        while (temp) {
            cout << no++ << ". Nama       : " << temp->data.nama << "\n";
            cout << "   Berat      : " << temp->data.berat << " kg\n";
            cout << "   Kategori   : " << temp->data.kategori << "\n";
            cout << "   Inspektur  : " << temp->data.inspektur << "\n";
            cout << "----------------------------------\n";
            temp = temp->next;
        }
    }

    void filterByInspektur(string nama) {
        NodeRiwayat* temp = head;
        bool ditemukan = false;

        cout << "\n=== FILTER INSPEKTUR: " << nama << " ===\n";

        while (temp) {
            if (temp->data.inspektur == nama) {
                cout << temp->data.nama << " | "
                     << temp->data.berat << " kg | "
                     << temp->data.kategori << endl;
                ditemukan = true;
            }
            temp = temp->next;
        }

        if (!ditemukan) cout << "[Tidak ditemukan]\n";
    }

    void filterByKategori(string kategori) {
        NodeRiwayat* temp = head;
        bool ditemukan = false;

        cout << "\n=== FILTER KATEGORI: " << kategori << " ===\n";

        while (temp) {
            if (temp->data.kategori == kategori) {
                cout << temp->data.nama << " | "
                     << temp->data.berat << " kg | "
                     << temp->data.inspektur << endl;
                ditemukan = true;
            }
            temp = temp->next;
        }

        if (!ditemukan) cout << "[Tidak ditemukan]\n";
    }

    void menuRiwayat() {
        int sub;
        do {
            cout << "\n=== MENU RIWAYAT ===\n";
            cout << "1. Tampil Semua\n";
            cout << "2. Filter Inspektur\n";
            cout << "3. Filter Kategori\n";
            cout << "0. Kembali\n";
            cout << "Pilih: ";
            cin >> sub;

            if (sub == 1) tampilRiwayat();

            else if (sub == 2) {
                string nama;
                cin.ignore();
                cout << "Nama inspektur: ";
                getline(cin, nama);
                filterByInspektur(nama);
            }

            else if (sub == 3) {
                string kategori;
                cout << "Kategori (Ringan/Berat): ";
                cin >> kategori;
                filterByKategori(kategori);
            }

        } while (sub != 0);
    }
};

// ============================================================
// DOUBLE LINKED LIST (GUDANG)
// ============================================================

struct NodeBarang {
    DataBarang data;
    NodeBarang* prev;
    NodeBarang* next;
};

class DoubleLinkedList {
private:
    NodeBarang* head;
    NodeBarang* tail;

public:
    DoubleLinkedList() {
        head = tail = nullptr;
    }

    void insertDepan(DataBarang d) {
        NodeBarang* newNode = new NodeBarang{d, nullptr, head};

        if (head) head->prev = newNode;
        else tail = newNode;

        head = newNode;
    }

    void insertBelakang(DataBarang d) {
        NodeBarang* newNode = new NodeBarang{d, tail, nullptr};

        if (tail) tail->next = newNode;
        else head = newNode;

        tail = newNode;
    }

    void tampilGudang() {
        if (!head) {
            cout << "[!] Gudang kosong.\n";
            return;
        }

        NodeBarang* cur = head;
        int no = 1;

        while (cur) {
            cout << no++ << ". Nama Barang : " << cur->data.nama << endl;
            cout << "   Berat       : " << cur->data.berat << " kg\n";
            cout << "   Kategori    : " << cur->data.kategori << endl;
            cout << "   Inspektur   : " << cur->data.inspektur << endl;
            cout << "----------------------------------\n";
            cur = cur->next;
        }
    }

    void hapusBarang(string kategori) {
        if (!head) {
            cout << "[Kosong]\n";
            return;
        }

        if (kategori == "Ringan") {
            if (head->data.kategori != "Ringan") {
                cout << "[!] Tidak ada barang ringan di depan\n";
                return;
            }

            NodeBarang* temp = head;
            head = head->next;

            if (head) head->prev = nullptr;
            else tail = nullptr;

            delete temp;
        }

        else if (kategori == "Berat") {
            if (tail->data.kategori != "Berat") {
                cout << "[!] Tidak ada barang berat di belakang\n";
                return;
            }

            NodeBarang* temp = tail;
            tail = tail->prev;

            if (tail) tail->next = nullptr;
            else head = nullptr;

            delete temp;
        }

        else {
            cout << "[!] Kategori tidak valid\n";
            return;
        }

        cout << "[OK] Barang berhasil dihapus\n";
    }
};

// ============================================================
// BRIDGE FUNCTION
// ============================================================

bool prosesBarang(DataBarang &d,
                  CircularLinkedList &inspektur,
                  DoubleLinkedList &gudang,
                  SingleLinkedList &riwayat) {

    if (d.berat <= 0) {
        cout << "[!] Berat tidak valid\n";
        return false;
    }

    d.kategori = tentukanKategori(d.berat);
    d.inspektur = inspektur.getInspekturAktif();

    if (d.kategori == "Ringan")
        gudang.insertDepan(d);
    else
        gudang.insertBelakang(d);

    riwayat.tambahRiwayat(d);
    inspektur.tambahCounterAktif();

    cout << "[OK] Barang masuk\n";
    return true;
}

// ============================================================
// MAIN
// ============================================================

int main() {
    DoubleLinkedList gudang;
    CircularLinkedList inspektur;
    SingleLinkedList riwayat;

    // Inisialisasi inspektur awal
    string namaAwal[] = {"Mikhael","Fathir","Haidar","Faiz"};
    for (string n : namaAwal) inspektur.tambahInspektur(n);

    int pilihan;
    int counter = 0;
    int intervalRotasi = 3;

    do {
        cout << "\n=====================================\n";
        cout << "        SISTEM MANAJEMEN GUDANG      \n";
        cout << "=====================================\n";
        cout << "1. Tambah Barang ke Gudang\n";
        cout << "2. Lihat Isi Gudang\n";
        cout << "3. Hapus Barang (Ringan / Berat)\n";
        cout << "4. Lihat Riwayat Barang\n";
        cout << "5. Statistik Inspektur\n";
        cout << "6. Lihat Daftar Inspektur\n";
        cout << "0. Keluar\n";
        cout << "-------------------------------------\n";
        cout << "Masukkan pilihan: ";

        cin >> pilihan;

        // Validasi input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[!] Input harus angka!\n";
            continue;
        }

        switch (pilihan) {

        case 1: {
            DataBarang d;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\n=== INPUT DATA BARANG ===\n";
            cout << "Nama Barang : ";
            getline(cin, d.nama);

            cout << "Berat (kg)  : ";
            cin >> d.berat;

            if (prosesBarang(d, inspektur, gudang, riwayat)) {
                counter++;

                if (counter % intervalRotasi == 0) {
                    inspektur.rotasi();
                    cout << "\n>> Rotasi inspektur!\n";
                    cout << "Inspektur sekarang: "
                         << inspektur.getInspekturAktif() << endl;
                }
            }
            break;
        }

        case 2:
            cout << "\n=== DATA GUDANG ===\n";
            gudang.tampilGudang();
            break;

        case 3: {
            string kategori;

            cout << "\n=== HAPUS BARANG ===\n";
            cout << "Masukkan kategori (Ringan / Berat): ";
            cin >> kategori;

            gudang.hapusBarang(kategori);
            break;
        }

        case 4:
            riwayat.menuRiwayat();
            break;

        case 5:
            inspektur.tampilStatistik();
            break;

        case 6:
            inspektur.tampilInspektur();
            break;

        case 0:
            cout << "\nShutdown\n";
            break;

        default:
            cout << "\n[!] Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    return 0;
}