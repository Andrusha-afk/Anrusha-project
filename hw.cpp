#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map> 
using namespace std;

struct Museum {
    string name;
    string location;
    string description;
    vector<string>* reviews;
    vector<string>* souvenirs;

    Museum() {
        reviews = new vector<string>();
        souvenirs = new vector<string>();
    }

    ~Museum() {
        delete reviews;
        delete souvenirs;
    }
};

void saveMuseumsByCity(const vector<Museum*>& museums) {
    map<string, vector<Museum*> > museumsByCity; 

    for (size_t i = 0; i < museums.size(); ++i) { 
        const Museum* museum = museums[i];

        if (museumsByCity.find(museum->location) == museumsByCity.end()) {
            museumsByCity[museum->location] = vector<Museum*>();
        }

        museumsByCity[museum->location].push_back(const_cast<Museum*>(museum));
    }

    for (map<string, vector<Museum*> >::const_iterator it = museumsByCity.begin(); it != museumsByCity.end(); ++it) { 
        const string& city = it->first;
        const vector<Museum*>& cityMuseums = it->second;

        string filename = city + ".txt";
        ofstream file(filename);
        if (!file) {
            cerr << "Ошибка открытия файла для записи музеев города " << city << ".\n";
            continue;
        }

        for (size_t i = 0; i < cityMuseums.size(); ++i) { 
            const Museum* museum = cityMuseums[i];
            file << museum->name << "|" << museum->location << "|" << museum->description << "|";

            for (size_t j = 0; j < museum->reviews->size(); ++j) { 
                file << (*museum->reviews)[j] << ",";
            }
            file << "|";

            for (size_t j = 0; j < museum->souvenirs->size(); ++j) { 
                file << (*museum->souvenirs)[j] << ",";
            }
            file << "\n";
        }

        file.close();
        cout << "Информация о музеях города " << city << " успешно сохранена в файл '" << filename << "'.\n";
    }
}

void loadMuseumsByCity(vector<Museum*>& museums) {
    vector<string> cities;
    cities.push_back("Владивосток");
    cities.push_back("Волгоград");
    cities.push_back("Москва");
    cities.push_back("Париж");
    cities.push_back("Марсель");
    cities.push_back("Нью-Йорк");
    cities.push_back("Лос-Анджелес");
    cities.push_back("Токио");
    cities.push_back("Киото");
    cities.push_back("Лондон");
    cities.push_back("Эдинбург");

    for (size_t i = 0; i < cities.size(); ++i) { 
        const string& city = cities[i];
        string filename = city + ".txt";
        ifstream file(filename);
        if (!file) {
            continue;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Museum* museum = new Museum();
            getline(ss, museum->name, '|');
            getline(ss, museum->location, '|');
            getline(ss, museum->description, '|');
            string reviews, souvenirs;
            getline(ss, reviews, '|');
            getline(ss, souvenirs, '|');
            stringstream reviewStream(reviews);
            string review;
            while (getline(reviewStream, review, ',')) {
                if (!review.empty()) {
                    museum->reviews->push_back(review);
                }
            }
            stringstream souvenirStream(souvenirs);
            string souvenir;
            while (getline(souvenirStream, souvenir, ',')) {
                if (!souvenir.empty()) {
                    museum->souvenirs->push_back(souvenir);
                }
            }
            museums.push_back(museum);
        }
        file.close();
        cout << "Информация о музеях города " << city << " успешно загружена из файла '" << filename << "'.\n";
    }
}

void displayMuseums(const vector<Museum*>& museums) {
    if (museums.empty()) {
        cout << "\nСписок музеев пуст. Добавьте новый музей.\n";
        return;
    }
    cout << "\nСписок музеев:\n";
    for (size_t i = 0; i < museums.size(); ++i) { 
        const Museum* museum = museums[i];
        cout << i + 1 << ". " << museum->name << " (" << museum->location << ")\n";
        cout << "   Описание: " << museum->description << "\n";
        if (!museum->reviews->empty()) {
            cout << "   Отзывы: \n";
            for (size_t j = 0; j < museum->reviews->size(); ++j) { 
                cout << "      - " << (*museum->reviews)[j] << "\n";
            }
        }
    }
}

void displaySouvenirs(const vector<Museum*>& museums) {
    if (museums.empty()) {
        cout << "\nСписок музеев пуст. Добавьте новый музей.\n";
        return;
    }
    cout << "\nСписок сувениров по музеям:\n";
    for (size_t i = 0; i < museums.size(); ++i) { 
        const Museum* museum = museums[i];
        cout << museum->name << " (" << museum->location << ")\n";
        if (museum->souvenirs->empty()) {
            cout << "   Сувениров пока нет.\n";
        } else {
            for (size_t j = 0; j < museum->souvenirs->size(); ++j) { 
                cout << "      - " << (*museum->souvenirs)[j] << "\n";
            }
        }
    }
}

void addMuseum(vector<Museum*>& museums, const string& city) {
    Museum* newMuseum = new Museum();
    newMuseum->location = city;
    cout << "Введите название музея: ";
    cin.ignore();
    getline(cin, newMuseum->name);
    cout << "Введите описание музея: ";
    getline(cin, newMuseum->description);
    museums.push_back(newMuseum);
    cout << "Музей успешно добавлен!\n";
}

void addReview(vector<Museum*>& museums) {
    if (museums.empty()) {
        cout << "\nСписок музеев пуст. Сначала добавьте музей.\n";
        return;
    }
    displayMuseums(museums);
    cout << "Введите номер музея, к которому хотите оставить отзыв: ";
    int index;
    cin >> index;
    cin.ignore();
    if (index < 1 || index > static_cast<int>(museums.size())) {
        cout << "Неверный номер музея.\n";
        return;
    }
    cout << "Введите ваш отзыв: ";
    string review;
    getline(cin, review);
    museums[index - 1]->reviews->push_back(review);
    cout << "Отзыв успешно добавлен!\n";
}

