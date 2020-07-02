/// \file Window.hpp
/// \brief Contains classes and functions declarations that provide main window
/// implementation.
/// \bug No known bugs.

#ifndef WINDOW_H
#define WINDOW_H

#include "Decoders/VideoDecoder.hpp"
#include "Playback/PlaybackVideo.hpp"
#include "Utilities/NetworkStream.hpp"

#include <QThread>
#include <QMainWindow>
#include <QUdpSocket>
#include <QNetworkDatagram>

///
namespace Ui {

	///
	class Window;
}

///
class Window : public QMainWindow {

	Q_OBJECT

public:

	///
	/// \param[in]	parent
	explicit Window(QWidget* parent = nullptr);

	///
	~Window() override;

public:

	///
	void initialize();

private slots:

	///
	void onDatagram();

	///
	/// \param[in]	image
	void onFrames(const QImage& frame);

signals:

	///
	/// \param[in]	data
	void onExtradata(const QByteArray& data);

	///
	/// \param[in]	data
	void onData(const QByteArray& data);


private:

	///
	Ui::Window* ui_;

	///
	QUdpSocket socket_;

	///
	QThread thread_;

	///
	Decoders::VideoDecoder* decoder_;

	///
	Utilities::Streams::NetworkStream stream_;
};

#endif
