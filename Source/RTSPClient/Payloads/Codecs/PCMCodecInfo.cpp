/// \file PCMCodecInfo.cpp
/// \brief Contains classes and functions definitions that provide PCM audio
/// codec information interface.
/// \bug No known bugs.

#include "PCMCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	samplingRate	Sampling rate.
		/// \param[in]	bitsPerSample	Number of bits per sample.
		/// \param[in]	channelsNumber	Number of channels.
		PCMCodecInfo::PCMCodecInfo(int samplingRate,
								   int bitsPerSample,
								   int channelsNumber) noexcept
			: AbstractAudioCodecInfo (CodecFormat::PCM),
			  samplingRate_(samplingRate),
			  bitsPerSample_(bitsPerSample),
			  channelsNumber_(channelsNumber) {
		}

		/// Destructor.
		/// \details Defaulted default destructor.
		PCMCodecInfo::~PCMCodecInfo() noexcept = default;

		/// Returns sampling rate.
		/// \details Returns PCM stream sampling rate.
		/// \return Sampling rate.
		int PCMCodecInfo::getSamplingRate() const noexcept {
			return samplingRate_;
		}

		/// Returns number of bits per sample.
		/// \details Returns PCM stream bits per sample.
		/// \return Number of bits per sample.
		int PCMCodecInfo::getBitsPerSample() const noexcept {
			return bitsPerSample_;
		}

		/// Returns number of channels.
		/// \details Returns PCM stream channels number.
		/// \return Number of channels.
		int PCMCodecInfo::getChannelsNumber() const noexcept {
			return channelsNumber_;
		}
	}
}
