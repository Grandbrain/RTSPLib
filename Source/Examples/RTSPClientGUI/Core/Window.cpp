/// \file Window.cpp
/// \brief Contains classes and functions definitions that provide main window
/// \brief implementation.
/// \bug No known bugs.

#include "Window.hpp"
#include "ui_Window.h"

///
/// \details
/// \param[in]	parent
Window::Window(QWidget* parent)
	: QMainWindow(parent),
	  ui_(new Ui::Window),
	  thread_(this),
	  stream_(Utilities::Streams::NetworkStream::ByteOrder::LittleEndian) {

	ui_->setupUi(this);
}

///
/// \details
Window::~Window() {
	delete ui_;

	thread_.quit();
	thread_.wait();
}

///
/// \details
/// \retval true on success.
/// \retval false on error.
void Window::initialize() {
	socket_.bind(50000);

	decoder_ = new Decoders::VideoDecoder;
	decoder_->initialize(Decoders::VideoDecoder::Codec::H264,
						 Decoders::VideoDecoder::Format::RGB888);

	decoder_->moveToThread(&thread_);

	connect(&socket_, &QUdpSocket::readyRead, this, &Window::onDatagram);
	connect(decoder_, &Decoders::VideoDecoder::onFrame, this, &Window::onFrames);
	connect(this, &Window::onExtradata, decoder_, &Decoders::VideoDecoder::setExtradata);
	connect(this, &Window::onData, decoder_, &Decoders::VideoDecoder::decode);
	connect(&thread_, &QThread::finished, decoder_, &QObject::deleteLater);

	thread_.start();
}

///
/// \details
void Window::onDatagram() {
	while (socket_.hasPendingDatagrams()) {
		auto datagram = socket_.receiveDatagram();
		if (datagram.isNull()) continue;

		auto data = datagram.data();
		if (data.isEmpty()) continue;

		stream_.parseDatagram(data);
	}

	QLinkedList<Utilities::Streams::NetworkFrame> frames;
	stream_.pendingFrames(frames);

	for (auto&& frame : frames) {
		qDebug() << frame.number;
		if (frame.flow == "v2sps1") {
			emit onExtradata(frame.data);
			//decoder_->setExtradata(frame.data);
		}
		else if (frame.flow == "v2cam1") {
			emit onData(frame.data);
			//decoder_->decode(frame.data);
		}
	}
}

///
/// \details
/// \param[in]	images
void Window::onFrames(const QImage& frame) {
	/*qDebug() << frames.size();
	for (auto&& frame : frames) {
		ui_->label->setPixmap(QPixmap::fromImage(frame));
	}*/
	ui_->label->setPixmap(QPixmap::fromImage(frame));
}
