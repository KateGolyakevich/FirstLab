#include "../include/ClinicUI.h"
#include "../include/ClinicFileManager.h"
#include <iostream>
#include <fstream>
#include <limits>

ClinicUI::ClinicUI() {
    seed_initial_data();
    ClinicFileManager::log("Запуск программного комплекса стоматологической клиники.");
}

ClinicUI::~ClinicUI() {
    cleanup_memory();
    ClinicFileManager::log("Штатное завершение работы программы.");
}

void ClinicUI::seed_initial_data() {
    std::ifstream check(state_file);
    bool exists = check.is_open();
    check.close();

    if (!exists) {
        std::ofstream init_file(state_file);
        if (init_file.is_open()) {
            init_file << "[DOCTORS] 3\n"
                      << "Терапевт;Иванов И.И.;10;450\n"
                      << "Хирург;Петров П.П.;15;300\n"
                      << "Ортодонт;Сидорова А.А.;8;110\n"
                      << "[SERVICES] 3\n"
                      << "Терапия;Лечение кариеса;2500;40;Иванов И.И.;16;0\n"
                      << "Хирургия;Удаление зуба;4000;30;Петров П.П.;Экстракция\n"
                      << "Ортодонтия;Установка брекетов;65000;90;Сидорова А.А.;Брекеты;Керамика\n"
                      << "[PATIENTS] 1\n"
                      << "Смирнов А.М.;1\n";
            init_file.close();
        }
    }

    ClinicFileManager::load_system_state(state_file, doctors, services, patients);

    // Сразу прикрепляем процедуру первому пациенту
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
        std::cout << "[Ошибка] Введите целое число!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void ClinicUI::manual_add_doctor() {
    std::cout << "\n--- Добавление врача в штат клиники ---\n";
    std::cout << "1. Терапевт\n2. Хирург\n3. Ортодонт\nВыбор: ";
    int type = get_int_input("");
    if (type < 1 || type > 3) {
        std::cout << "Неверный выбор!\n";
        return;
    }

    std::cout << "Введите ФИО врача: ";
    std::string name;
    std::getline(std::cin, name);
    int exp = get_int_input("Стаж работы (лет): ");

    std::string type_s;
    int spec_val = 0;

    if (type == 1) {
        type_s = "Терапевт";
        spec_val = get_int_input("Количество вылеченных зубов: ");
    } else if (type == 2) {
        type_s = "Хирург";
        spec_val = get_int_input("Количество проведенных операций: ");
    } else {
        type_s = "Ортодонт";
        spec_val = get_int_input("Пациентов с брекет-системами: ");
    }

    std::string line = type_s + ";" + name + ";" + std::to_string(exp) + ";" + std::to_string(spec_val);

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
                std::cout << "[Успех] Врач добавлен в штат!\n";
                ClinicFileManager::log("Добавлен новый врач в штат: " + name);
            }
        }
        std::remove("temp_doc.tmp");
    }
}

void ClinicUI::manual_add_service() {
    if (doctors.get_size() == 0) {
        std::cout << "[Ошибка] В клинике нет врачей для оказания услуг!\n";
        return;
    }

    std::cout << "\n--- Добавление услуги в прейскурант ---\n";
    std::cout << "1. Терапия\n2. Хирургия\n3. Ортодонтия\nВыбор профиля: ";
    int type = get_int_input("");
    if (type < 1 || type > 3) {
        std::cout << "Неверный профиль!\n";
        return;
    }

    std::cout << "Введите название процедуры: ";
    std::string title;
    std::getline(std::cin, title);
    int cost = get_int_input("Базовая стоимость (руб): ");
    int duration = get_int_input("Длительность приема (мин): ");

    std::cout << "\nВыберите лечащего врача:\n";
    for (size_t i = 0; i < doctors.get_size(); ++i) {
        std::cout << (i + 1) << ". " << doctors[i]->get_name()
                  << " (" << doctors[i]->get_doctor_type() << ")\n";
    }
    int doc_idx = get_int_input("Номер специалиста: ") - 1;
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
        std::cout << "Тип операции (Экстракция/Резекция): ";
        std::string op;
        std::getline(std::cin, op);
        line = "Хирургия;" + title + ";" + std::to_string(cost) + ";" + std::to_string(duration) + ";" + doc_name + ";" + op;
    } else {
        std::cout << "Ортодонтический аппарат (Брекеты/Элайнеры): ";
        std::string corr;
        std::getline(std::cin, corr);
        std::cout << "Материал конструкции (Керамика/Металл/Сапфир): ";
        std::string mat;
        std::getline(std::cin, mat);
        line = "Ортодонтия;" + title + ";" + std::to_string(cost) + ";" + std::to_string(duration) + ";" + doc_name + ";" + corr + ";" + mat;
    }

    std::ofstream temp("temp_srv.tmp");
    if (temp.is_open()) {
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
                temp_srvs[0]->set_doctor(doctors[doc_idx]);
                services.add(temp_srvs[0]);
                std::cout << "[Успех] Услуга внесена в прейскурант!\n";
                ClinicFileManager::log("Добавлена новая медицинская услуга: " + title);
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
    int card = get_int_input("Наличие карты клиники (1 - Да, 0 - Нет): ");

    patients.add(Patient(name, card == 1));
    std::cout << "[Успех] Пациент успешно зарегистрирован в картотеке!\n";
    ClinicFileManager::log("Зарегистрирован новый пациент: " + name);
}

