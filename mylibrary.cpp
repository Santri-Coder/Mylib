#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

// --- ANSI COLOR CODES ---
const string WHITE = "\033[97m";
const string GREEN = "\033[92m";
const string RED = "\033[91m";
const string RESET = "\033[0m";

// Nama file database untuk menyimpan daftar buku
const string DB_FILE = "list_buku.json";

// Global vector untuk menyimpan daftar buku
vector<string> books;

// Fungsi helper untuk mengganti spasi menjadi underscore
string replace_space(string str) {
    replace(str.begin(), str.end(), ' ', '_');
    return str;
}

// Fungsi helper untuk membersihkan whitespace di awal/akhir string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Memuat daftar buku dari file JSON secara manual (tanpa library eksternal)
void load_data() {
    ifstream infile(DB_FILE);
    if (infile.good()) {
        string line;
        while (getline(infile, line)) {
            size_t start = line.find("\"");
            if (start != string::npos) {
                size_t end = line.find("\"", start + 1);
                if (end != string::npos) {
                    string item = line.substr(start + 1, end - start - 1);
                    // Hindari membaca syntax JSON seperti kurung siku
                    if (item != "[" && item != "]") {
                        books.push_back(item);
                    }
                }
            }
        }
        infile.close();
    } else {
        // Daftar default jika file belum ada
        books = {
            "Mindset Book",
            "Psychology",
            "Dark Psychology",
            "Step To Grow Up",
            "Step To Rich"
        };
    }
}

// Menyimpan daftar buku ke file JSON dengan format indentasi
void save_data() {
    ofstream outfile(DB_FILE);
    if (outfile.is_open()) {
        outfile << "[\n";
        for (size_t i = 0; i < books.size(); ++i) {
            outfile << "    \"" << books[i] << "\"";
            if (i < books.size() - 1) {
                outfile << ",";
            }
            outfile << "\n";
        }
        outfile << "]";
        outfile.close();
    }
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void type_effect(const string& text, double delay = 0.05) {
    for (char char_byte : text) {
        cout << char_byte << flush;
        this_thread::sleep_for(chrono::milliseconds(static_cast<int>(delay * 1000)));
    }
}

void draw_banner(bool show_text = true) {
    string banner_top = WHITE + "  ▐▓█▀▀▀▀▀▀▀▀▀▀▀█▓▌  ▄▄▄▄▄\n"
                        "  ▐▓█           █▓▌  █▄▄▄█\n"
                        "  ▐▓█           █▓▌  █▄▄▄█\n"
                        "  ▐▓█▄▄▄▄▄▄▄▄▄▄▄█▓▌  █:███\n"
                        "       ▄▄███▄▄       █████\n"
                        " ╔═════════════════════════════════════════════════════╗" + RESET;
    string banner_bottom = WHITE + " ╚═════════════════════════════════════════════════════╝" + RESET;

    cout << banner_top << endl;
    if (show_text) {
        cout << WHITE << " ║" << GREEN << "        Database Library of Psychology & Mindset     " << WHITE << "║" << RESET << endl;
    } else {
        cout << WHITE << " ║                                                     ║" << RESET << endl;
    }
    cout << banner_bottom << endl;
}

void intro_animation() {
    clear_screen();
    string banner_top = WHITE + "  ▐▓█▀▀▀▀▀▀▀▀▀▀▀█▓▌  ▄▄▄▄▄\n"
                        "  ▐▓█           █▓▌  █▄▄▄█\n"
                        "  ▐▓█           █▓▌  █▄▄▄█\n"
                        "  ▐▓█▄▄▄▄▄▄▄▄▄▄▄█▓▌  █:███\n"
                        "       ▄▄███▄▄       █████\n"
                        " ╔═════════════════════════════════════════════════════╗" + RESET;
    cout << banner_top << endl;
    cout << WHITE << " ║" << GREEN << flush;
    type_effect("        Database Library of Psychology & Mindset     ", 0.05);
    cout << WHITE << "║\n" << RESET;
    cout << WHITE << " ╚═════════════════════════════════════════════════════╝" + RESET << endl;
    this_thread::sleep_for(chrono::milliseconds(500));

    for (int i = 0; i < 3; ++i) {
        clear_screen(); draw_banner(false); this_thread::sleep_for(chrono::milliseconds(300));
        clear_screen(); draw_banner(true); this_thread::sleep_for(chrono::milliseconds(300));
    }
    clear_screen(); draw_banner(true);
}

void show_menu() {
    cout << "\n" << GREEN << "Welcome sir azzkury" << RESET << endl;
    cout << WHITE << "I pray you can change your life with all my book" << RESET << "\n" << endl;

    for (size_t i = 0; i < books.size(); ++i) {
        cout << WHITE << (i + 1) << "." << RESET << " " << books[i] << endl;
    }

    cout << "\n" << GREEN << "A. Add Book" << RESET << endl;
    cout << RED << "B. Delete Book" << RESET << endl;
    cout << WHITE << "0. Exit" << RESET << endl;
}

void fetch_book(string book_name) {
    string filename = replace_space(book_name) + ".txt";
    clear_screen();
    draw_banner(true);
    cout << "\n" << GREEN << "[ Opening " << book_name << "... ]" << RESET << "\n" << endl;

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << WHITE << "File '" << filename << "' tidak ditemukan." << RESET << endl;
    }
    cout << "\n" << GREEN << "Tekan Enter untuk kembali..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // bersihkan buffer sebelum getchar
    cin.get();
}

