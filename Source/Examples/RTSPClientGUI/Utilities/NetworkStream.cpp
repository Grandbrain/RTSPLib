/// \file NetworkStream.cpp
/// \brief Contains definitions of utilities for processing network data.
/// \bug No known bugs.

#include "NetworkStream.hpp"

#include "Utilities/ChecksumUtilities.hpp"
#include "Utilities/ChronoUtilities.hpp"
#include "Utilities/MemoryStream.hpp"

namespace {

	/// Datagram protocol version.
	/// \details Specific protocol version to check data integrity.
	constexpr quint16 DATAGRAM_PROTOCOL_VERSION { 0x0100 };

	/// Master chunk identifier.
	/// \details Master chunk identifier code.
	constexpr quint8 CHUNK_MASTER_ID { 1 };

	/// Slave chunk identifier.
	/// \details Slave chunk identifier code.
	constexpr quint8 CHUNK_SLAVE_ID { 0 };

	/// RTL answer chunk identifier.
	/// \details RTL answer chunk identifier code.
	constexpr quint8 CHUNK_RTL_ANSWER_ID { 127 };

	/// RTL request chunk identifier.
	/// \details RTL request chunk identifier code.
	constexpr quint8 CHUNK_RTL_REQUEST_ID { 128 };

	/// Notification chunk identifier.
	/// \details Notification chunk identifier code.
	constexpr quint8 CHUNK_NOTIFICATION_ID { 129 };

	/// Datagram header size.
	/// \details Datagram header size in bytes.
	constexpr int DATAGRAM_HEADER_SIZE { 10 };

	/// Master chunk header size.
	/// \details Master chunk header size in bytes.
	constexpr int CHUNK_MASTER_HEADER_SIZE { 29 };

#if defined (NETWORK_PROTOCOL_EXTENDED) && (NETWORK_PROTOCOL_EXTENDED == 1)
	/// Slave chunk header size.
	/// \details Slave chunk header size in bytes.
	constexpr int CHUNK_SLAVE_HEADER_SIZE { 29 };
#else
	/// Slave chunk header size.
	/// \details Slave chunk header size in bytes.
	constexpr int CHUNK_SLAVE_HEADER_SIZE { 25 };
#endif

	/// RTL chunk header size.
	/// \details RTL chunk header size in bytes.
	constexpr int CHUNK_RTL_HEADER_SIZE { 4 };

	/// Notification chunk header size.
	/// \details Notification chunk header size in bytes.
	constexpr int CHUNK_NOTIFICATION_HEADER_SIZE { 3 };

	/// Chunk task identifier size.
	/// \details Chunk task identifier size in bytes.
	constexpr int CHUNK_TASK_SIZE { 6 };

	/// Chunk flow identifier size.
	/// \details Chunk flow identifier size in bytes.
	constexpr int CHUNK_FLOW_SIZE { 6 };

	/// Frame data maximum size.
	/// \details Frame maximum size without metadata in bytes.
	constexpr int FRAME_MAX_SIZE { 31850493 };

	/// Datagram maximum size.
	/// \details Datagram maximum size with metadata in bytes.
	constexpr int DATAGRAM_MAX_SIZE { 1500 };

	/// Chunk maximum size.
	/// \details Chunk maximum size with metadata in bytes.
	constexpr int CHUNK_MAX_SIZE { 512 };

	/// Datagram data maximum size.
	/// \details Datagram maximum size without metadata in bytes.
	constexpr int DATAGRAM_DATA_MAX_SIZE {
		DATAGRAM_MAX_SIZE - DATAGRAM_HEADER_SIZE
	};

	/// Master chunk data maximum size.
	/// \details Master chunk maximum size without metadata in bytes.
	constexpr int CHUNK_MASTER_DATA_MAX_SIZE {
		CHUNK_MAX_SIZE - CHUNK_MASTER_HEADER_SIZE
	};

	/// Slave chunk data maximum size.
	/// \details Slave chunk maximum size without metadata in bytes.
	constexpr int CHUNK_SLAVE_DATA_MAX_SIZE {
		CHUNK_MAX_SIZE - CHUNK_SLAVE_HEADER_SIZE
	};
}

