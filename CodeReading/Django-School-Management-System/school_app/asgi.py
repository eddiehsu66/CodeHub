"""
ASGI config for newapp project.

It exposes the ASGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/3.0/howto/deployment/asgi/
"""
# 异步服务器ASGI 是异步服务器网关接口，是 Django 2.0 引入的新的异步处理框架。
# ASGI 应用程序是一个可调用的对象，用于处理来自客户端的请求，并返回响应。ASGI 应用程序可以由任何符合 ASGI 规范的异步 Web 服务器运行，例如 Uvicorn、Daphne 等。
import os

from django.core.asgi import get_asgi_application

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "newapp.settings")

application = get_asgi_application()
#获取WSGI应用程序，WSGI 服务器会将请求传递给 application 对象
#然后 application 对象会找到相应的视图函数来处理请求，并将处理结果返回给 WSGI 服务器，最终由 WSGI 服务器将响应发送回客户端。