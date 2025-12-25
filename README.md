# Sum a large array using multi-thread

Run the test with and without multi-thread, and compare the results.

## How to test
```
g++ -std=c++20 main.cpp -o main
```

## Result

When hardware_concurrency is only 8, the difference is small, non-thread costs even less time than thread.

```
total = 200000000, time (without threading) = 1268486us
total = 200000000, time (with threading) = 1328360us
```

But when hardware_concurrency is 20, the benefit is quite significant:

```
total = 200000000, time (without threading) = 610471us
total = 200000000, time (with threading) = 74044us
```