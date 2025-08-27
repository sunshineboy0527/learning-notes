# Mybatis

## 概述

MyBatis本是apache的一个开源项目iBatis，2010年这个项目由apache software foundation迁移到了google code，并且改名为MyBatis。2013年11月迁移到Github。

iBATIS一词来源于“internet”和“abatis”的组合，是一个基于Java的持久层框架。iBATIS提供的持久层框架包括SQL Maps和Data Access Objects（DAOs）。

## MyBatis的优势

1. **灵活性**

-   MyBatis 允许开发者编写原生 SQL 语句，这意味着开发者可以充分利用数据库的特性，编写高效的 SQL 查询。它不像一些其他 ORM 框架那样完全隐藏 SQL，而是将 SQL 的编写权交给开发者，使得开发者可以根据不同的数据库和业务需求，灵活地编写 SQL 语句。
-   支持存储过程调用。存储过程是数据库中的一种功能，它可以将一系列的 SQL 操作封装在一起，作为一个整体执行。MyBatis 能够方便地调用存储过程，这对于一些复杂的业务逻辑处理非常有帮助，可以减少应用程序与数据库之间的交互次数，提高性能。

2.  **与数据库的解耦**

-   MyBatis 通过配置文件（如 XML 文件）来定义 SQL 映射，将 SQL 语句与 Java 代码分离。这种分离方式使得应用程序与数据库之间的耦合度大大降低。当数据库表结构发生变化或者数据库类型更换时，只需要修改配置文件中的 SQL 映射，而不需要修改大量的 Java 代码。例如，从 MySQL 数据库迁移到 Oracle 数据库，只需要调整 SQL 语句和连接配置，Java 业务逻辑代码可以保持不变。

3.  **性能优势**

-   MyBatis 在执行 SQL 语句时，会对 SQL 进行预编译。预编译是指在执行 SQL 语句之前，数据库会先对 SQL 语句进行语法分析和优化，生成一个执行计划。这样在多次执行相同的 SQL 语句时，数据库可以直接使用已经优化好的执行计划，而不需要每次都重新解析和优化 SQL，从而提高了执行效率。
-   它支持延迟加载（Lazy Loading）。延迟加载是一种优化数据库访问性能的策略。在默认情况下，MyBatis 不会立即加载关联对象，只有在真正需要使用关联对象时，才会去数据库中查询。例如，在一个订单系统中，订单对象关联了客户对象。如果没有启用延迟加载，每次查询订单时都会同时查询客户信息，这可能会导致不必要的性能开销。而启用延迟加载后，只有在需要访问客户信息时，才会去查询客户表，减少了数据库的查询次数和数据传输量。

4.  **易于学习和使用**

-   MyBatis 的核心概念相对简单，主要包括 SQL 映射文件、Mapper 接口等。对于有一定 Java 基础和数据库基础的开发者来说，很容易上手。它的文档也非常详细，提供了丰富的示例和说明，帮助开发者快速理解和使用 MyBatis。

## CRUD操作

### 在使用代理类之前
创建Mapper接口

```java
interface Mapper{
    void testCar();
}
```

再创建Mapper.xml

```xml
<!--namespace为Mapper接口全包名-->
<mapper namespace="com.xxx.Mapper">
    <insert id="insertCar" parameterType="java.util.Map">
        insert into t_car(car_num,brand,guide_price,produce_time,car_type) values(#{carNum},#{brand},#{guidePrice},#{produceTime},#{carType})
    </insert>

    <insert id="insertCarByPOJO" parameterType="com.powernode.mybatis.pojo.Car">
        insert into t_car(car_num,brand,guide_price,produce_time,car_type) values(#{carNum},#{brand},#{guidePrice},#{produceTime},#{carType})
    </insert>

    <delete id="deleteByCarNum">
        delete from t_car where car_num = #{SuiBianXie}
    </delete>

    <update id="updateCarByPOJO">
        update t_car set 
            car_num = #{carNum}, brand = #{brand}, 
            guide_price = #{guidePrice}, produce_time = #{produceTime}, 
            car_type = #{carType} 
        where id = #{id}
    </update>

    <select id="selectCarById" resultType="com.powernode.mybatis.pojo.Car">
        select * from t_car where id = #{id}
    </select>

    <select id="selectCarAll" resultType="com.powernode.mybatis.pojo.Car">
        <!--记得使用as起别名，让查询结果的字段名和java类的属性名对应上。-->
        select
            id, car_num as carNum, brand, guide_price as guidePrice, produce_time as produceTime, car_type as carType
        from
            t_car
    </select>
</mapper>
```

