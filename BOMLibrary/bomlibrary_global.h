#ifndef BOMLIBRARY_GLOBAL_H
#define BOMLIBRARY_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef BOMLIBRARY_LIB
# define BOMLIBRARY_EXPORT Q_DECL_EXPORT
#else
# define BOMLIBRARY_EXPORT Q_DECL_IMPORT
#endif

//extern "C" BOMLIBRARY_EXPORT BOMLibrary* BOMLibrary();

#endif // BOMLIBRARY_GLOBAL_H

//