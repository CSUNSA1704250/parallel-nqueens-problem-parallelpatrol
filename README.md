# N queens parallel implementation

## Compile

### Parallel

```
g++ src/nqueens.cpp -o build/main -fopenmp

```

### NonParallel

```
g++ src/npnreinas.cpp -o build/npmain
```

## Run

### Parallel

```
time ./build/main find 12
```
```
time ./build/main all 12 
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
