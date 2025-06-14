> 通过node server.js 启动服务器
> 
> 对应代码通过express框架进行测试

# Ajax

AJAX全称为Asynchronous JavaScript And XML，就是异步的JS和XML。 
通过AJAX可以在浏览器中向服务器发送异步请求，最大的优势：**无刷新获取数据**。 
AJAX不是新的编程语言，而是一种将现有的标准组合在一起使用的新方式。
它的核心是通过 JavaScript 发送 **异步 HTTP 请求**，实现动态加载数据，提升用户体验。

## Ajax特点

---

**AJAX 的核心特点**

1.  **异步通信**

    -   不阻塞页面渲染，用户操作不受影响。

2.  **局部更新**

    -   只刷新页面的某一部分，而不是整个页面。

3.  **多种数据格式支持**

    -   最初设计用于 XML，但现在更常用 **JSON**、HTML 或纯文本。

4.  **基于浏览器原生 API**

    -   早期依赖 `XMLHttpRequest` 对象，现代也可用 `fetch` API。

--- 

优点：
1. 可以无需刷新页面而与服务器端进行通信。
2. 允许你根据用户事件来更新部分页面内容。
缺点：
1. 没有浏览历史，不能回退
2. 存在跨域问题(同源)
3. SEO不友

### **AJAX 的工作原理**

1.  **用户触发事件**（如点击按钮、输入搜索词）。

2.  **JavaScript 创建 HTTP 请求** 并发送到服务器。

3.  **服务器处理请求** 并返回数据（如 JSON、XML、HTML）。

4.  **JavaScript 解析响应** 并动态更新页面内容。

### **AJAX 的实现方式**

#### 1. **原生 JavaScript（XMLHttpRequest）**

```javascript
const xhr = new XMLHttpRequest();
xhr.open('GET', 'https://api.example.com/data', true); // true 表示异步

xhr.onload = function() {
  if (xhr.status === 200) {
    const data = JSON.parse(xhr.responseText);
    console.log(data);
  } else {
    console.error('请求失败');
  }
};

xhr.onerror = function() {
  console.error('网络错误');
};

xhr.send();
```

#### 2. **现代方法（Fetch API）**

```javascript
fetch('https://api.example.com/data')
  .then(response => {
    if (!response.ok) throw new Error('请求失败');
    return response.json();
  })
  .then(data => console.log(data))
  .catch(error => console.error(error));
```

#### 3. **jQuery 封装（简化版）**

```javascript
$.ajax({
  url: 'https://api.example.com/data',
  method: 'GET',
  success: function(data) {
    console.log(data);
  },
  error: function(error) {
    console.error(error);
  }
});
```

#### 4. **axios实现**

**Axios** 是一个基于 Promise 的现代化 **HTTP 客户端**，用于浏览器和 Node.js 环境。它主要用于发送 **AJAX 请求**（如 GET、POST、PUT、DELETE 等），并提供了许多强大的功能，如 **请求/响应拦截、自动转换 JSON 数据、取消请求、并发请求** 等。

### **AJAX 的典型应用场景**

1.  **表单提交**

    -   用户注册/登录时无刷新验证（如显示"用户名已存在"）。

2.  **动态加载内容**

    -   无限滚动（如微博、新闻列表）。

3.  **搜索建议**

    -   输入关键词时实时显示搜索结果（如百度搜索框）。

4.  **购物车更新**

    -   添加商品后局部刷新购物车数量。

---

# jQuery

jQuery 提供了简洁的 AJAX 方法，可以轻松发送异步 HTTP 请求。以下是 jQuery 实现 AJAX 的几种常用方式：

---

## **1\. 基础方法：`$.ajax()`**

最通用的方法，可配置性强：

```javascript
$.ajax({
  url: 'https://api.example.com/data',  // 请求地址
  method: 'GET',                       // 请求方法（GET/POST/PUT/DELETE）
  data: { id: 123 },                   // 发送的数据（对象或查询字符串）
  dataType: 'json',                    // 预期返回的数据类型（json/xml/html）
  success: function(response) {        // 请求成功回调
    console.log('成功:', response);
  },
  error: function(xhr, status, error) { // 请求失败回调
    console.error('失败:', error);
  }
});
```

