# 用来记录spingboot学习笔记
使用spring-boot-demo来进行学习
### 第一节 demoHelloworld
文件结构说明:
* pom.xml为Maven构建说明文件
* main 中存放程序实际执行相关代码， test 存放程序测试相关代码，resources 存放静态文件，模板文件，应用配置
* DemoApplication.java 用来启动应用程序
* DemoAppllicationTests.java 
* Target存放生成文件

在/main/SpringBootDemoHelloworldApplication.java中，**@SpringBootApplication**是一个组合注解，包含以下三个方面:
* @Configuration表示这个类是一个配置类，会被 Spring 容器扫描。
* @EnableAutoConfiguration 注解表示启用自动配置，Spring Boot 根据你添加的 jar 包来自动配置项目。
* @ComponentScan 注解表示自动扫描包名下的组件，并注册为 Bean。

**@RestController**  是 Spring MVC 中的注解，表示这是一个控制器类，会处理 HTTP 请求。它是一个组合注解，包含了 @Controller 和 @ResponseBody 两个注解。

在其的main()方法中，SpringApplication.run(SpringBootDemoHelloworldApplication.class, args)，其是应用程序的入口，调用run方法来启动，第一个参数为启动类，第二个为命令行参数，string数组  

@GetMapping("/hello")用来映射http get请求，将该方法映射到/hello路径，之后调用sayHello()函数，@RequestParam()是获取请求中的参数值，之后绑定到方法参数上的 String who ，name="who"指代是表示请求中的参数名字为 "who",如果请求中没有这个参数，或者这个参数的值为空，那么将会使用默认值。

strUtil.isBlank()来判断who是否为空，strUtil.format，用来格式化字符串，返回类似于 _my name is {},who_ 此类格式字符串。

在测试文件中，/test/SpringBootDemoHelloworldApplicationTests.java中，@RunWith(SpringRunner.class)即为在JUnit测试SpringRunner.class（spring指提供的运行器）；@SpringBootTest在单元测试中启动整个Spring Boot应用程序，@Test，JUnit自动运行它们。

### 第二节 demo-properties  
就项目结构而言增加了/controller和/property，一般情况下，controller用来处理HTTP请求的组件，使用注解来映射到特定的URL路径上,property用于存储应用程序的配置信息，数据库连接，服务器地址等.    
>import cn.hutool.core.lang.Dict;  
>Dict.create().set(key,value);  
对于@Autowired修饰的字段或者方法,Spring容器会在创建这个类的实例时，自动为这个字段或者方法注入值。
对于/ApplicationProperty.java和/DeveloperProperty中:
* @Data注解可以自动生成getters,setters,equals,hashCode,toSteing等方法
* @Component注解表示该类为Spring组件  
* @Value("${application.name}") 和 @Value("${application.version}")，会自动读取配置文件中的属性值并进行赋值
* @ConfigurationProperties(prefix = "developer")，表示读取配置文件为以developer为前缀的属性。从property文件读取属性并进行赋值.
关于/resources/application.yml文件，其active为dev，其指向的便为application-dev.yml文件，即为dev环境

### 第三节 demo-actuator模块
spring-boot-starter-actuator 是 Spring Boot 提供的一个用于监控应用程序运行状态的模块。它通过暴露一系列的端点来提供应用程序的运行状态信息，包括内存使用情况、线程使用情况、请求和响应统计信息等。为了使用这个模块，只需要在项目中pom.yml中添加对应的依赖，并在application.yml中开启相应的端点即可。设置端点暴露的哪些内容，默认["health","info"]，设置"*"代表暴露所有可访问的端点
>< dependency>  
>    < groupId>org.springframework.boot< /groupId>  
>    < artifactId>spring-boot-starter-actuator< /artifactId>  
>< /dependency>    
缺点:没有可视化界面  

### 第四节 demo-Admin-client/server模块
Spring Boot Admin 可以监控 Spring Boot 单机或集群项目，它提供详细的健康 (Health)信息、内存信息、JVM 系统和环境属性、垃圾回收信息、日志设置和查看、定时任务查看、Spring Boot 缓存查看和管理等功能，感觉可以看作是对actuator的补充
client：在application.yml中，spring.boot.admin.client.url配置server的url，在pom.xml配置文档，需要配置:
>< dependency>
>     < groupId>de.codecentric< /groupId>
>     < artifactId>spring-boot-admin-starter-client< /artifactId>
>< /dependency>
server：在pom.xml配置
>< dependency>
>    < groupId>de.codecentric< /groupId>
>    < artifactId>spring-boot-admin-starter-server< /artifactId>
>< /dependency>  
