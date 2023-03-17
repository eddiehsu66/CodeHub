from django.db.models.signals import post_save
from django.dispatch import receiver

from .models import AcademicSession, AcademicTerm


@receiver(post_save, sender=AcademicSession)
# 监听post_save信号，当AcademicSession模型保存时，会调用after_saving_session函数
def after_saving_session(sender, created, instance, *args, **kwargs):
    """Change all academic sessions to false if this is true"""
    if instance.current is True:
    # 如果当前的学期是当前学年的，则将其他学年的学期设置为非当前学期
    # 通过exclude方法排除当前学年的学期，然后将其他学年的学期设置为非当前学期
        AcademicSession.objects.exclude(pk=instance.id).update(current=False)
    # exclude() 方法返回一个查询集，它不包含与查询集中的对象匹配的对象，之后调用update()方法，将其他学年的学期设置为非当前学期


@receiver(post_save, sender=AcademicTerm)
# 监听post_save信号，当AcademicTerm模型保存时，会调用after_saving_term函数
def after_saving_term(sender, created, instance, *args, **kwargs):
    """Change all academic terms to false if this is true."""
    if instance.current is True:
        AcademicTerm.objects.exclude(pk=instance.id).update(current=False)
        # exclude() 方法返回一个查询集，它不包含与查询集中的对象匹配的对象，之后调用update()方法，将其他学期设置为非当前学期
