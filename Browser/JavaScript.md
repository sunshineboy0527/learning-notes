# JavaScript：
* 概念：一门客户端脚本语言
	* 运行在客户端浏览器中的。每一个浏览器都有JavaScript的解析引擎
	* 脚本语言：不需要编译，直接就可以被浏览器解析执行了

* 功能：
	* 可以来增强用户和html页面的交互过程，可以来控制html元素，让页面有一些动态的效果，增强用户的体验。

* JavaScript发	展史：
	1. 1992年，Nombase公司，开发出第一门客户端脚本语言，专门用于表单的校验。命名为 ： C--	，后来更名为：ScriptEase
	2. 1995年，Netscape(网景)公司，开发了一门客户端脚本语言：LiveScript。后来，请来SUN公司的专家，修改LiveScript，命名为JavaScript
	3. 1996年，微软抄袭JavaScript开发出JScript语言
	4. 1997年，ECMA(欧洲计算机制造商协会)，制定出客户端脚本语言的标准：ECMAScript，就是统一了所有客户端脚本语言的编码方式。

	* JavaScript = ECMAScript + JavaScript自己特有的东西(BOM+DOM)

### ECMAScript：客户端脚本语言的标准

#### 基本语法：

1. **与html结合方式**
    1. 内部JS：
        * 定义`<script>`，标签体内容就是js代码
    2. 外部JS：
        * 定义`<script>`，通过`src`属性引入外部的js文件
    * 注意：
        1. `<script>`可以定义在html页面的任何地方。但是定义的位置会影响执行顺序。
        2. `<script>`可以定义多个。
2. **注释**
    1. 单行注释：`//注释内容`
    2. 多行注释：`/*注释内容*/`
3. **数据类型**：
    1. **原始数据类型**(基本数据类型)：
        1. `number`：数字。 
        > 整数/小数/NaN
        > NaN(not a number 一个不是数字的数字类型)
        2. `string`：字符串。 字符串  "abc" "a" 'abc'
        3. `boolean`: true和false
        4. `null`：一个对象为空的占位符
        5. `undefined`：未定义。如果一个变量没有给初始化值，则会被默认赋值为undefined
        
    2. **引用数据类型**：对象
    
4. **变量**
    * 变量：一小块存储数据的内存空间
    * Java语言是强类型语言，而**JavaScript是弱类型语言**。
        * 强类型：在开辟变量存储空间时，定义了空间将来存储的数据的数据类型。只能存储固定类型的数据
        * 弱类型：在开辟变量存储空间时，不定义空间将来的存储数据类型，可以存放任意类型的数据。
    * 语法：
        * var 变量名 = 初始化值;
    
    * `typeof`运算符：获取变量的类型。
        * 注：null运算后得到的是object
5. **运算符**
    1. 一元运算符：只有一个运算数的运算符
        `++`，`--` ， `+`(正号)  
        * `++` `--`: 自增(自减)
            * `++`(`--`) 在前，先自增(自减)，再运算
            * `++`(`--`) 在后，先运算，再自增(自减)
        * `+`(`-`)：正负号
        > 注意：在JS中，如果运算数不是运算符所要求的类型，那么js引擎会自动的将运算数进行类型转换
        >> * 其他类型转number：
        >> * string转number：按照字面值转换。如果字面值不是数字，则转为**NaN（不是数字的数字）**
        >> * boolean转number：true转为1，false转为0

    2. 算数运算符
        `+` `-` `*` `/` `%` ...

    3. 赋值运算符
        `=` `+=` `-=`....

    4. 比较运算符
        `>` `<` `>=` `<=` `==` `===`(全等于)
        * 比较方式
            1. 类型相同：直接比较
                * 字符串：按照字典顺序比较。按位逐一比较，直到得出大小为止。
            2. 类型不同：先进行类型转换，再比较
                * `===`：全等于。
                > 在比较之前，先判断类型，如果类型不一样，则直接返回false
        

    5. 逻辑运算符
        `&&` `||` `!`
        * 其他类型转`boolean`：
            1. `number`：0或NaN为假，其他为真
            2. `string`：除了空字符串("")，其他都是true
            3. `null`&`undefined`:都是false
            4. 对象：所有对象都为true
        > js中在以字符串为判断条件时，可以直接使用字符串变量作为逻辑判断参数`if(str)`
        >> 该方法同时也隐式的判断了**字符串不为空**
    
    6. 三元运算符
        `?` : 表达式
        ```js
        var a = 3;
        var b = 4;

        var c = a > b ? 1:0;
        ```
        * 语法：
            * `表达式? 值1:值2;`
            * 判断表达式的值，如果是true则取值1，如果是false则取值2；
    
