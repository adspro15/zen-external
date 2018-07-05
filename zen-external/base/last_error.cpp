#include "last_error.hpp" 
#include <windows.h>

namespace base
{
	hresult_t::hresult_t(HRESULT result):
		result_(result)
	{
	}

	hresult_t::~hresult_t()
	{
		if (FAILED(result_))
			set_last_hresult(result_);
	}

	hresult_t::operator HRESULT() const
	{
		return result_;
	}

	std::string get_error_message(int error)
	{
		char* message_buffer = nullptr;
		::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<char*>(&message_buffer), 0, nullptr);

		std::string message(message_buffer);

		::LocalFree(message_buffer);

		return message;
	}

	int get_last_error()
	{
		return ::GetLastError();
	}

	HRESULT last_result = 0;
	HRESULT get_last_hresult()
	{
		HRESULT tmp = last_result;
		last_result = 0;
		return tmp;
	}

	void set_last_hresult(HRESULT result)
	{
		last_result = result;
	}
}