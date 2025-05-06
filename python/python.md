# Python

## 0 入门

### 0.1 字符串打印

> python中单双引号都可以用来表示字符串
>
> c或Java中 **单引号**表示字符(char) **双引号**表示字符串(string)

测试程序：
```python
print("Hello Python")
```


**单双引号转义**：
```python
print("He said 'hello'")
print('He said "hello"')
print('\'s : \"teacher\'s\"')
```

**换行打印字符串**：
Python为解释型语言，会一行一行的解释代码
```python
# print("nihao\n
#       nihao") 会报错

#可以通过\结尾来进行 代码换行
print("nihao1212\
haha")
```

除了三引号外换行只能使用 \n 转移换行符来进行
```python
print("nihao"
      "nihao")
print("nihao" + "nihao")
print("nihao\nnihao")
```

**`'''`三引号中内容可以自动换号**:
```python
print('''第一行
    第二行
    第三行哈哈哈''')
print("""第一行
    第二行
    第三行哈哈哈""")
```

**注意：打印输出时类型必须一致**
```py
print(str(5 + 10) +"#")
```

**字符串格式化**：

> 通过format方法进行赋值，**数值类型**无需手动转换为字符串就可以打印

在字符中通过添加`{参数编号}`来对相应位置进行占位，之后通过`format(args...)`函数**对照相应顺序**来为对应位置进行替换
> `{}`中数字从0开始

通过关键字占位，**无需考虑顺序**

通过在字符串前加`f`来使得字符串内部关键字被自动识别赋值

> 打印浮点型小数时`{占位关键字:.2f}`可以对对应位置的浮点数进行保留两位小数的处理

```py
# 通过字符串中format方法进行字符串格式化
print("""祝贺{0}，
新年快乐，
万事吉祥，
{1}""".format("朋友们","平平安安"))

# 也可以通过关键词来进行相应替换
print("""祝贺{name}，
新年快乐，
万事吉祥，
{msg}""".format(msg="万事如意",name="朋友们"))

# 通过在字符串前加f，使字符串内关键字被自动识别赋值
year = "2025"
msg1 = "平平安安"
msg2 = "快快乐乐"
message = f"""
祝大家在{year}年，
{msg1}，
{msg2}
"""
print(message1)

message2 = f"祝大家在{year}年，{msg1}，{msg2}"
print(message2)
```

---

### 0.2 变量

变量：数字，字母，下划线组成 数字不能开头
不能重名，区分大小写，不能与关键字重名
```python
my_var = "第一个变量"
print("my_var = " + my_var)
```

> python从上到下进行解释，因此必须在使用前将被使用的变量创建

**python变量命名规范**：
- 下划线命名法：字母全小写，不同单词间用下划线(_)分隔 (在python中常用)
- 驼峰命名法：单词首字母大写分隔

> 下划线命名法通常用于**变量**
> 
> 驼峰命名法通常用于**类**

---

### 0.3 数学计算

支持`+` `-` `*` `/` 

`//`向下取整

乘方用`**`表示
- 5的3次方：`5 ** 3`

> 可以引入math库 来使用更多的数学函数

```python
# 在python头部添加
import math
```

案例使用：

计算
$$-b \pm \sqrt{(b^2 - 4 * a * c)}$$

```python
import math

# 计算案例
a = -1
b = -2
c = 3
result1 = -b + (b ** 2 - 4 * a * c) ** (1/2)
# 开根可以使用1/2次方，也可以使用math库中的 sqrt() 函数
result2 = -b - math.sqrt(b ** 2 - 4 * a * c)

print(result1)
print(result2)
```

---

### 0.4 注释

可以使用 `#` 来进行单行注释

> 三引号实现注释原理就是**将内容变为字符串**，不去使用就对不会影响程序输出结果

也可以使用`'''` 或 `"""` 三引号来进行~~多行注释~~

---

### 0.5 数据类型

> Python 是动态类型语言，变量的数据类型由赋给它的值自动确定。

**1. 基本数据类型**
- 整数 (`int`)
表示整数值，如 5, -3, 1000。
> Python 3 的 int 可以表示任意大小的整数（不受位数限制）。

- 浮点数 (`float`)
表示带小数点的数字，如 3.14, -0.001, 2.0。
也可以用科学计数法表示，如 1.5e2（即 150.0）。