6. 流程控制语句：
    1. `if...else...`
    2. `switch`:
        * **在java中**，switch语句可以接受的数据类型： byte int shor char,枚举(1.5) ,String(1.7)
            * switch(变量):
                case 值:
        * **在JS中**,switch语句可以接受任意的原始数据类型
    3. `while`
    4. `do...while`
    5. `for`
7. JS特殊语法：
    1. 语句以`;`结尾，如果一行只有一条语句则`;`可以省略 **(不建议)**
    2. 变量的定义使用`var`关键字，也可以不使用
        * **用**： 定义的变量是局部变量
        * **不用**：定义的变量是全局变量(不建议)

#### 基本对象：
1. `Function`：函数(方法)对象
    1. **创建**：
        - `var fun = new Function(形式参数列表,方法体); `**不用这种形式** 
        -
        ```js
            function 方法名称(形式参数列表){
                方法体
            }
        ```
        - 
        ```js
            var 方法名 = function(形式参数列表){
                方法体
            }
        ```
    2. **方法**：

    3. **属性**：
        `length`:代表形参的个数
    4. **特点**：
        - 方法定义时，**形参的类型**不用写,**返回值类型**也不写。
        - 方法是一个对象，如果定义名称相同的方法，会覆盖
        - 在JS中，方法的调用只与方法的名称有关，和参数列表无关
        - 在方法声明中有一个隐藏的内置对象（数组），arguments,封装所有的实际参数
    5. **调用**：
        `方法名称(实际参数列表);`

2. `Array`:数组对象
    1. 创建：
        1. `var arr = new Array(元素列表);`
        2. `var arr = new Array(默认长度);`
        3. `var arr = [元素列表];`
    2. 方法
        `join(参数)`:将数组中的元素按照指定的分隔符拼接为字符串
        `push()`	向数组的末尾添加一个或更多元素，并返回新的长度。
    3. 属性
        `length`:数组的长度
    4. 特点：
        - JS中，数组元素的类型可变的。
        - JS中，数组长度可变的。
3. `Boolean`
4. `Date`：日期对象
    1. 创建：
        `var date = new Date();`

    2. 方法：
        `toLocaleString()`：返回当前date对象对应的时间本地字符串格式
        `getTime()`:获取毫秒值。返回当前如期对象描述的时间到1970年1月1日零点的毫秒值差
5. `Math`：数学对象
    1. 创建：
        * 特点：Math对象不用创建，直接使用。
        `Math.方法名();`

    2. 方法：
        `random()`:返回 0 ~ 1 之间的随机数。 含0不含1
        `ceil(x)`：对数进行上舍入。
        `floor(x)`：对数进行下舍入。
        `round(x)`：把数四舍五入为最接近的整数。
    3. 属性：
        `PI`
6. `Number`
7. `String`
8. `RegExp`：正则表达式对象
    1. 正则表达式：定义字符串的组成规则。
        1. 单个字符:`[]`
            > 如： [a] [ab] [a-zA-Z0-9_]
            * 特殊符号代表特殊含义的单个字符:
                `\d`:单个数字字符 `[0-9]`
                `\w`:单个单词字符`[a-zA-Z0-9_]`
        2. 量词符号：
            `?`：表示出现0次或1次
            `*`：表示出现0次或多次
            `+`：出现1次或多次
            `{m,n}`:表示 m<= 数量 <= n
                * m如果缺省： `{,n}`:最多n次
                * n如果缺省：`{m,}` 最少m次
        3. 开始结束符号
            * `^`:开始
            * `$`:结束
    2. 正则对象：
        1. 创建
            1. `var reg = new RegExp("正则表达式");`
            2. `var reg = /正则表达式/;`
        2. 方法	
            1. `test(参数)`:验证指定的字符串是否符合正则定义的规范	
