#ifndef THAAP_GLOBAL_H
#define THAAP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(THAAP_LIBRARY)
#define THAAP_EXPORT Q_DECL_EXPORT
#else
#define THAAP_EXPORT Q_DECL_IMPORT
#endif

#endif // THAAP_GLOBAL_H
