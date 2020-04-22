// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: db.proto
#ifndef GRPC_db_2eproto__INCLUDED
#define GRPC_db_2eproto__INCLUDED

#include "db.pb.h"

#include <functional>
#include <grpc/impl/codegen/port_platform.h>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace dbcontent {

class QueryDB final {
 public:
  static constexpr char const* service_full_name() {
    return "dbcontent.QueryDB";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status DoQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::dbcontent::QueryReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dbcontent::QueryReply>> AsyncDoQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dbcontent::QueryReply>>(AsyncDoQueryRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dbcontent::QueryReply>> PrepareAsyncDoQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dbcontent::QueryReply>>(PrepareAsyncDoQueryRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReaderInterface< ::dbcontent::QueryReply>> DoAllQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request) {
      return std::unique_ptr< ::grpc::ClientReaderInterface< ::dbcontent::QueryReply>>(DoAllQueryRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::dbcontent::QueryReply>> AsyncDoAllQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::dbcontent::QueryReply>>(AsyncDoAllQueryRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::dbcontent::QueryReply>> PrepareAsyncDoAllQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::dbcontent::QueryReply>>(PrepareAsyncDoAllQueryRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void DoQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest* request, ::dbcontent::QueryReply* response, std::function<void(::grpc::Status)>) = 0;
      virtual void DoQuery(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dbcontent::QueryReply* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void DoQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest* request, ::dbcontent::QueryReply* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void DoQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest* request, ::dbcontent::QueryReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void DoQuery(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dbcontent::QueryReply* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void DoQuery(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dbcontent::QueryReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void DoAllQuery(::grpc::ClientContext* context, ::dbcontent::QueryRequest* request, ::grpc::ClientReadReactor< ::dbcontent::QueryReply>* reactor) = 0;
      #else
      virtual void DoAllQuery(::grpc::ClientContext* context, ::dbcontent::QueryRequest* request, ::grpc::experimental::ClientReadReactor< ::dbcontent::QueryReply>* reactor) = 0;
      #endif
    };
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    typedef class experimental_async_interface async_interface;
    #endif
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    async_interface* async() { return experimental_async(); }
    #endif
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::dbcontent::QueryReply>* AsyncDoQueryRaw(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::dbcontent::QueryReply>* PrepareAsyncDoQueryRaw(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientReaderInterface< ::dbcontent::QueryReply>* DoAllQueryRaw(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::dbcontent::QueryReply>* AsyncDoAllQueryRaw(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::dbcontent::QueryReply>* PrepareAsyncDoAllQueryRaw(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status DoQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::dbcontent::QueryReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dbcontent::QueryReply>> AsyncDoQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dbcontent::QueryReply>>(AsyncDoQueryRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dbcontent::QueryReply>> PrepareAsyncDoQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dbcontent::QueryReply>>(PrepareAsyncDoQueryRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReader< ::dbcontent::QueryReply>> DoAllQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request) {
      return std::unique_ptr< ::grpc::ClientReader< ::dbcontent::QueryReply>>(DoAllQueryRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::dbcontent::QueryReply>> AsyncDoAllQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::dbcontent::QueryReply>>(AsyncDoAllQueryRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::dbcontent::QueryReply>> PrepareAsyncDoAllQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::dbcontent::QueryReply>>(PrepareAsyncDoAllQueryRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void DoQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest* request, ::dbcontent::QueryReply* response, std::function<void(::grpc::Status)>) override;
      void DoQuery(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dbcontent::QueryReply* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void DoQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest* request, ::dbcontent::QueryReply* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void DoQuery(::grpc::ClientContext* context, const ::dbcontent::QueryRequest* request, ::dbcontent::QueryReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void DoQuery(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dbcontent::QueryReply* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void DoQuery(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dbcontent::QueryReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void DoAllQuery(::grpc::ClientContext* context, ::dbcontent::QueryRequest* request, ::grpc::ClientReadReactor< ::dbcontent::QueryReply>* reactor) override;
      #else
      void DoAllQuery(::grpc::ClientContext* context, ::dbcontent::QueryRequest* request, ::grpc::experimental::ClientReadReactor< ::dbcontent::QueryReply>* reactor) override;
      #endif
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::dbcontent::QueryReply>* AsyncDoQueryRaw(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::dbcontent::QueryReply>* PrepareAsyncDoQueryRaw(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientReader< ::dbcontent::QueryReply>* DoAllQueryRaw(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request) override;
    ::grpc::ClientAsyncReader< ::dbcontent::QueryReply>* AsyncDoAllQueryRaw(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReader< ::dbcontent::QueryReply>* PrepareAsyncDoAllQueryRaw(::grpc::ClientContext* context, const ::dbcontent::QueryRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_DoQuery_;
    const ::grpc::internal::RpcMethod rpcmethod_DoAllQuery_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status DoQuery(::grpc::ServerContext* context, const ::dbcontent::QueryRequest* request, ::dbcontent::QueryReply* response);
    virtual ::grpc::Status DoAllQuery(::grpc::ServerContext* context, const ::dbcontent::QueryRequest* request, ::grpc::ServerWriter< ::dbcontent::QueryReply>* writer);
  };
  template <class BaseClass>
  class WithAsyncMethod_DoQuery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_DoQuery() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_DoQuery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoQuery(::grpc::ServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::dbcontent::QueryReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestDoQuery(::grpc::ServerContext* context, ::dbcontent::QueryRequest* request, ::grpc::ServerAsyncResponseWriter< ::dbcontent::QueryReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_DoAllQuery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_DoAllQuery() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_DoAllQuery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoAllQuery(::grpc::ServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::grpc::ServerWriter< ::dbcontent::QueryReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestDoAllQuery(::grpc::ServerContext* context, ::dbcontent::QueryRequest* request, ::grpc::ServerAsyncWriter< ::dbcontent::QueryReply>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(1, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_DoQuery<WithAsyncMethod_DoAllQuery<Service > > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_DoQuery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_DoQuery() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc_impl::internal::CallbackUnaryHandler< ::dbcontent::QueryRequest, ::dbcontent::QueryReply>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::dbcontent::QueryRequest* request, ::dbcontent::QueryReply* response) { return this->DoQuery(context, request, response); }));}
    void SetMessageAllocatorFor_DoQuery(
        ::grpc::experimental::MessageAllocator< ::dbcontent::QueryRequest, ::dbcontent::QueryReply>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(0);
    #endif
      static_cast<::grpc_impl::internal::CallbackUnaryHandler< ::dbcontent::QueryRequest, ::dbcontent::QueryReply>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_DoQuery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoQuery(::grpc::ServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::dbcontent::QueryReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* DoQuery(
      ::grpc::CallbackServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::dbcontent::QueryReply* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* DoQuery(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::dbcontent::QueryReply* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_DoAllQuery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_DoAllQuery() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(1,
          new ::grpc_impl::internal::CallbackServerStreamingHandler< ::dbcontent::QueryRequest, ::dbcontent::QueryReply>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::dbcontent::QueryRequest* request) { return this->DoAllQuery(context, request); }));
    }
    ~ExperimentalWithCallbackMethod_DoAllQuery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoAllQuery(::grpc::ServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::grpc::ServerWriter< ::dbcontent::QueryReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerWriteReactor< ::dbcontent::QueryReply>* DoAllQuery(
      ::grpc::CallbackServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/)
    #else
    virtual ::grpc::experimental::ServerWriteReactor< ::dbcontent::QueryReply>* DoAllQuery(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_DoQuery<ExperimentalWithCallbackMethod_DoAllQuery<Service > > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_DoQuery<ExperimentalWithCallbackMethod_DoAllQuery<Service > > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_DoQuery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_DoQuery() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_DoQuery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoQuery(::grpc::ServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::dbcontent::QueryReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_DoAllQuery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_DoAllQuery() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_DoAllQuery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoAllQuery(::grpc::ServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::grpc::ServerWriter< ::dbcontent::QueryReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_DoQuery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_DoQuery() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_DoQuery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoQuery(::grpc::ServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::dbcontent::QueryReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestDoQuery(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_DoAllQuery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_DoAllQuery() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_DoAllQuery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoAllQuery(::grpc::ServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::grpc::ServerWriter< ::dbcontent::QueryReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestDoAllQuery(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncWriter< ::grpc::ByteBuffer>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(1, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_DoQuery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_DoQuery() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(0,
          new ::grpc_impl::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->DoQuery(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_DoQuery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoQuery(::grpc::ServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::dbcontent::QueryReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* DoQuery(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* DoQuery(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_DoAllQuery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_DoAllQuery() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(1,
          new ::grpc_impl::internal::CallbackServerStreamingHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const::grpc::ByteBuffer* request) { return this->DoAllQuery(context, request); }));
    }
    ~ExperimentalWithRawCallbackMethod_DoAllQuery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoAllQuery(::grpc::ServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::grpc::ServerWriter< ::dbcontent::QueryReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerWriteReactor< ::grpc::ByteBuffer>* DoAllQuery(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/)
    #else
    virtual ::grpc::experimental::ServerWriteReactor< ::grpc::ByteBuffer>* DoAllQuery(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_DoQuery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_DoQuery() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::dbcontent::QueryRequest, ::dbcontent::QueryReply>(
            [this](::grpc_impl::ServerContext* context,
                   ::grpc_impl::ServerUnaryStreamer<
                     ::dbcontent::QueryRequest, ::dbcontent::QueryReply>* streamer) {
                       return this->StreamedDoQuery(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_DoQuery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status DoQuery(::grpc::ServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::dbcontent::QueryReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedDoQuery(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::dbcontent::QueryRequest,::dbcontent::QueryReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_DoQuery<Service > StreamedUnaryService;
  template <class BaseClass>
  class WithSplitStreamingMethod_DoAllQuery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithSplitStreamingMethod_DoAllQuery() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::SplitServerStreamingHandler<
          ::dbcontent::QueryRequest, ::dbcontent::QueryReply>(
            [this](::grpc_impl::ServerContext* context,
                   ::grpc_impl::ServerSplitStreamer<
                     ::dbcontent::QueryRequest, ::dbcontent::QueryReply>* streamer) {
                       return this->StreamedDoAllQuery(context,
                         streamer);
                  }));
    }
    ~WithSplitStreamingMethod_DoAllQuery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status DoAllQuery(::grpc::ServerContext* /*context*/, const ::dbcontent::QueryRequest* /*request*/, ::grpc::ServerWriter< ::dbcontent::QueryReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with split streamed
    virtual ::grpc::Status StreamedDoAllQuery(::grpc::ServerContext* context, ::grpc::ServerSplitStreamer< ::dbcontent::QueryRequest,::dbcontent::QueryReply>* server_split_streamer) = 0;
  };
  typedef WithSplitStreamingMethod_DoAllQuery<Service > SplitStreamedService;
  typedef WithStreamedUnaryMethod_DoQuery<WithSplitStreamingMethod_DoAllQuery<Service > > StreamedService;
};

}  // namespace dbcontent


#endif  // GRPC_db_2eproto__INCLUDED