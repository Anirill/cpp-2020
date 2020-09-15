# Made advanced C++ 2020
### Домашние задания

##### Обзор веток и контента:
В репозитории 3 типа branch-ей:
+ master. Исходно он содержит в себе только README.md. По мере вашего решения задачек вам нужно будет создавать PR именно в этот branch. В asignee указывать github двоих ассистентов.
+ hw_${n}_{task}. Это ветки для маленьких домашних заданий. Всего планируется 10 штук, однако это число может измениться (в меньшую сторону). Малые домашние задания – это часто один файл, в который надо дописать что-то. Маленькие задания проверяют усвоение контента. Тестов для них нет, ассистенты проверяют все ручками.
+ proj_${n}_{task}. Это ветки для больших домашних заданий, то есть проектов. Всего планируется 5 штук, однако это число может измениться (в меньшую сторону). Большие домашние задания предполагаются многомодульными, то есть могут состоять из нескольких файлов, namespace-ов. Структура каждого большого дз следующая: на корневом уровне лежит папка с названием задания внутри которой лежит 4 файла: 2 директории и 2 регулярных файла. Директории – src и test. Директория test содержит тесты. Ее изменение карается смертной казнью =). Регулярные файлы readme.md и run.sh содержат описание задачи и скрипт запуска тестов соответственно (запускаем все под UNIX системой с установленным gcc). 

##### Алгоритм сдачи задания.
1) Сделать fork этого репозитория, если не делали его до этого. Надо добавить дополнительный remote для репозитория с которого вы сделали fork. [Stack Overflow](https://stackoverflow.com/questions/3903817/pull-new-updates-from-original-github-repository-into-forked-github-repository).
2) Забрать все branch-и с исходного репозитория pull-ом с remote-а оригинального репозитория (с которого вы сделали fork).
3) Сделать checkout на соответствующий branch с задачей.
4) Прочитать условие и решить задачу. Убедиться в том, что решение верное и проходит все тесты (если они есть).
5) Создать pull request в master (*Очевидно, в master вашего репозитория*). В asignee указать двоих ассистентов.

##### Разбалловка.
+ Маленькие задачи стоят меньше, чем большие: суммарный вклад маленьких задач в оценку: 30%. Дедлайн на маленькое задание – ровно 1 неделя (7 суток) с 23:59 даты публикации (даты публикации указаны в readme.md соответствующих задачек).
+ Большие задачи – дорогие. Суммарный вклад: 70%.
+ Нельзя обещать что все задачи в каждой категории будут стоить одинаково. В readme.md каждой задачи будет указано конкретное кол-во баллов за каждую задачу!
+ Суммарное кол-во баллов: 100.
+ Перевод баллов в оценку может производиться нелинейно с учетом рейтинга студентов. Алгоритм перевода будет опубликован ближе к концу нашего курса (в прочем, он вас интересовать сильно не должен – лучше смотреть на свою позицию в рейтинге). Позже мы создадим табличку в которой будут опубликованы баллы студентов.

##### Что-то пошло не так или непонятно?
Писать в tg: @konstantinleladze