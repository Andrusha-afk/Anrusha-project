#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Museum {
    string name;
    string location;
    string description;
    vector<string> reviews;
};

void displayMuseums(const vector<Museum>& museums) {
    if (museums.empty()) {
        cout << "\nСписок музеев пуст. Добавьте новый музей.\n";
        return;
    }
    cout << "\nСписок музеев:\n";
    for (size_t i = 0; i < museums.size(); i++) {
        cout << i + 1 << ". " << museums[i].name << " (" << museums[i].location << ")" << endl;
        cout << "   Описание: " << museums[i].description << "\n";
        if (!museums[i].reviews.empty()) {
            cout << "   Отзывы: \n";
            for (size_t j = 0; j < museums[i].reviews.size(); j++) {
                cout << "      - " << museums[i].reviews[j] << "\n";
            }
        }
    }
}

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

void addReview(vector<Museum>& museums) {
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
    museums[index - 1].reviews.push_back(review);
    cout << "Отзыв успешно добавлен!\n";
}

void recommendMuseum(const vector<Museum>& museums) {
    if (museums.empty()) {
        cout << "\nРекомендации отсутствуют, так как список музеев пуст.\n";
        return;
    }
    cout << "\nРекомендуем посетить: " << museums[0].name << " в " << museums[0].location << "\n";
}

int main() {
    vector<Museum> museums;
    int choice;
    string selectedCity;
    do {
        cout << "\nИндивидуальный гид по миру музеев и искусств";
        cout << "\nВыберите город:";
        cout << "\n1. Владивосток";
        cout << "\n2. Волгоград";
        cout << "\n3. Москва";
        cout << "\n4. Выход";
        cout << "\nВведите ваш выбор: ";
        cin >> choice;

        if (choice == 4) {
            cout << "\nСпасибо за использование гида! До свидания.\n";
            break;
        }

        switch (choice) {
            case 1:
                selectedCity = "Владивосток";
                break;
            case 2:
                selectedCity = "Волгоград";
                break;
            case 3:
                selectedCity = "Москва";
                break;
            default:
                cout << "\nНеверный выбор города, попробуйте снова.\n";
                continue;
        }

        int cityChoice;
        do {
            cout << "\nГород: " << selectedCity;
            cout << "\n1. Просмотреть список музеев";
            cout << "\n2. Добавить музей";
            cout << "\n3. Добавить отзыв";
            cout << "\n4. Получить рекомендацию";
            cout << "\n5. Назад к выбору города";
            cout << "\nВведите ваш выбор: ";
            cin >> cityChoice;
            cin.ignore();

            switch (cityChoice) {
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
                    recommendMuseum(museums);
                    break;
                case 5:
                    cout << "\nВозврат к выбору города.\n";
                    break;
                default:
                    cout << "\nНеверный выбор, попробуйте снова.\n";
            }
        } while (cityChoice != 5);

    } while (choice != 4);

    return 0;
} 