再创建MapperImpl

```java
public void testCar(){
    // 开启SqlSession会话
    SqlSession sqlSession = SqlSessionUtil.openSession();

    // 执行sql语句
    // insert方法为mybatis内置基本的插入方法
    // 通过传入参数Mapper.xml文件中的sql语句id值来执行对应sql语句
    int count = sqlSession.insert("insertCar", car);            //插入

    // int count = sqlSession.delete("deleteByCarNum", "102");      //删除
    // int count = sqlSession.update("updateCarByPOJO", car);       //更新
    // Object car = sqlSession.selectOne("selectCarById", 1);       //查询单条记录
    // List<Object> cars = sqlSession.selectList("selectCarAll");   //查询多条记录

    //提交事务
    sqlSession.commit();
    //关闭会话连接
    sqlSeeson.close();
}
```

service层注入该Mapper对象，调用该方法

```java
class Service{
    Mapper mapper = new MapperImpl();

    void method(){
        mapper.testCar(); //调用Mapper实现类方法
        ...
    }
}
```

### 使用代理类之后

创建Mapper接口

```java
interface Mapper{
    int mapperInsert();
}
```

创建Mapper.xml映射文件

```xml
<!--namespace为Mapper接口全包名-->
<mapper namespace="com.xxx.Mapper">
    <insert id="mapperInsert" parameterType="java.util.Map">
        insert into t_car(car_num,brand,guide_price,produce_time,car_type) values(#{carNum},#{brand},#{guidePrice},#{produceTime},#{carType})
    </insert>
</mapper>
```

直接注入service层，并调用其方法

```java
class Service{
    Mapper mapper = SqlSessionUtil.openSession().getMapper(Mapper.class);

    void method(){
        mapper.mapperInsert(); //调用Mapper代理类根据xml映射文件自动生成的Dao方法
        ...
    }
}
```

## 注解

> 通过注解使用Mybatis

## XML映射文件(官方推荐方案)

> 通过在相同包下的相同名称的XML文件来进行Mybatis的使用

一个项目中，可以有多个的MyBatis映射文件

**规则**：
- 映射配置文件名与`Mapper`接口名一致,且放在**相同的包下**(同包同名)。
- 映射配置文件的`namespace`属性与`Mapper`接口的全类名一致。
- XML映射文件中sql语句的`id`与`Mapper`接口中的**方法名**一致。

### 核心配置文件

一个项目中，有一个唯一的MyBatis核心配置文件

- configuration：根标签，表示配置信息。
- environments：环境（多个），以“s”结尾表示复数，也就是说mybatis的环境可以配置多个数据源。
   - default属性：表示默认使用的是哪个环境，default后面填写的是environment的id。**default的值只需要和environment的id值一致即可**。
- environment：具体的环境配置（**主要包括：事务管理器的配置 + 数据源的配置**）
   - id：给当前环境一个唯一标识，该标识用在environments的default后面，用来指定默认环境的选择。
- transactionManager：配置事务管理器
   - type属性：指定事务管理器具体使用什么方式，可选值包括两个
      - **JDBC**：使用JDBC原生的事务管理机制。**底层原理：事务开启conn.setAutoCommit(false); ...处理业务...事务提交conn.commit();**
      - **MANAGED**：交给其它容器来管理事务，比如WebLogic、JBOSS等。如果没有管理事务的容器，则没有事务。**没有事务的含义：只要执行一条DML语句，则提交一次**。