// Назначение услуги пациенту
void ClinicUI::assign_service_to_patient() {
    if (patients.get_size() == 0 || services.get_size() == 0) {
        std::cout << "[Ошибка] В системе нет доступных пациентов или услуг!\n";
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

    std::cout << "\nВыберите услугу:\n";
    for (size_t i = 0; i < services.get_size(); ++i) {
        std::cout << (i + 1) << ". " << services[i]->get_serve()
                  << " (" << services[i]->get_serve_type() << ", " << services[i]->get_cost() << " руб.)\n";
    }
    int s_idx = get_int_input("Номер услуги: ") - 1;
    if (s_idx < 0 || s_idx >= static_cast<int>(services.get_size())) {
        std::cout << "Неверный номер услуги!\n";
        return;
    }

    patients[p_idx] += services[s_idx];
    std::cout << "[Успех] Процедура \"" << services[s_idx]->get_serve()
              << "\" успешно добавлена в карту пациента " << patients[p_idx].get_name() << "!\n";

    ClinicFileManager::log("Пациенту " + patients[p_idx].get_name() +
                           " назначена процедура: " + services[s_idx]->get_serve());
}

void ClinicUI::show_system_state() const {
    std::cout << "\n================ ТЕКУЩЕЕ СОСТОЯНИЕ КЛИНИКИ ================\n";
    std::cout << "--- ШТАТ ВРАЧЕЙ ---\n" << doctors;
    std::cout << "\n--- ПРЕЙСКУРАНТ УСЛУГ ---\n" << services;
    std::cout << "\n--- КАРТОТЕКА ПАЦИЕНТОВ ---\n" << patients;
}

void ClinicUI::save_state() {
    if (ClinicFileManager::save_system_state(state_file, doctors, services, patients)) {
        std::cout << "[Успех] Состояние системы сохранено в файл: " << state_file << "\n";
    } else {
        std::cout << "[Ошибка] Не удалось сохранить файл!\n";
    }
}

void ClinicUI::load_state() {
    cleanup_memory();
    if (ClinicFileManager::load_system_state(state_file, doctors, services, patients)) {
        std::cout << "[Успех] Данные успешно восстановлены из файла: " << state_file << "\n";
    } else {
        std::cout << "[Ошибка] Не удалось прочитать файл базы данных!\n";
    }
}

void ClinicUI::generate_report() {
    if (ClinicFileManager::generate_text_report(report_file, doctors, services, patients)) {
        std::cout << "[Успех] Текстовый аналитический отчёт сформирован: " << report_file << "\n";
    } else {
        std::cout << "[Ошибка] Сбой формирования отчёта!\n";
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
        std::cout << "6. Сохранить состояние системы в файл (" << state_file << ")\n";
        std::cout << "7. Загрузить состояние системы из файла (" << state_file << ")\n";
        std::cout << "8. Сформировать текстовый отчёт (" << report_file << ")\n";
        std::cout << "0. Выход из программы\n";

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