9. `Global`
    1. 特点：全局对象，这个`Global`中封装的方法不需要对象就可以直接调用。  
    `方法名();`
    2. 方法：
        `encodeURI():url编码`
        `decodeURI():url解码`
        >

        `encodeURIComponent():url编码,编码的字符更多`
        `decodeURIComponent():url解码`
        > 字符也会给编码

        `parseInt()`:将字符串转为数字
        > 逐一判断每一个字符是否是数字，直到不是数字为止，将前边数字部分转为number
        
        `isNaN()`:判断一个值是否是NaN
        > NaN六亲不认，连自己都不认。NaN参与的==比较全部问false

        `eval()`:讲 JavaScript 字符串，并把它作为脚本代码来执行。
    3. URL编码
        传智播客 =  `%E4%BC%A0%E6%99%BA%E6%92%AD%E5%AE%A2`

### BOM:

1. **概念**：Browser Object Model 浏览器对象模型
    * 将浏览器的各个组成部分封装成对象。

2. **组成**：
    * `Window`：窗口对象
    > 其中还包含了DOM对象，因为比较重要，因此单独独立出来
    * `Navigator`：浏览器对象
    * `Screen`：显示器屏幕对象
    * `History`：历史记录对象
    * `Location`：地址栏对象

3. **Window：窗口对象**
    1. 创建
    2. 方法
        1. 与弹出框有关的方法：
        `alert()`	显示带有一段消息和一个**确认按钮**的警告框。
        `confirm()`	显示带有一段消息以及**确认按钮和取消按钮**的对话框。
            > * 如果用户点击确定按钮，则方法返回`true`
            > * 如果用户点击取消按钮，则方法返回`false`
        
            `prompt()`	显示可提示用户输入的对话框。
            > 返回值：获取用户输入的值

        2. 与打开关闭有关的方法：
            `close()`	关闭浏览器窗口。
            > 谁调用我 ，我关谁
        
            `open()`	打开一个新的浏览器窗口
            > 返回新的Window对象，可以传入想要打开的页面的URL

        3. 与定时器有关的方式
            `setTimeout()`	在指定的毫秒数后调用函数或计算表达式。
            > * 参数：
                1. js代码或者方法对象
                2. 毫秒值
            > * 返回值：唯一标识，用于取消定时器
        
            `clearTimeout()`	取消由 `setTimeout()` 方法设置的 timeout。
            `setInterval()`	按照指定的周期（以毫秒计）来调用函数或计算表达式。
            `clearInterval()`	取消由 setInterval() 设置的 timeout。

    3. 属性：
        1. 获取其他BOM对象：
            `history`
            `location`
            `Navigator`
            `Screen`:
        2. 获取DOM对象
            `document`
    4. 特点
        * Window对象不需要创建可以直接使用 `window`使用。 window.方法名();
        * `window`引用可以省略。  `方法名();`
    > `window.alert(" ");`
    > `alert(" ");`


4. **Location：地址栏对象**
    1. 创建(获取)：
        1. `window.location`
        2. `location`

    2. 方法：
        * `reload()`	重新加载当前文档。刷新
    3. 属性
        * `href`	设置或返回完整的 URL。
    > 设置当前窗口的地址栏URL值


5. **History：历史记录对象**
    1. 创建(获取)：
        1. `window.history`
        2. `history`

    2. 方法：
        * `back()`	加载 history 列表中的前一个 URL。
        * `forward()`	加载 history 列表中的下一个 URL。
        * `go(参数)`	加载 history 列表中的某个具体页面。
            > * 参数：
                * 正数：前进几个历史记录
                * 负数：后退几个历史记录

    3. 属性：
        * `length`	返回当前窗口历史列表中的 URL 数量。

### DOM：
概念： Document Object Model 文档对象模型
> 将标记语言文档的各个组成部分，封装为对象。可以使用这些对象，对标记语言文档进行CRUD的动态操作

W3C DOM 标准被分为 3 个不同的部分：

* **核心 DOM** - 针对任何结构化文档的标准模型
    * `Document`：文档对象
    * `Element`：元素对象
    * `Attribute`：属性对象
    * `Text`：文本对象
    * `Comment`:注释对象
    >
    * `Node`：节点对象，其他**5个的父对象**
* **XML DOM** - 针对 XML 文档的标准模型
* **HTML DOM** - 针对 HTML 文档的标准模型

