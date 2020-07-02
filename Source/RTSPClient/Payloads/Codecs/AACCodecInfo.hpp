/// \file AACCodecInfo.hpp
/// \brief Contains classes and functions declarations that provide AAC audio
/// codec information interface.
/// \bug No known bugs.

#ifndef AACCODECINFO_HPP
#define AACCODECINFO_HPP

#include "AbstractAudioCodecInfo.hpp"

#include <QByteArray>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that defines AAC audio codec information interface.
		class AACCodecInfo final : public AbstractAudioCodecInfo {
		public:

			/// Constructor.
			/// \param[in]	configBytes			ASC data.
			/// \param[in]	sizeLength			AU size length parameter.
			/// \param[in]	indexLength			AU index length parameter.
			/// \param[in]	indexDeltaLength	AU index delta length parameter.
			explicit AACCodecInfo(const QByteArray& configurationData,
								  int sizeLength,
								  int indexLength,
								  int indexDeltaLength) noexcept;

			/// Destructor.
			~AACCodecInfo() noexcept override;

		public:

			/// Returns ASC data.
			/// \return ASC data.
			QByteArray getConfigurationData() const noexcept;

			/// Returns AU size length parameter.
			/// \return AU size length parameter.
			int getSizeLength() const noexcept;

			/// Returns AU index length parameter.
			/// \return AU index length parameter.
			int getIndexLength() const noexcept;

			/// Returns AU index delta length parameter.
			/// \return AU index delta length parameter.
			int getIndexDeltaLength() const noexcept;

		private:

			/// ASC data.
			const QByteArray configurationData_;

			/// AU size length parameter.
			const int sizeLength_;

			/// AU index length parameter.
			const int indexLength_;

			/// AU index delta length parameter.
			const int indexDeltaLength_;
		};
	}
}

#endif
