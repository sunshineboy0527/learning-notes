# 整理一些比较重要的MySQL知识

---

## 存储引擎

### 概述
MySQL常见的存储引擎包括InnoDB、MyISAM、Memory、Archive等。每个存储引擎都有自己的特点和适用场景。

- InnoDB引擎支持事务和行级锁定，适用于需要高并发读写的应用；
- MyISAM引擎不支持事务，但适用于读操作较多的应用；
- Memory引擎数据全部存储在内存中，适用于对读写速度要求很高的应用等等。

具体如下：
1.  InnoDB：
    - MySQL默认的事务型存储引擎
    - 支持ACID事务
    - 具有较好的并发性能和数据完整性
    - 支持行级锁定。
    - 适用于大多数应用场景，尤其是需要事务支持的应用。 
2.  MyISAM：
    - 是MySQL早期版本中常用的存储引擎
    - 支持全文索引和表级锁定
    - 不支持事务
    - 由于其简单性和高性能，在某些特定的应用场景中会得到广泛应用，如**读密集**的应用。 
3.  MEMORY：
    - 称为HEAP，是将表存储在内存中的存储引擎
    - 具有非常高的读写性能，但数据会在服务器重启时丢失。
    - 适用于需要快速读写的临时数据集、缓存和临时表等场景。 
4.  CSV：
    - 将数据以纯文本格式存储的存储引擎
    - 适用于需要处理和导入/导出CSV格式数据的场景。 
5.  ARCHIVE：
    - 将数据高效地进行压缩和存储的存储引擎
    - 适用于需要长期存储大量历史数据且不经常查询的场景。 

### 查看存储引擎
使用以下命令可以查看所有的存储引擎

```sql
show engines \G;
```

MySQL默认的存储引擎是：`InnoDB`

### 指定存储引擎
在MySQL中，你可以在创建表时指定使用的存储引擎。
通过在CREATE TABLE语句中使用ENGINE关键字，你可以指定要使用的存储引擎。

```sql
CREATE TABLE my_table (column1 INT, column2 VARCHAR(50)) ENGINE = InnoDB; # 通过ENGINE来指定
```

### 修改存储引擎
MySQL中，你可以通过ALTER TABLE语句修改表的存储引擎。下面是修改存储引擎的示例：

```sql
ALTER TABLE my_table ENGINE = MyISAM;
```

在修改存储引擎之前，你需要考虑以下几点：

1.  修改存储引擎可能需要执行复制表的操作，因此可能会造成数据的丢失或不可用。确保在执行修改之前备份你的数据。 
2.  不是所有的存储引擎都支持相同的功能。要确保你选择的新存储引擎支持你应用程序所需的功能。 
3.  修改表的存储引擎可能会影响到现有的应用程序和查询。确保在修改之前评估和测试所有的影响。 
4.  ALTER TABLE语句可能需要适当的权限才能执行。确保你拥有足够的权限来执行修改存储引擎的操作。

---

## 索引

### 索引的创建
1. 主键字段会自动添加索引，不需要程序员干涉，主键字段上的索引被称为`主键索引`

2. unique约束的字段也会自动添加索引，不需要程序员干涉，这种字段上添加的索引称为`唯一索引`

3. 给特定字段添加索引

```sql
# 建表时添加索引：
CREATE TABLE emp (
    ...
    name varchar(255),
    ...
    INDEX idx_name (name)
);
```

```sql
# 建表完成后以修改表结构方式添加
ALTER TABLE emp ADD INDEX idx_name (name);
```

```sql
# 后续添加
create index idx_name on emp(name);
```

### 索引的删除
删除指定字段上的索引

```sql
ALTER TABLE emp DROP INDEX idx_name;
```

### 查看某张表上添加了哪些索引

```sql
show index from 表名;
```

### 索引的分类

不同的`存储引擎`有不同的索引类型和实现：

- **按照数据结构分类**：
   - B+树 索引（mysql的InnoDB存储引擎采用的就是这种索引）采用 B+树  的数据结构
   - Hash 索引（仅 `memory` 存储引擎支持）：采用  哈希表  的数据结构
