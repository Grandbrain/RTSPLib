/// \file AbstractAudioCodecInfo.hpp
/// \brief Contains classes and functions declarations that provide abstract
/// audio codec information interface.
/// \bug No known bugs.

#ifndef ABSTRACTAUDIOCODECINFO_HPP
#define ABSTRACTAUDIOCODECINFO_HPP

#include "AbstractCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that defines abstract audio codec information interface.
		class AbstractAudioCodecInfo : public AbstractCodecInfo {
		public:

			/// Constructor.
			/// \param[in]	codecFormat	Codec format.
			explicit AbstractAudioCodecInfo(CodecFormat codecFormat) noexcept;

			/// Destructor.
			~AbstractAudioCodecInfo() override = 0;
		};
	}
}

#endif
