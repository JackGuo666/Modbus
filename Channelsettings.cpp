#include "Channelsettings.h"
#include "config_data.h"
#include<qcombobox.h>
#include<qlineedit.h>
#include<qtextedit.h>
#include <qtablewidget.h>

Channelsettings::Channelsettings(QDialog* parent)
	: QDialog(parent), m_pData(nullptr)
{
	ui.setupUi(this);


	//test test
	ui.tableWidget->clear();
	ui.tableWidget->setColumnCount(10);
	QStringList headers;
	headers << "ID" << "名称" << "消息类型（功能码）" << "循环触发时间(ms)" << "读偏移" << "读长度" /*<< "错误码"*/ << "写偏移" << "写长度" << "注释";
	ui.tableWidget->setHorizontalHeaderLabels(headers);

	ui.tableWidget->setColumnWidth(2, 180);
	ui.tableWidget->setColumnWidth(3, 180);

	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	//ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	ui.tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个

	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
		//然后设置要根据内容使用宽度的列
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
}


void Channelsettings::on_pushButton_clicked()
{
	int rowcount = ui.tableWidget->rowCount();
	ui.tableWidget->insertRow(rowcount);
	QComboBox* messagetype = new QComboBox();
	//QTextEdit* cycletime = new QTextEdit();
	//QLineEdit* cycletime = new QLineEdit();
	//ui.tableWidget->setCellWidget(rowcount, 3, cycletime);
	int variant[8] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x0f,0x10 };
	QString functionnumber[8] = { "读多个位（线圈）-0x01","读多个位（离散输入）-0x02","读多个位（线圈）-0x03","读多个字（输入寄存器）-0x04","写单个位（线圈）-0x05","写单个字（寄存器）-0x06","写多个位（线圈）-0x0F"
	,"写多个字（寄存器)-0x10" };
	//QVariant userdata;
	//userdata.setValue(variant)
	for (int i = 0; i < 8; i++)
	{
		messagetype->addItem(functionnumber[i], variant[i]);
	}
	ui.tableWidget->setCellWidget(rowcount, 2, messagetype);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);


	QTableWidgetItem* Item0 = new QTableWidgetItem(QString::number(rowcount));
	QTableWidgetItem* Item1 = new QTableWidgetItem(QString("设备") + QString::number(rowcount));
	//QTableWidgetItem* Item2 = new QTableWidgetItem();
	QTableWidgetItem* Item3 = new QTableWidgetItem();
	QTableWidgetItem* Item4 = new QTableWidgetItem();
	QTableWidgetItem* Item5 = new QTableWidgetItem();
	QTableWidgetItem* Item6 = new QTableWidgetItem();
	QTableWidgetItem* Item7 = new QTableWidgetItem();
	QTableWidgetItem* Item8 = new QTableWidgetItem();

	ui.tableWidget->setItem(rowcount, ID, Item0);
	ui.tableWidget->setItem(rowcount, NAME, Item1);
	//ui.tableWidget->setItem(rowcount, MSGTYPE, Item2);
	ui.tableWidget->setItem(rowcount, POLLINGTIME, Item3);
	ui.tableWidget->setItem(rowcount, READOFFSET, Item4);
	ui.tableWidget->setItem(rowcount, READLENGTH, Item5);
	ui.tableWidget->setItem(rowcount, WRITEOFFSET, Item6);
	ui.tableWidget->setItem(rowcount, WRITELENGTH, Item7);
	ui.tableWidget->setItem(rowcount, NOTE, Item8);


	auto& channelVec = m_pData->getChannelVec();
	CChannelData* pData = new CChannelData();
	pData->m_unID = ui.tableWidget->item(rowcount, ID)->text().toUInt();
	pData->m_strDeviceName = ui.tableWidget->item(rowcount, NAME)->text();
	//pData->m_ucMsgType = ui.tableWidget->item(rowcount, MSGTYPE)->text().toUInt();
	pData->m_unPollingTime = ui.tableWidget->item(rowcount, POLLINGTIME)->text().toUInt();
	pData->m_unReadOffsetAddr = ui.tableWidget->item(rowcount, READOFFSET)->text().toUInt();
	pData->m_unReadLength = ui.tableWidget->item(rowcount, READLENGTH)->text().toUInt();
	pData->m_unWriteOffsetAddr = ui.tableWidget->item(rowcount, WRITEOFFSET)->text().toUInt();
	pData->m_unWriteLength = ui.tableWidget->item(rowcount, WRITELENGTH)->text().toUInt();
	pData->m_strNote = ui.tableWidget->item(rowcount, NOTE)->text();

	channelVec.push_back(pData);

	auto value = reinterpret_cast<std::uintptr_t>(pData);
	ui.tableWidget->item(rowcount, ID)->setData(Qt::UserRole, value);

}

Channelsettings::~Channelsettings()
{

}