#### 核心DOM模型：
**Document：文档对象**
- 创建(获取)：在html dom模型中可以使用window对象来获取
    1. `window.document`
    2. `document`
    > 上述两方法是基于**HTML DOM来使用的**
- 方法：
    - 获取`Element`对象：
        - `getElementById()`	： 根据id属性值获取元素对象。id属性值一般唯一
        - `getElementsByTagName()`：根据元素名称获取元素对象们。返回值是一个**数组**
        - `getElementsByClassName()`:根据Class属性值获取元素对象们。返回值是一个**数组**
        - `getElementsByName()`: 根据name属性值获取元素对象们。返回值是一个数组
    - 创建其他DOM对象：
        - `createAttribute(name)`
        - `createComment()`
        - `createElement()`
        - `createTextNode()`
- 属性
    
**Element：元素对象**
1. 获取/创建：通过document来获取和创建
2. 方法：
    - `removeAttribute(Element)`：删除属性
    - `setAttribute(Element, href)`：设置属性
> 在JavaScript中，Element对象本身并没有一个通用的 `value` 属性。然而，特定的HTML元素（如 `<input>`, `<textarea>`, `<select>` 等）确实具有 `value` 属性，这些属性可以通过JavaScript访问和修改。

**Node：节点对象，其他5个的父对象**
- 特点：所有dom对象都可以被认为是一个节点
- 方法：
    * CRUD dom树：
        * `appendChild()`：向节点的子节点列表的结尾添加新的子节点。
        * `removeChild()`	：删除（并返回）当前节点的指定子节点。
        * `replaceChild()`：用新节点替换一个子节点。
* 属性：
    * `parentNode` 返回节点的父节点。

#### HTML DOM:
> 功能：控制html文档的内容
1. 标签体的设置和获取：`innerHTML`
> 可以在标签体中添加文字，也可以添加标签
```js
div.innerHTML = "<a>超链接</a>"; //在aiv元素中添加 <a>超链接</a>
```

2. 使用`html`元素对象的属性
3. 控制元素样式
    1. 使用元素的style属性来设置
        如：
        ```js
            //修改样式方式1
            div1.style.border = "1px solid red";
            div1.style.width = "200px";
            //font-size--> fontSize
            div1.style.fontSize = "20px";
        ```
    2. 提前定义好类选择器的样式，通过元素的`className`属性来设置其`class`属性值。

### 事件监听机制：
**概念**：某些组件被执行了某些操作后，触发某些代码的执行。	
* 事件：某些操作。如： 单击，双击，键盘按下了，鼠标移动了
* 事件源：组件。如： 按钮 文本输入框...
* 监听器：代码。
* 注册监听：将事件，事件源，监听器结合在一起。 当事件源上发生了某个事件，则触发执行某个监听器代码。

**功能**： 某些组件被执行了某些操作后，触发某些代码的执行。
> * 造句：  xxx被xxx,我就xxx
>    * 我方水晶被摧毁后，我就责备对友。
>    * 敌方水晶被摧毁后，我就夸奖自己。

**如何绑定事件**
1. 直接在html标签上，指定事件的属性(操作)，属性值就是js代码
    - 事件：`onclick`--- 单击事件
> `<img src="" onclick="与该事件绑定的要执行的方法">`
>> 这种只有定义标签属性时才可用

> `<img src="" onclick="func();">`

2. 通过js获取元素对象，指定事件属性，设置一个函数
> 通过在js文件中获取元素对象，在将该对象与对应方法进行绑定
> `var elem = getElementById("id");`
> `elem.onclick = 对应方法名;`

> **注意**：js文件体定义要在元素下方，确保对应元素实现完成加载

**常见的事件**：
1. 点击事件：
    - `onclick`：单击事件
    - `ondblclick`：双击事件
2. 焦点事件
    - `onblur`：失去焦点
    - `onfocus`:元素获得焦点。

3. 加载事件：
    - `onload`：一张页面或一幅图像完成加载。

4. 鼠标事件：
    - `onmousedown`	鼠标按钮被按下。
    - `onmouseup`	鼠标按键被松开。
    - `onmousemove`	鼠标被移动。
    - `onmouseover`	鼠标移到某元素之上。
    - `onmouseout`	鼠标从某元素移开。
    
    
