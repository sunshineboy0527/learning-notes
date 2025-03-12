### MySQL基础知识(操作)

#### 开启服务:
1. services.msc 然后选择数据库启动或停止
2. cmd命令(需要以管理员身份运行) :
	开启数据库: `net start mysql80`
	停止数据库: `net stop mysql80`

#### 服务器连接(密码123456):
> 1. 利用MySQL 8.0 Command Line Client - Unicode进行连接
> 2. 通过控制台cmd输入指令: `mysql [-h 127.0.0.1] [-P 3306] -u root -p [password]`
>> * -h 表示连接其他ip地址的主机上的mysql
>> * password可以直接输入 也可以只写-p回车 接着再次输入密码
>> * 完整形式可以写为`mysql --h=127.0.0.1 --P=3306 --u=root --p=***`

#### 多表关系解决:
> 1. 一对多(多对一): 在多的一方建立外键,指向另一的一方的主键
> 2. 多对多: 建立中间表, 中间表中至少包含两个外键, 分别关联两方的主键
> 3. 一对一: 在任意一方加入外键, 关联另外一方的主键, 并且设置外键为唯一(UNIQUE)

#### 事务的四大特性:
> * 原子性（Atomicity）：事务是不可分割的最小操作单元，要么全部成功，要么全部失败。
> * 一致性（Consistency）：事务完成时，必须使所有的数据都保持一致状态。
> * 隔离性（Isolation）：数据库系统提供的隔离机制，保证事务在不受外部并发操作影响的独立环境下运行。
> * 持久性（Durability）：事务一旦提交或回滚，它对数据库中的数据的改变就是永久的。

#### 并发事务问题:
*概念*：多个事务之间隔离的，相互独立的。但是如果多个事务操作同一批数据，则会引发一些问题，设置不同的隔离级别就可以解决这些问题。
> * 赃读：一个事务读到另外一个事务还没有提交的数据。
> * 不可重复读：一个事务先后读取同一条记录，但两次读取的数据不同，称之为不可重复读。
> * 幻读：一个事务按照条件查询数据时，没有对应的数据行，但是在插入数据时，又发现这行数据已经存在，好像出现了 "幻影"。

---

### 相关指令cmd:
> 字段 属性列 行 元组行

#### DDL(Data Definition Language)数据定义语言
##### DDL-数据库操作:
* 查询所有数据库: `show databases;`
* 查询当前数据库: `select database();`
* 创建数据库: `create database [if not exists] 数据库名 [default charset 字符集] [collate 排序规则];`
* 删除数据库: `drop database [if exists] 数据库名;`
* 使用数据库: `use 数据库名;`

##### DDL-表操作:
* 查询当前数据库所有表: `show tables;`
* 查询表结构: `desc 表名;`
* 查询指定标的建表语句: `show create table 表名;`
* 创建表: `create table 表名(字段1 字段1类型[comment 字段1注释],...)[comment 表注释];`
* 向表中添加字段: `alter table 表名 add 字段名 类型(长度) [comment 注释] [约束];`
* 修改数据类型: `alter table 表名 modify 字段名 新数据类型(长度);`
* 修改字段名和字段类型: `alter table 表名 change 旧字段名 新字段名 类型(长度) [comment 注释] [约束];`
* 删除字段: `alter table 表名 drop 字段名;`
* 修改表名: `alter table 表名 rename to 新表名;`
* 删除表: `drop table [if exists] 表名;`
* 删除指定表,并重新创建该表: `truncate table 表名;`

#### DML(Data Manipulation Language)数据操作语言(增删改):
* 给指定字段添加数据: `insert into 表名 (字段名1,字段名2,...) values (值1,值2,...);`
* 给全部字段添加数据: `insert into 表名 values (值1,值2,...);`
* 批量添加数据: 
`- insert into 表名 (字段名1,字段名2,...) values (值1,值2,...), (值1,值2,...), (值1,值2,...);`
`- insert into 表名 values (值1,值2,...), (值1,值2,...), (值1,值2,...);`
* 修改数据: `update 表名 set 字段1 = 值1, 字段2 = 值2, ... [where 条件];`
* 删除数据: `delete from 表名 [where 条件];`

#### DQL(Data Query Language)数据查询语言(数据库中表的记录-数据):
>语法结构: 
> `select` 字段列表 `from` 表名列表 
> `where` 条件列表 
> `group by` 分组字段列表 
> `having` 分组后的条件 
> `order by` 排序字段列表 `limit` 分页参数

> `null`参与计算后，结果都为`null` 
>> `null + 3 = null`

* 执行顺序: 
`1.from` `2.where` `3.group by` `4.select` `5.order by` `6.limit`

* 查询多个字段: 
`select 字段1,字段2,... from 表名;`