- 布尔值 (`bool`)
表示逻辑值：`True` 或 `False`（注意首字母大写）。
> 本质上是 int 的子类，True == 1，False == 0。

- 复数 (`complex`)
表示复数，如 3 + 4j，其中 j 是虚数单位。

**2. 序列类型**
- 字符串 (`str`)
表示文本，用单引号 `'hello'`、双引号 `"world"` 或三引号 `'''多行字符串'''` 定义。
> **支持索引（如 s[0]）**、切片（如 s[1:3]）和不可变性（不能直接修改字符）。

- 列表 (`list`)
有序的可变序列，用方括号定义，如 [1, 2, 'a']。
> 支持增删改操作（如 append(), remove()）。

- 元组 (`tuple`)
有序的不可变序列，用圆括号定义，如 (1, 2, 'a')。
> 一旦创建不能修改，常用于固定数据（如坐标 (x, y)）。

**3. 映射类型**
- 字典 (`dict`)
键值对的集合，用花括号定义，如 {'name': 'Alice', 'age': 25}。
> 键必须是不可变类型（如 str, int, tuple），值可以是任意类型。

**4. 集合类型**
- 集合 (`set`)
无序的唯一元素集合，用花括号定义，如 {1, 2, 3}。
> 支持集合运算（并集、交集等），可变。

- 不可变集合 (`frozenset`)
不可变的集合，**创建后不能修改**。

**5. 其他类型**
- 空值 (`NoneType`)
表示空值或缺失值，**唯一实例是 None**。
> 在创建一个变量需要初始化，但不知道该变量具体值类型时，可以赋值为`None`

- 二进制类型

  - `bytes`：不可变字节序列，如 b'hello'。

  - `bytearray`：可变字节序列。

  - `memoryview`：用于直接操作二进制数据的内存视图。

**6. 特殊类型**
- 自定义类 (`class`)
- 用户定义的类实例也是数据类型。

**type函数**：
可以通过 `type()` 函数来判断该变量的类型，以此来确定该变量可以使用哪些类型所具有的函数
```python
print(type(b1)) # <class 'bool'>
print(len(b1)) # len函数不能用在bool类型上吗，报错！
```

**类型转换**：`要转换的类型(要转换的内容)`
```py
a = "32"
a_num = int(32) # a_num为int类型
```

---

### 0.6 运行模式

python有**命令行模式**和**交互模式**两种模式

> **命令行模式**：在文件中编写代码并最后运行

**命令行模式**：保存写好的代码并允许整个文件，py解释器一行一行执行，最后一起展示

> **交互模式**：在cmd终端通过python命令运行，之后键入相应指令来进行实时交互

**交互模式**：无需创建文件，输入一行，解释一行，无需 **print()** 函数打印即可显示结果，但指令不会被保存，退出即消失

---

### 0.7 输入

python通过`input()`函数进行输入操作

`input("提示内容")`
**参数**：为**提示内容**，
**返回值**：用来接收**输入内容**，输入内容一律为**字符串类型**，在变量接收后需要**手动进行类型转换**

```py
a = input("Please input a :")
print("a + 10 = " + str(int(a) + 10))
```

---

### 0.8 条件语句

**条件语句：**

语法：
```
if [条件]:
    [执行语句]
    [执行语句]
    ...
else:
    [执行语句]
    [执行语句]
    ...
```
需要**保证有缩进**，来区分`if`或`else`中的执行语句是否结束

**条件**：bool类型值，条件表达式，bool类型变量
**条件表达式**：由`==` `!=` `<` `<=` `>` `>=`组成的表达式 如：`x == 4`

测试案例：
```py
# 根据输入的心情指数判断今晚是否打游戏
mood_condition = input("今天心情指数(0-100)：")

if int(mood_condition) >= 60:
    print("打游戏")
else :
    print("不打游戏")
```

**条件语句嵌套：**

语法：
```
if [C1]:
    if [C2]:
        [执行语句A]
        ...
    else:
        [执行语句B]
        ...
else:
    [执行语句C]
    ...
```
|C1|C2|执行语句|
|:--|:--|:--|
|C1为True | C2为True | 执行语句A|
|C1为True | C2为False | 执行语句B|
|C1为False | C2为True或False | 执行语句C|

