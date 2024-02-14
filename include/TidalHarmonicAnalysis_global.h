#pragma once

#include <QtCore/qglobal.h>

#if defined(TidalHarmonicAnalysis)
#define TidalHarmonicAnalysis_EXPORT Q_DECL_EXPORT
#else
#define TidalHarmonicAnalysis_EXPORT Q_DECL_IMPORT
#endif
