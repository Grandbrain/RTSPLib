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
	  ui_(new Ui::Window) {

	ui_->setupUi(this);

	auto mediaWidget = new Player::Playback::PlaybackWidget(this);
	ui_->layoutCentral->addWidget(mediaWidget);
}

///
/// \details
Window::~Window() {
	delete ui_;

	destroy();
}

///
/// \details
/// \retval true on success.
/// \retval false on error.
bool Window::initialize() {
	return true;
}

///
/// \details
void Window::destroy() {

}
