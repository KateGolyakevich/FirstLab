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
    // 1. Создаем врачей клиники
    Therapist therapist("Иванов И.И.", 12, 340);
    Surgeon surgeon("Петров П.П.", 10, 95);
    Orthodontist orthodontist("Сидорова А.А.", 8, 47);

    std::cout << "--- Врачи клиники ---\n";
    std::cout << therapist << "\n";
    std::cout << surgeon << "\n";
    std::cout << orthodontist << "\n\n";

    // 2. Создаем услуги с привязкой к конкретным врачам
    TherapeuticService therapy("Лечение кариеса", 2500, 60, "36", false, &therapist);
    SurgicalService surgery("Удаление зуба мудрости", 4000, 40, "Удаление", &surgeon);
    OrthodonticService orthodontic("Установка брекетов", 50000, 90, "брекеты", "керамика", &orthodontist);

    std::cout << "--- Услуги клиники (с назначенными врачами) ---\n";
    std::cout << therapy << "\n";
    std::cout << surgery << "\n";
    std::cout << orthodontic << "\n\n";

    // 4. Демонстрация проверки соответствия врача и услуги (can_accept / set_doctor)
    std::cout << "--- Проверка привязки специалистов к услугам ---\n";
    TherapeuticService test_service("Чистка каналов", 3000, 50, "12", true);

    std::cout << "Попытка назначить Хирурга на терапию:\n";
    if (!test_service.set_doctor(&surgeon)) {
        std::cout << "-> Ошибка: Хирург не может вести терапевтический приём!\n";
    }

    std::cout << "Попытка назначить Терапевта на терапию:\n";
    if (test_service.set_doctor(&therapist)) {
        std::cout << "-> Успешно: " << therapist.get_name() << " назначен на услугу.\n";
    }
    std::cout << test_service << "\n\n";

    // 5. Демонстрация работы с Пациентами и расчета скидки
    // Пациент 1: БЕЗ скидочной карты
    Patient patient_first("Иванов И.И.", false);
    patient_first.add_service(new TherapeuticService("Лечение", 2500, 60, "36", true, &therapist));
    patient_first.add_service(new SurgicalService("Удаление", 4000, 40, "удаление", &surgeon));
    patient_first.add_service(new TherapeuticService("Пломбирование", 2500, 30, "11", false, &therapist));

    std::cout << ">>> Пациент БЕЗ карты\n";
    std::cout << patient_first << "\n\n";

    // Пациент 2: С картой клиники (скидка 2% на повторные приемы)
    Patient patient_second("Петров П.П.", true);
    patient_second.add_service(new TherapeuticService("Лечение", 2500, 60, "36", true, &therapist));
    patient_second.add_service(new SurgicalService("Удаление", 4000, 40, "удаление", &surgeon));
    //patient_second.add_service(new TherapeuticService("Пломбирование", 2500, 30, "11", false, &therapist));

    std::cout << ">>> Пациент С картой\n";
    std::cout << patient_second << "\n\n";

    return 0;
}