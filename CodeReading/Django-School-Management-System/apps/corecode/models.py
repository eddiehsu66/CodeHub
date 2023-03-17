from django.db import models

# Create your models here.


class SiteConfig(models.Model):
    """Site Configurations"""
    # SiteConfig存储网站配置信息 
    key = models.SlugField()
    #SlugField是一个字段，用于存储短字符串
    value = models.CharField(max_length=200)
    # CharField是一个字段，用于存储长字符串

    def __str__(self):
        return self.key

class AcademicSession(models.Model):
    """Academic Session"""

    name = models.CharField(max_length=200, unique=True)
    # unique=True表示该字段的值必须唯一
    current = models.BooleanField(default=True)
    # BooleanField是一个字段，用于存储布尔值
    class Meta:
        ordering = ["-name"]
    # ordering是一个属性，用于设置排序方式，为"-name"表示按照name字段的降序排列
    def __str__(self):
        return self.name


class AcademicTerm(models.Model):
    """Academic Term"""

    name = models.CharField(max_length=20, unique=True)
    current = models.BooleanField(default=True)

    class Meta:
        ordering = ["name"]
    # ordering是一个属性，用于设置排序方式，为"name"表示按照name字段的升序排列
    def __str__(self):
        return self.name


class Subject(models.Model):
    """Subject"""
    # Subject存储课程信息
    name = models.CharField(max_length=200, unique=True)

    class Meta:
        ordering = ["name"]

    def __str__(self):
        return self.name


class StudentClass(models.Model):
    # StudentClass存储班级信息
    name = models.CharField(max_length=200, unique=True)
    
    class Meta:
        verbose_name = "Class"
        verbose_name_plural = "Classes"
        ordering = ["name"]
    # verbose_name是一个属性，用于设置模型的单数名称
    # verbose_name_plural是一个属性，用于设置模型的复数名称
    # ordering是一个属性，用于设置排序方式，为"name"表示按照name字段的升序排列
    def __str__(self):
        return self.name
