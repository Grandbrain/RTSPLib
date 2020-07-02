/// \file H264CodecInfo.cpp
/// \brief Contains classes and functions definitions that provide H.264 video
/// codec information interface.
/// \bug No known bugs.

#include "H264CodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	spsData	SPS data.
		/// \param[in]	ppsData	PPS data.
		H264CodecInfo::H264CodecInfo(const QByteArray& spsData,
									 const QByteArray& ppsData) noexcept
			: AbstractVideoCodecInfo(CodecFormat::H264),
			  spsData_(spsData),
			  ppsData_(ppsData) {
		}

		/// Destructor.
		/// \details Defaulted default destructor.
		H264CodecInfo::~H264CodecInfo() noexcept = default;

		/// Returns SPS data.
		/// \details Returns Sequence Parameter Set (SPS) data.
		/// \return SPS data.
		QByteArray H264CodecInfo::getSPSData() const noexcept {
			return spsData_;
		}

		/// Returns PPS data.
		/// \details Returns Picture Parameter Set (PPS) data.
		/// \return PPS data.
		QByteArray H264CodecInfo::getPPSData() const noexcept {
			return ppsData_;
		}
	}
}
