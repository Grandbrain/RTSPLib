/// \file G711ACodecInfo.hpp
/// \brief Contains classes and functions declarations that provide G.711 A-law
/// audio codec information interface.
/// \bug No known bugs.

#ifndef G711ACODECINFO_HPP
#define G711ACODECINFO_HPP

#include "AbstractG711CodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that defines G.711 A-law audio codec information interface.
		class G711ACodecInfo final : public AbstractG711CodecInfo {
		public:

			/// Constructor.
			explicit G711ACodecInfo() noexcept;

			/// Constructor.
			/// \param[in]	samplingRate	Sampling rate.
			/// \param[in]	channelsNumber	Number of channels.
			explicit G711ACodecInfo(int samplingRate,
									int channelsNumber) noexcept;

			/// Destructor.
			~G711ACodecInfo() noexcept override;
		};
	}
}

#endif
