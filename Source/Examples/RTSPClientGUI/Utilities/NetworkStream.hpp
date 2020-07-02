/// \file NetworkStream.hpp
/// \brief Contains declarations of utilities for processing network data.
/// \bug No known bugs.

#ifndef NETWORKSTREAM_HPP
#define NETWORKSTREAM_HPP

#include <QHash>
#include <QByteArray>
#include <QLinkedList>

/// A namespace that contains utilities for data streams.
namespace Utilities::Streams {

	/// A structure that defines a network frame.
	struct NetworkFrame {

		/// Frame identifier.
		quint32 id = 0;

		/// Frame number.
		quint16 number = 0;

		/// Frame interpretation.
		quint8 interpretation = 0;

		/// Frame processing time.
		quint16 time = 0;

		/// Frame priority.
		quint8 priority = 10;

		/// Sender task identifier.
		QString task;

		/// Information flow identifier.
		QString flow;

		/// Frame data array.
		QByteArray data;
	};

	/// A class that provides a network frame builder implementation.
	class NetworkFrameBuilder {
	public:

		/// Constructs a network frame builder.
		explicit NetworkFrameBuilder() = default;

		/// Destroys the network frame builder.
		virtual ~NetworkFrameBuilder() = default;

	public:

		/// Indicates whether the frame is fully collected.
		/// \retval \c true if the frame is fully collected.
		/// \retval \c false the frame is not fully collected.
		bool isFrameCompleted() const;

		/// Returns the collected frame.
		/// \return Collected frame.
		const NetworkFrame& getFrame() const;

		/// Returns the collected frame.
		/// \return Collected frame.
		NetworkFrame& getFrame();

		/// Puts a master chunk to the frame.
		/// \param[in]	frameSize		Frame size.
		/// \param[in]	partialFrame	Chunk data.
		/// \retval \c true on success.
		/// \retval \c false on error.
		bool putMasterChunk(int frameSize, const NetworkFrame& partialFrame);

		/// Puts a slave chunk to the frame.
		/// \param[in]	frameOffset		Offset in frame data.
		/// \param[in]	partialFrame	Chunk data.
		/// \retval \c true on success.
		/// \retval \c false on error.
		bool putSlaveChunk(int frameOffset, const NetworkFrame& partialFrame);

	private:

		/// Calculates the number of chunks by frame size \a frameSize.
		/// \param[in]	frameSize	Frame size.
		/// \return Number of chunks.
		static int getChunkNumber(int frameSize);

	private:

		/// Indicates whether the master chunk is found.
		bool masterChunkFound_ = false;

		/// Number of collected chunks.
		int collectedChunks_ = 0;

		/// Number of detected chunks.
		int detectedChunks_ = 0;

		/// Network frame.
		NetworkFrame frame_;
	};

	/// A class that provides a network stream implementation.
	class NetworkStream {
	public:

		/// An enumeration that describes the byte order used for
		/// reading/writing the data.
		enum class ByteOrder {
			BigEndian	,	///< Most significant byte first.
			LittleEndian,	///< Least significant byte first.
		};

	public:

		/// Constructs a network stream.
		explicit NetworkStream();

		/// Constructs a network stream.
		/// \param[in]	byteOrder	Byte order.
		explicit NetworkStream(ByteOrder byteOrder);

		/// Destroys the network stream.
		virtual ~NetworkStream() = default;

	public:

		/// Returns the byte order setting.
		/// \return Byte order.
		ByteOrder byteOrder() const;

		/// Packs the network frame into datagrams.
		/// \param[in]	frame	Network frame.
		/// \return List of datagrams.
		QLinkedList<QByteArray> packFrame(const NetworkFrame& frame);

		/// Packs the network frame into datagrams.
		/// \param[in]	frame		Network frame.
		/// \param[out]	datagrams	List of datagrams.
		void packFrame(const NetworkFrame& frame,
					   QLinkedList<QByteArray>& datagrams);

		/// Parses a datagram to collect frames.
		/// \param[in]	data	Datagram data to parse.
		/// \param[in]	size	Datagram data size.
		void parseDatagram(const char* data, int size);

		/// Parses a datagram to collect frames.
		/// \param[in]	datagram	Datagram to parse.
		void parseDatagram(const QByteArray& datagram);

		/// Returns completed frames.
		/// \return List of frames.
		QLinkedList<NetworkFrame> pendingFrames();

		/// Returns completed frames.
		/// \param[out]	frames	List of frames.
		void pendingFrames(QLinkedList<NetworkFrame>& frames);

	private:

		/// Byte order.
		ByteOrder byteOrder_;

		/// A container for the collected frames.
		QHash<quint32, NetworkFrameBuilder> collectedFrames_;
	};
}

#endif
