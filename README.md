# N queens parallel implementation

## Compile

### Parallel

```
g++ src/nreinasm.cpp -o build/main -fopenmp
```

### NonParallel

```
g++ src/npnreinas.cpp -o build/npmain
```

## Run

### Parallel

```
./build/main 4
```

### NonParallel

```
./build/npmain 14
```
