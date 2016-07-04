#ifndef MY_PROTOCOL_H
#define MY_PROTOCOL_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QThread>
#include <QtSerialPort>
#include <stdint.h>

#define POLYNOMIAL 0x1D // x^8 + x^4 + x^3 + x^2 + 1

class TESTER : public QSerialPort {
    Q_OBJECT

public:
    explicit TESTER(QObject* parent = 0);

signals:
    void ReadyReadSignal(const QString& Hex);

private:
    QByteArray data;
    QMutex mutex;

    QByteArray Parcel(void* Data, uint8_t Len = 1);
    char CalcCrc(QByteArray& Data);
    bool CheckData(QByteArray& Data);

    void ReadyRead();
};

#endif // MY_PROTOCOL_H
