/// \file PlaybackCommon.hpp
/// \brief Contains declarations of common playback classes and functions.
/// \bug No known bugs.

#ifndef PLAYBACKCOMMON_HPP
#define PLAYBACKCOMMON_HPP

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

///
namespace Player {

	///
	namespace Playback {

		///
		class PlaybackInitializer final {

			Q_DISABLE_COPY(PlaybackInitializer)

		public:

			///
			/// \warning
			static void initialize();
		};
	}
}

#endif
