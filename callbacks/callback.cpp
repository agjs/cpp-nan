#include <node.h>

using namespace v8;

/*
    On line 27 we get a reference to the V8 execution context - isolate. Line 28 casts
    arg[0] (a Local<Value>) to a function object - cb. In a bit of a V8 quirk, the
    API is a little inconsistent here. Instead of calling something like ToNumber as
    we would to convert the Local<Value> to a Local<Number>, we must use the
    casting syntax here. There is good reason for this (involving type coercion), but
    let’s defer that to Chapter 2 where we’ll dive into the data types further.
    Line 29 is where we invoke the callback - using the Call method. Call accepts
    three parameters:
    1. Receiver - which is the JavaScript object that this will be bound to when
    this JavaScript callback is invoked. We are setting this to null, which will
    just set this to whatever the default is within the JavaScript code.
    2. Number of Arguments - zero in this case, but would correspond to the
    number of parameters we will pass to the callback when it is executed.
    3. Arguments - null here because we aren’t passing any arguments - otherwise
    we’d be passing in an array of Local<Value> objects.
    On execution, we’ll call whatever function was passed into CallThis’s first
    parameter.
*/

void Method(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<Function> cb = Local<Function>::Cast(args[0]);
    Local<String> name = Local<String>::Cast(args[1]);

    if(args[1]->IsFunction()) {
        return;
    }

    Local<Value> argv[1] = {args[1]};

    cb->Call(Null(isolate), 1, argv);
    return; // undefined returned to JavaScript
    
}

void init(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "foo", Method);
}

NODE_MODULE(callback_addon, init)