* 查询所有字段: 
`select * from 表名;`

* 设置别名:
 `select 字段1 [as 别名1], 字段2 [as 别名2], ... from 表名;`

* 去除重复记录: 
`select distinct 字段列表 from 表名;`

* 条件查询: 
`select 字段列表 from 表名 where 条件列表;`
> * `> 、< 、<= 、>= 、= 、<>`
> * `BETWEEN...AND`
> * `IN( 集合)` 
> * `LIKE`：模糊查询
>> 占位符：
>> * `_`:单个任意字符
>> * `%`：多个任意字符
> * `IS NULL`  
> * `AND`  或 `&&`
> * `OR`  或 `||` 
> * `NOT`  或 `!`
>> 推荐使用`AND` `OR` `NOT`

* 利用聚合函数(null值不参与)查询: 
`select 聚合函数(字段列表) from 表名;`
> 聚合函数：将一列数据作为整体，进行纵向计算
> * count：计算个数
>> 			1. 一般选择非空的列：主键
>> 			2. count(*)
> * max：计算最大值
> * min：计算最小值
> * sum：计算和
> * avg：计算平均值
>
> **注意**：
> * 聚合函数的计算，排除null值。
>
> **解决方案**：
>  * 选择非空的列进行计算
>  * `IFNULL(列,替换的值)`函数

* 分组查询: 
`select 字段列表 from 表名 [where 条件] group by 分组字段名 [having 分组后过滤条件];`
> 查询的字段应为：分组字段，聚合函数

* 排序查询: 
`select 字段列表 from 表名 order by 字段1 排序方式1, 字段2 排序方式2,...;`
> `ASC`升序(默认),`DESC`降序
> 多字段排序: 当第一个字段值相同时,才能根据第二个字段进行排序

* 分页查询: 
`select 字段列表 from 表名 limit 起始索引,查询记录数;`
> 起始索引 = (页码-1) * 每页展示记录数
> `limit` 是 MySQL特有的
    
#### DCL(Data control Language)数据控制语言
##### DCL-管理数据库用户:
* 查询用户:
` use mysql;`
` select * from user;`
* 创建用户:
 `create user '用户名'@'主机名' identified by '密码';`
* 修改用户密码: 
`alter user '用户名'@'主机名' identified with mysql_native_password by '新密码';`
`UPDATE USER SET PASSWORD = PASSWORD('新密码') WHERE USER = '用户名';`
`SET PASSWORD FOR '用户名'@'主机名' = PASSWORD('新密码');`
> * mysql中忘记了root用户的密码？
>   * cmd -- > net stop mysql 停止mysql服务 需要管理员运行该cmd
>   * 使用无验证方式启动mysql服务： mysqld --skip-grant-tables
>   * 打开新的cmd窗口,直接输入mysql命令，敲回车。就可以登录成功
>   * use mysql;
>   * update user set password = password('你的新密码') where user =  'root';
>   * 关闭两个窗口
>   * 打开任务管理器，手动结束mysqld.exe 的进程
>   * 启动mysql服务
>   * 使用新密码登录。
* 删除用户:
 `drop user '用户名'@'主机名';`

##### DCL-权限控制:
常见权限:
|||
|:---:|:---:|
|`ALL, ALL PRIVILEGES`| 所有权限|
|`SELECT`|查询数据|
|`INSERT`|插入数据|
|`UPDATE`|修改数据|
|`DELETE`|删除数据|
|`ALTER`|修改表|
|`DROP`|删除数据库/表/视图|
|`CREATE`|创建数据库/表|

* 查询权限: 
`show grants for '用户名'@'主机名';`
* 授予权限: 
`grant 权限列表 on 数据库名.表名 to '用户名'@'主机名';`
* 撤销权限: 
`revoke 权限列表 on 数据库名.表名 from '用户名'@'主机名';`

---

#### 约束
##### 非空约束
* 非空约束：`not null`，某一列的值不能为`null`
	1. 创建表时添加约束
    ```sql
		CREATE TABLE stu(
			id INT,
			name VARCHAR(20) NOT NULL -- name为非空
		);
    ```
	2. 创建表完后，添加非空约束
		`ALTER TABLE stu MODIFY name VARCHAR(20) NOT NULL;`

	3. 删除name的非空约束
		`ALTER TABLE stu MODIFY name VARCHAR(20);`

##### 唯一约束
* 唯一约束：`unique`，某一列的值不能重复
	> 唯一约束可以有`NULL`值，但是只能有一条记录为`null`
	* 在创建表时，添加唯一约束
        ```sql
    	CREATE TABLE stu(
    		id INT,
    		phone_number VARCHAR(20) UNIQUE -- 手机号
    	);
        ```
	* 删除唯一约束
		`ALTER TABLE stu DROP INDEX phone_number;`
	* 在表创建完后，添加唯一约束
		`ALTER TABLE stu MODIFY phone_number VARCHAR(20) UNIQUE;`

