# N queens parallel implementation

## Compile

### Parallel

```
g++ src/nreinasm.cpp -o build/main -fopenmp -O2
```

### NonParallel

```
g++ src/npnreinas.cpp -o build/npmain
```

## Run

### Parallel

```
time ./build/main 12
```

### NonParallel

```
time ./build/npmain 12
```

## Results

With 12 queens

Parallel

![Parallel](images/parallel.png)

NonParallel

![Non Parallel](images/nonparallel.png)
