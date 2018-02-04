#include <jvm/rtdata/exceptions.h>
#include <jvm/rtdata/runtime_const_pool.h>
#include <jvm/rtdata/symbol_ref.h>
#include <glog/logging.h>
using namespace cyh;

ExceptionHandler::ExceptionHandler(ExceptionInfo& entry, RuntimeConstPool* rt_pool)
{
    start_pc = entry.start_pc;
    end_pc = entry.end_pc;
    handler_pc = entry.handler_pc;
    if (entry.catch_type == 0) {
	catch_type = NULL;
    } else {
	catch_type = rt_pool->GetRef<ClassRef>(entry.catch_type);
    }
}

ExceptionTable::ExceptionTable(std::vector<ExceptionInfo>& exceptions, RuntimeConstPool* rt_pool)
{
    for (auto& entry : exceptions) {
	exception_handlers_.push_back(new ExceptionHandler(entry, rt_pool));
    }
}

ExceptionHandler* ExceptionTable::FindExceptionHandler(JClass* ex_class, int pc)
{
	DLOG(INFO) << "pc:" << pc;
    for (auto handler : exception_handlers_) {
	DLOG(INFO) << "handler range:(" << handler->start_pc << "," <<  handler->end_pc << ")";
	if (pc >= handler->start_pc && pc < handler->end_pc) {
	    if (handler->catch_type == NULL) {
		return handler;
	    }

	    auto catch_class = handler->catch_type->ResolveClass();
		DLOG(INFO) << "catch vs ex :" << catch_class->name() <<"#"<<ex_class->name();
	    if (catch_class == ex_class || catch_class->IsSuperClassOf(ex_class)) {
		return handler;
	    }
	}
    }
    return NULL;
}
