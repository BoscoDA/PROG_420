# Compile Instructions

## 1). CMake and Build Directory (REQUIRES cmake 3.1 or higher!!)

Navigate to the Euchre folder, once ther run the following command to create and navigate to a build folder"

```
mkdir build && cd build
```

Once in the build folder run the following commands in order:

```
cmake ../
```

```
make
```

```
./Euchre
```

## 2). Docer File

Navigate to the Euchre folder and fun the following commands to run it as a Docker container:

```
docker build . -t cpp2:Euchre
```

```
docker run cpp2:Euchre
```
