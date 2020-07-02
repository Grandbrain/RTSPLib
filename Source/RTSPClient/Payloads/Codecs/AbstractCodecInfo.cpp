/// \file AbstractCodecInfo.cpp
/// \brief Contains classes and functions definitions that provide abstract
/// codec information interface.
/// \bug No known bugs.

#include "AbstractCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	codecType	Codec type.
		/// \param[in]	codecFormat	Codec format.
		AbstractCodecInfo::AbstractCodecInfo(CodecType codecType,
											 CodecFormat codecFormat) noexcept
			: codecType_(codecType),
			  codecFormat_(codecFormat) {
		}

		/// Destructor.
		/// \details Defaulted default destructor.
		AbstractCodecInfo::~AbstractCodecInfo() = default;

		/// Returns codec type.
		/// \details Returns codec media type.
		/// \return Codec type.
		CodecType AbstractCodecInfo::getCodecType() const noexcept {
			return codecType_;
		}

		/// Returns codec format.
		/// \details Returns codec media format.
		/// \return Codec format.
		CodecFormat AbstractCodecInfo::getCodecFormat() const noexcept {
			return codecFormat_;
		}
	}
}
