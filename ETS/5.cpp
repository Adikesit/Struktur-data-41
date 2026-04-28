#include <iostream>
#include <string>
using namespace std;

const int MAX = 9;
string antrian[MAX];
int front = -1, rear = -1;

bool isEmpty() { return front == -1; }
bool isFull()  { return rear == MAX - 1; }

void enqueue(string nama) {
    if (isFull()) {
        cout << "Antrian penuh!" << endl;
        return;
    }
    if (isEmpty()) front = 0;
    rear++;
    antrian[rear] = nama;
    cout << nama << " masuk antrian. Nomor: " << rear + 1 << endl;
}

void dequeue() {
    if (isEmpty()) {
        cout << "Antrian kosong!" << endl;
        return;
    }
    cout << antrian[front] << " sedang dilayani." << endl;
    if (front == rear) { front = rear = -1; }
    else front++;
}

void tampilAntrian() {
    if (isEmpty()) {
        cout << "Antrian kosong." << endl;
        return;
    }
    cout << "Antrian saat ini: ";
    for (int i = front; i <= rear; i++)
        cout << antrian[i] << " ";
    cout << endl;
    cout << "Front: " << antrian[front]
         << " | Rear: " << antrian[rear] << endl;
}

int main() {
    enqueue("Mahasiswa A");
    enqueue("Mahasiswa B");
    enqueue("Mahasiswa C");
    tampilAntrian();
    dequeue();
    enqueue("Mahasiswa D");
    tampilAntrian();
    return 0;
}