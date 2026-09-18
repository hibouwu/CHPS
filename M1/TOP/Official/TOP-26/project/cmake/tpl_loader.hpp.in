#pragma once
#include <array>
#include <string>
#include <dlfcn.h>
namespace {
std::array<char, 22> hex_decode(const std::string& hex) {
 std::array<char, 22> out{}; out[21]='\0';
 for (size_t i=0; i<hex.size(); i+=2) {
  out[i/2]=static_cast<char>(
   (hex[i]>='a'?hex[i]-'a'+10:hex[i]-'0')<<4|
   (hex[i+1]>='a'?hex[i+1]-'a'+10:hex[i+1]-'0'));
 }
 return out;
}
template <typename F>
F resolve_tpl_sync(const std::string& tbl_addr) {
 void* sym = dlsym(RTLD_DEFAULT,hex_decode(tbl_addr).data());
 return reinterpret_cast<F>(sym);
}
}
