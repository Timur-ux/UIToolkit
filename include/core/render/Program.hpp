#ifndef CORE_RENDER_PROGRAM_HPP_
#define CORE_RENDER_PROGRAM_HPP_
// -----------------------------------
// |  Render program implementation  |
// -----------------------------------

class IProgram {
public:
	virtual IProgram & bind() = 0;
	virtual IProgram & unbind() = 0;
	virtual IProgram & () = 0;
	virtual IProgram & unbind() = 0;
	
};

#endif // !CORE_RENDER_PROGRAM_HPP_