/// A namespace that contains utilities for data streams.
namespace Utilities::Streams {

	/// Indicates whether the frame is fully collected.
	/// \details Compares the number of collected and detected chunks.
	/// \retval \c true if the frame is fully collected.
	/// \retval \c false the frame is not fully collected.
	bool NetworkFrameBuilder::isFrameCompleted() const {
		return detectedChunks_ != 0 && collectedChunks_ == detectedChunks_;
	}

	/// Returns the collected frame.
	/// \details Returns a reference to the collected frame.
	/// \return Collected frame.
	const NetworkFrame& NetworkFrameBuilder::getFrame() const {
		return frame_;
	}

	/// Returns the collected frame.
	/// \details Returns a reference to the collected frame.
	/// \return Collected frame.
	NetworkFrame& NetworkFrameBuilder::getFrame() {
		return frame_;
	}

	/// Puts a master chunk to the frame.
	/// \details Writes chunk data to the frame buffer. The \a frameSize
	/// parameter is necessary to calculate the total number of chunks.
	/// \param[in]	frameSize		Frame size.
	/// \param[in]	partialFrame	Chunk data.
	/// \retval \c true on success.
	/// \retval \c false on error.
	bool NetworkFrameBuilder::putMasterChunk(int frameSize,
											 const NetworkFrame& partialFrame) {

		if (isFrameCompleted() ||
			masterChunkFound_ ||
			frameSize <= 0 ||
			frameSize < partialFrame.data.size() ||
			partialFrame.data.isEmpty())
			return false;

#if defined (NETWORK_PROTOCOL_EXTENDED) && (NETWORK_PROTOCOL_EXTENDED == 1)
		if (collectedChunks_ == 0) {
			frame_.id = partialFrame.id;
			frame_.number = partialFrame.number;
			frame_.interpretation = partialFrame.interpretation;
			frame_.time = partialFrame.time;
			frame_.priority = partialFrame.priority;
			frame_.task = partialFrame.task;
			frame_.flow = partialFrame.flow;

			if (frame_.data.size() < frameSize) frame_.data.resize(frameSize);
			frame_.data.replace(0, partialFrame.data.size(), partialFrame.data);

			collectedChunks_ = 1, detectedChunks_ = getChunkNumber(frameSize);
		}
		else {
			int detectedChunks = getChunkNumber(frameSize);

			if (detectedChunks < detectedChunks_ ||
				detectedChunks < collectedChunks_ + 1)
				return false;

			frame_.number = partialFrame.number;

			if (frame_.data.size() < frameSize) frame_.data.resize(frameSize);
			frame_.data.replace(0, partialFrame.data.size(), partialFrame.data);

			++collectedChunks_;
			detectedChunks_ = detectedChunks;
		}
#else
		frame_.id = partialFrame.id;
		frame_.number = partialFrame.number;
		frame_.interpretation = partialFrame.interpretation;
		frame_.time = partialFrame.time;
		frame_.priority = partialFrame.priority;
		frame_.task = partialFrame.task;
		frame_.flow = partialFrame.flow;

		frame_.data.reserve(frameSize);
		frame_.data.append(partialFrame.data.data(), partialFrame.data.size());

		collectedChunks_ = 1, detectedChunks_ = getChunkNumber(frameSize);
#endif

		masterChunkFound_ = true;
		if (isFrameCompleted()) frame_.data.squeeze();

		return true;
	}

