"""
WSGI config for school_app project.

It exposes the WSGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/3.0/howto/deployment/wsgi/
"""
#同步服务器，WSGI是Web Server Gateway Interface的缩写，是Python语言定义的一种Web服务器和Web应用程序或框架之间的接口。
import os

from django.core.wsgi import get_wsgi_application

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "school_app.settings")
#设置环境变量，告诉Django使用哪个配置文件来启动项目。
application = get_wsgi_application()
#获取WSGI应用程序，ASGI 服务器会将请求传递给 application 对象
#然后 application 对象会找到相应的视图函数来处理请求，并将处理结果返回给 ASGI 服务器，最终由 ASGI 服务器将响应发送回客户端。
