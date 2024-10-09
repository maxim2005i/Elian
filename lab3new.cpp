#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void loadFromFile(const char* filename, char**& array, int& size) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не удалось открыть файл!" << endl;
        return;
    }

    size = 0;
    array = new char*[100]; // Начальный размер массива
    while (!file.eof()) {
        array[size] = new char[256]; // Максимальная длина строки
        file.getline(array[size], 256);
        if (strlen(array[size]) > 0) {
            size++;
        }
    }
    file.close();
}

void addString(char**& array, int& size) {
    char* newString = new char[256];
    cout << "Введите строку для добавления: ";
    cin.ignore(); // Очищаем буфер
    cin.getline(newString, 256);

    array[size] = newString;
    size++;
}

void deleteString(char**& array, int& size) {
    int index;
    cout << "Введите индекс строки для удаления (0 - " << size - 1 << "): ";
    cin >> index;

    if (index < 0 || index >= size) {
        cout << "Некорректный индекс!" << endl;
        return;
    }

    delete[] array[index];
    
    for (int i = index; i < size - 1; i++) {
        array[i] = array[i + 1];
    }
    
    size--;
}

void editString(char**& array, int size) {
    int index;
    cout << "Введите индекс строки для редактирования (0 - " << size - 1 << "): ";
    cin >> index;

    if (index < 0 || index >= size) {
        cout << "Некорректный индекс!" << endl;
        return;
    }

    cout << "Введите новую строку: ";
    cin.ignore(); // Очищаем буфер
    char* newString = new char[256];
    cin.getline(newString, 256);

    delete[] array[index];
    array[index] = newString;
}

void saveToFile(const char* filename, char** array, int size) {
    ofstream file(filename);
    if (!file) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        file << array[i] << endl;
    }
    
    file.close();
}

void freeMemory(char** array, int size) {
    for (int i = 0; i < size; i++) {
        delete[] array[i];
    }
    delete[] array;
}

int main() {
    char** array = nullptr;
    int size = 0;
    
    loadFromFile("1.txt", array, size);
    
    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить строку\n";
        cout << "2. Удалить строку\n";
        cout << "3. Редактировать строку\n";
        cout << "4. Вывести массив на экран\n";
        cout << "5. Сохранить в новый файл\n";
        cout << "6. Вычисления по запросу\n";
	cout << "7. Выйти\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addString(array, size);
                break;
            case 2:
                deleteString(array, size);
                break; 
	            case 3:
                editString(array, size);
                break;
            case 4:
                for (int i = 0; i < size; i++) {
                    cout << i << ": " << array[i] << endl;
                }
                break;
            case 5: {
                char filename[256];
                cout << "Введите имя файла для сохранения: ";
                cin >> filename;
                saveToFile(filename, array, size);
                break;
            }

	    case 6: {	 
			    int i1;
			    int i2;
			    char operation;
       cout <<"Введите первое число"<<endl;
       cin >> i1; 
       
       cout<<"Введите 3нак операции (+ - * /):"<<endl;
       cin >> operation;

       cout<<"Введите второе число"<< endl;
       cin >> i2;
       
       if(operation == '+'){
          cout <<i1<<"+"<<i2<<"="<<i1+i2<<endl;}
        else if(operation == '-'){
          cout<<i1<<"-"<<i2<<"="<<i1-i2<<endl;  }
        else if(operation == '*'){
          cout<<i1<<"*"<<i2<<"="<<i1*i2<<endl;}
        else if(operation=='/'){
          if (i2 != 0){
              cout<<i1<<"/"<<i2<<"="<<i1/i2<<endl; }
            else{
              cerr<<"Деление на 0!"<<endl;
             break; }
        } else{
          cerr<<"UNKNOWN"<<endl;
          break;
        }
	break;
                                }
            case 7:
                freeMemory(array, size);
                break;
            default:
                cout << "Некорректный выбор!" << endl;
                break;
        }
    } while (choice != 7);
	return 0;
}

