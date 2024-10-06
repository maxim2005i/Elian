#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Data {
	int id;
	string name;
	int serialnumber;
	double price;
	string country;
	string firm;
	int amount;
};

// Функция для чтения данных из файла в динамический массив
Data* read_data_from_file(const string& filename, int& size) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла: " << filename << endl;
        size = 0;
        return nullptr; // Возвращаем nullptr в случае ошибки
    }

    size = 7; // в нашей БД будет 7 разных лекарств
    Data* dataArray = new Data[size];

    for (int i = 0; i < size; ++i) {
        if (!(file >> dataArray[i].id >> dataArray[i].name >> dataArray[i].serialnumber >> dataArray[i].price >> dataArray[i].country >> dataArray[i].firm >> dataArray[i].amount )) {
            cerr << "Ошибка чтения данных из файла." << endl;
            delete[] dataArray; // Освобождаем память при ошибке
            return nullptr;
        }
    }

    file.close();
    return dataArray; // Возвращаем заполненный динамический массив структур
}

int main() {
    const string filename = "1.txt";
    int size = 0;

    Data* dataArray = read_data_from_file(filename, size);

    // Проверяем, были ли считаны данные
    if (dataArray != nullptr) {
        // Выводим прочитанные данные
        for (int i = 0; i < size; ++i) {
            cout << "id: " << dataArray[i].id
		 << ", Name: " << dataArray[i].name 
                 << ", Serial Number: " << dataArray[i].serialnumber 
                 << ", Price: " << dataArray[i].price 
	    	 << ", Country: " << dataArray[i].country 
                 << ", Firm: " << dataArray[i].firm 
                 << ", Amount: " << dataArray[i].amount << endl;     	}

        delete[] dataArray; // Освобождаем память
    } else {
        cout << "Нет данных для отображения." << endl;
    }

    return 0;
}

