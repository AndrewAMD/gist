# Build Command (go)

```
go build -o cdll.dll -buildmode=c-shared
```

# CPP

This only works with Win32.

Go generates a header file - this is technically not needed as long as you are using C-types.

# Output

```
hello world
0
10
20
30
40
Secret message: "hello, there!!!"
age: 34, height: 70.50"
age: 35, height: 71.50"
age: 36, height: 200.10"
doing task...
roar
task completed...
0
1
2
3
4
5
6
7
8
9
10

C:\Users\normal\source\repos\education\hello_go\x64\Debug\hello_go.exe (process 32) exited with code 0.
Press any key to close this window . . .
```
