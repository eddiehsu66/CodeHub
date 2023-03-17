from django import forms
from django.forms import ModelForm, modelformset_factory
# forms.py是一个文件，用于存储表单，表单是一个类，用于处理用户提交的数据，比如用户登录时提交的用户名和密码，用户注册时提交的用户名，密码，邮箱等
from .models import (
    AcademicSession,# 学年
    AcademicTerm,#  学期
    SiteConfig,# 网站配置信息
    StudentClass,# 班级
    Subject,# 课程
)

SiteConfigForm = modelformset_factory(
    SiteConfig,
    fields=(
        "key",
        "value",
    ),
    extra=0,
)
# modelformset_factory()函数用于创建一个模型表单集，模型表单集是一个表单集，
# 它包含多个模型表单，模型表单集是一个类，用于处理用户提交的数据，比如用户登录时提交的用户名和密码，用户注册时提交的用户名，密码，邮箱等


class AcademicSessionForm(ModelForm):
    prefix = "Academic Session"
    # prefix是一个属性，用于设置表单的前缀
    class Meta:
        model = AcademicSession
        fields = ["name", "current"]
    # fields是一个属性，用于设置表单的字段，为"name"表示只显示name字段
    # model是一个属性，用于设置表单的模型，为AcademicSession表示该表单的模型为AcademicSession

class AcademicTermForm(ModelForm):
    prefix = "Academic Term"
    class Meta:
        model = AcademicTerm
        fields = ["name", "current"]

class SubjectForm(ModelForm):
    prefix = "Subject"

    class Meta:
        model = Subject
        fields = ["name"]


class StudentClassForm(ModelForm):
    # 用于创建学生班级表单
    prefix = "Class"

    class Meta:
        model = StudentClass
        fields = ["name"]


class CurrentSessionForm(forms.Form):
    current_session = forms.ModelChoiceField(
        queryset=AcademicSession.objects.all(),
        help_text='Click <a href="/session/create/?next=current-session/">here</a> to add new session',
    )
    # ModelChoiceField()函数用于创建一个模型选择字段，模型选择字段是一个表单字段。
    # queryset是一个属性，用于设置表单的查询集，为AcademicSession.objects.all()表示该表单的查询集为AcademicSession的所有对象
    current_term = forms.ModelChoiceField(
        queryset=AcademicTerm.objects.all(),
        help_text='Click <a href="/term/create/?next=current-session/">here</a> to add new term',
    )