void addSouvenir(vector<Museum*>& museums) {
    if (museums.empty()) {
        cout << "\nСписок музеев пуст. Сначала добавьте музей.\n";
        return;
    }
    displayMuseums(museums);
    cout << "Введите номер музея, к которому хотите добавить сувениры: ";
    int index;
    cin >> index;
    cin.ignore();
    if (index < 1 || index > static_cast<int>(museums.size())) {
        cout << "Неверный номер музея.\n";
        return;
    }
    cout << "Введите название сувенира: ";
    string souvenir;
    getline(cin, souvenir);
    museums[index - 1]->souvenirs->push_back(souvenir);
    cout << "Сувенир успешно добавлен!\n";
}

void cleanup(vector<Museum*>& museums) {
    for (size_t i = 0; i < museums.size(); ++i) { 
        delete museums[i];
    }
    museums.clear();
}

int main() {
    vector<Museum*> museums;
    loadMuseumsByCity(museums); 
    int choice;
    string selectedCity;
    do {
        cout << "\nИндивидуальный гид по миру музеев и искусств";
        cout << "\nВыберите страну:";
        cout << "\n1. Россия";
        cout << "\n2. Франция";
        cout << "\n3. США";
        cout << "\n4. Япония";
        cout << "\n5. Великобритания";
        cout << "\n6. Выход";
        cout << "\nВведите ваш выбор: ";
        cin >> choice;
        if (choice == 6) {
            saveMuseumsByCity(museums); 
            cleanup(museums);
            cout << "\nСпасибо за использование гида! До свидания.\n";
            break;
        }
        switch (choice) {
            case 1: { 
                int cityChoice;
                cout << "\nВыберите город России:";
                cout << "\n1. Владивосток";
                cout << "\n2. Волгоград";
                cout << "\n3. Москва";
                cout << "\nВведите ваш выбор: ";
                cin >> cityChoice;
                switch (cityChoice) {
                    case 1: selectedCity = "Владивосток"; break;
                    case 2: selectedCity = "Волгоград"; break;
                    case 3: selectedCity = "Москва"; break;
                    default: cout << "\nНеверный выбор города, попробуйте снова.\n"; continue;
                }
                break;
            }
            case 2: { 
                int cityChoice;
                cout << "\nВыберите город Франции:";
                cout << "\n1. Париж";
                cout << "\n2. Марсель";
                cout << "\nВведите ваш выбор: ";
                cin >> cityChoice;
                switch (cityChoice) {
                    case 1: selectedCity = "Париж"; break;
                    case 2: selectedCity = "Марсель"; break;
                    default: cout << "\nНеверный выбор города, попробуйте снова.\n"; continue;
                }
                break;
            }
            case 3: { 
                int cityChoice;
                cout << "\nВыберите город США:";
                cout << "\n1. Нью-Йорк";
                cout << "\n2. Лос-Анджелес";
                cout << "\nВведите ваш выбор: ";
                cin >> cityChoice;
                switch (cityChoice) {
                    case 1: selectedCity = "Нью-Йорк"; break;
                    case 2: selectedCity = "Лос-Анджелес"; break;
                    default: cout << "\nНеверный выбор города, попробуйте снова.\n"; continue;
                }
                break;
            }
            case 4: { 
                int cityChoice;
                cout << "\nВыберите город Японии:";
                cout << "\n1. Токио";
                cout << "\n2. Киото";
                cout << "\nВведите ваш выбор: ";
                cin >> cityChoice;
                switch (cityChoice) {
                    case 1: selectedCity = "Токио"; break;
                    case 2: selectedCity = "Киото"; break;
                    default: cout << "\nНеверный выбор города, попробуйте снова.\n"; continue;
                }
                break;
            }
            case 5: { 
                int cityChoice;
                cout << "\nВыберите город Великобритании:";
                cout << "\n1. Лондон";
                cout << "\n2. Эдинбург";
                cout << "\nВведите ваш выбор: ";
                cin >> cityChoice;
                switch (cityChoice) {
                    case 1: selectedCity = "Лондон"; break;
                    case 2: selectedCity = "Эдинбург"; break;
                    default: cout << "\nНеверный выбор города, попробуйте снова.\n"; continue;
                }
                break;
            }
            default:
                cout << "\nНеверный выбор страны, попробуйте снова.\n";
                continue;
        }
        int cityAction;
        do {
            cout << "\nГород: " << selectedCity;
            cout << "\n1. Просмотреть список музеев";
            cout << "\n2. Добавить музей";
            cout << "\n3. Добавить отзыв";
            cout << "\n4. Добавить сувенир";
            cout << "\n5. Просмотреть сувениры";
            cout << "\n6. Назад к выбору страны";
            cout << "\nВведите ваш выбор: ";
            cin >> cityAction;
            cin.ignore();
            switch (cityAction) {
                case 1:
                    displayMuseums(museums);
                    break;
                case 2:
                    addMuseum(museums, selectedCity);
                    break;
                case 3:
                    addReview(museums);
                    break;
                case 4:
                    addSouvenir(museums);
                    break;
                case 5:
                    displaySouvenirs(museums);
                    break;
                case 6:
                    cout << "\nВозврат к выбору страны.\n";
                    break;
                default:
                    cout << "\nНеверный выбор, попробуйте снова.\n";
            }
        } while (cityAction != 6);
    } while (choice != 6);
    return 0;
}