/// \file AbstractVideoCodecInfo.hpp
/// \brief Contains classes and functions declarations that provide abstract
/// video codec information interface.
/// \bug No known bugs.

#ifndef ABSTRACTVIDEOCODECINFO_HPP
#define ABSTRACTVIDEOCODECINFO_HPP

#include "AbstractCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that defines abstract video codec information interface.
		class AbstractVideoCodecInfo : public AbstractCodecInfo {
		public:

			/// Constructor.
			/// \param[in]	codecFormat	Codec format.
			explicit AbstractVideoCodecInfo(CodecFormat codecFormat) noexcept;

			/// Destructor.
			~AbstractVideoCodecInfo() override = 0;
		};
	}
}

#endif
