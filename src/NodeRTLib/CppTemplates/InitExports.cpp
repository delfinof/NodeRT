﻿    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New)
      //localRef = Persistent<FunctionTemplate>::New(FunctionTemplate::New(New));
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("@(Model.Name)").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      @if(Model.MemberASyncMethods.Length > 0 || Model.StaticASyncMethods.Length > 0)
      {
      @:Local<Value> asyncSymbol = Nan::New<String>("__winRtAsync__").ToLocalChecked();
      @:Local<Function> func;
      @:Local<FunctionTemplate> funcTemplate;
      }
      @if(Model.MemberSyncMethods.Length > 0) {
      @:
      foreach(var method in Model.MemberSyncMethods) {
      @:Nan::SetPrototypeMethod(localRef, "@(TX.Uncap(TX.CSharpMethodToCppMethod(method.Name)))", @(TX.CSharpMethodToCppMethod(method.Name));
        }
      @:
      }
      @if(Model.MemberASyncMethods.Length > 0) {
      @:
      foreach(var method in Model.MemberASyncMethods) {
      @:funcTemplate = Nan::New<FunctionTemplate>(@TX.CSharpMethodToCppMethod(method.Name)).ToLocalChecked();
      @:func = Nan::GetFunction(funcTemplate).ToLocalChecked();
      @:Nan::ForceSet(func, asyncSymbol, True(), PropertyAttribute::DontEnum);
      @:Nan::SetPrototype(localRef, Nan::New<String>("@(TX.Uncap(TX.CSharpMethodToCppMethod(method.Name)))").ToLocalChecked(), func);
        }
      @:
      }
      @if(Model.HasMemberEvents) {  
      @:
      @:Local<Function> addListenerFunc = Nan::GetFunction(Nan::New<FunctionTemplate>(AddListener).ToLocalChecked()).ToLocalChecked();
      @:Nan::SetPrototype(localRef, Nan::New<String>("addListener").ToLocalChecked(), addListenerFunc);
      @:Nan::SetPrototype(localRef, Nan::New<String>("on").ToLocalChecked(), addListenerFunc);
      
      @:Local<Function> removeListenerFunc = Nan::GetFunction(Nan::New<FunctionTemplate>(RemoveListener).ToLocalChecked()).ToLocalChecked();
      @:Nan::SetPrototype(localRef, Nan::New<String>("removeListener").ToLocalChecked(), removeListenerFunc);
      @:Nan::SetPrototype(localRef, Nan::New<String>("off").ToLocalChecked(), removeListenerFunc);
      }
      @if(Model.MemberProperties.Length > 0) {
      @:
      foreach(var prop in Model.MemberProperties) {
        var propName = TX.Uncap(prop.Name);
      if (prop.GetSetMethod() != null) {
      @:Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("@(propName)").ToLocalChecked(), @(prop.Name)Getter, @(prop.Name)Setter);
      }
      else {
      @:Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("@(propName)").ToLocalChecked(), @(prop.Name)Getter);
      }
      }}
      
      Local<Function> constructor = Nan::GetFunction(localRef).ToLocalChecked();

      @{
        if(Model.StaticSyncMethods.Length > 0) {
        foreach(var method in Model.StaticSyncMethods) {
      @:Nan::SetMethod(constructor, "@(TX.Uncap(TX.CSharpMethodToCppMethod(method.Name)))", @TX.CSharpMethodToCppMethod(method.Name));
          }
        }
        if(Model.StaticASyncMethods.Length > 0) {
          foreach(var method in Model.StaticASyncMethods) {
      @:func = Nan::GetFunction(Nan::New<FunctionTemplate>(@TX.CSharpMethodToCppMethod(method.Name)).ToLocalChecked()).ToLocalChecked();
      @:Nan::Set(func,->Set(asyncSymbol, True(), PropertyAttribute::DontEnum);
      @:Nan::Set(constructor, Nan::New<String>("@(TX.Uncap(TX.CSharpMethodToCppMethod(method.Name)))").ToLocalChecked(), func);
          }
        }

        if(Model.StaticProperties.Length > 0) {
          foreach(var prop in Model.StaticProperties) {
            var propName = TX.Uncap(prop.Name);
            if (prop.GetSetMethod() != null) 
            {
      @:Nan::SetAccessor(constructor, Nan::New<String>("@(propName)").ToLocalChecked(), @(prop.Name)Getter, @(prop.Name)Setter);
            }
            else 
            {
      @:Nan::SetAccessor(constructor, Nan::New<String>("@(propName)").ToLocalChecked(), @(prop.Name)Getter);
            }
          }
        }

        if (Model.HasStaticEvents)
        {
      @:
          if (!Model.HasMemberEvents)
          {
      @:Local<Function> addListenerFunc = Nan::GetFunction(Nan::New<FunctionTemplate>(AddListener).ToLocalChecked()).ToLocalChecked();
          }
      @:Nan::Set(constructor, Nan::New<String>("addListener").ToLocalChecked(), addListenerFunc);
      @:Nan::set(constructor, Nan::New<String>("on").ToLocalChecked(), addListenerFunc);
            
          if (!Model.HasMemberEvents)
          {
      @:Local<Function> removeListenerFunc = Nan::GetFunction(Nan::New<FunctionTemplate>(RemoveListener).ToLocalChecked()).ToLocalChecked();
          }
          
      @:Nan::Set(constructor, Nan::New<String>("removeListener").ToLocalChecked(), removeListenerFunc);
      @:Nan::Set(constructor, Nan::New<String>("off").ToLocalChecked(), removeListenerFunc);
        }
      }
      @Nan::Set(exports, Nan::New<String>("@(Model.Name)").ToLocalChecked(), constructor);
    }
