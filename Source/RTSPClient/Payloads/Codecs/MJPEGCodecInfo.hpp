/// \file MJPEGCodecInfo.hpp
/// \brief Contains classes and functions declarations that provide Motion JPEG
/// video codec information interface.
/// \bug No known bugs.

#ifndef MJPEGCODECINFO_HPP
#define MJPEGCODECINFO_HPP

#include "AbstractVideoCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that defines Motion JPEG video codec information interface.
		class MJPEGCodecInfo final : public AbstractVideoCodecInfo {
		public:

			/// Default constructor.
			explicit MJPEGCodecInfo() noexcept;

			/// Destructor.
			~MJPEGCodecInfo() noexcept override;
		};
	}
}

#endif