- dataSource：指定数据源
   - type属性：用来指定具体使用的数据库连接池的策略，可选值包括三个
      - **UNPOOLED**：采用传统的获取连接的方式，虽然也实现Javax.sql.DataSource接口，但是并没有使用池的思想。
         - property可以是：
            - driver 这是 JDBC 驱动的 Java 类全限定名。
            - url 这是数据库的 JDBC URL 地址。
            - username 登录数据库的用户名。
            - password 登录数据库的密码。
            - defaultTransactionIsolationLevel 默认的连接事务隔离级别。
            - defaultNetworkTimeout 等待数据库操作完成的默认网络超时时间（单位：毫秒）
      - **POOLED**：采用传统的javax.sql.DataSource规范中的连接池，mybatis中有针对规范的实现。
         - property可以是（除了包含**UNPOOLED**中之外）：
            - poolMaximumActiveConnections 在任意时间可存在的活动（正在使用）连接数量，默认值：10
            - poolMaximumIdleConnections 任意时间可能存在的空闲连接数。
            - 其它....
      - **JNDI**：采用服务器提供的JNDI技术实现，来获取DataSource对象，不同的服务器所能拿到DataSource是不一样。如果不是web或者maven的war工程，JNDI是不能使用的。
         - property可以是（最多只包含以下两个属性）：
            - initial_context 这个属性用来在 InitialContext 中寻找上下文（即，initialContext.lookup(initial_context)）这是个可选属性，如果忽略，那么将会直接从 InitialContext 中寻找 data_source 属性。
            - data_source 这是引用数据源实例位置的上下文路径。提供了 initial_context 配置时会在其返回的上下文中进行查找，没有提供时则直接在 InitialContext 中查找。
- mappers：在mappers标签中可以配置多个sql映射文件的路径。
- mapper：配置某个sql映射文件的路径
   - resource属性：使用相对于类路径的资源引用方式
   - url属性：使用完全限定资源定位符（URL）方式

## 动态SQL

### `<if>` 标签

`<if>` 标签用于根据条件动态地添加 SQL 片段。
`<where>`标签用于配合`<if>`标签使用，会去除出现开头多余的`or`或`and`。
`<set>`标签会去除`<if>`标签内容中多余的`,`。

```xml
<select id="selectUsersByCondition" parameterType="com.example.model.UserCondition" resultType="com.example.model.User">
    SELECT * FROM users
    <where>
        <if test="name != null and name != ''">
            AND name = #{name}
        </if>
        <if test="age != null">
            AND age = #{age}
        </if>
    </where>
</select>
```
在这个例子中，`<if>` 标签根据 `UserCondition` 对象中的 `name` 和 `age` 属性的值，动态地添加 SQL 条件。如果 `name` 不为空，则添加 `AND name = #{name}` 条件；如果 `age` 不为空，则添加 `AND age = #{age}` 条件。这样，开发者可以根据不同的查询条件动态地生成 SQL 查询语句。

### `<choose>`、`<when>` 和 `<otherwise>` 标签

`<choose>`、`<when>` 和 `<otherwise>` 标签类似于 Java 中的 `switch` 语句，用于根据不同的条件选择不同的 SQL 片段。例如：

```xml
<select id="selectUsersByType" parameterType="int" resultType="com.example.model.User">
    SELECT * FROM users
    <where>
        <choose>
            <when test="type == 1">
                AND status = 'active'
            </when>
            <when test="type == 2">
                AND status = 'inactive'
            </when>
            <otherwise>
                AND status IS NOT NULL
            </otherwise>
        </choose>
    </where>
</select>
```
在这个例子中，`<choose>` 标签定义了一个条件选择结构。`<when>` 标签用于指定不同的条件分支，`<otherwise>` 标签用于指定默认分支。根据传入的 `type` 参数值，MyBatis 会选择对应的 SQL 片段添加到查询语句中。

### `<foreach>` 标签

`<foreach>` 标签用于处理集合类型的参数，例如在 SQL 查询中动态地添加多个条件。例如：

```xml
<select id="selectUsersByIds" parameterType="list" resultType="com.example.model.User">
    SELECT * FROM users
    <where>
        <foreach item="id" collection="list" open="(" separator="," close=")">
            id = #{id}
        </foreach>
    </where>
</select>
```

在这个例子中，`<foreach>` 标签用于处理传入的 `list` 参数。
- `item` 属性指定了集合中的每个元素的别名，
- `collection` 属性指定了集合的类型（这里是 `list`），
- `open` 和 `close` 属性指定了集合的起始和结束符号，
- `separator` 属性指定了集合元素之间的分隔符。

MyBatis 会根据集合中的元素动态地生成多个条件，并用逗号分隔，最终生成的 SQL 查询语句类似于：

