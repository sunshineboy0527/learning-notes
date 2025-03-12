## JDBC：
概念：`Java DataBase Connectivity`  Java 数据库连接， Java语言操作数据库
> JDBC本质：其实是官方（sun公司）定义的一套操作所有关系型数据库的规则，即接口。各个数据库厂商去实现这套接口，提供数据库驱动jar包。我们可以使用这套接口（JDBC）编程，真正执行的代码是驱动jar包中的实现类。

> **大致操作步骤**：
> 1. 导入驱动`jar`包 `mysql-connector-java-8.0.22.jar`
    > * 复制`mysql-connector-java-8.0.22.jar`到项目的`libs`目录下
    > * 右键-->`Add As Library`
> 2. 注册驱动 利用`jdk`自带的`sql`中的`Driver`类，将指定的数据库驱动与`DriverManager`建立绑定，内部自动创建绑定了驱动的`DriverManager`(驱动管理器)对象
> 3. 获取数据库连接对象 `Connection`
> 4. 定义`sql`语句: `String`类型字符串
> 5. 获取执行`sql`语句的对象: `Statement`
> 6. 执行sql，接受返回结果
> 7. 处理结果
> 8. 释放资源

> `MySQL8`以上的驱动要求声明时区，
> 在`jdbc`连接的`url`后面加上`serverTimezone=UTC`即可解决问题

* 代码实现：
```java
    //1. 导入驱动jar包
    //2.注册驱动
    //Class.forName("com.mysql.jdbc.Driver");
    Class.forName("com.mysql.cj.jdbc.Driver");//mysql8版本类位置
    //3.获取数据库连接对象
    Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/db3", "root", "root");
    //4.定义sql语句
    String sql = "update account set balance = 500 where id = 1";
    //5.获取执行sql的对象 Statement
    Statement stmt = conn.createStatement();
    //6.执行sql
    int count = stmt.executeUpdate(sql);
    //7.处理结果
    System.out.println(count);
    //8.释放资源
    stmt.close();
    conn.close();
```
> 注意：`MySQL`服务器返回的时间区域值无法被`JDBC`驱动识别，或者该时间区域值可能对应多个不同的时区。解决这个问题的方法是明确配置`JDBC`连接字符串中的`serverTimezone`参数，指定一个具体的时间区域。
> * `?serverTimezone=Asia/Shanghai`    在连接数据库时，在要连接的数据库名后添加`?serverTimezone=UTC` `UTC为具体某一时区`

#### 1. DriverManager：驱动管理对象
* 功能：
    * 注册驱动：告诉程序该使用哪一个数据库驱动jar
       > 注册给定的驱动程序`DriverManager`: 
       > `static void registerDriver(Driver driver)`

        > *写代码使用*:
        > `Class.forName("com.mysql.jdbc.Driver");`
        > 在加载所指定的驱动类到内存时，会自动调用静态代码块，将指定的驱动与`DriverManager`绑定
        
        通过查看源码发现：在`com.mysql.jdbc.Driver`类中存在静态代码块
        ```java
            static {
                try {
                    java.sql.DriverManager.registerDriver(new Driver());
                } catch (SQLException E) {
                    throw new RuntimeException("Can't register driver!");
                }
            }
        ```
        > 注意：mysql5之后的驱动jar包可以省略注册驱动的步骤。
    * 获取数据库连接：
        * 方法：`static Connection getConnection(String url, String user, String password)`
        * 参数：
            * `url`：指定连接的路径
                * 语法：`jdbc:mysql://ip地址(域名):端口号/数据库名称`
                * 例子：`jdbc:mysql://localhost:3306/db3`
                * 细节：如果连接的是本机`mysql`服务器，并且`mysql`服务默认端口是`3306`，则`url`可以简写为：`jdbc:mysql:///`数据库名称
            * `user`：用户名
            * `password`：密码 
#### 2. Connection：数据库连接对象(需要释放)
1. 功能：
    * 获取执行sql 的对象
        * `Statement createStatement()`
        * `PreparedStatement prepareStatement(String sql)`  
    * 管理事务：
        * 开启事务：`setAutoCommit(boolean autoCommit)`
        > 调用该方法设置参数为`false`，即开启事务
        * 提交事务：`commit()` 
        * 回滚事务：`rollback()`
#### 3. Statement：执行sql的对象(需要释放)
执行`sql`
* `boolean execute(String sql)` 
> 可以执行任意的sql 了解 
* `int executeUpdate(String sql)`
>

> 执行`DML（insert、update、delete）`语句、`DDL(create，alter、drop)`语句
>
> *返回值*：影响的行数，可以通过这个影响的行数判断`DML`语句是否执行成功 返回值`>0`的则执行成功，反之，则失败。
* `ResultSet executeQuery(String sql)`
>

