/// \file ConnectionParameters.cpp
/// \brief Contains classes and functions definitions that provide connection
/// parameters for the Real Time Streaming Protocol (RTSP) client.
/// \bug No known bugs.

#include "RTSPConnectionParameters.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Default constructor.
		/// \details
		RTSPConnectionParametes::RTSPConnectionParametes() {

		}

		///
		/// \details
		/// \param[in]	connectionUrl
		RTSPConnectionParametes::RTSPConnectionParametes(
			const QString& connectionUrl) {

			setConnectionUrl(connectionUrl);
			saveCredentials(connectionUrl);
		}

		///
		/// \details
		/// \param[in]	connectionUrl
		/// \param[in]	userName
		/// \param[in]	password
		RTSPConnectionParametes::RTSPConnectionParametes(
			const QString& connectionUrl,
			const QString& userName,
			const QString& userPassword) {

			setConnectionUrl(connectionUrl);
			setUserName(userName);
			setUserPassword(userPassword);
		}

		/// Destructor.
		/// \details
		RTSPConnectionParametes::~RTSPConnectionParametes() {

		}

		///
		/// \details
		/// \return
		RTSPConnectionParametes::TransportProtocol
			RTSPConnectionParametes::getTransportProtocol() const {

			return transportProtocol_;
		}

		///
		/// \details
		/// \param[in]	transportProtocol
		void RTSPConnectionParametes::setTransportProtocol(
			RTSPConnectionParametes::TransportProtocol transportProtocol) {

			transportProtocol_ = transportProtocol;
		}

		///
		/// \details
		/// \return
		RTSPConnectionParametes::RequiredTracks
			RTSPConnectionParametes::getRequiredTracks() const {

			return requiredTracks_;
		}

		///
		/// \details
		/// \param[in]	requiredTracks
		void RTSPConnectionParametes::setRequiredTracks(
			RTSPConnectionParametes::RequiredTracks requiredTracks) {

			requiredTracks_ = requiredTracks;
		}

		///
		/// \details
		/// \return
		qint64 RTSPConnectionParametes::getConnectionTimeout() const {
			return connectionTimeout_;
		}

		///
		/// \details
		/// \param[in]	connectionTimeout
		void RTSPConnectionParametes::setConnectionTimeout(
			qint64 connectionTimeout) {

			connectionTimeout_ = connectionTimeout;
		}

		///
		/// \details
		/// \return
		qint64 RTSPConnectionParametes::getRequestTimeout() const {
			return requestTimeout_;
		}

		///
		/// \details
		/// \param[in]	requestTimeout
		void RTSPConnectionParametes::setRequestTimeout(qint64 requestTimeout) {
			requestTimeout_ = requestTimeout;
		}

		///
		/// \details
		/// \return
		QUrl RTSPConnectionParametes::getConnectionUrl() const {
			return connectionUrl_;
		}

		///
		/// \details
		/// \param[in]	connectionUrl
		void RTSPConnectionParametes::setConnectionUrl(
			const QUrl& connectionUrl) {

			if (!connectionUrl.isValid() || connectionUrl.isRelative())
				throw std::invalid_argument(
					"Connection URL should be valid and absolute");

			connectionUrl_ = connectionUrl.adjusted(
				QUrl::RemoveScheme |
				QUrl::RemoveAuthority
			);

			connectionUrl_.setScheme("rtsp");
			connectionUrl_.setPort(554);
		}

		///
		/// \details
		/// \return
		QString RTSPConnectionParametes::getUserAgent() const {
			return userAgent_;
		}

		///
		/// \details
		/// \param[in]	userAgent
		void RTSPConnectionParametes::setUserAgent(const QString& userAgent) {
			userAgent_ = userAgent;
		}

		///
		/// \details
		/// \return
		QString RTSPConnectionParametes::getUserName() const {
			return userName_;
		}

		///
		/// \details
		/// \param[in]	userName
		void RTSPConnectionParametes::setUserName(const QString& userName) {
			userName_ = userName;
		}

		///
		/// \details
		/// \return
		QString RTSPConnectionParametes::getUserPassword() const {
			return userPassword_;
		}

		///
		/// \details
		/// \param[in]	userPassword
		void RTSPConnectionParametes::setUserPassword(
			const QString& userPassword) {

			userPassword_ = userPassword;
		}

		///
		/// \details
		/// \param[in]	connectionUrl
		void RTSPConnectionParametes::saveCredentials(
			const QUrl& connectionUrl) {

			auto userInfo = connectionUrl.userInfo().split(':');

			if (userInfo.size() == 2) {
				userName_ = userInfo.first();
				userPassword_ = userInfo.last();
			}
		}
	}
}
