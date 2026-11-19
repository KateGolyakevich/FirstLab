#include <iostream>
#include <limits>
#include "../include/Collection.hpp"
#include "../include/Therapist.h"
#include "../include/Surgeon.h"
#include "../include/Orthodontist.h"
#include "../include/TherapeuticService.h"
#include "../include/SurgicalService.h"
#include "../include/OrthodonticService.h"
#include "../include/Patient.h"
#include "../include/ClinicFileManager.h"

// Вспомогательная функция безопасного ввода чисел
int get_int_input(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "[Ошибка ввода] Введите целое число!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Функция ручного добавления врача
void manual_add_doctor(Collection<Doctor*>& doctors) {
    std::cout << "\n--- Добавление врача ---\n";
    std::cout << "1. Терапевт\n2. Хирург\n3. Ортодонт\nВыбор: ";
    int type = get_int_input("");
    std::cout << "Введите ФИО врача: ";
    std::string name;
    std::getline(std::cin, name);
    int exp = get_int_input("Стаж работы (лет): ");

    if (type == 1) {
        int teeth = get_int_input("Вылечено зубов: ");
        doctors.add(new Therapist(name, exp, teeth));
    } else if (type == 2) {
        int ops = get_int_input("Проведено операций: ");
        doctors.add(new Surgeon(name, exp, ops));
    } else if (type == 3) {
        int braces = get_int_input("Пациентов с брекетами: ");
        doctors.add(new Orthodontist(name, exp, braces));
    } else {
        std::cout << "Неверный тип!\n";
        return;
    }
    std::cout << "[Успех] Врач добавлен в штат!\n";
    ClinicFileManager::log_event("journal.log", "Добавлен новый врач: " + name);
}

// Функция ручного добавления пациента
void manual_add_patient(Collection<Patient>& patients) {
    std::cout << "\n--- Регистрация нового пациента ---\n";
    std::cout << "Введите ФИО пациента: ";
    std::string name;
    std::getline(std::cin, name);
    int card_choice = get_int_input("Есть дисконтная карта? (1 - Да, 0 - Нет): ");
    patients.add(Patient(name, card_choice == 1));
    std::cout << "[Успех] Пациент зарегистрирован!\n";
    ClinicFileManager::log_event("journal.log", "Зарегистрирован пациент: " + name);
}

int main() {
    Collection<Doctor*> doctors;
    Collection<Service*> services;
    Collection<Patient> patients;

    // Первичная инициализация базовыми данными (если файлов ещё нет)
    Doctor* d1 = new Therapist("Иванов И.И.", 10, 450);
    Doctor* d2 = new Surgeon("Петров П.П.", 15, 300);
    doctors.add(d1);
    doctors.add(d2);
    services.add(new TherapeuticService("Лечение кариеса", 2500, 40, "16", false, d1));
    services.add(new SurgicalService("Удаление зуба", 4000, 30, "Экстракция", d2));
    patients.add(Patient("Смирнов А.М.", true));

    ClinicFileManager::log_event("journal.log", "Запуск программы стоматологической клиники.");

    const std::string state_file = "clinic_state.txt";
    const std::string report_file = "clinic_report.txt";

    while (true) {
        std::cout << "\n====================================================\n";
        std::cout << "     СТОМАТОЛОГИЧЕСКАЯ КЛИНИКА (ЛАБОРАТОРНАЯ №7)    \n";
        std::cout << "====================================================\n";
        std::cout << "1. Просмотр текущего состояния системы\n";
        std::cout << "2. Добавить врача (ручной ввод)\n";
        std::cout << "3. Зарегистрировать пациента (ручной ввод)\n";
        std::cout << "4. Сохранить состояние системы в файл (" << state_file << ")\n";
        std::cout << "5. Загрузить состояние системы из файла (" << state_file << ")\n";
        std::cout << "6. Сформировать текстовый отчёт (" << report_file << ")\n";
        std::cout << "0. Выход из программы\n";

        int choice = get_int_input("Выберите действие: ");

        if (choice == 1) {
            std::cout << "\n--- ШТАТ ВРАЧЕЙ ---\n" << doctors;
            std::cout << "\n--- ПРЕЙСКУРАНТ УСЛУГ ---\n" << services;
            std::cout << "\n--- КАРТОТЕКА ПАЦИЕНТОВ ---\n" << patients;
        } else if (choice == 2) {
            manual_add_doctor(doctors);
        } else if (choice == 3) {
            manual_add_patient(patients);
        } else if (choice == 4) {
            if (ClinicFileManager::save_system_state(state_file, doctors, services, patients)) {
                std::cout << "[Успех] Состояние успешно сохранено в " << state_file << "\n";
            } else {
                std::cout << "[Ошибка] Не удалось записать файл!\n";
            }
        } else if (choice == 5) {
            if (ClinicFileManager::load_system_state(state_file, doctors, services, patients)) {
                std::cout << "[Успех] Состояние восстановлено из " << state_file << "\n";
            } else {
                std::cout << "[Ошибка] Файл не найден или повреждён!\n";
            }
        } else if (choice == 6) {
            if (ClinicFileManager::generate_text_report(report_file, doctors, services, patients)) {
                std::cout << "[Успех] Аналитический отчёт сохранён в " << report_file << "\n";
            } else {
                std::cout << "[Ошибка] Ошибка генерации отчёта!\n";
            }
        } else if (choice == 0) {
            std::cout << "Завершение работы программы...\n";
            ClinicFileManager::log_event("journal.log", "Штатный выход из программы.");
            break;
        } else {
            std::cout << "Неверный пункт меню!\n";
        }
    }

    // Очистка памяти
    for (size_t i = 0; i < doctors.get_size(); ++i) delete doctors[i];
    for (size_t i = 0; i < services.get_size(); ++i) delete services[i];

    return 0;
}