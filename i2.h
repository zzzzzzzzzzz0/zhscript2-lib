#include <string>
#include <vector>

//using l4_jieshi___ =
typedef bool (*l4_jieshi___)(void* l4, const char* src,bool src_is_file,const char* src2,void* qv_up,int argc,const char**argv, std::vector<std::string> *ret);
typedef void* (*l4_new_qu___)(void* shangji);
typedef void (*l4_delete_qu___)(void* qu);
typedef int (*l4_var_new___)(void* jsq, void* qu, const char* name, const char* val);
typedef void (*l4_mk_suidao___)(void *qv, const char *name, unsigned long fnaddr, int ret, size_t argc, ...);
typedef const char* (*l4_err___)(void* l4);
typedef void (*l4_err_clear___)(void* l4);

typedef int (*callback4___  )(void* jsq, const char* src,bool src_is_file,const char* src2,void* qv_up,      int argc,const char**argv, std::vector<std::string>* ret);
typedef int (*callback4_2___)(void* jsq, const char* src,bool src_is_file,const char* src2,void* qv_up, std::vector<std::string>* argv, std::vector<std::string>* ret);
typedef int (*callback4_3___)(void* jsq, void* ce, const char* src,bool src_is_file,const char* src2,void* qv_up, void* attr_1, void* attr_2,      int argc,const char**argv, std::vector<std::string>* ret);
typedef int (*callback4_4___)(void* jsq, void* ce, const char* src,bool src_is_file,const char* src2,void* qv_up, void* attr_1, void* attr_2, std::vector<std::string>* argv, std::vector<std::string>* ret);
/*
static void attr__(std::vector<std::string>* ret, int* err, clpars_item___* ci, int argc, ...) {
	va_list argv;
	va_start(argv, argc);
	for (int i = 0; i < argc; i++) {
		char* s = va_arg(argv, char*);
		if(s) {
			string s2 = s;
		}
	}
	va_end(argv);
}
*/

#define cb4_if_err__(ret, err0) \
	if(ret <= 0) { \
		if(ret == -1) { \
			break; \
		} else if(ret == -2) { \
		} else if(ret == -3) { \
			*err = jieshiqi_err_go_ + keyword_end_; \
			break; \
		} else if(ret == -4) { \
			*err = jieshiqi_err_go_ + keyword_exit_; \
			break; \
		} else { \
			*err = err0; \
			break; \
		} \
	}
