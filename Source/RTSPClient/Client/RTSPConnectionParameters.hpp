/// \file ConnectionParameters.hpp
/// \brief Contains classes and functions declarations that provide connection
/// parameters for the Real Time Streaming Protocol (RTSP) client.
/// \bug No known bugs.

#ifndef CONNECTIONPARAMETERS_HPP
#define CONNECTIONPARAMETERS_HPP

#include "Base/Export.hpp"

#include <QtCore>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		///
		class RTSPCLIENT_EXPORT RTSPConnectionParametes {
		public:

			///
			enum class TransportProtocol {
				UDP
			};

			///
			enum class RequiredTracks {
				Audio,
				Video,
				All
			};

		public:

			/// Default constructor.
			explicit RTSPConnectionParametes();

			///
			/// \param[in]	connectionUrl
			explicit RTSPConnectionParametes(const QString& connectionUrl);

			///
			/// \param[in]	connectionUrl
			/// \param[in]	userName
			/// \param[in]	password
			explicit RTSPConnectionParametes(const QString& connectionUrl,
											 const QString& userName,
											 const QString& userPassword);

			/// Destructor.
			virtual ~RTSPConnectionParametes();

		public:

			///
			/// \return
			TransportProtocol getTransportProtocol() const;

			///
			/// \param[in]	transportProtocol
			void setTransportProtocol(TransportProtocol transportProtocol);

			///
			/// \return
			RequiredTracks getRequiredTracks() const;

			///
			/// \param[in]	requiredTracks
			void setRequiredTracks(RequiredTracks requiredTracks);

			///
			/// \return
			qint64 getConnectionTimeout() const;

			///
			/// \param[in]	connectionTimeout
			void setConnectionTimeout(qint64 connectionTimeout);

			///
			/// \return
			qint64 getRequestTimeout() const;

			///
			/// \param[in]	requestTimeout
			void setRequestTimeout(qint64 requestTimeout);

			///
			/// \return
			QUrl getConnectionUrl() const;

			///
			/// \param[in]	connectionUrl
			void setConnectionUrl(const QUrl& connectionUrl);

		private:

			///
			TransportProtocol transportProtocol_ { TransportProtocol::UDP };

			///
			RequiredTracks requiredTracks_ { RequiredTracks::All };

			///
			qint64 connectionTimeout_ { 0 };

			///
			qint64 requestTimeout_ { 0 };

			///
			QUrl connectionUrl_;

			///
			QString userAgent_;

			///
			QString userName_;

			///
			QString userPassword_;
		};

	}
}

#endif
