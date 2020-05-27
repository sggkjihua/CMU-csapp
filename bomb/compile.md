- lea, load effective address, 加载有效地址. 指令形式是从存储器读数据到寄存器, 效果是将存储器的有效地址写入到目的操作数, 简单说, 就是C语言中的”&”.

  ```
  movl $foo, %edi
  leal foo, %edi
  ```

- 同时, lea还有个很有用但同时又很难理解的用法, 例如这样:

  ```
  leal 5(%edx, %edx, 2), %eax
  ```

  假设%edx的值为x, 上面这行会将%eax的值设置为”3x+5”.

- jmp 是无条件跳转

-  ADD A,B  

  A=A+B; 前面的作为destination

- CMP A,B

  如果相等则置为1，否则置为0

- `je` 指令【Jump if Equals】在**ZF**被置位时跳转。`je` 是 `jz` 【Jump if Zero】的别名

  所以就是当结果为0的时候跳转

- JG	大于跳转（若 leftOp > rightOp）



#### 设置断点

根据行的位置进行断点设置

b *0x400f3a



打印寄存器里面的值

p $rsp



打印内存地址里面的值

x/1u 0x12341