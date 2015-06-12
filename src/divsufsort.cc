#include "node.h"
#include "v8.h"

namespace {

using v8::Exception;
using v8::Handle;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void RegisterModule(Handle<Object> target) { }

} // anonymous namespace

NODE_MODULE(divsufsort, RegisterModule)
