/// \file AbstractG711CodecInfo.hpp
/// \brief Contains classes and functions declarations that provide abstract
/// G.711 audio codec information interface.
/// \bug No known bugs.

#ifndef ABSTRACTG711CODECINFO_HPP
#define ABSTRACTG711CODECINFO_HPP

#include "AbstractAudioCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that defines abstract G.711 audio codec information interface.
		class AbstractG711CodecInfo : public AbstractAudioCodecInfo {
		public:

			/// Constructor.
			/// \param[in]	codecFormat	Codec format.
			explicit AbstractG711CodecInfo(CodecFormat codecFormat) noexcept;

			/// Constructor.
			/// \param[in]	codecFormat		Codec format.
			/// \param[in]	samplingRate	Sampling rate.
			/// \param[in]	channelsNumber	Number of channels.
			explicit AbstractG711CodecInfo(CodecFormat codecFormat,
										   int samplingRate,
										   int channelsNumber) noexcept;

			/// Destructor.
			~AbstractG711CodecInfo() override = 0;

		public:

			/// Returns sampling rate.
			/// \return Sampling rate.
			int getSamplingRate() const noexcept;

			/// Returns number of channels.
			/// \return Number of channels.
			int getChannelsNumber() const noexcept;

		private:

			/// Sampling rate.
			const int samplingRate_;

			/// Number of channels.
			const int channelsNumber_;
		};
	}
}

#endif
