from django.apps import AppConfig

# 主要目的是允许开发者对Django应用程序进行各种配置。
class CorecodeConfig(AppConfig):
    name = "apps.corecode"

    def ready(self):
        import apps.corecode.signals
        # 用于执行任何需要在Django应用程序启动时完成的任务。
