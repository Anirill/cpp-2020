# Задача 3: simple compose

### Условие:
Необходимо написать функцию, которая считает композицию функций. На вход она получает 2 аргумента - количество функций и сами функции в массиве. Функцию compose можно сделать рекурсивной. Если n = 0, то возвращать нужно идемпотентную функцию, если n = 1, то можно вернуть саму функцию. В файле main.cpp написаны примитивные тестики. Также в main.cpp можно посмотреть на то, как инстанцировать операции (op1), и как создавать creater-ы этих самых операций (op2). Если кто знаком с библиотекой redux, то можно провести аналогию с action-ами и action creater-ами. PS: запрещено создавать дополнительные вспомогательные функции вне кода функции compose, мотивировка: compose – библиотечная функция, а чем меньше зависимостей у библиотечных компонент, тем проще ее расширять и читать.

##### Стоимость:
Задача стоит 3 балла.

##### Срок сдачи:
Решения сданные позже 23:59:59 6 Октября 2020 года не принимаются.