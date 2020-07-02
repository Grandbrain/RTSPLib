/// \file G726CodecInfo.hpp
/// \brief Contains classes and functions declarations that provide G.726 audio
/// codec information interface.
/// \bug No known bugs.

#ifndef G726CODECINFO_HPP
#define G726CODECINFO_HPP

#include "AbstractAudioCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that defines G.726 audio codec information interface.
		class G726CodecInfo final : public AbstractAudioCodecInfo {
		public:

			/// Constructor.
			/// \param[in]	bitrate	Bitrate.
			explicit G726CodecInfo(int bitrate) noexcept;

			/// Constructor.
			/// \param[in]	bitrate			Bitrate.
			/// \param[in]	samplingRate	Sampling rate.
			/// \param[in]	channelsNumber	Number of channels.
			explicit G726CodecInfo(int bitrate,
								   int samplingRate,
								   int channelsNumber) noexcept;

			/// Destructor.
			~G726CodecInfo() noexcept override;

		public:

			/// Returns bitrate.
			/// \return Bitrate.
			int getBitrate() const noexcept;

			/// Returns sampling rate.
			/// \return Sampling rate.
			int getSamplingRate() const noexcept;

			/// Returns number of channels.
			/// \return Number of channels.
			int getChannelsNumber() const noexcept;

		private:

			/// Bitrate.
			const int bitrate_;

			/// Sampling rate.
			const int samplingRate_;

			/// Number of channels.
			const int channelsNumber_;
		};
	}
}

#endif
