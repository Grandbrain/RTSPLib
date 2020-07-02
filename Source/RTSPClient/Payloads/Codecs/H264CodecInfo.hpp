/// \file H264CodecInfo.hpp
/// \brief Contains classes and functions declarations that provide H.264 video
/// codec information interface.
/// \bug No known bugs.

#ifndef H264CODECINFO_HPP
#define H264CODECINFO_HPP

#include "AbstractVideoCodecInfo.hpp"

#include <QByteArray>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that defines H.264 video codec information interface.
		class H264CodecInfo final : public AbstractVideoCodecInfo {
		public:

			/// Constructor.
			/// \param[in]	spsData	SPS data.
			/// \param[in]	ppsData	PPS data.
			explicit H264CodecInfo(const QByteArray& spsData,
								   const QByteArray& ppsData) noexcept;

			/// Destructor.
			~H264CodecInfo() noexcept override;

		public:

			/// Returns SPS data.
			/// \return SPS data.
			QByteArray getSPSData() const noexcept;

			/// Returns PPS data.
			/// \return PPS data.
			QByteArray getPPSData() const noexcept;

		private:

			/// SPS data.
			const QByteArray spsData_;

			/// PPS data.
			const QByteArray ppsData_;
		};
	}
}

#endif
