/// \file AACCodecInfo.cpp
/// \brief Contains classes and functions definitions that provide AAC audio
/// codec information interface.
/// \bug No known bugs.

#include "AACCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	configBytes			ASC data.
		/// \param[in]	sizeLength			AU size length parameter.
		/// \param[in]	indexLength			AU index length parameter.
		/// \param[in]	indexDeltaLength	AU index delta length parameter.
		AACCodecInfo::AACCodecInfo(const QByteArray& configurationData,
								   int sizeLength,
								   int indexLength,
								   int indexDeltaLength) noexcept
			: AbstractAudioCodecInfo(CodecFormat::AAC),
			  configurationData_(configurationData),
			  sizeLength_(sizeLength),
			  indexLength_(indexLength),
			  indexDeltaLength_(indexDeltaLength) {
		}

		/// Destructor.
		/// \details Defaulted default destructor.
		AACCodecInfo::~AACCodecInfo() noexcept = default;

		/// Returns ASC data.
		/// \details Returns Audio-specific configuration (ASC) data.
		/// \return ASC data.
		QByteArray AACCodecInfo::getConfigurationData() const noexcept {
			return configurationData_;
		}

		/// Returns AU size length parameter.
		/// \details Returns Access Unit (AU) size length parameter.
		/// \return AU size length parameter.
		int AACCodecInfo::getSizeLength() const noexcept {
			return sizeLength_;
		}

		/// Returns AU index length parameter.
		/// \details Returns Access Unit (AU) index length parameter.
		/// \return AU index length parameter.
		int AACCodecInfo::getIndexLength() const noexcept {
			return indexLength_;
		}

		/// Returns AU index delta length parameter.
		/// \details Returns Access Unit (AU) index delta length parameter.
		/// \return AU index delta length parameter.
		int AACCodecInfo::getIndexDeltaLength() const noexcept {
			return indexDeltaLength_;
		}
	}
}
