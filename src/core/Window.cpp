#include "core/Window.hpp"
#include "IWindow.hpp"
#include "utils/error.hpp"
#include <GLFW/glfw3.h>
#include <cassert>
using namespace core;

Window::Window(ui::IMouse &theMouse, ui::IKeyboard &theKeyboard, std::string title, int width, int height, bool resizeable)
	: ui::IWindow(theMouse, theKeyboard), width_(width), height_(height) {
	glfwWindowHint(GLFW_RESIZABLE, resizeable ? GL_TRUE : GL_FALSE);
	window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if(!window_)
		utils::error() << "Can't create glfw window!";

	focus();
}

void Window::updateViewport() {
	assert(window_);
	glViewport(windowX_, windowY_, width_, height_);
}

Window::~Window() {
	destroy();
}

void Window::destroy() {
	glfwDestroyWindow(window_);
	window_ = nullptr;
}

void Window::startRenderLoop() {
	if(!window_) 
		utils::error() << "Window not created or destroyed. Can't start render loop";

	while(!glfwWindowShouldClose(window_)) {
		glfwPollEvents();
		glfwSwapBuffers(window_);
		updateViewport();
	}
};


ui::IWindow &Window::focus() {
	assert(window_);
	glfwMakeContextCurrent(window_);
	return *this;
}

ui::IWindow &Window::minimize() {
	assert(window_);
	glfwIconifyWindow(window_);
	return *this;
}

ui::IWindow &Window::resize(double newWidth, double newHeight) {
	assert(window_);
	width_ = newWidth, height_ = newHeight;
	return *this;
}

ui::IWindow &Window::move(double newX, double newY) {
	assert(window_);
	windowX_ = newX, windowY_ = newY;
	return *this;
}


ui::IWindow &Window::fullscreen() {
	assert(window_);
	glfwMaximizeWindow(window_);
	return *this;
}

ui::IWindow &Window::windowed() {
	assert(window_);
	glfwRestoreWindow(window_);
	return *this;
}

