// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: ns.proto
#ifndef GRPC_ns_2eproto__INCLUDED
#define GRPC_ns_2eproto__INCLUDED

#include "ns.pb.h"

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

namespace ns {

class NetStats final {
 public:
  static constexpr char const* service_full_name() {
    return "ns.NetStats";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status GetNetStats(::grpc::ClientContext* context, const ::ns::Request& request, ::ns::Response* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ns::Response>> AsyncGetNetStats(::grpc::ClientContext* context, const ::ns::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ns::Response>>(AsyncGetNetStatsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ns::Response>> PrepareAsyncGetNetStats(::grpc::ClientContext* context, const ::ns::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ns::Response>>(PrepareAsyncGetNetStatsRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void GetNetStats(::grpc::ClientContext* context, const ::ns::Request* request, ::ns::Response* response, std::function<void(::grpc::Status)>) = 0;
      virtual void GetNetStats(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::ns::Response* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void GetNetStats(::grpc::ClientContext* context, const ::ns::Request* request, ::ns::Response* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void GetNetStats(::grpc::ClientContext* context, const ::ns::Request* request, ::ns::Response* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void GetNetStats(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::ns::Response* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void GetNetStats(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::ns::Response* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
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
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ns::Response>* AsyncGetNetStatsRaw(::grpc::ClientContext* context, const ::ns::Request& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ns::Response>* PrepareAsyncGetNetStatsRaw(::grpc::ClientContext* context, const ::ns::Request& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status GetNetStats(::grpc::ClientContext* context, const ::ns::Request& request, ::ns::Response* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ns::Response>> AsyncGetNetStats(::grpc::ClientContext* context, const ::ns::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ns::Response>>(AsyncGetNetStatsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ns::Response>> PrepareAsyncGetNetStats(::grpc::ClientContext* context, const ::ns::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ns::Response>>(PrepareAsyncGetNetStatsRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void GetNetStats(::grpc::ClientContext* context, const ::ns::Request* request, ::ns::Response* response, std::function<void(::grpc::Status)>) override;
      void GetNetStats(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::ns::Response* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void GetNetStats(::grpc::ClientContext* context, const ::ns::Request* request, ::ns::Response* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void GetNetStats(::grpc::ClientContext* context, const ::ns::Request* request, ::ns::Response* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void GetNetStats(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::ns::Response* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void GetNetStats(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::ns::Response* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
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
    ::grpc::ClientAsyncResponseReader< ::ns::Response>* AsyncGetNetStatsRaw(::grpc::ClientContext* context, const ::ns::Request& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::ns::Response>* PrepareAsyncGetNetStatsRaw(::grpc::ClientContext* context, const ::ns::Request& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_GetNetStats_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status GetNetStats(::grpc::ServerContext* context, const ::ns::Request* request, ::ns::Response* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_GetNetStats : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_GetNetStats() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_GetNetStats() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetNetStats(::grpc::ServerContext* /*context*/, const ::ns::Request* /*request*/, ::ns::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetNetStats(::grpc::ServerContext* context, ::ns::Request* request, ::grpc::ServerAsyncResponseWriter< ::ns::Response>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_GetNetStats<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_GetNetStats : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_GetNetStats() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc_impl::internal::CallbackUnaryHandler< ::ns::Request, ::ns::Response>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::ns::Request* request, ::ns::Response* response) { return this->GetNetStats(context, request, response); }));}
    void SetMessageAllocatorFor_GetNetStats(
        ::grpc::experimental::MessageAllocator< ::ns::Request, ::ns::Response>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(0);
    #endif
      static_cast<::grpc_impl::internal::CallbackUnaryHandler< ::ns::Request, ::ns::Response>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_GetNetStats() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetNetStats(::grpc::ServerContext* /*context*/, const ::ns::Request* /*request*/, ::ns::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* GetNetStats(
      ::grpc::CallbackServerContext* /*context*/, const ::ns::Request* /*request*/, ::ns::Response* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* GetNetStats(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::ns::Request* /*request*/, ::ns::Response* /*response*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_GetNetStats<Service > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_GetNetStats<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_GetNetStats : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_GetNetStats() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_GetNetStats() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetNetStats(::grpc::ServerContext* /*context*/, const ::ns::Request* /*request*/, ::ns::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_GetNetStats : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_GetNetStats() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_GetNetStats() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetNetStats(::grpc::ServerContext* /*context*/, const ::ns::Request* /*request*/, ::ns::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetNetStats(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_GetNetStats : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_GetNetStats() {
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
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->GetNetStats(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_GetNetStats() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetNetStats(::grpc::ServerContext* /*context*/, const ::ns::Request* /*request*/, ::ns::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* GetNetStats(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* GetNetStats(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetNetStats : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_GetNetStats() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::ns::Request, ::ns::Response>(
            [this](::grpc_impl::ServerContext* context,
                   ::grpc_impl::ServerUnaryStreamer<
                     ::ns::Request, ::ns::Response>* streamer) {
                       return this->StreamedGetNetStats(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_GetNetStats() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetNetStats(::grpc::ServerContext* /*context*/, const ::ns::Request* /*request*/, ::ns::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetNetStats(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::ns::Request,::ns::Response>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_GetNetStats<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_GetNetStats<Service > StreamedService;
};

}  // namespace ns


#endif  // GRPC_ns_2eproto__INCLUDED