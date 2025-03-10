#include <iostream>
#include <vector>
#include <string> 
#include <fstream>
using namespace std;

struct Museum {
    string name;
    string location;
    string description;
    vector<string> reviews;
    vector<string> souvenirs;
};
void saveMuseumsToFile(vector<Museum>& museums) { //это ссылка на вектор объектов типа Museum.
    ofstream file("museums.txt");
    if (!file) {
        cout << "Ошибка: не удалось открыть файл для записи.\n";
        return;
    } 
    for (Museum museum : museums) { //Цикл проходит по всем элементам контейнера museums по порядку.
        file << museum.name << "|" << museum.location << "|" << museum.description << "|";
        for (int i = 0; i < museum.reviews.size(); ++i) {
            file << museum.reviews[i];
            if (i < museum.reviews.size() - 1) file << ","; //Эта строка кода добавляет запятую (,) после каждого элемента, кроме последнего , при записи элементов из контейнера reviews объекта museum в файл.
        }
        file << "|";
        for (int i = 0; i < museum.souvenirs.size(); ++i) {
            file << museum.souvenirs[i];
            if (i < museum.souvenirs.size() - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
    cout << "Данные успешно сохранены в файл 'museums.txt'.\n";
}

vector<Museum> loadMuseumsFromFile() { //Функция vector<Museum> loadMuseumsFromFile() — это функция, которая загружает данные о музеях из файла и возвращает их в виде вектора объектов типа Museum.
    vector<Museum> museums;
    ifstream file("museums.txt");
    if (!file) {
        cout << "Файл 'museums.txt' не найден.\n";
        return museums;
    }

    string line;
    while (getline(file, line)) {
        Museum museum;
        int pos = 0;
        museum.name = line.substr(0, line.find('|'));
        pos = line.find('|') + 1;
        museum.location = line.substr(pos, line.find('|', pos) - pos);
        pos = line.find('|', pos) + 1;
        museum.description = line.substr(pos, line.find('|', pos) - pos);
        pos = line.find('|', pos) + 1;

        string reviewsStr = line.substr(pos, line.find('|', pos) - pos);
        pos = line.find('|', pos) + 1;
        if (!reviewsStr.empty()) {
            int start = 0;
            size_t end = reviewsStr.find(',');
            while (end != string::npos) {
                museum.reviews.push_back(reviewsStr.substr(start, end - start));
                start = end + 1;
                end = reviewsStr.find(',', start);
            }
            museum.reviews.push_back(reviewsStr.substr(start));
        }

        // Разбираем сувениры
        string souvenirsStr = line.substr(pos);
        if (!souvenirsStr.empty()) {
            int start = 0;
            int end = souvenirsStr.find(','); // end — это позиция первой запятой в строке, найденная с помощью метода find(',').
            while (end != string::npos) { // Цикл продолжается, пока end != string::npos. Это означает, что пока есть запятые в строке, мы продолжаем разбивать её на части.
                museum.souvenirs.push_back(souvenirsStr.substr(start, end - start));
                start = end + 1;
                end = souvenirsStr.find(',', start);
            }
            museum.souvenirs.push_back(souvenirsStr.substr(start));
        }

        museums.push_back(museum); //push_back — это метод стандартного контейнера std::vector в C++. Он добавляет новый элемент в конец вектора, увеличивая его размер на 1.
    }
    file.close();
    cout << "Данные успешно загружены из файла 'museums.txt'.\n";
    return museums;
}

// Функция для отображения списка музеев
void displayMuseums (vector<Museum>& museums) {
    if (museums.empty()) {
        cout << "Список музеев пуст.\n";
        return;
    }
    cout << "Список музеев:\n";
    for (int i = 0; i < museums.size(); ++i) { //Префиксный инкремент (++i): 2. Постфиксный инкремент (i++):
        cout << i + 1 << ". " << museums[i].name << " (" << museums[i].location << ")\n";
        cout << "   Описание: " << museums[i].description << "\n";
        if (!museums[i].reviews.empty()) {
            cout << "   Отзывы:\n";
            for (string review : museums[i].reviews) { // : разделить переменную в коллекции 
                cout << "      - " << review << "\n";
            }
        }
        if (!museums[i].souvenirs.empty()) {
            cout << "   Сувениры:\n";
            for (string souvenir : museums[i].souvenirs) {
                cout << "      - " << souvenir << "\n";
            }
        }
    }
}

// Функция для добавления нового музея
void addMuseum(vector<Museum>& museums) {
    Museum newMuseum;
    cout << "Введите название музея: ";
    cin.ignore();
    getline(cin, newMuseum.name);
    cout << "Введите город: ";
    getline(cin, newMuseum.location);
    cout << "Введите описание музея: ";
    getline(cin, newMuseum.description);
    museums.push_back(newMuseum);
    cout << "Музей успешно добавлен!\n";
}

// Функция для добавления отзыва
void addReview(vector<Museum>& museums) {
    if (museums.empty()) {
        cout << "Список музеев пуст. Добавьте новый музей.\n";
        return;
    }
    displayMuseums(museums);
    cout << "Введите номер музея для добавления отзыва: ";
    int index;
    cin >> index;
    if (index < 1 || index >(museums.size())) {
        cout << "Неверный номер музея.\n";
        return;
    }
    cout << "Введите ваш отзыв: ";
    cin.ignore(); //Это необходимо, если перед этим использовался cin >>, так как он оставляет символ новой строки (\n) в
    string review;
    getline(cin, review);
    museums[index - 1].reviews.push_back(review); //index - 1 — индекс музея в векторе (вычитание -1 используется, если пользователь вводит номер музея с 1, а не с 0).
    cout << "Отзыв успешно добавлен!\n";
}

// Функция для добавления сувенира
void addSouvenir(vector<Museum>& museums) {
    if (museums.empty()) {
        cout << "Список музеев пуст. Добавьте новый музей.\n";
        return;
    }
    displayMuseums(museums);
    cout << "Введите номер музея для добавления сувенира: ";
    int index;
    cin >> index;
    if (index < 1 or index > (museums.size())) {
        cout << "Неверный номер музея.\n";
        return;
    }
    cout << "Введите название сувенира: ";
    cin.ignore();
    string souvenir;
    getline(cin, souvenir);
    museums[index - 1].souvenirs.push_back(souvenir);
    cout << "Сувенир успешно добавлен!\n";
}

int main() {
    setlocale(0, "RU");
    system("chsp 1251");
    vector<Museum> museums = loadMuseumsFromFile();

    int choice;
    while (true) { 
        cout << "\nИндивидуальный гид по музеям\n";
        cout << "1. Просмотреть список музеев\n";
        cout << "2. Добавить музей\n";
        cout << "3. Добавить отзыв\n";
        cout << "4. Добавить сувенир\n";
        cout << "5. Сохранить и выйти\n";
        cout << "Введите ваш выбор: ";

        if (!(cin >> choice)) {
            cout << "Ошибка ввода. Программа завершается.\n";
            break; 
        }

        switch (choice) {
        case 1:
            displayMuseums(museums);
            break;
        case 2:
            addMuseum(museums);
            break;
        case 3:
            addReview(museums);
            break;
        case 4:
            addSouvenir(museums);
            break;
        case 5:
            saveMuseumsToFile(museums);
            cout << "Данные сохранены. До свидания!\n";
            return 0; 
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
    }

    return 0;
}