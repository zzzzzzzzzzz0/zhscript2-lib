/*
 * main.cpp
 *
 *  Created on: 2019年8月2日
 *      Author: zzzzzzzzzzz
 */

#include <fstream>
#include "../i2.h"

extern "C" void jia__(const char* s, const char* code, size_t w, const char* add,
		callback4_4___ cb, void* jsq, void* ce, void* qv_up, std::vector<std::string>* ret) {
	if(!s || !code) {
		return;
	}
	if((w > 0 && (!add ||!add[0])) || w > 10000) {
		w = 0;
	}
	std::string ret3;
	for(; *s; s++) {
		std::vector<std::string> argv, ret2;
		argv.push_back(std::to_string((unsigned)(unsigned char)*s));
		argv.push_back(std::string() + *s);
		int ret4 = cb(jsq, ce, code, false, NULL, qv_up, NULL, NULL, &argv, &ret2);
		if(ret4 <= 0 && ret4 != -2) {
			break;
		}
		std::string s2;
		if(ret2.size() >= 1)
			s2 += ret2[0];
		if(ret2.size() >= 2)
			s2 += std::stoi(ret2[1]);
		while(s2.size() < w) {
			s2 = add + s2;
		}
		if(w > 0) {
			s2 = s2.substr(s2.length() - w);
		}
		ret3 += s2;
	}
	ret->push_back(ret3);
}

extern "C" int xor__(const char* filename1, const char* miname, bool isfile, const char* filename2) {
	std::fstream in(filename1, std::ios::in | std::ios::binary);
	if(!in.is_open()) {
		return 1;
	}
	std::fstream out(filename2, std::ios::out | std::ios::binary);
	if(!out.is_open()) {
		return 2;
	}
	std::string mi;
	if(isfile) {
		std::fstream f(miname, std::ios::in | std::ios::binary | std::ios::ate);
		if(!f.is_open()) {
			return 3;
		}
		mi.resize(f.tellg());
		f.seekg(0);
		f.read(&mi[0], mi.size());
		f.close();
	} else
		mi = miname;
	const int siz = 1024;
	char buf[siz];
	while(!in.eof()) {
		in.read(buf, siz);
		int siz2 = in.gcount();
		size_t i3 = 0;
		for(int i = 0; i < siz2; i++, i3++) {
			if(i3 >= mi.size()) {
				i3 = 0;
			}
			unsigned char c = buf[i];
			c ^= mi[i3];
			buf[i] = c;
		}
		out.write(buf, siz2);
	}
	out.close();
	in.close();
	return 0;
}
