# Java反射机制


## 实际使用案例

--- 

### 1. 假设你知道属性名

--- 

你知道以下这几条信息：

- 类名是：com.reflect.User
- 该类中有String类型的name属性和int类型的age属性。
- 另外你也知道该类的设计符合JavaBean规范。（也就是说属性私有化，对外提供setter和getter方法）

通过反射机制给User对象的name属性赋值zhangsan，给age属性赋值20岁。

```java
public class UserTest {
    public static void main(String[] args) throws Exception{
        // 已知类名
        String className = "com.reflect.User";
        // 已知属性名
        String propertyName = "age";

        // 通过反射机制给User对象的age属性赋值20岁
        Class<?> clazz = Class.forName(className);
        Object obj = clazz.newInstance(); // 创建对象

        // 根据属性名获取setter方法名
        String setMethodName = "set" + propertyName.toUpperCase().charAt(0) + propertyName.substring(1);

        // 获取Method
        Method setMethod = clazz.getDeclaredMethod(setMethodName, int.class);

        // 调用Method
        setMethod.invoke(obj, 20);

        System.out.println(obj);
    }
}

```