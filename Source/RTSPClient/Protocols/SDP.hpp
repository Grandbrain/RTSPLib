/// \file SDP.hpp
/// \brief Contains classes and functions declarations that provide
/// Session Description Protocol (SDP) implementation.
/// \bug No known bugs.

#ifndef SDP_HPP
#define SDP_HPP

#include <QtCore>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		///
		struct SDPTrack {

			///
			enum class Type {
				AAC		,
				G711	,
				G711A	,
				G711U	,
				G726	,
				PCM		,
				H264	,
				MJPEG

			} type;

			///
			struct AACInfo {

				///
				QByteArray configBytes;

			} AAC;

			///
			struct G711Info {

				///
				int sampleRate = 8000;

				///
				int channels = 1;

			} G711;
		};
	}
}

#endif
