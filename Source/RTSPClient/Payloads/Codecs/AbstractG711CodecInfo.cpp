/// \file AbstractG711CodecInfo.cpp
/// \brief Contains classes and functions definitions that provide abstract
/// G.711 audio codec information interface.
/// \bug No known bugs.

#include "AbstractG711CodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	codecFormat	Codec format.
		AbstractG711CodecInfo::AbstractG711CodecInfo(
			CodecFormat codecFormat) noexcept
			: AbstractG711CodecInfo(codecFormat, 8000, 1) {
		}

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	codecFormat		Codec format.
		/// \param[in]	samplingRate	Sampling rate.
		/// \param[in]	channelsNumber	Number of channels.
		AbstractG711CodecInfo::AbstractG711CodecInfo(
			CodecFormat codecFormat,
			int samplingRate,
			int channelsNumber) noexcept
			: AbstractAudioCodecInfo(codecFormat),
			  samplingRate_(samplingRate),
			  channelsNumber_(channelsNumber) {
		}

		/// Destructor.
		/// \details Defaulted default destructor.
		AbstractG711CodecInfo::~AbstractG711CodecInfo() = default;

		/// Returns sampling rate.
		/// \details Returns G.711 stream sampling rate.
		/// \return Sampling rate.
		int AbstractG711CodecInfo::getSamplingRate() const noexcept {
			return samplingRate_;
		}

		/// Returns number of channels.
		/// \details Returns G.711 stream channels number.
		/// \return Number of channels.
		int AbstractG711CodecInfo::getChannelsNumber() const noexcept {
			return channelsNumber_;
		}
	}
}
