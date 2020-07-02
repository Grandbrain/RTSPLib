/// \file MJPEGCodecInfo.cpp
/// \brief Contains classes and functions definitions that provide Motion JPEG
/// video codec information interface.
/// \bug No known bugs.

#include "MJPEGCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Default constructor.
		/// \details Initializes object fields.
		MJPEGCodecInfo::MJPEGCodecInfo() noexcept
			: AbstractVideoCodecInfo(CodecFormat::MJPEG) {
		}

		/// Destructor.
		/// \details Defaulted default destructor.
		MJPEGCodecInfo::~MJPEGCodecInfo() noexcept = default;
	}
}