**多条件语句：**

语法：
```
if [C1]:
    [执行语句A]
    ...
elif [C2]:
    [执行语句B]
    ...
else:
    [执行语句C]
    ...
```
|C1|执行语句|
|---|---|
|C1 为True | 执行语句A|
|C2 为True | 执行语句B|
|C1 and C2为False | 执行语句C|

**多条件优化方案**：

> 有别于Java和C：`&&`(与) `||`(或) `!`(非)
> `&` `|` (逻辑执行完之后会继续向后执行) 

逻辑运算符：`and`(与) `or`(或) `not`(非)

使用逻辑运算符进行优化条件：

---

### 0.9 列表

**列表**：可变长，可以存放不同类型数据，可以通过索引访问操作

```py
# 列表声明
blank_list = []  # 空列表
shopping_list = ["键盘", "鼠标"]
```

**列表常规操作**：
```py
# 列表声明
shopping_list = ["键盘", "鼠标"]
print(shopping_list)

shopping_list.append("显示器")
print(shopping_list)

shopping_list.remove("鼠标")
print(shopping_list)

print(len(shopping_list))  # 列表元素数量

print(shopping_list[0])  # 根据索引获取元素

shopping_list[0] = "鼠标"  # 根据索引直接修改对应元素
print(shopping_list)
```

**列表特殊案例**：

元素全为数字时可以进行以下操作
```py
# 元素全为数字时可以进行以下操作
num_list = [1, 13, -7, 2, 9]
print(num_list)
print(max(num_list)) # 最大值
print(min(num_list)) # 最小值
print(sum(num_list)) # 和
print(sorted(num_list)) # 默认从小到大，可以通过reverse参数修改规则
```

---

### 0.10 字典

**字典**： 内部通过键值对实现
**键**：必须为不可变类型，**键唯一**
```py
contacts = {"张伟" : "1234567890",
            "李四" : "9231154321",
            "王五" : "1387654321"}
print(contacts)
```

字典常见操作：
```py
# 更新和添加
contacts["王五"] = "0000000000" # 若该键已存在，则将原值覆盖
contacts["王五1"] = "0000000000" # 若该键不存在，则将该键和值添加到字典中
print(contacts)

# 判断该键在字典中是否已存在，返回bool值
print("张伟" in contacts) # True

# 删除键值对，若不存在则报错
del contacts["王五1"]
print(contacts)

# 查看字典中键值对个数
print(len(contacts))

# 返回字典中所有的键
print(contacts.keys())

# 返回字典中的所有值
print(contacts.values())

# 返回字典中的所有键值对
print(contacts.items())
```

若字典中有**重名的键**，此时可以通过元组(tuple)来存储进行区分
列表可变不能使用，因此使用元组(tuple)
> 元组的定义用`()`，列表定义用`[]`，字典定义用`{}`
```py
ep_tuple1 = ("张伟", 18)
ep_tuple2 = ("张伟", 24)
ep_tuple3 = ("张伟", 35)
# 键不能为列表（键必须为不可变长）
# ep_contacts1 = {["张伟",1]:"1234",
#                 ["张伟",2]:"1234",
#                 ["张伟",3]:"1234"}
ep_contacts = {ep_tuple1 : "1234567890",
               ep_tuple2 : "1231241567",
               ep_tuple3 : "1387654321"}
print(ep_contacts)
```

---

### 0.11 循环语句

**for循环**：
语法：
```
for 变量名 in 可迭代对象:
    # 对每个变量做一些事
    # ...
```
for下缩进的语句会被包裹进for循环结构内

for循环时，遍历字典时，会将每个键值对赋值到元组变量中
```py
# for循环
temperature_dict = {"1":36.8,
                    "2":35.7,
                    "3":34.6}

# 将字典中的每个键值对赋值在元组变量中
for temperature_tuple in temperature_dict.items():
    temperature_id = temperature_tuple[0]
    temperature = temperature_tuple[1]
    print(temperature_id, temperature)

# 将字典中的每个键值对分别赋值在对应key，value变量中
for key, value in temperature_dict.items():
    print(key, value)
```
**注意**：因为字典的键为必须为不可变长类型，且唯一，因此使用 **元组(tuple)** 来存储键值对