void Channelsettings::setDeviceData(CDeviceData* pData)
{
	m_pData = pData;

	//初始化界面
	auto &channelVec = m_pData->getChannelVec();
	for (int i = 0; i < channelVec.count(); i++)
	{
		int nRow = ui.tableWidget->rowCount();
		ui.tableWidget->insertRow(nRow);

		QTableWidgetItem* Item0 = new QTableWidgetItem(QString::number(channelVec[i]->m_unID));
		QTableWidgetItem* Item1 = new QTableWidgetItem(channelVec[i]->m_strDeviceName);

		//=======================================
		//QTableWidgetItem* Item2 = new QTableWidgetItem(channelVec[i]->m_ucMsgType);
		QComboBox* messagetype = new QComboBox();
		//QTextEdit* cycletime = new QTextEdit();
		//QLineEdit* cycletime = new QLineEdit();
		//ui.tableWidget->setCellWidget(rowcount, 3, cycletime);
		int variant[8] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x0f,0x10 };
		QString functionnumber[8] = { "读多个位（线圈）-0x01","读多个位（离散输入）-0x02","读多个位（线圈）-0x03","读多个字（输入寄存器）-0x04","写单个位（线圈）-0x05","写单个字（寄存器）-0x06","写多个位（线圈）-0x0F"
		,"写多个字（寄存器)-0x10" };
		//QVariant userdata;
		//userdata.setValue(variant)
		for (int i = 0; i < 8; i++)
		{
			messagetype->addItem(functionnumber[i], variant[i]);
		}
		messagetype->setCurrentIndex(channelVec[i]->m_ucMsgType);
		ui.tableWidget->setCellWidget(i, MSGTYPE, messagetype);
		ui.tableWidget->horizontalHeader()->setSectionResizeMode(MSGTYPE, QHeaderView::ResizeToContents);
		//========================================

		QTableWidgetItem* Item3 = new QTableWidgetItem(QString::number(channelVec[i]->m_unPollingTime));
		QTableWidgetItem* Item4 = new QTableWidgetItem(QString::number(channelVec[i]->m_unReadOffsetAddr));
		QTableWidgetItem* Item5 = new QTableWidgetItem(QString::number(channelVec[i]->m_unReadLength));
		QTableWidgetItem* Item6 = new QTableWidgetItem(QString::number(channelVec[i]->m_unWriteOffsetAddr));
		QTableWidgetItem* Item7 = new QTableWidgetItem(QString::number(channelVec[i]->m_unWriteLength));
		QTableWidgetItem* Item8 = new QTableWidgetItem(channelVec[i]->m_strNote);

		auto value = reinterpret_cast<std::uintptr_t>(channelVec[i]);
		Item0->setData(Qt::UserRole, value);

		ui.tableWidget->setItem(i, ID, Item0);
		ui.tableWidget->setItem(i, NAME, Item1);
		//ui.tableWidget->setItem(i, 2, Item2);
		ui.tableWidget->setItem(i, POLLINGTIME, Item3);
		ui.tableWidget->setItem(i, READOFFSET, Item4);
		ui.tableWidget->setItem(i, READLENGTH, Item5);
		ui.tableWidget->setItem(i, WRITEOFFSET, Item6);
		ui.tableWidget->setItem(i, WRITELENGTH, Item7);
		ui.tableWidget->setItem(i, NOTE, Item8);
	}
}

void Channelsettings::on_pushButton_2_clicked()
{
	int currentrow = ui.tableWidget->currentRow();
	if (currentrow < 0)
	{
		return;
	}

	std::uintptr_t i = ui.tableWidget->item(currentrow, 0)->data(Qt::UserRole).toUInt();
	void* p = (void*)i;


	auto& vecChannel = m_pData->getChannelVec();
	for (QVector<CChannelData*>::iterator iter = vecChannel.begin(); iter != vecChannel.end();)
	{
		if ((*iter) == p)
		{
			delete (*iter);
			vecChannel.erase(iter);//删除该行
		}
		else
		{
			iter++;
		}
	}

	ui.tableWidget->removeRow(currentrow);
}

void Channelsettings::on_pushButton_3_clicked()
{
	m_pData;

	auto channelVec = m_pData->getChannelVec();
	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		//CChannelData* pData = new CChannelData();
		//通道的值在复位变量的userrole上
		CChannelData* pData = (CChannelData*)ui.tableWidget->item(i, ID)->data(Qt::UserRole).toInt();

		pData->m_unID = ui.tableWidget->item(i, ID)->text().toUInt();
		pData->m_strDeviceName = ui.tableWidget->item(i, NAME)->text();

		//

		QComboBox* combox = (QComboBox*)ui.tableWidget->cellWidget(i, MSGTYPE);
		pData->m_ucMsgType = combox->currentIndex();
		//
		pData->m_unPollingTime = ui.tableWidget->item(i, POLLINGTIME)->text().toUInt();
		pData->m_unReadOffsetAddr = ui.tableWidget->item(i, READOFFSET)->text().toUInt();
		pData->m_unReadLength = ui.tableWidget->item(i, READLENGTH)->text().toUInt();
		pData->m_unWriteOffsetAddr = ui.tableWidget->item(i, WRITEOFFSET)->text().toUInt();
		pData->m_unWriteLength = ui.tableWidget->item(i, WRITELENGTH)->text().toUInt();
		pData->m_strNote = ui.tableWidget->item(i, NOTE)->text();
	}
	
	accept();
}

void Channelsettings::on_pushButton_4_clicked()
{
	//取消
}
