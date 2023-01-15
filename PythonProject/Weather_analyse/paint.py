# coding=gbk
import matplotlib.pyplot as plt
import csv
def paint(x,y,xlabel,ylabel,title):
    plt.rcParams["font.sans-serif"] = ['SimHei']
    plt.rcParams["axes.unicode_minus"] = False

    for x_data,y_data in zip(x,y):
        plt.bar(x_data, y_data,color = ['#FA8600'])

    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)

    plt.show()
def main(filename,title):
    temp=[]
    with open(filename, 'r', errors='ignore', newline='') as f:
        cr = csv.DictReader(f)
        for row in cr:
            temp.append(row)
    x=[]
    y=[]
    xlabel=list(temp[0].keys())[0]
    ylabel=list(temp[0].keys())[1]
    for i in temp:
        x.append(str(list(i.values())[0]))
        y.append(float(list(i.values())[1]))
    print(temp)
    print(x,y)
    paint(x,y,xlabel,ylabel,title)
if  __name__=='__main__':
    main('result/air.csv','全国过去24h空气质量Top20')
    main('result/avg_temp.csv','全国过去24h平均温度Top20')
    main('result/max_temp.csv', '全国过去24h最高温度Top20')
    main('result/min_temp.csv', '全国过去24h最低温度Top20')
    main('result/rain.csv', '全国过去24h累计降水量Top20')

