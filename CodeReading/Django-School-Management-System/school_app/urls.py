"""newapp URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.conf import settings
from django.conf.urls.static import static
from django.urls import include, path

urlpatterns = [
    path("accounts/", include("django.contrib.auth.urls")),
    path("", include("apps.corecode.urls")),
    path("student/", include("apps.students.urls")),
    path("staff/", include("apps.staffs.urls")),
    path("finance/", include("apps.finance.urls")),
    path("result/", include("apps.result.urls")),
    # 如果一个请求的 URL 匹配了 accounts/，Django 会将这个请求转发给 django.contrib.auth.urls 模块中的 URL 模式去处理。
] + static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
# static() 函数用于生成一个 URL 模式，这个 URL 模式会将请求的 URL 转发给 Django 的文件处理视图，这个视图会在 MEDIA_ROOT 目录中查找对应的文件并返回给客户端。
# MEDIA_ROOT 是一个目录，用于存放上传的文件，这个目录是在 settings.py 中定义的。
# MEDIA_URL 是一个 URL，用于访问 MEDIA_ROOT 目录中的文件，这个 URL 也是在 settings.py 中定义的。
# static() 函数的第一个参数是 URL 模式，第二个参数是一个目录，这个目录是用于存放上传的文件的。
