#include "tester.h"

TESTER::TESTER(QObject* parent)
    : QSerialPort(parent)
{
    setPortName("COM5");
    setBaudRate(9600);
    setParity(QSerialPort::NoParity);
    setFlowControl(QSerialPort::NoFlowControl);

    connect(this, &QSerialPort::readyRead, this, &TESTER::ReadyRead); //, Qt::QueuedConnection);

    if (!open(ReadWrite))
        qDebug() << "open err";
}

void TESTER::ReadyRead()
{
    uint8_t tmp;
    data.append(readAll());
    if (data.size() > 3) {
        if (data.size() >= data[2]) {
            switch (data[3]) {
            case 0:
                tmp = 0x37;
                waitForReadyRead(50);
                emit ReadyReadSignal(data.toHex().toUpper());
                write(Parcel(&tmp));
                break;
            case 1:
                tmp = 0x01;
                waitForReadyRead(50);
                emit ReadyReadSignal(data.toHex().toUpper());
                write(Parcel(&tmp));
                break;
            default:
                break;
            }
            data.clear();
        }
    }
}

bool TESTER::CheckData(QByteArray& Data)
{
    if (Data.at(0) == 85 && Data.at(1) == -86) {
        if (int(Data[2]) == Data.size()) {
            if (uint8_t(Data[Data.size() - 1]) == CalcCrc(Data)) {
                return true;
            }
        }
    }
    return false;
}

QByteArray TESTER::Parcel(void* Data, uint8_t Len)
{
    uint8_t* p8 = (uint8_t*)Data;
    data.clear();
    data.push_back(-86); //старт 0x55
    data.push_back(85); //старт 0xAA
    data.push_back(Len + 4); //размер посылки
    for (int i = 0; i < Len; ++i) {
        data.push_back(*p8++); //данные
    }
    data.push_back(1); //байт для crc
    data[data.size() - 1] = CalcCrc(data); //crc
    return data;
}

char TESTER::CalcCrc(QByteArray& Data)
{
    uint8_t crc8 = 0;
    for (uint16_t i = 0; i < Data.size() - 1; ++i) {
        crc8 ^= Data[i];
        for (uint16_t j = 0; j < 8; ++j) {
            if (crc8 & 0x80) {
                crc8 = (crc8 << 1) ^ POLYNOMIAL;
            }
            else {
                crc8 <<= 1;
            }
        }
    }
    return crc8;
}
