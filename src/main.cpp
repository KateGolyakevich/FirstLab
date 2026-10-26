#include <iostream>
#include <vector>
#include "../include/Therapist.h"
#include "../include/Surgeon.h"
#include "../include/Orthodontist.h"
#include "../include/TherapeuticService.h"
#include "../include/SurgicalService.h"
#include "../include/OrthodonticService.h"
#include "../include/Patient.h"

int main() {
    std::cout << "===================\n";
    std::cout << " ВРАЧИ (DOCTOR)\n";
    std::cout << "===================\n";

    // 1. Полиморфная коллекция указателей на абстрактный базовый класс Doctor
    std::vector<Doctor*> clinic_staff;
    clinic_staff.push_back(new Therapist("Иванов И.И.", 8, 450));
    clinic_staff.push_back(new Surgeon("Петров П.П.", 15, 320));
    clinic_staff.push_back(new Orthodontist("Сидорова А.А.", 6, 85));

    // Полиморфный обход врачей: каждый объект вызывает свои версии методов
    for (const auto* doc : clinic_staff) {
        std::cout << *doc << "\n";
        doc->perform_procedure(); // Специфическое действие
        std::cout << "--------------------------------------------------------\n";
    }

    std::cout << "\n===============================\n";
    std::cout << " УСЛУГИ (SERVICE) И ПАЦИЕНТЫ\n";
    std::cout << "=================================\n";

    // Создаем пациентов
    Patient patient1("Кузнецов В.С.", true);  // С дисконтной картой
    Patient patient2("Морозов Д.А.", false); // Без карты

    // 2. Создание полиморфных объектов услуг и проверка динамического контракта can_accept()
    Service* s1 = new TherapeuticService("Лечение пульпита", 3000, 60, "16", true, clinic_staff[0]);
    Service* s2 = new SurgicalService("Сложное удаление зуба мудрости", 4500, 45, "Экстракция ретинированного зуба", clinic_staff[1]);
    Service* s3 = new OrthodonticService("Установка элайнеров", 75000, 90, "Элайнеры", "Полимер", clinic_staff[2]);

    // Проверка попытки ошибочного назначения (хирург на терапию)
    std::cout << "\nПроверка назначения несовместимого специалиста:\n";
    s1->set_doctor(clinic_staff[1]); // Должна возникнуть ошибка

    // Добавляем услуги через перегруженный оператор +=
    patient1 += s1;
    patient1 += s2;
    patient2 += s3;

    // Выводим информацию о пациентах (полиморфный вывод всех вложенных услуг)
    std::cout << "\nИнформация по пациентам:\n";
    std::cout << patient1 << "\n";
    std::cout << patient2 << "\n";

    // Вызов полиморфного действия для всех услуг пациента
    patient1.execute_all_services();
    patient2.execute_all_services();

    // 3. Корректное освобождение памяти (деструктор Patient очищает свои услуги)
    // Очищаем коллекцию врачей
    std::cout << "\nОсвобождение памяти врачей через виртуальный деструктор...\n";
    for (auto* doc : clinic_staff) {
        delete doc; // Вызывается виртуальный деструктор ~Doctor()
    }
    clinic_staff.clear();

    std::cout << "\nПрограмма успешно завершена.\n";
    return 0;
}