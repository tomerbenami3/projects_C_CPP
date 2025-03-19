#ifndef MT_PAR_ALGORITHMS_HPP
#define MT_PAR_ALGORITHMS_HPP

#include "thread_pool_executor.hpp"
#include <vector>
#include <future>

namespace mt {

template <typename Container, typename MapFn, typename ReduceFn, typename ResultType>
ResultType par_map_reduce(const Container& container, 
                          MapFn map, 
                          ReduceFn reduce, 
                          ResultType initial_value, 
                          mt::ThreadPoolExecutor<10>& pool)
{
    using MappedType = decltype(map(*container.begin()));
    std::vector<std::future<MappedType>> futures;

    for (const auto& element : container) {
        auto promise = std::make_shared<std::promise<MappedType>>();
        futures.emplace_back(promise->get_future());

        pool.submit([map, element, promise]() {
            promise->set_value(map(element));
        });
    }

    ResultType result = initial_value;
    for (auto& future : futures) {
        result = reduce(result, future.get());
    }

    return result;
}

} // namespace mt

#endif // MT_PAR_ALGORITHMS_HPP