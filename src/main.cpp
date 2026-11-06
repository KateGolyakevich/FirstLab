#include <iostream>
#include "../include/Collection.hpp"
#include "../include/Therapist.h"
#include "../include/Surgeon.h"
#include "../include/Orthodontist.h"
#include "../include/TherapeuticService.h"
#include "../include/SurgicalService.h"
#include "../include/OrthodonticService.h"
#include "../include/Patient.h"

int main() {
    std::cout << "=== 1. ШТАТ ВРАЧЕЙ (Collection<Doctor*>) ===\n";
    Collection<Doctor*> staff;
    staff.add(new Therapist("Иванов И.И.", 10, 450));
    staff.add(new Surgeon("Петров П.П.", 15, 300));
    staff.add(new Orthodontist("Сидорова А.А.", 7, 90));
    std::cout << staff << "\n";

    int surgeon_idx = find_if(staff, [](Doctor* d) { return d->get_doctor_type() == "Хирург"; });
    if (surgeon_idx != -1) {
        std::cout << "Найден профильный хирург: " << staff[surgeon_idx]->get_name() << "\n\n";
    }

    std::cout << "=== 2. КАРТОЧКА ПАЦИЕНТА И УСЛУГИ (Collection<Service*>) ===\n";
    Patient patient("Смирнов К.А.", true); // Пациент с дисконтной картой

    Service* s1 = new TherapeuticService("Лечение кариеса", 2500, 40, "15", false, staff[0]);
    Service* s2 = new SurgicalService("Удаление зуба", 4000, 30, "Экстракция", staff[1]);
    Service* s3 = new TherapeuticService("Повторная чистка", 2000, 30, "15", true, staff[0]);

    patient += s1;
    patient += s2;
    patient += s3;
    std::cout << patient << "\n";

    std::cout << "-> Удаление услуги из плана лечения:\n";
    patient -= s2;
    std::cout << patient << "\n";

    std::cout << "=== 3. КАРТОТЕКА КЛИНИКИ (Collection<Patient>) ===\n";
    Collection<Patient> registry;
    registry.add(patient);
    registry.add(Patient("Ковалева Е.С.", false));
    std::cout << registry << "\n";

    delete s1;
    delete s2;
    delete s3;
    for (size_t i = 0; i < staff.get_size(); ++i) delete staff[i];

    std::cout << "Работа программы завершена успешно.\n";
    return 0;
}