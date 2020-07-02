/// \file G711UCodecInfo.hpp
/// \brief Contains classes and functions declarations that provide G.711 μ-law
/// audio codec information interface.
/// \bug No known bugs.

#ifndef G711UCODECINFO_HPP
#define G711UCODECINFO_HPP

#include "AbstractG711CodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that defines G.711 μ-law audio codec information interface.
		class G711UCodecInfo final : public AbstractG711CodecInfo {
		public:

			/// Constructor.
			explicit G711UCodecInfo() noexcept;

			/// Constructor.
			/// \param[in]	samplingRate	Sampling rate.
			/// \param[in]	channelsNumber	Number of channels.
			explicit G711UCodecInfo(int samplingRate,
									int channelsNumber) noexcept;

			/// Destructor.
			~G711UCodecInfo() noexcept override;
		};
	}
}

#endif
