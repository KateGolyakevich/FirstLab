#include "../include/ClinicUI.h"
#include "../include/Therapist.h"
#include "../include/Surgeon.h"
#include "../include/Orthodontist.h"
#include "../include/TherapeuticService.h"
#include "../include/SurgicalService.h"
#include "../include/OrthodonticService.h"
#include "../include/ClinicFileManager.h"
#include <iostream>
#include <limits>

ClinicUI::ClinicUI() {
    seed_initial_data();
    ClinicFileManager::log_event(log_file, "Запуск программного комплекса клиники.");
}

ClinicUI::~ClinicUI() {
    cleanup_memory();
    ClinicFileManager::log_event(log_file, "Завершение работы программы.");
}

void ClinicUI::seed_initial_data() {
    Doctor* d1 = new Therapist("Иванов И.И.", 10, 450);
    Doctor* d2 = new Surgeon("Петров П.П.", 15, 300);
    doctors.add(d1);
    doctors.add(d2);

    services.add(new TherapeuticService("Лечение кариеса", 2500, 40, "16", false, d1));
    services.add(new SurgicalService("Удаление зуба", 4000, 30, "Экстракция", d2));

    patients.add(Patient("Смирнов А.М.", true));
}

void ClinicUI::cleanup_memory() {
    for (size_t i = 0; i < doctors.get_size(); ++i) {
        delete doctors[i];
    }
    doctors.clear();

    for (size_t i = 0; i < services.get_size(); ++i) {
        delete services[i];
    }
    services.clear();
}

int ClinicUI::get_int_input(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "[Ошибка] Введите корректное число!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void ClinicUI::manual_add_doctor() {
    std::cout << "\n--- Добавление врача в штат ---\n";
    std::cout << "1. Терапевт\n2. Хирург\n3. Ортодонт\nВыбор: ";
    int type = get_int_input("");

    std::cout << "Введите ФИО врача: ";
    std::string name;
    std::getline(std::cin, name);
    int exp = get_int_input("Стаж работы (лет): ");

    Doctor* new_doctor = nullptr;
    try {
        if (type == 1) {
            int teeth = get_int_input("Вылечено зубов: ");
            new_doctor = new Therapist(name, exp, teeth);
        } else if (type == 2) {
            int ops = get_int_input("Проведено операций: ");
            new_doctor = new Surgeon(name, exp, ops);
        } else if (type == 3) {
            int braces = get_int_input("Пациентов с брекетами: ");
            new_doctor = new Orthodontist(name, exp, braces);
        } else {
            std::cout << "Неверный тип специальности!\n";
            return;
        }

        doctors.add(new_doctor);
        std::cout << "[Успех] Врач успешно добавлен в систему!\n";
        ClinicFileManager::log_event(log_file, "Добавлен новый врач: " + name);

    } catch (...) {
        delete new_doctor; // Защита от утечки при сбое
        std::cout << "[Ошибка] Не удалось добавить врача.\n";
    }
}

void ClinicUI::manual_add_patient() {
    std::cout << "\n--- Регистрация нового пациента ---\n";
    std::cout << "Введите ФИО пациента: ";
    std::string name;
    std::getline(std::cin, name);
    int card = get_int_input("Наличие дисконтной карты (1 - Да, 0 - Нет): ");

    patients.add(Patient(name, card == 1));
    std::cout << "[Успех] Карточка пациента зарегистрирована!\n";
    ClinicFileManager::log_event(log_file, "Зарегистрирован пациент: " + name);
}

void ClinicUI::show_system_state() const {
    std::cout << "\n================ ТЕКУЩЕЕ СОСТОЯНИЕ СИСТЕМЫ ================\n";
    std::cout << "--- ШТАТ ВРАЧЕЙ ---\n" << doctors;
    std::cout << "\n--- КАТАЛОГ УСЛУГ ---\n" << services;
    std::cout << "\n--- КАРТОТЕКА ПАЦИЕНТОВ ---\n" << patients;
}

void ClinicUI::save_state() {
    if (ClinicFileManager::save_system_state(state_file, doctors, services, patients)) {
        std::cout << "[Успех] Данные сохранены в файл: " << state_file << "\n";
    } else {
        std::cout << "[Ошибка] Сбой сохранения файла!\n";
    }
}

void ClinicUI::load_state() {
    cleanup_memory();
    if (ClinicFileManager::load_system_state(state_file, doctors, services, patients)) {
        std::cout << "[Успех] Состояние успешно восстановлено из файла: " << state_file << "\n";
    } else {
        std::cout << "[Ошибка] Не удалось прочитать файл данных!\n";
    }
}

void ClinicUI::generate_report() {
    if (ClinicFileManager::generate_text_report(report_file, doctors, services, patients)) {
        std::cout << "[Успех] Сформирован текстовый аналитический отчёт: " << report_file << "\n";
    } else {
        std::cout << "[Ошибка] Не удалось сформировать отчёт!\n";
    }
}

void ClinicUI::run() {
    while (true) {
        std::cout << "\n====================================================\n";
        std::cout << "     СТОМАТОЛОГИЧЕСКАЯ КЛИНИКА (ЛАБОРАТОРНАЯ №7)    \n";
        std::cout << "====================================================\n";
        std::cout << "1. Просмотр текущего состояния системы\n";
        std::cout << "2. Добавить врача (ручной ввод)\n";
        std::cout << "3. Зарегистрировать пациента (ручной ввод)\n";
        std::cout << "4. Сохранить состояние системы в файл\n";
        std::cout << "5. Загрузить состояние системы из файла\n";
        std::cout << "6. Сформировать текстовый отчёт\n";
        std::cout << "0. Выход\n";

        int choice = get_int_input("Выберите действие: ");

        switch (choice) {
            case 1: show_system_state(); break;
            case 2: manual_add_doctor(); break;
            case 3: manual_add_patient(); break;
            case 4: save_state(); break;
            case 5: load_state(); break;
            case 6: generate_report(); break;
            case 0: return;
            default: std::cout << "Неверный пункт меню!\n"; break;
        }
    }
}