##### 主键约束
* 主键约束：`primary key`
	> * 含义：非空且唯一
	>> * 一张表只能有一个字段为主键
	>> * 主键就是表中记录的唯一标识

	* 在创建表时，添加主键约束
        ```sql
		create table stu(
			id int primary key,-- 给id添加主键约束
			name varchar(20)
		);
        ```
	* 删除主键
		`ALTER TABLE stu DROP PRIMARY KEY;`
        > ~~`ALTER TABLE stu MODIFY id INT`~~ ;

	* 创建完表后，添加主键
		`ALTER TABLE stu MODIFY id INT PRIMARY KEY;`

	* 自动增长：
		> 如果某一列是数值类型的，使用 `auto_increment` 可以来完成值得自动增长
		* 在创建表时，添加主键约束，并且完成主键自增长
        ```sql
		create table stu(
			id int primary key auto_increment,-- 给id添加主键约束
			name varchar(20)
		);
        ```
		* 删除自动增长
		`ALTER TABLE stu MODIFY id INT;`
		* 添加自动增长
		`ALTER TABLE stu MODIFY id INT AUTO_INCREMENT;`

##### 外键约束:
> `foreign key`,让表于表产生关系，从而保证数据的正确性。
* 添加外键:
    * 建表时添加: 
    `CREATE TABLE 表名(字段名 数据类型,..., [CONSTRAINT] [外键名称] FOREIGN KEY (外键字段名) REFERENCES 主表 (主表列名));`
    ```sql
    create table 表名(
            ....,
            外键列,
            CONSTRAINT 外键名称 FOREIGN KEY (外键列名称)
            REFERENCES 主表名称(主表列名称)
        );
    ```
    * 建表后添加: 
    `ALTER TABLE 表名 ADD [CONSTRAINT 外键名称] FOREIGN KEY (外键字段名) REFERENCES 主表 (主表列名) ;`
    > 添加外键时若需要指定外键名则用`CONSTRAINT 外键名` ...
    > 否则系统会自动为该外键指定外键名

> MySQL：
>>  ```sql
>>  CREATE TABLE Orders(
>>      O_Id int NOT NULL,
>>      OrderNo int NOT NULL,
>>      P_Id int,
>>      PRIMARY KEY (O_Id),
>>      FOREIGN KEY (P_Id) REFERENCES Persons(P_Id)
>>  )
>>  ```
>
> SQL Server / Oracle / MS Access：
>> ```sql
>> CREATE TABLE Orders(
>>     O_Id int NOT NULL PRIMARY KEY,
>>     OrderNo int NOT NULL,
>>     P_Id int FOREIGN KEY REFERENCES Persons(P_Id)
>> )
>> ```
>
>如需命名 FOREIGN KEY 约束，并定义多个列的 FOREIGN KEY 约束，请使用下面的 SQL 语法：
>> MySQL / SQL Server / Oracle / MS Access：
> ```sql
> CREATE TABLE Orders(
>     O_Id int NOT NULL,
>     OrderNo int NOT NULL,
>     P_Id int,
>     PRIMARY KEY (O_Id),
>     CONSTRAINT fk_PerOrders FOREIGN KEY (P_Id)
>     REFERENCES Persons(P_Id)
> )
> ```

* 删除外键(MySQL): 
`ALTER TABLE 表名 DROP FOREIGN KEY 外键名称;`
> SQL Server / Oracle / MS Access：
>> `ALTER TABLE 表名 DROP CONSTRAINT 外键名`

* 删除/更新外键行为:
    * (默认行为)`NO ACTION`(与 `RESTRICT` 一致): 
    当在父表中删除/更新对应记录时，首先检查该记录是否有对应外键，如果有则不允许删除/更新。
    * `CASCADE`: 
    当在父表中删除/更新对应记录时，首先检查该记录是否有对应外键，如果有，则也删除/更新外键在子表中的记录。
    * `SET NULL`: 
    当在父表中删除对应记录时，首先检查该记录是否有对应外键，如果有则设置子表中该外键值为null（这就要求该外键允许取null）。
    **语法**: 
    `ALTER TABLE 表名 ADD CONSTRAINT 外键名称 FOREIGN KEY (外键字段) REFERENCES 主表名 (主表字段名) ON UPDATE CASCADE ON DELETE CASCADE;`
* 级联操作
    * 添加级联操作
        语法：`ALTER TABLE 表名 ADD CONSTRAINT 外键名称 FOREIGN KEY (外键字段名称) REFERENCES 主表名称(主表列名称) ON UPDATE CASCADE ON DELETE CASCADE;`
    * 分类：
        * 级联更新：`ON UPDATE CASCADE` 
        * 级联删除：`ON DELETE CASCADE` 
    > 级联操作：在删除数据时，连同外键与其关联的数据行一同删除
    >> **谨慎使用**

