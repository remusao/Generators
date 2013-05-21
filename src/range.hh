#ifndef RANGE_HH_
# define RANGE_HH_

#include <assert.h>
#include "yield.hh"
#include "generator.hh"
#include "coroutine.hh"

namespace generator
{
	namespace
	{
		template <bool Reverse>
		struct __RangeFunctor
		{
			private:
				long long int accu_;
				long long int stop_;
				long long int step_;
				coroutine __coroutine;

			public:
				__RangeFunctor() = delete;
				__RangeFunctor(const __RangeFunctor&) = default;
				__RangeFunctor& operator=(const __RangeFunctor&) = delete;

				__RangeFunctor(__RangeFunctor&&) = default;
				__RangeFunctor& operator=(__RangeFunctor&&) = default;
				__RangeFunctor(long long int start, long long int  stop, long long int step)
					: accu_(start), stop_(stop), step_(step)
				{
				}
				long long int operator()();
		};

		template <>
		long long int
		__RangeFunctor<false>::operator()()
		{
			reenter(this->__coroutine)
			{
				for (; accu_ < stop_; accu_ += step_)
					yield return accu_;
			}
			throw __EndOfGenerator();
		}

		template <>
		long long int
		__RangeFunctor<true>::operator()()
		{
			reenter(this->__coroutine)
			{
				for (; accu_ > stop_; accu_ += step_)
					yield return accu_;
			}
			throw __EndOfGenerator();
		}
	};


    //
    // Exports two generators
    //

	__Generator<long long int> range(long long int start, long long int stop, long long int step)
	{
		// formula r[i] = start + step*i where i >= 0 and r[i] < stop.
		assert(step != 0);

		if (step < 0)
		{
			assert(stop < start);
			return __Generator<long long int>(__RangeFunctor<true>(start, stop, step));
		}
		else
		{
			assert(stop > start);
			return __Generator<long long int>(__RangeFunctor<false>(start, stop, step));
		}
	}

	__Generator<long long int> range(long long int stop)
	{
		return range(0, stop, 1);
	}
}

#include "unyield.hh"

#endif /* !RANGE_HH_ */
