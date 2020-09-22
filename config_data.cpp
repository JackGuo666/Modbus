#include "config_data.h"

/*! \fn Config::CBaseData::CBaseData()
*********************************************************************************************************
** \brief Config::CBaseData::CBaseData
** \details
** \return
** \author gw
** \date 2016年1月4日
** \note
********************************************************************************************************/
CBaseData::CBaseData()
	:m_bModifyFlag(false)
{

}

/*! \fn Config::CBaseData::~CBaseData()
*********************************************************************************************************
** \brief Config::CBaseData::~CBaseData
** \details
** \return
** \author gw
** \date 2016年1月4日
** \note
********************************************************************************************************/
CBaseData::~CBaseData()
{

}

CDeviceData::CDeviceData()
{

}

CDeviceData::~CDeviceData()
{

}

QVector<CChannelData*>& CDeviceData::getChannelVec()
{
	// TODO: 在此处插入 return 语句
	return m_vecChannel;
}


CModbusClientData::CModbusClientData()
{
	m_uResponseTime = 1000;
	m_bTcp = TCP_COMM;
}

CModbusClientData::~CModbusClientData()
{

}

void CModbusClientData::SetClientName(const QString& strName)
{
	m_strName = strName;
 }

CChannelData::CChannelData()
{

}

CChannelData::~CChannelData()
{

}
