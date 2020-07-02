/// \file main.cpp
/// \brief Contains entry point to the application.
/// \bug No known bugs.

#include <QCoreApplication>

#include "RTSPClient/Client/RTSPClient.hpp"

/// Runs the main application thread.
/// \details Starts the message transfer pipeline between different subsystems.
/// \param[in]	argc	Number of arguments passed to the program.
/// \param[in]	argv	Array of pointers that contain arguments passed
///						to the program.
/// \return Exit status.
int main(int argc, char *argv[]) {
	QCoreApplication a(argc, argv);

	RTSPLib::RTSPClient::RTSPClient client;
	QPair<quint16, quint16> ports { 50000, 50001 };
	QUrl stream { "track1" };
	QUrl url {"rtsp://192.168.11.20:554/udpstream_ch1_stream1_h264"};

	client.open(url);
	client.setup(stream, ports);
	client.play();

	return a.exec();
}
