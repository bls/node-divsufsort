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
using v8::Number;
using node::Buffer;

/*
  Ideas: allow caller to pass a pre-allocated buffer if they want; 
  reasonable allocations might be "quite large". If output buffer is
  not big enough, extend it.
*/

/*
  saint_t divsufsort(const sauchar_t *T, saidx_t *SA, saidx_t n);
*/
NAN_METHOD(divsufsort_) {
  NanScope();

  if (args.Length() != 2) {
    return NanThrowTypeError("Wrong number of arguments");
  }
  Local<Value> arg0 = args[0];
  Local<Value> arg1 = args[1];
  if(!Buffer::HasInstance(arg0)) {
    return NanThrowTypeError("First argument should be Buffer");
  }
  if(!Buffer::HasInstance(arg1)) {
    return NanThrowTypeError("Second argument should be Buffer");
  }

  // TODO: check that the two input buffers are, in fact, different!

  Handle<Object> tObj = arg0->ToObject();
  Handle<Object> saObj = arg1->ToObject();

  size_t tLen = Buffer::Length(tObj);
  size_t saLen = Buffer::Length(saObj);

  if(sizeof(saidx_t) != 4 || sizeof(sauchar_t) != 1) {
    return NanThrowError("Internal error: unexpected types");
  }
  if(saLen < (sizeof(saidx_t) * tLen)) { // TODO: integer overflow
    return NanThrowError("Output buffer too small");
  }

  sauchar_t *T = reinterpret_cast<sauchar_t *>(Buffer::Data(tObj));
  saidx_t *SA = reinterpret_cast<saidx_t *>(Buffer::Data(saObj));

  saint_t ret = divsufsort(T, SA, tLen);

  NanReturnValue(NanNew<Number>(ret));
}


NAN_METHOD(divbwt_) {
  NanScope();
  NanReturnUndefined();
}

/*
  saidx_t divbwt(const sauchar_t *T, sauchar_t *U, saidx_t *A, saidx_t n);
*/
void InitAll(Handle<Object> exports) {
  exports->Set(NanNew<String>("divsufsort"),
    NanNew<FunctionTemplate>(divsufsort_)->GetFunction());
  exports->Set(NanNew<String>("divbwt"),
    NanNew<FunctionTemplate>(divbwt_)->GetFunction());
}

NODE_MODULE(divsufsort, InitAll)

} // namespace
