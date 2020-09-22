#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MODBUS_LIB)
#  define MODBUS_EXPORT Q_DECL_EXPORT
# else
#  define MODBUS_EXPORT Q_DECL_IMPORT
# endif
#else
# define MODBUS_EXPORT
#endif
