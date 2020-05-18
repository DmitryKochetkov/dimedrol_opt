# dimedrol_opt

В этот личный репозиторий я складываю свои эксперименты с методами оптимизации на C++.

# Реализовано

## Метод роя частиц / Swarm particle Optimization

Сделан на уровне университетской лабы. Хотелось бы заставить его нормально оптимизировать заданный набор многомерных функций, возможно придется хранить отдельно параметры velocity для каждой из них.

## Алгоритм пчелиной колонии / Artificial bee colony algorithm

Пока без фазы пчел-разведчиков, но работает, черт возьми. А фаза разведчиков наоборот делает его не работоспособным, я ее пока закомментировал. Возможно причина в том, что там банально переменная выходит за границы. Потому что так то на этой точке значение действительно оптимальнее ожидаемого.

# Планируется

- Линейное программирование
- Выпуклое программирование
- MILP
