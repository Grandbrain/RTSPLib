/// \file SDPMediaTrackInfo.hpp
/// \brief Contains classes and functions declarations that provide SDP media
/// track information interface.
/// \bug No known bugs.

#ifndef SDPMEDIATRACKINFO_HPP
#define SDPMEDIATRACKINFO_HPP

#include "Payloads/Codecs/AbstractCodecInfo.hpp"

#include <QString>
#include <QSharedPointer>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that defines SDP media track information interface.
		class SDPMediaTrackInfo final {
		public:

			/// Constructor.
			/// \param[in]	trackName			Track name.
			/// \param[in]	codecInfo			Codec information interface.
			/// \param[in]	samplesFrequency	Samples frequency.
			explicit SDPMediaTrackInfo(
				const QString& trackName,
				const QSharedPointer<AbstractCodecInfo>& codecInfo,
				int samplesFrequency) noexcept;

		public:

			/// Returns track name.
			/// \return Track name.
			QString getTrackName() const noexcept;

			/// Returns codec information interface.
			/// \return Codec information interface.
			QSharedPointer<AbstractCodecInfo> getCodecInfo() const noexcept;

			/// Returns samples frequency.
			/// \return Samples frequency.
			int getSamplesFrequency() const noexcept;

		private:

			/// Track name.
			const QString trackName_;

			/// Codec information interface.
			const QSharedPointer<AbstractCodecInfo> codecInfo_;

			/// Samples frequency.
			const int samplesFrequency_;
		};
	}
}

#endif
