import requests
from bs4 import BeautifulSoup
import csv
import json
import xml.dom.minidom


def getHTMLtext(url):
    try:
        r = requests.get(url, timeout=30)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        bs = BeautifulSoup(r.text, "html.parser")  # 创建BeautifulSoup对象
        body = bs.body
        if (body):
            print("成功访问")
            return r.text
        else:
            print("空包")
            return 1
    except:
        print("访问错误")
        return 0


def get_content(html, area):
    bs = BeautifulSoup(html, "html.parser")  # 创建BeautifulSoup对象
    body = bs.body
    # 下面爬取当天的数据

    data2 = body.find_all('div', {'class': 'left-div'})
    text = data2[2].find('script').string
    text = text[text.index('=') + 1:-2]  # 移除改var data=将其变为json数据
    jd = json.loads(text)
    dayone = jd['od']['od2']
    final_day = []  # 存放当天的数据
    count = 0
    for i in dayone:
        temp = []
        if count == 0:
            count = count + 1
            continue
        if count <= 24:
            temp.append(area)  # 添加地区名称
            temp.append(i['od21'])  # 添加时间
            temp.append(i['od22'])  # 添加当前时刻温度
            temp.append(i['od25'])  # 添加当前时刻风级
            temp.append(i['od26'])  # 添加当前时刻降水量
            temp.append(i['od27'])  # 添加当前时刻相对湿度
            temp.append(i['od28'])  # 添加当前时刻控制质量
            final_day.append(temp)
        count = count + 1
    return final_day


def write_to_csv(file_name, data):
    with open(file_name, 'a', errors='ignore', newline='') as f:
        header = ['地区', '小时', '温度', '风级', '降水量', '相对湿度', '空气质量']
        f_csv = csv.writer(f)
        f_csv.writerow(header)
        f_csv.writerows(data)


def main():  # url = 'http://www.weather.com.cn/weather/101280701.shtml'  # 7天天气中国天气网
    dom = xml.dom.minidom.parse('id.xml')
    root = dom.documentElement
    county = root.getElementsByTagName('county')
    base = 'http://www.weather.com.cn/weather/'
    a = 0;
    for eachcounty in county:
        name = eachcounty.getAttribute('name')
        idcode = eachcounty.getAttribute('weatherCode')
        url = base + idcode + '.shtml'
        html = getHTMLtext(url)
        if html != 1 and html != 0:
            data = get_content(html, name)
            write_to_csv('weather_'+ str(a).zfill(3) + '.csv', data)
            a = a + 1
if __name__ == '__main__':
    main()