---

## **2\. 快捷方法**

### **GET 请求：`$.get()`**

```javascript
$.get(
  'https://api.example.com/data',
  { id: 123 },  // 可选：发送的查询参数
  function(response) {
    console.log('成功:', response);
  },
  'json'       // 可选：预期返回的数据类型
);
```

---

### **POST 请求：`$.post()`**

```javascript
$.post(
  'https://api.example.com/data',
  { name: 'John', age: 30 },  // 发送的数据
  function(response) {
    console.log('成功:', response);
  },
  'json'
);
```

---

### **加载 HTML 片段：`$.load()`**

```javascript
$('#result').load('/partial.html #content'); // 加载指定页面的片段
```

---

## **3\. 高级用法**

### **发送 JSON 数据**

```javascript
$.ajax({
  url: '/api/data',
  method: 'POST',
  contentType: 'application/json',  // 设置请求头
  data: JSON.stringify({ key: 'value' }), // 手动转为 JSON
  success: function(response) {
    console.log(response);
  }
});
```

---

### **处理文件上传（FormData）**

```javascript
const formData = new FormData();
formData.append('file', $('#fileInput')\[0\].files\[0\]);

$.ajax({
  url: '/upload',
  method: 'POST',
  data: formData,
  processData: false,  // 禁止 jQuery 处理数据
  contentType: false,  // 禁止自动设置 Content-Type
  success: function(response) {
    console.log('上传成功');
  }
});
```

---

### **全局 AJAX 事件**

```javascript
// 所有 AJAX 请求开始前触发
$(document).ajaxStart(function() {
  $('#loading').show();
});

// 所有 AJAX 请求完成后触发
$(document).ajaxStop(function() {
  $('#loading').hide();
});
```

---

## **4\. 链式调用与 Deferred**

jQuery AJAX 返回 `Deferred` 对象，支持 Promise 风格：

```javascript
$.get('https://api.example.com/data')
  .done(function(response) {
    console.log('成功:', response);
  })
  .fail(function(xhr, status, error) {
    console.error('失败:', error);
  })
  .always(function() {
    console.log('请求完成（无论成功或失败）');
  });
```

---

## **5\. 跨域请求（JSONP）**

针对跨域接口（仅支持 GET）：

```javascript
$.ajax({
  url: 'https://api.example.com/data?callback=?', // jQuery 自动替换 ? 为随机函数名
  dataType: 'jsonp',
  success: function(response) {
    console.log(response);
  }
});
```

---

# axios库

