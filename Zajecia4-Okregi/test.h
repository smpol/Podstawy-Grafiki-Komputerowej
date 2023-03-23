#ifndef TEST_H
#define TEST_H

#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class testData;

class test
{
    Q_OBJECT
public:
    test();
    test(const test &);
    test &operator=(const test &);
    ~test();

private:
    QSharedDataPointer<testData> data;
};

#endif // TEST_H
