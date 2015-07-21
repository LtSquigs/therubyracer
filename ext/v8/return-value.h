// -*- mode: c++ -*-
#ifndef RR_RETURN_VALUE_H
#define RR_RETURN_VALUE_H

namespace rr {

  class ReturnValue {
  public:

    template <class T>
    class Base : public Wrapper<v8::ReturnValue<T>> {
    public:

      Base(v8::ReturnValue<T> value) : Wrapper<v8::ReturnValue<T>>(value) {}
      Base(VALUE self) : Wrapper<v8::ReturnValue<T>>(self) {}

      static VALUE GetIsolate(VALUE self) {
        Base<T> ret(self);
        return Isolate(ret->GetIsolate());
      }

    };

    class Value : public Base<v8::Value> {
    public:

      Value(v8::ReturnValue<v8::Value> value) : Base(value) {}
      Value(VALUE self) : Base(self) {}

      static VALUE Set(VALUE self, VALUE handle) {
        Value ret(self);
        Locker lock(ret->GetIsolate());
        v8::Local<v8::Value> value((rr::Value(handle)));
        ret->Set(value);
        return Qnil;
      }

      static VALUE Set_bool(VALUE self, VALUE value) {
        Value ret(self);
        Locker lock(ret->GetIsolate());
        ret->Set((bool)Bool(value));
        return Qnil;
      }

      static VALUE Set_double(VALUE self, VALUE value) {
        Value ret(self);
        Locker lock(ret->GetIsolate());
        ret->Set(NUM2DBL(value));
        return Qnil;
      }

      static VALUE Set_int32_t(VALUE self, VALUE i) {
        Value ret(self);
        Locker lock(ret->GetIsolate());
        ret->Set(NUM2INT(i));
        return Qnil;
      }

      static VALUE Set_uint32_t(VALUE self, VALUE i) {
        Value ret(self);
        Locker lock(ret->GetIsolate());
        ret->Set(NUM2UINT(i));
        return Qnil;
      }

      static VALUE SetNull(VALUE self) {
        Value ret(self);
        Locker lock(ret->GetIsolate());
        ret->SetNull();
        return Qnil;
      }

      static VALUE SetUndefined(VALUE self) {
        Value ret(self);
        Locker lock(ret->GetIsolate());
        ret->SetUndefined();
        return Qnil;
      }

      static VALUE SetEmptyString(VALUE self) {
        Value ret(self);
        Locker lock(ret->GetIsolate());
        ret->SetEmptyString();
        return Qnil;
      }

      static inline void Init() {
        ClassBuilder("Value", ReturnValue::Class, ReturnValue::Class).
          defineMethod("Set", &Set).
          defineMethod("Set_bool", &Set_bool).
          defineMethod("Set_double", &Set_double).
          defineMethod("Set_int32_t", &Set_int32_t).
          defineMethod("Set_uint32_t", &Set_uint32_t).
          defineMethod("SetNull", &SetNull).
          defineMethod("SetUndefined", &SetUndefined).
          defineMethod("SetEmptyString", &SetEmptyString).
          defineMethod("GetIsolate", &GetIsolate).
          store(&Class);
      }

    };

    class Void : public Base<void> {
    public:

      Void(v8::ReturnValue<void> value) : Base(value) {}
      Void(VALUE self) : Base(self) {}

      static inline void Init() {
        ClassBuilder("Void", ReturnValue::Class, ReturnValue::Class).
          defineMethod("GetIsolate", &GetIsolate).
          store(&Class);
      }

    };

    static VALUE Class;

    static void Init() {
      ClassBuilder("ReturnValue").
        store(&Class);

      Value::Init();
      Void::Init();
    }

  };
}
#endif /* RR_RETURN_VALUE_H */