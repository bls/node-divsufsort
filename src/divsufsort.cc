#include <node.h>
#include <nan.h>
#include <v8.h>

#include "divsufsort.h"

namespace {

using v8::Exception;
using v8::FunctionTemplate;
using v8::Handle;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

/*
  Ideas: allow caller to pass a pre-allocated buffer if they want; 
  reasonable allocations might be "quite large". If output buffer is
  not big enough, extend it.
*/

/*
  saint_t divsufsort(const sauchar_t *T, saidx_t *SA, saidx_t n);
*/
NAN_METHOD(divsufsort) {
  NanScope();
  v8::Local<v8::Object> obj = NanNew<v8::Object>();
  NanReturnUndefined();
}


NAN_METHOD(divbwt) {
  NanScope();
  NanReturnUndefined();
}

/*
  //size_t length = node::Buffer::Length(buffer);
  //uint8_t* data = (uint8_t*) node::Buffer::Data(buffer);
  //return buffer;
}

/*
  saidx_t divbwt(const sauchar_t *T, sauchar_t *U, saidx_t *A, saidx_t n);
*/

void InitAll(Handle<Object> exports) {
  exports->Set(NanNew<String>("nothing"),
    NanNew<FunctionTemplate>(divsufsort)->GetFunction());
  exports->Set(NanNew<String>("aString"),
    NanNew<FunctionTemplate>(divbwt)->GetFunction());
}

NODE_MODULE(NativeExtension, InitAll)

} // namespace
