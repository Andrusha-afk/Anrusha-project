#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Структура для хранения информации о музее
struct Museum {
    string name; //Название
    string location; //Локация
    string description; //Описание
    vector<string> reviews; // Отзывы
    vector<string> souvenirs; // Сувениры
};

// Функция для сохранения данных в файл
void saveMuseumsByCity(const vector<Museum>& museums) {
    map<string, vector<Museum> > museumsByCity;

    // Группируем музеи по городам
    for (size_t i = 0; i < museums.size(); ++i) {
        const Museum& museum = museums[i];
        museumsByCity[museum.location].push_back(museum);
    }

    // Сохраняем данные в файлы
    for (map<string, vector<Museum> >::const_iterator it = museumsByCity.begin(); it != museumsByCity.end(); ++it) {
        const string& city = it->first;
        const vector<Museum>& cityMuseums = it->second;

        string filename = city + ".txt";
        ofstream file(filename.c_str()); 
        if (!file) {
            cout << "Ошибка открытия файла для записи музеев города " << city << ".\n";
            continue;
        }

        for (size_t i = 0; i < cityMuseums.size(); ++i) {
            const Museum& museum = cityMuseums[i];
            file << museum.name << "|"
                 << museum.location << "|"
                 << museum.description << "|";

            // Сохраняем отзывы
            for (size_t j = 0; j < museum.reviews.size(); ++j) {
                file << museum.reviews[j] << ",";
            }
            file << "|";

            // Сохраняем сувениры
            for (size_t j = 0; j < museum.souvenirs.size(); ++j) {
                file << museum.souvenirs[j] << ",";
            }
            file << "\n";
        }

        file.close();
        cout << "Информация о музеях города " << city << " успешно сохранена в файл '" << filename << "'.\n";
    }
}

// Функция для загрузки данных из файлов
void loadMuseumsByCity(vector<Museum>& museums) {
    // Список городов
    string cities[] = {"Владивосток", "Москва", "Париж", "Лондон"};
    size_t cityCount = sizeof(cities) / sizeof(cities[0]);

    for (size_t i = 0; i < cityCount; ++i) {
        const string& city = cities[i];
        string filename = city + ".txt";
        ifstream file(filename.c_str()); 
        if (!file) {
            continue; // Если файл не существует, переходим к следующему городу
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Museum museum;

            // Разбираем строку на поля
            getline(ss, museum.name, '|');
            getline(ss, museum.location, '|');
            getline(ss, museum.description, '|');

            string reviews, souvenirs;
            getline(ss, reviews, '|');
            getline(ss, souvenirs, '|');

            // Разбираем отзывы
            stringstream reviewStream(reviews);
            string review;
            while (getline(reviewStream, review, ',')) {
                if (!review.empty()) {
                    museum.reviews.push_back(review);
                }
            }

            // Разбираем сувениры
            stringstream souvenirStream(souvenirs);
            string souvenir;
            while (getline(souvenirStream, souvenir, ',')) {
                if (!souvenir.empty()) {
                    museum.souvenirs.push_back(souvenir);
                }
            }

            museums.push_back(museum);
        }

        file.close();
        cout << "Информация о музеях города " << city << " успешно загружена из файла '" << filename << "'.\n";
    }
}

// Функция для отображения списка музеев
void displayMuseums(const vector<Museum>& museums) {
    if (museums.empty()) {
        cout << "\nСписок музеев пуст. Добавьте новый музей.\n";
        return;
    }

    cout << "\nСписок музеев:\n";
    for (size_t i = 0; i < museums.size(); ++i) {
        const Museum& museum = museums[i];
        cout << i + 1 << ". " << museum.name << " (" << museum.location << ")\n";
        cout << "   Описание: " << museum.description << "\n";

        if (!museum.reviews.empty()) {
            cout << "   Отзывы: \n";
            for (size_t j = 0; j < museum.reviews.size(); ++j) {
                cout << "      - " << museum.reviews[j] << "\n";
            }
        }
    }
}

// Функция для добавления нового музея
void addMuseum(vector<Museum>& museums, const string& city) {
    Museum newMuseum;
    newMuseum.location = city;

    cout << "Введите название музея: ";
    cin.ignore();
    getline(cin, newMuseum.name);

    cout << "Введите описание музея: ";
    getline(cin, newMuseum.description);

    museums.push_back(newMuseum);
    cout << "Музей успешно добавлен!\n";
}

// Функция для добавления отзыва
void addReview(vector<Museum>& museums) {
    if (museums.empty()) {
        cout << "\nСписок музеев пуст. Сначала добавьте музей.\n";
        return;
    }

    displayMuseums(museums);
    cout << "Введите номер музея, к которому хотите оставить отзыв: ";
    int index;
    cin >> index;

    if (index < 1 || index > static_cast<int>(museums.size())) {
        cout << "Неверный номер музея.\n";
        return;
    }

    cout << "Введите ваш отзыв: ";
    cin.ignore();
    string review;
    getline(cin, review);

    museums[index - 1].reviews.push_back(review);
    cout << "Отзыв успешно добавлен!\n";
}

// Функция для добавления сувенира
void addSouvenir(vector<Museum>& museums) {
    if (museums.empty()) {
        cout << "\nСписок музеев пуст. Сначала добавьте музей.\n";
        return;
    }

    displayMuseums(museums);
    cout << "Введите номер музея, к которому хотите добавить сувенир: ";
    int index;
    cin >> index;

    if (index < 1 || index > static_cast<int>(museums.size())) {
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
    vector<Museum> museums;

    // Автоматическая загрузка данных при запуске программы
    loadMuseumsByCity(museums);

    int choice;
    string selectedCity;

    do {
        cout << "\nИндивидуальный гид по миру музеев и искусств\n";
        cout << "1. Россия\n";
        cout << "2. Франция\n";
        cout << "3. Великобритания\n";
        cout << "4. Выход\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        if (choice == 5) {
            // Автоматическое сохранение данных при выходе из программы
            saveMuseumsByCity(museums);
            cout << "\nСпасибо за использование гида! До свидания.\n";
            break;
        }

        switch (choice) {
            case 1:
                selectedCity = "Москва";
                break;
            case 2:
                selectedCity = "Париж";
                break;
            case 3:
                selectedCity = "Лондон";
                break;
            default:
                cout << "\nНеверный выбор страны, попробуйте снова.\n";
                continue;
        }

        int cityAction;
        do {
            cout << "\nГород: " << selectedCity << "\n";
            cout << "1. Просмотреть список музеев\n";
            cout << "2. Добавить музей\n";
            cout << "3. Добавить отзыв\n";
            cout << "4. Добавить сувенир\n";
            cout << "5. Назад к выбору страны\n";
            cout << "Введите ваш выбор: ";
            cin >> cityAction;

            switch (cityAction) {
                case 1:
                    displayMuseums(museums);
                    break;
                case 2:
                    addMuseum(museums, selectedCity);
                    saveMuseumsByCity(museums); // Сохраняем данные после добавления
                    break;
                case 3:
                    addReview(museums);
                    saveMuseumsByCity(museums); // Сохраняем данные после добавления
                    break;
                case 4:
                    addSouvenir(museums);
                    saveMuseumsByCity(museums); // Сохраняем данные после добавления
                    break;
                case 5:
                    cout << "\nВозврат к выбору страны.\n";
                    break;
                default:
                    cout << "\nНеверный выбор, попробуйте снова.\n";
            }
        } while (cityAction != 5);
    } while (choice != 4);

    return 0;
}