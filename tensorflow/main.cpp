/*
 * main.cpp
 *
 *  Created on: 2018年12月15日
 *      Author: zzzzzzzzzzz
 */

#include <tensorflow/c/c_api.h>
#include <string>
#include <stdexcept>
#include <cstdarg>
#include <vector>
#include "../i.h"

class array___ {
public:
	TF_Tensor ** o_ = nullptr;
	int length_ = 0;
	~array___() {
		if(o_) {
			delete o_;
			o_ = nullptr;
		}
	}
};

static void* jsq_ = nullptr;
static ex___ ex_ = nullptr;

using TF_NewTensor___ =  TF_Tensor* (*)(
    TF_DataType, const int64_t* dims, int num_dims, void* data, size_t len,
    void (*deallocator)(void* data, size_t len, void* arg),
    void* deallocator_arg);
static TF_NewTensor___ TF_NewTensor_ = nullptr;

using TF_AddInputList___ =  void (*)(TF_OperationDescription* desc,
                                           const TF_Output* inputs,
                                           int num_inputs);
static TF_AddInputList___ TF_AddInputList_ = nullptr;

using TF_SessionRun___ = void (*)(
    TF_Session* session,
    // RunOptions
    const TF_Buffer* run_options,
    // Input tensors
    const TF_Output* inputs, TF_Tensor* const* input_values, int ninputs,
    // Output tensors
    const TF_Output* outputs, TF_Tensor** output_values, int noutputs,
    // Target operations
    const TF_Operation* const* target_opers, int ntargets,
    // RunMetadata
    TF_Buffer* run_metadata,
    // Output status
    TF_Status*);
static TF_SessionRun___ TF_SessionRun_ = nullptr;

using TF_NewBuffer___ = TF_Buffer* (*)();
static TF_NewBuffer___ TF_NewBuffer_ = nullptr;

static void free1__(void * data, size_t len, void* arg) {}
static void free2__(void * data, size_t len) {free(data);}

static void ex__(void *ce, const char* s) {
	std::string err;
	if(s) {
		for(;*s; s++)
			if(*s >= ' ' && *s <= 127)
				err += *s;
	}
	err += " 不是数字或地址";
	ex_(jsq_, ce, 0, err.c_str(), "");
}

static TF_Output *output__(void *ce, int argc, va_list &argv) {
	TF_Output *il = new TF_Output[argc];
	for (int i = 0; i < argc; ++i) {
		char* s = va_arg(argv, char*);
		try {
			TF_Operation* o = (TF_Operation*)std::stoul(s);
			il[i] = TF_Output {o, 0};
		} catch(std::invalid_argument &e) {
			ex__(ce, s);
			delete il;
			return nullptr;
		}
	}
	return il;
}