- **按照物理存储分类**：
   - 聚集索引：索引和表中数据在一起，数据存储的时候就是按照索引顺序存储的。一张表只能有一个聚集索引。
   - 非聚集索引：索引和表中数据是分开的，索引是独立于表空间的，一张表可以有多个非聚集索引。
- **按照字段特性分类**：
   - 主键索引（primary key）
   - 唯一索引（unique）
   - 普通索引（index）
   - 全文索引（fulltext：仅 `InnoDB和MyISAM` 存储引擎支持）
- **按照字段个数分类**：
   - 单列索引、联合索引（也叫复合索引、组合索引）

**！！！MySQL索引采用了B+树数据结构（采用16阶）**

### MySQL索引采用B+树

> B Trees数据结构存在的缺点是：**不适合做区间查找，对于区间查找效率较低**。假设要查id在[3~7]之间的，需要查找的是3,4,5,6,7。那么查这每个索引值都需要从头节点开始。**因此MySQL使用了B+ Trees解决了这个问题。**

**B+树相较于B树的改进**：
- B+树将数据都存储在叶子节点中。并且叶子节点之间使用链表连接，这样很适合范围查询。
- B+树的非叶子节点上只有索引值，没有数据，所以非叶子节点可以存储更多的索引值，这样让B+树更矮更胖，提高检索效率。

