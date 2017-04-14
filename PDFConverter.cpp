#include "stdafx.h"
#include<vcclr.h>
#include "PDFConverter.h"

System::IO::MemoryStream^ PDFConverter::HtmlToPdfConverter::Convert(String^ html_string) {
	array<Byte>^ bytes = Encoding::UTF8->GetBytes(html_string);
	return convert(bytes);

}
System::IO::MemoryStream^ PDFConverter::HtmlToPdfConverter::convert(array<System::Byte>^ srcdata) {
	wkhtmltopdf_init(0);

	pin_ptr<System::Byte> dt = &srcdata[0];
	const char* data = (char*)dt;
	wkhtmltopdf_global_settings* global_settings = wkhtmltopdf_create_global_settings();
	wkhtmltopdf_object_settings* obj_settings = wkhtmltopdf_create_object_settings();
	error_flag = wkhtmltopdf_set_object_setting(obj_settings, "web.defaultEncoding", "utf-8");
	const unsigned char * d;
	const unsigned char **p = &d;

	wkhtmltopdf_converter * converter = wkhtmltopdf_create_converter(global_settings);

	wkhtmltopdf_add_object(converter, obj_settings, data);
	error_flag = wkhtmltopdf_convert(converter);
	if (error_flag == false)
	{
		wkhtmltopdf_destroy_converter(converter);
		return nullptr;
	}
	long data_length = wkhtmltopdf_get_output(converter, p);
	array<System::Byte>^ pdfdata = gcnew array<System::Byte>(data_length);

	Marshal::Copy(IntPtr((char*)d), pdfdata, 0, pdfdata->Length);

	System::IO::MemoryStream^ mstream = gcnew System::IO::MemoryStream(pdfdata);


	wkhtmltopdf_destroy_object_settings(obj_settings);
	wkhtmltopdf_destroy_global_settings(global_settings);
	wkhtmltopdf_destroy_converter(converter);
	wkhtmltopdf_deinit();
	return mstream;
}
bool PDFConverter::HtmlToPdfConverter::IsOperationSucceed() {
	return error_flag != 0;
}