extern "C" {

void init__(void* jsq, ex___ ex, TF_NewTensor___ nt, TF_AddInputList___ ail, TF_SessionRun___ sr, TF_NewBuffer___ nb) {
	jsq_=jsq;
	ex_ = ex;
	TF_NewTensor_ = nt;
	TF_AddInputList_ = ail;
	TF_SessionRun_ = sr;
	TF_NewBuffer_ = nb;
}

TF_Tensor *float__(void *ce, char* s) {
	float f;
	try {
		f = std::stof(s);
	} catch(std::invalid_argument &e) {
		ex__(ce, s);
		return nullptr;
	}
	return TF_NewTensor_(TF_FLOAT, NULL, 0, &f, sizeof(float), free1__, NULL);
}

void add_list1__(void *ce, TF_OperationDescription *desc, int argc, ...) {
	va_list argv;
	va_start(argv, argc);
	TF_Output *o = output__(ce, argc, argv);
	va_end(argv);
	if(!o)
		return;
	TF_AddInputList_(desc, o, argc);
	delete o;
}

TF_Output *array2__(void *ce, int argc, ...) {
	va_list argv;
	va_start(argv, argc);
	TF_Output *o = output__(ce, argc, argv);
	va_end(argv);
	return o;
}
void free_array2__(int argc, ...) {
	va_list argv;
	va_start(argv, argc);
	for (int i = 0; i < argc; ++i) {
		TF_Output *o = va_arg(argv, TF_Output*);
		delete o;
	}
	va_end(argv);
}

int array_length__(void *ce, array___* a) {
	if(a->length_ < 0) {
		ex_(jsq_, ce, 0, "地址不适", "");
		return 0;
	}
	return a ? a->length_ : 0;
}
TF_Tensor ** array_o__(array___* a) {
	return a ? a->o_ : nullptr;
}
void free_array__(int argc, ...) {
	va_list argv;
	va_start(argv, argc);
	for (int i = 0; i < argc; ++i) {
		array___ *a = va_arg(argv, array___*);
		delete a;
	}
	va_end(argv);
}

array___* jincan__(int argc, ...) {
	array___* a = new array___{new TF_Tensor *[argc], argc};
	va_list argv;
	va_start(argv, argc);
	for (int i = 0; i < argc; ++i) {
		a->o_[i] = va_arg(argv, TF_Tensor*);
	}
	va_end(argv);
	return a;
}
array___* chucan__(int cnt) {
	array___* a = new array___{new TF_Tensor *[cnt], cnt};
	for(int i = 0; i < cnt; i++)
		a->o_[i] = NULL;
	return a;
}
TF_Tensor * chucan2__(array___* a) {
	return a ? *(a->o_) : nullptr;
}

void fmt__(void *ce, std::vector<std::string>* ret, char* typ, int argc, ...) {
	va_list argv;
	va_start(argv, argc);
	for (int i = 0; i < argc; ++i) {
		void* p = va_arg(argv, void*);
		switch(typ[0]) {
		case 'f': {
			float *f = (float *)p;
			ret->push_back(std::to_string(*f));
			break; }
		default:
			ex_(jsq_, ce, 0, typ, "");
			return;
		}
	}
	va_end(argv);
}

TF_Buffer* file__(const char* file) {
	FILE* f = fopen(file, "rb");
	if (f == NULL)
		return NULL;

	fseek(f, 0, SEEK_END);
	size_t fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	if (fsize < 1) {
		fclose(f);
		return NULL;
	}

	void* data = malloc(fsize);
	fread(data, fsize, 1, f);
	fclose(f);

	TF_Buffer* buf = TF_NewBuffer_();
	buf->data = data;
	buf->length = fsize;
	buf->data_deallocator = free2__;

	return buf;
}

/*
（（赋予出以调用‘sess_run1__’、‘话’、NULL、‘入组’、‘10’、1、‘出组’、NULL、0、NULL、‘态’。）
（赋予出以调用‘sess_run2__’、‘话’、NULL、‘入组’、‘进参’、‘出组’、NULL、0、NULL、‘态’。）
赋予出以调用‘sess_run3__’、‘话’、NULL、‘入组’、‘进参’、‘出组’、‘出参’、NULL、0、NULL、‘态’。
表态。
显示先调用‘data__’、f、调用‘TF_TensorData’、‘出’了换行。）

函数“sess_run1__”以、‘句柄2’、“&-&-&-&-&-i-&-&-i-&-&”。
函数“sess_run2__”以、‘句柄2’、“&-&-&-&-&-&-&-i-&-&”。
函数“sess_run3__”以、‘句柄2’、“&-&-&-&-&-&-&-&-i-&-&”。
TF_Tensor * sess_run1__(TF_Session* session, const TF_Buffer* run_options,
		TF_Output* inputs, TF_Tensor * tensor_in, int ninputs,
		const TF_Output* outputs,
		const TF_Operation* const* target_opers, int ntargets,
		TF_Buffer* run_metadata,
		TF_Status* status) {
	TF_Tensor** input_values;
	//input_values = {&tensor_in};
	input_values = &tensor_in;

	TF_Tensor * tensor_out = NULL;
	TF_Tensor** output_values;
	//output_values = {&tensor_out};
	output_values = &tensor_out;

	TF_SessionRun_(session, run_options,
			inputs, input_values, ninputs,
			outputs, output_values, 1,
		target_opers, ntargets,
		run_metadata,
		status);
	return tensor_out;
}
TF_Tensor * sess_run2__(TF_Session* session, const TF_Buffer* run_options,
		TF_Output* inputs, array___* jincan,
		const TF_Output* outputs,
		const TF_Operation* const* target_opers, int ntargets,
		TF_Buffer* run_metadata,
		TF_Status* status) {
	TF_Tensor * tensor_out = NULL;
	TF_Tensor** output_values;
	output_values = &tensor_out;

	TF_SessionRun_(session, run_options,
			inputs, jincan->o_, jincan->length_,
			outputs, output_values, 1,
		target_opers, ntargets,
		run_metadata,
		status);
	//jincan->o_ = nullptr;
	return tensor_out;
}
TF_Tensor * sess_run3__(TF_Session* session, const TF_Buffer* run_options,
		TF_Output* inputs, array___* jincan,
		const TF_Output* outputs, array___* chucan,
		const TF_Operation* const* target_opers, int ntargets,
		TF_Buffer* run_metadata,
		TF_Status* status) {
	TF_SessionRun_(session, run_options,
			inputs, jincan->o_, jincan->length_,
			outputs, chucan->o_, chucan->length_,
		target_opers, ntargets,
		run_metadata,
		status);
	return *(chucan->o_);
}*/

}
