#!/usr/bin/env python
"""Django's command-line utility for administrative tasks."""
import os
import sys


def main():
    os.environ.setdefault("DJANGO_SETTINGS_MODULE", "school_app.settings")
    #设置环境变量 DJANGO_SETTINGS_MODULE 为 school_app.settings，这个变量用于告诉 Django 使用哪个配置文件来启动项目。
    try:
        from django.core.management import execute_from_command_line
        #导入 Django 的命令行工具 execute_from_command_line，用于执行命令行操作。
    except ImportError as exc:
        raise ImportError(
            "Couldn't import Django. Are you sure it's installed and "
            "available on your PYTHONPATH environment variable? Did you "
            "forget to activate a virtual environment?"
        ) from exc
    execute_from_command_line(sys.argv)
    #执行命令行操作，sys.argv 是一个列表，其中包含了从命令行传递给程序的参数。这个函数会解析这些参数并执行相应的操作，例如运行开发服务器、创建数据库等。


if __name__ == "__main__":
    main()
