/// \file AbstractAudioCodecInfo.cpp
/// \brief Contains classes and functions definitions that provide abstract
/// audio codec information interface.
/// \bug No known bugs.

#include "AbstractAudioCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	codecFormat	Codec format.
		AbstractAudioCodecInfo::AbstractAudioCodecInfo(
				CodecFormat codecFormat) noexcept
			: AbstractCodecInfo(CodecType::Audio, codecFormat) {
		}

		/// Destructor.
		/// \details Defaulted default destructor.
		AbstractAudioCodecInfo::~AbstractAudioCodecInfo() = default;
	}
}
