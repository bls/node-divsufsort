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

  if(!node::Buffer::HasInstance(arg0)) {
    return NanThrowTypeError("First argument must be a Buffer");
  }
  if(!node::Buffer::HasInstance(arg1)) {
    return NanThrowTypeError("Second argument must be a Buffer");
  }

  Handle<Object> tObj = arg0->ToObject();
  Handle<Object> saObj = arg1->ToObject();

  size_t tLen = node::Buffer::Length(tObj);
  size_t saLen = node::Buffer::Length(saObj);

  if(sizeof(saidx_t) != 4 || sizeof(sauchar_t) != 1) {
    return NanThrowError("Internal error: unexpected types");
  }
  if(saLen < (sizeof(saidx_t) * tLen)) { // TODO: integer overflow
    return NanThrowError("Output buffer too small");
  }

  sauchar_t *T = reinterpret_cast<sauchar_t *>(node::Buffer::Data(tObj));
  saidx_t *SA = reinterpret_cast<saidx_t *>(node::Buffer::Data(saObj));

  saint_t ret = divsufsort(T, SA, tLen);
  if(ret < 0) {
    return NanThrowError("divsufsort failed");
  }
  NanReturnValue(NanNew<Number>(0));
}


NAN_METHOD(divbwt_) {
  NanScope();

  if (args.Length() != 3) {
    return NanThrowTypeError("Wrong number of arguments");
  }
  Local<Value> arg0 = args[0];
  Local<Value> arg1 = args[1];
  Local<Value> arg2 = args[2];

  if(!node::Buffer::HasInstance(arg0)) {
    return NanThrowTypeError("First argument must be a Buffer");
  }
  if(!node::Buffer::HasInstance(arg1)) {
    return NanThrowTypeError("Second argument must be a Buffer");
  }
  if(!node::Buffer::HasInstance(arg2)) {
    return NanThrowTypeError("Third argument must be a Buffer");
  }

  Handle<Object> tObj = arg0->ToObject();
  Handle<Object> uObj = arg1->ToObject();
  Handle<Object> aObj = arg2->ToObject();

  size_t tLen = node::Buffer::Length(tObj);
  size_t uLen = node::Buffer::Length(uObj);
  size_t aLen = node::Buffer::Length(aObj);

  if(sizeof(saidx_t) != 4 || sizeof(sauchar_t) != 1) {
    return NanThrowError("Internal error: unexpected types");
  }
  if(tLen != uLen) {
    return NanThrowError("First and second args must be same size");
  }
  if(aLen < (sizeof(saidx_t) * tLen)) { // TODO: integer overflow
    return NanThrowError("Third buffer too small");
  }

  sauchar_t *T = reinterpret_cast<sauchar_t *>(node::Buffer::Data(tObj));
  sauchar_t *U = reinterpret_cast<sauchar_t *>(node::Buffer::Data(uObj));
  saidx_t *AUX = reinterpret_cast<saidx_t *>(node::Buffer::Data(aObj));

  saidx_t ret = divbwt(T, U, AUX, tLen);
  if(ret < 0) {
    return NanThrowError("divbwt failed");
  }

  NanReturnValue(NanNew<Number>(ret));
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
