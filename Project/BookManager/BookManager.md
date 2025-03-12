## Java Swing图书管理系统

### 数据库设计
E-R图：

分析：

* 用户user表
```sql
CREATE TABLE user (
    id INT PRIMARY KEY COMMENT '用户id 主键',
    username VARCHAR(255) NOT NULL COMMENT '用户名',
    password VARCHAR(255) NOT NULL COMMENT '密码',
    category INT NOT NULL COMMENT '用户类别', -- 角色 1 普通  2 管理员
    sex VARCHAR(1) NOT NULL COMMENT '用户性别',
    phone CHAR(11) NOT NULL COMMENT '用户电话'
);
```

* 图书类别表book_type
```sql
CREATE TABLE book_type (
    id INT PRIMARY KEY COMMENT '图书类别id 主键',
    type_name VARCHAR(255) NOT NULL COMMENT '图书类别名称',
    remark VARCHAR(255) NOT NULL COMMENT '图书类别说明'
);
```

* 图书表book
```sql
CREATE TABLE book (
    id INT PRIMARY KEY COMMENT '图书id 主键',
    book_name VARCHAR(255) NOT NULL COMMENT '图书名称',
    author VARCHAR(255) NOT NULL COMMENT '作者',
    publish VARCHAR(255) NOT NULL COMMENT '出版社',
    price DOUBLE NOT NULL COMMENT '图书价格',
    number INT NOT NULL COMMENT '图书数量',			-- 库存数量
    book_status TINYINT NOT NULL COMMENT '借阅状态', -- 状态 1 上架  2 下架
    remark VARCHAR(255) NOT NULL COMMENT '图书描述',
    type_id INT NOT NULL COMMENT '图书类别 外键 映射图书类别表',
    CONSTRAINT fk_type FOREIGN KEY (type_id)
        REFERENCES book_type (id)
);
```

* 借阅信息表
```sql
CREATE TABLE borrowInfo (
    id INT PRIMARY KEY COMMENT '图书借阅信息表id 主键',
    status INT NOT NULL COMMENT '借阅状态',		-- 借阅状态 1 在借  2 已还
    borrow_time BIGINT NOT NULL COMMENT '借阅时间',
    return_time BIGINT NOT NULL COMMENT '归还时间',
    user_id INT NOT NULL COMMENT '用户id 外键',
    book_id INT NOT NULL COMMENT '图书id 外键',
    CONSTRAINT fk_userid_borrow FOREIGN KEY (user_id)
        REFERENCES user (id),
    CONSTRAINT fk_bookid_borrow FOREIGN KEY (book_id)
        REFERENCES book (id)
);
```

### 业务流程
用户打开图书管理程序自动进入**登录页面**

#### 管理员
1. 管理员登录选择**管理员状态**进入管理员主页面
2. 从上方快捷栏位选择对应管理业务模块
    * 默认页面为用户管理页面
    * 选择书籍管理页面
    * 选择书籍类别管理页面

#### 普通用户
1. 用户通过**普通用户状态**登录进入主页面
    > 若没有账号，则可以点击下方**注册按钮**进入注册页面
2. 进入主页面后，通过选择对应模块按钮进入对应模块
    * 借书页面
        * 内部包含查询页面
    > 可以在已展示的图书中借阅，若没有则可以通过查询按钮查询

    * 还书页面

### 模块界面设计
一共设计**注册界面**，**用户主页面(user)**，**借阅图书界面(user)**，**归还图书界面(user)**，**管理用户界面(admin)**，**管理书籍界面(admin)**，**管理书籍类别界面(admin)** 8 个界面。

登录界面：

注册界面：

用户主页面(user)：

借阅图书界面(user)：内部含有查询图书功能

归还图书界面(user):

管理用户界面(admin)：

管理书籍界面(admin)：

管理书籍类别界面(admin)：

### 代码结构划分
划分为controller, dao, frame, model,utils，这 5 个包。

* dao: 用于存放进行数据库操作相关类
* frame: 用于存放Swing界面类
* model: 用于存放实体类
* controller: 用于对dao和frame包进行联动
> 数据库更新后，或界面中按钮等被按下后，界面对应的变化逻辑
* utils: 用于存放相关工具类



### 运行实例

# 11/14
完成了所有实体类的创建，JDBC工具类，登录工具类，SQL语句工具类，用户数据库操作UserDao类，登录界面和登录逻辑，注册界面搭建

注册逻辑未实现完成。

# 11/15
完成注册逻辑
用户主界面搭建
用户查询书籍和借书界面搭建