> 具体查阅(https://www.javasoho.com/axios/)中文文档

> 更现代化，支持Promise语法 ~~之前只能用回调~~
>
> 体积小，专注处理AJAX

**Axios** 是一个基于 Promise 的现代化 **HTTP 客户端**，用于浏览器和 Node.js 环境。它主要用于发送 **AJAX 请求**（如 GET、POST、PUT、DELETE 等），并提供了许多强大的功能，如 **请求/响应拦截、自动转换 JSON 数据、取消请求、并发请求** 等。

---

## Axios API用法

---

> 通用方式

可以通过向 `axios` 传递相关配置来创建请求

### axios(config)

```javascript
// 发送 POST 请求
axios({  
    method: 'post',
    url: '/user/12345',  
    data: {    
        firstName: 'Fred',    
        lastName: 'Flintstone'  
        }
    });
```


```javascript
// 获取远端图片
axios({  
    method:'get',  
    url:'http://bit.ly/2mTM3nY',  
    responseType:'stream'})  
    .then(function(response) {  
        response.data.pipe(fs.createWriteStream('ada_lovelace.jpg'))}
    );
```


### axios(url[, config])

```javascript
// 发送 GET 请求（默认的方法）
axios('/user/12345');
```



## Axios 的主要用途
---------------

### **1\. 发送 HTTP 请求**

Axios 可以轻松发送各种 HTTP 请求，并支持 **Promise** 语法（`.then()` 和 `.catch()`），比传统的 `XMLHttpRequest` 或 `fetch` 更易用。

各种方式请求方法：
```javascript
axios.request(config)
axios.get(url[, config])
axios.delete(url[, config])
axios.head(url[, config])
axios.options(url[, config])
axios.post(url[, data[, config]])
axios.put(url[, data[, config]])
axios.patch(url[, data[, config]])
```

```javascript
// GET 请求
axios.get('https://api.example.com/data')
  .then(response => console.log(response.data))
  .catch(error => console.error(error));

// POST 请求
axios.post('https://api.example.com/data', { name: 'John' })
  .then(response => console.log(response.data))
  .catch(error => console.error(error));

// PUT 请求
axios.put('https://api.example.com/data/1', { name: 'Updated John' });

// DELETE 请求
axios.delete('https://api.example.com/data/1');
```

* * * *

### **2\. 自动转换 JSON 数据**

-   Axios **自动解析** 返回的 JSON 数据，无需手动调用 `response.json()`（如 `fetch` 需要）。

-   请求数据也会 **自动序列化** 为 JSON（如果发送的是 JavaScript 对象）。

```javascript
// 使用 fetch 需要手动解析 JSON
fetch('https://api.example.com/data')
  .then(response => response.json())  // 需要额外步骤
  .then(data => console.log(data));

// 使用 Axios 自动解析
axios.get('https://api.example.com/data')
  .then(response => console.log(response.data));  // 直接获取 data
```

* * * *

### **3\. 全局配置（BaseURL、Headers、超时等）**

可以设置 **全局默认值**，避免重复代码：

```javascript
axios.defaults.baseURL = 'https://api.example.com';
axios.defaults.headers.common['Authorization'] = 'Bearer token123';
axios.defaults.timeout = 5000; // 5秒超时

// 后续请求会自动应用这些配置
axios.get('/data')  // 实际请求 https://api.example.com/data
  .then(response => console.log(response.data));
```

* * * *

### **4\. 拦截请求和响应**

可以在请求发送前或响应返回后 **拦截并修改** 数据：

```javascript
// 请求拦截器（如添加 Token）
axios.interceptors.request.use(
  config => {
    config.headers.Authorization = 'Bearer token123';
    return config;
  },
  error => Promise.reject(error)
);

// 响应拦截器（如统一处理错误）
axios.interceptors.response.use(
  response => response.data,  // 直接返回 data，避免每次手动取
  error => {
    if (error.response.status === 401) {
      alert("请登录！");
    }
    return Promise.reject(error);
  }
);
```

* * * *

### **5\. 并发请求**

可以同时发送多个请求，并在所有请求完成后处理结果：

```javascript
axios.all([
  axios.get('https://api.example.com/users'),
  axios.get('https://api.example.com/posts')
])
.then(axios.spread((usersResponse, postsResponse) \=> {
  console.log(usersResponse.data, postsResponse.data);
}));
```

* * * *

### **6\. 取消请求**

可以 **中止** 正在进行的请求（适用于搜索框输入防抖等场景）：

```javascript
const source = axios.CancelToken.source();

axios.get('https://api.example.com/data', {
  cancelToken: source.token
})
  .then(response => console.log(response.data))
  .catch(error => {
    if (axios.isCancel(error)) {
      console.log('请求被取消:', error.message);
    }
  });

// 取消请求
source.cancel('用户取消了请求');
```

* * * *

### **7\. 上传/下载文件**

支持 **文件上传**（`FormData`）和 **下载**（Blob 数据）：

```javascript
// 上传文件
const formData = new FormData();
formData.append('file', fileInput.files[0]);

axios.post('https://api.example.com/upload', formData, {
  headers: { 'Content-Type': 'multipart/form-data' }
});

// 下载文件
axios.get('https://api.example.com/download', { responseType: 'blob' })
  .then(response => {
    const url = window.URL.createObjectURL(new Blob([response.data]));
    const link = document.createElement('a');
    link.href = url;
    link.setAttribute('download', 'file.pdf');
    document.body.appendChild(link);
    link.click();
  });
```

---

# fetch

> 原生js中的函数，新版本出现，用于替代传统的 `XMLHttpRequest`（XHR），让发送ajax请求变得更加便捷

**`fetch`** 是浏览器提供的一个现代、基于 **Promise** 的 **网络请求 API**，用于替代传统的 `XMLHttpRequest`（XHR）。它提供了一种更简洁、灵活的方式来发送 HTTP 请求并处理响应。

---

## **fetch 的核心特点**

1.  **基于 Promise**

    -   使用 `.then()` 和 `.catch()` 处理异步操作，避免回调地狱。

    -   支持 `async/await` 语法，代码更清晰。

2.  **内置支持 JSON、FormData、Blob 等数据类型**

    -   可以方便地处理不同格式的请求和响应数据。

3.  **更简洁的 API**

    -   相比 `XMLHttpRequest`，代码更少，逻辑更直观。

4.  **默认不携带 Cookie**

    -   需要手动设置 `credentials: 'include'` 以发送 Cookie（如跨域请求）。

5.  **不自动解析 JSON**

    -   需要手动调用 `.json()` 方法解析 JSON 响应。

6.  **没有请求/响应拦截器**

    -   需要自行封装或使用第三方库（如 `axios`）实现拦截功能。

7.  **不支持请求取消（需结合 `AbortController`）**

    -   可以通过 `AbortController` 中止请求。

---

## **fetch 基本用法**

### **1\. GET 请求**

```javascript
fetch('https://api.example.com/data')
  .then(response => {
    if (!response.ok) {
      throw new Error('网络请求失败');
    }
    return response.json(); // 解析 JSON 数据
  })
  .then(data => console.log(data))
  .catch(error => console.error(error));
```

### **2\. POST 请求（发送 JSON）**

```javascript
fetch('https://api.example.com/data', {
  method: 'POST',
  headers: {
    'Content-Type': 'application/json',
  },
  body: JSON.stringify({ name: 'John', age: 30 }), // 发送 JSON 数据
})
  .then(response => response.json())
  .then(data => console.log(data))
  .catch(error => console.error(error));
```

### **3\. POST 请求（发送 FormData）**

```javascript
const formData = new FormData();
formData.append('username', 'John');
formData.append('avatar', fileInput.files\[0\]); // 上传文件

fetch('https://api.example.com/upload', {
  method: 'POST',
  body: formData, // 无需手动设置 Content-Type
})
  .then(response => response.json())
  .then(data => console.log(data));
```

### **4\. 设置请求头**

```javascript
fetch('https://api.example.com/data', {
  headers: {
    'Authorization': 'Bearer token123',
    'Custom-Header': 'value',
  },
});
```

### **5\. 处理不同的响应类型**

```javascript
// 获取文本
fetch('/text').then(response => response.text());

// 获取 Blob（如图片、文件）
fetch('/image.png').then(response => response.blob());

// 获取 ArrayBuffer（二进制数据）
fetch('/data.bin').then(response => response.arrayBuffer());
```

### **6\. 跨域请求（CORS）**

```javascript
fetch('https://another-domain.com/api', {
  mode: 'cors', // 默认就是 'cors'
  credentials: 'include', // 发送 Cookie（如需跨域认证）
});
```

---

## **fetch 高级用法**

### **1\. 取消请求（AbortController）**

```javascript
const controller = new AbortController();
const signal = controller.signal;

fetch('https://api.example.com/data', { signal })
  .then(response => response.json())
  .catch(error => {
    if (error.name === 'AbortError') {
      console.log('请求被取消');
    }
  });

// 取消请求
controller.abort();
```

### **2\. 超时控制**

```javascript
const timeout = (ms) => new Promise((_, reject) =>
  setTimeout(() => reject(new Error('请求超时')), ms)
);

Promise.race([
  fetch('https://api.example.com/data'),
  timeout(5000), // 5秒超时
])
  .then(response => response.json())
  .catch(error => console.error(error));
```

### **3\. 错误处理**

`fetch` **不会自动 reject HTTP 错误状态（如 404、500）**，需要手动检查 `response.ok`：

```javascript
fetch('https://api.example.com/not-found')
  .then(response => {
    if (!response.ok) {
      throw new Error(`HTTP 错误: ${response.status}`);
    }
    return response.json();
  })
  .catch(error => console.error(error));
```

# 跨域与解决

## 1、什么是跨越？

-   一个网页向另一个不同域名/不同协议/不同端口的网页请求资源，这就是跨域。
-   跨域原因产生：在当前域名请求网站中，默认不允许通过ajax请求发送其他域名。

## 2、为什么会产生跨域请求？

- 因为浏览器使用了同源策略

## 3、什么是同源策略？

- 同源策略是Netscape提出的一个著名的安全策略，现在所有支持JavaScript的浏览器都会使用这个策略。同源策略是浏览器最核心也最基本的安全功能，如果缺少同源策略，浏览器的正常功能可能受到影响。可以说web是构建在同源策略的基础之上的，浏览器只是针对同源策略的一种实现。
-   同源： 协议、域名、端口号 必须完全相同。 `违背同源策略就是跨域`。

## 4、为什么浏览器要使用同源策略？

-   是为了保证用户的信息安全，防止恶意网站窃取数据，如果网页之间不满足同源要求，将不能:
-   -1、共享Cookie、LocalStorage、IndexDB
-   -2、获取DOM
-   -3、AJAX请求不能发送

## 5、跨域的五个解决方式:

1. 前端使用jsonp （不推荐使用）
2. 后台Http请求转发
3. 后台配置同源Cors （推荐）
4. 使用SpringCloud网关
5. 5、使用nginx做转发 (推荐)

### 解决跨域问题方案1、jsonP (麻烦，野路子，不推荐)

1. JSONP 是什么?

JSONP(JSON with Padding)，是一个非官方的跨域解决方案，纯粹凭借程序员的聪明 才智开发出来，只支持 get 请求。

2. JSONP 怎么工作的？

在网页有一些标签天生具有跨域能力，比如：`img` `link` `iframe` `script`。 JSONP 就是利用 script 标签的跨域能力来发送请求的。

### Ⅰ-jsonP的使用

```js
   // 1. 动态的创建一个 script 标签------------------------------------------------------------
    var script = document.createElement("script");
	//2. 设置 script 的 src， 设置回调函数
    script.src = "http://localhost:3000/testAJAX?callback=abc";
    function abc(data) {
      alert(data.name);
    };
   // 3. 将 script 添加到 body 中
    document.body.appendChild(script);

   // 4. 服务器中路由的处理------------------------------------------------------
    router.get("/testAJAX", function (req, res) {
      console.log("收到请求");
      var callback = req.query.callback;
      var obj = {
        ame: "孙悟空",
        age: 18
      }
      res.send(callback + "(" + JSON.stringify(obj) + ")");
    });

```

### Ⅱ-jQuery发送jsonP请求

```js
//前端代码-----------------------------------------------------------------------------------
$('button').eq(0).click(function () {
  $.getJSON('http://127.0.0.1:8000/jquery-jsonp-server?callback=?', function (data) {
    $('#result').html(`
                名称: ${data.name}<br>
                校区: ${data.city}
            `)
  });
});

//服务端代码-----------------------------------------------------------
app.all('/jquery-jsonp-server', (request, response) => {
  // response.send('console.log("hello jsonp")');
  const data = {
    name: '尚硅谷',
    city: ['北京', '上海', '深圳']
  };
  //将数据转化为字符串
  let str = JSON.stringify(data);
  //接收 callback 参数
  let cb = request.query.callback;

  //返回结果
  response.end(`${cb}(${str})`);
});

```

### 解决跨域问题方案2、CORS （官方推荐）

> 只需在服务器端接受请求时，添加**响应头**即可

1. **CORS是什么?**

CORS（Cross-Origin Resource Sharing），跨域资源共享。CORS 是官方的跨域解决方 案，它的特点是不需要在客户端做任何特殊的操作，完全在服务器中进行处理，支持 get 和 post 请求。跨域资源共享标准新增了一组 HTTP 首部字段，允许服务器声明哪些 源站通过浏览器有权限访问哪些资源

2. **CORS是怎么工作的?**

CORS 是通过设置一个响应头来告诉浏览器，该请求允许跨域，浏览器收到该响应 以后就会对响应放行。

### Ⅰ-代码示例

```js
app.all('/cors-server', (request, response) => {
  //设置响应头
    //响应首部中可以携带一个 Access-Control-Allow-Origin 字段
  response.setHeader("Access-Control-Allow-Origin", "*");
    //Access-Control-Allow-Headers 首部字段用于预检请求的响应。其指明了实际请求中允许携带的首部字
  response.setHeader("Access-Control-Allow-Headers", '*');
    //Access-Control-Allow-Methods 首部字段用于预检请求的响应。其指明了实际请求所允许使用的 HTTP
  response.setHeader("Access-Control-Allow-Method", '*');
  // response.setHeader("Access-Control-Allow-Origin", "http://127.0.0.1:5500");
  response.send('hello CORS');
});

```

### AJAX跨域解决方案

#### 方案1：设置响应头

- 核心原理：跨域访问的资源允许你跨域访问。

- 实现：

   ```java
    response.setHeader("Access-Control-Allow-Origin", "http://localhost:8080"); // 允许某个
    response.setHeader("Access-Control-Allow-Origin", "*"); // 允许所有
    ```

#### 方案2：jsonp

- jsonp：json with padding（带填充的json【学完之后再理解这个什么意思！！！】）
- jsonp不是一个真正的ajax请求。只不过可以完成ajax的局部刷新效果。可以说jsonp是一种类ajax请求的机制。
- jsonp不是ajax请求，但是可以完成局部刷新的效果，并且可以解决跨域问题。
- 注意：jsonp解决跨域的时候，只支持GET请求。不支持post请求。

#### 方案3：jQuery封装的jsonp

- 牛人们写的jQuery库，已经对jsonp进行了封装。大家可以直接拿来用。

- 用之前需要引入jQuery库的js文件。（这里的jQuery库咱们就不再封装了，咱们直接用jQuery写好的jsonp方式。）

- jQuery中的jsonp其实就是我们方案2的高度封装，底层原理完全相同。

- 核心代码

  ```javascript
    $.ajax({
        type : "GET",
        url : "跨域的url",
        dataType : "jsonp", // 指定数据类型
        jsonp : "fun", // 指定参数名（不设置的时候，默认是："callback"）
        jsonpCallback : "sayHello" // 指定回调函数的名字
    							   // （不设置的时候，jQuery会自动生成一个随机的回调函数，
        						   //并且这个回调函数还会自动调用success的回调函数。）
    })
    ```

    

#### 方案4：代理机制（httpclient）

- 使用Java程序怎么去发送get/post请求呢？【GET和POST请求就是HTTP请求。】
  - 第一种方案：使用JDK内置的API（java.net.URL.....），这些API是可以发送HTTP请求的。
  - 第二种方案：使用第三方的开源组件，比如：apache的httpclient组件。（httpclient组件是开源免费的，可以直接用）
- 在java程序中，使用httpclient组件可以发送http请求。
  - 对于httpclient组件的代码，大家目前可以不进行深入的研究，可以从网上直接搜。然后粘贴过来，改一改，看看能不能完成发送get和post请求。
  - 使用httpclient组件，需要先将这个组件相关的jar包引入到项目当中。