	/// Puts a slave chunk to the frame.
	/// \details Writes chunk data at the offset \a frameOffset to the
	/// frame buffer.
	/// \param[in]	frameOffset		Offset in frame data.
	/// \param[in]	partialFrame	Chunk data.
	/// \retval \c true on success.
	/// \retval \c false on error.
	bool NetworkFrameBuilder::putSlaveChunk(int frameOffset,
											const NetworkFrame& partialFrame) {

#if defined (NETWORK_PROTOCOL_EXTENDED) && (NETWORK_PROTOCOL_EXTENDED == 1)
		if (isFrameCompleted() ||
			frameOffset <= 0 ||
			partialFrame.data.isEmpty())
			return false;

		int frameSize = frameOffset + partialFrame.data.size();

		if (masterChunkFound_ && frameSize > frame_.data.size())
			return false;

		if (collectedChunks_ == 0) {
			frame_.id = partialFrame.id;
			frame_.number = partialFrame.number;
			frame_.interpretation = partialFrame.interpretation;
			frame_.time = partialFrame.time;
			frame_.priority = partialFrame.priority;
			frame_.task = partialFrame.task;
			frame_.flow = partialFrame.flow;
		}

		if (frame_.data.size() < frameSize) frame_.data.resize(frameSize);

		frame_.data.replace(frameOffset,
							partialFrame.data.size(),
							partialFrame.data);
#else
		Q_UNUSED(frameOffset)

		if (isFrameCompleted() ||
			!masterChunkFound_ ||
			partialFrame.data.isEmpty() ||
			frame_.data.capacity() <
				(frame_.data.size() + partialFrame.data.size()))
			return false;

		frame_.data.append(partialFrame.data.data(), partialFrame.data.size());
#endif

		++collectedChunks_;
		if (isFrameCompleted()) frame_.data.squeeze();

		return true;
	}

	/// Calculates the number of chunks by frame size \a frameSize.
	/// \details Calculates the number of chunks, simulating a breakdown
	/// of the frame into datagrams.
	/// \param[in]	frameSize	Frame size.
	/// \return Number of chunks.
	int NetworkFrameBuilder::getChunkNumber(int frameSize) {
		auto result = 0;

		while (frameSize > 0) {
			auto datagramSize = DATAGRAM_DATA_MAX_SIZE;

			while (frameSize > 0 && datagramSize > 0) {
				auto headerSize = result == 0 ? CHUNK_MASTER_HEADER_SIZE
											  : CHUNK_SLAVE_HEADER_SIZE;

				auto dataSize = result == 0 ? CHUNK_MASTER_DATA_MAX_SIZE
											: CHUNK_SLAVE_DATA_MAX_SIZE;

				if (datagramSize <= headerSize) break;

				datagramSize -= headerSize;
				dataSize = qMin(dataSize, qMin(datagramSize, frameSize));
				++result, frameSize -= dataSize, datagramSize -= dataSize;
			}
		}

		return result;
	}

	/// Constructs a network stream.
	/// \details Constructs a default network stream.
	NetworkStream::NetworkStream()
		: NetworkStream(ByteOrder::BigEndian) {
	}

	/// Constructs a network stream.
	/// \details Constructs a network stream with the specified byte order.
	/// \param[in]	byteOrder	Byte order.
	NetworkStream::NetworkStream(ByteOrder byteOrder)
		: byteOrder_(byteOrder) {
	}

	/// Returns the byte order setting.
	/// \details Returns the current byte order setting of either
	/// big-endian or little-endian.
	/// \return Byte order.
	NetworkStream::ByteOrder NetworkStream::byteOrder() const {
		return byteOrder_;
	}

	/// Packs the network frame into datagrams.
	/// \details Packs frame data and metadata into a list of datagrams.
	/// \param[in]	frame	Network frame.
	/// \return List of datagrams.
	QLinkedList<QByteArray> NetworkStream::packFrame(const NetworkFrame& frame) {
		QLinkedList<QByteArray> datagrams;
		packFrame(frame, datagrams);
		return datagrams;
	}

