#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Medicine {
private:
    int id;
    string name;
    int serialnumber;
    double price;
    string country;
    string firm;
    int amount;

public:
    // Конструктор по умолчанию
    Medicine() : id(0), name(""), serialnumber(0), price(0.0), country(""), firm(""), amount(0) {}

    // Конструктор с параметрами
    Medicine(int id, string name, int serialnumber, double price, string country, string firm, int amount)
        : id(id), name(name), serialnumber(serialnumber), price(price), country(country), firm(firm), amount(amount) {}

    // Методы для доступа к свойствам
    void setId(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setSerialNumber(int serialnumber) { this->serialnumber = serialnumber; }
    void setPrice(double price) { this->price = price; }
    void setCountry(string country) { this->country = country; }
    void setFirm(string firm) { this->firm = firm; }
    void setAmount(int amount) { this->amount = amount; }

    int getId() const { return id; }
    string getName() const { return name; }
    int getSerialNumber() const { return serialnumber; }
    double getPrice() const { return price; }
    string getCountry() const { return country; }
    string getFirm() const { return firm; }
    int getAmount() const { return amount; }

    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Serial Number: " << serialnumber
             << ", Price: " << price << ", Country: " << country << ", Firm: " << firm
             << ", Amount: " << amount << endl;
    }
};

void loadMedicines(Medicine*& medicines, int& count, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return;
    }

    string line;
    count = 0;
    
    while (getline(file, line)) {
        istringstream ss(line);
        string token;

        // Получаем данные из строки
        int id, serialnumber, amount;
        double price;
        string name, country, firm;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ','); serialnumber = stoi(token);
        getline(ss, token, ','); price = stod(token);
        getline(ss, country, ',');
        getline(ss, firm, ',');
        getline(ss, token, ','); amount = stoi(token);

        medicines[count++] = Medicine(id, name, serialnumber, price, country, firm, amount);
    }

    file.close();
}

void saveMedicines(Medicine* medicines, int count, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return;
    }

    for (int i = 0; i < count; ++i) {
        file << medicines[i].getId() << ","
             << medicines[i].getName() << ","
             << medicines[i].getSerialNumber() << ","
             << medicines[i].getPrice() << ","
             << medicines[i].getCountry() << ","
             << medicines[i].getFirm() << ","
             << medicines[i].getAmount() << endl;
    }

    file.close();
}

void displayMedicines(Medicine* medicines, int count) {
    for (int i = 0; i < count; ++i) {
        medicines[i].display();
    }
}

void editMedicine(Medicine* medicines, int count) {
    int index;
    cout << "Введите номер строки (индекс объекта) для редактирования (0-" << count - 1 << "): ";
    cin >> index;

    if (index < 0 || index >= count) {
        cout << "Неверный индекс!" << endl;
        return;
    }

    int choice;
    cout << "Выберите свойство для редактирования:\n"
         << "1. ID\n"
         << "2. Name\n"
         << "3. Serial Number\n"
         << "4. Price\n"
         << "5. Country\n"
         << "6. Firm\n"
         << "7. Amount\n";
    cin >> choice;

    switch (choice) {
        case 1: {
            int id;
            cout << "Введите новый ID: ";
            cin >> id;
            medicines[index].setId(id);
            break;
        }
        case 2: {
            string name;
            cout << "Введите новое имя: ";
            cin >> name;
            medicines[index].setName(name);
            break;
        }
        case 3: {
            int serialnumber;
            cout << "Введите новый серийный номер: ";
            cin >> serialnumber;
            medicines[index].setSerialNumber(serialnumber);
            break;
        }
        case 4: {
            double price;
            cout << "Введите новую цену: ";
            cin >> price;
            medicines[index].setPrice(price);
            break;
        }
        case 5: {
            string country;
            cout << "Введите новую страну: ";
            cin >> country;
            medicines[index].setCountry(country);
            break;
        }
        case 6: {
            string firm;
            cout << "Введите новую фирму: ";
            cin >> firm;
            medicines[index].setFirm(firm);
            break;
        }
        case 7: {
            int amount;
            cout << "Введите новое количество: ";
            cin >> amount;
            medicines[index].setAmount(amount);
            break;
        }
        default:
            cout << "Неверный выбор!" << endl;
            break;
    }
}

void addMedicine(Medicine*& medicines, int& count) {
    Medicine* newMedicines = new Medicine[count + 1];

    for (int i = 0; i < count; ++i) {
        newMedicines[i] = medicines[i];
    }

    int id, serialnumber, amount;
    double price;
    string name, country, firm;

    cout << "Введите ID: ";
    cin >> id;
    cout << "Введите имя: ";
    cin >> name;
    cout << "Введите серийный номер: ";
    cin >> serialnumber;
    cout << "Введите цену: ";
    cin >> price;
    cout << "Введите страну: ";
    cin >> country;
    cout << "Введите фирму: ";
    cin >> firm;
    cout << "Введите количество: ";
    cin >> amount;

    newMedicines[count] = Medicine(id, name, serialnumber, price, country, firm, amount);
    
    delete[] medicines; // Освобождение старого массива
    medicines = newMedicines; // Указатель на новый массив
    count++;
}

void deleteMedicine(Medicine*& medicines, int& count) {
    int index;
    cout << "Введите индекс объекта для удаления (0-" << count - 1 << "): ";
    cin >> index;

    if (index < 0 || index >= count) {
        cout << "Неверный индекс!" << endl;
        return;
    }

    Medicine* newMedicines = new Medicine[count - 1];

    for (int i = 0; i < index; ++i) {
        newMedicines[i] = medicines[i];
    }

    for (int i = index + 1; i < count; ++i) {
        newMedicines[i - 1] = medicines[i];
    }

    delete[] medicines; // Освобождение старого массива
    medicines = newMedicines; // Указатель на новый массив
    count--;
}

int main() {
    Medicine* medicines = new Medicine[100]; // Предположим максимальное количество объектов 100
    int count = 0;

    loadMedicines(medicines, count, "1.txt");

    while (true) {
        cout << "\nМеню:\n"
             << "1. Просмотр всех объектов\n"
             << "2. Редактирование объекта\n"
             << "3. Добавление нового объекта\n"
             << "4. Удаление объекта\n"
             << "5. Сохранение в файл\n"
             << "6. Выход\n";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                displayMedicines(medicines, count);
                break;
            case 2:
                editMedicine(medicines, count);
		displayMedicines(medicines, count);
                break;
            case 3:
                addMedicine(medicines, count);
		displayMedicines(medicines, count);
                break;
            case 4:
                deleteMedicine(medicines, count);
		displayMedicines(medicines, count);
                break;
            case 5: {
                string filename;
                cout << "Введите имя файла для сохранения: ";
                cin >> filename;
                saveMedicines(medicines, count, filename);
                break;
            }
            case 6:
                delete[] medicines; // Освобождение памяти
                return 0;
            default:
                cout << "Неверный выбор!" << endl;
                break;
        }
    }

    delete[] medicines; // Освобождение памяти
}

