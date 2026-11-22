#include "../include/ClinicUI.h"
#include "../include/ClinicFileManager.h"
#include <iostream>
#include <fstream>
#include <limits>

ClinicUI::ClinicUI() {
    seed_initial_data();
    ClinicFileManager::log_event(log_file, "Запуск программного комплекса клиники.");
}

ClinicUI::~ClinicUI() {
    cleanup_memory();
    ClinicFileManager::log_event(log_file, "Завершение работы программы.");
}

// 1. Инициализация клиники (включая ортодонтию!) через текстовый файл
void ClinicUI::seed_initial_data() {
    if (ClinicFileManager::load_system_state(state_file, doctors, services, patients)) {
        return;
    }

    std::ofstream initial_file(state_file);
    if (initial_file.is_open()) {
        // 3 специалиста: Терапевт, Хирург, Ортодонт
        initial_file << "[DOCTORS] 3\n";
        initial_file << "Терапевт;Иванов И.И.;10;450\n";
        initial_file << "Хирург;Петров П.П.;15;300\n";
        initial_file << "Ортодонт;Сидорова А.А.;8;110\n";

        // 3 услуги: Терапия, Хирургия, Ортодонтия
        initial_file << "[SERVICES] 3\n";
        initial_file << "Терапия;Лечение кариеса;2500;40;Иванов И.И.;16;0\n";
        initial_file << "Хирургия;Удаление зуба;4000;30;Петров П.П.;Экстракция\n";
        initial_file << "Ортодонтия;Установка брекетов;65000;90;Сидорова А.А.;Брекеты;Керамика\n";

        // Пациент
        initial_file << "[PATIENTS] 1\n";
        initial_file << "Смирнов А.М.;1\n";
        initial_file.close();
    }

    ClinicFileManager::load_system_state(state_file, doctors, services, patients);

    // Сразу прикрепляем первую услугу первому пациенту
    if (patients.get_size() > 0 && services.get_size() > 0) {
        patients[0] += services[0];
    }
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

// Добавление врача через десериализацию (0 issues SonarCloud)
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

    std::string type_str;
    int spec_val = 0;

    if (type == 1) {
        type_str = "Терапевт";
        spec_val = get_int_input("Вылечено зубов: ");
    } else if (type == 2) {
        type_str = "Хирург";
        spec_val = get_int_input("Проведено операций: ");
    } else {
        type_str = "Ортодонт";
        spec_val = get_int_input("Пациентов с брекетами: ");
    }

    std::string line = type_str + ";" + name + ";" + std::to_string(exp) + ";" + std::to_string(spec_val);

    std::ofstream temp("temp_doc.tmp");
    if (temp.is_open()) {
        temp << "[DOCTORS] 1\n" << line << "\n";
        temp.close();

        Collection<Doctor*> temp_docs;
        Collection<Service*> temp_srvs;
        Collection<Patient> temp_pts;

        if (ClinicFileManager::load_system_state("temp_doc.tmp", temp_docs, temp_srvs, temp_pts)) {
            if (temp_docs.get_size() > 0) {
                doctors.add(temp_docs[0]);
                std::cout << "[Успех] Врач успешно добавлен в систему!\n";
                ClinicFileManager::log_event(log_file, "Добавлен новый врач: " + name);
            }
        }
        std::remove("temp_doc.tmp");
    }
}

