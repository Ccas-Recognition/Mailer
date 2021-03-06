В данном описании планируется раскрыть примерные особенности почтового агента, сопутствующих интструментов (утилит) и его настройку.

Для начала опишу *возможности* этого агента.

---

# Возможности почтового агента  

1.  Отправка писем по одному неограниченному количеству адресатов. Любые вложения поддерживаются. Главное, чтобы время ожидания сервиса не превышало некоторый порог (это неважно, обычно, это сразу заметно в любой программе почтовой).  

2.  GUI пока не предоставляется, так как всё писал исключительно для себя. В будущем перепишу с нормальным удобным user-friendly интерфейсом на bootstrap. Пока будет так (думаю, разберётесь).  

3.  Парсер входного потока: `[cpp]`
```shell
  ./cpp-parser/main.cpp
```

Позволяет обрубать пробелы, удалять концы строк, формировать свой вывод в виде массива строк, то есть ['a@mail.ru', 'b@mail.ru', ... , 'z@mail.ru', ... ]. Легко настраиваем, под капотом [boost/algorithm/string.hpp](http://www.boost.org/doc/libs/1_46_1/doc/html/string_algo.html).  

4\. Автоматическое копирование в буфер каждого следующего нового адреса (удобно для ручного копирования адресов). `[node.js][mac os x]`
```shell
  node ./cpp-parser/runner.js runner.js <io_file>
```

Принимает на вход распарсенный файл вида:

```txt
a@mail.ru  
b@mail.ru  
....  
z@mail.ru  
```

Создаёт/использует файл `<io_file>_stat`, содержащий строку последнего почтового адреса, скопированного в буфер. 

##Workflow этой программы:  

4.1.    Проверка существования файла `<io_file>` 
 
4.2.    Проверка существования файла статистики `<io_file>_stat`. В случае если файл существует, копируется почтовый адрес находящийся в той строке, чей номер записан в `<io_file>_sat`, индекс строки после этого увеличивается и записывается в файл стастики. Если файла не существуется, берётся первая строка и файл стастики создаётся.  

4.3.    По окончании операций выводится сообщение на консоль и в уведомление системы (`terminal-notifier`) о том, который адрес был скопирован.  

## Зависимости:  

> node.js v.0.10.x   

```shell 
  cd cpp-parser/
  npm install path
  npm install copy-paste 
```

> terminal-notifier  

```shell
  ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
  brew update && brew upgrade
  brew install terminal-notifier
```

## TODO  

a. Поддержка нескольких систем (linux, windows).  
b. Проверка на то, что файл уже закончился и что счётчик не нужно обновлять.  
c. Проверка на правильность адресов (RegExp).  

---

# Описание настроек почтового клиента

1.  Настройки аккаунта, с которого будут отправляться сообщения находятся в файле:
```shell
  ./config/environments/development.rb
```
в секции `config.action_mailer.smtp_settings`.

![Пример настроек аккаунта](http://dl2.joxi.net/drive/0003/2969/248729/141230/671ddef261.jpg)  


2\.  Список рассылки устанавливается в файле в переменной `@@arr` в виде ['a@mail.ru', 'b@mail.ru', ... ]
```shell
  ./app/controllers/sendmail_controller.rb
```

![Пример задания списка](http://dl1.joxi.net/drive/0003/2969/248729/141230/c71d0ce621.jpg)  

3\.  Редактирование текста письма и вложений.

![Пояснительная структура папок и нужных файлов](http://dl2.joxi.net/drive/0003/2969/248729/141230/c33d11b97b.jpg)  


```shell
  ./app/mailers/user_mailer.rb
```
содержит следующее:

3.1.    Поле отправителя `default from: "\"DCC RAS\" <imta5.ccas@gmail.com>"` приведёт к тому, что в качестве отправителя будет написано `DCC RAS`, а адрес, с которого было отправлено, будет заменён на `imta.ccas@gmail.com` (в случае наличия прав и разрешении вашего (почтового сервиса на использование псевдонимов)[https://support.google.com/a/answer/33327?hl=ru]).
  
3.2.    Функция `imta_first_call` принимает автоматически на вход каждый следующий почтовый адрес, на который нужно отправить письмо, и прикрепляет вложения (`attachments['<путь от корня к файлу>'] = File.read('<путь от корня к файлу>`), и отправляет письмо с темой, указанной в свойстве `subject: `  функции `mail`).  

Обратите внимание, что название `imta_first_call` согласуется с названием представления (view'шка) `imta_first_call.text.erb`:

```shell
   ./app/views/user_mailer/imta_first_call.text.erb
```

Этот файл содержит текст письма, который и будет отправляться получателю.

---

# Дополнительно

## Автор

Виктор Чугунов (с) 2014  
[Vkontakte](http://vk.com/victorian)  
[skype](http://skype:mr_victorian)  
[LinkedIn](ru.linkedin.com/pub/victor-chugunov/68/566/806/)  
[GitHub](https://github.com/vichugunov)  
[Website](http://viteam.ru)  
[CV](https://www.dropbox.com/s/rwan3y62te7mxe1/Full_Eng.pdf?dl=0)  
[E-mail](mailto:vichugunov@gmail.com)  

По любым вопросам обращаться к автору. (т.е. ко мне ^_^ )  

## Workflow

В случае внесения каких-то правок в код, необходимости запустить сервис с новыми данными для рассылки или ещё что-то, предлагаю (на данный момент) следующий workflow:

1.  Вносите правки в код этого репозитория.  
2.  Сообщаете автору номер вашего коммита.  
3.  Автор обновляет репозиторий на своём сервере и запускает рассылку.

В дальнейшем полностью пересядем на Heroku и будете сами всё запускать.

Ставить RoR на любую систему, отличную от unix, крайне не советую - чревато проблемами совместимости. 

В случае если поставите RoR ( читайте мануалы ) рассылка активируется по адресу http://localhost:3000/mail

---
