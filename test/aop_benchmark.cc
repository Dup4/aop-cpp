#include "benchmark/benchmark.h"

#include "aop/aop.h"

#include "./class/a.h"

namespace aop::test {

static void BenchmarkHello4(benchmark::State& state) {
    A a;
    for (auto _ : state) {
        int x = 1;
        a.Hello4(x);
    }
}

static void BenchmarkHello4Impl(benchmark::State& state) {
    A a;
    for (auto _ : state) {
        int x = 1;
        a.hello4(x);
    }
}

BENCHMARK(BenchmarkHello4);
BENCHMARK(BenchmarkHello4Impl);

}  // namespace aop::test