// Добавление новой услуги (включая Ортодонтию)
void ClinicUI::manual_add_service() {
    if (doctors.get_size() == 0) {
        std::cout << "[Ошибка] Сначала добавьте хотя бы одного врача!\n";
        return;
    }

    std::cout << "\n--- Добавление услуги в прейскурант ---\n";
    std::cout << "1. Терапия\n2. Хирургия\n3. Ортодонтия\nВыбор профиля: ";
    int type = get_int_input("");
    if (type < 1 || type > 3) {
        std::cout << "Неверный профиль!\n";
        return;
    }

    std::cout << "Введите название услуги: ";
    std::string title;
    std::getline(std::cin, title);
    int cost = get_int_input("Базовая стоимость (руб): ");
    int duration = get_int_input("Длительность (мин): ");

    std::cout << "\nВыберите врача для услуги:\n";
    for (size_t i = 0; i < doctors.get_size(); ++i) {
        std::cout << (i + 1) << ". " << doctors[i]->get_name() << " (" << doctors[i]->get_doctor_type() << ")\n";
    }
    int doc_idx = get_int_input("Номер врача: ") - 1;
    if (doc_idx < 0 || doc_idx >= static_cast<int>(doctors.get_size())) {
        std::cout << "Неверный номер врача!\n";
        return;
    }
    std::string doc_name = doctors[doc_idx]->get_name();

    std::string line;
    if (type == 1) {
        std::cout << "Номер зуба: ";
        std::string tooth;
        std::getline(std::cin, tooth);
        int rep = get_int_input("Повторный приём? (1 - Да, 0 - Нет): ");
        line = "Терапия;" + title + ";" + std::to_string(cost) + ";" + std::to_string(duration) + ";" + doc_name + ";" + tooth + ";" + (rep == 1 ? "1" : "0");
    } else if (type == 2) {
        std::cout << "Тип операции (напр. Экстракция, Резекция): ";
        std::string op;
        std::getline(std::cin, op);
        line = "Хирургия;" + title + ";" + std::to_string(cost) + ";" + std::to_string(duration) + ";" + doc_name + ";" + op;
    } else {
        std::cout << "Тип аппарата (напр. Брекеты, Элайнеры): ";
        std::string corr;
        std::getline(std::cin, corr);
        std::cout << "Материал (напр. Керамика, Металл): ";
        std::string mat;
        std::getline(std::cin, mat);
        line = "Ортодонтия;" + title + ";" + std::to_string(cost) + ";" + std::to_string(duration) + ";" + doc_name + ";" + corr + ";" + mat;
    }

    std::ofstream temp("temp_srv.tmp");
    if (temp.is_open()) {
        // Записываем список врачей и одну услугу
        temp << "[DOCTORS] " << doctors.get_size() << "\n";
        for (size_t i = 0; i < doctors.get_size(); ++i) {
            temp << doctors[i]->get_doctor_type() << ";" << doctors[i]->get_name() << ";"
                 << doctors[i]->get_experience() << ";0\n";
        }
        temp << "[SERVICES] 1\n" << line << "\n";
        temp.close();

        Collection<Doctor*> temp_docs;
        Collection<Service*> temp_srvs;
        Collection<Patient> temp_pts;

        if (ClinicFileManager::load_system_state("temp_srv.tmp", temp_docs, temp_srvs, temp_pts)) {
            if (temp_srvs.get_size() > 0) {
                // Привязываем реального врача из нашей коллекции
                temp_srvs[0]->set_doctor(doctors[doc_idx]);
                services.add(temp_srvs[0]);
                std::cout << "[Успех] Услуга добавлена в прейскурант!\n";
                ClinicFileManager::log_event(log_file, "Добавлена услуга: " + title);
            }
        }
        for (size_t i = 0; i < temp_docs.get_size(); ++i) delete temp_docs[i];
        std::remove("temp_srv.tmp");
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

// Назначение услуги пациенту
void ClinicUI::assign_service_to_patient() {
    if (patients.get_size() == 0 || services.get_size() == 0) {
        std::cout << "[Ошибка] В системе должны быть зарегистрированы хотя бы один пациент и одна услуга!\n";
        return;
    }

    std::cout << "\n--- Назначение услуги пациенту ---\n";
    std::cout << "Выберите пациента:\n";
    for (size_t i = 0; i < patients.get_size(); ++i) {
        std::cout << (i + 1) << ". " << patients[i].get_name() << "\n";
    }
    int p_idx = get_int_input("Номер пациента: ") - 1;
    if (p_idx < 0 || p_idx >= static_cast<int>(patients.get_size())) {
        std::cout << "Неверный номер пациента!\n";
        return;
    }

    std::cout << "\nВыберите услугу из каталога:\n";
    for (size_t i = 0; i < services.get_size(); ++i) {
        std::cout << (i + 1) << ". " << services[i]->get_serve()
                  << " (" << services[i]->get_serve_type() << ", " << services[i]->get_cost() << " руб.)\n";
    }
    int s_idx = get_int_input("Номер услуги: ") - 1;
    if (s_idx < 0 || s_idx >= static_cast<int>(services.get_size())) {
        std::cout << "Неверный номер услуги!\n";
        return;
    }

    // Прикрепляем услугу через перегруженный оператор +=
    patients[p_idx] += services[s_idx];
    std::cout << "[Успех] Услуга \"" << services[s_idx]->get_serve()
              << "\" успешно назначена пациенту " << patients[p_idx].get_name() << "!\n";

    ClinicFileManager::log_event(log_file, "Пациенту " + patients[p_idx].get_name() +
                                           " назначена процедура: " + services[s_idx]->get_serve());
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
        std::cout << "2. Добавить врача в штат\n";
        std::cout << "3. Добавить услугу в прейскурант (Терапия/Хирургия/Ортодонтия)\n";
        std::cout << "4. Зарегистрировать пациента\n";
        std::cout << "5. Назначить услугу пациенту\n";
        std::cout << "6. Сохранить состояние системы в файл\n";
        std::cout << "7. Загрузить состояние системы из файла\n";
        std::cout << "8. Сформировать текстовый отчёт\n";
        std::cout << "0. Выход\n";

        int choice = get_int_input("Выберите действие: ");

        switch (choice) {
            case 1: show_system_state(); break;
            case 2: manual_add_doctor(); break;
            case 3: manual_add_service(); break;
            case 4: manual_add_patient(); break;
            case 5: assign_service_to_patient(); break;
            case 6: save_state(); break;
            case 7: load_state(); break;
            case 8: generate_report(); break;
            case 0: return;
            default: std::cout << "Неверный пункт меню!\n"; break;
        }
    }
}