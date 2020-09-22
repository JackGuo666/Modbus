#include "devicestudio/imainwindow.h"
#include "devicestudio/main_module.h"
#include "devicestudio/iprojmgr.h"
#include "mp\Ade.h"
#include "qtlog\QsLog.h"
#include "devicestudio/treewidget.h"
#include "devicestudio\treeitem_def.h"
#include "devicestudio\tabwidget.h"


#include <modbus_module.h>
#include <qglobal.h>
#include <qstring.h>
#include <fstream>
#include <iostream>
#include <QDomDocument>
#include <QJsonObject>
#include <QStandardItemModel>
#include <QModelIndex>
#include <qtreewidget.h>


static CModubsModule *s_ptrModule = nullptr;

extern "C" MODBUS_EXPORT IPluginModule * CreateModule()
{
	//CoUninitialize();


	////USES_CONVERSION;
	//HRESULT hr = S_OK;
	//CoInitialize(NULL);

	//// create an instance of the application manager
	//IApplicationManager* pIApplicationManager = NULL;
	//hr = CoCreateInstance(CLSID_ApplicationManager, NULL, CLSCTX_ALL, IID_IApplicationManager, (LPVOID*)&pIApplicationManager);
	//if (SUCCEEDED(hr))
	//{
	//	// request the specified MULTIPROG version from the application manager
	//	IDispatch* pIDispatch = NULL;
	//	_Application* pIApplication = NULL;
	//	hr = pIApplicationManager->GetApplication(MULTIPROG_VERSION, &pIDispatch);
	//	if (SUCCEEDED(hr))
	//	{
	//		// query for the application interface from the generic IDispatch interface
	//		hr = pIDispatch->QueryInterface(&pIApplication);
	//		if (SUCCEEDED(hr))
	//		{
	//			// access the application path
	//			BSTR bsPath = NULL;
	//			hr = pIApplication->get_Path(&bsPath);
	//			pIApplication->put_Visible(true);
	//		}
	//	}
	//}


	s_ptrModule = new CModubsModule;
	return s_ptrModule;
	//	return  s_ptrModule.get();
}

#include "qtlog\QsLog.h"
CModubsModule::CModubsModule()
{
	m_pMainModule = nullptr;
}

bool CModubsModule::CModubsModule::SaveToProjectFile(QDomDocument* pXml)
{
	QDomDocument* pDom = m_pMainModule->GetProjMgr()->GetDocument();

	QDomNode n = pDom->documentElement().firstChild();

	//while (!n.isNull())
	{
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if (!e.isNull())
		{
			QString strTmp = e.tagName();// the node really is an element.

			if (strTmp.compare("fes") == 0)
			{
				QDomNode n = e.firstChild();

				//删除fes下的节点
				e.removeChild(n.toElement());

				QDomElement newElem = pDom->createElement("test");
				QDomText newText = pDom->createTextNode("你好");
				newElem.appendChild(newText);
				e.appendChild(newElem);

				

			}
		}
	}

	return true;
}

bool CModubsModule::LoadFromProjectFile(QDomDocument* pXml)
{
	QDomDocument* pDom = m_pMainModule->GetProjMgr()->GetDocument();

	QDomNode n = pDom->documentElement().firstChild();
	
	//while (!n.isNull())
	{
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if (!e.isNull())
		{
			QString strTmp = e.tagName();// the node really is an element.

			//fes根节点下一级节点
			if (strTmp.compare("fes") == 0)
			{
				QDomNode n = e.firstChild();

				//读xml文件，写到数组里初始化界面
				auto e = n.toElement();
				strTmp = e.tagName();


			}

			n.nextSibling();
		}
	}
	
	return true;
}

void CModubsModule::SetLoadDeviceName(const QString& strDeviceName)
{

}

bool CModubsModule::SaveToJsonFile(QJsonObject* pJson)
{
	Q_ASSERT(pJson);

	/*测试每个模块添加*/
	(*pJson)["age"] = "18";
	(*pJson)["name"] = "flywm";

	QJsonObject obj;
	obj.insert("date", "2019-07-21");
	obj.insert("cond_txt", "多云");
	obj.insert("cond_code", "101");
	obj.insert("hum", "23");
	obj.insert("tmp_H", "31");
	obj.insert("tmp_L", "25");


	pJson->insert("weather", obj);
	return true;
}