	/// Packs the network frame into datagrams.
	/// \details Packs frame data and metadata into a list of datagrams.
	/// \param[in]	frame		Network frame.
	/// \param[out]	datagrams	List of datagrams.
	void NetworkStream::packFrame(const NetworkFrame& frame,
								  QLinkedList<QByteArray>& datagrams) {

		if (frame.task.isEmpty() ||
			frame.flow.isEmpty() ||
			frame.data.isEmpty() ||
			frame.task.toUtf8().size() > CHUNK_TASK_SIZE ||
			frame.flow.toUtf8().size() > CHUNK_FLOW_SIZE ||
			frame.data.size() > FRAME_MAX_SIZE)
			return;

		auto index = 0, slaveChunkNumber = 1, frameSize = frame.data.size();
		auto taskArray = frame.task.toUtf8(), flowArray = frame.flow.toUtf8();

		taskArray.append(CHUNK_TASK_SIZE - taskArray.size(), '\0');
		flowArray.append(CHUNK_FLOW_SIZE - flowArray.size(), '\0');

		while (index < frameSize) {
			int left = frameSize - index, grow = 0, size = DATAGRAM_HEADER_SIZE;

			if (index == 0) {
				grow += qMin(left, CHUNK_MASTER_DATA_MAX_SIZE);
				size += CHUNK_MASTER_HEADER_SIZE + grow;
			}

			while (grow < left &&
				   DATAGRAM_MAX_SIZE - size > CHUNK_SLAVE_HEADER_SIZE) {

				auto freeSize =
					DATAGRAM_MAX_SIZE - CHUNK_SLAVE_HEADER_SIZE - size;

				auto dataSize = qMin(freeSize, CHUNK_SLAVE_DATA_MAX_SIZE);
				auto packSize = qMin(dataSize, left - grow);
				auto allSize = CHUNK_SLAVE_HEADER_SIZE + packSize;

				size += allSize, grow += packSize;
			}

			QByteArray datagram;
			datagram.reserve(size);

			MemoryStream stream(&datagram, QIODevice::WriteOnly);

			if (byteOrder_ == ByteOrder::LittleEndian)
				stream.setByteOrder(MemoryStream::ByteOrder::LittleEndian);

			stream << static_cast<quint16>(DATAGRAM_PROTOCOL_VERSION);
			stream << static_cast<quint16>(datagram.capacity());
			stream << static_cast<quint32>(0);
			stream << static_cast<quint16>(0);

			while (datagram.size() < datagram.capacity()) {
				if (index == 0) {
					auto freeSize = datagram.capacity() -
									datagram.size() -
									CHUNK_MASTER_HEADER_SIZE;

					auto dataSize = qMin(freeSize, CHUNK_MASTER_DATA_MAX_SIZE);
					auto allSize = CHUNK_MASTER_HEADER_SIZE + dataSize;

					stream << static_cast<quint8>(CHUNK_MASTER_ID);
					stream << static_cast<quint16>(allSize);
					stream.writeRawData(taskArray.data(), CHUNK_TASK_SIZE);
					stream.writeRawData(flowArray.data(), CHUNK_FLOW_SIZE);
					stream << static_cast<quint32>(frame.id);
					stream << static_cast<quint8>(frame.interpretation);
					stream << static_cast<quint8>(frame.priority);
					stream << static_cast<quint16>(frame.time);
					stream << static_cast<quint16>(frame.number);
					stream << static_cast<quint32>(frameSize);
					stream.writeRawData(frame.data.data() + index, dataSize);

					index += dataSize;

				} else {
					auto freeSize = datagram.capacity() -
									datagram.size() -
									CHUNK_SLAVE_HEADER_SIZE;

					auto dataSize = qMin(freeSize, CHUNK_SLAVE_DATA_MAX_SIZE);
					auto allSize = CHUNK_SLAVE_HEADER_SIZE + dataSize;

					stream << static_cast<quint8>(CHUNK_SLAVE_ID);
					stream << static_cast<quint16>(allSize);
					stream.writeRawData(taskArray.data(), CHUNK_TASK_SIZE);
					stream.writeRawData(flowArray.data(), CHUNK_FLOW_SIZE);
					stream << static_cast<quint32>(frame.id);
					stream << static_cast<quint8>(frame.interpretation);
					stream << static_cast<quint8>(frame.priority);
					stream << static_cast<quint16>(frame.time);
					stream << static_cast<quint16>(slaveChunkNumber++);
#if defined (NETWORK_PROTOCOL_EXTENDED) && (NETWORK_PROTOCOL_EXTENDED == 1)
					stream << static_cast<quint32>(index);
#endif
					stream.writeRawData(frame.data.data() + index, dataSize);

					index += dataSize;
				}
			}

			stream.seek(8);
			stream << Checksum::crc16(datagram);

			if (stream.status() != MemoryStream::Status::Ok) {
				datagrams.clear();
				break;
			}
			else datagrams.append(datagram);
		}
	}

