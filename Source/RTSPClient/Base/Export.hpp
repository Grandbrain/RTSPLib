/// \file Export.hpp
/// \brief Contains macro definitions that provide directives to export types
/// from shared library.
/// \bug No known bugs.

#ifndef EXPORT_HPP
#define EXPORT_HPP

#include <QtGlobal>

#if defined(RTSPCLIENT_LIBRARY)
	#define RTSPCLIENT_EXPORT Q_DECL_EXPORT
#else
	#define RTSPCLIENT_EXPORT Q_DECL_IMPORT
#endif

#endif