```sql
SELECT * FROM users WHERE id = 1 OR id = 2 OR id = 3
```


## 其他

### MyBatis中接口代理机制及使用

使用javassist生成DaoImpl类

```java
package com.powernode.bank.utils;

import org.apache.ibatis.javassist.CannotCompileException;
import org.apache.ibatis.javassist.ClassPool;
import org.apache.ibatis.javassist.CtClass;
import org.apache.ibatis.javassist.CtMethod;
import org.apache.ibatis.session.SqlSession;

import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Arrays;

/**
 * 使用javassist库动态生成dao接口的实现类
 *
 * @author 老杜
 * @version 1.0
 * @since 1.0
 */
public class GenerateDaoByJavassist {

    /**
     * 根据dao接口生成dao接口的代理对象
     *
     * @param sqlSession   sql会话
     * @param daoInterface dao接口
     * @return dao接口代理对象
     */
    public static Object getMapper(SqlSession sqlSession, Class daoInterface) {
        ClassPool pool = ClassPool.getDefault();
        // 生成代理类
        CtClass ctClass = pool.makeClass(daoInterface.getPackageName() + ".impl." + daoInterface.getSimpleName() + "Impl");
        // 接口
        CtClass ctInterface = pool.makeClass(daoInterface.getName());
        // 代理类实现接口
        ctClass.addInterface(ctInterface);
        // 获取所有的方法
        Method[] methods = daoInterface.getDeclaredMethods();
        Arrays.stream(methods).forEach(method -> {
            // 拼接方法的签名
            StringBuilder methodStr = new StringBuilder();
            String returnTypeName = method.getReturnType().getName();
            methodStr.append(returnTypeName);
            methodStr.append(" ");
            String methodName = method.getName();
            methodStr.append(methodName);
            methodStr.append("(");
            Class<?>[] parameterTypes = method.getParameterTypes();
            for (int i = 0; i < parameterTypes.length; i++) {
                methodStr.append(parameterTypes[i].getName());
                methodStr.append(" arg");
                methodStr.append(i);
                if (i != parameterTypes.length - 1) {
                    methodStr.append(",");
                }
            }
            methodStr.append("){");
            // 方法体当中的代码怎么写？
            // 获取sqlId（这里非常重要：因为这行代码导致以后namespace必须是接口的全限定接口名，sqlId必须是接口中方法的方法名。）
            String sqlId = daoInterface.getName() + "." + methodName;
            // 获取SqlCommondType
            String sqlCommondTypeName = sqlSession.getConfiguration().getMappedStatement(sqlId).getSqlCommandType().name();
            if ("SELECT".equals(sqlCommondTypeName)) {
                methodStr.append("org.apache.ibatis.session.SqlSession sqlSession = com.powernode.bank.utils.SqlSessionUtil.openSession();");
                methodStr.append("Object obj = sqlSession.selectOne(\"" + sqlId + "\", arg0);");
                methodStr.append("return (" + returnTypeName + ")obj;");
            } else if ("UPDATE".equals(sqlCommondTypeName)) {
                methodStr.append("org.apache.ibatis.session.SqlSession sqlSession = com.powernode.bank.utils.SqlSessionUtil.openSession();");
                methodStr.append("int count = sqlSession.update(\"" + sqlId + "\", arg0);");
                methodStr.append("return count;");
            }
            methodStr.append("}");
            System.out.println(methodStr);
            try {
                // 创建CtMethod对象
                CtMethod ctMethod = CtMethod.make(methodStr.toString(), ctClass);
                ctMethod.setModifiers(Modifier.PUBLIC);
                // 将方法添加到类
                ctClass.addMethod(ctMethod);
            } catch (CannotCompileException e) {
                throw new RuntimeException(e);
            }
        });
        try {
            // 创建代理对象
            Class<?> aClass = ctClass.toClass();
            Constructor<?> defaultCon = aClass.getDeclaredConstructor();
            Object o = defaultCon.newInstance();
            return o;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
```

**namespace必须是dao接口的全限定名称，id必须是dao接口中的方法名**

以上所讲内容mybatis内部已经实现了:只需通过`sqlSession`调用`getMapper`方法即可

```java
AccountDao accountDao = (AccountDao)sqlSession.getMapper(AccountDao.class);
```

