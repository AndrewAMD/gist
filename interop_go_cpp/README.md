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
golang thd_id:  10712
Cpp thd_id: 10712

0
golang thd_id:  5756
1
golang thd_id:  5756
2
golang thd_id:  5756
3
golang thd_id:  5756
4
golang thd_id:  5756
golang thd_id:  10712
return
5
golang thd_id:  5756
6
golang thd_id:  5756
7
golang thd_id:  5756
8
golang thd_id:  5756
9
golang thd_id:  5756
10
golang thd_id:  5756

C:\Users\normal\source\repos\education\hello_go\Debug\hello_go.exe (process 8344) exited with code 0.
Press any key to close this window . . .
```