> 执行`DQL(select)`语句
#### 4. ResultSet：结果集对象,封装查询结果(需要释放)
* `boolean next()`: 游标向下移动一行，判断当前行是否是最后一行末尾(是否有数据)，如果是，则返回`false`，如果不是则返回`true`
* `getXxx(参数)`:获取数据
    * `Xxx`：代表数据类型
    > 如： `int getInt()` ,	`String getString()`
    * 参数：
        * `int`：代表列的编号,从1开始   
        > 如： `getString(1)`
        * `String`：代表列名称
        > 如： `getDouble("balance")`

* 注意：
    获取表中数据建议加上判断或直接利用while循环遍历
    * 游标向下移动一行
    * 判断是否有数据
    * 获取数据

    ```java
    //循环判断游标是否是最后一行末尾
    while(rs.next()){
        //获取数据
        int id = rs.getInt(1);
        String name = rs.getString("name");
        double balance = rs.getDouble(3);

        System.out.println(id + "---" + name + "---" + balance);
    }
    ```
#### 5. PreparedStatement：执行sql的对象
1. SQL注入问题：在拼接`sql`时，有一些`sql`的特殊关键字参与字符串的拼接。会造成安全性问题
    > * 输入用户随便，输入密码：a' or 'a' = 'a
    > * sql：`select * from user where username = 'fhdsjkf' and password = 'a' or 'a' = 'a'` 

2. 解决`sql`注入问题：使用`PreparedStatement`对象来解决
3. 预编译的SQL：参数使用`?`作为占位符
4. 步骤：
    > * 导入驱动`jar`包 `mysql-connector-java-8.0.22.jar`
    > * 注册驱动
    > * 获取数据库连接对象 `Connection`
    > * 定义`sql`
    >   * 注意：sql的参数使用`?`作为占位符。 
    > 如：`select * from user where username = ? and password = ?;`
    >   * 获取执行sql语句的对象 
    > `PreparedStatement  Connection.prepareStatement (String sql)`
    > * 给`？`赋值：
    >     * 方法： `setXxx(参数1,参数2)`
    >         * `参数1`：`？`的位置编号 从1 开始
    >         * `参数2`：`？`的值
    > * 执行`sql`，接受返回结果，不需要传递`sql`语句
    > * 处理结果
    > * 释放资源

5. 注意：后期都会使用`PreparedStatement`来完成增删改查的所有操作
    > * 可以防止SQL注入
    > * 效率更高

#### JDBC控制事务：
1. 事务：一个包含多个步骤的业务操作。如果这个业务操作被事务管理，则这多个步骤要么同时成功，要么同时失败。
2. 操作：
    1. 开启事务
    2. 提交事务
    3. 回滚事务
3. 使用`Connection`对象来管理事务
    * 开启事务：`setAutoCommit(boolean autoCommit)` ：调用该方法设置参数为`false`，即开启事务
        * 在执行`sql`之前开启事务
    * 提交事务：`commit()` 
        * 当所有`sql`都执行完提交事务
    * 回滚事务：`rollback()` 
        * 在`catch`中回滚事务
> 在开启事务后，在调用`execute`方法执行`sql`语句中间出现异常，导致下方`sql`语句无法成功执行，且数据并没执行`commit()`提交，此时之前执行成功得到的结果并不会改变数据库中的数据，在`catch`捕获异常代码块中，通过`rollback()`方法回滚事务，撤销前面已执行单位提交的`sql`语句。

#### JDBC工具类
为了简化代码，将每次使用都要使用的公共部分抽取到JDBC工具类中，便于后续使用。
* 在加载工具类时，同时注册驱动
* 抽取一个方法获取连接对象
* 抽取一个方法释放资源
> 通过使用配置文件的方式，从配置文件中读取对应参数，增强代码可维护性

#### JDBC连接池
1. 概念：其实就是一个容器(集合)，存放数据库连接的容器。
> 当系统初始化好后，容器被创建，容器中会申请一些连接对象，当用户来访问数据库时，从容器中获取连接对象，用户访问完之后，会将连接对象归还给容器。

2. 好处：
    * 节约资源
    * 用户访问高效

3. 实现：
    * 标准接口：`DataSource`   javax.sql包下的
        * 获取连接：`getConnection()`
        * 归还连接：`Connection.close()`。
        > 如果连接对象`Connection`是从连接池中获取的，那么调用`Connection.close()`方法，则不会再关闭连接,而是归还连接。

> 一般我们不去实现它，有数据库厂商来实现
> * `C3P0`：数据库连接池技术
> * `Druid`：数据库连接池实现技术，由阿里巴巴提供的

> 通过配置文件配置相应的数据来配置相应配置
> 连接参数 驱动类,连接数据库地址,用户名,密码
> 连接池参数 初始连接池大小,最大连接池大小,超时检查时间

##### C3P0：数据库连接池技术
1. 导入jar包 (两个) 
`c3p0-0.9.5.2.jar `
`mchange-commons-java-0.2.12.jar`
> * 不要忘记导入数据库驱动jar包
2. 定义配置文件：
    * 名称： `c3p0.properties` 或者 `c3p0-config.xml` 会自动加载
    * 路径：直接将文件放在src目录下即可。
