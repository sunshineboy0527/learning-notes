# C/C++常见小技巧
> `#include<bits/stdc++.h>`万能头

#### 数值与字符串相互转换的几种方法   P1980
先从简单的开始
```c
string to_string (int val);
string to_string (double val);
```
这是C++11新增的库函数，已重载各种标准类型，用法很简单，例如 string s = to_string(123);
但是对于大量数据只能一个数一个数转换，颇为繁琐
还有一种方法就是 stringstream 
> 使用stringstream 需包含头文件 `<sstream>`
```c
int a = 123, b = 456, c = 789;
stringstream ss;
ss << a << b << c;
//以上几行把a b c三个变量读入字符串流中，这样就可以把a b c三个变量无缝衔接起来，但是需要注意的是，stringstream型不能直接输出，也不支持迭代器，需要利用stringstream类的成员函数str()才能把它当成普通字符串来用，例如
string s = ss.str();
```

#### 统计字符串中某字符出现次数     P1980
```c
//需要引入 <algorithm>头文件
count(s.begin(), s.end(), x+'0')
```