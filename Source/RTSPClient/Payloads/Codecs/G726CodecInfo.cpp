/// \file G726CodecInfo.cpp
/// \brief Contains classes and functions definitions that provide G.726 audio
/// codec information interface.
/// \bug No known bugs.

#include "G726CodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	bitrate	Bitrate.
		G726CodecInfo::G726CodecInfo(int bitrate) noexcept
			: G726CodecInfo(bitrate, 8000, 1) {
		}

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	bitrate			Bitrate.
		/// \param[in]	samplingRate	Sampling rate.
		/// \param[in]	channelsNumber	Number of channels.
		G726CodecInfo::G726CodecInfo(int bitrate,
									 int samplingRate,
									 int channelsNumber) noexcept
			: AbstractAudioCodecInfo(CodecFormat::G726),
			  bitrate_(bitrate),
			  samplingRate_(samplingRate),
			  channelsNumber_(channelsNumber) {
		}

		/// Destructor.
		/// \details Defaulted default destructor.
		G726CodecInfo::~G726CodecInfo() noexcept = default;

		/// Returns bitrate.
		/// \details Returns G.726 stream bitrate.
		/// \return Bitrate.
		int G726CodecInfo::getBitrate() const noexcept {
			return bitrate_;
		}

		/// Returns sampling rate.
		/// \details Returns G.726 stream sampling rate.
		/// \return Sampling rate.
		int G726CodecInfo::getSamplingRate() const noexcept {
			return samplingRate_;
		}

		/// Returns number of channels.
		/// \details Returns G.726 stream channels number.
		/// \return Number of channels.
		int G726CodecInfo::getChannelsNumber() const noexcept {
			return channelsNumber_;
		}
	}
}
