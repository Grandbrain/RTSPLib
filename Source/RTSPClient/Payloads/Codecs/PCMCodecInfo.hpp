/// \file PCMCodecInfo.hpp
/// \brief Contains classes and functions declarations that provide PCM audio
/// codec information interface.
/// \bug No known bugs.

#ifndef PCMCODECINFO_HPP
#define PCMCODECINFO_HPP

#include "AbstractAudioCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that defines PCM audio codec information interface.
		class PCMCodecInfo final : public AbstractAudioCodecInfo {
		public:

			/// Constructor.
			/// \param[in]	samplingRate	Sampling rate.
			/// \param[in]	bitsPerSample	Number of bits per sample.
			/// \param[in]	channelsNumber	Number of channels.
			explicit PCMCodecInfo(int samplingRate,
								  int bitsPerSample,
								  int channelsNumber) noexcept;

			/// Destructor.
			~PCMCodecInfo() noexcept override;

		public:

			/// Returns sampling rate.
			/// \return Sampling rate.
			int getSamplingRate() const noexcept;

			/// Returns number of bits per sample.
			/// \return Number of bits per sample.
			int getBitsPerSample() const noexcept;

			/// Returns number of channels.
			/// \return Number of channels.
			int getChannelsNumber() const noexcept;

		private:

			/// Sampling rate.
			const int samplingRate_;

			/// Number of bits per sample.
			const int bitsPerSample_;

			/// Number of channels.
			const int channelsNumber_;
		};
	}
}

#endif