5. 键盘事件：
    - `onkeydown`	某个键盘按键被按下。	
    - `onkeyup`		某个键盘按键被松开。
    - `onkeypress`	某个键盘按键被按下并松开。

6. 选择和改变
    - `onchange`	域的内容被改变。
    - `onselect`	文本被选中。

7. 表单事件：
    - `onsubmit`	确认按钮被点击。
    - `onreset`	重置按钮被点击。

---

## 变量声明

在 JavaScript 中，变量声明主要有以下 5 种方式，每种方式都有不同的作用域和特性：

---

### 1. **`var`** (ES5 及之前)

-   **作用域**：函数作用域（function scope）

-   **变量提升**：会提升到函数顶部

-   **可重复声明**：允许

-   **全局属性**：会成为 `window` 对象的属性

-   **示例**：

    ```javascript
    var x \= 10;
    if (true) {
      var x \= 20; // 同一个变量
    }
    console.log(x); // 20
    ```

### 2. **`let`** (ES6+)

-   **作用域**：块级作用域（block scope，如 `{}` 内）

-   **变量提升**：存在暂时性死区（TDZ），不会实际提升

-   **可重复声明**：不允许

-   **全局属性**：不会成为 `window` 的属性

-   **示例**：

    ```javascript
    let y \= 10;
    if (true) {
      let y \= 20; // 不同的变量
    }
    console.log(y); // 10
    ```

### 3. **`const`** (ES6+)

-   **作用域**：块级作用域

-   **变量提升**：存在暂时性死区

-   **可重复声明**：不允许

-   **必须初始化**：声明时必须赋值

-   **不可重新赋值**：基本类型不可变，但对象/数组内容可修改

-   **示例**：

    ```javascript
    const z \= 10;
    // z = 20; // 报错

    const obj \= { a: 1 };
    obj.a \= 2; // 允许
    ```

### 4. **隐式声明**（不推荐）

-   直接赋值未声明的变量：

    ```javascript
    a \= 30; // 自动成为全局变量（严格模式下报错）
    ```

### 5. **`function` 声明**

-   **作用域**：函数作用域

-   **变量提升**：整个函数会被提升

-   **示例**：

    ```javascript
    console.log(foo()); // "Hello"（函数被提升）
    function foo() {
      return "Hello";
    }
    ```

---

### 对比表格

| 特性 | `var` | `let` | `const` | 隐式声明 | `function` |
| --- |  --- |  --- |  --- |  --- |  --- |
| **作用域** | 函数作用域 | 块级作用域 | 块级作用域 | 全局 | 函数作用域 |
| --- |  --- |  --- |  --- |  --- |  --- |
| **提升** | 完全提升 | 不提升（TDZ） | 不提升（TDZ） | \- | 完全提升 |
| **重复声明** | 允许 | 不允许 | 不允许 | \- | 允许 |
| **全局属性** | 是 | 否 | 否 | 是 | 是 |
| **是否需要初始化** | 否 | 否 | 是 | \- | \- |
| **可重新赋值** | 是 | 是 | 否 | 是 | 是 |

---

### 推荐使用

1.  **默认使用 `const`**：除非需要重新赋值

2.  **需要重新赋值时用 `let`**：替代 `var`

3.  **避免使用 `var`**：除非需要兼容旧代码

4.  **禁用隐式声明**：严格模式下会报错（`'use strict'`）

5.  **函数表达式优先**：用 `const foo = function() {}` 替代 `function foo() {}` 可避免提升

---

# jQuery库

