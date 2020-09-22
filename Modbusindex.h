#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Modbusindex.h"
#include "QtWidgetsClass.h"

class IMainModule;
class CModbusClientData;

class Modbusindex : public QMainWindow
{
    Q_OBJECT

public:
    Modbusindex(QWidget *parent, IMainModule* pMainModule);

private:
    Ui::ModbusindexClass ui;
    QtWidgetsClass Csettings;
    IMainModule* m_pMainModule;

    QVector<CModbusClientData*> m_vecClient;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void clicked_goto(void);

    void Slot_station_name_modify(int nRow, int nCol);
};