void add_book() {
    clear_screen();
    draw_banner(true);
    cout << "\n" << GREEN << "Add Name book: " << RESET;
    
    string name;
    getline(cin, name);
    name = trim(name);

    if (!name.empty()) {
        string source = replace_space(name) + ".txt";
        books.push_back(name);
        save_data(); // Simpan ke database JSON

        // Cek jika file .txt belum ada, lalu buat baru
        ifstream check_file(source);
        if (!check_file.good()) {
            ofstream f(source);
            if (f.is_open()) {
                f << "Konten buku: " << name;
                f.close();
            }
        } else {
            check_file.close();
        }

        cout << "\n" << GREEN << "Buku '" << name << "' berhasil ditambahkan!" << RESET << endl;
    } else {
        cout << "\n" << RED << "Nama tidak boleh kosong." << RESET << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(1000));
}

void delete_book() {
    clear_screen();
    draw_banner(true);
    for (size_t i = 0; i < books.size(); ++i) {
        cout << WHITE << (i + 1) << "." << RESET << " " << books[i] << endl;
    }

    cout << "\n" << GREEN << "Choose Number To Deleted: " << RESET;
    string pilihan;
    getline(cin, pilihan);

    try {
        int idx = stoi(pilihan) - 1;
        if (idx >= 0 && idx < static_cast<int>(books.size())) {
            string target_book = books[idx];
            string filename = replace_space(target_book) + ".txt";

            books.erase(books.begin() + idx);
            save_data(); // Simpan perubahan ke JSON

            if (remove(filename.c_str()) == 0) {
                cout << "\n" << WHITE << "File " << filename << " telah dihapus." << RESET << endl;
            } else {
                cout << "\n" << WHITE << "Data buku dihapus." << RESET << endl;
            }
        } else {
            cout << "\n" << RED << "Nomor tidak valid!" << RESET << endl;
        }
    } catch (invalid_argument&) {
        cout << "\n" << RED << "Masukkan angka yang benar!" << RESET << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(1500));
}

int main() {
    load_data();
    intro_animation();

    while (true) {
        clear_screen();
        draw_banner(true);
        show_menu();

        cout << "\n" << GREEN << "Pilih opsi: " << RESET;
        string pilihan;
        getline(cin, pilihan);
        
        // Mengubah input menjadi uppercase
        for (char &c : pilihan) c = toupper(c);
        pilihan = trim(pilihan);

        if (pilihan == "A") {
            add_book();
        } else if (pilihan == "B") {
            delete_book();
        } else if (pilihan == "0") {
            cout << "\n" << GREEN << "Sampai jumpa lagi, Tuan Muda Azzkury." << RESET << endl;
            break;
        } else if (!pilihan.empty() && all_of(pilihan.begin(), pilihan.end(), ::isdigit)) {
            int idx = stoi(pilihan) - 1;
            if (idx >= 0 && idx < static_cast<int>(books.size())) {
                fetch_book(books[idx]);
            } else {
                cout << "\n" << RED << "Nomor tidak tersedia!" << RESET << endl;
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
        } else {
            cout << "\n" << RED << "Pilihan tidak valid!" << RESET << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }
    return 0;
}
