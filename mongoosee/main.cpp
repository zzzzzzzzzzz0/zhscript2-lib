/*
 * main.cpp
 *
 *  Created on: 2017年10月7日
 *      Author: zzzzzzzzzzz
 */

#include "mongoose.h"
#include <string>
#include <vector>
#include <map>

extern "C" {
MG_INTERNAL int mg_uri_to_local_path(struct http_message *hm,
                                     const struct mg_serve_http_opts *opts,
                                     char **local_path,
                                     struct mg_str *remainder);
MG_INTERNAL void mg_find_index_file(const char *path, const char *list,
                                    char **index_file, cs_stat_t *stp);
struct mg_str mg_get_mime_type(const char *path, const char *dflt,
                                      const struct mg_serve_http_opts *opts);
void mg_if_get_conn_addr(struct mg_connection *nc, int remote,
                         union socket_address *sa);
}
#define MG_FREE free

using l4_jieshi___ = bool (*)(void* l4, const char* src,bool src_is_file,const char* src2,void* qv_up,int argc,const char**argv, std::vector<std::string> *ret);
using l4_new_qu___ = void* (*)(void* shangji);
using l4_delete_qu___ = void (*)(void* qu);
using l4_var_new___ = int (*)(void* jsq, void* qu, const char* name, const char* val, bool readonly, int type, bool is_noparam);
using l4_mk_suidao___ = void (*)(void *qv, const char *name, unsigned long fnaddr, int ret, size_t argc, ...);
using l4_err___ = const char* (*)(void* l4);
using l4_err_clear___ = void (*)(void* l4);

static void *l4_;
static void *shangji_;
static l4_jieshi___ l4_jieshi_;
static l4_new_qu___ l4_new_qu_;
static l4_delete_qu___ l4_delete_qu_;
static l4_var_new___ l4_var_new_;
static l4_mk_suidao___ l4_mk_suidao_;
static l4_err___ l4_err_;
static l4_err_clear___ l4_err_clear_;

extern "C" void init__(void* l4, void* shangji,
		l4_jieshi___ jieshi, l4_new_qu___ new_qu, l4_delete_qu___ delete_qu,
		l4_var_new___ var_new, l4_mk_suidao___ mk_suidao,
		l4_err___ err, l4_err_clear___ err_clear) {
	l4_ = l4;
	shangji_ = shangji;
	l4_jieshi_ = jieshi;
	l4_new_qu_ = new_qu;
	l4_delete_qu_ = delete_qu;
	l4_var_new_ = var_new;
	l4_mk_suidao_ = mk_suidao;
	l4_err_ = err;
	l4_err_clear_ = err_clear;
}

//static struct mg_serve_http_opts opt_server_;
static std::map<long, struct mg_serve_http_opts*> opts_server_;
static long opts_server_i__(struct mg_connection *nc) {
	union socket_address sa;
	mg_if_get_conn_addr(nc, 0, &sa);
	return sa.sin.sin_port;
}
static const struct mg_serve_http_opts *opts_server__(struct mg_connection *nc) {
	return opts_server_[opts_server_i__(nc)];
}

static std::string s__(const struct mg_str &s1) {
	std::string s2;
	for(size_t i = 0; i < s1.len; i++)
		s2 += s1.p[i];
	return s2;
}
static void urldecode__(std::string &url) {
	size_t siz = url.size();
	char *buf = new char[siz + 1];
	if(mg_url_decode(url.data(), siz, buf, siz, 0) > 0) {
		url = buf;
	}
	delete buf;
}

static void jieshi__(const char* src, bool src_is_file, void*qu, struct mg_connection *nc, struct http_message *hm) {
	std::vector<std::string> ret;
	const struct mg_serve_http_opts *opt = opts_server__(nc);
	if(!l4_jieshi_(l4_, src, src_is_file, nullptr, qu, 0, nullptr, &ret)) {
		ret.clear();
		ret.push_back("Content-Type: text/plain; charset=utf-8\r\n");
		ret.push_back(l4_err_(l4_));
		l4_err_clear_(l4_);
	}
	if(ret.size() > 2) {
		const std::string &path3 = ret[2];
		mg_http_serve_file(nc, hm, path3.c_str(),
				mg_get_mime_type(path3.c_str(), ret[1].c_str(), opt),
				mg_mk_str(opt->extra_headers));
	} else {
		std::string out;
		out += "HTTP/1.1 200 OK\r\n";
		if(ret.size() > 1) {
			out += ret[0];
		} else {
			out += "Content-Type: text/html; charset=utf-8\r\n";
		}
		out += "Content-Length: ";
		if(ret.size() > 0) {
			const std::string &ret1 = ret[ret.size() - 1];
			out += std::to_string(ret1.size());
			out += "\r\n\r\n";
			out += ret1;
		} else {
			out += "0\r\n\r\n";
		}
		mg_printf(nc, "%s", out.c_str());
	}
}

