/// \file RTSPClient.hpp
/// \brief Contains classes and functions declarations that provide Real Time
/// Streaming Protocol (RTSP) client implementation.
/// \bug No known bugs.

#ifndef RTSPCLIENT_HPP
#define RTSPCLIENT_HPP

#include "RTSPConnectionParameters.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that provides RTP camera implementation.
		class RTSPCLIENT_EXPORT RTSPClient : public QObject {

			Q_OBJECT

		public:

			/// Default constructor.
			/// \param[in]	parent	Parent object.
			explicit RTSPClient(QObject* parent = nullptr);

			/// Destructor.
			~RTSPClient() override;

		public:

			///
			/// \param[in]	url	RTSP connection URL.
			/// \retval true on success.
			/// \retval false on error.
			bool open(const QUrl& url);

			///
			void close();

			/// Sets up the media stream.
			/// \param[in]	path	Media stream path.
			/// \param[in]	ports	Ports for receiving RTP and RTCP data.
			/// \retval true on success.
			/// \retval false on error.
			bool setup(const QUrl& path, const QPair<quint16, quint16>& ports);

			///
			/// \retval true on success.
			/// \retval false on error.
			bool reset();

			/// Starts playback of the media stream.
			/// \retval true on success.
			/// \retval false on error.
			bool play();

			/// Pauses playback of the media stream.
			/// \retval true on success.
			/// \retval false on error.
			bool pause();

			///
			/// \retval
			/// \retval
			bool isOpen() const;

		protected:

			/// Handles timer events.
			/// \param[in]	event	Timer event.
			void timerEvent(QTimerEvent* event) override;

		private slots:

			/// Performs an action when receiving RTP data.
			void onRTPDatagram();

			/// Performs an action when receiving RTCP data.
			void onRTCPDatagram();

		signals:

			/// Signals the readiness of media stream data.
			/// \param[in]	data	Media stream data.
			void onData(const QByteArray& data);

		private:

			/// Opaque type for private data.
			struct RTSPClientPrivate;

			/// Private data.
			const QScopedPointer<RTSPClientPrivate> private_;
		};
	}
}

#endif
