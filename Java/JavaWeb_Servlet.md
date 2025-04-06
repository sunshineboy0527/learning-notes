### servlet

1. Servlet的体系结构	

> Servlet -- 接口
> 	
> GenericServlet -- 抽象类
> 	
> HttpServlet  -- 抽象类

2. Servlet相关配置
`urlpartten`:Servlet访问路径
> - 一个`Servlet`可以定义多个访问路径 ： `@WebServlet({"/d4","/dd4","/ddd4"})`
> - 路径定义规则：
>>	- `/xxx`：路径匹配
>>	- `/xxx/xxx`:多层路径，目录结构
>>	- `*.do`：扩展名匹配

3. Web项目jar包都需放在WEB-INF目录的lib文件夹下,原因：
> 1. src 下的源文件（如：.java）经过了编译之后放在 `WEB-INF/classes` 目录下
> 2. lib 包在编译前需要放在 WEB-INF 下编译后才能出现在 `WEB-INF/lib` 目录下，所以除了 tomcat 自带的 jar 包（JRE）外，项目所需 jar 包都应放在 WEB-INF 的 lib 目录下，否则部署的web项目就会缺少lib包

### HTTP：

概念：`Hyper Text Transfer Protocol` 超文本传输协议
* 传输协议：定义了，客户端和服务器端通信时，发送数据的格式
* 特点：
	1. 基于`TCP/IP`的高级协议
	2. 默认端口号:`80`
	3. 基于请求/响应模型的:一次请求对应一次响应
	4. 无状态的：每次请求之间相互独立，不能交互数据

### Tomcat部署

> - 关于Tomcat服务器的目录
>   - bin ： 这个目录是Tomcat服务器的命令文件存放的目录，比如：启动Tomcat，关闭Tomcat等。
>   - conf： 这个目录是Tomcat服务器的配置文件存放目录。（server.xml文件中可以配置端口号，默认Tomcat端口是8080）
>   - lib ：这个目录是Tomcat服务器的核心程序目录，因为Tomcat服务器是Java语言编写的，这里的jar包里面都是class文件。
>   - logs: Tomcat服务器的日志目录，Tomcat服务器启动等信息都会在这个目录下生成日志文件。
>   - temp：Tomcat服务器的临时目录。存储临时文件。
>   - webapps：这个目录当中就是用来存放大量的webapp（web application：web应用）
>   - work：这个目录是用来存放JSP文件翻译之后的java文件以及编译之后的class文件。

1. 直接将项目放到`webapps`目录下即可。
    * `/hello`：项目的访问路径-->虚拟目录
    > 简化部署：将项目打成一个`war`包，再将`war`包放置到`webapps`目录下。
    >> `war`包会自动解压缩

2. 配置`conf/server.xml`文件
    在<Host>标签体中配置
    ```xml
    <Context docBase="D:\hello" path="/hehe" />
    ```
    > * `docBase`:项目存放的路径
    > * `path`：虚拟目录

3. 在`conf\Catalina\localhost`创建任意名称的`xml`文件
    在文件中编写
    ```xml
    <Context docBase="D:\hello" />
    ```
    > * 虚拟目录：xml文件的名称

* **java静态项目**的目录结构
    内部有html，js，css等静态网页文件
* **java动态项目**的目录结构：
    - 项目的根目录
        - 静态网页文件
        - WEB-INF目录（决定动态项目）：
            - web.xml：web项目的核心配置文件
            - classes目录：放置字节码文件的目录
            - lib目录：放置依赖的jar包