static void suidao__(std::vector<std::string> *ret, void* qu, struct mg_connection *nc, struct http_message *hm, int argc, ...) {
	std::vector<std::string> p;
	{
		va_list argv;
		va_start(argv, argc);
		for(int i = 0; i < argc; ++i) {
			char* s = va_arg(argv, char*);
			p.push_back(s ? s : "NULL");
		}
		va_end(argv);
	}
	if(p.size() < 1)
		return;
	const std::string &tag = p[0];
	if(tag == "ip") {
		ret->push_back(inet_ntoa(nc->sa.sin.sin_addr));
		return;
	}
	if(tag == "uri") {
		ret->push_back(s__(hm->uri));
		return;
	}
	if(tag == "参") {
		std::string s = s__(hm->query_string);
		if(p.size() == 1)
			ret->push_back(s);
		else {
			std::vector<std::string> p2;
			for(size_t i3 = 0;;) {
				size_t i = s.find('&', i3);
				if(i == std::string::npos) {
					if(i3 >= s.size())
						break;
					i = s.size();
				}
				size_t i2 = s.find('=', i3);
				if(i2 == std::string::npos) {
					p2.push_back(s.substr(i3, i - i3));
					p2.push_back("");
				} else {
					p2.push_back(s.substr(i3, i2 - i3));
					i2++;
					p2.push_back(s.substr(i2, i - i2));
				}
				i3 = i + 1;
			}
			for(size_t i2 = 0; i2 < p2.size(); i2 ++)
				urldecode__(p2[i2]);
			for(size_t i = 1; i < p.size(); i++) {
				bool has = false;
				for(size_t i2 = 0; i2 < p2.size(); i2 += 2) {
					if(p2[i2] == p[i]) {
						ret->push_back(p2[i2 + 1]);
						has = true;
					}
				}
				if(!has)
					ret->push_back("");
			}
		}
		return;
	}
}

static void cb_server__(struct mg_connection *nc, int ev, void *p) {
	if (ev == MG_EV_HTTP_REQUEST) {
		struct http_message *hm = (struct http_message *) p;
		const struct mg_serve_http_opts *opt = opts_server__(nc);
		{
			std::string path2;
			{
				size_t uri_len = std::string::npos;
				{
					std::string uri = s__(hm->uri);
					std::string ext = "/zhscript:";
					if(uri.find(ext) == 0) {
						std::string s = uri.substr(ext.length());
						urldecode__(s);
						jieshi__(s.c_str(), false, shangji_, nc, hm);
						return;
					}
					ext = ".zs.";
					size_t i = uri.find(ext);
					if(i != std::string::npos) {
						uri_len = hm->uri.len;
						hm->uri.len = i + ext.length() - 1;
					}
				}
				{
					char *path = NULL;
					struct mg_str path_info;
					if (mg_uri_to_local_path(hm, opt, &path, &path_info) == 0) {
						mg_http_send_error(nc, 404, NULL);
						return;
					}
					if(uri_len != std::string::npos) {
						hm->uri.len = uri_len;
					}
					path2 = path;
					cs_stat_t st;
					if((mg_stat(path, &st) == 0) && S_ISDIR(st.st_mode)) {
						char *index_file = NULL;
						mg_find_index_file(path, opt->index_files, &index_file, &st);
						if(index_file) {
							path2 = index_file;
						}
					}
					MG_FREE(path);
					path = NULL;
				}
			}
			bool is_zs;
			{
				std::string ext = ".zs";
				is_zs = path2.rfind(ext) == path2.length() - ext.length();
			}
			if(is_zs) {
				void* qu = l4_new_qu_(shangji_);
				l4_mk_suidao_(qu, "得", (unsigned long)suidao__, 2, 2, nc, hm);
				jieshi__(path2.c_str(), true, qu, nc, hm);
				l4_delete_qu_(qu);
				return;
			}
		}
		mg_serve_http(nc, hm, *opt);
	}
}

extern "C" void server__(char* addr, char* root, bool loop, std::vector<std::string> *ret) {
	struct mg_mgr* mgr = new struct mg_mgr;
	struct mg_connection *nc;

	mg_mgr_init(mgr, NULL);
	nc = mg_bind(mgr, addr, cb_server__);
	if (nc == NULL) {
		ret->push_back("Failed to create listener");
		return;
	}

	// Set up HTTP server parameters
	mg_set_protocol_http_websocket(nc);
	struct mg_serve_http_opts *opt = new struct mg_serve_http_opts;
	opts_server_[opts_server_i__(nc)] = opt;
	opt->document_root = root;
	opt->enable_directory_listing = "yes";
	opt->index_files = "index.html,index.zs";

	if(!loop) {
		ret->push_back("");
		ret->push_back(std::to_string((unsigned long)mgr));
		return;
	}

	for (;;) {
		mg_mgr_poll(mgr, 1000);
	}
	mg_mgr_free(mgr);
}

static int exit_web_get_ = 0;
static std::string err_web_get_, web_get_;

static void cb_web_get__(struct mg_connection *nc, int ev, void *ev_data) {
	struct http_message *hm = (struct http_message *) ev_data;

	switch (ev) {
	case MG_EV_CONNECT:
		if (*(int *) ev_data != 0) {
			err_web_get_ = strerror(*(int *) ev_data);
			exit_web_get_ = 1;
		}
		break;
	case MG_EV_HTTP_REPLY:
		nc->flags |= MG_F_CLOSE_IMMEDIATELY;
		web_get_ = hm->body.p;
		exit_web_get_ = 1;
		break;
	case MG_EV_CLOSE:
		if (exit_web_get_ == 0) {
			err_web_get_ = "Server closed connection";
			exit_web_get_ = 1;
		}
		break;
	default:
		break;
	}
}

extern "C" void web_get__(char *url, std::vector<std::string> *ret) {
	struct mg_mgr mgr;

	mg_mgr_init(&mgr, NULL);

	err_web_get_.clear();
	web_get_.clear();
	mg_connect_http(&mgr, cb_web_get__, url, NULL, NULL);

	while (exit_web_get_ == 0) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);

	ret->push_back(web_get_);
	ret->push_back(err_web_get_);
}
