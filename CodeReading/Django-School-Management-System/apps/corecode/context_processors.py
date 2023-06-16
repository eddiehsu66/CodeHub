from .models import AcademicSession, AcademicTerm, SiteConfig
# siteConfig是一个模型，用于存储网站的配置信息，比如网站的名称，网站的logo等
# context_processors.py是一个文件，用于存储上下文处理器，上下文处理器是一个函数，它会在每个请求中被调用，返回一个字典，这个字典会被添加到模板的上下文中
# contexts来负责桥接模板和视图，将模板中的变量和视图中的数据进行绑定，这样模板中的变量就可以使用视图中的数据了
def site_defaults(request):
    current_session = AcademicSession.objects.get(current=True)
    current_term = AcademicTerm.objects.get(current=True)
    vals = SiteConfig.objects.all()
    contexts = {
        "current_session": current_session.name,
        "current_term": current_term.name,
    }
    for val in vals:
        contexts[val.key] = val.value

    return contexts
    # contexts 使用字典的形式存储网站的配置信息，比如网站的名称，网站的logo等