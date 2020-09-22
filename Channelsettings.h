#pragma once

#include <QWidget>
#include <qdialog.h>
#include "ui_Channelsettings.h"

#pragma execution_character_set("utf-8")

class CDeviceData;

class Channelsettings : public QDialog
{
	Q_OBJECT

		enum{};
public:
	Channelsettings(QDialog *parent = Q_NULLPTR);
	~Channelsettings();
	void CchannelID(QString name)
	{
		ui.label_3->setText(QString("Éè±¸")+name);
		ui.label_5->setText(name + QString("%DRV"));
		ui.label_7->setText(name);
	}

	void setDeviceData(CDeviceData* pData);
private:
	Ui::Channelsettings ui;
	CDeviceData* m_pData;
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
};
