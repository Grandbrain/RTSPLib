/// \file AbstractVideoCodecInfo.cpp
/// \brief Contains classes and functions definitions that provide abstract
/// video codec information interface.
/// \bug No known bugs.

#include "AbstractVideoCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	codecFormat	Codec format.
		AbstractVideoCodecInfo::AbstractVideoCodecInfo(
				CodecFormat codecFormat) noexcept
			: AbstractCodecInfo(CodecType::Video, codecFormat) {
		}

		/// Destructor.
		/// \details Defaulted default destructor.
		AbstractVideoCodecInfo::~AbstractVideoCodecInfo() = default;
	}
}