	/// Parses a datagram to collect frames.
	/// \details Parses a datagram to collect frames and other messages.
	/// \param[in]	data	Datagram data to parse.
	/// \param[in]	size	Datagram data size.
	void NetworkStream::parseDatagram(const char* data, int size) {
		parseDatagram(QByteArray::fromRawData(data, size));
	}

	/// Parses a datagram to collect frames.
	/// \details Parses a datagram to collect frames and other messages.
	/// \param[in]	datagram	Datagram to parse.
	void NetworkStream::parseDatagram(const QByteArray& datagram) {
		if (datagram.size() <= DATAGRAM_HEADER_SIZE ||
			datagram.size() > DATAGRAM_MAX_SIZE) return;

		MemoryStream stream(datagram);

		if (byteOrder_ == ByteOrder::LittleEndian)
			stream.setByteOrder(MemoryStream::ByteOrder::LittleEndian);

		quint16 datagramVersion;
		stream >> datagramVersion;

		quint16 datagramSize;
		stream >> datagramSize;

		quint32 datagramRTC;
		stream >> datagramRTC;

		quint16 datagramCRC16;
		stream >> datagramCRC16;

		if (datagramVersion != DATAGRAM_PROTOCOL_VERSION ||
			datagramSize != datagram.size() ||
			datagramCRC16 != Checksum::crc16(datagram, {8, 9}))
			return;

		while (stream.bytesAvailable() > CHUNK_NOTIFICATION_HEADER_SIZE) {
			quint8 chunkID;
			stream >> chunkID;

			if (chunkID == CHUNK_MASTER_ID) {
				if (stream.bytesAvailable() < CHUNK_MASTER_HEADER_SIZE)
					break;

				quint16 chunkSize;
				stream >> chunkSize;

				QByteArray frameTask(CHUNK_TASK_SIZE, Qt::Uninitialized);
				stream.readRawData(frameTask.data(), frameTask.size());

				QByteArray frameFlow(CHUNK_FLOW_SIZE, Qt::Uninitialized);
				stream.readRawData(frameFlow.data(), frameFlow.size());

				quint32 frameID;
				stream >> frameID;

				quint8 frameInterpretation;
				stream >> frameInterpretation;

				quint8 framePriority;
				stream >> framePriority;

				quint16 frameTime;
				stream >> frameTime;

				quint16 frameNumber;
				stream >> frameNumber;

				quint32 frameSize;
				stream >> frameSize;

				if (chunkSize <= CHUNK_MASTER_HEADER_SIZE ||
					chunkSize > CHUNK_MAX_SIZE ||
					frameSize > FRAME_MAX_SIZE ||
					(chunkSize - CHUNK_MASTER_HEADER_SIZE) >
						stream.bytesAvailable())
					break;

				auto data = datagram.data() + stream.position();
				auto size = chunkSize - CHUNK_MASTER_HEADER_SIZE;

				stream.skipRawData(size);

				NetworkFrame frame;
				frame.id = frameID;
				frame.number = frameNumber;
				frame.interpretation = frameInterpretation;
				frame.time = frameTime;
				frame.priority = framePriority;
				frame.task = frameTask;
				frame.flow = frameFlow;
				frame.data = QByteArray::fromRawData(data, size);

				auto iterator = collectedFrames_.find(frameID);

				if (iterator == collectedFrames_.end())
					iterator = collectedFrames_.insert(frameID,
													   NetworkFrameBuilder{ });

				iterator.value().putMasterChunk(frameSize, frame);
			}
			else if (chunkID == CHUNK_SLAVE_ID) {
				if (stream.bytesAvailable() < CHUNK_SLAVE_HEADER_SIZE)
					break;

				quint16 chunkSize;
				stream >> chunkSize;

				QByteArray frameTask(CHUNK_TASK_SIZE, Qt::Uninitialized);
				stream.readRawData(frameTask.data(), frameTask.size());

				QByteArray frameFlow(CHUNK_FLOW_SIZE, Qt::Uninitialized);
				stream.readRawData(frameFlow.data(), frameFlow.size());

				quint32 frameID;
				stream >> frameID;

				quint8 frameInterpretation;
				stream >> frameInterpretation;

				quint8 framePriority;
				stream >> framePriority;

				quint16 frameTime;
				stream >> frameTime;

				quint16 slaveChunkNumber;
				stream >> slaveChunkNumber;

#if defined (NETWORK_PROTOCOL_EXTENDED) && (NETWORK_PROTOCOL_EXTENDED == 1)
				quint32 frameOffset;
				stream >> frameOffset;
#endif

				if (chunkSize <= CHUNK_SLAVE_HEADER_SIZE ||
					chunkSize > CHUNK_MAX_SIZE ||
					(chunkSize - CHUNK_SLAVE_HEADER_SIZE) >
						stream.bytesAvailable())
					break;

				auto data = datagram.data() + stream.position();
				auto size = chunkSize - CHUNK_SLAVE_HEADER_SIZE;

				stream.skipRawData(size);

				NetworkFrame frame;
				frame.id = frameID;
				frame.interpretation = frameInterpretation;
				frame.time = frameTime;
				frame.priority = framePriority;
				frame.task = frameTask;
				frame.flow = frameFlow;
				frame.data = QByteArray::fromRawData(data, size);

				auto iterator = collectedFrames_.find(frameID);

#if defined (NETWORK_PROTOCOL_EXTENDED) && (NETWORK_PROTOCOL_EXTENDED == 1)
				if (iterator == collectedFrames_.end())
					iterator = collectedFrames_.insert(frameID,
													   NetworkFrameBuilder{ });

				iterator.value().putSlaveChunk(frameOffset, frame);
#else
				if (iterator != collectedFrames_.end())
					iterator.value().putSlaveChunk(0, frame);
#endif
			}
			else if (chunkID == CHUNK_RTL_ANSWER_ID) {
				if (datagram.size() !=
					(DATAGRAM_HEADER_SIZE + CHUNK_RTL_HEADER_SIZE - 1))
					break;

				quint16 session;
				stream >> session;

				quint8 reserved;
				stream >> reserved;
			}
			else if (chunkID == CHUNK_RTL_REQUEST_ID) {
				if (datagram.size() !=
					(DATAGRAM_HEADER_SIZE + CHUNK_RTL_HEADER_SIZE - 1))
					break;

				quint16 session;
				stream >> session;

				quint8 reserved;
				stream >> reserved;
			}
			else if (chunkID == CHUNK_NOTIFICATION_ID) {
				if (datagram.size() !=
					(DATAGRAM_HEADER_SIZE + CHUNK_NOTIFICATION_HEADER_SIZE - 1))
					break;

				quint16 reserved;
				stream >> reserved;
			}
			else break;
		}
	}

	/// Returns completed frames.
	/// \details Returns frames that received all their data.
	/// \return List of frames.
	QLinkedList<NetworkFrame> NetworkStream::pendingFrames() {
		QLinkedList<NetworkFrame> frames;
		pendingFrames(frames);
		return frames;
	}

	/// Returns completed frames.
	/// \details Returns frames that received all their data.
	/// \param[out]	frames	List of frames.
	void NetworkStream::pendingFrames(QLinkedList<NetworkFrame>& frames) {
		auto iterator = collectedFrames_.begin();
		while (iterator != collectedFrames_.end()) {
			if (iterator.value().isFrameCompleted()) {
				frames.append(iterator.value().getFrame());
				iterator = collectedFrames_.erase(iterator);
			}
			else ++iterator;
		}
	}
}
