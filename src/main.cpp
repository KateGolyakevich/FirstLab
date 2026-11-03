#include <iostream>
#include <string>
#include "../include/Collection.hpp"
#include "../include/Therapist.h"
#include "../include/Surgeon.h"
#include "../include/Orthodontist.h"
#include "../include/TherapeuticService.h"
#include "../include/SurgicalService.h"
#include "../include/OrthodonticService.h"
#include "../include/Patient.h"

int main() {
    std::cout << "===========================\n";
    std::cout << " 1. КАТАЛОГ ВРАЧЕЙ КЛИНИКИ: \n";
    std::cout << "===========================\n";

    // Создаем коллекцию врачей клиники на базе нашего шаблона
    Collection<Doctor*> clinic_doctors;

    Doctor* doc_therapist = new Therapist("Иванов И.И.", 8, 420);
    Doctor* doc_surgeon   = new Surgeon("Петров П.П.", 15, 310);
    Doctor* doc_ortho     = new Orthodontist("Сидорова А.А.", 6, 85);

    clinic_doctors.add(doc_therapist);
    clinic_doctors.add(doc_surgeon);
    clinic_doctors.add(doc_ortho);

    std::cout << "Штат врачей клиники (всего специалистов: " << clinic_doctors.get_size() << "):\n";
    std::cout << clinic_doctors << "\n";

    // Использование шаблонной функции: поиск профильного специалиста по предикату
    int surgeon_idx = find_if(clinic_doctors, [](Doctor* d) {
        return d->get_doctor_type() == "Хирург";
    });

    if (surgeon_idx != -1) {
        std::cout << "Найден дежурный хирург для сложных операций: "
                  << clinic_doctors[surgeon_idx]->get_name() << "\n\n";
    }

    std::cout << "================================\n";
    std::cout << " 2. ПЛАН ЛЕЧЕНИЯ ПАЦИЕНТА: \n";
    std::cout << "================================\n";

    Collection<Service*> patient_treatment_plan;

    Service* s1 = new TherapeuticService("Лечение глубокого кариеса", 2800, 45, "16", false, doc_therapist);
    Service* s2 = new SurgicalService("Сложное удаление зуба мудрости", 4500, 40, "Экстракция ретинированного зуба", doc_surgeon);
    Service* s3 = new TherapeuticService("Повторная чистка и пломбировка каналов", 3200, 50, "16", true, doc_therapist);
    Service* s4 = new OrthodonticService("Установка брекет-системы", 60000, 90, "Брекеты", "Керамика", doc_ortho);

    // 1. Добавление услуг в план лечения пациента (через метод add и оператор +=)
    std::cout << "-> Формирование плана лечения (добавление 3 услуг)...\n";
    patient_treatment_plan.add(s1);
    patient_treatment_plan.add(s2);
    patient_treatment_plan += s3; // Добавление через оператор +=

    std::cout << "Текущий план лечения пациента (назначено услуг: " << patient_treatment_plan.get_size() << "):\n";
    std::cout << patient_treatment_plan << "\n";

    // 2. Добавление новой услуги пациенту в процессе лечения
    std::cout << "-> Пациент обратился с жалобой на прикус. Добавляем ортодонтию:\n";
    patient_treatment_plan.add(s4);
    std::cout << "Обновлённый план лечения (услуг: " << patient_treatment_plan.get_size() << "):\n";
    std::cout << patient_treatment_plan << "\n";

    // 3. Расчет стоимости плана с помощью шаблонной функции calculate_sum
    double total_cost = calculate_sum(patient_treatment_plan, [](Service* s) {
        return s->get_cost();
    });
    std::cout << "Итоговая стоимость всех запланированных процедур: " << total_cost << " руб.\n\n";

    // 4. Поиск услуги в плане лечения по предикату
    int repeated_idx = find_if(patient_treatment_plan, [](Service* s) {
        return s->is_repeated_service();
    });
    if (repeated_idx != -1) {
        std::cout << "В плане найдена повторная процедура на позиции [" << repeated_idx << "]: \""
                  << patient_treatment_plan[repeated_idx]->get_serve() << "\"\n";
    }

    // 5. Удаление услуги из плана лечения (пациент решил перенести удаление зуба)
    std::cout << "\n-> Пациент отказался от операции по удалению зуба. Удаляем услугу из плана...\n";
    bool removed = patient_treatment_plan.remove(s2);
    if (removed) {
        std::cout << "[Успех] Хирургическая операция исключена из плана лечения.\n";
    }

    std::cout << "\nПлан лечения после удаления услуги (осталось услуг: " << patient_treatment_plan.get_size() << "):\n";
    std::cout << patient_treatment_plan << "\n";

    // 6. Шаблонная фильтрация: выделить из оставшихся процедур только терапевтические
    Collection<Service*> therapy_only = filter_collection(patient_treatment_plan, [](Service* s) {
        return s->get_serve_type() == "Терапия";
    });
    std::cout << "Отфильтрованные процедуры терапевтического профиля:\n";
    std::cout << therapy_only << "\n";

    std::cout << "=====================================\n";
    std::cout << " 3. КАРТОТЕКА ПАЦИЕНТОВ КЛИНИКИ:\n";
    std::cout << "=====================================\n";

    // Шаблонный контейнер для хранения объектов пациентов (по значению)
    Collection<Patient> clinic_registry;

    Patient patient_first("Иванов Петр Сергеевич", true);   // С картой клиники
    Patient patient_smirnova("Смирнова Анна Игоревна", false); // Без карты

    // Прикрепляем услуги к карточке пациента
    patient_first += patient_treatment_plan[0];
    patient_first += patient_treatment_plan[1];
    patient_smirnova += s2;

    // Добавляем пациентов в картотеку клиники
    clinic_registry.add(patient_first);
    clinic_registry.add(patient_smirnova);

    std::cout << "Реестр зарегистрированных пациентов клиники (всего: " << clinic_registry.get_size() << "):\n";
    std::cout << clinic_registry << "\n";

    std::cout << "\n-> Очистка каталогов и освобождение динамической памяти...\n";

    delete s1;
    delete s2;
    delete s3;
    delete s4;

    for (size_t i = 0; i < clinic_doctors.get_size(); ++i) {
        delete clinic_doctors[i];
    }
    clinic_doctors.clear();
    patient_treatment_plan.clear();
    clinic_registry.clear();

    std::cout << "Все коллекции очищены. Программа завершена штатно.\n";
    return 0;
}