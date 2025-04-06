# Mybatis

## 1. 概述

MyBatis本是apache的一个开源项目iBatis，2010年这个项目由apache software foundation迁移到了google code，并且改名为MyBatis。2013年11月迁移到Github。

iBATIS一词来源于“internet”和“abatis”的组合，是一个基于Java的持久层框架。iBATIS提供的持久层框架包括SQL Maps和Data Access Objects（DAOs）。

## 2. MyBatis的优势

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

## 3. CRUD操作

### 3.1 添加



### 3.2 删除



### 3.3 更新



### 3.4 查询

## 4. 注解

> 通过注解使用Mybatis

## 5. XML映射文件(官方推荐方案)

> 通过在相同包下的相同名称的XML文件来进行Mybatis的使用

**规则**：
- 映射配置文件名与`Mapper`接口名一致,且放在**相同的包下**(同包同名)。
- 映射配置文件的`namespace`属性与`Mapper`接口的全类名一致。
- XML映射文件中sql语句的`id`与`Mapper`接口中的**方法名**一致。

## 6. 动态SQL

### 6.1 `<if>` 标签

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

### 6.2 `<choose>`、`<when>` 和 `<otherwise>` 标签

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

### 6.3 `<foreach>` 标签

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
