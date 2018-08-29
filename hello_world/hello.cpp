#include <node.h>

using namespace v8;

/**
 * FunctionCallbackInfo<Value> &args
 * The argument information given to function call callbacks. This
 * class provides access to information about the context of the call,
 * including the receiver, the number and values of arguments, and
 * the holder of the function.
 */

void Method(const FunctionCallbackInfo<Value> &args)
{
/*  
    An Isolate object represents the V8 instance itself.
    The name comes from the fact that the execution engine, when embedded in a web browser like Chrome,
    could be executing many JavaScript environments simultaneously - associated
    with web pages running in separate tabs and windows. When we have multiple
    pages open, each page’s JavaScript instance must be isolated from the others -
    otherwise one page’s script could access/modify another’s global objects (like
    window.location or window.document). . . which would be bad. V8 uses
    the notion of an Isolate, combined with a Context, to provide these parallel
    execution environments
*/
    Isolate *isolate = args.GetIsolate();
    
    Local<String> retval = String::NewFromUtf8(isolate, "hello world");
    args.GetReturnValue().Set(retval);
}

void init(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(hello_addon, init)