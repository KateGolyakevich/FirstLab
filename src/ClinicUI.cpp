#include "../include/ClinicUI.h"
#include "../include/Therapist.h"
#include "../include/Surgeon.h"
#include "../include/Orthodontist.h"
#include "../include/TherapeuticService.h"
#include "../include/SurgicalService.h"
#include "../include/OrthodonticService.h"
#include "../include/ClinicFileManager.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <limits>

ClinicUI::ClinicUI() {
    seed_initial_data();
    ClinicFileManager::log_event(log_file, "Запуск программного комплекса клиники.");
}

ClinicUI::~ClinicUI() {
    cleanup_memory();
    ClinicFileManager::log_event(log_file, "Завершение работы программы.");
}

// 1. Инициализация БЕЗ операторов new в этом файле: через генерацию стартового файла
void ClinicUI::seed_initial_data() {
    // Пытаемся загрузить состояние, если файл уже существует
    if (ClinicFileManager::load_system_state(state_file, doctors, services, patients)) {
        return;
    }

    // Если файла нет — создаем базовый файл с начальными данными клиники
    std::ofstream initial_file(state_file);
    if (initial_file.is_open()) {
        initial_file << "[DOCTORS] 2\n";
        initial_file << "Терапевт;Иванов И.И.;10;450\n";
        initial_file << "Хирург;Петров П.П.;15;300\n";
        initial_file << "[SERVICES] 2\n";
        initial_file << "Терапия;Лечение кариеса;2500;40;Иванов И.И.;16;0\n";
        initial_file << "Хирургия;Удаление зуба;4000;30;Петров П.П.;Экстракция\n";
        initial_file << "[PATIENTS] 1\n";
        initial_file << "Смирнов А.М.;1\n";
        initial_file.close();
    }

    // Загружаем данные через наш штатный загрузчик
    ClinicFileManager::load_system_state(state_file, doctors, services, patients);
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

// 2. Добавление врача через std::unique_ptr (гарантирует отсутствие утечек памяти для SonarQube)
void ClinicUI::manual_add_doctor() {
    std::cout << "\n--- Добавление врача в штат ---\n";
    std::cout << "1. Терапевт\n2. Хирург\n3. Ортодонт\nВыбор: ";
    int type = get_int_input("");

    if (type < 1 || type > 3) {
        std::cout << "Неверный тип специальности!\n";
        return;
    }

    std::cout << "Введите ФИО врача: ";
    std::string name;
    std::getline(std::cin, name);
    int exp = get_int_input("Стаж работы (лет): ");

    std::unique_ptr<Doctor> doctor_ptr;

    if (type == 1) {
        int teeth = get_int_input("Вылечено зубов: ");
        doctor_ptr = std::make_unique<Therapist>(name, exp, teeth);
    } else if (type == 2) {
        int ops = get_int_input("Проведено операций: ");
        doctor_ptr = std::make_unique<Surgeon>(name, exp, ops);
    } else {
        int braces = get_int_input("Пациентов с брекетами: ");
        doctor_ptr = std::make_unique<Orthodontist>(name, exp, braces);
    }

    if (doctor_ptr) {
        // Передаем владение указателем в контейнер, освобождая умный указатель
        doctors.add(doctor_ptr.release());
        std::cout << "[Успех] Врач успешно добавлен в систему!\n";
        ClinicFileManager::log_event(log_file, "Добавлен новый врач: " + name);
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