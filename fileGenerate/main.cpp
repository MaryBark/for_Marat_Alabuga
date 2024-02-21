#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Создаем и открываем файл для чтения
    QFile file("text.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for reading:" << file.errorString();
        return 1;
    }

    QTextStream in(&file);
    int count = 0;
    QRegularExpression regex("pattern");

    // Считываем файл построчно и проверяем каждую строку на соответствие шаблону
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (regex.match(line).hasMatch()) {
            count++;
        }
    }

    // Выводим количество строк, удовлетворяющих шаблону
    qDebug() << "Number of lines matching the pattern:" << count;

    // Закрываем файл
    file.close();

    return app.exec();
}
