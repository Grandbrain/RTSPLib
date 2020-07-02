/// \file ChronoUtilities.hpp
/// \brief Contains declarations of utilities for calculating timestamps.
/// \bug No known bugs.

#ifndef CHRONOUTILITIES_HPP
#define CHRONOUTILITIES_HPP

#include <QtGlobal>

/// A namespace that contains utilities for calculating timestamps.
namespace Utilities::Chrono {

	/// Generates a 64-bit timestamp from microseconds.
	/// \return A 64-bit timestamp from microseconds.
	quint64 timestampMicroseconds64() noexcept;

	/// Generates a 32-bit timestamp from microseconds.
	/// \return A 32-bit timestamp from microseconds.
	quint32 timestampMicroseconds32() noexcept;
}

#endif