> 需要引入jQuery库 `https://cdn.bootcdn.net/ajax/libs/jquery/3.7.1/jquery.min.js`
>
> 查找相关开源库可以在(https://www.bootcdn.cn/)搜索

> 体积大，除了能处理Ajax还能简化js其他操作

jQuery 是一个快速、简洁的 JavaScript 库，简化了 DOM 操作、事件处理、动画和 Ajax 交互。以下是 jQuery 的常用操作总结：

* * * *

## 1\. DOM 操作

### **选择元素**

```javascript
// 基本选择器
$("#id")          // ID 选择器
$(".class")       // Class 选择器
$("div")          // 标签选择器
$("div.class")    // 组合选择器

// 层级选择器
$("parent > child")  // 直接子元素
$("ancestor descendant")  // 所有后代

// 过滤选择器
$("li:first")     // 第一个元素
$("li:last")      // 最后一个元素
$("li:even")      // 偶数索引元素
$("li:odd")       // 奇数索引元素
$("li:eq(2)")     // 第 3 个元素（索引从 0 开始）
$("li:gt(2)")     // 索引大于 2 的元素
$("li:lt(2)")     // 索引小于 2 的元素
```

### **修改内容**

```javascript
$("#el").html("<b>新内容</b>")  // 设置 HTML
$("#el").text("纯文本")        // 设置文本
$("#el").val("input值")       // 设置表单值

// 获取内容
let html = $("#el").html()
let text = $("#el").text()
let value = $("#el").val()
```

### **修改属性**

```javascript
$("#el").attr("href", "https://example.com")  // 设置属性
let href = $("#el").attr("href")             // 获取属性

$("#el").removeAttr("disabled")              // 移除属性

// data-\* 属性
$("#el").data("key", "value")                // 设置 data-key
let data = $("#el").data("key")              // 获取 data-key
```

### **修改 CSS 和样式**

```javascript
$("#el").css("color", "red")                 // 设置单个样式
$("#el").css({ "color": "red", "font-size": "16px" })  // 设置多个样式

$("#el").addClass("active")                  // 添加类
$("#el").removeClass("active")               // 移除类
$("#el").toggleClass("active")               // 切换类
```

### **DOM 遍历**

```javascript
$("#el").parent()           // 直接父元素
$("#el").parents("div")     // 所有匹配的祖先元素
$("#el").children()         // 直接子元素
$("#el").find(".item")      // 所有匹配的后代元素
$("#el").siblings()         // 所有兄弟元素
$("#el").next()             // 下一个兄弟元素
$("#el").prev()             // 上一个兄弟元素
```

### **DOM 增删改**

```javascript
// 插入元素
$("#el").append("<p>追加内容</p>")      // 内部末尾
$("#el").prepend("<p>前置内容</p>")     // 内部开头
$("#el").after("<p>之后插入</p>")       // 外部之后
$("#el").before("<p>之前插入</p>")      // 外部之前

// 移除元素
$("#el").remove()           // 删除元素及其事件
$("#el").empty()            // 清空子元素
```

* * * *

## 2\. 事件处理

### **绑定事件**

```javascript
$("#btn").click(function() {
    alert("点击事件");
});

// 常用事件
$("#el").on("click", handler)   // 推荐（支持动态元素）
$("#el").click(handler)        // 简写
$("#el").hover(handlerIn, handlerOut)  // 鼠标悬停
$("#el").submit(handler)       // 表单提交
$("#el").keypress(handler)     // 键盘按下

// 事件委托（适用于动态元素）
$("#parent").on("click", ".child", handler)
```

### **解绑事件**

```javascript
$("#el").off("click")      // 移除所有点击事件
$("#el").off("click", handler)  // 移除特定处理函数
```

### **触发事件**

```javascript
$("#el").click()          // 手动触发点击
$("#el").trigger("click") // 推荐方式
```

* * * *

## 3\. Ajax 请求

```javascript
// GET 请求
$.get("url", { key: "value" }, function(data) {
    console.log(data);
});

// POST 请求
$.post("url", { key: "value" }, function(data) {
    console.log(data);
});

// 完整 Ajax
$.ajax({
    url: "api/data",
    method: "GET",
    data: { id: 1 },
    success: function(data) {
        console.log(data);
    },
    error: function(err) {
        console.error(err);
    }
});
```

* * * *

## 4\. 动画效果

```javascript
$("#el").hide()          // 隐藏
$("#el").show()          // 显示
$("#el").toggle()        // 切换显示/隐藏

// 滑动效果
$("#el").slideUp()
$("#el").slideDown()
$("#el").slideToggle()

// 淡入淡出
$("#el").fadeIn()
$("#el").fadeOut()
$("#el").fadeToggle()

// 自定义动画
$("#el").animate({
    opacity: 0.5,
    left: "+=50px"
}, 1000);
```

* * * *

## 5\. 实用工具

```javascript
// 遍历元素
$("li").each(function(index) {
    console.log(index, $(this).text());
});

// 检查元素是否存在
if ($("#el").length) {
    console.log("元素存在");
}

// 延迟执行
setTimeout(function() {
    $("body").css("background", "red");
}, 1000);
```