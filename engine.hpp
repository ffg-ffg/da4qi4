#ifndef DAQI_ENGINE_HPP
#define DAQI_ENGINE_HPP

#include <memory>

#include <list>
#include <vector>

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

namespace da4qi4
{

class IOContextPool
    : private boost::noncopyable
{
public:
    explicit IOContextPool(std::size_t pool_size = 0);

    void Run();
    void Stop();
    void Wait();

    size_t Size() const
    {
        return _io_contexts.size();
    }

    boost::asio::io_context& GetIOContext();

private:
    using IOContextPtr = std::shared_ptr<boost::asio::io_context>;
    using IOContextWork = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;

    bool _stopping = false;
    std::vector<IOContextPtr> _io_contexts;
    std::list<IOContextWork> _work;
    std::size_t _next_index;

    std::vector<std::shared_ptr<std::thread>> _threads;
};

} //namespace da4qi4
#endif // DAQI_ENGINE_HPP