![未命名文件 (1).png](https://cdn.nlark.com/yuque/0/2023/png/21376908/1692349477753-ce686f45-052c-4935-9212-5edf0f73149f.png#averageHue=%23060604&clientId=ua5acc0fc-19f8-4&from=paste&height=605&id=u5c2e3e09&originHeight=605&originWidth=1189&originalType=binary&ratio=1&rotation=0&showTitle=false&size=53656&status=done&style=shadow&taskId=ubbc8ad77-4829-41f1-b628-6d554d4e9ca&title=&width=1189)

### 经典面试题：

1. **mysql为什么选择B+树作为索引的数据结构，而不是B树？**

- 非叶子节点上可以存储更多的键值，阶数可以更大，更矮更胖，磁盘IO次数少，数据查询效率高。
- 所有**数据都是有序存储在叶子节点**上，让范围查找，分组查找效率更高。
- 数据页之间、数据记录之间**采用链表链接**，让升序降序更加方便操作。

2. **如果一张表没有主键索引，那还会创建B+树吗？**
当一张表没有主键索引时，默认会使用一个隐藏的内置的聚集索引（clustered index）。这个聚集索引是基于表的物理存储顺序构建的，通常是使用B+树来实现的。

### 索引调优

> 若只有一个主键索引，而没有任何其他二级索引，查找时会进行全表扫描

> **二级索引数据结构**：B+树，叶子节点存放的数据为该表的主键值，查询数据时会现根据条件查找到对应记录的主键值，再通过回表操作(回到原数据表)进行查找

**二级索引**：二级索引也属于非聚集索引。也有人把二级索引称为辅助索引。

![二级索引数据结构.png](https://cdn.nlark.com/yuque/0/2023/png/21376908/1692417425624-818e9980-dbe6-4470-a4b2-9c91b33ca2b6.png#averageHue=%23fcfcfc&clientId=u333d438f-7a08-4&from=paste&height=312&id=ud7db5feb&originHeight=312&originWidth=1045&originalType=binary&ratio=1&rotation=0&showTitle=false&size=20570&status=done&style=shadow&taskId=ud87cd638-0631-45e1-8db2-692fa8231ae&title=&width=1045)

```sql
复合索引为：idx_a_b_c (a, b, c)

# (完全遵循最左前缀)（索引效果最佳）
WHERE a = 1 AND b = 2 AND c = 3

# (完全遵循最左前缀) 采用部分索引，连续使用，效果良好
WHERE a = 1 AND b = 2

# (完全遵循最左前缀) 索引仍然有效！ MySQL的查询优化器非常智能，它会根据索引的定义顺序重排你的查询条件。
# 它会识别出a=1是索引的最左列，然后按(a, b)的顺序来使用索引。所以，SQL中条件的书写顺序不重要，优化器会帮你调整。
WHERE b = 2 AND a = 1 （注意顺序！）

# (部分匹配左前缀) 条件从a开始，但跳过了b，c列在这个查询中不会被用于索引查找
WHERE a = 1 AND c = 3
```

> 若`where`条件后字段包含了复合索引的最左边字段，但是顺序不对，此时仍然会采用索引，SQL中条件的书写顺序不重要，优化器会帮你调整。

> **违反最左前缀（索引失效，全表扫描）**

**最左前缀原则**：MySQL在使用复合索引时，会从索引定义的最左边的列开始，向右连续匹配，直到遇到范围查询（`>`, `<`, `BETWEEN`, `LIKE`）等停止匹配。

**索引下推**：是一种**减少回表次数**的优化。它在存储引擎层提前过滤掉**不符合条件**的记录，让需要回表的记录数变少。（MySQL底层默认自动执行）
将查询中的过滤条件下推到索引层级中处理，从而减少回表次数，优化查询性能。

（在使用索引下推时，MySQL 会在索引的叶节点层级执行查询的过滤条件，过滤掉无用的索引记录，仅返回符合条件的记录的主键，这样就可以避免查询时回表读取表格的数据行，从而缩短了整个查询过程的时间。）

> 覆盖索引看的是`select`后的字段

**覆盖索引**：是一种**避免回表**的优化。只有在DQL语句**查找的字段全部存在于设置的索引**中才会进行索引覆盖，查找的字段中若有一个不存在于设置的索引中，就会导致回表操作

### 索引创建原则
1. 表数据量庞大，通常超过百万条数据。
2. 经常出现在where，order by，group by后面的字段建议添加索引。
3. 创建索引的字段尽量具有很强的唯一性。
4. 如果字段存储文本，内容较大，一定要创建前缀索引。
5. 尽量使用复合索引，使用单列索引容易回表查询。
6. 如果一个字段中的数据不会为NULL，建议建表时添加not null约束，这样优化器就知道使用哪个索引列更加有效。
7. 不要创建太多索引，当对数据进行增删改的时候，索引需要重新重新排序。
8. 如果很少的查询，经常的增删改不建议加索引。

---

## MySQL优化

除了上述索引调优外还有以下一些：

### 查看数据库整体情况

通过以下命令可以查看当前数据库在SQL语句执行方面的整体情况：

```sql
# 反映了从 MySQL 服务器启动到当前时刻，各个操作总数
show global status like 'Com_select'; # SELECT 总数
show global status like 'Com_insert'; # INSERT 总数
show global status like 'Com_delete'; # DELETE 总数
show global status like 'Com_update'; # UPDATE 总数

show global status like 'Com_______'; # 查看各个操作执行总数
```

可以了解 MySQL 服务器的长期执行情况，并在优化查询性能时，帮助我们了解 MySQL 的性能瓶颈。

### 慢查询日志
慢查询日志文件可以将查询较慢的DQL语句记录下来，便于我们定位需要调优的select语句。

```sql
# 查询日志功能是否开启
show variables like 'slow_query_log';
```

慢查询日志功能默认是关闭的。请修改my.ini文件来开启慢查询日志功能，在my.ini的[mysqld]后面添加如下配置：

```sql
[mysqld]
slow_query_log=1 # 表示开启慢查询日志功能
long_query_time=3 # 表示只要SELECT语句的执行耗时超过3秒则将其记录到慢查询日志中。
```

慢查询日志文件默认存储在：`C:\dev\mysql-8.0.36-winx64\data`目录下，默认的名字是：`计算机名-slow.log`

### show profiles
通过show profiles可以查看一个SQL语句在执行过程中具体的耗时情况。帮助我们更好的定位问题所在。


查看当前数据库是否支持 profile操作：
```sql
select @@have_profiling;
```

查看 profiling 开关是否打开：

```sql
select @@profiling;
```

将 profiling 开关打开：

```sql
set profiling = 1;
```

可以执行多条DQL语句，然后使用 show profiles; 来查看当前数据库中执行过的每个SELECT语句的耗时情况。

```sql
select empno,ename from emp;
select empno,ename from emp where empno=7369;
select count(*) from emp;
show profiles;
```

查看某个SQL语句语句在执行过程中，每个阶段的耗时情况：

```sql
show profile for query 4;
```

想查看执行过程中cpu的情况，可以执行以下命令：

```sql
show profile cpu for query 4;
```

### explain
explain命令可以查看一个DQL语句的执行计划，根据执行计划可以做出相应的优化措施。提高执行效率。

```sql
explain select * from xxx where xxx;
```

### 索引失效情况

**索引列参加了运算，索引失效**

```sql
explain select * from t_emp where sal*10 > 50000;
```
验证结果：索引失效

**索引列进行模糊查询时以 `%` 开始的，索引失效**

```sql
explain select * from t_emp where name like '%飞';
```
验证结果：索引失效

**索引列是字符串类型，但查询时省略了单引号，索引失效**

```sql
explain select * from t_emp where age=20;
```
验证结果：索引失效

**查询条件中有or，只要有未添加索引的字段，索引失效**

```sql
explain select * from t_emp where name='张三' or sal=5000;
```
验证结果：索引失效

**当查询的符合条件的记录在表中占比较大，索引失效**

**关于is null和is not null的索引失效问题**

走索引还是不走索引，与数据分布有很大关系，如果**符合条件的记录占比较大，会考虑使用全表扫描，而放弃走索引**。

### 前缀索引

一个字段类型是varchar或text字段，字段中存储的是文本或者大文本，直接对这种长文本创建索引，会让索引体积很大，此时可以**将字符串的前几个字符截取下来当做索引来创建**。这种索引被称为前缀索引。

```sql
# 前缀索引创建
create index idx_emp4_ename_2 on emp4(ename(2)); # 将ename字段值的前两个字符作为索引值
```

前缀索引取值规则如下：

```sql
select count(distinct substring(ename,1,前几个字符)) / count(*) from emp4;
```

以上查询结果越接近1，表示索引的效果越好。（原理：做索引值的话，索引值越具有唯一性效率越高）

### order by

将排序字段设置为索引（底层数据结构为B+树，已经排好序）

遵循左前缀原则，若全为升序或降序时，无需创建新索引

```sql
# 排序各字段规则不一致
explain select id,age,sal from workers order by age asc, sal desc;
```

若排序各字段规则不一致则需要创建新索引

```sql
create index idx_workers_ageasc_saldesc on workers(age asc, sal desc);
```

### group by

将分组字段设置为索引；遵循左前缀原则

### limit

使用覆盖索引，加子查询

### 主键优化

- 主键值不要太长，二级索引叶子结点上存储的是主键值，主键值太长，容易导致索引占用空间较大。
- 尽量使用`auto_increment`生成主键。尽量不要使用`uuid`做主键，因为`uuid`不是顺序插入。
- 最好不要使用业务主键，因为业务的变化会导致主键值的频繁修改，主键值不建议修改，因为主键值修改，聚集索引一定会重新排序。
- 在插入数据时，主键值最好是顺序插入，插入主键值如果是乱序的，B+树叶子结点需要不断的重新排序，重排过程中还会频繁涉及到**页分裂和页合并**的操作，效率较低。

### insert优化

- 批量插入：数据量较大时，不要一条一条插入，可以批量插入，当然，建议一次插入数据不超过1000条
```sql
insert into t_user(id,name,age) values (1,'jack',20),(2,'lucy',30),(3,'timi',22);
```

- 当插入大量数据时，建议手动开启事务和手动提交事务。
- 主键值建议采用顺序插入。
- 超大数据量插入可以考虑使用mysql提供的`load`指令，`load`指令可以将csv文件中的数据批量导入到数据库表当中，并且效率很高。

### count优化

分组函数count的使用方式：

- count(主键)
   - 原理：将每个主键值取出，累加
- count(常量值)
   - 原理：获取到每个常量值，累加
- count(字段)
   - 原理：取出字段的每个值，判断是否为NULL，不为NULL则累加。
- count(*)
   - 原理：不用取值，底层mysql做了优化，直接统计总行数，效率最高。

结论：如果你要统计一张表中数据的总行数，**建议使用 count(*)**

**若真正要提高效率可借助第三方工具，redis等**

### update优化

> 当存储引擎是InnoDB时，表的行级锁是针对索引添加的锁，如果索引失效了，或者不是索引列时，会提升为表级锁。

尽力避免开启表级锁;
因此，为了更新的效率，建议**update语句中where条件中的字段是添加索引的**。