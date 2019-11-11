/// \file PlaybackCommon.cpp
/// \brief Contains definitions of common playback classes and functions.
/// \bug No known bugs.

#include "PlaybackCommon.hpp"

namespace Player {

	namespace Playback {

		///
		/// \details
		/// \warning
		void PlaybackInitializer::initialize() {
			QSurfaceFormat format;
			format.setDepthBufferSize(24);

			QSurfaceFormat::setDefaultFormat(format);
		}
	}
}
