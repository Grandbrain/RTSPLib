/// \file Window.hpp
/// \brief Contains classes and functions declarations that provide main window
/// implementation.
/// \bug No known bugs.

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

#include "Playback/PlaybackWidget.hpp"

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
	/// \retval true on success.
	/// \retval false on error.
	bool initialize();

	///
	void destroy();

private:

	///
	Ui::Window* ui_;
};

#endif
