// PDFConverter.h

#pragma once

#include "include\wkhtmltox\pdf.h"


using namespace System;
using namespace Runtime;
using namespace InteropServices;
using namespace Text;
namespace PDFConverter {
	[SerializableAttribute]
	public ref class HtmlToPdfConverter : MarshalByRefObject
	{
		// TODO: Add your methods for this class here.
	public:
		//array<System::Byte>^ Convert(array<System::Byte>^ html_data);
		System::IO::MemoryStream^ Convert(String^ html_string);
		bool IsOperationSucceed();
	private:
		System::IO::MemoryStream^ convert(array<System::Byte>^ srcdata);
		int error_flag;
		static bool isInit;

	};
}
