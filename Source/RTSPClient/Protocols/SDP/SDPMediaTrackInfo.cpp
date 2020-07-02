/// \file SDPMediaTrackInfo.cpp
/// \brief Contains classes and functions definitions that provide SDP media
/// track information interface.
/// \bug No known bugs.

#include "SDPMediaTrackInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	trackName			Track name.
		/// \param[in]	codecInfo			Codec information interface.
		/// \param[in]	samplesFrequency	Samples frequency.
		SDPMediaTrackInfo::SDPMediaTrackInfo(
			const QString& trackName,
			const QSharedPointer<AbstractCodecInfo>& codecInfo,
			int samplesFrequency) noexcept
			: trackName_(trackName),
			  codecInfo_(codecInfo),
			  samplesFrequency_(samplesFrequency) {
		}

		/// Returns track name.
		/// \return Track name.
		QString SDPMediaTrackInfo::getTrackName() const noexcept {
			return trackName_;
		}

		/// Returns codec information interface.
		/// \return Codec information interface.
		QSharedPointer<AbstractCodecInfo>
			SDPMediaTrackInfo::getCodecInfo() const noexcept {
			return codecInfo_;
		}

		/// Returns samples frequency.
		/// \return Samples frequency.
		int SDPMediaTrackInfo::getSamplesFrequency() const noexcept {
			return samplesFrequency_;
		}
	}
}