void CModubsModule::Init(IMainModule* pMainModule)
{
	Q_ASSERT(pMainModule);
	if (!pMainModule)
	{
		return;
	}

	m_pMainModule = pMainModule;
	//获得UI指针
	m_pMainWindow = pMainModule->GetMainWindow();

	//创建modbus左边树形结构
	CreateTreeItem();
	connect(m_pMainWindow->GetLeftTree(), SIGNAL(clicked(const QModelIndex&)), this, SLOT(Slot_ClickLeftTreeItem(const QModelIndex&)));
	connect(m_pMainWindow->GetTabWidget(), SIGNAL(tabCloseRequested(int)), this, SLOT(Slot_CloseOneTabWidget(int)));


	_Application* pApp = m_pMainWindow->GetMPApplition();
	if (!pApp)
	{
		m_pMainModule->LogToFile("MainModule", "MP app pointer is null!");
		return;
	}
	pApp->put_Visible(true);

	QString string("D:\\test_struct\\ttt.mwt");
	BSTR bstr = ::SysAllocString((OLECHAR*)string.utf16());
		// use it

	std::ofstream file;
	string = "D:\\test_struct\\ttt\\dt\\Task_Info\\Task_Info.TYB";
	file.open(string.toStdString().c_str(), std::ios::app);
	if (file.is_open())
	{
		std::cout << "成功打开" << std::endl;
		file << "\n" << "TYPE" << "\n";
		file << "\tTask_Name_TEST_35 : STRING(35);" << "\n";
		file << "END_TYPE" << "\n";

		file << "\n" << "TYPE" << "\n";
		file << "\tArray_WORD_21 : ARRAY[0..20] OF WORD;" << "\n";
		file << "END_TYPE" << "\n";
		file.close();
	}


	VARIANT_BOOL bVar;
	_Project*pro;
	HRESULT ret = pApp->get_ActiveProject((Project **)&pro);
	ret = pro->Close(adeCrNotConfirm, &bVar);
	ret = pApp->OpenProject(bstr, AdeConfirmRule::adeCrNotConfirm, &bVar);

	//没有实现该功能
	ret = pApp->ExecuteCommand(adeCmdBuildMake, &bVar);

	::SysFreeString(bstr);
	pApp->Release();
}

void CModubsModule::UnInit()
{

}

void CModubsModule::CreateTreeItem()
{
	//FTU
	QStandardItemModel* pTreeModel = (QStandardItemModel*)m_pMainWindow->GetLeftTree()->model();
	QStandardItem* pTopItem = (QStandardItem*)pTreeModel->item(0, 0);

	//modbus
	QStandardItem* pModbus = new QStandardItem(tr("modbus"));
	pModbus->setData(TREE_MODBUS_ITEM, Qt::UserRole);
	pModbus->setIcon(QIcon("./ini/icons/analog.png"));
	pTreeModel->appendRow(pModbus);

	QStandardItem* pClient = new QStandardItem(tr("modbus client"));
	pClient->setData(TREE_MODBUS_CLIENT_ITEM, Qt::UserRole);
	pClient->setIcon(QIcon("./ini/icons/analog.png"));
	pModbus->appendRow(pClient);

	QStandardItem* pServer = new QStandardItem(tr("modbus server"));
	pServer->setData(TREE_MODBUS_SERVER_ITEM, Qt::UserRole);
	pServer->setIcon(QIcon("./ini/icons/analog.png"));
	pModbus->appendRow(pServer);

	QStandardItem* pMaster = new QStandardItem(tr("modbus master"));
	pMaster->setData(TREE_MODBUS_MASTER_ITEM, Qt::UserRole);
	pMaster->setIcon(QIcon("./ini/icons/analog.png"));
	pModbus->appendRow(pMaster);

	QStandardItem* pSlave = new QStandardItem(tr("modbus slave"));
	pSlave->setData(TREE_MODBUS_SLAVE_ITEM, Qt::UserRole);
	pSlave->setIcon(QIcon("./ini/icons/analog.png"));
	pModbus->appendRow(pSlave);
}

void CModubsModule::Slot_CloseOneTabWidget(int iIndex)
{
	//
	QWidget* pCloseWgt = m_pMainWindow->GetTabWidget()->widget(iIndex);
	if (!m_MTabIndex.contains(pCloseWgt))
	{
		return;
	}



	if (pCloseWgt != NULL)
	{
		if (pCloseWgt->objectName() == "Monitor")
		{
			m_pMainWindow->GetTabWidget()->removeTab(iIndex);
			return;
		}
		int iIndex2 = m_MTabIndex[pCloseWgt];
		m_MIndexTab.remove(iIndex2);
		m_MTabIndex.remove(pCloseWgt);
		m_pMainWindow->GetTabWidget()->removeTab(iIndex);

		//删除需要关闭的wgt
// 		if (qobject_cast<CChoosePointsWgt*>(pCloseWgt) == NULL)
// 		{
// 			//点表选择不删
// 			pCloseWgt->deleteLater();
// 		}

	}
}

#include "Modbusindex.h"
void CModubsModule::Slot_ClickLeftTreeItem(const QModelIndex& mIndex)
{
	int nType = mIndex.data(Qt::UserRole).toInt();
	if (nType == TREE_MODBUS_CLIENT_ITEM)
	{
		if (m_MIndexTab.contains(TREE_MODBUS_CLIENT_ITEM))
		{
			m_pMainWindow->GetTabWidget()->setCurrentWidget(m_MIndexTab[TREE_MODBUS_CLIENT_ITEM]);
		}
		else
		{
			Modbusindex* pModbus = new Modbusindex(nullptr, m_pMainModule);
			m_pMainWindow->GetTabWidget()->AddTab(pModbus, tr("modbus"), tr("modbus"));
			//index和widget映射关系
			m_MIndexTab.insert(TREE_MODBUS_CLIENT_ITEM, pModbus);
			m_MTabIndex.insert(pModbus, TREE_MODBUS_CLIENT_ITEM);
			m_pMainWindow->GetTabWidget()->setCurrentWidget(m_MIndexTab[TREE_MODBUS_CLIENT_ITEM]);
		}
		

	}

}