3. 创建核心对象 数据库连接池对象 `ComboPooledDataSource`
> 调用无参，使用默认配置
> 调用有参，使用配置文件中指定配置
4. 获取连接： `getConnection()`
* 代码：
```java
    //1.创建数据库连接池对象
    DataSource ds  = new ComboPooledDataSource();
    //2. 获取连接对象
    Connection conn = ds.getConnection();
```
##### Druid：数据库连接池实现技术，由阿里巴巴提供的
1. 导入jar包 `druid-1.0.9.jar`
2. 定义配置文件：
    * 是`properties`形式的
    * 可以叫任意名称，可以放在任意目录下
3. 加载配置文件。`Properties`
4. 获取数据库连接池对象：通过工厂来来获取  `DruidDataSourceFactory`
5. 获取连接：`getConnection`
* 代码：
```java
    //加载配置文件
    Properties pro = new Properties();
    InputStream is = DruidDemo.class.getClassLoader().getResourceAsStream("druid.properties");
    pro.load(is);
    //获取连接池对象
    DataSource ds = DruidDataSourceFactory.createDataSource(pro);
    //获取连接
    Connection conn = ds.getConnection();
```

*定义工具类*
> 1. 定义一个类 JDBCUtils
> 2. 提供静态代码块加载配置文件，初始化连接池对象
> 3. 提供方法
>     * 获取连接方法：通过数据库连接池获取连接
>     * 释放资源
>     * 获取连接池的方法


* 代码：
```java
public class JDBCUtils {
    //1.定义成员变量 DataSource
    private static DataSource ds ;

    static{
        try {
            //1.加载配置文件
            Properties pro = new Properties();
            pro.load(JDBCUtils.class.getClassLoader().getResourceAsStream("druid.properties"));
            //2.获取DataSource
            ds = DruidDataSourceFactory.createDataSource(pro);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    /**
        * 获取连接
        */
    public static Connection getConnection() throws SQLException {
        return ds.getConnection();
    }
    /**
    * 释放资源
    */
    public static void close(Statement stmt,Connection conn){
        /* if(stmt != null){
            try {
                stmt.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        if(conn != null){
            try {
                conn.close();//归还连接
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }*/
        close(null,stmt,conn);
    }
    /**
     *  释放资源
     * 重载方法
     */
    public static void close(ResultSet rs , Statement stmt, Connection conn){
        if(rs != null){
            try {
                rs.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        if(stmt != null){
            try {
                stmt.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        if(conn != null){
            try {
                conn.close();//归还连接
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
    /**
        * 获取连接池方法
        */
    public static DataSource getDataSource(){
        return  ds;
    }
}
```
> 其中`Connection`对象并不是释放 而是归还给连接池`DataSource`

#### Spring JDBCTemplate
概念：`Spring`框架对JDBC的简单封装。提供了一个`JDBCTemplate`对象简化`JDBC`的开发。

**使用**：
1. 导入jar包
2. 创建`JdbcTemplate`对象。
    * `JdbcTemplate template = new JdbcTemplate(ds);`
> `JdbcTemplate`对象依赖于数据源`DataSource`
3. 调用`JdbcTemplate`的方法来完成CRUD的操作
    > 参数 `sql语句` `(其他...)`
    * `update()`:执行DML语句。增、删、改语句
    * `queryForMap()`:查询结果将结果集封装为`map`集合，将列名作为`key`，将值作为`value` 将这条记录封装为一个`map`集合
    > * 注意：这个方法查询的结果集长度只能是1
    * `queryForList()`:查询结果将结果集封装为list集合
    > * 注意：将每一条记录封装为一个`Map`集合，再将`Map`集合装载到`List`集合中
    * `query()`:查询结果，将结果封装为`JavaBean`对象
        * `query`的参数：`RowMapper`
            * 一般我们使用`BeanPropertyRowMapper`实现类。可以完成数据到`JavaBean`的自动封装
            * `new BeanPropertyRowMapper<类型>(类型.class)`
    ```java
    //自己实现query方法的第二个参数
    //RowMapper接口
    String sql = "select * from emp";
    List<Emp> list = template.query(sql, new RowMapper<Emp>() {
        @Override
        public Emp mapRow(ResultSet rs, int i) throws SQLException {
            Emp emp = new Emp();
            int id = rs.getInt("id");
            String ename = rs.getString("ename");
            int job_id = rs.getInt("job_id");
            int mgr = rs.getInt("mgr");
            Date joindate = rs.getDate("joindate");
            double salary = rs.getDouble("salary");
            double bonus = rs.getDouble("bonus");
            int dept_id = rs.getInt("dept_id");

            emp.setId(id);
            emp.setEname(ename);
            emp.setJob_id(job_id);
            emp.setMgr(mgr);
            emp.setJoindate(joindate);
            emp.setSalary(salary);
            emp.setBonus(bonus);
            emp.setDept_id(dept_id);

            return emp;
        }
    });
    ```
    > 自己定义匿名内部类中的具体处理操作
    * `queryForObject`：查询结果，将结果封装为对象
        * 一般用于聚合函数的查询