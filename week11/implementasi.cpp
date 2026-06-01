/*
 ============================================================
  SIMULASI SISTEM FOLDER - STRUKTUR DATA TREE (GENERAL TREE)
  Materi: Tree, Parent-Child, Dynamic Memory, Recursive Traversal
 ============================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ============================================================
// STRUKTUR NODE
// Setiap node merepresentasikan satu folder
// ============================================================
class FolderNode {
public:
    string name;
    FolderNode* parent;
    vector<FolderNode*> children;

    FolderNode(string folderName, FolderNode* parentNode = nullptr) {
        name = folderName;
        parent = parentNode;
    }
};

// ============================================================
// KELAS UTAMA: FILE SYSTEM TREE
// ============================================================
class FileSystemTree {
private:
    FolderNode* root;

    // --- Helper: Cari folder berdasarkan nama (rekursif) ---
    FolderNode* searchRecursive(FolderNode* node, const string& target) {
        if (node == nullptr) return nullptr;
        if (node->name == target) return node;

        for (FolderNode* child : node->children) {
            FolderNode* found = searchRecursive(child, target);
            if (found != nullptr) return found;
        }
        return nullptr;
    }

    // --- Helper: Hitung jumlah folder (rekursif) ---
    int countRecursive(FolderNode* node) {
        if (node == nullptr) return 0;
        int count = 1; // hitung diri sendiri
        for (FolderNode* child : node->children) {
            count += countRecursive(child);
        }
        return count;
    }

    // --- Helper: Tampilkan struktur direktori (Preorder) ---
    void displayTree(FolderNode* node, int level, bool isLast, string prefix) {
        if (node == nullptr) return;

        cout << prefix;
        if (level == 0) {
            cout << "[" << node->name << "]" << endl;
            prefix = "";
        } else {
            if (isLast) {
                cout << "└── 📁 " << node->name << endl;
                prefix += "    ";
            } else {
                cout << "├── 📁 " << node->name << endl;
                prefix += "│   ";
            }
        }

        for (int i = 0; i < (int)node->children.size(); i++) {
            bool last = (i == (int)node->children.size() - 1);
            displayTree(node->children[i], level + 1, last, prefix);
        }
    }

    // --- Helper: Preorder traversal (Root -> Children) ---
    void preorderRecursive(FolderNode* node) {
        if (node == nullptr) return;
        cout << "[" << node->name << "] ";
        for (FolderNode* child : node->children) {
            preorderRecursive(child);
        }
    }

    // --- Helper: Postorder traversal (Children -> Root) ---
    void postorderRecursive(FolderNode* node) {
        if (node == nullptr) return;
        for (FolderNode* child : node->children) {
            postorderRecursive(child);
        }
        cout << "[" << node->name << "] ";
    }

    // --- Helper: Hapus semua child secara rekursif (free memory) ---
    void deleteSubtree(FolderNode* node) {
        if (node == nullptr) return;
        for (FolderNode* child : node->children) {
            deleteSubtree(child);
        }
        delete node;
    }

    // --- Helper: Bangun path lengkap dari root ke node ---
    string buildPath(FolderNode* node) {
        if (node == nullptr) return "";
        if (node->parent == nullptr) return node->name;
        return buildPath(node->parent) + "/" + node->name;
    }

public:
    // --- Constructor: buat root folder ---
    FileSystemTree(string rootName) {
        root = new FolderNode(rootName, nullptr);
        cout << "✅ File system dibuat dengan root: [" << rootName << "]\n";
    }

    // --- Destructor: bersihkan semua memori ---
    ~FileSystemTree() {
        deleteSubtree(root);
    }

    // ============================================================
    // FITUR 1: BUAT FOLDER BARU
    // parentName = nama folder induk
    // newFolder  = nama folder baru yang ingin dibuat
    // ============================================================
    bool createFolder(const string& parentName, const string& newFolder) {
        FolderNode* parent = searchRecursive(root, parentName);
        if (parent == nullptr) {
            cout << "❌ Folder [" << parentName << "] tidak ditemukan!\n";
            return false;
        }

        // Cek duplikat nama di parent yang sama
        for (FolderNode* child : parent->children) {
            if (child->name == newFolder) {
                cout << "⚠️  Folder [" << newFolder << "] sudah ada di dalam [" << parentName << "]!\n";
                return false;
            }
        }

        FolderNode* newNode = new FolderNode(newFolder, parent);
        parent->children.push_back(newNode);
        cout << "✅ Folder [" << newFolder << "] berhasil dibuat di dalam [" << parentName << "]\n";
        return true;
    }

    // ============================================================
    // FITUR 2: HAPUS FOLDER
    // (beserta seluruh subfolder di dalamnya)
    // ============================================================
    bool deleteFolder(const string& folderName) {
        if (root->name == folderName) {
            cout << "❌ Tidak bisa menghapus root folder!\n";
            return false;
        }

        FolderNode* target = searchRecursive(root, folderName);
        if (target == nullptr) {
            cout << "❌ Folder [" << folderName << "] tidak ditemukan!\n";
            return false;
        }

        FolderNode* parent = target->parent;

        // Hapus dari daftar children milik parent
        auto& siblings = parent->children;
        siblings.erase(remove(siblings.begin(), siblings.end(), target), siblings.end());

        // Hitung dulu berapa node yang akan dihapus
        int deletedCount = countRecursive(target);

        // Hapus node beserta seluruh subtree-nya
        deleteSubtree(target);

        cout << "✅ Folder [" << folderName << "] dan " << (deletedCount - 1)
             << " subfolder di dalamnya berhasil dihapus!\n";
        return true;
    }

    // ============================================================
    // FITUR 3: TAMPILKAN STRUKTUR DIREKTORI
    // ============================================================
    void displayDirectory() {
        cout << "\n📂 STRUKTUR DIREKTORI:\n";
        cout << "========================\n";
        displayTree(root, 0, true, "");
        cout << "========================\n";
    }

    // ============================================================
    // FITUR 4: CARI FOLDER TERTENTU
    // ============================================================
    void searchFolder(const string& folderName) {
        FolderNode* result = searchRecursive(root, folderName);
        if (result == nullptr) {
            cout << "🔍 Folder [" << folderName << "] TIDAK ditemukan.\n";
        } else {
            cout << "🔍 Folder [" << folderName << "] DITEMUKAN!\n";
            cout << "   📍 Path: " << buildPath(result) << "\n";
            if (result->parent != nullptr) {
                cout << "   👆 Parent: [" << result->parent->name << "]\n";
            }
            cout << "   👶 Jumlah child: " << result->children.size() << "\n";
        }
    }

    // ============================================================
    // FITUR 5: HITUNG JUMLAH FOLDER
    // ============================================================
    void countFolders() {
        int total = countRecursive(root);
        cout << "📊 Total folder dalam sistem: " << total << " folder\n";
    }

    // ============================================================
    // FITUR 6: TAMPILKAN PATH LENGKAP SUATU FOLDER
    // ============================================================
    void showFullPath(const string& folderName) {
        FolderNode* target = searchRecursive(root, folderName);
        if (target == nullptr) {
            cout << "❌ Folder [" << folderName << "] tidak ditemukan!\n";
        } else {
            cout << "📍 Path lengkap [" << folderName << "]: " << buildPath(target) << "\n";
        }
    }

    // ============================================================
    // TRAVERSAL: PREORDER
    // ============================================================
    void preorderTraversal() {
        cout << "\n🔁 PREORDER TRAVERSAL (Root → Children):\n";
        cout << "   ";
        preorderRecursive(root);
        cout << "\n";
    }

    // ============================================================
    // TRAVERSAL: POSTORDER
    // ============================================================
    void postorderTraversal() {
        cout << "\n🔁 POSTORDER TRAVERSAL (Children → Root):\n";
        cout << "   ";
        postorderRecursive(root);
        cout << "\n";
    }
};

// ============================================================
// MENU INTERAKTIF
// ============================================================
void printMenu() {
    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║     SIMULASI SISTEM FOLDER - TREE    ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║  1. Buat Folder Baru                 ║\n";
    cout << "║  2. Hapus Folder                     ║\n";
    cout << "║  3. Tampilkan Struktur Direktori     ║\n";
    cout << "║  4. Cari Folder                      ║\n";
    cout << "║  5. Hitung Jumlah Folder             ║\n";
    cout << "║  6. Tampilkan Path Lengkap           ║\n";
    cout << "║  7. Preorder Traversal               ║\n";
    cout << "║  8. Postorder Traversal              ║\n";
    cout << "║  0. Keluar                           ║\n";
    cout << "╚══════════════════════════════════════╝\n";
    cout << "Pilihan: ";
}

// ============================================================
// DEMO: Bangun struktur awal mirip Windows File Explorer
// ============================================================
void buildDemoStructure(FileSystemTree& fs) {
    cout << "\n📦 Membangun struktur demo...\n";

    // Level 1
    fs.createFolder("C:", "Program Files");
    fs.createFolder("C:", "Users");
    fs.createFolder("C:", "Windows");
    fs.createFolder("C:", "System32");

    // Level 2 - Program Files
    fs.createFolder("Program Files", "Microsoft Office");
    fs.createFolder("Program Files", "Google");
    fs.createFolder("Program Files", "Steam");

    // Level 2 - Users
    fs.createFolder("Users", "Admin");
    fs.createFolder("Users", "Public");

    // Level 3 - Admin
    fs.createFolder("Admin", "Documents");
    fs.createFolder("Admin", "Downloads");
    fs.createFolder("Admin", "Desktop");
    fs.createFolder("Admin", "Pictures");

    // Level 3 - Microsoft Office
    fs.createFolder("Microsoft Office", "Word");
    fs.createFolder("Microsoft Office", "Excel");
    fs.createFolder("Microsoft Office", "PowerPoint");

    // Level 3 - Google
    fs.createFolder("Google", "Chrome");
    fs.createFolder("Google", "Drive");

    // Level 4
    fs.createFolder("Documents", "Kuliah");
    fs.createFolder("Documents", "Kerja");
    fs.createFolder("Kuliah", "Struktur Data");
    fs.createFolder("Kuliah", "Kalkulus");
    fs.createFolder("Kuliah", "Sistem Operasi");

    cout << "✅ Struktur demo selesai dibangun!\n";
}

// ============================================================
// MAIN PROGRAM
// ============================================================
int main() {
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║   SIMULASI FILE SYSTEM DENGAN TREE   ║\n";
    cout << "║     Struktur Data - General Tree     ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";

    // Buat root folder
    FileSystemTree fs("C:");

    // Bangun struktur demo
    buildDemoStructure(fs);

    int pilihan;
    string input1, input2;

    do {
        printMenu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Nama folder parent: ";
                getline(cin, input1);
                cout << "Nama folder baru  : ";
                getline(cin, input2);
                fs.createFolder(input1, input2);
                break;

            case 2:
                cout << "Nama folder yang ingin dihapus: ";
                getline(cin, input1);
                fs.deleteFolder(input1);
                break;

            case 3:
                fs.displayDirectory();
                break;

            case 4:
                cout << "Nama folder yang dicari: ";
                getline(cin, input1);
                fs.searchFolder(input1);
                break;

            case 5:
                fs.countFolders();
                break;

            case 6:
                cout << "Nama folder: ";
                getline(cin, input1);
                fs.showFullPath(input1);
                break;

            case 7:
                fs.preorderTraversal();
                break;

            case 8:
                fs.postorderTraversal();
                break;

            case 0:
                cout << "\n👋 Terima kasih! Program selesai.\n";
                break;

            default:
                cout << "❌ Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    return 0;
}