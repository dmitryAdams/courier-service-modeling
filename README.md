# courier-service-modeling
Прилодения для моделирования системы распределения заказов между курьерами

Цель моделирования – сбор информации о работе курьеров для последующей оптимизации курьерской службы

Тестируются 3 способа распределния заказов:
1) Нахождение курьера, который сможет приняться за этот заказ после выполнения всех уже имеющихся за минимальное время
2) Распределение заказа случайному курьеру
3) Если есть свободные курьеры, то отдаём заказ самому ближайшему свободному, в противном случае будем оставлять пписьмо в филиале на потом, пока у какого-нибудь курьера не появится возможность забрать его 

Классы системы:
AbstractEvent - базовый интерфейс для классов событий
OfficeVisitEvent - класс событий, отвечающий за вход или выход из филиала компании
LetterMovingEvent - класс, отвечающий за отправку и получение писем

Branch - класс филиала компании
Courier - класс одного отдельного курьера
Service - класс, управляющий курьерами, разделяющий задачи между ними

Generator - класс для генерации запросов
Time - вспомогательный класс для перевода времени в удобный формат

Использованые инструменты:
Основной и единственный язык программирования - C++
Библиотека для работы с графическим интерфейсом - Qt

Файловая система проекта:
Под каждый класс выделяется отдельная директория, в который хранится заголовочный файл и cpp файл с реализацией
Все директории, отвечающие за события, в одной директории Events
Также весь код, реализующий графический интерфейс, находится в отдельной папке Events
Отдельная директория sprites, хранящая изображения для спрайтов