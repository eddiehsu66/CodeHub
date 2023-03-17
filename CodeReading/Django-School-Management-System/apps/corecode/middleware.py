from .models import AcademicSession, AcademicTerm


class SiteWideConfigs:
    # 用于创建一个网站配置信息中间件
    def __init__(self, get_response):
        self.get_response = get_response
    # self.get_response`是一个可调用对象，它需要一个请求作为参数，并返回一个响应。
    def __call__(self, request):
    # 将current_session和current_term添加到响应中进行回复；
        current_session = AcademicSession.objects.get(current=True)
        current_term = AcademicTerm.objects.get(current=True)

        request.current_session = current_session
        request.current_term = current_term
        
        response = self.get_response(request)
        # 用于返回响应
        return response
