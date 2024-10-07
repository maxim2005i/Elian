#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int a;
int k;
int addsize = 0;
int id1;
string name1;
int serialnumber1;
double price1;
string country1;
string firm1;
int amount1;

struct Data {
	int id; // id лекарства в базе данных
	string name; // название лекарства
	int serialnumber; // серийный номер лекарства
	double price; // цена
	string country; // страна-производитель
	string firm; // фирма-производитель
	int amount; // кол-во купленного лекарства за неделю среди покупателей
};

// Функция для чтения данных из файла в динамический массив
Data* read_data_from_file(const string& filename, int& size) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла: " << filename << endl;
        size = 0;
        return nullptr; // Возвращаем nullptr в случае ошибки
    }

    size = addsize + 7; // в нашей БД будет 7 разных лекарств изначально
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
	string line;
	cout << "Какую функцию необходимо выполнить? Введите номер" << endl;
	cout << "1 - Просмотр данных в массиве" << endl;
	cout << "2 - Редактирование записей \n3 - Вычисления по запросу" << endl;
	cin >> k;
	if (k != 1 and k != 2 and k != 3) {
	cout << "Ошибка ввода функции" << endl;
	}
	if (k == 1)
       	{
    const string filename = "1.txt";
    int size = 0;

    Data* dataArray = read_data_from_file(filename, size);

    // Проверяем, были ли считаны данные
    if (dataArray != nullptr) {
        // Вывод данных из массива на экран
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
        cout << "Нет данных для отображения. Убедитесь, что Вы верно ввели название файла" << endl;
    }
	}

	if (k == 2){
		cout <<"Введите номер требуемой функции"<< endl;
		cout <<"1 - Добавление записи в массив \n2 - Удаление записи из массива \n3 - Редактирование определенной записи"<< endl;
		cin >> a;
		if (a == 1) {
			cout << "Введите новую запись. Вводя новое поле, нажимайте enter каждый раз:id; название лекарства; серийный номер(3-4 цифры); цена; страна-производитель; фирма-производитель; количество " << endl;
			std::ofstream fout;
			fout.open("2.txt");
			cin >> id1;
			cin >> name1;
			cin >> serialnumber1;
			cin >> price1;
			cin >> country1;
			cin >> firm1;
			cin >> amount1;

			fout << id1 << " " << name1 << " "<< serialnumber1 << " " << price1 << " " << country1 << " "<< firm1 << " " << amount1 << endl; 
			fout.close();
			const string inputFileName = "2.txt";
			const string outputFileName = "1.txt";
			ifstream inputFile(inputFileName);
		if (!inputFile) {
		cerr << "Error while transmitting data" << endl;
		return 1;
		}	
		ofstream outputFile(outputFileName, ios::app);
			
			if (!outputFile) {
			cerr <<"Error while opening destination file" << endl;
			return 1;
			}
			while (getline(inputFile, line)) {
				outputFile << line << endl;
			}
			inputFile.close();
			outputFile.close();
			cout<< "Данные были успешно добавлены" << endl;
		}
		 remove("2.txt");
		 
				}
	return 0;

}