#### 数据库的备份和还原

命令行：
* 语法：
    * 备份： `mysqldump -u 用户名 -p 密码 数据库名称 > 保存的路径`
    * 还原：
        1. 登录数据库
        2. 创建数据库 `create database;`
        3. 使用数据库 `use`
        4. 执行文件。`source 文件路径`

#### 多表查询:
连接查询: 
* 内连接查询:
    隐式内连接: `select 字段列表 from 表1, 表2 where 条件...;`
    显示内连接: `select 字段列表 from 表1 [inner] join 表2 on 连接条件...;`
> 连接查询: 查询两张表交集的部分
>
>一般将为每张表起一个别名，方便调用
>> * 笛卡尔积：
>>    * 有两个集合A,B .取这两个集合的所有组成情况。
>>    * 要完成多表查询，需要消除无用的数据

* 外连接查询:
    左外连接: `select 字段列表 from 表1 left [outer] join 表2 on 条件...;`
    右外连接: `select 字段列表 from 表1 right [outer] join 表2 on 条件...;`
> 外连接查询: 相当于查询表1(左表)/表2(右表)的所有数据, 包含表1和表2交集部分的数据

* 自连接查询:
    自连接: `select 字段列表 from 表A 别名A join 表A 别名B on 条件...;`
> 自连接查询: 可以是内连接查询,也可以是外连接查询

* 联合查询:
    联合查询: `select 字段列表 from 表A... UNION [All] select 字段列表 from 表B...;`
> 联合查询: 将多次查询的结果给合并起来,形成一张新的查询结果集-ALL可对结果去重
> 字段列表数量与各个类型要一致

* 子查询:---嵌套查询
    子查询: `select * from t1 where column1 = (select column1 from t2);`
    >
    * 标量子查询(返回结果为单个值),
    > 子查询的结果是单行单列的:
    >> 子查询可以作为条件，使用运算符去判断。 
    >> 运算符： `> >= < <= =` 
    * 列子查询(子查询结果为一列),
    > 子查询的结果是多行单列的：
	>> 子查询可以作为条件，使用运算符`IN ANY ALL`来判断
    >>> `IN`：在指定项内，同 `IN(项1,项2,…)`。
    >>> `ANY`：与比较操作符联合使用，表示与子查询返回的任何值比较为 `TRUE` ，则返回 `TRUE` 。
    >>> `SOME`：`ANY` 的别名，较少使用。
    >>> `ALL`：与比较操作符联合使用，表示与子查询返回的所有值比较都为 `TRUE` ，则返回 `TRUE`
    
    * 行子查询(子查询结果为一行)
    > 行子查询是指子查询返回的结果集是一行 N 列，该子查询的结果通常是对表的某行数据进行查询而返回的结果集。
    > `SELECT * FROM article WHERE (title,content,uid) = (SELECT title,content,uid FROM blog WHERE bid=2)`

    * 表子查询(子查询结果为多行多列)
    > 子查询的结果是多行多列的：
	> 子查询可以作为一张*虚拟表*参与查询
    > 将子查询结果作为*虚拟表*

 > 子查询: 嵌套查询
	
#### 事务:
* 查看/设置事务提交方式:
    查询事务是否为自动提交: 
    `select @@autocommit;`
    设置事务提交方式: 
    `set @@autocommit = 0;`
> 隐式操作

* 开启事务(与第一个类似): 
 `start transaction 或 begin;`
> 显式开启事务

* 提交事务: `commit;`
* 回滚事务: `rollback;`
> 回滚事务，撤销之前已执行但未提交的工作。

* 修改事务的默认提交方式：
    * 查看事务的默认提交方式：`SELECT @@autocommit;` `1 代表自动提交  0 代表手动提交`
    * 修改默认提交方式： `set @@autocommit = 0;`

##### 事务隔离级别:
* 查看事务隔离级别:
    `SELECT @@TRANSACTION_ISOLATION;`
* 设置事务隔离级别:	
    `SET [ SESSION | GLOBAL ] TRANSACTION ISOLATION LEVEL { READ UNCOMMITTED | READ COMMITTED | REPEATABLE READ | SERIALIZABLE }`

|隔离级别|问题|
|:---:|:---:|
|`READ UNCOMMITTED`|脏读、不可重复读、幻读|
|`READ COMMITTED`|不可重复读、幻读|
|`REPEATABLE READ`(**MySQL默认**)| 产生的问题：幻读|
|`SERIALIZABLE`| 可以解决所有的问题|

> 事务隔离级别:事务隔离级别越高，数据越安全，但是性能越低。