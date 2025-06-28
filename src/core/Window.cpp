#include "core/Window.hpp"
#include "IWindow.hpp"
#include "core/OpenGLHeaders.hpp"
#include "utils/error.hpp"
#include <GLFW/glfw3.h>
#include <cassert>
using namespace core;

Window::Window(std::unique_ptr<core::Mouse> &&theMouse,
         std::unique_ptr<core::Keyboard> &&theKeyboard, std::string title,
         int width, int height, bool resizeable)
	: ui::IWindow(*theMouse, *theKeyboard), mouse_(std::move(theMouse)), keyboard_(std::move(theKeyboard)), width_(width), height_(height) {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resizeable ? GL_TRUE : GL_FALSE);

	window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if(!window_)
		utils::error() << "Can't create glfw window!";

	focus();

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) 
		utils::error() << "Can't init glew!";

	mouse_->registryEvents(window_);
	keyboard_->registryEvents(window_);
	
}

ui::IWindow & Window::close() {
	assert(window_);
	glfwSetWindowShouldClose(window_, 1);

	return *this;
}

void Window::updateViewport() {
	assert(window_);
	glfwGetWindowSize(window_, &width_, &height_);
	glViewport(0, 0, width_, height_);
}

Window::~Window() {
	glfwDestroyWindow(window_);
	window_ = nullptr;
}

void Window::startRenderLoop(std::function<void()> & renderFunc) {
	if(!window_) 
		utils::error() << "Window not created or destroyed. Can't start render loop";

	while(!glfwWindowShouldClose(window_)) {
		glfwSwapBuffers(window_);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();
		updateViewport();
		renderFunc();
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
	glfwSetWindowSize(window_, width_, height_);
	return *this;
}

ui::IWindow &Window::move(double newX, double newY) {
	assert(window_);
	windowX_ = newX, windowY_ = newY;
	glfwSetWindowPos(window_, windowX_, windowY_);
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

