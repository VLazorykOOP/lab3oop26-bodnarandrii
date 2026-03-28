#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Date {
private:
    int day;   // 1-31 
    int month; // 1-12 
    int year;  

public:

    Date() {
        day = 1; month = 1; year = 2000;
    }

    Date(int d, int m, int y) {
        setYear(y); setMonth(m); setDay(d);
    }

    void setYear(int y) { year = y; }
    
    void setMonth(int m) {
        if (m >= 1 && m <= 12) month = m;
        else {
            cout << "Error: Month must be 1-12! Set to 1.\n";
            month = 1;
        }
    }

    void setDay(int d) {
        if (d >= 1 && d <= 31) day = d;
        else {
            cout << "Error: Day must be 1-31! Set to 1.\n";
            day = 1;
        }
    }

    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }

    void printFormat1() {
        string mNames[] = {"", "January", "February", "March", "April", "May", "June", 
                           "July", "August", "September", "October", "November", "December"};
        cout << "Format 1: " << day << " " << mNames[month] << " " << year << endl;
    }

    void printFormat2() {
        cout << "Format 2: " << setfill('0') << setw(2) << day << "." 
             << setfill('0') << setw(2) << month << "." << year << endl;
    }
};

// ЗАДАЧА 2.1: КЛАС VECTOR (ДИНАМІЧНИЙ МАСИВ)

class Vector {
private:
    int* data;      // Вказівник на елементи масиву 
    int size;       // Кількість елементів 
    int state;      // Стан: 0 - Ок, 1 - Помилка індексу/пам'яті [cite: 683, 695]
    static int count; // Лічильник створених об'єктів 

public:
    Vector() {
        size = 1;
        data = new int[size];
        data[0] = 0;
        state = 0;
        count++;
    }

    Vector(int n) {
        if (n <= 0) { state = 1; size = 1; data = new int[1]; data[0] = 0; }
        else {
            size = n;
            data = new int[size];
            for (int i = 0; i < size; i++) data[i] = 0;
            state = 0;
        }
        count++;
    }

    Vector(int n, int value) {
        if (n <= 0) { state = 1; size = 1; data = new int[1]; data[0] = 0; }
        else {
            size = n;
            data = new int[size];
            for (int i = 0; i < size; i++) data[i] = value;
            state = 0;
        }
        count++;
    }

    //Конструктор копій 
    Vector(const Vector& other) {
        size = other.size;
        state = other.state;
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
        count++;
    }

    //Оператор присвоєння
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this; 
        delete[] data; 
        size = other.size;
        state = other.state;
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
        return *this;
    }
 
    ~Vector() {
        delete[] data;
        count--;
    }

    void setElement(int index, int value = 0) {
        if (index >= 0 && index < size) data[index] = value;
        else { cout << "Error: Index out of bounds!\n"; state = 1; }
    }

    int getElement(int index) {
        if (index >= 0 && index < size) return data[index];
        cout << "Error: Index out of bounds!\n"; 
        state = 1; 
        return 0;
    }

    void print() {
        cout << "Vector (size " << size << "): [ ";
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << "] State: " << state << endl;
    }

    // Додавання векторів [cite: 693]
    Vector Add(const Vector& b) {
        int minSize = (size < b.size) ? size : b.size; // Додаємо по найменшому розміру
        Vector result(minSize);
        for (int i = 0; i < minSize; i++) result.data[i] = data[i] + b.data[i];
        return result;
    }

    // Віднімання векторів [cite: 693]
    Vector Sub(const Vector& b) {
        int minSize = (size < b.size) ? size : b.size;
        Vector result(minSize);
        for (int i = 0; i < minSize; i++) result.data[i] = data[i] - b.data[i];
        return result;
    }

    // Множення на число типу short [cite: 693]
    Vector Mul(short scalar) {
        Vector result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] * scalar;
        return result;
    }

    // Порівняння: Більше [cite: 694]
    bool isGreater(const Vector& b) {
        // Просте порівняння: якщо сума елементів більша
        int sumA = 0, sumB = 0;
        for (int i = 0; i < size; i++) sumA += data[i];
        for (int i = 0; i < b.size; i++) sumB += b.data[i];
        return sumA > sumB;
    }
 
    static int getCount() { return count; }
};

// Ініціалізація статичної змінної
int Vector::count = 0;

void testDate() {
    int d, m, y;
    cout << "\n--- Testing Date Class ---" << endl;
    cout << "Enter Day (1-31): "; cin >> d;
    cout << "Enter Month (1-12): "; cin >> m;
    cout << "Enter Year: "; cin >> y;

    Date myDate(d, m, y); 
    
    myDate.printFormat1();
    myDate.printFormat2();
}

void testVector() {
    int size1, val1, size2, val2;
    short scalar;

    cout << "\n--- Testing Vector Class ---" << endl;
    
    // Створення Вектора 1
    cout << "Enter size for Vector 1: "; cin >> size1;
    cout << "Enter initial value for all elements in Vector 1: "; cin >> val1;
    Vector v1(size1, val1);
    
    // Створення Вектора 2
    cout << "Enter size for Vector 2: "; cin >> size2;
    cout << "Enter initial value for all elements in Vector 2: "; cin >> val2;
    Vector v2(size2, val2);

    cout << "\nVectors created:" << endl;
    cout << "V1: "; v1.print();
    cout << "V2: "; v2.print();

    cout << "\nTesting Addition (V1 + V2):" << endl;
    Vector v3 = v1.Add(v2);
    v3.print();

    cout << "\nTesting Multiplication of V1 by a short number." << endl;
    cout << "Enter a short number to multiply V1: "; cin >> scalar;
    Vector v4 = v1.Mul(scalar);
    v4.print();

    cout << "\nTotal Vector objects currently in memory: " << Vector::getCount() << endl;
}

int main() {
    int choice = -1;

    while (choice != 0) {
        cout << "\n===============================" << endl;
        cout << "      MAIN MENU      " << endl;
        cout << "===============================" << endl;
        cout << "1. Test Task 1.1 (Date Class)" << endl;
        cout << "2. Test Task 2.1 (Vector Class)" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                testDate();
                break;
            case 2:
                testVector();
                break;
            case 0:
                cout << "Exiting program. Good luck!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}