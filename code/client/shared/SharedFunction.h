#pragma once

template<class T>
struct shared_function
{
    std::shared_ptr<F> f;
    shared_function() = default;
    shared_function(F&& f_)
            : f(std::make_shared<F>(std::move(f_)))
    {
    }
    shared_function(shared_function const&) = default;
    shared_function(shared_function&&) = default;
    shared_function& operator=(shared_function const&) = default;
    shared_function& operator=(shared_function&&) = default;

    template<class... As>
    auto operator()(As&&... as) const
    {
        return (*f)(std::forward<As>(as)...);
    }
};

template<class F>
shared_function<std::decay_t<F>> make_shared_function(F&& f)
{
    return { std::forward<F>(f) };
}