**for在规定范围内循环语法**：

**range()函数**：
- `range(stop)`
- `range(start,stop[,step])`

**参数**：
**start**: 计数从 start 开始。默认是从 0 开始。
> 例如 range(5) 等价于 range(0， 5)

**stop**: 计数到 stop 结束，但不包括 stop。
> 例如：range(0， 5) 是 [0, 1, 2, 3, 4] 没有 5

**step**：步长，默认为 1。
> 例如：range(0， 5) 等价于 range(0, 5, 1)

```
# 遍历 [0,a) 区间，从0开始，每次+1，直到a-1
for 变量名 in range(a):
    # 对每个变量做一些事
    # ... 

# 遍历 [a,b) 区间，从a开始，每次+1，直到b-1
for 变量名 in range(a,b):
    # 对每个变量做一些事
    # ... 

# 遍历 [a,b) 区间，从a开始，每次+c，直到b-1
for 变量名 in range(a,b,c):
    # 对每个变量做一些事
    # ... 
```

---

**while循环**：
语法：
```
# 若条件A为True，则进入循环，否则跳出循环
while 条件A:
    行动B
```

例子：
```py
# while循环
# 打印您输入的所有值之和的平均值
total = 0
count = 0
user_input = input("Enter a number(type q to quit): ")
while user_input != 'q' :
    num = float(user_input)
    total += num
    count += 1
    user_input = input("Enter a number(type q to quit): ")
if count == 0:
    result = 0
else:
    result = total / count

print("The avg of sum you type is：" + str(result))
```

---

### 0.12 函数

定义函数语法：
```
# 参数 和 返回值 都可以省略
def func_name([args...]):
    # 函数体代码
    # ...
    # [return ...] 若不写，默认返回None
```

例子：
```py
# 计算矩形面积
def calculate_rectangle_area(width, height):
    area = width * height
    print(f"此时矩形面积为：{area}")
    # return area

calculate_rectangle_area(4,5)
# print(calculate_rectangle_area(4,5))
```

---

### 0.13 引入模块

python中常用的函数为内置函数

若要使用实现某些功能的函数，但内置函数无法满足时，可以引入其他模块，使用引入模块的库函数

**引入方式**：
- `import 模块名`
```py
import statistics

print(statistics.median([1, -78, 20])) # 打印中位数 1
```

- `from...import...语句`
```py
from statistics import median

print(median([1, -78, 20])) # 打印中位数 1
```

- `from...import *`
 
> 不推荐，因为若引入多个模块，可能会导致多模块中函数重名的现象

```py
from statistics import *

print(median([1, -78, 20])) # 打印中位数 1
```

模块分类：
- 内置模块：需要引入

> 第三方模块可以通过`pip install`命令安装

- 第三方模块：需要下载，然后再进行引入

---

### 0.14 类

类中包含：属性，方法

语法：
```
class 类名:
    # 类属性定义
    属性名 = 属性值

    # 构造方法 
    # 第一个参数永远为self，用于把属性绑定在实例对象上
    def __init__(self[, ...]):
        # 构造函数内部代码
        # ...
    
    # 类的定义相关代码
    # ...

    # 方法定义
    def 方法名(self[, ...]):
        # 方法体
        # ...

----------------------------------

# 创建对象
对象名称 = 类名(除self外的参数) # self无需手动传递 

# 获取对象属性
对象名.属性名

# 调用对象方法
对象名.方法名(形参列表)
```

创建对象时，`__init__()`构造方法被自动调用执行

**`self`用法**：在构造方法和方法上的第一个参数
```py
def __init__(self):
    self.name = "XXX" # 将对象的name属性赋值
    # name = "XXX" python只认为将 普通name 变量赋值
```

属性定义：
```py
class A:
    # 定义类属性
    attribute1 = "类属性"

    # 通过构造函数可以赋值，也可以定义动态属性
    def __init__(self, name):
        # 通过self.表示该属性属于A对象的属性
        # 该属性并未提前声明，在此声明也可行
        self.username = name
        self.attribute1 = "类属性赋值"
```
`attribute1`属性与`username`属性区别：
- `attribute1`属性：可以直接用`类名.`方式直接调用
- `username`属性：

---

